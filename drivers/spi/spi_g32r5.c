/**
 * @file spi_g32r5.c
 * @author Quincy.W <wangqyfm@foxmail.com>
 * @brief G32R5 SPI as a Zephyr SPI controller
 * @version 0.1
 * @date 2026-10-12
 *
 * @copyright Copyright (c) 2025-2026
 *
 * Polling master driver. The baud generator is LSPCLK, and a legal
 * SCLK is in [LSPCLK/128, LSPCLK/4]. FIFO words are 16 bits wide and
 * transmit data is left-justified; received data is right-justified.
 * SPI_MODE_LOOP closes the internal SIMO-to-SOMI path and is rejected
 * unless the controller is master. Slave, LSB-first and multi-line
 * modes are not implemented.
 */

#define DT_DRV_COMPAT geehy_g32r5_spi

#include "spi.h"

/*
 * Zephyr's spi.h defines SPI_MODE_MASTER as a deprecated alias of
 * SPI_OP_MODE_CONTROLLER. Capture the HAL enumerator before that.
 */
enum {
	G32R5_SPI_CTRL_MASTER = SPI_MODE_MASTER,
};

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

LOG_MODULE_REGISTER(spi_g32r5, CONFIG_SPI_LOG_LEVEL);

#include "spi/spi_context.h"
#include "sysctl.h"

/* Clock-control subsystem id 2 is LSPCLK. See clock_control_g32r5.c. */
#define G32R5_LSPCLK_ID 2

struct g32r5_spi_config {
	uint32_t base;
	uint16_t overrun_char;
	const struct pinctrl_dev_config *pinctrl;
};

struct g32r5_spi_data {
	struct spi_context ctx;
	uint32_t lspclk_hz;
	uint32_t frequency;
	uint32_t operation;
	uint32_t word_timeout_cyc;
	bool hw_ready;
};

static int spi_enable_clock(uint32_t base)
{
	switch (base) {
	case SPIA_BASE:
		SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
		return 0;
#if defined(SPIB_BASE)
	case SPIB_BASE:
		SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);
		return 0;
#endif
	default:
		return -ENODEV;
	}
}

static int spi_check_bufs(const struct spi_buf_set *set, uint8_t dfs)
{
	size_t i;

	if (set == NULL) {
		return 0;
	}

	for (i = 0; i < set->count; i++) {
		if ((set->buffers[i].len % dfs) != 0U) {
			return -EINVAL;
		}
	}

	return 0;
}

static int spi_apply_config(const struct device *dev, const struct spi_config *config)
{
	const struct g32r5_spi_config *cfg = dev->config;
	struct g32r5_spi_data *data = dev->data;
	SPI_TransferProtocol protocol;
	uint32_t word_bits;
	uint32_t ratio;
	uint32_t timeout_us;

	if ((config->operation & SPI_OP_MODE_PERIPHERAL) != 0U) {
		return -ENOTSUP;
	}

	if ((config->operation & SPI_TRANSFER_LSB) != 0U) {
		return -ENOTSUP;
	}

	if ((config->operation & SPI_LINES_MASK) != SPI_LINES_SINGLE) {
		return -ENOTSUP;
	}

	word_bits = SPI_WORD_SIZE_GET(config->operation);
	if ((word_bits < 1U) || (word_bits > 16U) || (config->frequency == 0U) ||
	    (data->lspclk_hz == 0U)) {
		return -EINVAL;
	}

	/* BRR is 7 bits: SCLK = LSPCLK / (BRR + 1), and BRR + 1 is 4..128. */
	if (config->frequency > (data->lspclk_hz / 4U)) {
		return -EINVAL;
	}

	ratio = data->lspclk_hz / config->frequency;
	if ((ratio < 4U) || (ratio > 128U)) {
		return -EINVAL;
	}

	switch (config->operation & (SPI_MODE_CPOL | SPI_MODE_CPHA)) {
	case 0U:
		protocol = SPI_PROT_POL0PHA0;
		break;
	case SPI_MODE_CPHA:
		protocol = SPI_PROT_POL0PHA1;
		break;
	case SPI_MODE_CPOL:
		protocol = SPI_PROT_POL1PHA0;
		break;
	default:
		protocol = SPI_PROT_POL1PHA1;
		break;
	}

	SPI_disableModule(cfg->base);
	SPI_setConfig(cfg->base, data->lspclk_hz, protocol, (SPI_Mode)G32R5_SPI_CTRL_MASTER,
		      config->frequency, (uint16_t)word_bits);

	if ((config->operation & SPI_MODE_LOOP) != 0U) {
		SPI_enableLoopback(cfg->base);
	} else {
		SPI_disableLoopback(cfg->base);
	}

	SPI_enableFIFO(cfg->base);
	SPI_resetTxFIFO(cfg->base);
	SPI_resetRxFIFO(cfg->base);
	SPI_enableModule(cfg->base);

	timeout_us = ((word_bits * 1000000U) / config->frequency) + 1000U;
	data->word_timeout_cyc = k_us_to_cyc_ceil32(timeout_us);
	data->frequency = config->frequency;
	data->operation = config->operation;
	data->hw_ready = true;
	return 0;
}

