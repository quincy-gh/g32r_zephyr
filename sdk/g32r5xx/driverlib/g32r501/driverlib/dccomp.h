//###########################################################################
//
// FILE:    DCCOMP.h
//
// TITLE:   G32R501 DCCOMP driver.
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
// 1. Some comments, module names, macro definitions, enum names,
//    function names, register names
//
//###########################################################################

#ifndef DCCOMP_H
#define DCCOMP_H

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
//! \addtogroup DCCOMP_api DCCOMP
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_dccomp.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//
// Minimum and maximum values of valid seed value
//
#define DCCOMP_VALIDSEED_MIN 4U
#define DCCOMP_VALIDSEED_MAX 0xFFFFU

//
// Minimum and maximum values of counter0/1 seed value
//
#define DCCOMP_COUNTSEED_MIN 1U
#define DCCOMP_COUNTSEED_MAX 0xFFFFFU

//
// The reset value required to start or enable specific DCCOMP operations
//
#define DCCOMP_ENABLE_VALUE     (0xAU)

//
// The reset value required to stop or disable specific DCCOMP operations
//
#define DCCOMP_DISABLE_VALUE    (0x5U)

//
// A 16-bit register mask
//
#define DCCOMP_REG_WORD_MASK    (0xFFFFU)

//
// A 8-bit register mask
//
#define DCCOMP_REG_BYTE_MASK    (0xFFU)

//
// A mask for the DCCOMP counter seed registers
//
#define DCCOMP_SEED_REG_MASK    (0xFFF0U)

//
// A mask for the DCCOMP counter seed value
//
#define DCCOMP_SEED_CNT_MASK    (0xF0000U)

//*****************************************************************************
//
//! The following are defines for the mode parameter of the
//! DCCOMP_enableSingleShotMode() function.
//
//*****************************************************************************
typedef enum
{
    //! Use to stop counting when counter0 and valid0 both reach zero
    DCCOMP_MODE_COUNTER_ZERO = 0xA00U,

    //! Use to stop counting when counter1 reaches zero
    DCCOMP_MODE_COUNTER_ONE  = 0xB00U
} DCCOMP_SingleShotMode;

//*****************************************************************************
//
//! The following are defines for the identifier parameter of the
//! DCCOMP_getRevisionNumber() function.
//
//*****************************************************************************
typedef enum
{
    DCCOMP_REVISION_MINOR       = 0x0U,  //!< The module minor revision number
    DCCOMP_REVISION_MAJOR       = 0x2U,  //!< The module major revision number
} DCCOMP_RevisionNumber;

//*****************************************************************************
//
//! The following are defines for the source parameter of the
//! DCCOMP_setCounter1ClkSource() function.
//
//*****************************************************************************
typedef enum
{
    DCCOMP_COUNT1SRC_PLL           = 0x0U, //!< PLLRAWCLK Clock Out Source
    DCCOMP_COUNT1SRC_INTOSC1       = 0x2U, //!< Internal OUARTllator1 Clock Source
    DCCOMP_COUNT1SRC_INTOSC2       = 0x3U, //!< Internal OUARTllator2 Clock Source
} DCCOMP_Count1ClockSource;

