//###########################################################################
//
// FILE:    zidian_math.h
//
// TITLE:   Zidian for Math.
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
// 2. Add Doxygen for Zidian math intrinsics (A5).
//###########################################################################

#ifndef ZIDIAN_MATH_H
#define ZIDIAN_MATH_H

#include <math.h>
#include <stdint.h>
#include "cmsis_compiler.h"
#include "zidian_cde.h"

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
//! \addtogroup zidian_math_api Zidian Math
//! \brief Zidian VCX/CX inline math intrinsics for Cortex-M52.
//! @{
//
//*****************************************************************************


//*****************************************************************************
//
//! Zidian VCX/CX inline math intrinsics.
//
//*****************************************************************************
//*****************************************************************************
//
//! \brief Computes sin(pi*x) in per-unit form.
//!
//! \param src is the per-unit input.
//!
//! \return Returns sin(src * pi).
//
//*****************************************************************************
__STATIC_FORCEINLINE float __sinpuf32(float src)
{
    float result_f32;

    __ASM volatile (
        SINPUF32(%[output], %[input])
        :[output] "=t" (result_f32)
        :[input] "t" (src)
    );

    return result_f32;
}

//*****************************************************************************
//
//! \brief Computes sin(x) in radians.
//!
//! \param src is the angle in radians.
//!
//! \return Returns sin(src).
//
//*****************************************************************************
__STATIC_FORCEINLINE float __sin(float src)
{
    float result_div2pi;
    float result_f32;

    __ASM volatile (
        DIV2PIF32(%[output], %[input])
        :[output] "=t" (result_div2pi)
        :[input] "t" (src)
    );
    __ASM volatile (
        SINPUF32(%[output], %[input])
        :[output] "=t" (result_f32)
        :[input] "t" (result_div2pi)
    );

    return result_f32;
}

//*****************************************************************************
//
//! \brief Computes cos(pi*x) in per-unit form.
//!
//! \param src is the per-unit input.
//!
//! \return Returns cos(src * pi).
//
//*****************************************************************************
__STATIC_FORCEINLINE float __cospuf32(float src)
{
    float result_f32;

    __ASM volatile (
        COSPUF32(%[output], %[input])
        :[output] "=t" (result_f32)
        :[input] "t" (src)
    );

    return result_f32;
}

//*****************************************************************************
//
//! \brief Computes cos(x) in radians.
//!
//! \param src is the angle in radians.
//!
//! \return Returns cos(src).
//
//*****************************************************************************
__STATIC_FORCEINLINE float __cos(float src)
{
    float result_div2pi;
    float result_f32;

    __ASM volatile (
        DIV2PIF32(%[output], %[input])
        :[output] "=t" (result_div2pi)
        :[input] "t" (src)
    );
    __ASM volatile (
        COSPUF32(%[output], %[input])
        :[output] "=t" (result_f32)
        :[input] "t" (result_div2pi)
    );

    return result_f32;
}

//*****************************************************************************
//
//! \brief Computes atan(x)/pi in per-unit form.
//!
//! \param src is the input value.
//!
//! \return Returns atan(src)/pi.
//
//*****************************************************************************
__STATIC_FORCEINLINE float __atanpuf32(float src)
{
    float result_f32;

    __ASM volatile (
        ATANPUF32(%[output], %[input])
        :[output] "=t" (result_f32)
        :[input] "t" (src)
    );

    return result_f32;
}

//*****************************************************************************
//
//! \brief Computes atan(x) in radians.
//!
//! \param src is the input value.
//!
//! \return Returns atan(src).
//
//*****************************************************************************
__STATIC_FORCEINLINE float __atan(float src)
{
    float result_atanpu;
    float result_f32;

    __ASM volatile (
        ATANPUF32(%[output], %[input])
        :[output] "=t" (result_atanpu)
        :[input] "t" (src)
    );
    __ASM volatile (
        MPY2PIF32(%[output], %[input])
        :[output] "=t" (result_f32)
        :[input] "t" (result_atanpu)
    );

    return result_f32;
}

//*****************************************************************************
//
//! \brief Multiplies the input by 2*pi.
//!
//! \param src is the input value.
//!
//! \return Returns src * 2*pi.
//
//*****************************************************************************
__STATIC_FORCEINLINE float __mpy2pif32(float src)
{
    float result_f32;

    __ASM volatile (
        MPY2PIF32(%[output], %[input])
        :[output] "=t" (result_f32)
        :[input] "t" (src)
    );

    return result_f32;
}

