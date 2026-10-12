# Copyright (c) 2026, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(g32r5_lvgl_st7789)

# Upstream LVGL sample. Backlight and the panel display device are local:
# the stock ST7789 driver does not release chip-select after each command.
target_sources(app PRIVATE
	${ZEPHYR_BASE}/samples/subsys/display/lvgl/src/main.c
	src/backlight.c
	src/display_panel.c
)
