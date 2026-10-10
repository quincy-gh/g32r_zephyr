//###########################################################################
//
// FILE:    xbar.h
//
// TITLE:   G32R501 X-BAR driver.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//
// Modifications:
// - 2024-09-13:
// 1. Macro definitions, enum definitions, function naming
//
//###########################################################################

#ifndef XBAR_H
#define XBAR_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup xbar_api XBAR
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_flbxbar.h"
#include "inc/hw_pwmxbar.h"
#include "inc/hw_inputxbar.h"
#include "inc/hw_outputxbar.h"
#include "inc/hw_xbar.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Useful defines used within the driver functions.
// Not intended for use by application code.
//
//*****************************************************************************
#define XBAR_OUTPUT_CFG_REG_BASE  (OUTPUTXBAR_BASE + XBAR_O_OUTPUT1MUX0TO15CFG)
#define XBAR_OUTPUT_EN_REG_BASE   (OUTPUTXBAR_BASE + XBAR_O_OUTPUT1MUXENABLE)
#define XBAR_PWM_CFG_REG_BASE     (PWMXBAR_BASE + XBAR_O_TRIP4MUX0TO15CFG)
#define XBAR_PWM_EN_REG_BASE      (PWMXBAR_BASE + XBAR_O_TRIP4MUXENABLE)
#define XBAR_FLB_CFG_REG_BASE     (FLBXBAR_BASE + XBAR_O_AUXSIG0MUX0TO15CFG)
#define XBAR_FLB_EN_REG_BASE      (FLBXBAR_BASE + XBAR_O_AUXSIG0MUXENABLE)
#define XBAR_INPUT_BASE           (INPUTXBAR_BASE + XBAR_O_INPUT1SELECT)

#define XBAR_INPUT_FLG_INPUT_M    0x00FFU
#define XBAR_INPUT_FLG_REG_M      0xFF00U
#define XBAR_INPUT_FLG_REG_1      0x0000U
#define XBAR_INPUT_FLG_REG_2      0x0100U
#define XBAR_INPUT_FLG_REG_3      0x0200U
#define XBAR_INPUT_FLG_REG_4      0x0300U

#define XBAR_GPIO_MAX_CNT                59U
#define XBAR_GPIO_AIO_MIN_CNT            224U
#define XBAR_GPIO_AIO_MAX_CNT            247U
#define XBAR_NON_GPIO_MIN_CNT            0xFFFDU
#define XBAR_NON_GPIO_MAX_CNT            0xFFFFU

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
// The following values define the muxes parameter for XBAR_enablePWMMux(),
// XBAR_enableOutputMux(), XBAR_disablePWMMux(), and
// XBAR_disableOutputMux().
//
//*****************************************************************************
#define XBAR_MUX00                  0x00000001U //!< Mask for X-BAR mux 0
#define XBAR_MUX01                  0x00000002U //!< Mask for X-BAR mux 1
#define XBAR_MUX02                  0x00000004U //!< Mask for X-BAR mux 2
#define XBAR_MUX03                  0x00000008U //!< Mask for X-BAR mux 3
#define XBAR_MUX04                  0x00000010U //!< Mask for X-BAR mux 4
#define XBAR_MUX05                  0x00000020U //!< Mask for X-BAR mux 5
#define XBAR_MUX06                  0x00000040U //!< Mask for X-BAR mux 6
#define XBAR_MUX07                  0x00000080U //!< Mask for X-BAR mux 7
#define XBAR_MUX08                  0x00000100U //!< Mask for X-BAR mux 8
#define XBAR_MUX09                  0x00000200U //!< Mask for X-BAR mux 9
#define XBAR_MUX10                  0x00000400U //!< Mask for X-BAR mux 10
#define XBAR_MUX11                  0x00000800U //!< Mask for X-BAR mux 11
#define XBAR_MUX12                  0x00001000U //!< Mask for X-BAR mux 12
#define XBAR_MUX13                  0x00002000U //!< Mask for X-BAR mux 13
#define XBAR_MUX14                  0x00004000U //!< Mask for X-BAR mux 14
#define XBAR_MUX15                  0x00008000U //!< Mask for X-BAR mux 15
#define XBAR_MUX16                  0x00010000U //!< Mask for X-BAR mux 16
#define XBAR_MUX17                  0x00020000U //!< Mask for X-BAR mux 17
#define XBAR_MUX18                  0x00040000U //!< Mask for X-BAR mux 18
#define XBAR_MUX19                  0x00080000U //!< Mask for X-BAR mux 19
#define XBAR_MUX20                  0x00100000U //!< Mask for X-BAR mux 20
#define XBAR_MUX21                  0x00200000U //!< Mask for X-BAR mux 21
#define XBAR_MUX22                  0x00400000U //!< Mask for X-BAR mux 22
#define XBAR_MUX23                  0x00800000U //!< Mask for X-BAR mux 23
#define XBAR_MUX24                  0x01000000U //!< Mask for X-BAR mux 24
#define XBAR_MUX25                  0x02000000U //!< Mask for X-BAR mux 25
#define XBAR_MUX26                  0x04000000U //!< Mask for X-BAR mux 26
#define XBAR_MUX27                  0x08000000U //!< Mask for X-BAR mux 27
#define XBAR_MUX28                  0x10000000U //!< Mask for X-BAR mux 28
#define XBAR_MUX29                  0x20000000U //!< Mask for X-BAR mux 29
#define XBAR_MUX30                  0x40000000U //!< Mask for X-BAR mux 30
#define XBAR_MUX31                  0x80000000U //!< Mask for X-BAR mux 31
#endif

//*****************************************************************************
//
//! The following values define the \e output parameter for
//! XBAR_setOutputMuxConfig(), XBAR_enableOutputMux(), and
//! XBAR_disableOutputMux().
//
//*****************************************************************************
typedef enum
{
    XBAR_OUTPUT1 = 0,       //!< OUTPUT1 of the Output X-BAR
    XBAR_OUTPUT2 = 2,       //!< OUTPUT2 of the Output X-BAR
    XBAR_OUTPUT3 = 4,       //!< OUTPUT3 of the Output X-BAR
    XBAR_OUTPUT4 = 6,       //!< OUTPUT4 of the Output X-BAR
    XBAR_OUTPUT5 = 8,       //!< OUTPUT5 of the Output X-BAR
    XBAR_OUTPUT6 = 10,      //!< OUTPUT6 of the Output X-BAR
    XBAR_OUTPUT7 = 12,      //!< OUTPUT7 of the Output X-BAR
    XBAR_OUTPUT8 = 14       //!< OUTPUT8 of the Output X-BAR
} XBAR_OutputNum;

//*****************************************************************************
//
//! The following values define the \e trip parameter for
//! XBAR_setPWMMuxConfig(), XBAR_enablePWMMux(), and XBAR_disablePWMMux().
//
//*****************************************************************************
typedef enum
{
    XBAR_TRIP4  = 0,        //!< TRIP4 of the PWM X-BAR
    XBAR_TRIP5  = 2,        //!< TRIP5 of the PWM X-BAR
    XBAR_TRIP7  = 4,        //!< TRIP7 of the PWM X-BAR
    XBAR_TRIP8  = 6,        //!< TRIP8 of the PWM X-BAR
    XBAR_TRIP9  = 8,        //!< TRIP9 of the PWM X-BAR
    XBAR_TRIP10 = 10,       //!< TRIP10 of the PWM X-BAR
    XBAR_TRIP11 = 12,       //!< TRIP11 of the PWM X-BAR
    XBAR_TRIP12 = 14        //!< TRIP12 of the PWM X-BAR
} XBAR_TripNum;

