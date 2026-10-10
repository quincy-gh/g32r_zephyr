# Copyright (c) 2026, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

board_runner_args(pyocd "--target=g32r502" "--frequency=10000000")

include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
