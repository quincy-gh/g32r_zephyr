//###########################################################################
//
// FILE:    comp.c
//
// TITLE:   G32R502 COMP driver.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
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
// - 2026-06-30:
// 1. Module naming, macro definition, register naming, and some function naming.
//
//###########################################################################

#include "comp.h"

//*****************************************************************************
//
// COMP_configFilterHigh
//
//*****************************************************************************
void
COMP_configFilterHigh(uint32_t base, uint16_t samplePrescale,
                       uint16_t sampleWindow, uint16_t threshold)
{
    uint16_t regValue;

    //
    // Check the arguments.
    //
    ASSERT(COMP_isBaseValid(base));
    ASSERT(samplePrescale <= 1023U);
    ASSERT((sampleWindow >= 1U) && (sampleWindow <= 32U));
    ASSERT((threshold - 1U) >= ((sampleWindow - 1U) / 2U));

    //
    // Shift the sample window and threshold values into the correct positions
    // and write them to the appropriate register.
    //
    regValue = ((sampleWindow - 1U) << COMP_CTRIPHFILCTL_SAMPWIN_S) |
               ((threshold - 1U) << COMP_CTRIPHFILCTL_THRESH_S);

    WRPRT_DISABLE;

    HWREGH(base + COMP_O_CTRIPHFILCTL) =
        (HWREGH(base + COMP_O_CTRIPHFILCTL) &
         ~(COMP_CTRIPHFILCTL_SAMPWIN_M | COMP_CTRIPHFILCTL_THRESH_M)) |
        regValue;

    //
    // Set the filter sample clock prescale for the high COMParator.
    //
    HWREGH(base + COMP_O_CTRIPHFILCLKCTL) = samplePrescale;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// COMP_configFilterLow
//
//*****************************************************************************
void
COMP_configFilterLow(uint32_t base, uint16_t samplePrescale,
                      uint16_t sampleWindow, uint16_t threshold)
{
    uint16_t regValue;

    //
    // Check the arguments.
    //
    ASSERT(COMP_isBaseValid(base));
    ASSERT(samplePrescale <= 1023U);
    ASSERT((sampleWindow >= 1U) && (sampleWindow <= 32U));
    ASSERT((threshold - 1U) >= ((sampleWindow - 1U) / 2U));

    //
    // Shift the sample window and threshold values into the correct positions
    // and write them to the appropriate register.
    //
    regValue = ((sampleWindow - 1U) << COMP_CTRIPLFILCTL_SAMPWIN_S) |
               ((threshold - 1U) << COMP_CTRIPLFILCTL_THRESH_S);

    WRPRT_DISABLE;

    HWREGH(base + COMP_O_CTRIPLFILCTL) =
        (HWREGH(base + COMP_O_CTRIPLFILCTL) &
         ~(COMP_CTRIPLFILCTL_SAMPWIN_M | COMP_CTRIPLFILCTL_THRESH_M)) |
        regValue;

    //
    // Set the filter sample clock prescale for the low COMParator.
    //
    HWREGH(base + COMP_O_CTRIPLFILCLKCTL) = samplePrescale;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// COMP_configLatchOnPWMSYNC
//
//*****************************************************************************
void
COMP_configLatchOnPWMSYNC(uint32_t base, bool highEnable, bool lowEnable)
{
    //
    // Check the arguments.
    //
    ASSERT(COMP_isBaseValid(base));

    //
    // If the highEnable is true, set the bit that will enable PWMSYNC to reset
    // the high COMParator digital filter latch. If not, clear the bit.
    //
    WRPRT_DISABLE;

    if(highEnable)
    {
        HWREGH(base + COMP_O_COMPSTSCLR) |= COMP_COMPSTSCLR_HSYNCCLREN;
    }
    else
    {
        HWREGH(base + COMP_O_COMPSTSCLR) &= ~COMP_COMPSTSCLR_HSYNCCLREN;
    }

    //
    // If the lowEnable is true, set the bit that will enable PWMSYNC to reset
    // the low COMParator digital filter latch. If not, clear the bit.
    //
    if(lowEnable)
    {
        HWREGH(base + COMP_O_COMPSTSCLR) |= COMP_COMPSTSCLR_LSYNCCLREN;
    }
    else
    {
        HWREGH(base + COMP_O_COMPSTSCLR) &= ~COMP_COMPSTSCLR_LSYNCCLREN;
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// COMP_configRamp
//
//*****************************************************************************
void
COMP_configRamp(uint32_t base, uint16_t maxRampVal, uint16_t decrementVal,
                 uint16_t delayVal, uint16_t pwmSyncSrc, bool useRampValShdw)
{
    //
    // Check the arguments.
    //
    ASSERT(COMP_isBaseValid(base));
    ASSERT(delayVal <= COMP_RAMPDLYS_DELAY_M);
    ASSERT((pwmSyncSrc >= 1U) && (pwmSyncSrc <= 16U));

    WRPRT_DISABLE;

    //
    // Write the ramp generator source to the register
    //
    HWREGH(base + COMP_O_COMPDACCTL) =
        (HWREGH(base + COMP_O_COMPDACCTL) &
         ~COMP_COMPDACCTL_RAMPSOURCE_M) |
        ((uint16_t)(pwmSyncSrc - 1U) << COMP_COMPDACCTL_RAMPSOURCE_S);

    //
    // Set or clear the bit that determines from where the max ramp value
    // should be loaded.
    //
    if(useRampValShdw)
    {
        HWREGH(base + COMP_O_COMPDACCTL) |= COMP_COMPDACCTL_RAMPLOADSEL;
    }
    else
    {
        HWREGH(base + COMP_O_COMPDACCTL) &= ~COMP_COMPDACCTL_RAMPLOADSEL;
    }

    WRPRT_ENABLE;

    //
    // Write the maximum ramp value to the shadow register.
    //
    HWREGH(base + COMP_O_RAMPMAXREFS) = maxRampVal;

    //
    // Write the ramp decrement value to the shadow register.
    //
    HWREGH(base + COMP_O_RAMPDECVALS) = decrementVal;

    //
    // Write the ramp delay value to the shadow register.
    //
    HWREGH(base + COMP_O_RAMPDLYS) = delayVal;
}

