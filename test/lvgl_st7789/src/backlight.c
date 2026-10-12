/*
 * Copyright (c) 2026, Quincy.W <wangqyfm@foxmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * ATK-MD0240 LCD_PWR has a pulldown. The panel stays dark until this
 * pin is driven high. The ST7789 driver has no backlight GPIO.
 */

#include <zephyr/device.h>
#include <zephyr/drivers/led.h>
#include <zephyr/kernel.h>

static int lcd_backlight_on(void)
{
	const struct device *backlight = DEVICE_DT_GET(DT_NODELABEL(lcd_pwr));
	int ret;

	if (!device_is_ready(backlight)) {
		printk("lcd backlight device is not ready\n");
		return -ENODEV;
	}

	ret = led_on(backlight, 0);
	if (ret < 0) {
		printk("lcd backlight on failed: %d\n", ret);
	}

	return ret;
}

SYS_INIT(lcd_backlight_on, APPLICATION, 0);
