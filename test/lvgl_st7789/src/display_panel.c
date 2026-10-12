/*
 * Copyright (c) 2026, Quincy.W <wangqyfm@foxmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * ST7789 display device for the LVGL sample. The Zephyr MIPI DBI helper
 * either drops chip-select between the command byte and its payload, or
 * leaves it low for the whole session. This glass latches a command only
 * when chip-select stays low for that command plus its data and then rises.
 * Mode 3, INVON (0x21): 0xF800 is pure red, 0x07E0 pure green, 0x001F pure blue.
 */

#include <stdint.h>
#include <string.h>

#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/kernel.h>
#include <lvgl.h>

#define PANEL_NODE DT_NODELABEL(atk_md0240)
#define PANEL_W    DT_PROP(PANEL_NODE, width)
#define PANEL_H    DT_PROP(PANEL_NODE, height)

static const struct device *const spi = DEVICE_DT_GET(DT_NODELABEL(spia));
static const struct gpio_dt_spec dc = GPIO_DT_SPEC_GET(DT_NODELABEL(mipi_dbi_atk), dc_gpios);
static const struct gpio_dt_spec reset = GPIO_DT_SPEC_GET(DT_NODELABEL(mipi_dbi_atk), reset_gpios);
static const struct gpio_dt_spec cs_gpio = GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(spia), cs_gpios, 0);

static struct spi_config spi_cfg = {
	.frequency = DT_PROP(PANEL_NODE, mipi_max_frequency),
	.operation = SPI_OP_MODE_CONTROLLER | SPI_WORD_SET(8) | SPI_HOLD_ON_CS | SPI_MODE_CPOL |
		     SPI_MODE_CPHA,
	.cs = {
		.gpio = GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(spia), cs_gpios, 0),
		.delay = 10,
		.cs_is_gpio = true,
	},
};

static K_MUTEX_DEFINE(panel_lock);

static int panel_bytes(bool is_data, const uint8_t *buf, size_t len)
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

	return spi_write(spi, &spi_cfg, &txs);
}

