/**
 * @file uart_g32r5.c
 * @author Quincy.W <wangqyfm@foxmail.com>
 * @brief 
 * @version 0.2
 * @date 2026-10-09
 * 
 * @copyright Copyright (c) 2025-2026
 * 
 */

#define DT_DRV_COMPAT geehy_g32r5_uart

#include <errno.h>
#include <stdint.h>

#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/irq.h>
#include <zephyr/sys/util.h>

#include "uart.h"
#include "sysctl.h"

#define G32R5_LSPCLK_ID 2
#define G32R5_UART_FIFO_DEPTH 16U

#if defined(CONFIG_UART_G32R5_FIFO)
#define G32R5_UART_TX_IRQ UART_INT_TXFF
#define G32R5_UART_RX_IRQ UART_INT_RXFF
#else
#define G32R5_UART_TX_IRQ UART_INT_TXRDY
#define G32R5_UART_RX_IRQ UART_INT_RXRDY_BRKDT
#endif

struct g32r5_uart_config {
	uint32_t base;
	const struct pinctrl_dev_config *pinctrl;
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	void (*irq_config_func)(const struct device *dev);
#endif
};

struct g32r5_uart_data {
	uint32_t baud_rate;
	uint32_t lspclk_hz;
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	uart_irq_callback_user_data_t user_cb;
	void *user_data;
#endif
};

static int uart_enable_clock(uint32_t base)
{
	switch (base) {
	case UARTA_BASE:
		SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTA);
		return 0;
	case UARTB_BASE:
		SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTB);
		return 0;
#if defined(UARTC_BASE)
	case UARTC_BASE:
		SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTC);
		return 0;
#endif
	default:
		return -ENODEV;
	}
}

static bool uart_rx_available(uint32_t base)
{
#if defined(CONFIG_UART_G32R5_FIFO)
	return UART_getRxFIFOStatus(base) != UART_FIFO_RX0;
#else
	return UART_isDataAvailableNonFIFO(base);
#endif
}

static uint32_t uart_tx_space(uint32_t base)
{
#if defined(CONFIG_UART_G32R5_FIFO)
	uint32_t level = (uint32_t)UART_getTxFIFOStatus(base);

	if (level >= G32R5_UART_FIFO_DEPTH) {
		return 0U;
	}

	return G32R5_UART_FIFO_DEPTH - level;
#else
	return UART_isSpaceAvailableNonFIFO(base) ? 1U : 0U;
#endif
}

#if defined(CONFIG_UART_G32R5_FIFO)
/* Level bits read back as zero on this SCI, so every RMW must rewrite them. */
static uint16_t fftx_keep_level(uint16_t value)
{
	value &= (uint16_t)~UART_FFTX_TXFFIL_M;
	value |= (uint16_t)CONFIG_UART_G32R5_FIFO_TX_THRESHOLD;
	return value;
}

static uint16_t ffrx_keep_level(uint16_t value)
{
	value &= (uint16_t)~UART_FFRX_RXFFIL_M;
	value |= (uint16_t)CONFIG_UART_G32R5_FIFO_RX_THRESHOLD;
	return value;
}
#endif

static void uart_buffer_setup(uint32_t base)
{
#if defined(CONFIG_UART_G32R5_FIFO)
	uint16_t tx;
	uint16_t rx;

	/*
	 * UART_setConfig() clears SCIFFENA. Hold the FIFOs in reset, then
	 * release them in the same write that programs the level. A later
	 * read-modify-write would store zeros back into the level field.
	 */
	UART_enableFIFO(base);
	HWREGH(base + UART_O_FFTX) &= (uint16_t)~UART_FFTX_TXFIFORESET;
	HWREGH(base + UART_O_FFRX) &= (uint16_t)~UART_FFRX_RXFIFORESET;

	tx = fftx_keep_level(HWREGH(base + UART_O_FFTX) | UART_FFTX_TXFIFORESET);
	rx = ffrx_keep_level(HWREGH(base + UART_O_FFRX) | UART_FFRX_RXFIFORESET |
			     UART_FFRX_RXFFOVRCLR);
	HWREGH(base + UART_O_FFTX) = tx;
	HWREGH(base + UART_O_FFRX) = rx;
#else
	UART_disableFIFO(base);
#endif
}

