# Copyright (c) 2025, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(${ZEPHYR_BASE}/drivers)

zephyr_sources(
  soc.c
  )

if(CONFIG_ARMCLANG_STD_LIBC)
    set(LINKER_SCRIPT ${BOARD_DIR}/armclang_scatter.sct)
    set_property(GLOBAL PROPERTY LINKER_SCRIPT_USE_SCATTER TRUE)
    set(CMAKE_EXE_LINKER_FLAGS_INIT "--scatter=CMakeScatter.scatter")
    set(CMAKE_MODULE_LINKER_FLAGS_INIT "--scatter=CMakeScatter.scatter")
    set(CMAKE_SHARED_LINKER_FLAGS_INIT "--scatter=CMakeScatter.scatter")
    set(CMAKE_EXE_LINKER_FLAGS_INIT "-fuse-ld=lld -Wl,--gc-sections")
endif()

zephyr_include_directories(.)

zephyr_linker_sources(ITCM_SECTION itcm_rv.ld)

set(SOC_LINKER_SCRIPT ${ZEPHYR_BASE}/include/zephyr/arch/arm/cortex_m/scripts/linker.ld CACHE INTERNAL "")