//*****************************************************************************
//
// The following values define the trip parameter for XBAR_setFLBMuxConfig(),
// XBAR_enableFLBMux(), and XBAR_disableFLBMux().
//
//*****************************************************************************
typedef enum
{
    XBAR_AUXSIG0 = 0,
    XBAR_AUXSIG1 = 2,
    XBAR_AUXSIG2 = 4,
    XBAR_AUXSIG3 = 6,
    XBAR_AUXSIG4 = 8,
    XBAR_AUXSIG5 = 10,
    XBAR_AUXSIG6 = 12,
    XBAR_AUXSIG7 = 14
} XBAR_AuxSigNum;

//*****************************************************************************
//
//! The following values define the \e input parameter for XBAR_setInputPin().
//
//*****************************************************************************
typedef enum
{
    XBAR_INPUT1,            //!< PWM[TZ1], PWM[TRIP1], X-BARs, CAPs
    XBAR_INPUT2,            //!< PWM[TZ2], PWM[TRIP2], X-BARs, CAPs
    XBAR_INPUT3,            //!< PWM[TZ3], PWM[TRIP3], X-BARs, CAPs
    XBAR_INPUT4,            //!< ADC wrappers, X-BARs, XINT1, CAPs
    XBAR_INPUT5,            //!< EXTSYNCIN1, X-BARs, XINT2, CAPs
    XBAR_INPUT6,            //!< EXTSYNCIN2, PWM[TRIP6], X-BARs, XINT3, CAPs
    XBAR_INPUT7,            //!< X-BARs, CAPs
    XBAR_INPUT8,            //!< X-BARs, CAPs
    XBAR_INPUT9,            //!< X-BARs, CAPs
    XBAR_INPUT10,           //!< X-BARs, CAPs
    XBAR_INPUT11,           //!< X-BARs, CAPs
    XBAR_INPUT12,           //!< X-BARs, CAPs
    XBAR_INPUT13,           //!< XINT4, X-BARs, CAPs
    XBAR_INPUT14,           //!< XINT5, X-BARs, CAPs
    XBAR_INPUT15,           //!< CAPs
    XBAR_INPUT16            //!< CAPs
} XBAR_InputNum;

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
//! The following values define the \e muxConfig parameter for
//! XBAR_setOutputMuxConfig().
//
//*****************************************************************************
typedef enum
{
    //
    //OUTPUTXBAR
    //
    XBAR_OUT_MUX00_COMP1_CTRIPOUTH        = 0x0000,
    XBAR_OUT_MUX00_COMP1_CTRIPOUTH_OR_L   = 0x0001,
    XBAR_OUT_MUX00_ADCAEVT1                = 0x0002,
    XBAR_OUT_MUX00_CAP1_OUT               = 0x0003,
    XBAR_OUT_MUX01_COMP1_CTRIPOUTL        = 0x0200,
    XBAR_OUT_MUX01_INPUTXBAR1              = 0x0201,
    XBAR_OUT_MUX01_FLB1_OUT4               = 0x0202,
    XBAR_OUT_MUX01_ADCCEVT1                = 0x0203,
    XBAR_OUT_MUX02_COMP2_CTRIPOUTH        = 0x0400,
    XBAR_OUT_MUX02_COMP2_CTRIPOUTH_OR_L   = 0x0401,
    XBAR_OUT_MUX02_ADCAEVT2                = 0x0402,
    XBAR_OUT_MUX02_CAP2_OUT               = 0x0403,
    XBAR_OUT_MUX03_COMP2_CTRIPOUTL        = 0x0600,
    XBAR_OUT_MUX03_INPUTXBAR2              = 0x0601,
    XBAR_OUT_MUX03_FLB1_OUT5               = 0x0602,
    XBAR_OUT_MUX03_ADCCEVT2                = 0x0603,
    XBAR_OUT_MUX04_COMP3_CTRIPOUTH        = 0x0800,
    XBAR_OUT_MUX04_COMP3_CTRIPOUTH_OR_L   = 0x0801,
    XBAR_OUT_MUX04_ADCAEVT3                = 0x0802,
    XBAR_OUT_MUX04_CAP3_OUT               = 0x0803,
    XBAR_OUT_MUX05_COMP3_CTRIPOUTL        = 0x0A00,
    XBAR_OUT_MUX05_INPUTXBAR3              = 0x0A01,
    XBAR_OUT_MUX05_FLB2_OUT4               = 0x0A02,
    XBAR_OUT_MUX05_ADCCEVT3                = 0x0A03,
    XBAR_OUT_MUX06_COMP4_CTRIPOUTH        = 0x0C00,
    XBAR_OUT_MUX06_COMP4_CTRIPOUTH_OR_L   = 0x0C01,
    XBAR_OUT_MUX06_ADCAEVT4                = 0x0C02,
    XBAR_OUT_MUX06_CAP4_OUT               = 0x0C03,
    XBAR_OUT_MUX07_COMP4_CTRIPOUTL        = 0x0E00,
    XBAR_OUT_MUX07_INPUTXBAR4              = 0x0E01,
    XBAR_OUT_MUX07_FLB2_OUT5               = 0x0E02,
    XBAR_OUT_MUX07_ADCCEVT4                = 0x0E03,
    XBAR_OUT_MUX08_COMP5_CTRIPOUTH        = 0x1000,
    XBAR_OUT_MUX08_COMP5_CTRIPOUTH_OR_L   = 0x1001,
    XBAR_OUT_MUX08_ADCBEVT1                = 0x1002,
    XBAR_OUT_MUX08_CAP5_OUT               = 0x1003,
    XBAR_OUT_MUX09_COMP5_CTRIPOUTL        = 0x1200,
    XBAR_OUT_MUX09_INPUTXBAR5              = 0x1201,
    XBAR_OUT_MUX09_FLB3_OUT4               = 0x1202,
    XBAR_OUT_MUX10_COMP6_CTRIPOUTH        = 0x1400,
    XBAR_OUT_MUX10_COMP6_CTRIPOUTH_OR_L   = 0x1401,
    XBAR_OUT_MUX10_ADCBEVT2                = 0x1402,
    XBAR_OUT_MUX10_CAP6_OUT               = 0x1403,
    XBAR_OUT_MUX11_COMP6_CTRIPOUTL        = 0x1600,
    XBAR_OUT_MUX11_INPUTXBAR6              = 0x1601,
    XBAR_OUT_MUX11_FLB3_OUT5               = 0x1602,
    XBAR_OUT_MUX12_COMP7_CTRIPOUTH        = 0x1800,
    XBAR_OUT_MUX12_COMP7_CTRIPOUTH_OR_L   = 0x1801,
    XBAR_OUT_MUX12_ADCBEVT3                = 0x1802,
    XBAR_OUT_MUX12_CAP7_OUT               = 0x1803,
    XBAR_OUT_MUX13_COMP7_CTRIPOUTL        = 0x1A00,
    XBAR_OUT_MUX13_ADCSOCA                 = 0x1A01,
    XBAR_OUT_MUX13_FLB4_OUT4               = 0x1A02,
    XBAR_OUT_MUX14_ADCBEVT4                = 0x1C02,
    XBAR_OUT_MUX14_EXTSYNCOUT              = 0x1C03,
    XBAR_OUT_MUX15_ADCSOCB                 = 0x1E01,
    XBAR_OUT_MUX15_FLB4_OUT5               = 0x1E02,
    XBAR_OUT_MUX16_SD1FLT1_COMPH           = 0x2000,
    XBAR_OUT_MUX16_SD1FLT1_COMPH_OR_COMPL  = 0x2001,
    XBAR_OUT_MUX17_SD1FLT1_COMPL           = 0x2200,
    XBAR_OUT_MUX18_SD1FLT2_COMPH           = 0x2400,
    XBAR_OUT_MUX18_SD1FLT2_COMPH_OR_COMPL  = 0x2401,
    XBAR_OUT_MUX19_SD1FLT2_COMPL           = 0x2600,
    XBAR_OUT_MUX20_SD1FLT3_COMPH           = 0x2800,
    XBAR_OUT_MUX20_SD1FLT3_COMPH_OR_COMPL  = 0x2801,
    XBAR_OUT_MUX21_SD1FLT3_COMPL           = 0x2A00,
    XBAR_OUT_MUX22_SD1FLT4_COMPH           = 0x2C00,
    XBAR_OUT_MUX22_SD1FLT4_COMPH_OR_COMPL  = 0x2C01,
    XBAR_OUT_MUX23_SD1FLT4_COMPL           = 0x2E00

} XBAR_OutputMuxConfig;

