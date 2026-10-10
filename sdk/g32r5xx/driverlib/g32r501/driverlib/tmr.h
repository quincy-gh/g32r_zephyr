//#############################################################################
//
// FILE:    tmr.h
//
// TITLE:   G32R501 CPU timer Driver
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
// 1. Module prefix naming
//
//###########################################################################

#ifndef TMR_H
#define TMR_H

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

#ifdef __G32R501XX__

//*****************************************************************************
//
//! \addtogroup tmr_api TMR
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_tmr.h"
#include "debug.h"
#include "sysctl.h"

//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************
//*****************************************************************************
//
//! Values that can be passed to TMR_setEmulationMode() as the
//! \e mode parameter.
//
//****************************************************************************
typedef enum
{
  //! Denotes that the timer will stop after the next decrement
  TMR_EMULATIONMODE_STOPAFTERNEXTDECREMENT = 0x0000,
  //! Denotes that the timer will stop when it reaches zero
  TMR_EMULATIONMODE_STOPATZERO = 0x0400,
  //! Denotes that the timer will run free
  TMR_EMULATIONMODE_RUNFREE = 0x0800
}TMR_EmulationMode;

//*****************************************************************************
//
//! The following are values that can be passed to
//! TMR_selectClockSource() as the \e source parameter.
//
//*****************************************************************************
typedef enum
{
    //! System Clock Source
    TMR_CLOCK_SOURCE_SYS     = 0x0,
    //! Internal Oscillator 1 Clock Source
    TMR_CLOCK_SOURCE_INTOSC1 = 0x1,
    //! Internal Oscillator 2 Clock Source
    TMR_CLOCK_SOURCE_INTOSC2 = 0x2,
    //! External Clock Source
    TMR_CLOCK_SOURCE_XTAL    = 0x3,
    //!FLPUMPOSC Clock Source
    TMR_CLOCK_SOURCE_FLPUMPOSC    = 0x4,
} TMR_ClockSource;

//*****************************************************************************
//
//! The following are values that can be passed to
//! TMR_selectClockSource() as the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    TMR_CLOCK_PRESCALER_1  = 0,      //!< Prescaler value of / 1
    TMR_CLOCK_PRESCALER_2  = 1,      //!< Prescaler value of / 2
    TMR_CLOCK_PRESCALER_4  = 2,      //!< Prescaler value of / 4
    TMR_CLOCK_PRESCALER_8  = 3,      //!< Prescaler value of / 8
    TMR_CLOCK_PRESCALER_16 = 4       //!< Prescaler value of / 16
} TMR_Prescaler;

//*****************************************************************************
//
//! \internal
//! Checks CPU timer base address.
//!
//! \param base specifies the Timer module base address.
//!
//! This function determines if a CPU timer module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool TMR_isBaseValid(uint32_t base)
{
    return((base == TMR0_BASE) || (base == TMR1_BASE) ||
           (base == TMR2_BASE));
}
#endif

//*****************************************************************************
//
//! Clears CPU timer overflow flag.
//!
//! \param base is the base address of the timer module.
//!
//! This function clears the CPU timer overflow flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void TMR_clearOverflowFlag(uint32_t base)
{
    ASSERT(TMR_isBaseValid(base));

    //
    // Set OVRFLG bit of CTRL register
    //
    HWREGH(base + TMR_O_TCR) |= TMR_TCR_TIF;
}

//*****************************************************************************
//
//! Disables CPU timer interrupt.
//!
//! \param base is the base address of the timer module.
//!
//! This function disables the CPU timer interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void TMR_disableInterrupt(uint32_t base)
{
    ASSERT(TMR_isBaseValid(base));

    //
    // Clear INTEN bit of CTRL register
    //
    HWREGH(base + TMR_O_TCR) &= ~TMR_TCR_TIE;
}

