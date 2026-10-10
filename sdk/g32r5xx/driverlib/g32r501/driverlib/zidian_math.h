//###########################################################################
//
// FILE:    zidian_math.h
//
// TITLE:   Zidian for Math.
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

#ifndef ZIDIAN_MATH_H
#define ZIDIAN_MATH_H

#include <math.h>
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
// Instrinsic Functions
//
//*****************************************************************************
//
// __sinpuf32(float)
//
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

//
// __sin(float)
//
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

//
// __cospuf32(float)
//
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

//
// __cos(float)
//
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

//
// __atanpuf32(float)
//
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

//
// __atan(float)
//
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

//
// __mpy2pif32(float)
//
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

//
// __div2pif32(float)
//
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

//
// __sqrtf32(float)
//
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

//
// __divf32(float, float)
//
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

//
// __quadf32(float, float)
//
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

//
// __divf32_atan2(float, float)
//
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

//
// __atan2puf32(float, float)
//
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

//
// __atan2(float, float)
//
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
//
// sqrtf(float)
//
#undef sqrtf
#define sqrtf   __relaxed_sqrtf
__STATIC_FORCEINLINE float __relaxed_sqrtf(float x)
{
    return __sqrtf32(x);
}

//
// sinf(float)
//
#undef sinf
#define sinf    __relaxed_sinf
__STATIC_FORCEINLINE float __relaxed_sinf(float x)
{
    return __sin(x);
}

//
// cosf(float)
//
#undef cosf
#define cosf    __relaxed_cosf
__STATIC_FORCEINLINE float __relaxed_cosf(float x)
{
    return __cos(x);
}

//
// atanf(float)
//
#undef atanf
#define atanf   __relaxed_atanf
__STATIC_FORCEINLINE float __relaxed_atanf(float x)
{
    return __atan2(x, 1.0f);
}

//
// atan2f(float, float)
//
#undef atan2f
#define atan2f  __relaxed_atan2f
__STATIC_FORCEINLINE float __relaxed_atan2f(float y, float x)
{
    return __atan2(y, x);
}

#endif // __ZIDIAN_FCAU__

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // ZIDIAN_MATH_H