//*****************************************************************************
//
//! The following are defines for the source parameter of the
//! DCCOMP_setCounter0ClkSource() function.
//
//*****************************************************************************
typedef enum
{
    DCCOMP_COUNT0SRC_XTAL       = 0x0U,    //!< XTAL Clock Source
    DCCOMP_COUNT0SRC_INTOSC1    = 0x1U,    //!< Internal OUARTllator1 Clock Source
    DCCOMP_COUNT0SRC_INTOSC2    = 0x2U,    //!< Internal OUARTllator2 Clock Source
} DCCOMP_Count0ClockSource;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks DCCOMP base address.
//!
//! \param base specifies the DCCOMP module base address.
//!
//! This function determines if an DCCOMP module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
DCCOMP_isBaseValid(uint32_t base)
{
    return(
           (base == DCCOMP0_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Enables the DCCOMP module.
//!
//! \param base is the DCCOMP module base address
//!
//! This function starts the DCCOMP counter operation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Set DCCOMP enable bit field.
    //
    WRPRT_DISABLE;

    HWREGH(base + DCCOMP_O_DCCOMPCTRL) = (HWREGH(base + DCCOMP_O_DCCOMPCTRL) &
                                  ~(DCCOMP_DCCOMPCTRL_DCCOMPEN_M)) | DCCOMP_ENABLE_VALUE;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable the DCCOMP module.
//!
//! \param base is the DCCOMP module base address
//!
//! This function stops the DCCOMP counter operation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Reset DCCOMP enable bit field.
    //
    WRPRT_DISABLE;

    HWREGH(base + DCCOMP_O_DCCOMPCTRL) = (HWREGH(base + DCCOMP_O_DCCOMPCTRL) &
                                  ~(DCCOMP_DCCOMPCTRL_DCCOMPEN_M)) | DCCOMP_DISABLE_VALUE;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable DCCOMP Error Signal
//!
//! \param base is the DCCOMP module base address
//!
//! This function enables the error signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_enableErrorSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Enable the error signal
    //
    WRPRT_DISABLE;

    HWREGH(base + DCCOMP_O_DCCOMPCTRL) = (HWREGH(base + DCCOMP_O_DCCOMPCTRL) &
                                  ~(DCCOMP_DCCOMPCTRL_ERREN_M)) |
                                  (DCCOMP_ENABLE_VALUE << 4U);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable DCCOMP Done Signal
//!
//! \param base is the DCCOMP module base address
//!
//! This function enables the done signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_enableDoneSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Enable the done interrupt signal
    //
    WRPRT_DISABLE;

    HWREGH(base + DCCOMP_O_DCCOMPCTRL) = (HWREGH(base + DCCOMP_O_DCCOMPCTRL) &
                                  ~(DCCOMP_DCCOMPCTRL_DONEEN_M)) |
                                  (DCCOMP_ENABLE_VALUE << 12U);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable DCCOMP Error Signal
//!
//! \param base is the DCCOMP module base address
//!
//! This function disables the error signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_disableErrorSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Disable the error signal
    //
    WRPRT_DISABLE;

    HWREGH(base + DCCOMP_O_DCCOMPCTRL) = (HWREGH(base + DCCOMP_O_DCCOMPCTRL) &
                                  ~(DCCOMP_DCCOMPCTRL_ERREN_M)) |
                                 (DCCOMP_DISABLE_VALUE << 4U);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable DCCOMP Done Signal
//!
//! \param base is the DCCOMP module base address
//!
//! This function disables the done signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_disableDoneSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Disable the done interrupt signal
    //
    WRPRT_DISABLE;

    HWREGH(base + DCCOMP_O_DCCOMPCTRL) = (HWREGH(base + DCCOMP_O_DCCOMPCTRL) &
                                  ~(DCCOMP_DCCOMPCTRL_DONEEN_M)) |
                                 (DCCOMP_DISABLE_VALUE << DCCOMP_DCCOMPCTRL_DONEEN_S);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable DCCOMP Single-Shot Mode
//!
//! \param base is the DCCOMP module base address
//! \param mode is the selected Single-Shot operation mode
//!
//! This function enables the single-shot mode and sets the operation mode.
//!
//! The \e mode parameter can have one of two values:
//! - \b DCCOMP_MODE_COUNTER_ZERO - Stops counting when counter0 and valid0 both
//!   reach zero
//! - \b DCCOMP_MODE_COUNTER_ONE  - Stops counting when counter1 reaches zero
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_enableSingleShotMode(uint32_t base, DCCOMP_SingleShotMode mode)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Set Single-Shot mode value to the appropriate register
    //
    if(mode == DCCOMP_MODE_COUNTER_ZERO)
    {
        WRPRT_DISABLE;

        HWREGH(base + DCCOMP_O_DCCOMPCTRL) = (HWREGH(base + DCCOMP_O_DCCOMPCTRL) &
                                      ~(DCCOMP_DCCOMPCTRL_SIGEN_M)) |
                                     (uint16_t)DCCOMP_MODE_COUNTER_ZERO;

        WRPRT_ENABLE;
    }
    else
    {
        WRPRT_DISABLE;

        HWREGH(base + DCCOMP_O_DCCOMPCTRL) = (HWREGH(base + DCCOMP_O_DCCOMPCTRL) &
                                      ~(DCCOMP_DCCOMPCTRL_SIGEN_M)) |
                                     (uint16_t)DCCOMP_MODE_COUNTER_ONE;

        WRPRT_ENABLE;
    }
}

//*****************************************************************************
//
//! Disable DCCOMP Single-Shot Mode
//!
//! \param base is the DCCOMP module base address
//!
//! This function disables the DCCOMP Single-Shot operation mode
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_disableSingleShotMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Reset Single-Shot enable bit field.
    //
    WRPRT_DISABLE;

    HWREGH(base + DCCOMP_O_DCCOMPCTRL) = (HWREGH(base + DCCOMP_O_DCCOMPCTRL) &
                                  ~(DCCOMP_DCCOMPCTRL_SIGEN_M)) |
                                 (DCCOMP_DISABLE_VALUE << DCCOMP_DCCOMPCTRL_SIGEN_S);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Get Error Flag Status
//!
//! \param base is the DCCOMP module base address
//!
//! This function gets the error flag status.
//!
//! \return Returns \b true if an error has occurred, \b false if no errors
//! have occurred.
//
//*****************************************************************************
static inline bool
DCCOMP_getErrorStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Get the error flag
    //
    return((bool)((HWREGH(base + DCCOMP_O_DCCOMPFLG) & DCCOMP_DCCOMPFLG_ERRFLG) ==
                  DCCOMP_DCCOMPFLG_ERRFLG));
}

//*****************************************************************************
//
//! Get Single-Shot Done Flag Status
//!
//! \param base is the DCCOMP module base address
//!
//! This function gets the single-shot done flag status.
//!
//! \return Returns \b true if single-shot mode has completed, \b false if
//! single-shot mode has not completed.
//
//*****************************************************************************
static inline bool
DCCOMP_getSingleShotStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Read the done flag
    //
    return((bool)((HWREGH(base + DCCOMP_O_DCCOMPFLG) & DCCOMP_DCCOMPFLG_SIGDONEFLG) ==
                  DCCOMP_DCCOMPFLG_SIGDONEFLG));
}