//*****************************************************************************
//
//! \brief Divides the input by 2*pi.
//!
//! \param src is the input value.
//!
//! \return Returns src / (2*pi).
//
//*****************************************************************************
__STATIC_FORCEINLINE float __div2pif32(float src)
{
    float result_f32;

    __ASM volatile (
        DIV2PIF32(%[output], %[input])
        :[output] "=t" (result_f32)
        :[input] "t" (src)
    );

    return result_f32;
}

//*****************************************************************************
//
//! \brief Computes the square root.
//!
//! \param src is the input value.
//!
//! \return Returns sqrt(src).
//
//*****************************************************************************
__STATIC_FORCEINLINE float __sqrtf32(float src)
{
    float result_f32;

    __ASM volatile (
        SQRTF32(%[output], %[input])
        :[output] "=t" (result_f32)
        :[input] "t" (src)
    );

    return result_f32;
}

//*****************************************************************************
//
//! \brief Divides two single-precision values.
//!
//! \param num is the numerator; denom is the denominator.
//!
//! \return Returns num / denom.
//
//*****************************************************************************
__STATIC_FORCEINLINE float __divf32(float num, float denom)
{
    float result_f32;

    __ASM volatile (
        DIVF32(%[output], %[input1], %[input2])
        :[output] "=t" (result_f32)
        :[input1] "t" (num), [input2] "t" (denom)
    );

    return result_f32;
}

//*****************************************************************************
//
//! \brief Returns the atan2 quadrant offset in per-unit form.
//!
//! \param y is the Y input; x is the X input.
//!
//! \return Returns the quadrant term for atan2.
//
//*****************************************************************************
__STATIC_FORCEINLINE float __quadf32(float y, float x)
{
    float quadrant;

    __ASM volatile (
        QUADF32(%[output], %[input1], %[input2])
        :[output] "=t" (quadrant)
        :[input1] "t" (y), [input2] "t" (x)
    );

    return quadrant;
}

//*****************************************************************************
//
//! \brief Computes |y/x| for atan2.
//!
//! \param y is the Y input; x is the X input.
//!
//! \return Returns |y/x|.
//
//*****************************************************************************
__STATIC_FORCEINLINE float __divf32_atan2(float y, float x)
{
    float ratio;

    __ASM volatile (
        DIVF32_ATAN2(%[output], %[input1], %[input2])
        :[output] "=t" (ratio)
        :[input1] "t" (y), [input2] "t" (x)
    );

    return ratio;
}

//*****************************************************************************
//
//! \brief Returns the 64-bit remainder from CX1D divide.
//!
//! \param x is the low operand passed to CX1D.
//!
//! \return Returns the 64-bit remainder.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint64_t __div64re64(uint32_t x)
{
    uint64_t remainder = 0ULL;

    (void)x;

    __ASM volatile (
        "cx1d p0, %Q0, %R0, #0x0"
        : "=r" (remainder)
        :
        : "cc", "memory"
    );

    return remainder;
}

//*****************************************************************************
//
//! \brief Unsigned 64-bit divide (CX3DA mode 0).
//!
//! \param y is the low dividend word; x1 is the high dividend word; x2 is the divisor.
//!
//! \return Returns the 64-bit quotient.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint64_t __div64uu64(uint32_t y, uint32_t x1, uint32_t x2)
{
    uint64_t quotient = ((uint64_t)x1 << 32) | (uint64_t)y;
    const uint64_t divisor = (uint64_t)x2;

    __ASM volatile (
        "cx3da p0, %Q0, %R0, %Q1, %R1, #0x0"
        : "+r" (quotient)
        : "r" (divisor)
        : "cc", "memory"
    );

    return quotient;
}

//*****************************************************************************
//
//! \brief Signed/unsigned 64-bit divide (CX3DA mode 1).
//!
//! \param y is the low dividend word; x1 is the high dividend word; x2 is the divisor.
//!
//! \return Returns the 64-bit quotient.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint64_t __div64iu64(uint32_t y, uint32_t x1, uint32_t x2)
{
    uint64_t quotient = ((uint64_t)x1 << 32) | (uint64_t)y;
    const uint64_t divisor = (uint64_t)x2;

    __ASM volatile (
        "cx3da p0, %Q0, %R0, %Q1, %R1, #0x1"
        : "+r" (quotient)
        : "r" (divisor)
        : "cc", "memory"
    );

    return quotient;
}

//*****************************************************************************
//
//! \brief Signed 64-bit divide (CX3DA mode 2).
//!
//! \param y is the low dividend word; x1 is the high dividend word; x2 is the signed divisor.
//!
//! \return Returns the 64-bit quotient.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint64_t __div64ii64(uint32_t y, uint32_t x1, uint32_t x2)
{
    uint64_t quotient = ((uint64_t)x1 << 32) | (uint64_t)y;
    const uint64_t divisor = (uint64_t)(uint32_t)x2;

    __ASM volatile (
        "cx3da p0, %Q0, %R0, %Q1, %R1, #0x2"
        : "+r" (quotient)
        : "r" (divisor)
        : "cc", "memory"
    );

    return quotient;
}