//*****************************************************************************
//
//! Enables CPU timer interrupt.
//!
//! \param base is the base address of the timer module.
//!
//! This function enables the CPU timer interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void TMR_enableInterrupt(uint32_t base)
{
    uint16_t tcrValue = 0;
    ASSERT(TMR_isBaseValid(base));

    //
    // Set INTEN bit of CTRL register
    //
    tcrValue = HWREGH(base + TMR_O_TCR) & (~TMR_TCR_TIF);
    HWREGH(base + TMR_O_TCR) = tcrValue | TMR_TCR_TIE;
}

//*****************************************************************************
//
//! Reloads CPU timer counter.
//!
//! \param base is the base address of the timer module.
//!
//! This function reloads the CPU timer counter with the values contained in
//! the CPU timer period register.
//!
//! \return None.
//
//*****************************************************************************
static inline void TMR_reloadTimerCounter(uint32_t base)
{
    uint16_t tcrValue = 0;
    ASSERT(TMR_isBaseValid(base));

    //
    // Set RELOAD bit of register CTRL
    //
    tcrValue = HWREGH(base + TMR_O_TCR) & (~TMR_TCR_TIF);
    HWREGH(base + TMR_O_TCR) = tcrValue | TMR_TCR_TRB;
}

//*****************************************************************************
//
//! Stops CPU timer.
//!
//! \param base is the base address of the timer module.
//!
//! This function stops the CPU timer.
//!
//! \return None.
//
//*****************************************************************************
static inline void TMR_stopTimer(uint32_t base)
{
    uint16_t tcrValue = 0;
    ASSERT(TMR_isBaseValid(base));

    //
    // Set STOPEN bit of register CTRL
    //
    tcrValue = HWREGH(base + TMR_O_TCR) & (~TMR_TCR_TIF);
    HWREGH(base + TMR_O_TCR) = tcrValue | TMR_TCR_TSS;
}

//*****************************************************************************
//
//! Starts(restarts) CPU timer.
//!
//! \param base is the base address of the timer module.
//!
//! This function starts (restarts) the CPU timer.
//!
//! \b Note: This function doesn't reset the timer counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void TMR_resumeTimer(uint32_t base)
{
    ASSERT(TMR_isBaseValid(base));

    //
    // Clear STOPEN bit of register CTRL
    //
    HWREGH(base + TMR_O_TCR) &= ~TMR_TCR_TSS;
}

//*****************************************************************************
//
//! Starts(restarts) CPU timer.
//!
//! \param base is the base address of the timer module.
//!
//! This function starts (restarts) the CPU timer.
//!
//! \b Note: This function reloads the timer counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void TMR_startTimer(uint32_t base)
{
    uint16_t tcrValue = 0;
    ASSERT(TMR_isBaseValid(base));

    //
    // Reload the timer counter
    //
    tcrValue = HWREGH(base + TMR_O_TCR) & (~TMR_TCR_TIF);
    HWREGH(base + TMR_O_TCR) = tcrValue | TMR_TCR_TRB;

    //
    // Clear STOPEN bit of register CTRL
    //
    HWREGH(base + TMR_O_TCR) &= ~TMR_TCR_TSS;
}

//*****************************************************************************
//
//! Sets CPU timer period.
//!
//! \param base is the base address of the timer module.
//! \param periodCount is the CPU timer period count.
//!
//! This function sets the CPU timer period count.
//!
//! \return None.
//
//*****************************************************************************
static inline void TMR_setPeriod(uint32_t base, uint32_t periodCount)
{
    ASSERT(TMR_isBaseValid(base));

    //
    // Load the MSB period Count
    //
    HWREG(base + TMR_O_PRD) = periodCount;
}

//*****************************************************************************
//
//! Returns the current CPU timer counter value.
//!
//! \param base is the base address of the timer module.
//!
//! This function returns the current CPU timer counter value.
//!
//! \return Returns the current CPU timer count value.
//
//*****************************************************************************
static inline uint32_t TMR_getTimerCount(uint32_t base)
{
    ASSERT(TMR_isBaseValid(base));

    //
    // Get the TIMH:TIM registers value
    //
    return(HWREG(base + TMR_O_TIM));
}

