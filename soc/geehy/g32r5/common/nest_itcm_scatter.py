# Copyright (c) 2026 Quincy.W <wangqyfm@foxmail.com>
# SPDX-License-Identifier: Apache-2.0
"""Move the ITCM scatter load region inside the FLASH load region.

Zephyr's armlink generator emits every memory region as its own load
region. ITCM is RAM at 0x0, so that places itcm.ramfunc (SysCtl_delay)
at execution address 0 with the same load address. The bytes never land
in flash, arch_data_copy() copies 0 to 0, and the first clock-init call
executes empty ITCM.

Nesting the execution region in the FLASH load region gives it a flash
load address and an execution address of 0. __itcm_load_start /
__itcm_start / __itcm_size already point at Image$$ITCM$$*, so
arch_data_copy() then does the copy. Running the script twice is a no-op.
"""

import re
import sys


def _matching_brace(text, open_index):
    depth = 0
    for index in range(open_index, len(text)):
        char = text[index]
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0:
                return index
    raise SystemExit("nest_itcm_scatter: unbalanced braces")


def nest(text):
    load = re.search(
        r"(?m)^ITCM[ \t]+0x[0-9A-Fa-f]+[ \t]+NOCOMPRESS[ \t]+0x[0-9A-Fa-f]+[ \t]*\r?\n\{",
        text,
    )
    if load is None:
        return text

    open_index = text.find("{", load.start())
    close_index = _matching_brace(text, open_index)
    execution = text[open_index + 1:close_index].strip("\r\n")
    if "ITCM" not in execution:
        raise SystemExit("nest_itcm_scatter: ITCM load region has no execution region")

    text = text[:load.start()] + text[close_index + 1:]
    text = text.lstrip("\r\n")

    flash = re.search(
        r"(?m)^FLASH[ \t]+0x[0-9A-Fa-f]+[ \t]+NOCOMPRESS[ \t]+0x[0-9A-Fa-f]+[ \t]*\r?\n\{",
        text,
    )
    if flash is None:
        raise SystemExit("nest_itcm_scatter: FLASH load region not found")

    # Keep the original first execution region as the root region. Inserting
    # ITCM at the front shifts every later load address and armlink then
    # refuses to place __scatterload in a non-root region.
    flash_open = text.find("{", flash.start())
    flash_close = _matching_brace(text, flash_open)
    return (
        text[:flash_close]
        + "\n"
        + execution
        + "\n"
        + text[flash_close:]
    )


def main(argv):
    if len(argv) != 2:
        raise SystemExit("usage: nest_itcm_scatter.py <scatter-file>")
    path = argv[1]
    with open(path, "r", encoding="utf-8", newline="") as handle:
        original = handle.read()
    updated = nest(original)
    if updated != original:
        with open(path, "w", encoding="utf-8", newline="") as handle:
            handle.write(updated)


if __name__ == "__main__":
    main(sys.argv)
