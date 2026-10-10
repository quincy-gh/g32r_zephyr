# Copyright (c) 2025, Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0

/*
 * Inject the G32R5 SDK's ITCM sections into Zephyr's `.itcm` output section.
 *
 * This file is pulled in by zephyr_linker_sources(ITCM_SECTION ...) and is
 * #included inside the .itcm section body. The .itcm section links as
 * VMA=ITCM, LMA=ROMABLE_REGION (FLASH); Zephyr's arch_data_copy() in
 * z_prep_c() copies it into ITCM before C init, matching the official
 * SDK's copy.table behaviour.
 */

KEEP(*(itcm.ramfunc))
KEEP(*(itcm.instruction))