//*****************************************************************************
//
//! \brief CRC-8 on the low byte (CX2A).
//!
//! \param y is the accumulated CRC; x is the new data word.
//!
//! \return Returns the updated CRC.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint32_t __crc8l32(uint32_t y, uint32_t x)
{
    uint32_t result = y;

    __ASM volatile (
        _CX2A(%[output], %[input], 0x8)
        : [output] "+r" (result)
        : [input] "r" (x)
        : "cc", "memory"
    );

    return result;
}

//*****************************************************************************
//
//! \brief CRC-16 polynomial 1 on the low halfword (CX2A).
//!
//! \param y is the accumulated CRC; x is the new data word.
//!
//! \return Returns the updated CRC.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint32_t __crc16p1l32(uint32_t y, uint32_t x)
{
    uint32_t result = y;

    __ASM volatile (
        _CX2A(%[output], %[input], 0x9)
        : [output] "+r" (result)
        : [input] "r" (x)
        : "cc", "memory"
    );

    return result;
}

//*****************************************************************************
//
//! \brief CRC-16 polynomial 2 on the low halfword (CX2A).
//!
//! \param y is the accumulated CRC; x is the new data word.
//!
//! \return Returns the updated CRC.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint32_t __crc16p2l32(uint32_t y, uint32_t x)
{
    uint32_t result = y;

    __ASM volatile (
        _CX2A(%[output], %[input], 0xa)
        : [output] "+r" (result)
        : [input] "r" (x)
        : "cc", "memory"
    );

    return result;
}

//*****************************************************************************
//
//! \brief CRC-32 on the low word (CX2A).
//!
//! \param y is the accumulated CRC; x is the new data word.
//!
//! \return Returns the updated CRC.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint32_t __crc32l32(uint32_t y, uint32_t x)
{
    uint32_t result = y;

    __ASM volatile (
        _CX2A(%[output], %[input], 0xb)
        : [output] "+r" (result)
        : [input] "r" (x)
        : "cc", "memory"
    );

    return result;
}

//*****************************************************************************
//
//! \brief CRC-8 on the high byte (CX2A).
//!
//! \param y is the accumulated CRC; x is the new data word.
//!
//! \return Returns the updated CRC.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint32_t __crc8h32(uint32_t y, uint32_t x)
{
    uint32_t result = y;

    __ASM volatile (
        _CX2A(%[output], %[input], 0xc)
        : [output] "+r" (result)
        : [input] "r" (x)
        : "cc", "memory"
    );

    return result;
}

//*****************************************************************************
//
//! \brief CRC-16 polynomial 1 on the high halfword (CX2A).
//!
//! \param y is the accumulated CRC; x is the new data word.
//!
//! \return Returns the updated CRC.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint32_t __crc16p1h32(uint32_t y, uint32_t x)
{
    uint32_t result = y;

    __ASM volatile (
        _CX2A(%[output], %[input], 0xd)
        : [output] "+r" (result)
        : [input] "r" (x)
        : "cc", "memory"
    );

    return result;
}

//*****************************************************************************
//
//! \brief CRC-16 polynomial 2 on the high halfword (CX2A).
//!
//! \param y is the accumulated CRC; x is the new data word.
//!
//! \return Returns the updated CRC.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint32_t __crc16p2h32(uint32_t y, uint32_t x)
{
    uint32_t result = y;

    __ASM volatile (
        _CX2A(%[output], %[input], 0xe)
        : [output] "+r" (result)
        : [input] "r" (x)
        : "cc", "memory"
    );

    return result;
}

//*****************************************************************************
//
//! \brief CRC-32 on the high word (CX2A).
//!
//! \param y is the accumulated CRC; x is the new data word.
//!
//! \return Returns the updated CRC.
//
//*****************************************************************************
__STATIC_FORCEINLINE uint32_t __crc32h32(uint32_t y, uint32_t x)
{
    uint32_t result = y;

    __ASM volatile (
        _CX2A(%[output], %[input], 0xf)
        : [output] "+r" (result)
        : [input] "r" (x)
        : "cc", "memory"
    );

    return result;
}

