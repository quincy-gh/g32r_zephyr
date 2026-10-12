/*
 * Copyright (c) 2026, Quincy.W <wangqyfm@foxmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Two-board SPI link. Use the expansion headers, not the CAN or QSPI
 * sockets. Connect:
 *
 *   GND ---- GND
 *   GPIO12 - GPIO12  SPIA CLK
 *   GPIO11 - GPIO11  SPIA SIMO (master out, slave in)
 *   GPIO1 -- GPIO1   SPIA SOMI (master in, slave out)
 *   GPIO0 -- GPIO0   SPIA STE, active low
 *   GPIO13 - GPIO13  501 ready, active low
 *   GPIO17 - GPIO17  502 ready, active low
 *
 * SIMO ties to SIMO. The current master drives that net and the slave
 * pin is an input, so the same wires still work after the role swap.
 * Do not use GPIO2/3 (501 CAN via S5), GPIO4/5 (502 CAN), GPIO8-10
 * (501 QSPI), GPIO16 (XCLKOUT), GPIO28/29 (console), or the LED pins.
 *
 * Each mode runs both directions at 10 MHz: phase 1 has 501 as master,
 * phase 2 swaps. The driver has no peripheral mode, so the slave side
 * programs the HAL directly and left-justifies each byte the same way
 * the master driver does. 10 MHz is exact on both clocks (501 LSPCLK
 * 60 MHz / 6, 502 LSPCLK 50 MHz / 5).
 */

#include "spi.h"

#include <stdint.h>
#include <string.h>

#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/kernel.h>
#include <zephyr/ztest.h>

#define LINK_HZ       10000000U
#define LINK_WORDS    8U
#define LINK_WAIT_MS  20000
#define PIN_501_READY 13U
#define PIN_502_READY 17U
#define G32R5_LSPCLK_ID 2

#if defined(CONFIG_SOC_SERIES_G32R502)
#define LINK_IS_502 1
#else
#define LINK_IS_502 0
#endif

static const struct device *const spi = DEVICE_DT_GET(DT_NODELABEL(spia));
static const struct device *const gpioa = DEVICE_DT_GET(DT_NODELABEL(gpioa));
static const uint32_t spi_base = DT_REG_ADDR(DT_NODELABEL(spia));

struct link_mode {
	const char *name;
	uint16_t flags;
	SPI_TransferProtocol protocol;
	uint8_t p1_master;
	uint8_t p1_slave;
	uint8_t p2_master;
	uint8_t p2_slave;
};

static const struct link_mode link_modes[] = {
	{ "mode0", 0U, SPI_PROT_POL0PHA0, 0x10, 0x80, 0x20, 0x90 },
	{ "mode1", SPI_MODE_CPHA, SPI_PROT_POL0PHA1, 0x30, 0xA0, 0x40, 0xB0 },
	{ "mode2", SPI_MODE_CPOL, SPI_PROT_POL1PHA0, 0x50, 0xC0, 0x60, 0xD0 },
	{ "mode3", SPI_MODE_CPOL | SPI_MODE_CPHA, SPI_PROT_POL1PHA1, 0x70, 0xE0, 0x18, 0xF0 },
};

static uint32_t lspclk_hz;

static void link_dump(const char *name, const uint8_t *buf, size_t len)
{
	size_t i;

	printk("%s:", name);
	for (i = 0; i < len; i++) {
		printk(" %02x", buf[i]);
	}
	printk("\n");
}

static int link_wait_low(gpio_pin_t pin)
{
	int64_t end = k_uptime_get() + LINK_WAIT_MS;

	while (k_uptime_get() < end) {
		if (gpio_pin_get(gpioa, pin) == 0) {
			return 0;
		}
		k_msleep(1);
	}

	return -ETIMEDOUT;
}

static void link_pattern(uint8_t *buf, uint8_t base)
{
	size_t i;

	for (i = 0; i < LINK_WORDS; i++) {
		buf[i] = (uint8_t)(base + i);
	}
}

static int link_slave(const uint8_t *tx, uint8_t *rx, size_t len, gpio_pin_t ready_pin,
		      SPI_TransferProtocol protocol)
{
	int64_t end;
	size_t i;

	if ((len == 0U) || (len > 16U) || (lspclk_hz == 0U)) {
		return -EINVAL;
	}

	SPI_disableModule(spi_base);
	SPI_setConfig(spi_base, lspclk_hz, protocol, SPI_MODE_SLAVE, LINK_HZ, 8U);
	SPI_disableLoopback(spi_base);
	SPI_setSTESignalPolarity(spi_base, SPI_STE_ACTIVE_LOW);
	SPI_enableFIFO(spi_base);
	SPI_resetTxFIFO(spi_base);
	SPI_resetRxFIFO(spi_base);
	SPI_enableModule(spi_base);

	for (i = 0; i < len; i++) {
		SPI_writeDataNonBlocking(spi_base, (uint16_t)tx[i] << 8);
	}

	gpio_pin_set(gpioa, ready_pin, 0);

	end = k_uptime_get() + LINK_WAIT_MS;
	while ((uint32_t)SPI_getRxFIFOStatus(spi_base) < len) {
		if (k_uptime_get() >= end) {
			gpio_pin_set(gpioa, ready_pin, 1);
			return -ETIMEDOUT;
		}
	}

	for (i = 0; i < len; i++) {
		rx[i] = (uint8_t)(SPI_readDataNonBlocking(spi_base) & 0xFFU);
	}

	gpio_pin_set(gpioa, ready_pin, 1);
	return 0;
}

