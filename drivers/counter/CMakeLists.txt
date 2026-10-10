# Copyright (c) 2026, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_COUNTER_G32R5_TMR)
  target_sources(drivers__counter PRIVATE counter_g32r5_tmr.c)
endif()