//*****************************************************************************
//
//! \brief Computes atan2(y,x)/pi in per-unit form.
//!
//! \param y is the Y input; x is the X input.
//!
//! \return Returns atan2(y,x)/pi.
//
//*****************************************************************************
__STATIC_FORCEINLINE float __atan2puf32(float y, float x)
{
    float quadrant;
    float ratio;
    float result_atanpu;
    float result_f32;

    __ASM volatile (
        QUADF32(%[output1], %[input1], %[input2])
        :[output1] "+t" (quadrant)
        :[input1] "t" (y), [input2] "t" (x)
    );
    __ASM volatile (
        DIVF32_ATAN2(%[output2], %[input1], %[input2])
        :[output2] "+t" (ratio)
        :[input1] "t" (y), [input2] "t" (x)
    );
    __ASM volatile (
        ATANPUF32(%[output], %[input])
        :[output] "+t" (result_atanpu) 
        :[input] "t" (ratio)
    );
    __ASM volatile (
        _ADDF32(%[output], %[input1], %[input2])
        :[output] "+t" (result_f32) 
        :[input1] "t" (quadrant), [input2] "t" (result_atanpu)
    );

    return result_f32;
}

//*****************************************************************************
//
//! \brief Computes atan2(y,x) in radians.
//!
//! \param y is the Y input; x is the X input.
//!
//! \return Returns atan2(y,x).
//
//*****************************************************************************
__STATIC_FORCEINLINE float __atan2(float y, float x)
{
    float quadrant;
    float ratio;
    float result_atanpu;
    float result_add;
    float result_f32;

    __ASM volatile (
        QUADF32(%[output1], %[input1], %[input2])
        :[output1] "+t" (quadrant)
        :[input1] "t" (y), [input2] "t" (x)
    );
    __ASM volatile (
        DIVF32_ATAN2(%[output2], %[input1], %[input2])
        :[output2] "+t" (ratio)
        :[input1] "t" (y), [input2] "t" (x)
    );
    __ASM volatile (
        ATANPUF32(%[output], %[input])
        :[output] "+t" (result_atanpu) 
        :[input] "t" (ratio)
    );
    __ASM volatile (
        _ADDF32(%[output], %[input1], %[input2])
        :[output] "+t" (result_add) 
        :[input1] "t" (quadrant), [input2] "t" (result_atanpu)
    );
    __ASM volatile (
        MPY2PIF32(%[output], %[input])
        :[output] "+t" (result_f32) 
        :[input] "t" (result_add)
    );

    return result_f32;
}

#if defined(__ZIDIAN_FCAU__)
//*****************************************************************************
//
// Instead software interface in math.h if defined __ZIDIAN_FCAU__
//
//*****************************************************************************
//*****************************************************************************
//
//! \brief Relaxed sqrtf() mapping when __ZIDIAN_FCAU__ is defined.
//!
//! \param x is the input value.
//!
//! \return Returns sqrt(x) via Zidian hardware.
//
//*****************************************************************************
#undef sqrtf
#define sqrtf   __relaxed_sqrtf
__STATIC_FORCEINLINE float __relaxed_sqrtf(float x)
{
    return __sqrtf32(x);
}

//*****************************************************************************
//
//! \brief Relaxed sinf() mapping when __ZIDIAN_FCAU__ is defined.
//!
//! \param x is the angle in radians.
//!
//! \return Returns sin(x) via Zidian hardware.
//
//*****************************************************************************
#undef sinf
#define sinf    __relaxed_sinf
__STATIC_FORCEINLINE float __relaxed_sinf(float x)
{
    return __sin(x);
}

//*****************************************************************************
//
//! \brief Relaxed cosf() mapping when __ZIDIAN_FCAU__ is defined.
//!
//! \param x is the angle in radians.
//!
//! \return Returns cos(x) via Zidian hardware.
//
//*****************************************************************************
#undef cosf
#define cosf    __relaxed_cosf
__STATIC_FORCEINLINE float __relaxed_cosf(float x)
{
    return __cos(x);
}

//*****************************************************************************
//
//! \brief Relaxed atanf() mapping when __ZIDIAN_FCAU__ is defined.
//!
//! \param x is the input value.
//!
//! \return Returns atan(x) via Zidian hardware.
//
//*****************************************************************************
#undef atanf
#define atanf   __relaxed_atanf
__STATIC_FORCEINLINE float __relaxed_atanf(float x)
{
    return __atan2(x, 1.0f);
}

//*****************************************************************************
//
//! \brief Relaxed atan2f() mapping when __ZIDIAN_FCAU__ is defined.
//!
//! \param y is the Y input; x is the X input.
//!
//! \return Returns atan2(y,x) via Zidian hardware.
//
//*****************************************************************************
#undef atan2f
#define atan2f  __relaxed_atan2f
__STATIC_FORCEINLINE float __relaxed_atan2f(float y, float x)
{
    return __atan2(y, x);
}

#endif // __ZIDIAN_FCAU__

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

#endif // ZIDIAN_MATH_H
