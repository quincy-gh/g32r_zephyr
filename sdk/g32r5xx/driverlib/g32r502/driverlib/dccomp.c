//###########################################################################
//
// FILE:    DCCOMP.c
//
// TITLE:   G32R502 DCCOMP driver.
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
// 1. Partial comments, module names, function names, register names,
//    and local variable data types
// 2. Deleted calls to DCC_enableErrorSignal() and DCC_enableDoneSignal()
//   in DCCOMP_measureClockFrequency() function
//
//###########################################################################

#include "dccomp.h"

//*****************************************************************************
//
// DCCOMP_getRevisionNumber
//
//*****************************************************************************
uint16_t
DCCOMP_getRevisionNumber(uint32_t base, DCCOMP_RevisionNumber identifier)
{
    uint16_t number = 0;

    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    //  Get specified revision number or scheme
    //
    if(identifier == DCCOMP_REVISION_MINOR)
    {
        number = (HWREGH(base + DCCOMP_O_DCCOMPREV) & DCCOMP_DCCOMPREV_MINOR_M);
    }
    else if(identifier == DCCOMP_REVISION_MAJOR)
    {
        number = (HWREGH(base + DCCOMP_O_DCCOMPREV) & DCCOMP_DCCOMPREV_MAJOR_M) >>
                 DCCOMP_DCCOMPREV_MAJOR_S;
    }

    return(number);
}


//*****************************************************************************
//
// DCCOMP_verifyClockFrequency
//
//*****************************************************************************
bool
DCCOMP_verifyClockFrequency(uint32_t base,
                         DCCOMP_Count1ClockSource clock1,
                         float32_t freq1,
                         DCCOMP_Count0ClockSource clock0,
                         float32_t freq0,
                         float32_t tolerance,
                         float32_t freqerr,
                         float32_t freq_sysclk)
{
    uint32_t total_error;
    uint32_t window;
    uint32_t count0;
    uint32_t valid;
    uint32_t count1;
    bool     status;

    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // If Fclk1 > Fclk0,
    //    Async. Error (In Clock0 cycles) = 2 + 2*(Fsysclk/Fclk0)
    //
    // If Fclk1 < Fclk0,
    //    Async. Error (In Clock0 cycles) = 2*(Fclk0/Fclk1) + 2*(Fsysclk/Fclk0)
    //
    if(freq1 > freq0)
    {
        total_error = (uint32_t)(2.0f + (2.0f * (freq_sysclk / freq0)));
    }
    else
    {
        total_error = (uint32_t)((2.0f * (freq0 / freq1)) +
                                 (2.0f * (freq_sysclk / freq0)));
    }

    //
    // Digitization error = 8 Clock0 cycles
    //
    total_error += 8U;

    //
    // Window (in Cycles) = (Total Error) / (0.01 * Tolerance)
    //
    window = (uint32_t)((float32_t)total_error / (0.01f * tolerance));

    //
    // Error due to variance in clock frequency =
    // window * (Allowable Frequency Tolerance (in %) / 100)
    //
    total_error += (float32_t)window * (freqerr / 100.0f);

    //
    // DCCOMP counter configuration :
    // Counter0 = Window - Total Error
    // Valid0 = 2 * Total Error
    // Counter1 = Window * (Fclk1 / Fclk0)
    //
    count0 = window - total_error;
    valid  = 2U * total_error;
    count1 = (uint32_t)(window * freq1 / freq0);

    //
    // Clear Error & Done Flag
    //
    DCCOMP_clearErrorFlag(base);
    DCCOMP_clearDoneFlag(base);

    //
    // Disable DCCOMP and the error and done signals
    //
    DCCOMP_disableModule(base);
    DCCOMP_disableErrorSignal(base);
    DCCOMP_disableDoneSignal(base);

    //
    // Configure Clock Source0 and clock source1
    //
    DCCOMP_setCounter0ClkSource(base, clock0);
    DCCOMP_setCounter1ClkSource(base, clock1);

    //
    // Configure COUNTER-0, COUNTER-1 & Valid Window
    //
    DCCOMP_setCounterSeeds(base, count0, valid, count1);

    //
    // Enable Single Shot mode
    //
    DCCOMP_enableSingleShotMode(base, DCCOMP_MODE_COUNTER_ZERO);

    //
    // Enable DCCOMP to start counting
    //
    DCCOMP_enableModule(base);

    //
    // Wait until Error or Done Flag is generated
    //
    while(!(DCCOMP_getSingleShotStatus(base) || DCCOMP_getErrorStatus(base)))
    {
    }

    //
    // Returns true if DCCOMP completes without error
    //
    if(DCCOMP_getSingleShotStatus(base))
    {
        status = true;
    }
    else
    {
        status = false;
    }

    return(status);
}

