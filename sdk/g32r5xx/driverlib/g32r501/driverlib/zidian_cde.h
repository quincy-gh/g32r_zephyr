//###########################################################################
//
// FILE:    zidian_cde.h
//
// TITLE:   Zidian for Custom Datapath Extension (CDE).
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
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
// Built-in Functions (call functions in c file)
//
//*****************************************************************************
// CX2
#define __tas(x)       __arm_cx2(0x0, x, 0x1)
#define __rstatus(x)   __arm_cx2(0x0, x, 0x2)
#define __wstatus(x)   __arm_cx2(0x0, x, 0x3)
#define __neg(x)       __arm_cx2(0x0, x, 0x4)

// CX2A
#define __crc8l(y, x)      __arm_cx2a(0x0, y, x, 0x8)
#define __crc16p1l(y, x)   __arm_cx2a(0x0, y, x, 0x9)
#define __crc16p2l(y, x)   __arm_cx2a(0x0, y, x, 0xa)
#define __crc32l(y, x)     __arm_cx2a(0x0, y, x, 0xb)
#define __crc8h(y, x)      __arm_cx2a(0x0, y, x, 0xc)
#define __crc16p1h(y, x)   __arm_cx2a(0x0, y, x, 0xd)
#define __crc16p2h(y, x)   __arm_cx2a(0x0, y, x, 0xe)
#define __crc32h(y, x)     __arm_cx2a(0x0, y, x, 0xf)

// CX2DA
#define __tast(y, x)   __arm_cx2da(0x0, y, x, 0x40)

// CX3
#define __sh1add(x1, x2)       __arm_cx3(0x0, x1, x2, 0x8)
#define __sh1addi(x1, x2)      __arm_cx3(0x0, x1, x2, 0x18)
#define __sh1addexh(x1, x2)    __arm_cx3(0x0, x1, x2, 0xa)
#define __sh1addexhi(x1, x2)   __arm_cx3(0x0, x1, x2, 0x1a)
#define __sh1addexl(x1, x2)    __arm_cx3(0x0, x1, x2, 0xb)
#define __sh1addexli(x1, x2)   __arm_cx3(0x0, x1, x2, 0x1b)
#define __sh1sub(x1, x2)       __arm_cx3(0x0, x1, x2, 0xc)
#define __sh1subi(x1, x2)      __arm_cx3(0x0, x1, x2, 0x1c)
#define __sh1subexh(x1, x2)    __arm_cx3(0x0, x1, x2, 0xe)
#define __sh1subexhi(x1, x2)   __arm_cx3(0x0, x1, x2, 0x1e)
#define __sh1subexl(x1, x2)    __arm_cx3(0x0, x1, x2, 0xf)
#define __sh1subexli(x1, x2)   __arm_cx3(0x0, x1, x2, 0x1f)

// CX3D
#define __hstas(x1, x2)   __arm_cx3d(0x0, x1, x2, 0x20)
#define __hstsa(x1, x2)   __arm_cx3d(0x0, x1, x2, 0x21)
#define __lstas(x1, x2)   __arm_cx3d(0x0, x1, x2, 0x22)
#define __lstsa(x1, x2)   __arm_cx3d(0x0, x1, x2, 0x23)
#define __max(x1, x2)     __arm_cx3d(0x0, x1, x2, 0x25)

// CX3DA
#define __hbitsel(y, x1, x2)   __arm_cx3da(0, y, x1, x2, 0x2)

// VCX2
#define __rd_scr(x)    __arm_vcx2_u32(0x0, x, 0x6)
#define __wr_scr(x)    __arm_vcx2_u32(0x0, x, 0x7)

//*****************************************************************************
//
// Assembly (write in inline assembly funcitions)
//
//*****************************************************************************
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

// VNEG
#define VNEG(VRa)   _CX2(VRa, VRa, 0x4)

// RSTATUS
#define RSTATUS(Rd)   _CX2(Rd, Rd, 0x2)

// WSTATUS
#define WSTATUS(Rd)   _CX2(Rd, Rd, 0x3)

// VITBM2
#define VITBM2(VR0)   _CX2(VR0, VR0, 0x1)

// VITBM3
#define VITBM3(VR0, VR1, VR2) \
        _CX2DA(VR0, VR1, VR2, 0x40)

// VITDHADDSUB
#define VITDHADDSUB(VR4, VR3, VR2, VRa) \
        _CX3D(VR4, VR3, VR2, VRa, 0x20)

// VITDHSUBADD
#define VITDHSUBADD(VR4, VR3, VR2, VRa) \
        _CX3D(VR4, VR3, VR2, VRa, 0x21)

// VITDLADDSUB
#define VITDLADDSUB(VR4, VR3, VR2, VRa) \
        _CX3D(VR4, VR3, VR2, VRa, 0x22)

// VITDLSUBADD
#define VITDLSUBADD(VR4, VR3, VR2, VRa) \
        _CX3D(VR4, VR3, VR2, VRa, 0X23)

// VITLSEL
#define VITLSEL(VRa, VRb, VR4, VR3, VT1s, VT0s, VT1, VT0) \
        _CX3D(VT1s, VRa, VR4, VT1, 0x25) \
        _CX3D(VT0s, VRb, VR3, VT0, 0x25)

// VTRACE
#define VTRACE(VR1, VR0, VT0, VT1) \
        _CX3DA(VR0, VR1, VT0, VT1, 0x2)

// VCADD
#define VCADD(VR5, VR4, VR3, VR2) \
        _CX3(VR5, VR5, VR3, 0x8) \
        _CX3(VR4, VR4, VR2, 0x18)

// VCSUB
#define VCSUB(VR5, VR4, VR3, VR2) \
        _CX3(VR5, VR5, VR3, 0xc) \
        _CX3(VR4, VR4, VR2, 0x1c) \

// VCDADD16
#define VCDADD16(VRaL, VR5, VR4, VR3, VR2) \
        _CX3(VR5, VR4, VR3, 0xa) \
        _CX3(VRaL, VR4, VR2, 0x1b) \
        _OR(VR5, VRaL, VR5)

// VCDSUB16
#define VCDSUB16(VRaL, VR6, VR4, VR3, VR2) \
        _CX3(VR6, VR4, VR3, 0xe) \
        _CX3(VRaL, VR4, VR2, 0x1f) \
        _OR(VR6, VRaL, VR6)

// VCMPY
#define VCMPY(VR3, VR2, VR1, VR0) \
        _CMPYS(VR3, VR0, VR1) \
        _CMPYAX(VR2, VR0, VR1) \
        VNEG(VR3)

// VCMAC
#define VCMAC(VR5, VR4, VR3, VR2, VR1, VR0) \
        VCADD(VR5, VR4, VR3, VR2) \
        VCMPY(VR3, VR2, VR1, VR0)

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

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // ZIDIAN_CDE_H