//*****************************************************************************
//
//! Set CPU timer pre-scaler value.
//!
//! \param base is the base address of the timer module.
//! \param prescaler is the CPU timer pre-scaler value.
//!
//! This function sets the pre-scaler value for the CPU timer. For every value
//! of (prescaler + 1), the CPU timer counter decrements by 1.
//!
//! \return None.
//
//*****************************************************************************
static inline void TMR_setPreScaler(uint32_t base, uint16_t prescaler)
{
    ASSERT(TMR_isBaseValid(base));

    //
    // Writes to PSCL.PSCPRDL and PSCH.PSCPRDH bits
    //
    HWREGH(base + TMR_O_TPRH) = prescaler >> 8U;
    HWREGH(base + TMR_O_TPR) = (prescaler & TMR_TPR_TDDR_M) ;
}

//*****************************************************************************
//
//! Return the CPU timer overflow status.
//!
//! \param base is the base address of the timer module.
//!
//! This function returns the CPU timer overflow status.
//!
//! \return Returns true if the CPU timer has overflowed, false if not.
//
//*****************************************************************************
static inline bool TMR_getTimerOverflowStatus(uint32_t base)
{
    ASSERT(TMR_isBaseValid(base));

    //
    // Check if OVRFLG bits of register CTRL are set
    //
    return(((HWREGH(base + TMR_O_TCR) & TMR_TCR_TIF) ==
            TMR_TCR_TIF) ? true : false);
}


//*****************************************************************************
//
//! Select CPU Timer 2 Clock Source and Prescaler
//!
//! \param base is the base address of the timer module.
//! \param source is the clock source to use for CPU Timer 2
//! \param prescaler is the value that configures the selected clock source
//! relative to the system clock
//!
//! This function selects the specified clock source and prescaler value
//! for the CPU timer (CPU timer 2 only).
//!
//! The \e source parameter can be any one of the following:
//! - \b TMR_CLOCK_SOURCE_SYS     - System Clock
//! - \b TMR_CLOCK_SOURCE_INTOSC1 - Internal Oscillator 1 Clock
//! - \b TMR_CLOCK_SOURCE_INTOSC2 - Internal Oscillator 2 Clock
//! - \b TMR_CLOCK_SOURCE_XTAL    - External Clock
//!
//! The \e prescaler parameter can be any one of the following:
//! - \b TMR_CLOCK_PRESCALER_1  - Prescaler value of / 1
//! - \b TMR_CLOCK_PRESCALER_2  - Prescaler value of / 2
//! - \b TMR_CLOCK_PRESCALER_4  - Prescaler value of / 4
//! - \b TMR_CLOCK_PRESCALER_8  - Prescaler value of / 8
//! - \b TMR_CLOCK_PRESCALER_16 - Prescaler value of / 16
//!
//! \return None.
//
//*****************************************************************************
static inline void TMR_selectClockSource(uint32_t base,
                                              TMR_ClockSource source,
                                              TMR_Prescaler prescaler)
{
    ASSERT(base == TMR2_BASE);

    //
    // Set source and prescaler for CPU Timer 2
    //
    if(base == TMR2_BASE)
    {
        WRPRT_DISABLE;

        //
        // Set Clock Source
        //
        HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) &=
            ~SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_M;

        HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) |= (uint16_t)source;

        //
        // Set Clock Prescaler
        //
        HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) &=
            ~SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_M;

        HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) |= ((uint16_t)prescaler <<
                SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_S);

        WRPRT_ENABLE;
    }
    return; 
}

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! Sets Emulation mode for CPU timer.
//!
//! \param base is the base address of the timer module.
//! \param mode is the emulation mode of the timer.
//!
//! This function sets the behaviour of CPU timer during emulation. Valid
//! values mode are: TMR_EMULATIONMODE_STOPAFTERNEXTDECREMENT,
//! TMR_EMULATIONMODE_STOPATZERO and TMR_EMULATIONMODE_RUNFREE.
//!
//! \return None.
//
//*****************************************************************************
extern void TMR_setEmulationMode(uint32_t base,
                                      TMR_EmulationMode mode);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#endif // #ifdef __G32R501XX__

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // TMR_H
