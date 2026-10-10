# Copyright (c) 2026 Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0
#
# Included at the end of Zephyr's CMakeLists, after the scatter files have
# been registered. APPEND must use the same relative OUTPUT name.

set(_g32r5_nest_script ${CMAKE_CURRENT_LIST_DIR}/nest_itcm_scatter.py)

foreach(_scatter linker_zephyr_pre0.cmd linker.cmd)
  add_custom_command(
    OUTPUT ${_scatter}
    APPEND
    COMMAND ${PYTHON_EXECUTABLE} ${_g32r5_nest_script}
            ${CMAKE_CURRENT_BINARY_DIR}/${_scatter}
    DEPENDS ${_g32r5_nest_script}
  )
endforeach()