static int panel_cmd(uint8_t cmd, const uint8_t *data, size_t len)
{
	int ret;

	ret = panel_bytes(false, &cmd, 1);
	if ((ret == 0) && (data != NULL) && (len > 0U)) {
		ret = panel_bytes(true, data, len);
	}

	spi_release(spi, &spi_cfg);
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

static int panel_hw_init(void)
{
	static const uint8_t colmod = 0x55;
	uint8_t madctl = DT_PROP(PANEL_NODE, mdac);
	int ret;

	ret = panel_reset();
	if (ret < 0) {
		return ret;
	}

	ret = panel_cmd(0x01, NULL, 0);
	if (ret < 0) {
		return ret;
	}
	k_msleep(120);

	ret = panel_cmd(0x11, NULL, 0);
	if (ret < 0) {
		return ret;
	}
	k_msleep(120);

	ret = panel_cmd(0x36, &madctl, 1);
	ret |= panel_cmd(0x3A, &colmod, 1);
	ret |= panel_cmd(0x21, NULL, 0);
	ret |= panel_cmd(0x13, NULL, 0);
	ret |= panel_cmd(0x29, NULL, 0);
	return ret;
}

static int panel_window(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	uint8_t arg[4];
	uint16_t x1 = x + w - 1U;
	uint16_t y1 = y + h - 1U;
	int ret;

	arg[0] = (uint8_t)(x >> 8);
	arg[1] = (uint8_t)x;
	arg[2] = (uint8_t)(x1 >> 8);
	arg[3] = (uint8_t)x1;
	ret = panel_cmd(0x2A, arg, 4);
	arg[0] = (uint8_t)(y >> 8);
	arg[1] = (uint8_t)y;
	arg[2] = (uint8_t)(y1 >> 8);
	arg[3] = (uint8_t)y1;
	ret |= panel_cmd(0x2B, arg, 4);
	return ret;
}

static int panel_blanking_on(const struct device *dev)
{
	int ret;

	ARG_UNUSED(dev);
	k_mutex_lock(&panel_lock, K_FOREVER);
	ret = panel_cmd(0x28, NULL, 0);
	k_mutex_unlock(&panel_lock);
	return ret;
}

static int panel_blanking_off(const struct device *dev)
{
	int ret;

	ARG_UNUSED(dev);
	k_mutex_lock(&panel_lock, K_FOREVER);
	ret = panel_cmd(0x29, NULL, 0);
	k_mutex_unlock(&panel_lock);
	return ret;
}

static int panel_write(const struct device *dev, const uint16_t x, const uint16_t y,
		       const struct display_buffer_descriptor *desc, const void *buf)
{
	const uint8_t *src = buf;
	uint16_t pitch = desc->pitch != 0U ? desc->pitch : desc->width;
	uint16_t row;
	uint8_t cmd = 0x2C;
	int ret;
	static bool first = true;

	ARG_UNUSED(dev);

	if ((desc->width == 0U) || (desc->height == 0U) || (buf == NULL)) {
		return -EINVAL;
	}

	if (first) {
		first = false;
		printk("panel: first write %ux%u at %u,%u\n", desc->width, desc->height, x, y);
	}

	k_mutex_lock(&panel_lock, K_FOREVER);
	ret = panel_window(x, y, desc->width, desc->height);
	if (ret == 0) {
		ret = panel_bytes(false, &cmd, 1);
	}
	for (row = 0U; (ret == 0) && (row < desc->height); row++) {
		ret = panel_bytes(true, src, (size_t)desc->width * 2U);
		src += (size_t)pitch * 2U;
	}
	spi_release(spi, &spi_cfg);
	k_mutex_unlock(&panel_lock);
	return ret;
}

static void panel_capabilities(const struct device *dev, struct display_capabilities *caps)
{
	ARG_UNUSED(dev);
	memset(caps, 0, sizeof(*caps));
	caps->x_resolution = PANEL_W;
	caps->y_resolution = PANEL_H;
	caps->supported_pixel_formats = PIXEL_FORMAT_RGB_565X;
	caps->current_pixel_format = PIXEL_FORMAT_RGB_565X;
	caps->current_orientation = DISPLAY_ORIENTATION_NORMAL;
}

static int panel_set_pixel_format(const struct device *dev, const enum display_pixel_format format)
{
	ARG_UNUSED(dev);
	return (format == PIXEL_FORMAT_RGB_565X) ? 0 : -ENOTSUP;
}

static int panel_init(const struct device *dev)
{
	int ret;

	ARG_UNUSED(dev);

	if (!device_is_ready(spi) || !gpio_is_ready_dt(&dc) || !gpio_is_ready_dt(&reset) ||
	    !gpio_is_ready_dt(&cs_gpio)) {
		printk("panel: spi or gpio not ready\n");
		return -ENODEV;
	}

	ret = gpio_pin_configure_dt(&dc, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		printk("panel: dc config %d\n", ret);
		return ret;
	}

	ret = panel_hw_init();
	printk("panel: init %d\n", ret);
	return ret;
}

static DEVICE_API(display, panel_api) = {
	.blanking_on = panel_blanking_on,
	.blanking_off = panel_blanking_off,
	.write = panel_write,
	.get_capabilities = panel_capabilities,
	.set_pixel_format = panel_set_pixel_format,
};

DEVICE_DT_DEFINE(PANEL_NODE, panel_init, NULL, NULL, NULL, POST_KERNEL, CONFIG_DISPLAY_INIT_PRIORITY,
		 &panel_api);

static int panel_marker(void)
{
	const struct device *disp = DEVICE_DT_GET(PANEL_NODE);
	static uint8_t line[PANEL_W * 2U];
	struct display_buffer_descriptor desc = {
		.buf_size = sizeof(line),
		.width = PANEL_W,
		.height = 1,
		.pitch = PANEL_W,
	};
	uint16_t y;
	int ret = 0;
	size_t i;

	lv_mem_monitor_t mon;

	lv_mem_monitor(&mon);
	printk("panel: lv total %u free %u biggest %u\n", (unsigned int)mon.total_size,
	       (unsigned int)mon.free_size, (unsigned int)mon.free_biggest_size);

	for (i = 0U; i < sizeof(line); i += 2U) {
		line[i] = 0x07;
		line[i + 1U] = 0xE0;
	}

	for (y = 0U; (ret == 0) && (y < 40U); y++) {
		ret = display_write(disp, 0, y, &desc, line);
	}

	printk("panel: green band %d\n", ret);
	return 0;
}

SYS_INIT(panel_marker, APPLICATION, 99);
