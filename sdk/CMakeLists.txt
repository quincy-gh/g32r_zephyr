# sdk/CMakeLists.txt
# Copyright (c) 2025, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

zephyr_library()

# G32R5xx SDK V1.1.1 layout: driverlib under g32r5xx/. Device header and
# system_*.h sit together under device_support/<soc>/common/device/Geehy.
# core_cm52.h comes from Zephyr cmsis_6; do not add the vendor CMSIS tree.
# The TI-style bitfield headers are not used.
# G32R502 is single-core and its header does not check __CORE_CPUx__.
# G32R501 headers require exactly one of __CORE_CPU0__ / __CORE_CPU1__.
# Dual-core images select it from the board qualifier (.../cpu0 or .../cpu1).
# Single-core 501 has no cluster, so it stays CPU0.
if(CONFIG_SOC_SERIES_G32R502)
  set(G32R5_DEV g32r502)
  zephyr_compile_definitions(
      -D__ARM_ARCH_8_1M_MAIN___
      -D__ARM_TARGET_COPROC
      -D__G32R502__
      -D__G32R502XX__
  )
elseif("${BOARD_QUALIFIERS}" MATCHES "(^|/)cpu1$")
  set(G32R5_DEV g32r501)
  zephyr_compile_definitions(
      -D__ARM_ARCH_8_1M_MAIN___
      -D__ARM_TARGET_COPROC
      -D__G32R501__
      -D__G32R501XX__
      -D__CORE_CPU1__
  )
else()
  set(G32R5_DEV g32r501)
  zephyr_compile_definitions(
      -D__ARM_ARCH_8_1M_MAIN___
      -D__ARM_TARGET_COPROC
      -D__G32R501__
      -D__G32R501XX__
      -D__CORE_CPU0__
  )
endif()

zephyr_include_directories(g32r5xx/device_support/${G32R5_DEV}/common/device/Geehy)
zephyr_include_directories(g32r5xx/driverlib/${G32R5_DEV}/driverlib)

file(GLOB_RECURSE HAL_SOURCES
    g32r5xx/driverlib/${G32R5_DEV}/driverlib/*.c
)

# Remove some files
set(BLACKLIST_HAL_SOURCES
 "${CMAKE_CURRENT_SOURCE_DIR}/g32r5xx/driverlib/${G32R5_DEV}/driverlib/interrupt.c"
)

list(REMOVE_ITEM HAL_SOURCES ${BLACKLIST_HAL_SOURCES})

zephyr_library_sources(${HAL_SOURCES})
