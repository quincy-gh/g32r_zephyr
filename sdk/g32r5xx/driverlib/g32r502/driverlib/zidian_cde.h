//###########################################################################
//
// FILE:    zidian_cde.h
//
// TITLE:   Zidian for Custom Datapath Extension (CDE).
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
//
// You may not use this file except in compliance with the
// GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
//
// The program is only for reference, which is distributed in the hope
// that it will be useful and instructional for customers to develop
// their software. Unless required by applicable law or agreed to in
// writing, the program is distributed on an "AS IS" BASIS, WITHOUT
// ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
// See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
// and limitations under the License.
// $
//
// Modifications:
// - 2026-06-30:
// 2. Add Doxygen for CDE intrinsics and assembly macros (A5).
//###########################################################################

#ifndef ZIDIAN_CDE_H
#define ZIDIAN_CDE_H

#include <arm_cde.h>

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup zidian_cde_api Zidian CDE
//! \brief Custom Datapath Extension (CDE) builtins and inline-asm helpers.
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! Built-in CDE wrappers (map to \c __arm_cx* / \c __arm_vcx* intrinsics).
//
//*****************************************************************************

//*****************************************************************************
//
//! CX1D: 64-bit divide remainder.
//
//*****************************************************************************
#define __div64re(x)          __arm_cx1d(0x0, 0x0)

//*****************************************************************************
//
//! CX2A: CRC helpers on low/high halfwords.
//
//*****************************************************************************
#define __crc8l(y, x)         __arm_cx2a(0x0, y, x, 0x8)
#define __crc16p1l(y, x)      __arm_cx2a(0x0, y, x, 0x9)
#define __crc16p2l(y, x)      __arm_cx2a(0x0, y, x, 0xa)
#define __crc32l(y, x)        __arm_cx2a(0x0, y, x, 0xb)
#define __crc8h(y, x)         __arm_cx2a(0x0, y, x, 0xc)
#define __crc16p1h(y, x)      __arm_cx2a(0x0, y, x, 0xd)
#define __crc16p2h(y, x)      __arm_cx2a(0x0, y, x, 0xe)
#define __crc32h(y, x)        __arm_cx2a(0x0, y, x, 0xf)

//*****************************************************************************
//
//! CX3DA: 64-bit divide variants (unsigned, mixed, signed).
//
//*****************************************************************************
#define __div64uu(y, x1, x2)  __arm_cx3da(0x0, y, x1, x2, 0x0)
#define __div64iu(y, x1, x2)  __arm_cx3da(0x0, y, x1, x2, 0x1)
#define __div64ii(y, x1, x2)  __arm_cx3da(0x0, y, x1, x2, 0x2)

//*****************************************************************************
//
//! VCX2: Per-unit and scalar float ops (sin/cos/atan, 2pi scale, sqrt).
//
//*****************************************************************************
#define __sinpu(x)            __arm_vcx2(0x0, x, 0x0)
#define __cospu(x)            __arm_vcx2(0x0, x, 0x1)
#define __atanpu(x)           __arm_vcx2(0x0, x, 0x2)
#define __mul2pi(x)           __arm_vcx2(0x0, x, 0x3)
#define __div2pi(x)           __arm_vcx2(0x0, x, 0x4)
#define __sqrt(x)             __arm_vcx2(0x0, x, 0x5)
#define __rd_scr(x)           __arm_vcx2(0x0, x, 0x6)
#define __wr_scr(x)           __arm_vcx2(0x0, x, 0x7)

//*****************************************************************************
//
//! VCX3: Float divide, quadrant, and atan2 ratio helpers.
//
//*****************************************************************************
#define __div(x1, x2)         __arm_vcx3(0x0, x1, x2, 0x0)
#define __quad(x1, x2)        __arm_vcx3(0x0, x1, x2, 0x1)
#define __div_atan2(x1, x2)   __arm_vcx3(0x0, x1, x2, 0x2)

//*****************************************************************************
//
//! Inline assembly opcode strings for Zidian math intrinsics.
//
//*****************************************************************************
// CX1D
#define _CX1D(Rd) \
        "cx1d p0, "#Rd", "#Rd"+1, #0x0 \n"

// CX2
#define _CX2(Rd, Rn, imm) \
        "cx2 p0, "#Rd", "#Rn", #"#imm" \n"