static int link_master(const uint8_t *tx, uint8_t *rx, size_t len, gpio_pin_t peer_ready,
		       uint16_t mode_flags)
{
	const struct spi_buf txb = {
		.buf = (void *)tx,
		.len = len,
	};
	const struct spi_buf rxb = {
		.buf = rx,
		.len = len,
	};
	const struct spi_buf_set txs = {
		.buffers = &txb,
		.count = 1,
	};
	const struct spi_buf_set rxs = {
		.buffers = &rxb,
		.count = 1,
	};
	const struct spi_config cfg = {
		.frequency = LINK_HZ,
		.operation = SPI_OP_MODE_CONTROLLER | SPI_WORD_SET(8) | mode_flags,
	};
	int ret;

	ret = link_wait_low(peer_ready);
	if (ret < 0) {
		return ret;
	}

	/* Slave FIFO is loaded before it drives ready. Give STE a quiet edge. */
	k_busy_wait(100);
	return spi_transceive(spi, &cfg, &txs, &rxs);
}

static void link_check(const char *phase, const uint8_t *tx, const uint8_t *expect,
		       const uint8_t *rx)
{
	link_dump(phase, rx, LINK_WORDS);
	zassert_mem_equal(rx, expect, LINK_WORDS, "%s payload mismatch", phase);
	ARG_UNUSED(tx);
}

static void link_before(void *fixture)
{
	const struct device *clk = DEVICE_DT_GET(DT_NODELABEL(sysclk));
	gpio_pin_t own_ready = LINK_IS_502 ? PIN_502_READY : PIN_501_READY;
	gpio_pin_t peer_ready = LINK_IS_502 ? PIN_501_READY : PIN_502_READY;
	int ret;

	ARG_UNUSED(fixture);
	printk("spi link wires: GND, GPIO12 CLK, GPIO11 SIMO, GPIO1 SOMI, GPIO0 STE\n");
	printk("spi link ready: GPIO13 from 501, GPIO17 from 502, both active low\n");
	printk("spi link rate: %u Hz, modes 0-3\n", LINK_HZ);

	zassert_true(device_is_ready(spi));
	zassert_true(device_is_ready(gpioa));
	zassert_true(device_is_ready(clk));

	ret = clock_control_get_rate(clk, (clock_control_subsys_t)G32R5_LSPCLK_ID, &lspclk_hz);
	zassert_ok(ret);
	zassert_true(lspclk_hz >= (LINK_HZ * 4U));

	ret = gpio_pin_configure(gpioa, own_ready, GPIO_OUTPUT_HIGH | GPIO_PULL_UP);
	zassert_ok(ret);
	ret = gpio_pin_configure(gpioa, peer_ready, GPIO_INPUT | GPIO_PULL_UP);
	zassert_ok(ret);
}

ZTEST(g32r5_spi_link, test_both_roles)
{
	size_t mode_index;

	for (mode_index = 0; mode_index < ARRAY_SIZE(link_modes); mode_index++) {
		const struct link_mode *mode = &link_modes[mode_index];
		uint8_t m1_tx[LINK_WORDS];
		uint8_t s1_tx[LINK_WORDS];
		uint8_t m2_tx[LINK_WORDS];
		uint8_t s2_tx[LINK_WORDS];
		uint8_t rx[LINK_WORDS];
		char label[40];
		int ret;

		link_pattern(m1_tx, mode->p1_master);
		link_pattern(s1_tx, mode->p1_slave);
		link_pattern(m2_tx, mode->p2_master);
		link_pattern(s2_tx, mode->p2_slave);
		memset(rx, 0, sizeof(rx));

		if (LINK_IS_502) {
			printk("%s phase 1: 502 slave\n", mode->name);
			ret = link_slave(s1_tx, rx, LINK_WORDS, PIN_502_READY, mode->protocol);
			zassert_ok(ret, "%s 502 slave timed out; check CLK/STE/SIMO and GPIO17",
				   mode->name);
			snprintk(label, sizeof(label), "%s phase1 502 rx", mode->name);
			link_check(label, s1_tx, m1_tx, rx);

			printk("%s phase 2: 502 master\n", mode->name);
			memset(rx, 0, sizeof(rx));
			ret = link_master(m2_tx, rx, LINK_WORDS, PIN_501_READY, mode->flags);
			zassert_ok(ret, "%s 502 master timed out waiting for 501 ready on GPIO13",
				   mode->name);
			snprintk(label, sizeof(label), "%s phase2 502 rx", mode->name);
			link_check(label, m2_tx, s2_tx, rx);
		} else {
			printk("%s phase 1: 501 master\n", mode->name);
			ret = link_master(m1_tx, rx, LINK_WORDS, PIN_502_READY, mode->flags);
			zassert_ok(ret, "%s 501 master timed out waiting for 502 ready on GPIO17",
				   mode->name);
			snprintk(label, sizeof(label), "%s phase1 501 rx", mode->name);
			link_check(label, m1_tx, s1_tx, rx);

			printk("%s phase 2: 501 slave\n", mode->name);
			memset(rx, 0, sizeof(rx));
			ret = link_slave(s2_tx, rx, LINK_WORDS, PIN_501_READY, mode->protocol);
			zassert_ok(ret, "%s 501 slave timed out; check CLK/STE/SIMO and GPIO13",
				   mode->name);
			snprintk(label, sizeof(label), "%s phase2 501 rx", mode->name);
			link_check(label, s2_tx, m2_tx, rx);
		}
	}
}

ZTEST_SUITE(g32r5_spi_link, NULL, NULL, link_before, NULL, NULL);