#if defined(CONFIG_UART_INTERRUPT_DRIVEN)
static bool uart_tx_irq_enabled(uint32_t base)
{
#if defined(CONFIG_UART_G32R5_FIFO)
	return (HWREGH(base + UART_O_FFTX) & UART_FFTX_TXFFIENA) != 0U;
#else
	return (HWREGH(base + UART_O_CTL2) & UART_CTL2_TXINTENA) != 0U;
#endif
}

static bool uart_rx_irq_enabled(uint32_t base)
{
#if defined(CONFIG_UART_G32R5_FIFO)
	return (HWREGH(base + UART_O_FFRX) & UART_FFRX_RXFFIENA) != 0U;
#else
	return (HWREGH(base + UART_O_CTL2) & UART_CTL2_RXBKINTENA) != 0U;
#endif
}
#endif

static uint32_t uart_hw_config(uint8_t data_bits, uint8_t stop_bits, uint8_t parity)
{
	uint32_t config = 0U;

	switch (data_bits) {
	case UART_CFG_DATA_BITS_5:
		config |= UART_CONFIG_WLEN_5;
		break;
	case UART_CFG_DATA_BITS_6:
		config |= UART_CONFIG_WLEN_6;
		break;
	case UART_CFG_DATA_BITS_7:
		config |= UART_CONFIG_WLEN_7;
		break;
	case UART_CFG_DATA_BITS_8:
		config |= UART_CONFIG_WLEN_8;
		break;
	default:
		return 0U;
	}

	if (stop_bits == UART_CFG_STOP_BITS_2) {
		config |= UART_CONFIG_STOP_TWO;
	} else if (stop_bits != UART_CFG_STOP_BITS_1) {
		return 0U;
	}

	switch (parity) {
	case UART_CFG_PARITY_NONE:
		config |= UART_CONFIG_PAR_NONE;
		break;
	case UART_CFG_PARITY_EVEN:
		config |= UART_CONFIG_PAR_EVEN;
		break;
	case UART_CFG_PARITY_ODD:
		config |= UART_CONFIG_PAR_ODD;
		break;
	default:
		return 0U;
	}

	return config;
}

static int uart_apply_format(const struct device *dev, uint32_t baud, uint32_t hw_config)
{
	const struct g32r5_uart_config *cfg = dev->config;
	struct g32r5_uart_data *data = dev->data;

	if ((baud == 0U) || (data->lspclk_hz / 16U < baud)) {
		return -EINVAL;
	}

	UART_setConfig(cfg->base, data->lspclk_hz, baud, hw_config);
	data->baud_rate = baud;
	return 0;
}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void g32r5_uart_isr(const struct device *dev)
{
	struct g32r5_uart_data *data = dev->data;

	if (data->user_cb != NULL) {
		data->user_cb(dev, data->user_data);
	}
}
#endif

static int g32r5_uart_init(const struct device *dev)
{
	const struct device *clk = DEVICE_DT_GET(DT_NODELABEL(sysclk));
	const struct g32r5_uart_config *cfg = dev->config;
	struct g32r5_uart_data *data = dev->data;
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
	if (ret < 0) {
		return ret;
	}

	ret = uart_enable_clock(cfg->base);
	if (ret < 0) {
		return ret;
	}

	UART_performSoftwareReset(cfg->base);
	ret = uart_apply_format(dev, data->baud_rate,
				UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
					UART_CONFIG_PAR_NONE);
	if (ret < 0) {
		return ret;
	}

	UART_resetChannels(cfg->base);
	UART_disableInterrupt(cfg->base, UART_INT_RXRDY_BRKDT | UART_INT_TXRDY | UART_INT_RXERR |
						 UART_INT_TXFF | UART_INT_RXFF);
	uart_buffer_setup(cfg->base);
	UART_enableModule(cfg->base);

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	cfg->irq_config_func(dev);
#endif

	return 0;
}

static int g32r5_uart_poll_in(const struct device *dev, unsigned char *c)
{
	const struct g32r5_uart_config *cfg = dev->config;

	if (!uart_rx_available(cfg->base)) {
		return -1;
	}

	*c = UART_readCharNonBlocking(cfg->base);
	return 0;
}