//*****************************************************************************
//
//! Clear Error Status Flag
//!
//! \param base is the DCCOMP module base address
//!
//! This function clears the DCCOMP error status flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_clearErrorFlag(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Clear error status flag
    //
    WRPRT_DISABLE;

    HWREGH(base + DCCOMP_O_DCCOMPFLG) |= DCCOMP_DCCOMPFLG_ERRFLG;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Clear Single-Shot Done Status Flag
//!
//! \param base is the DCCOMP module base address
//!
//! This function clears the DCCOMP single-shot done status flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_clearDoneFlag(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Clear done status flag
    //
    WRPRT_DISABLE;

    HWREGH(base + DCCOMP_O_DCCOMPFLG) |= DCCOMP_DCCOMPFLG_SIGDONEFLG;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Get Current Value of Counter 0
//!
//! \param base is the DCCOMP module base address
//!
//! This function gets current value of counter 0.
//!
//! \note Reads of the counter value may not be exact since the read operation
//! is synchronized to the vbus clock.
//!
//! \return Returns the current value of counter 0.
//
//*****************************************************************************
static inline uint32_t
DCCOMP_getCounter0Value(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Get the current counter 0 value
    //
    return(HWREG(base + DCCOMP_O_DCCOMPCLKSRCCNT0));
}

