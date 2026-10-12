/*
 * Copyright (c) 2026, Quincy.W <wangqyfm@foxmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Mode 3 is the edge this glass samples. INVON (0x21) is required for a
 * primary color: 0xF800 is pure red, 0x07E0 pure green, 0x001F pure blue.
 * INVOFF shows the complement, so red bytes look cyan.
 */

#include <stdint.h>

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/kernel.h>

#define PANEL_HZ   1000000U
#define PANEL_W    240U
#define PANEL_ROWS 320U

static const struct device *const spi = DEVICE_DT_GET(DT_NODELABEL(spia));
static const struct gpio_dt_spec dc = GPIO_DT_SPEC_GET(DT_NODELABEL(mipi_dbi_atk), dc_gpios);
static const struct gpio_dt_spec reset = GPIO_DT_SPEC_GET(DT_NODELABEL(mipi_dbi_atk), reset_gpios);
static const struct gpio_dt_spec cs_gpio = GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(spia), cs_gpios, 0);

static struct spi_config panel_cfg(uint16_t mode_flags)
{
	struct spi_config cfg = {
		.frequency = PANEL_HZ,
		.operation = SPI_OP_MODE_CONTROLLER | SPI_WORD_SET(8) | SPI_HOLD_ON_CS | mode_flags,
		.cs = {
			.gpio = cs_gpio,
			.delay = 10,
			.cs_is_gpio = true,
		},
	};

	return cfg;
}

static int panel_bytes(struct spi_config *cfg, bool is_data, const uint8_t *buf, size_t len)
{
	const struct spi_buf tx = {
		.buf = (void *)buf,
		.len = len,
	};
	const struct spi_buf_set txs = {
		.buffers = &tx,
		.count = 1,
	};
	int ret;

	ret = gpio_pin_set_dt(&dc, is_data ? 1 : 0);
	if (ret < 0) {
		return ret;
	}

	return spi_write(spi, cfg, &txs);
}

static int panel_cmd(struct spi_config *cfg, uint8_t cmd, const uint8_t *data, size_t len)
{
	int ret;

	ret = panel_bytes(cfg, false, &cmd, 1);
	if ((ret == 0) && (data != NULL) && (len > 0U)) {
		ret = panel_bytes(cfg, true, data, len);
	}

	spi_release(spi, cfg);
	return ret;
}

static int panel_reset(void)
{
	int ret;

	ret = gpio_pin_set_dt(&cs_gpio, 0);
	if (ret < 0) {
		return ret;
	}

	ret = gpio_pin_configure_dt(&reset, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return ret;
	}

	gpio_pin_set_dt(&reset, 1);
	k_msleep(10);
	gpio_pin_set_dt(&reset, 0);
	k_msleep(120);
	return 0;
}

static int panel_wake(struct spi_config *cfg, uint8_t madctl)
{
	static const uint8_t colmod = 0x55;
	int ret;

	ret = panel_reset();
	if (ret < 0) {
		return ret;
	}

	ret = panel_cmd(cfg, 0x01, NULL, 0);
	if (ret < 0) {
		return ret;
	}
	k_msleep(120);

	ret = panel_cmd(cfg, 0x11, NULL, 0);
	if (ret < 0) {
		return ret;
	}
	k_msleep(120);

	ret = panel_cmd(cfg, 0x36, &madctl, 1);
	ret |= panel_cmd(cfg, 0x3A, &colmod, 1);
	ret |= panel_cmd(cfg, 0x21, NULL, 0);
	ret |= panel_cmd(cfg, 0x13, NULL, 0);
	ret |= panel_cmd(cfg, 0x29, NULL, 0);
	k_msleep(20);
	return ret;
}

static int panel_fill(struct spi_config *cfg, uint8_t hi, uint8_t lo)
{
	static uint8_t line[PANEL_W * 2U];
	uint8_t window[4];
	uint8_t cmd;
	size_t i;
	int ret;

	for (i = 0; i < sizeof(line); i += 2U) {
		line[i] = hi;
		line[i + 1U] = lo;
	}

	window[0] = 0x00;
	window[1] = 0x00;
	window[2] = (uint8_t)((PANEL_W - 1U) >> 8);
	window[3] = (uint8_t)(PANEL_W - 1U);
	ret = panel_cmd(cfg, 0x2A, window, 4);
	window[2] = (uint8_t)((PANEL_ROWS - 1U) >> 8);
	window[3] = (uint8_t)(PANEL_ROWS - 1U);
	ret |= panel_cmd(cfg, 0x2B, window, 4);
	if (ret < 0) {
		return ret;
	}

	cmd = 0x2C;
	ret = panel_bytes(cfg, false, &cmd, 1);
	for (i = 0; (ret == 0) && (i < PANEL_ROWS); i++) {
		ret = panel_bytes(cfg, true, line, sizeof(line));
	}
	spi_release(spi, cfg);
	return ret;
}

static int panel_show(const char *name, uint16_t mode_flags, uint8_t hi, uint8_t lo)
{
	struct spi_config cfg = panel_cfg(mode_flags);
	int ret;

	printk("panel %s: cs pin %u, reset then fill\n", name, cs_gpio.pin);
	ret = panel_wake(&cfg, 0x00);
	printk("panel %s: wake %d\n", name, ret);
	if (ret < 0) {
		return ret;
	}

	ret = panel_fill(&cfg, hi, lo);
	printk("panel %s: fill %d, red for 3s then lvgl\n", name, ret);
	k_msleep(3000);
	return ret;
}

static int panel_check(void)
{
	int ret;

	if (!device_is_ready(spi) || !gpio_is_ready_dt(&dc) || !gpio_is_ready_dt(&reset) ||
	    !gpio_is_ready_dt(&cs_gpio)) {
		printk("panel check: pin or spi not ready\n");
		return -ENODEV;
	}

	return panel_show("mode3 red", SPI_MODE_CPOL | SPI_MODE_CPHA, 0xF8, 0x00);
}

SYS_INIT(panel_check, APPLICATION, 50);
