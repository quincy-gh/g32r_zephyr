# Copyright (c) 2025, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

board_runner_args(pyocd "--target=g32r501dxx" "--frequency=10000000")

include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
