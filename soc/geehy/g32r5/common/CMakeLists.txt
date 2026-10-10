# Copyright (c) 2025, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(.)

# armlink emits the ITCM memory region as a load region at 0x0, so
# itcm.ramfunc is not stored in flash and arch_data_copy() is a no-op.
# Append a rewrite of the generated scatter files once they exist.
# GNU ld is unaffected: itcm_rv.ld already gives .itcm a flash LMA.
if(CONFIG_ARMCLANG_STD_LIBC)
  # ${} inside DEFER is expanded when the call runs, in Zephyr's directory.
  # Expand the paths now so include() receives a literal file name.
  cmake_language(EVAL CODE "
    cmake_language(DEFER DIRECTORY [[${ZEPHYR_BASE}]]
      CALL include [[${CMAKE_CURRENT_LIST_DIR}/nest_itcm_register.cmake]])
  ")
endif()