//*****************************************************************************
//
//! The following values define the \e muxConfig parameter for
//! XBAR_setPWMMuxConfig().
//
//*****************************************************************************
typedef enum
{
    XBAR_PWM_MUX00_COMP1_CTRIPH          = 0x0000,
    XBAR_PWM_MUX00_COMP1_CTRIPH_OR_L     = 0x0001,
    XBAR_PWM_MUX00_ADCAEVT1               = 0x0002,
    XBAR_PWM_MUX00_CAP1_OUT              = 0x0003,
    XBAR_PWM_MUX01_COMP1_CTRIPL          = 0x0200,
    XBAR_PWM_MUX01_INPUTXBAR1             = 0x0201,
    XBAR_PWM_MUX01_FLB1_OUT4              = 0x0202,
    XBAR_PWM_MUX01_ADCCEVT1               = 0x0203,
    XBAR_PWM_MUX02_COMP2_CTRIPH          = 0x0400,
    XBAR_PWM_MUX02_COMP2_CTRIPH_OR_L     = 0x0401,
    XBAR_PWM_MUX02_ADCAEVT2               = 0x0402,
    XBAR_PWM_MUX02_CAP2_OUT              = 0x0403,
    XBAR_PWM_MUX03_COMP2_CTRIPL          = 0x0600,
    XBAR_PWM_MUX03_INPUTXBAR2             = 0x0601,
    XBAR_PWM_MUX03_FLB1_OUT5              = 0x0602,
    XBAR_PWM_MUX03_ADCCEVT2               = 0x0603,
    XBAR_PWM_MUX04_COMP3_CTRIPH          = 0x0800,
    XBAR_PWM_MUX04_COMP3_CTRIPH_OR_L     = 0x0801,
    XBAR_PWM_MUX04_ADCAEVT3               = 0x0802,
    XBAR_PWM_MUX04_CAP3_OUT              = 0x0803,
    XBAR_PWM_MUX05_COMP3_CTRIPL          = 0x0A00,
    XBAR_PWM_MUX05_INPUTXBAR3             = 0x0A01,
    XBAR_PWM_MUX05_FLB2_OUT4              = 0x0A02,
    XBAR_PWM_MUX05_ADCCEVT3               = 0x0A03,
    XBAR_PWM_MUX06_COMP4_CTRIPH          = 0x0C00,
    XBAR_PWM_MUX06_COMP4_CTRIPH_OR_L     = 0x0C01,
    XBAR_PWM_MUX06_ADCAEVT4               = 0x0C02,
    XBAR_PWM_MUX06_CAP4_OUT              = 0x0C03,
    XBAR_PWM_MUX07_COMP4_CTRIPL          = 0x0E00,
    XBAR_PWM_MUX07_INPUTXBAR4             = 0x0E01,
    XBAR_PWM_MUX07_FLB2_OUT5              = 0x0E02,
    XBAR_PWM_MUX07_ADCCEVT4               = 0x0E03,
    XBAR_PWM_MUX08_COMP5_CTRIPH          = 0x1000,
    XBAR_PWM_MUX08_COMP5_CTRIPH_OR_L     = 0x1001,
    XBAR_PWM_MUX08_ADCBEVT1               = 0x1002,
    XBAR_PWM_MUX08_CAP5_OUT              = 0x1003,
    XBAR_PWM_MUX09_COMP5_CTRIPL          = 0x1200,
    XBAR_PWM_MUX09_INPUTXBAR5             = 0x1201,
    XBAR_PWM_MUX09_FLB3_OUT4              = 0x1202,
    XBAR_PWM_MUX10_COMP6_CTRIPH          = 0x1400,
    XBAR_PWM_MUX10_COMP6_CTRIPH_OR_L     = 0x1401,
    XBAR_PWM_MUX10_ADCBEVT2               = 0x1402,
    XBAR_PWM_MUX10_CAP6_OUT              = 0x1403,
    XBAR_PWM_MUX11_COMP6_CTRIPL          = 0x1600,
    XBAR_PWM_MUX11_INPUTXBAR6             = 0x1601,
    XBAR_PWM_MUX11_FLB3_OUT5              = 0x1602,
    XBAR_PWM_MUX12_COMP7_CTRIPH          = 0x1800,
    XBAR_PWM_MUX12_COMP7_CTRIPH_OR_L     = 0x1801,
    XBAR_PWM_MUX12_ADCBEVT3               = 0x1802,
    XBAR_PWM_MUX12_CAP7_OUT              = 0x1803,
    XBAR_PWM_MUX13_COMP7_CTRIPL          = 0x1A00,
    XBAR_PWM_MUX13_ADCSOCA                = 0x1A01,
    XBAR_PWM_MUX13_FLB4_OUT4              = 0x1A02,
    XBAR_PWM_MUX14_ADCBEVT4               = 0x1C02,
    XBAR_PWM_MUX14_EXTSYNCOUT             = 0x1C03,
    XBAR_PWM_MUX15_ADCSOCB                = 0x1E01,
    XBAR_PWM_MUX15_FLB4_OUT5              = 0x1E02,
    XBAR_PWM_MUX16_SD1FLT1_COMPH          = 0x2000,
    XBAR_PWM_MUX16_SD1FLT1_COMPH_OR_COMPL = 0x2001,
    XBAR_PWM_MUX17_SD1FLT1_COMPL          = 0x2200,
    XBAR_PWM_MUX17_INPUTXBAR7             = 0x2201,
    XBAR_PWM_MUX18_SD1FLT2_COMPH          = 0x2400,
    XBAR_PWM_MUX18_SD1FLT2_COMPH_OR_COMPL = 0x2401,
    XBAR_PWM_MUX19_SD1FLT2_COMPL          = 0x2600,
    XBAR_PWM_MUX19_INPUTXBAR8             = 0x2601,
    XBAR_PWM_MUX20_SD1FLT3_COMPH          = 0x2800,
    XBAR_PWM_MUX20_SD1FLT3_COMPH_OR_COMPL = 0x2801,
    XBAR_PWM_MUX21_SD1FLT3_COMPL          = 0x2A00,
    XBAR_PWM_MUX21_INPUTXBAR9             = 0x2A01,
    XBAR_PWM_MUX22_SD1FLT4_COMPH          = 0x2C00,
    XBAR_PWM_MUX22_SD1FLT4_COMPH_OR_COMPL = 0x2C01,
    XBAR_PWM_MUX23_SD1FLT4_COMPL          = 0x2E00,
    XBAR_PWM_MUX23_INPUTXBAR10            = 0x2E01,
    XBAR_PWM_MUX25_INPUTXBAR11            = 0x3201,
    XBAR_PWM_MUX27_INPUTXBAR12            = 0x3601,
    XBAR_PWM_MUX29_INPUTXBAR13            = 0x3A01,
    XBAR_PWM_MUX31_INPUTXBAR14            = 0x3E01
} XBAR_PWMMuxConfig;

