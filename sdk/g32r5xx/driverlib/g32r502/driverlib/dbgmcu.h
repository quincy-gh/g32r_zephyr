//###########################################################################
//
// FILE:    dbgmcu.h
//
// TITLE:   Driver for DBGMCU.
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
//###########################################################################

#ifndef DBGMCU_H
#define DBGMCU_H

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
//! \addtogroup dbgmcu_api DBGMCU
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_dbgmcu.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"

//*****************************************************************************
//
//! Values that can be passed to DBGMCU_enableDebugHaltSignal() and
//! DBGMCU_disableDebugHaltSignal() as the \e signal parameter.
//
//*****************************************************************************
typedef enum
{
    DBGMCU_DEBUG_HALT_PWM1   = 0x3000U,
    DBGMCU_DEBUG_HALT_PWM2   = 0x3001U,
    DBGMCU_DEBUG_HALT_PWM3   = 0x3002U,
    DBGMCU_DEBUG_HALT_PWM4   = 0x3003U,
    DBGMCU_DEBUG_HALT_PWM5   = 0x3004U,
    DBGMCU_DEBUG_HALT_PWM6   = 0x3005U,
    DBGMCU_DEBUG_HALT_PWM7   = 0x3006U,

    DBGMCU_DEBUG_HALT_CAP1   = 0x3008U,
    DBGMCU_DEBUG_HALT_CAP2   = 0x3009U,
    DBGMCU_DEBUG_HALT_CAP3   = 0x300AU,

    DBGMCU_DEBUG_HALT_COMP1  = 0x3010U,
    DBGMCU_DEBUG_HALT_COMP2  = 0x3011U,
    DBGMCU_DEBUG_HALT_COMP3  = 0x3012U,
    DBGMCU_DEBUG_HALT_COMP4  = 0x3013U,

    DBGMCU_DEBUG_HALT_QEP1   = 0x3018U,

    DBGMCU_DEBUG_HALT_LINA   = 0x3800U,
    DBGMCU_DEBUG_HALT_UARTA  = 0x3801U,
    DBGMCU_DEBUG_HALT_SPIA   = 0x3802U,
    DBGMCU_DEBUG_HALT_I2CA   = 0x3803U,
    DBGMCU_DEBUG_HALT_CANA   = 0x3804U,
    DBGMCU_DEBUG_HALT_UARTB  = 0x3809U,
    DBGMCU_DEBUG_HALT_I2CB   = 0x380BU,
    DBGMCU_DEBUG_HALT_UARTC  = 0x380DU,
    DBGMCU_DEBUG_HALT_FLB1   = 0x3810U,
    DBGMCU_DEBUG_HALT_FLB2   = 0x3811U,
    DBGMCU_DEBUG_HALT_FLB3   = 0x3812U,
    DBGMCU_DEBUG_HALT_FLB4   = 0x3813U,
    DBGMCU_DEBUG_HALT_WDT    = 0x4000U,
    DBGMCU_DEBUG_HALT_TMR0   = 0x4008U,
    DBGMCU_DEBUG_HALT_TMR1   = 0x4009U,
    DBGMCU_DEBUG_HALT_TMR2   = 0x400AU,
    DBGMCU_DEBUG_HALT_DMA    = 0x400BU
} DBGMCU_DebugHaltSignal;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Retrieves the DBGMCU ID code.
//!
//! \param eqr is a pointer to the location where the Equipment ID will be stored.
//! \param wvr is a pointer to the location where the Wafer Version ID will be stored.
//!
//! This function reads the DBGMCU ID code from the hardware and separates it 
//! into the Equipment ID and the Wafer Version ID, which are stored at the 
//! locations pointed to by eqr and wvr, respectively.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_getIDCode(uint16_t *eqr, uint16_t *wvr)
{
    *eqr = (uint16_t)(HWREG(DBGMCU_BASE + DBGMCU_O_IDCODE) &
                        DBGMCU_IDCODE_EQR_M);
    *wvr = (uint16_t)((HWREG(DBGMCU_BASE + DBGMCU_O_IDCODE) &
                         DBGMCU_IDCODE_WVR_M) >>
                        DBGMCU_IDCODE_WVR_S);
}

//*****************************************************************************
//
//! Enables the stop mode debugging
//!
//! This function enables the stop mode debugging.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_enableStopModeDebug(void)
{
    HWREG(DBGMCU_BASE + DBGMCU_O_CTRL) |= DBGMCU_CTRL_STOP_CLK_EN;
}

//*****************************************************************************
//
//! Disables the stop mode debugging
//!
//! This function disables the stop mode debugging.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_disableStopModeDebug(void)
{
    HWREG(DBGMCU_BASE + DBGMCU_O_CTRL) &= ~DBGMCU_CTRL_STOP_CLK_EN;
}