static uint16_t spi_load_tx(struct spi_context *ctx, uint8_t dfs, uint32_t word_bits,
			    uint16_t overrun)
{
	uint16_t raw = overrun;
	uint32_t mask = (word_bits == 16U) ? 0xFFFFU : ((1U << word_bits) - 1U);

	if (spi_context_tx_buf_on(ctx)) {
		if (dfs == 1U) {
			raw = ctx->tx_buf[0];
		} else {
			memcpy(&raw, ctx->tx_buf, sizeof(raw));
		}
	}

	raw = (uint16_t)(raw & mask);
	return (uint16_t)(raw << (16U - word_bits));
}

static void spi_store_rx(struct spi_context *ctx, uint8_t dfs, uint32_t word_bits, uint16_t raw)
{
	uint32_t mask = (word_bits == 16U) ? 0xFFFFU : ((1U << word_bits) - 1U);

	raw = (uint16_t)(raw & mask);
	if (!spi_context_rx_buf_on(ctx)) {
		return;
	}

	if (dfs == 1U) {
		ctx->rx_buf[0] = (uint8_t)raw;
	} else {
		memcpy(ctx->rx_buf, &raw, sizeof(raw));
	}
}

static int spi_wait_rx(uint32_t base, uint32_t timeout_cyc)
{
	uint32_t start = k_cycle_get_32();

	while (SPI_getRxFIFOStatus(base) == SPI_FIFO_RXEMPTY) {
		if ((k_cycle_get_32() - start) > timeout_cyc) {
			return -ETIMEDOUT;
		}
	}

	return 0;
}

static int spi_shift(const struct device *dev, uint8_t dfs, uint32_t word_bits)
{
	const struct g32r5_spi_config *cfg = dev->config;
	struct g32r5_spi_data *data = dev->data;
	struct spi_context *ctx = &data->ctx;

	SPI_resetTxFIFO(cfg->base);
	SPI_resetRxFIFO(cfg->base);

	while (spi_context_tx_on(ctx) || spi_context_rx_on(ctx)) {
		uint16_t tx;
		int ret;

		tx = spi_load_tx(ctx, dfs, word_bits, cfg->overrun_char);
		SPI_writeDataNonBlocking(cfg->base, tx);

		ret = spi_wait_rx(cfg->base, data->word_timeout_cyc);
		if (ret < 0) {
			LOG_ERR("RX timeout");
			return ret;
		}

		spi_store_rx(ctx, dfs, word_bits, SPI_readDataNonBlocking(cfg->base));

		if (spi_context_tx_on(ctx)) {
			spi_context_update_tx(ctx, dfs, 1);
		}
		if (spi_context_rx_on(ctx)) {
			spi_context_update_rx(ctx, dfs, 1);
		}
	}

	return 0;
}