// CX2A
#define _CX2A(Rd, Rn, imm) \
        "cx2a p0, "#Rd", "#Rn", #"#imm" \n"

// CX2DA
#define _CX2DA(Rd, Rdp1, Rn, imm) \
        "cx2da p0, "#Rd", "#Rdp1", "#Rn", #"#imm" \n"

// CX3
#define _CX3(Rd, Rn, Rm, imm) \
        "cx3 p0, "#Rd", "#Rn", "#Rm", #"#imm" \n"

// CX3D
#define _CX3D(Rd, Rdp1, Rn, Rm, imm) \
        "cx3d p0, "#Rd", "#Rdp1", "#Rn", "#Rm", #"#imm" \n"

// CX3DA
#define _CX3DA(Rd, Rdp1, Rn, Rm, imm) \
        "cx3da p0, "#Rd", "#Rdp1", "#Rn", "#Rm", #"#imm" \n"

// VCX2
#define _VCX2(Sd, Sn, imm) \
        "vcx2 p0, "#Sd", "#Sn", #"#imm" \n"

// VCX3
#define _VCX3(Sd, Sn, Sm, imm) \
        "vcx3 p0, "#Sd", "#Sn", "#Sm", #"#imm" \n"

// LW
#define _LW(Rd, Rs, imm) \
        "ldr "#Rd", ["#Rs", #"#imm"] \n"
#define _LW_PRE(Rd, Rs, imm) \
        "ldr "#Rd", ["#Rs", #"#imm"]! \n"
#define _LW_POST(Rd, Rs, imm) \
        "ldr "#Rd", ["#Rs"], #"#imm" \n"

// SW
#define _SW(Rd, Rs, imm) \
        "str "#Rd", ["#Rs", #"#imm"] \n"
#define _SW_PRE(Rd, Rs, imm) \
        "str "#Rd", ["#Rs", #"#imm"]! \n"
#define _SW_POST(Rd, Rs, imm) \
        "str "#Rd", ["#Rs"], #"#imm" \n"

// MV
#define _MV(Rd, Rm) \
        "mov "#Rd", "#Rm" \n"

// AND
#define _AND(Rd, Rn, Rm) \
        "and "#Rd", "#Rn", "Rm" \n"

// OR
#define _OR(Rd, Rn, Rm) \
        "orr "#Rd", "#Rn", "#Rm" \n"

// CMPY
#define _CMPYS(Rd, Rn, Rm) \
        "smusd "#Rd", "#Rn", "#Rm" \n"
#define _CMPYA(Rd, Rn, Rm) \
        "smuad "#Rd", "#Rn", "#Rm" \n"
#define _CMPYSX(Rd, Rn, Rm) \
        "smusdx "#Rd", "#Rn", "#Rm" \n"
#define _CMPYAX(Rd, Rn, Rm) \
        "smuadx "#Rd", "#Rn", "#Rm" \n"

// ADDF32
#define _ADDF32(Sd, Sn, Sm) \
        "vadd.f32 "#Sd", "#Sn", "#Sm" \n"

// SINPUF32
#define SINPUF32(Sd, Sn)   _VCX2(Sd, Sn, 0x0)

// COSPUF32
#define COSPUF32(Sd, Sn)   _VCX2(Sd, Sn, 0x1)

// ATANPUF32
#define ATANPUF32(Sd, Sn)   _VCX2(Sd, Sn, 0x2)

// MPY2PIF32
#define MPY2PIF32(Sd, Sn)   _VCX2(Sd, Sn, 0x3)

// DIV2PIF32
#define DIV2PIF32(Sd, Sn)   _VCX2(Sd, Sn, 0x4)

// SQRTF32
#define SQRTF32(Sd, Sn)   _VCX2(Sd, Sn, 0x5)

// DIVF32
#define DIVF32(Sd, Sn, Sm)   _VCX3(Sd, Sn, Sm, 0x0)

// QUADF32
#define QUADF32(Sd, Sn, Sm)   _VCX3(Sd, Sn, Sm, 0x1)

// DIVF32_ATAN2
#define DIVF32_ATAN2(Sd, Sn, Sm)   _VCX3(Sd, Sn, Sm, 0x2)

//! @}
//
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // ZIDIAN_CDE_H