static void g32r5_uart_poll_out(const struct device *dev, unsigned char c)
{
	const struct g32r5_uart_config *cfg = dev->config;

	while (uart_tx_space(cfg->base) == 0U) {
	}

	UART_writeCharNonBlocking(cfg->base, c);
}

static int g32r5_uart_err_check(const struct device *dev)
{
	const struct g32r5_uart_config *cfg = dev->config;
	uint16_t status = UART_getRxStatus(cfg->base);
	int errors = 0;

	if ((status & UART_RXST_OE) != 0U) {
		errors |= UART_ERROR_OVERRUN;
	}
	if ((status & UART_RXST_PE) != 0U) {
		errors |= UART_ERROR_PARITY;
	}
	if ((status & UART_RXST_FE) != 0U) {
		errors |= UART_ERROR_FRAMING;
	}
	if ((status & UART_RXST_BRKDT) != 0U) {
		errors |= UART_BREAK;
	}
#if defined(CONFIG_UART_G32R5_FIFO)
	if (UART_getOverflowStatus(cfg->base)) {
		uint16_t rx = HWREGH(cfg->base + UART_O_FFRX);

		errors |= UART_ERROR_OVERRUN;
		HWREGH(cfg->base + UART_O_FFRX) =
			ffrx_keep_level(rx | UART_FFRX_RXFFOVRCLR);
	}
#endif

	/*
	 * RXST error flags are cleared by a module software reset.
	 * UART_clearInterruptStatus() does that for these sources and
	 * does not change baud or frame format.
	 */
	if (errors != 0) {
		UART_clearInterruptStatus(cfg->base, UART_INT_FE | UART_INT_OE |
							      UART_INT_PE | UART_INT_RXERR);
	}

	return errors;
}

#ifdef CONFIG_UART_USE_RUNTIME_CONFIGURE
static int g32r5_uart_configure(const struct device *dev, const struct uart_config *cfg_in)
{
	const struct g32r5_uart_config *cfg = dev->config;
	uint32_t hw_config;
	int ret;

	if (cfg_in->flow_ctrl != UART_CFG_FLOW_CTRL_NONE) {
		return -ENOTSUP;
	}

	hw_config = uart_hw_config(cfg_in->data_bits, cfg_in->stop_bits, cfg_in->parity);
	if (hw_config == 0U) {
		return -ENOTSUP;
	}

	ret = uart_apply_format(dev, cfg_in->baudrate, hw_config);
	if (ret == 0) {
		/* setConfig() clears SCIFFENA while the baud registers are written. */
		uart_buffer_setup(cfg->base);
	}

	return ret;
}

static int g32r5_uart_config_get(const struct device *dev, struct uart_config *cfg_out)
{
	const struct g32r5_uart_config *cfg = dev->config;
	struct g32r5_uart_data *data = dev->data;
	uint16_t ccr = HWREGH(cfg->base + UART_O_CCR);
	uint16_t wlen = ccr & UART_CONFIG_WLEN_MASK;

	cfg_out->baudrate = data->baud_rate;
	cfg_out->flow_ctrl = UART_CFG_FLOW_CTRL_NONE;
	cfg_out->stop_bits = ((ccr & UART_CONFIG_STOP_MASK) == UART_CONFIG_STOP_TWO) ?
				     UART_CFG_STOP_BITS_2 :
				     UART_CFG_STOP_BITS_1;

	switch (UART_getParityMode(cfg->base)) {
	case UART_CONFIG_PAR_EVEN:
		cfg_out->parity = UART_CFG_PARITY_EVEN;
		break;
	case UART_CONFIG_PAR_ODD:
		cfg_out->parity = UART_CFG_PARITY_ODD;
		break;
	default:
		cfg_out->parity = UART_CFG_PARITY_NONE;
		break;
	}

	switch (wlen) {
	case UART_CONFIG_WLEN_5:
		cfg_out->data_bits = UART_CFG_DATA_BITS_5;
		break;
	case UART_CONFIG_WLEN_6:
		cfg_out->data_bits = UART_CFG_DATA_BITS_6;
		break;
	case UART_CONFIG_WLEN_7:
		cfg_out->data_bits = UART_CFG_DATA_BITS_7;
		break;
	case UART_CONFIG_WLEN_8:
		cfg_out->data_bits = UART_CFG_DATA_BITS_8;
		break;
	default:
		return -ENOTSUP;
	}

	return 0;
}
#endif

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static int g32r5_uart_fifo_fill(const struct device *dev, const uint8_t *tx_data, int len)
{
	const struct g32r5_uart_config *cfg = dev->config;
	int sent = 0;

	while ((sent < len) && (uart_tx_space(cfg->base) != 0U)) {
		UART_writeCharNonBlocking(cfg->base, tx_data[sent]);
		sent++;
	}

	return sent;
}