//*****************************************************************************
//
// The following values define the muxConfig parameter for
// XBAR_setFLBMuxConfig().
//
//*****************************************************************************
typedef enum
{
    XBAR_FLB_MUX00_COMP1_CTRIPH           = 0x0000,
    XBAR_FLB_MUX00_COMP1_CTRIPH_OR_L      = 0x0001,
    XBAR_FLB_MUX00_ADCAEVT1                = 0x0002,
    XBAR_FLB_MUX00_CAP1_OUT               = 0x0003,
    XBAR_FLB_MUX01_COMP1_CTRIPL           = 0x0200,
    XBAR_FLB_MUX01_INPUTXBAR1              = 0x0201,
    XBAR_FLB_MUX01_FLB1_OUT4               = 0x0202,
    XBAR_FLB_MUX01_ADCCEVT1                = 0x0203,
    XBAR_FLB_MUX02_COMP2_CTRIPH           = 0x0400,
    XBAR_FLB_MUX02_COMP2_CTRIPH_OR_L      = 0x0401,
    XBAR_FLB_MUX02_ADCAEVT2                = 0x0402,
    XBAR_FLB_MUX02_CAP2_OUT               = 0x0403,
    XBAR_FLB_MUX03_COMP2_CTRIPL           = 0x0600,
    XBAR_FLB_MUX03_INPUTXBAR2              = 0x0601,
    XBAR_FLB_MUX03_FLB1_OUT5               = 0x0602,
    XBAR_FLB_MUX03_ADCCEVT2                = 0x0603,
    XBAR_FLB_MUX04_COMP3_CTRIPH           = 0x0800,
    XBAR_FLB_MUX04_COMP3_CTRIPH_OR_L      = 0x0801,
    XBAR_FLB_MUX04_ADCAEVT3                = 0x0802,
    XBAR_FLB_MUX04_CAP3_OUT               = 0x0803,
    XBAR_FLB_MUX05_COMP3_CTRIPL           = 0x0A00,
    XBAR_FLB_MUX05_INPUTXBAR3              = 0x0A01,
    XBAR_FLB_MUX05_FLB2_OUT4               = 0x0A02,
    XBAR_FLB_MUX05_ADCCEVT3                = 0x0A03,
    XBAR_FLB_MUX06_COMP4_CTRIPH           = 0x0C00,
    XBAR_FLB_MUX06_COMP4_CTRIPH_OR_L      = 0x0C01,
    XBAR_FLB_MUX06_ADCAEVT4                = 0x0C02,
    XBAR_FLB_MUX06_CAP4_OUT               = 0x0C03,
    XBAR_FLB_MUX07_COMP4_CTRIPL           = 0x0E00,
    XBAR_FLB_MUX07_INPUTXBAR4              = 0x0E01,
    XBAR_FLB_MUX07_FLB2_OUT5               = 0x0E02,
    XBAR_FLB_MUX07_ADCCEVT4                = 0x0E03,
    XBAR_FLB_MUX08_COMP5_CTRIPH           = 0x1000,
    XBAR_FLB_MUX08_COMP5_CTRIPH_OR_L      = 0x1001,
    XBAR_FLB_MUX08_ADCBEVT1                = 0x1002,
    XBAR_FLB_MUX08_CAP5_OUT               = 0x1003,
    XBAR_FLB_MUX09_COMP5_CTRIPL           = 0x1200,
    XBAR_FLB_MUX09_INPUTXBAR5              = 0x1201,
    XBAR_FLB_MUX09_FLB3_OUT4               = 0x1202,
    XBAR_FLB_MUX10_COMP6_CTRIPH           = 0x1400,
    XBAR_FLB_MUX10_COMP6_CTRIPH_OR_L      = 0x1401,
    XBAR_FLB_MUX10_ADCBEVT2                = 0x1402,
    XBAR_FLB_MUX10_CAP6_OUT               = 0x1403,
    XBAR_FLB_MUX11_COMP6_CTRIPL           = 0x1600,
    XBAR_FLB_MUX11_INPUTXBAR6              = 0x1601,
    XBAR_FLB_MUX11_FLB3_OUT5               = 0x1602,
    XBAR_FLB_MUX12_COMP7_CTRIPH           = 0x1800,
    XBAR_FLB_MUX12_COMP7_CTRIPH_OR_L      = 0x1801,
    XBAR_FLB_MUX12_ADCBEVT3                = 0x1802,
    XBAR_FLB_MUX12_CAP7_OUT               = 0x1803,
    XBAR_FLB_MUX13_COMP7_CTRIPL           = 0x1A00,
    XBAR_FLB_MUX13_ADCSOCA                 = 0x1A01,
    XBAR_FLB_MUX13_FLB4_OUT4               = 0x1A02,
    XBAR_FLB_MUX14_ADCBEVT4                = 0x1C02,
    XBAR_FLB_MUX14_EXTSYNCOUT              = 0x1C03,
    XBAR_FLB_MUX15_ADCSOCB                 = 0x1E01,
    XBAR_FLB_MUX15_FLB4_OUT5               = 0x1E02,
    XBAR_FLB_MUX16_SD1FLT1_COMPH           = 0x2000,
    XBAR_FLB_MUX16_SD1FLT1_COMPH_OR_COMPL  = 0x2001,
    XBAR_FLB_MUX16_SD1FLT1_COMPZ           = 0x2002,
    XBAR_FLB_MUX16_SD1FLT1_DRINT           = 0x2003,
    XBAR_FLB_MUX17_SD1FLT1_COMPL           = 0x2200,
    XBAR_FLB_MUX17_INPUTXBAR7              = 0x2201,
    XBAR_FLB_MUX18_SD1FLT2_COMPH           = 0x2400,
    XBAR_FLB_MUX18_SD1FLT2_COMPH_OR_COMPL  = 0x2401,
    XBAR_FLB_MUX18_SD1FLT2_COMPZ           = 0x2402,
    XBAR_FLB_MUX18_SD1FLT2_DRINT           = 0x2403,
    XBAR_FLB_MUX19_SD1FLT2_COMPL           = 0x2600,
    XBAR_FLB_MUX19_INPUTXBAR8              = 0x2601,
    XBAR_FLB_MUX20_SD1FLT3_COMPH           = 0x2800,
    XBAR_FLB_MUX20_SD1FLT3_COMPH_OR_COMPL  = 0x2801,
    XBAR_FLB_MUX20_SD1FLT3_COMPZ           = 0x2802,
    XBAR_FLB_MUX20_SD1FLT3_DRINT           = 0x2803,
    XBAR_FLB_MUX21_SD1FLT3_COMPL           = 0x2A00,
    XBAR_FLB_MUX21_INPUTXBAR9              = 0x2A01,
    XBAR_FLB_MUX22_SD1FLT4_COMPH           = 0x2C00,
    XBAR_FLB_MUX22_SD1FLT4_COMPH_OR_COMPL  = 0x2C01,
    XBAR_FLB_MUX22_SD1FLT4_COMPZ           = 0x2C02,
    XBAR_FLB_MUX22_SD1FLT4_DRINT           = 0x2C03,
    XBAR_FLB_MUX23_SD1FLT4_COMPL           = 0x2E00,
    XBAR_FLB_MUX23_INPUTXBAR10             = 0x2E01,
    XBAR_FLB_MUX25_INPUTXBAR11             = 0x3201,
    XBAR_FLB_MUX27_INPUTXBAR12             = 0x3601,
    XBAR_FLB_MUX29_INPUTXBAR13             = 0x3A01,
    XBAR_FLB_MUX31_INPUTXBAR14             = 0x3E01
} XBAR_FLBMuxConfig;