//*****************************************************************************
//
// DCCOMP_measureClockFrequency
//
//*****************************************************************************
float32_t
DCCOMP_measureClockFrequency(uint32_t base,
                          DCCOMP_Count1ClockSource clock1,
                          DCCOMP_Count0ClockSource clock0,
                          float32_t freq0,
                          float32_t tolerance,
                          float32_t freqerr,
                          float32_t freq_sysclk)
{
    uint32_t total_error;
    uint32_t window;
    uint32_t count0;
    uint32_t valid;
    uint32_t count1;
    uint32_t actual_cnt1;
    float32_t freq1;

    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Async. Error = 2 + 2*(Fsysclk/Fclk0)
    // Digitization error = 8 Clock0 cycles
    // Total DCCOMP error = Async Error + Digitization error
    //
    total_error = (uint32_t)(2.0f + (2.0f * (freq_sysclk / freq0)));
    total_error += 8U;

    //
    // Window (in Cycles) = (Total Error) / (0.01 * Tolerance)
    //
    window = (uint32_t)(total_error / (0.01f * tolerance));

    //
    // Error due to variance in clock frequency =
    // window * (Allowable Frequency Tolerance (in %) / 100)
    //
    total_error += (float32_t)window * (freqerr / 100.0f);

    //
    // DCCOMP counter configuration :
    // Counter0 = Window - Total Error
    // Valid0 = 2 * Total Error
    // Counter1 = Maximum counter value (0xFFFFF)
    //
    count0 = window - total_error;
    valid  = 2U * total_error;
    count1 = 0xFFFFFU;

    //
    // Clear Error & Done Flag
    //
    DCCOMP_clearErrorFlag(base);
    DCCOMP_clearDoneFlag(base);

    //
    // Disable DCCOMP and the error and done signals
    //
    DCCOMP_disableModule(base);
    DCCOMP_disableErrorSignal(base);
    DCCOMP_disableDoneSignal(base);

    //
    // Configure Clock Source0 and clock source1
    //
    DCCOMP_setCounter0ClkSource(base, clock0);
    DCCOMP_setCounter1ClkSource(base, clock1);

    //
    // Configure COUNTER-0, COUNTER-1 & Valid Window
    //
    DCCOMP_setCounterSeeds(base, count0, valid, count1);

    //
    // Enable Single Shot mode
    //
    DCCOMP_enableSingleShotMode(base, DCCOMP_MODE_COUNTER_ZERO);

    //
    // Enable DCCOMP to start counting
    //
    DCCOMP_enableModule(base);

    //
    // Wait until Error or Done Flag is generated
    //
    while(!(DCCOMP_getSingleShotStatus(base) || DCCOMP_getErrorStatus(base)))
    {
    }

    //
    // Calculate the difference of the current counter
    // values with the initial fed counter values. This
    // will give the counts corresponding to the frequency
    // of each clock source
    //
    actual_cnt1 = count1 - DCCOMP_getCounter1Value(base);

    //
    // Compute the frequency using relation F1 = (F0 * Actual C1)/Window.
    //
    freq1 =  (freq0 * actual_cnt1) / (count0 + valid);

    return(freq1);
}

//*****************************************************************************
//
// DCCOMP_continuousMonitor
//
//*****************************************************************************
void
DCCOMP_continuousMonitor(uint32_t base,
                      DCCOMP_Count1ClockSource clock1,
                      float32_t freq1,
                      DCCOMP_Count0ClockSource clock0,
                      float32_t freq0,
                      float32_t tolerance,
                      float32_t freqerr,
                      float32_t freq_sysclk)
{
    uint32_t total_error;
    uint32_t window;
    uint32_t count0;
    uint32_t valid;
    uint32_t count1;

    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // If Fclk1 > Fclk0,
    //     Async. Error (In Clock0 cycles) = 2 + 2*(Fsysclk/Fclk0)
    //
    // If Fclk1 < Fclk0,
    //     Async. Error (In Clock0 cycles) = 2*(Fclk0/Fclk1) + 2*(Fsysclk/Fclk0)
    //
    if(freq1 > freq0)
    {
        total_error = (uint32_t)(2.0f + (2.0f * (freq_sysclk / freq0)));
    }
    else
    {
        total_error = (uint32_t)((2.0f * (freq0 / freq1)) +
                                 (2.0f * (freq_sysclk / freq0)));
    }

    //
    // Digitization error = 8 Clock0 cycles
    //
    total_error += 8U;

    //
    // Window (in Cycles) = (Total Error) / (0.01 * Tolerance)
    //
    window = (uint32_t)((float32_t)total_error / (0.01f * tolerance));

    //
    // Error due to variance in clock frequency =
    // window * (Allowable Frequency Tolerance (in %) / 100)
    //
    total_error += (float32_t)window * (freqerr / 100.0f);

    //
    // DCCOMP counter configuration :
    // Counter0 = Window - Total     Error
    // Valid0 = 2 * Total Error
    // Counter1 = Window * (Fclk1 / Fclk0)
    //
    count0 = window - total_error;
    valid  = 2U * total_error;
    count1 = (uint32_t)(window * freq1 / freq0);

    //
    // Clear Error & Done Flag
    //
    DCCOMP_clearErrorFlag(base);
    DCCOMP_clearDoneFlag(base);

    //
    // Disable DCCOMP and the error and done signals
    //
    DCCOMP_disableModule(base);
    DCCOMP_disableErrorSignal(base);
    DCCOMP_disableDoneSignal(base);

    //
    // Configure Clock Source0 and clock source1
    //
    DCCOMP_setCounter0ClkSource(base, clock0);
    DCCOMP_setCounter1ClkSource(base, clock1);

    //
    // Configure COUNTER-0, COUNTER-1 & Valid Window
    //
    DCCOMP_setCounterSeeds(base, count0, valid, count1);

    //
    // Enable Continuous mode
    //
    DCCOMP_disableSingleShotMode(base);

    //
    // Enable Error Signal
    //
    DCCOMP_enableErrorSignal(base);

    //
    // Enable DCCOMP to start counting
    //
    DCCOMP_enableModule(base);
}