//*****************************************************************************
//
//! Enables the global timestamp halt
//!
//! This function enables the global timestamp halt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_enableGlobalTimestampHalt(void)
{
    HWREG(DBGMCU_BASE + DBGMCU_O_CTRL) |= DBGMCU_CTRL_HALT_GTS_STOP;
}

//*****************************************************************************
//
//! Disables the global timestamp halt.
//!
//! This function disables the global timestamp halt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_disableGlobalTimestampHalt(void)
{
    HWREG(DBGMCU_BASE + DBGMCU_O_CTRL) &= ~DBGMCU_CTRL_HALT_GTS_STOP;
}

//*****************************************************************************
//
//! Enables the real-time mode.
//!
//! This function enables the real-time mode, which allows ISRs to be serviced
//! in DEBUG HALT.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_enableRealTimeMode(void)
{
    HWREG(DBGMCU_BASE + DBGMCU_O_CTRL) |= DBGMCU_CTRL_HALT_INT_REP;
}

//*****************************************************************************
//
//! Disables the real-time mode.
//!
//! This function disables the real-time mode, which prohibits ISRs from being
//! serviced in DEBUG HALT.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_disableRealTimeMode(void)
{
    HWREG(DBGMCU_BASE + DBGMCU_O_CTRL) &= ~DBGMCU_CTRL_HALT_INT_REP;
}

//*****************************************************************************
//
//! Enables the interrupt run mode.
//!
//! This function enables the interrupt run mode, which allows ISRs to be
//! halted in real-time mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_enableIntRunMode(void)
{
    HWREG(DBGMCU_BASE + DBGMCU_O_CTRL) |= DBGMCU_CTRL_REAL_INT;
}

//*****************************************************************************
//
//! Disables the interrupt run mode.
//!
//! This function disables the interrupt run mode, which prohibits ISRs from
//! being halted in real-time mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_disableIntRunMode(void)
{
    HWREG(DBGMCU_BASE + DBGMCU_O_CTRL) &= ~DBGMCU_CTRL_REAL_INT;
}

//*****************************************************************************
//
//! Enables the external trigger output.
//!
//! This function enables the external trigger output, which means that TRGIO
//! is connected to TRGOUT.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_enableExternalTriggerOutput(void)
{
    HWREG(DBGMCU_BASE + DBGMCU_O_CTRL) |= DBGMCU_CTRL_TRGIODIRSEL;
}

//*****************************************************************************
//
//! Disables the external trigger output.
//!
//! This function disables the external trigger output, which means that TRGIO
//! is connected to TRGIN.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_disableExternalTriggerOutput(void)
{
    HWREG(DBGMCU_BASE + DBGMCU_O_CTRL) &= ~DBGMCU_CTRL_TRGIODIRSEL;
}

//*****************************************************************************
//
//! Enables the DEBUG HALT signal for peripheral.
//!
//! \param signal is the DEBUG HALT signal to be enabled, specified as only
//! one of the \b DBGMCU_DebugHaltSignal values.
//!
//! This function enables the DEBUG HALT signal that affects the behavior of
//! peripheral during emulation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_enableDebugHaltSignal(DBGMCU_DebugHaltSignal signal)
{
    uint32_t dbgRegAddr;
    uint32_t shiftAmt;

    //
    // Get the debug register address
    //
    dbgRegAddr = DBGMCU_BASE + (((uint32_t)signal >> 8U) & 0xFFU);

    //
    // Get the peripheral's shift in register
    //
    shiftAmt = (uint32_t)signal & 0xFFU;

    //
    // Enable the DEBUG HALT signal for peripheral
    //
    HWREG(dbgRegAddr) |= (1U << shiftAmt);
}

//*****************************************************************************
//
//! Disables the DEBUG HALT signal for peripheral.
//!
//! \param signal is the DEBUG HALT signal to be disabled, specified as only
//! one of the \b DBGMCU_DEBUG_HALT_???? values.
//!
//! This function disables the DEBUG HALT signal and prevents DEBUG HALT from
//! affecting the behavior of peripheral during emulation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DBGMCU_disableDebugHaltSignal(DBGMCU_DebugHaltSignal signal)
{
    uint32_t dbgRegAddr;
    uint32_t shiftAmt;

    //
    // Get the debug register address
    //
    dbgRegAddr = DBGMCU_BASE + (((uint32_t)signal >> 8U) & 0xFFU);

    //
    // Get the peripheral's shift in register
    //
    shiftAmt = (uint32_t)signal & 0xFFU;

    //
    // Disable the DEBUG HALT signal for peripheral
    //
    HWREG(dbgRegAddr) &= ~(1U << shiftAmt);
}

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

#endif // DBGMCU_H