static int g32r5_uart_fifo_read(const struct device *dev, uint8_t *rx_data, const int size)
{
	const struct g32r5_uart_config *cfg = dev->config;
	int got = 0;

	while ((got < size) && uart_rx_available(cfg->base)) {
		rx_data[got] = UART_readCharNonBlocking(cfg->base);
		got++;
	}

	return got;
}

static void g32r5_uart_irq_tx_enable(const struct device *dev)
{
	const struct g32r5_uart_config *cfg = dev->config;

#if defined(CONFIG_UART_G32R5_FIFO)
	HWREGH(cfg->base + UART_O_FFTX) =
		fftx_keep_level(HWREGH(cfg->base + UART_O_FFTX) | UART_FFTX_TXFFIENA);
#else
	UART_enableInterrupt(cfg->base, G32R5_UART_TX_IRQ);
#endif
}

static void g32r5_uart_irq_tx_disable(const struct device *dev)
{
	const struct g32r5_uart_config *cfg = dev->config;

#if defined(CONFIG_UART_G32R5_FIFO)
	HWREGH(cfg->base + UART_O_FFTX) = fftx_keep_level(
		HWREGH(cfg->base + UART_O_FFTX) & (uint16_t)~UART_FFTX_TXFFIENA);
#else
	UART_disableInterrupt(cfg->base, G32R5_UART_TX_IRQ);
#endif
}

static int g32r5_uart_irq_tx_ready(const struct device *dev)
{
	const struct g32r5_uart_config *cfg = dev->config;

	if (!uart_tx_irq_enabled(cfg->base)) {
		return 0;
	}

	return (int)uart_tx_space(cfg->base);
}

static int g32r5_uart_irq_tx_complete(const struct device *dev)
{
	const struct g32r5_uart_config *cfg = dev->config;

#if defined(CONFIG_UART_G32R5_FIFO)
	/* TXFFST does not include the shift register. */
	if (UART_getTxFIFOStatus(cfg->base) != UART_FIFO_TX0) {
		return 0;
	}

	return ((HWREGH(cfg->base + UART_O_CTL2) & UART_CTL2_TXEMPTY) != 0U) ? 1 : 0;
#else
	return UART_isTransmitterBusy(cfg->base) ? 0 : 1;
#endif
}

static void g32r5_uart_irq_rx_enable(const struct device *dev)
{
	const struct g32r5_uart_config *cfg = dev->config;

#if defined(CONFIG_UART_G32R5_FIFO)
	HWREGH(cfg->base + UART_O_FFRX) =
		ffrx_keep_level(HWREGH(cfg->base + UART_O_FFRX) | UART_FFRX_RXFFIENA);
#else
	UART_enableInterrupt(cfg->base, G32R5_UART_RX_IRQ);
#endif
}

static void g32r5_uart_irq_rx_disable(const struct device *dev)
{
	const struct g32r5_uart_config *cfg = dev->config;

#if defined(CONFIG_UART_G32R5_FIFO)
	HWREGH(cfg->base + UART_O_FFRX) = ffrx_keep_level(
		HWREGH(cfg->base + UART_O_FFRX) & (uint16_t)~UART_FFRX_RXFFIENA);
#else
	UART_disableInterrupt(cfg->base, G32R5_UART_RX_IRQ);
#endif
}

static int g32r5_uart_irq_rx_ready(const struct device *dev)
{
	const struct g32r5_uart_config *cfg = dev->config;

	if (!uart_rx_irq_enabled(cfg->base)) {
		return 0;
	}

	return uart_rx_available(cfg->base) ? 1 : 0;
}

static void g32r5_uart_irq_err_enable(const struct device *dev)
{
	const struct g32r5_uart_config *cfg = dev->config;

	UART_enableInterrupt(cfg->base, UART_INT_RXERR);
}

