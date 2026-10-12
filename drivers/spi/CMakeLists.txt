# Copyright (c) 2026, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_SPI_G32R5)
  target_sources(drivers__spi PRIVATE spi_g32r5.c)
endif()