static int spi_g32r5_transceive(const struct device *dev, const struct spi_config *config,
				const struct spi_buf_set *tx_bufs, const struct spi_buf_set *rx_bufs)
{
	struct g32r5_spi_data *data = dev->data;
	uint32_t word_bits;
	uint8_t dfs;
	int ret;

	spi_context_lock(&data->ctx, false, NULL, NULL, config);

	word_bits = SPI_WORD_SIZE_GET(config->operation);
	dfs = (word_bits > 8U) ? 2U : 1U;

	ret = spi_check_bufs(tx_bufs, dfs);
	if (ret == 0) {
		ret = spi_check_bufs(rx_bufs, dfs);
	}
	if (ret < 0) {
		spi_context_unlock_unconditionally(&data->ctx);
		return ret;
	}

	if (!data->hw_ready || (data->frequency != config->frequency) ||
	    (data->operation != config->operation)) {
		ret = spi_apply_config(dev, config);
		if (ret < 0) {
			data->hw_ready = false;
			spi_context_unlock_unconditionally(&data->ctx);
			return ret;
		}
	}

	data->ctx.config = config;
	spi_context_cs_control(&data->ctx, true);
	spi_context_buffers_setup(&data->ctx, tx_bufs, rx_bufs, dfs);

	ret = spi_shift(dev, dfs, word_bits);
	if (ret < 0) {
		spi_context_unlock_unconditionally(&data->ctx);
		return ret;
	}

	spi_context_cs_control(&data->ctx, false);
	spi_context_release(&data->ctx, 0);
	return 0;
}

static int spi_g32r5_release(const struct device *dev, const struct spi_config *config)
{
	struct g32r5_spi_data *data = dev->data;

	ARG_UNUSED(config);
	spi_context_unlock_unconditionally(&data->ctx);
	return 0;
}

static DEVICE_API(spi, g32r5_spi_api) = {
	.transceive = spi_g32r5_transceive,
	.release = spi_g32r5_release,
};

static int g32r5_spi_init(const struct device *dev)
{
	const struct device *clk = DEVICE_DT_GET(DT_NODELABEL(sysclk));
	const struct g32r5_spi_config *cfg = dev->config;
	struct g32r5_spi_data *data = dev->data;
	int ret;

	if (!device_is_ready(clk)) {
		return -ENODEV;
	}

	ret = clock_control_get_rate(clk, (clock_control_subsys_t)G32R5_LSPCLK_ID,
				     &data->lspclk_hz);
	if (ret < 0) {
		return ret;
	}

	ret = pinctrl_apply_state(cfg->pinctrl, PINCTRL_STATE_DEFAULT);
	if ((ret < 0) && (ret != -ENOENT)) {
		return ret;
	}

	ret = spi_enable_clock(cfg->base);
	if (ret < 0) {
		return ret;
	}

	/* PCLKCR is not ordered with the first access of the SPI block. */
	k_busy_wait(1);

	SPI_disableModule(cfg->base);
	SPI_disableInterrupt(cfg->base, SPI_INT_RX_OVERRUN | SPI_INT_RX_DATA_TX_EMPTY |
					     SPI_INT_RXFF | SPI_INT_TXFF);

	ret = spi_context_cs_configure_all(&data->ctx);
	if (ret < 0) {
		return ret;
	}

	spi_context_unlock_unconditionally(&data->ctx);
	return 0;
}

#define G32R5_SPI_INIT(n)                                                                          \
	PINCTRL_DT_INST_DEFINE(n);                                                                 \
	static struct g32r5_spi_data g32r5_spi_data_##n = {                                        \
		SPI_CONTEXT_INIT_LOCK(g32r5_spi_data_##n, ctx),                                    \
		SPI_CONTEXT_INIT_SYNC(g32r5_spi_data_##n, ctx),                                    \
		SPI_CONTEXT_CS_GPIOS_INITIALIZE(DT_DRV_INST(n), ctx)};                             \
	static const struct g32r5_spi_config g32r5_spi_config_##n = {                              \
		.base = DT_INST_REG_ADDR(n),                                                       \
		.overrun_char = (uint16_t)DT_INST_PROP_OR(n, overrun_character, 0),                \
		.pinctrl = PINCTRL_DT_INST_DEV_CONFIG_GET(n),                                      \
	};                                                                                         \
	DEVICE_DT_INST_DEFINE(n, g32r5_spi_init, NULL, &g32r5_spi_data_##n,                        \
			      &g32r5_spi_config_##n, POST_KERNEL, CONFIG_SPI_INIT_PRIORITY,        \
			      &g32r5_spi_api);

DT_INST_FOREACH_STATUS_OKAY(G32R5_SPI_INIT)
