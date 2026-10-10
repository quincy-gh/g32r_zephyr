# G32R5
# Copyright (c) 2025, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

add_subdirectory_ifdef(CONFIG_SOC_FAMILY_G32R5 sdk)
add_subdirectory_ifdef(CONFIG_SOC_FAMILY_G32R5 drivers)
zephyr_include_directories_ifdef(CONFIG_SOC_FAMILY_G32R5 include)