//*****************************************************************************
//
//! The following values define the \e inputFlag parameter for
//! XBAR_getInputFlagStatus() and XBAR_clearInputFlag().
//
//*****************************************************************************
typedef enum
{
    //
    // XBARFLG1
    //
    XBAR_INPUT_FLG_COMP1_CTRIPL    = 0x0000,
    XBAR_INPUT_FLG_COMP1_CTRIPH    = 0x0001,
    XBAR_INPUT_FLG_COMP2_CTRIPL    = 0x0002,
    XBAR_INPUT_FLG_COMP2_CTRIPH    = 0x0003,
    XBAR_INPUT_FLG_COMP3_CTRIPL    = 0x0004,
    XBAR_INPUT_FLG_COMP3_CTRIPH    = 0x0005,
    XBAR_INPUT_FLG_COMP4_CTRIPL    = 0x0006,
    XBAR_INPUT_FLG_COMP4_CTRIPH    = 0x0007,
    XBAR_INPUT_FLG_COMP5_CTRIPL    = 0x0008,
    XBAR_INPUT_FLG_COMP5_CTRIPH    = 0x0009,
    XBAR_INPUT_FLG_COMP6_CTRIPL    = 0x000A,
    XBAR_INPUT_FLG_COMP6_CTRIPH    = 0x000B,
    XBAR_INPUT_FLG_COMP7_CTRIPL    = 0x000C,
    XBAR_INPUT_FLG_COMP7_CTRIPH    = 0x000D,
    XBAR_INPUT_FLG_COMP1_CTRIPOUTL = 0x0010,
    XBAR_INPUT_FLG_COMP1_CTRIPOUTH = 0x0011,
    XBAR_INPUT_FLG_COMP2_CTRIPOUTL = 0x0012,
    XBAR_INPUT_FLG_COMP2_CTRIPOUTH = 0x0013,
    XBAR_INPUT_FLG_COMP3_CTRIPOUTL = 0x0014,
    XBAR_INPUT_FLG_COMP3_CTRIPOUTH = 0x0015,
    XBAR_INPUT_FLG_COMP4_CTRIPOUTL = 0x0016,
    XBAR_INPUT_FLG_COMP4_CTRIPOUTH = 0x0017,
    XBAR_INPUT_FLG_COMP5_CTRIPOUTL = 0x0018,
    XBAR_INPUT_FLG_COMP5_CTRIPOUTH = 0x0019,
    XBAR_INPUT_FLG_COMP6_CTRIPOUTL = 0x001A,
    XBAR_INPUT_FLG_COMP6_CTRIPOUTH = 0x001B,
    XBAR_INPUT_FLG_COMP7_CTRIPOUTL = 0x001C,
    XBAR_INPUT_FLG_COMP7_CTRIPOUTH = 0x001D,
    //
    // XBARFLG2
    //
    XBAR_INPUT_FLG_INPUT1           = 0x0100,
    XBAR_INPUT_FLG_INPUT2           = 0x0101,
    XBAR_INPUT_FLG_INPUT3           = 0x0102,
    XBAR_INPUT_FLG_INPUT4           = 0x0103,
    XBAR_INPUT_FLG_INPUT5           = 0x0104,
    XBAR_INPUT_FLG_INPUT6           = 0x0105,
    XBAR_INPUT_FLG_ADCSOCA          = 0x0106,
    XBAR_INPUT_FLG_ADCSOCB          = 0x0107,
    XBAR_INPUT_FLG_INPUT7           = 0x0108,
    XBAR_INPUT_FLG_INPUT8           = 0x0109,
    XBAR_INPUT_FLG_INPUT9           = 0x010A,
    XBAR_INPUT_FLG_INPUT10          = 0x010B,
    XBAR_INPUT_FLG_INPUT11          = 0x010C,
    XBAR_INPUT_FLG_INPUT12          = 0x010D,
    XBAR_INPUT_FLG_INPUT13          = 0x010E,
    XBAR_INPUT_FLG_INPUT14          = 0x010F,
    XBAR_INPUT_FLG_CAP1_OUT        = 0x0110,
    XBAR_INPUT_FLG_CAP2_OUT        = 0x0111,
    XBAR_INPUT_FLG_CAP3_OUT        = 0x0112,
    XBAR_INPUT_FLG_CAP4_OUT        = 0x0113,
    XBAR_INPUT_FLG_CAP5_OUT        = 0x0114,
    XBAR_INPUT_FLG_CAP6_OUT        = 0x0115,
    XBAR_INPUT_FLG_EXTSYNCOUT       = 0x0116,
    XBAR_INPUT_FLG_ADCAEVT1         = 0x0117,
    XBAR_INPUT_FLG_ADCAEVT2         = 0x0118,
    XBAR_INPUT_FLG_ADCAEVT3         = 0x0119,
    XBAR_INPUT_FLG_ADCAEVT4         = 0x011A,
    XBAR_INPUT_FLG_ADCBEVT1         = 0x011B,
    XBAR_INPUT_FLG_ADCBEVT2         = 0x011C,
    XBAR_INPUT_FLG_ADCBEVT3         = 0x011D,
    XBAR_INPUT_FLG_ADCBEVT4         = 0x011E,
    XBAR_INPUT_FLG_ADCCEVT1         = 0x011F,
    //
    // XBARFLG3
    //
    XBAR_INPUT_FLG_ADCCEVT2         = 0x0200,
    XBAR_INPUT_FLG_ADCCEVT3         = 0x0201,
    XBAR_INPUT_FLG_ADCCEVT4         = 0x0202,
    XBAR_INPUT_FLG_ADCDEVT1         = 0x0203,
    XBAR_INPUT_FLG_ADCDEVT2         = 0x0204,
    XBAR_INPUT_FLG_ADCDEVT3         = 0x0205,
    XBAR_INPUT_FLG_ADCDEVT4         = 0x0206,
    XBAR_INPUT_FLG_SD1FLT1_COMPL    = 0x0207,
    XBAR_INPUT_FLG_SD1FLT1_COMPH    = 0x0208,
    XBAR_INPUT_FLG_SD1FLT2_COMPL    = 0x0209,
    XBAR_INPUT_FLG_SD1FLT2_COMPH    = 0x020A,
    XBAR_INPUT_FLG_SD1FLT3_COMPL    = 0x020B,
    XBAR_INPUT_FLG_SD1FLT3_COMPH    = 0x020C,
    XBAR_INPUT_FLG_SD1FLT4_COMPL    = 0x020D,
    XBAR_INPUT_FLG_SD1FLT4_COMPH    = 0x020E,
    XBAR_INPUT_FLG_CAP7_OUT        = 0x0217,
    XBAR_INPUT_FLG_SD1FLT1_COMPZ    = 0x0218,
    XBAR_INPUT_FLG_SD1FLT1_DRINT    = 0x0219,
    XBAR_INPUT_FLG_SD1FLT2_COMPZ    = 0x021A,
    XBAR_INPUT_FLG_SD1FLT2_DRINT    = 0x021B,
    XBAR_INPUT_FLG_SD1FLT3_COMPZ    = 0x021C,
    XBAR_INPUT_FLG_SD1FLT3_DRINT    = 0x021D,
    XBAR_INPUT_FLG_SD1FLT4_COMPZ    = 0x021E,
    XBAR_INPUT_FLG_SD1FLT4_DRINT    = 0x021F,
    //
    // XBARFLG4
    //
    XBAR_INPUT_FLG_FLB1_OUT4        = 0x0310,
    XBAR_INPUT_FLG_FLB1_OUT5        = 0x0311,
    XBAR_INPUT_FLG_FLB2_OUT4        = 0x0312,
    XBAR_INPUT_FLG_FLB2_OUT5        = 0x0313,
    XBAR_INPUT_FLG_FLB3_OUT4        = 0x0314,
    XBAR_INPUT_FLG_FLB3_OUT5        = 0x0315,
    XBAR_INPUT_FLG_FLB4_OUT4        = 0x0316,
    XBAR_INPUT_FLG_FLB4_OUT5        = 0x0317,
} XBAR_InputFlag;
#endif

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Enables the Output X-BAR mux values to be passed to the output signal.
//!
//! \param output is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be enabled.
//!
//! This function enables the mux values to be passed to the X-BAR output
//! signal. The \e output parameter is a value \b XBAR_OUTPUTy where y is
//! the output number between 1 and 8 inclusive.
//!
//! The \e muxes parameter is a bit field of the muxes being enabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be OR'd together to enable several
//! muxes on an output at the same time. For example, passing this function
//! ( \b XBAR_MUX04 | \b XBAR_MUX10 ) would enable muxes 4 and 10.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_enableOutputMux(XBAR_OutputNum output, uint32_t muxes)
{
    //
    // Set the enable bit.
    //
    WRPRT_DISABLE;

    HWREG(XBAR_OUTPUT_EN_REG_BASE + (uint16_t)output * 2) |= muxes;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables the Output X-BAR mux values from being passed to the output.
//!
//! \param output is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be disabled.
//!
//! This function disables the mux values from being passed to the X-BAR output
//! signal. The \e output parameter is a value \b XBAR_OUTPUTy where y is
//! the output number between 1 and 8 inclusive.
//!
//! The \e muxes parameter is a bit field of the muxes being disabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be OR'd together to disable several
//! muxes on an output at the same time. For example, passing this function
//! ( \b XBAR_MUX04 | \b XBAR_MUX10 ) would disable muxes 4 and 10.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_disableOutputMux(XBAR_OutputNum output, uint32_t muxes)
{
    //
    // Clear the enable bit.
    //
    WRPRT_DISABLE;

    HWREG(XBAR_OUTPUT_EN_REG_BASE + (uint16_t)output * 2) &= ~(muxes);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables or disables the output latch to drive the selected output.
//!
//! \param output is the X-BAR output being configured.
//! \param enable is a flag that determines whether or not the latch is
//! selected to drive the X-BAR output.
//!
//! This function sets the Output X-BAR output signal latch mode. If the
//! \e enable parameter is \b true, the output specified by \e output will be
//! driven by the output latch.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_setOutputLatchMode(XBAR_OutputNum output, bool enable)
{
    WRPRT_DISABLE;

    //
    // Set or clear the latch setting bit based on the enable parameter.
    //
    if(enable)
    {
        HWREGH(OUTPUTXBAR_BASE + XBAR_O_OUTPUTLATCHENABLE) |=
            0x1U << ((uint16_t)output / 2U);
    }
    else
    {
        HWREGH(OUTPUTXBAR_BASE + XBAR_O_OUTPUTLATCHENABLE) &=
            ~(0x1U << ((uint16_t)output / 2U));
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Returns the status of the output latch
//!
//! \param output is the X-BAR output being checked.
//!
//! \return Returns \b true if the output corresponding to \e output was
//! triggered. If not, it will return \b false.
//
//*****************************************************************************
static inline bool
XBAR_getOutputLatchStatus(XBAR_OutputNum output)
{
    //
    // Get the status of the Output X-BAR output latch.
    //
    return((HWREGH(OUTPUTXBAR_BASE + XBAR_O_OUTPUTLATCH) &
            (0x1U << ((uint16_t)output / 2U))) != 0U);
}

//*****************************************************************************
//
//! Clears the output latch for the specified output.
//!
//! \param output is the X-BAR output being configured.
//!
//! This function clears the Output X-BAR output latch. The output to be
//! configured is specified by the \e output parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_clearOutputLatch(XBAR_OutputNum output)
{
    //
    // Set the bit that clears the corresponding OUTPUTLATCH bit.
    //
    HWREGH(OUTPUTXBAR_BASE + XBAR_O_OUTPUTLATCHCLR) |=
        0x1U << ((uint16_t)output / 2U);
}

//*****************************************************************************
//
//! Forces the output latch for the specified output.
//!
//! \param output is the X-BAR output being configured.
//!
//! This function forces the Output X-BAR output latch. The output to be
//! configured is specified by the \e output parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_forceOutputLatch(XBAR_OutputNum output)
{
    //
    // Set the bit that forces the corresponding OUTPUTLATCH bit.
    //
    HWREGH(OUTPUTXBAR_BASE + XBAR_O_OUTPUTLATCHFRC) =
        (uint16_t)0x1U << ((uint16_t)output / 2U);
}

//*****************************************************************************
//
//! Configures the polarity of an Output X-BAR output.
//!
//! \param output is the X-BAR output being configured.
//! \param invert is a flag that determines whether the output is active-high
//! or active-low.
//!
//! This function inverts the Output X-BAR signal if the \e invert parameter is
//! \b true. If \e invert is \b false, the signal will be passed as is. The
//! \e output parameter is a value \b XBAR_OUTPUTy where y is the output
//! number between 1 and 8 inclusive.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_invertOutputSignal(XBAR_OutputNum output, bool invert)
{
    //
    // Set or clear the polarity setting bit based on the invert parameter.
    //
    WRPRT_DISABLE;

    if(invert)
    {
        HWREGH(OUTPUTXBAR_BASE + XBAR_O_OUTPUTINV) |=
            0x1U << ((uint16_t)output / 2U);
    }
    else
    {
        HWREGH(OUTPUTXBAR_BASE + XBAR_O_OUTPUTINV) &=
            ~(0x1U << ((uint16_t)output / 2U));
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables the PWM X-BAR mux values to be passed to an PWM module.
//!
//! \param trip is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be enabled.
//!
//! This function enables the mux values to be passed to the X-BAR trip
//! signal. The \e trip parameter is a value \b XBAR_TRIPy where y is
//! the number of the trip signal on the PWM.
//!
//! The \e muxes parameter is a bit field of the muxes being enabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be logically OR'd together to
//! enable several muxes on an output at the same time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_enablePWMMux(XBAR_TripNum trip, uint32_t muxes)
{
    //
    // Set the enable bit.
    //
    WRPRT_DISABLE;

    HWREG(XBAR_PWM_EN_REG_BASE + (uint32_t)trip * 2) |= muxes;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables the PWM X-BAR mux values to be passed to an PWM module.
//!
//! \param trip is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be disabled.
//!
//! This function disables the mux values to be passed to the X-BAR trip
//! signal. The \e trip parameter is a value \b XBAR_TRIPy where y is
//! the number of the trip signal on the PWM.
//!
//! The \e muxes parameter is a bit field of the muxes being disabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be logically OR'd together to
//! disable several muxes on an output at the same time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_disablePWMMux(XBAR_TripNum trip, uint32_t muxes)
{
    //
    // Clear the enable bit.
    //
    WRPRT_DISABLE;

    HWREG(XBAR_PWM_EN_REG_BASE + (uint32_t)trip * 2) &= ~(muxes);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Configures the polarity of an PWM X-BAR output.
//!
//! \param trip is the X-BAR output being configured.
//! \param invert is a flag that determines whether the output is active-high
//! or active-low.
//!
//! This function inverts the PWM X-BAR trip signal if the \e invert
//! parameter is \b true. If \e invert is \b false, the signal will be passed
//! as is. The \e trip parameter is a value \b XBAR_TRIPy where y is
//! the number of the trip signal on the PWM X-BAR that is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_invertPWMSignal(XBAR_TripNum trip, bool invert)
{
    //
    // Set or clear the polarity setting bit based on the invert parameter.
    //
    WRPRT_DISABLE;

    if(invert)
    {
        HWREGH(PWMXBAR_BASE + XBAR_O_TRIPOUTINV) |=
            0x1U << ((uint16_t)trip / 2U);
    }
    else
    {
        HWREGH(PWMXBAR_BASE + XBAR_O_TRIPOUTINV) &=
            ~(0x1U << ((uint16_t)trip / 2U));
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the GPIO / non-GPIO pin for an Input X-BAR input.
//!
//! \param input is the X-BAR input being configured.
//! \param pin is the identifying number of the pin.
//!
//! This function configures which GPIO is assigned to an Input X-BAR input.
//! The \e input parameter is a value in the form of a define \b XBAR_INPUTy
//! where y is a the input number for the Input X-BAR.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! For the other non - GPIO values:
//! 0xFFFD: '1' will be driven to the destination
//! 0xFFFE: '1' will be driven to the destination
//! 0xFFFF: '0' will be driven to the destination
//! NOTE: Pin value greater than the available number of GPIO pins on a
//! device (except 0xFFFF) will cause the destination to be driven '1'.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_setInputPin(XBAR_InputNum input, uint16_t pin)
{
    //
    // Check the argument.
    //
    // The range of pin values: (0 <= pin <= 59) || (0xFFFD <= pin <= 0xFFFF) || (224 <= pin <= 247)
    //
    ASSERT((pin <= XBAR_GPIO_MAX_CNT) ||
          (pin >= XBAR_NON_GPIO_MIN_CNT) ||
          ((pin >= XBAR_GPIO_AIO_MIN_CNT) && (pin <= XBAR_GPIO_AIO_MAX_CNT)));

    //
    // Write the requested pin to the appropriate input select register.
    //
    WRPRT_DISABLE;

    HWREGH(XBAR_INPUT_BASE + (uint16_t)input * 2) = pin;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks an input to the Input X-BAR.
//!
//! \param input is an input to the Input X-BAR.
//!
//! This function locks the specific input on the Input X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_lockInput(XBAR_InputNum input)
{
    //
    // lock the input in the INPUTSELECTLOCK register.
    //
    WRPRT_DISABLE;
    HWREG(INPUTXBAR_BASE + XBAR_O_INPUTSELECTLOCK) =
        (uint32_t)1U << (uint16_t)input;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks the Output X-BAR.
//!
//! This function locks the Output X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_lockOutput(void)
{
    //
    // Lock the Output X-BAR with the OUTPUTLOCK register.
    // Write key 0x5A5A to the KEY bits and 1 to LOCK bit.
    //
    WRPRT_DISABLE;

    HWREG(OUTPUTXBAR_BASE + XBAR_O_OUTPUTLOCK) =
        ((uint32_t)0x5A5A << XBAR_OUTPUTLOCK_KEY_S) |
        (uint32_t)XBAR_OUTPUTLOCK_KEY_M;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks the PWM X-BAR.
//!
//! This function locks the PWM X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_lockPWM(void)
{
    //
    // Lock the PWM X-BAR with the TRIPLOCK register.
    // Write key 0x5A5A to the KEY bits and 1 to LOCK bit.
    //
    WRPRT_DISABLE;

    HWREG(PWMXBAR_BASE + XBAR_O_TRIPLOCK) =
        ((uint32_t)0x5A5A << XBAR_TRIPLOCK_KEY_S) |
        (uint32_t)XBAR_TRIPLOCK_KEY_M;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables the FLB X-BAR mux values to be passed to an FLB module.
//!
//! \param auxSignal is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be enabled.
//!
//! This function enables the mux values to be passed to the X-BAR auxSignal
//! signal. The \e auxSignal parameter is a value \b XBAR_AUXSIGy where y is
//! the number of the signal on the FLB.
//!
//! The \e muxes parameter is a bit field of the muxes being enabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be logically OR'd together to
//! enable several muxes on an output at the same time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_enableFLBMux(XBAR_AuxSigNum auxSignal, uint32_t muxes)
{
    //
    // Set the enable bit.
    //
    WRPRT_DISABLE;

    HWREG(XBAR_FLB_EN_REG_BASE + (uint32_t)(auxSignal * 2)) |= muxes;


    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables the FLB X-BAR mux values to be passed to an FLB module.
//!
//! \param auxSignal is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be disabled.
//!
//! This function disables the mux values to be passed to the X-BAR auxSignal
//! signal. The \e auxSignal parameter is a value \b XBAR_AUXSIGy where y is
//! the number of the signal on the FLB.
//!
//! The \e muxes parameter is a bit field of the muxes being disabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be logically OR'd together to
//! disable several muxes on an output at the same time.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_disableFLBMux(XBAR_AuxSigNum auxSignal, uint32_t muxes)
{
    //
    // Clear the enable bit.
    //
    WRPRT_DISABLE;

    HWREG(XBAR_FLB_EN_REG_BASE + (uint32_t)(auxSignal * 2)) &= ~(muxes);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Configures the polarity of an FLB X-BAR output.
//!
//! \param auxSignal is the X-BAR output being configured.
//! \param invert is a flag that determines whether the output is active-high
//! or active-low.
//!
//! This function inverts the FLB X-BAR auxSignal signal if the \e invert
//! parameter is \b true. If \e invert is \b false, the signal will be passed
//! as is. The \e auxSignal parameter is a value \b XBAR_AUXSIGy where y is
//! the number of the signal on the FLB X-BAR that is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void
XBAR_invertFLBSignal(XBAR_AuxSigNum auxSignal, bool invert)
{
    //
    // Set or clear the polarity setting bit based on the invert parameter.
    //
    WRPRT_DISABLE;

    if(invert)
    {
        HWREGH(FLBXBAR_BASE + XBAR_O_AUXSIGOUTINV) |=
            0x1U << ((uint16_t)auxSignal / 2U);
    }
    else
    {
        HWREGH(FLBXBAR_BASE + XBAR_O_AUXSIGOUTINV) &=
            ~(0x1U << ((uint16_t)auxSignal / 2U));
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Configures the Output X-BAR mux that determines the signals passed to an
//! output.
//!
//! \param output is the X-BAR output being configured.
//! \param muxConfig is mux configuration that specifies the signal.
//!
//! This function configures an Output X-BAR mux. This determines which
//! signal(s) should be passed through the X-BAR to a GPIO. The \e output
//! parameter is a value \b XBAR_OUTPUTy where y is a the output number
//! between 1 and 8 inclusive.
//!
//! The \e muxConfig parameter for OUTPUT XBAR is the mux configuration
//! value that specifies which signal will be passed from the mux. The
//! values have the format of \b XBAR_OUT_MUXnn_xx where the 'xx' is
//! the signal and nn is the mux number.
//!
//! This function may be called for each mux of an output and their values will
//! be logically OR'd before being passed to the output signal. This means that
//! this function may be called, for example, with the argument
//! \b XBAR_OUT_MUX00_CAP1_OUT and then with the argument
//! \b XBAR_OUT_MUX01_INPUTXBAR1, resulting in the values of MUX00 and MUX01
//! being logically OR'd if both are enabled. Calling the function twice for
//! the same mux on the output will result in the configuration in the second
//! call overwriting the first.
//!
//! \return None.
//
//*****************************************************************************
extern void
XBAR_setOutputMuxConfig(XBAR_OutputNum output, XBAR_OutputMuxConfig muxConfig);

//*****************************************************************************
//
//! Configures the PWM X-BAR mux that determines the signals passed to an
//! PWM module.
//!
//! \param trip is the X-BAR output being configured.
//! \param muxConfig is mux configuration that specifies the signal.
//!
//! This function configures an PWM X-BAR mux. This determines which signal(s)
//! should be passed through the X-BAR to an PWM module. The \e trip
//! parameter is a value \b XBAR_TRIPy where y is a the number of the trip
//! signal on the PWM.
//!
//! The \e muxConfig parameter is the mux configuration value that specifies
//! which signal will be passed from the mux. The values have the format of
//! \b XBAR_PWM_MUXnn_xx where the 'xx' is the signal and nn is the mux
//! number (0 through 31). The possible values are found in <tt>xbar.h</tt>
//!
//! This function may be called for each mux of an output and their values will
//! be logically OR'd before being passed to the trip signal. This means that
//! this function may be called, for example, with the argument
//! \b XBAR_PWM_MUX00_CAP1_OUT and then with the argument
//! \b XBAR_PWM_MUX01_INPUTXBAR1, resulting in the values of MUX00 and MUX03
//! being logically OR'd if both are enabled. Calling the function twice for
//! the same mux on the output will result in the configuration in the second
//! call overwriting the first.
//!
//! \return None.
//
//*****************************************************************************
extern void
XBAR_setPWMMuxConfig(XBAR_TripNum trip, XBAR_PWMMuxConfig muxConfig);

//*****************************************************************************
//
//! Returns the status of the input latch.
//!
//! \param inputFlag is the X-BAR input latch being checked. Values are in the
//! format of /b XBAR_INPUT_FLG_XXXX where "XXXX" is name of the signal.
//!
//! \return Returns \b true if the X-BAR input corresponding to the
//! \e inputFlag has been triggered. If not, it will return \b false.
//
//*****************************************************************************
extern bool
XBAR_getInputFlagStatus(XBAR_InputFlag inputFlag);

//*****************************************************************************
//
//! Clears the input latch for the specified input latch.
//!
//! \param inputFlag is the X-BAR input latch being cleared.
//!
//! This function clears the Input X-BAR input latch. The input latch to be
//! cleared is specified by the \e inputFlag parameter.
//!
//! \return None.
//
//*****************************************************************************
extern void
XBAR_clearInputFlag(XBAR_InputFlag inputFlag);

//*****************************************************************************
//
//! Configures the FLB X-BAR mux that determines the signals passed to a
//! FLB module.
//!
//! \param auxSignal is the X-BAR output being configured.
//! \param muxConfig is mux configuration that specifies the signal.
//!
//! This function configures an FLB X-BAR mux. This determines which signal(s)
//! should be passed through the X-BAR to an FLB module. The \e auxSignal
//! parameter is a value \b XBAR_AUXSIGy where y is a the number of the
//! signal on the FLB.
//!
//! The \e muxConfig parameter is the mux configuration value that specifies
//! which signal will be passed from the mux. The values have the format of
//! \b XBAR_FLB_MUXnn_xx where the 'xx' is the signal and nn is the mux
//! number (0 through 31). The possible values are found in <tt>xbar.h</tt>
//!
//! This function may be called for each mux of an output and their values will
//! be logically OR'd before being passed to the signal. This means that
//! this function may be called, for example, with the argument
//! \b XBAR_FLB_MUX00_CAP1_OUT and then with the argument
//! \b XBAR_FLB_MUX03_INPUTXBAR2, resulting in the values of MUX00 and MUX03
//! being logically OR'd if both are enabled. Calling the function twice for
//! the same mux on the output will result in the configuration in the second
//! call overwriting the first.
//!
//! \return None.
//
//*****************************************************************************
extern void XBAR_setFLBMuxConfig(XBAR_AuxSigNum auxSignal,
                                 XBAR_FLBMuxConfig muxConfig);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // XBAR_H
