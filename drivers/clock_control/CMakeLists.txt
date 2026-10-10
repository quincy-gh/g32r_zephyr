# Copyright (c) 2025, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_SOC_FAMILY_G32R5)
  target_sources(drivers__clock_control PRIVATE clock_control_g32r5.c)
endif()
