# Copyright (c) 2026, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(${ZEPHYR_BASE}/drivers)

zephyr_sources(
  soc.c
  )

zephyr_include_directories(.)

zephyr_linker_sources(ITCM_SECTION itcm_rv.ld)

set(SOC_LINKER_SCRIPT ${ZEPHYR_BASE}/include/zephyr/arch/arm/cortex_m/scripts/linker.ld CACHE INTERNAL "")
