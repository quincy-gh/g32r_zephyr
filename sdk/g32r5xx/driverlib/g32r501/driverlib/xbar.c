//###########################################################################
//
// FILE:    xbar.c
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
// 1. Macro definition, function naming
//
//###########################################################################

#include "xbar.h"

//*****************************************************************************
//
// XBAR_setOutputMuxConfig
//
//*****************************************************************************
void
XBAR_setOutputMuxConfig(XBAR_OutputNum output, XBAR_OutputMuxConfig muxConfig)
{
    uint32_t shift;
    uint16_t offset;

    //
    // If the configuration is for MUX16-31, we'll need an odd value to index
    // into the config registers.
    
    if(((uint32_t)muxConfig & 0x2000U) != 0U)
    {
        offset = ((uint16_t)output << 2U) + 4U;
    }
    else
    {
        offset = (uint16_t)output << 2U;
    }

    //
    // Extract the shift from the input value.
    //
    shift = ((uint32_t)muxConfig >> 8U) & 0x1FU;

    //
    // Write the requested muxing value for this XBAR output.
    //
    WRPRT_DISABLE;

    HWREG(XBAR_OUTPUT_CFG_REG_BASE + offset) =
        (HWREG(XBAR_OUTPUT_CFG_REG_BASE + offset) &
         ~((uint32_t)0x3U << shift)) |
        (((uint32_t)muxConfig & 0x3U) << shift);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// XBAR_setPWMMuxConfig
//
//*****************************************************************************
void
XBAR_setPWMMuxConfig(XBAR_TripNum trip, XBAR_PWMMuxConfig muxConfig)
{
    uint32_t shift;
    uint16_t offset;

    //
    // If the configuration is for MUX16-31, we'll need an odd value to index
    // into the config registers.
    
    if(((uint32_t)muxConfig & 0x2000U) != 0U)
    {
        offset = ((uint16_t)trip << 2U) + 4U;
    }
    else
    {
        offset = (uint16_t)trip << 2U;
    }

    //
    // Extract the shift from the input value.
    //
    shift = ((uint32_t)muxConfig >> 8U) & 0x1FU;

    //
    // Write the requested muxing value for this XBAR trip.
    //
    WRPRT_DISABLE;

    HWREG(XBAR_PWM_CFG_REG_BASE + (uint32_t)offset) =
        (HWREG(XBAR_PWM_CFG_REG_BASE + (uint32_t)offset) & ~((uint32_t)0x3U << shift)) |
        (((uint32_t)muxConfig & 0x3U) << shift);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// XBAR_setFLBMuxConfig
//
//*****************************************************************************
void
XBAR_setFLBMuxConfig(XBAR_AuxSigNum auxSignal, XBAR_FLBMuxConfig muxConfig)
{
    uint32_t shift;
    uint16_t offset;

    //
    // If the configuration is for MUX16-31, we'll need an odd value to index
    // into the config registers.
    
    if(((uint32_t)muxConfig & 0x2000U) != 0U)
    {
        offset = ((uint16_t)auxSignal << 2U) + 4U;
    }
    else
    {
        offset = (uint16_t)auxSignal << 2U;
    }

    //
    // Extract the shift from the input value.
    //
    shift = ((uint32_t)muxConfig >> 8U) & 0x1FU;

    //
    // Write the requested muxing value for this XBAR auxSignal.
    //
    WRPRT_DISABLE;


    HWREG(XBAR_FLB_CFG_REG_BASE + (uint32_t)offset) =
        (HWREG(XBAR_FLB_CFG_REG_BASE + (uint32_t)offset) & ~((uint32_t)0x3U << shift)) |
        (((uint32_t)muxConfig & 0x3U) << shift);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// XBAR_getInputFlagStatus
//
//*****************************************************************************
bool
XBAR_getInputFlagStatus(XBAR_InputFlag inputFlag)
{
    uint32_t offset;
    uint32_t inputMask;

    //
    // Determine flag register offset.
    //
    switch((uint16_t)inputFlag & XBAR_INPUT_FLG_REG_M)
    {
        case XBAR_INPUT_FLG_REG_1:
            offset = XBAR_O_FLG1;
            break;

        case XBAR_INPUT_FLG_REG_2:
            offset = XBAR_O_FLG2;
            break;

        case XBAR_INPUT_FLG_REG_3:
            offset = XBAR_O_FLG3;
            break;

        case XBAR_INPUT_FLG_REG_4:
            offset = XBAR_O_FLG4;
            break;

        default:
            //
            // This should never happen if a valid inputFlag value is used.
            //
            offset = 0U;
            break;
    }

    //
    // Get the status of the X-BAR input latch.
    //
    inputMask = (uint32_t)1U << ((uint32_t)inputFlag & XBAR_INPUT_FLG_INPUT_M);

    return((HWREG(XBAR_BASE + offset) & inputMask) != 0U);
}

//*****************************************************************************
//
// XBAR_clearInputFlag
//
//*****************************************************************************
void
XBAR_clearInputFlag(XBAR_InputFlag inputFlag)
{
    uint32_t offset;
    uint32_t inputMask;

    //
    // Determine flag clear register offset.
    //
    switch((uint16_t)inputFlag & XBAR_INPUT_FLG_REG_M)
    {
        case XBAR_INPUT_FLG_REG_1:
            offset = XBAR_O_CLR1;
            break;

        case XBAR_INPUT_FLG_REG_2:
            offset = XBAR_O_CLR2;
            break;

        case XBAR_INPUT_FLG_REG_3:
            offset = XBAR_O_CLR3;
            break;

        case XBAR_INPUT_FLG_REG_4:
            offset = XBAR_O_CLR4;
            break;

        default:
            //
            // This should never happen if a valid inputFlag value is used.
            //
            offset = 0U;
            break;
    }

    //
    // Set the bit that clears the X-BAR input latch.
    //
    inputMask = (uint32_t)1U << ((uint32_t)inputFlag & XBAR_INPUT_FLG_INPUT_M);
    HWREG(XBAR_BASE + offset) = inputMask;
}