//*****************************************************************************
//
//! Get Current Value of the Valid Duration Counter for Counter 0
//!
//! \param base is the DCCOMP module base address
//!
//! This function gets current value of the valid duration counter for
//! counter 0.
//!
//! \note Reads of the counter value may not be exact since the read operation
//! is synchronized to the vbus clock.
//!
//! \return Returns the current value of the valid duration counter.
//
//*****************************************************************************
static inline uint16_t
DCCOMP_getValidCounter0Value(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Get the current valid duration counter value
    //
    return(HWREGH(base + DCCOMP_O_DCCOMPCLKSRCVAL0));
}

//*****************************************************************************
//
//! Get Current Value of Counter 1
//!
//! \param base is the DCCOMP module base address
//!
//! This function gets current value of counter 1.
//!
//! \note Reads of the counter value may not be exact since the read operation
//! is synchronized to the vbus clock.
//!
//! \return Returns the current value of counter 1.
//
//*****************************************************************************
static inline uint32_t
DCCOMP_getCounter1Value(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    // Get the current counter 1 value
    //
    return(HWREG(base + DCCOMP_O_DCCOMPCLKSRCCNT1));
}

//*****************************************************************************
//
//! Set Counter 1 Clock Source
//!
//! \param base is the DCCOMP module base address
//! \param source is the selected clock source for counter 1
//!
//! This function sets the counter 1 clock source.
//!
//! The \e source parameter can have one of following values:
//! - \b DCCOMP_COUNT1SRC_PLL          - PLL021SSP Clock Out Source
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_setCounter1ClkSource(uint32_t base, DCCOMP_Count1ClockSource source)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    //  Set the specified clock source
    //
    WRPRT_DISABLE;

    //
    //  DCCOMP Clk source is of 4bits DCCOMPCLKSRC1[3:0]
    //
    HWREGH(base + DCCOMP_O_DCCOMPCLKSRCSEL1) = (HWREGH(base + DCCOMP_O_DCCOMPCLKSRCSEL1) &
                                    (DCCOMP_REG_BYTE_MASK << 4U)) |
                                   ((DCCOMP_ENABLE_VALUE << 12U) |
                                    (uint16_t)source);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Counter 0 Clock Source
//!
//! \param base is the DCCOMP module base address
//! \param source is the selected clock source for counter 0
//!
//! This function sets the counter 0 clock source.
//!
//! The \e source parameter can have one of following values:
//! - \b DCCOMP_COUNT0SRC_XTAL         - Accurate Clock Source
//! - \b DCCOMP_COUNT0SRC_INTOSC1      - Internal OUARTllator1 Clock Source
//! - \b DCCOMP_COUNT0SRC_INTOSC2      - Internal OUARTllator2 Clock Source
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCCOMP_setCounter0ClkSource(uint32_t base, DCCOMP_Count0ClockSource source)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    //  Set the specified clock source
    //
    WRPRT_DISABLE;

    HWREGH(base + DCCOMP_O_DCCOMPCLKSRCSEL0) = (HWREGH(base + DCCOMP_O_DCCOMPCLKSRCSEL0) &
                                    ~(DCCOMP_DCCOMPCLKSRCSEL0_CLKSRCSEL0_M)) |
                                    (uint16_t)source;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Get Counter 1 Clock Source
//!
//! \param base is the DCCOMP module base address
//!
//! This function gets the counter 1 clock source.
//!
//! \return Returns one of the following enumerated source values:
//! - \b DCCOMP_COUNT1SRC_PLL          - PLL021SSP Clock Out Source

//
//*****************************************************************************
static inline uint16_t
DCCOMP_getCounter1ClkSource(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    //  Get the specified clock source
    //
    return(HWREGH(base + DCCOMP_O_DCCOMPCLKSRCSEL1) & DCCOMP_DCCOMPCLKSRCSEL1_CLKSRCSEL1_M);
}