static void g32r5_uart_irq_err_disable(const struct device *dev)
{
	const struct g32r5_uart_config *cfg = dev->config;

	UART_disableInterrupt(cfg->base, UART_INT_RXERR);
}

static int g32r5_uart_irq_is_pending(const struct device *dev)
{
	return g32r5_uart_irq_rx_ready(dev) || g32r5_uart_irq_tx_ready(dev);
}

static void g32r5_uart_irq_update(const struct device *dev)
{
	ARG_UNUSED(dev);
}

static void g32r5_uart_irq_callback_set(const struct device *dev,
					uart_irq_callback_user_data_t cb, void *user_data)
{
	struct g32r5_uart_data *data = dev->data;

	data->user_cb = cb;
	data->user_data = user_data;
}
#endif

static DEVICE_API(uart, g32r5_uart_driver_api) = {
	.poll_in = g32r5_uart_poll_in,
	.poll_out = g32r5_uart_poll_out,
	.err_check = g32r5_uart_err_check,
#ifdef CONFIG_UART_USE_RUNTIME_CONFIGURE
	.configure = g32r5_uart_configure,
	.config_get = g32r5_uart_config_get,
#endif
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.fifo_fill = g32r5_uart_fifo_fill,
	.fifo_read = g32r5_uart_fifo_read,
	.irq_tx_enable = g32r5_uart_irq_tx_enable,
	.irq_tx_disable = g32r5_uart_irq_tx_disable,
	.irq_tx_ready = g32r5_uart_irq_tx_ready,
	.irq_tx_complete = g32r5_uart_irq_tx_complete,
	.irq_rx_enable = g32r5_uart_irq_rx_enable,
	.irq_rx_disable = g32r5_uart_irq_rx_disable,
	.irq_rx_ready = g32r5_uart_irq_rx_ready,
	.irq_err_enable = g32r5_uart_irq_err_enable,
	.irq_err_disable = g32r5_uart_irq_err_disable,
	.irq_is_pending = g32r5_uart_irq_is_pending,
	.irq_update = g32r5_uart_irq_update,
	.irq_callback_set = g32r5_uart_irq_callback_set,
#endif
};

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
#define G32R5_UART_IRQ_CONFIG(n, name)                                                           \
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(n, name, irq),                                           \
		    DT_INST_IRQ_BY_NAME(n, name, priority), g32r5_uart_isr,                      \
		    DEVICE_DT_INST_GET(n), 0);                                                   \
	irq_enable(DT_INST_IRQ_BY_NAME(n, name, irq));

#define G32R5_UART_IRQ_HANDLER(n)                                                              \
	static void g32r5_uart_config_func_##n(const struct device *dev)                       \
	{                                                                                      \
		G32R5_UART_IRQ_CONFIG(n, rx)                                                   \
		G32R5_UART_IRQ_CONFIG(n, tx)                                                   \
	}
#define G32R5_UART_IRQ_HANDLER_FUNC_INIT(n) .irq_config_func = g32r5_uart_config_func_##n
#else
#define G32R5_UART_IRQ_HANDLER(n)
#define G32R5_UART_IRQ_HANDLER_FUNC_INIT(n)
#endif

#define G32R5_UART_INIT(n)                                                                     \
	PINCTRL_DT_INST_DEFINE(n);                                                             \
	G32R5_UART_IRQ_HANDLER(n)                                                              \
	static struct g32r5_uart_data g32r5_uart_data_##n = {                                  \
		.baud_rate = DT_INST_PROP(n, current_speed),                                   \
	};                                                                                     \
	static const struct g32r5_uart_config g32r5_uart_config_##n = {                        \
		.base = DT_INST_REG_ADDR(n),                                                   \
		.pinctrl = PINCTRL_DT_INST_DEV_CONFIG_GET(n),                                  \
		G32R5_UART_IRQ_HANDLER_FUNC_INIT(n)};                                          \
	DEVICE_DT_INST_DEFINE(n, g32r5_uart_init, NULL, &g32r5_uart_data_##n,                  \
			      &g32r5_uart_config_##n, PRE_KERNEL_1, CONFIG_SERIAL_INIT_PRIORITY, \
			      &g32r5_uart_driver_api);

DT_INST_FOREACH_STATUS_OKAY(G32R5_UART_INIT)