//*****************************************************************************
//
//! Get Counter 0 Clock Source
//!
//! \param base is the DCCOMP module base address
//!
//! This function gets the counter 0 clock source.
//!
//! \return Returns one of the following enumerated source values:
//! - \b DCCOMP_COUNT0SRC_XTAL         - Accurate Clock Source
//! - \b DCCOMP_COUNT0SRC_INTOSC1      - Internal OUARTllator1 Clock Source
//! - \b DCCOMP_COUNT0SRC_INTOSC2      - Internal OUARTllator2 Clock Source
//
//*****************************************************************************
static inline uint16_t
DCCOMP_getCounter0ClkSource(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));

    //
    //  Get the specified clock source
    //
    return(HWREGH(base + DCCOMP_O_DCCOMPCLKSRCSEL0) & DCCOMP_DCCOMPCLKSRCSEL0_CLKSRCSEL0_M);
}

//*****************************************************************************
//
//! Set the seed values
//!
//! \param base is the DCCOMP module base address
//! \param counter0 sets the seed value that gets loaded into Counter 0
//! \param validCounter0 sets the seed value that gets loaded into the valid
//!  duration counter for Counter 0
//! \param counter1 sets the seed value that gets loaded into Counter 1
//!
//! This function sets the seed values for Counter 0, Valid Duration Counter 0,
//! and Counter 1.
//!
//! \note
//! -# Operating DCCOMP with '0' set as the seed value for Counter 0, Valid
//! Duration Counter 0, and/or Counter 1 will result in undefined operation.
//! -# The Valid Duration Counter 0 is designed to be at least four cycles
//! wide and shouldn't be programmed with a value less than '4'.
//!
//! \return None.
//
//*****************************************************************************


static inline void
DCCOMP_setCounterSeeds(uint32_t base, uint32_t counter0, uint32_t validCounter0,
                    uint32_t counter1)
{
    //
    // Check the arguments.
    //
    ASSERT(DCCOMP_isBaseValid(base));
    ASSERT(validCounter0 >= DCCOMP_VALIDSEED_MIN);
    ASSERT(counter0 >= DCCOMP_COUNTSEED_MIN);
    ASSERT(counter1 >= DCCOMP_COUNTSEED_MIN);
    ASSERT(validCounter0 <= DCCOMP_VALIDSEED_MAX);
    ASSERT(counter0 <= DCCOMP_COUNTSEED_MAX);
    ASSERT(counter1 <= DCCOMP_COUNTSEED_MAX);

    WRPRT_DISABLE;

    //
    // Set Counter 0 Seed
    //
    HWREGH(base + DCCOMP_O_DCCOMPCNTSEED0) = counter0 & DCCOMP_REG_WORD_MASK;
    HWREGH(base + DCCOMP_O_DCCOMPCNTSEED0 + 2U) = (HWREGH(base + DCCOMP_O_DCCOMPCNTSEED0 + 2U) &
                                          DCCOMP_SEED_REG_MASK) |
                                         ((uint32_t)(counter0 &
                                          DCCOMP_SEED_CNT_MASK) >> 16U);

    //
    // Set Valid Duration Counter 0 Seed
    //
    HWREGH(base + DCCOMP_O_DCCOMPVALSEED0) = validCounter0;

    //
    // Set Counter 1 Seed
    //
    HWREGH(base + DCCOMP_O_DCCOMPCNTSEED1) = counter1 & DCCOMP_REG_WORD_MASK;
    HWREGH(base + DCCOMP_O_DCCOMPCNTSEED1 + 2U ) = (HWREGH(base + DCCOMP_O_DCCOMPCNTSEED1 +2U) &
                                          DCCOMP_SEED_REG_MASK) |
                                         ((uint32_t)(counter1 &
                                          DCCOMP_SEED_CNT_MASK) >> 16U);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Get DCCOMP Version Number
//!
//! \param base is the DCCOMP module base address
//! \param identifier is the selected revision number identifier
//!
//! This function gets the specific version number.
//!
//! The \e identifier parameter can have one of these values:
//! - \b DCCOMP_REVISION_MINOR      - The minor revision number
//! - \b DCCOMP_REVISION_MAJOR      - The major revision number
//!
//! \return Specified revision number
//
//*****************************************************************************
extern uint16_t
DCCOMP_getRevisionNumber(uint32_t base, DCCOMP_RevisionNumber identifier);


//*****************************************************************************
//
//! Verify the frequency of a clock source using a reference clock
//!
//! \param base is the DCCOMP module base address
//! \param clock1 is the clock source to be verified
//! \param freq1 is the frequency of the clock source to be verified
//! \param clock0 is the reference clock
//! \param freq0 is the frequency of the reference clock
//! \param tolerance is the DCCOMP error tolerance in percentage
//! \param freqerr is the allowable Frequency Tolerance in percentage
//! \param freq_sysclk is the frequency of the system clock
//!
//! This function verifies the frequency of the specified clock using a
//! reference clock.
//!
//! \note Make sure that the frequency of all the clocks are in the same unit
//!
//! \return Returns \b true if the actual frequency of clock1 is matching
//! freq1, \b false otherwise
//
//*****************************************************************************
extern bool
DCCOMP_verifyClockFrequency(uint32_t base,
                         DCCOMP_Count1ClockSource clock1,
                         float32_t freq1,
                         DCCOMP_Count0ClockSource clock0,
                         float32_t freq0,
                         float32_t tolerance,
                         float32_t freqerr,
                         float32_t freq_sysclk);

//*****************************************************************************
//
//! Measure the frequency of a clock source using a reference clock
//!
//! \param base is the DCCOMP module base address
//! \param clock1 is the clock source to be measured
//! \param clock0 is the reference clock
//! \param freq0 is the frequency of the reference clock
//! \param tolerance is the DCCOMP error tolerance in percentage
//! \param freqerr is the allowable Frequency Tolerance in percentage
//! \param freq_sysclk is the frequency of the system clock
//!
//! This function measures the frequency of the specified clock using a
//! reference clock.
//!
//! \note Make sure that the frequency of all the clocks are in the same unit
//!
//! \return Measured clock frequency
//
//*****************************************************************************
extern float32_t
DCCOMP_measureClockFrequency(uint32_t base,
                          DCCOMP_Count1ClockSource clock1,
                          DCCOMP_Count0ClockSource clock0,
                          float32_t freq0,
                          float32_t tolerance,
                          float32_t freqerr,
                          float32_t freq_sysclk);

//*****************************************************************************
//
//! Continuously monitor the frequency of a clock source using a reference clock
//!
//! \param base is the DCCOMP module base address
//! \param clock1 is the clock source to be verified
//! \param freq1 is the frequency of the clock source to be verified
//! \param clock0 is the reference clock
//! \param freq0 is the frequency of the reference clock
//! \param tolerance is the DCCOMP error tolerance in percentage
//! \param freqerr is the allowable Frequency Tolerance in percentage
//! \param freq_sysclk is the frequency of the system clock
//!
//! This function continuously monitors the frequency of the specified clock
//! using a reference clock. An error signal is generated if the frequency
//! ratio is altered.
//!
//! \note Make sure that the frequency of all the clocks are in the same unit
//!
//! \note This function does not enable the DCCOMP interrupt. The user application
//! must enable it to trigger an intetrupt when an error is detected.
//!
//! \return Returns None
//
//*****************************************************************************
extern void
DCCOMP_continuousMonitor(uint32_t base,
                      DCCOMP_Count1ClockSource clock1,
                      float32_t freq1,
                      DCCOMP_Count0ClockSource clock0,
                      float32_t freq0,
                      float32_t tolerance,
                      float32_t freqerr,
                      float32_t freq_sysclk);
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

#endif // DCCOMP_H
