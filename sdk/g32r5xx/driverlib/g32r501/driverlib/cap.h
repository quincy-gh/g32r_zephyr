//###########################################################################
//
// FILE:    cap.h
//
// TITLE:   G32R501 CAP driver
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
// 1. Module naming, macro definition, enumeration naming, register naming,
//    partial function naming
//
//###########################################################################

#ifndef CAP_H
#define CAP_H

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
//! \addtogroup CAP_api CAP
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Includes
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_cap.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// CAP minimum and maximum values
//
//*****************************************************************************
#define CAP_MAX_PRESCALER_VALUE       32U  // Maximum Pre-scaler value

//*****************************************************************************
//
// Values that can be passed to CAP_enableInterrupt(),
// CAP_disableInterrupt(), CAP_clearInterrupt() and CAP_forceInterrupt() as
// the intFlags parameter and returned by CAP_getInterruptSource().
//
//*****************************************************************************
//! Event 1 ISR source
//!
#define CAP_ISR_SOURCE_CAPTURE_EVENT_1 0x2U
//! Event 2 ISR source
//!
#define CAP_ISR_SOURCE_CAPTURE_EVENT_2 0x4U
//! Event 3 ISR source
//!
#define CAP_ISR_SOURCE_CAPTURE_EVENT_3 0x8U
//! Event 4 ISR source
//!
#define CAP_ISR_SOURCE_CAPTURE_EVENT_4 0x10U
//! Counter overflow ISR source
//!
#define CAP_ISR_SOURCE_COUNTER_OVERFLOW 0x20U
//! Counter equals period ISR source
//!
#define CAP_ISR_SOURCE_COUNTER_PERIOD 0x40U
//! Counter equals compare ISR source
//!
#define CAP_ISR_SOURCE_COUNTER_COMPARE 0x80U

//*****************************************************************************
//
//! Values that can be passed to CAP_setEmulationMode() as the
//! \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    //! TSCTR is stopped on emulation suspension
    CAP_EMULATION_STOP             = 0x0U,
    //! TSCTR runs until 0 before stopping on emulation suspension
    CAP_EMULATION_RUN_TO_ZERO      = 0x1U,
    //! TSCTR is not affected by emulation suspension
    CAP_EMULATION_FREE_RUN         = 0x2U
}CAP_EmulationMode;

//*****************************************************************************
//
//! Values that can be passed to CAP_setCaptureMode() as the
//! \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    //! CAP operates in continuous capture mode
    CAP_CONTINUOUS_CAPTURE_MODE    = 0U,
    //! CAP operates in one shot capture mode
    CAP_ONE_SHOT_CAPTURE_MODE      = 1U
}CAP_CaptureMode;

//*****************************************************************************
//
//! Values that can be passed to CAP_setEventPolarity(),CAP_setCaptureMode(),
//! CAP_enableCounterResetOnEvent(),CAP_disableCounterResetOnEvent(),
//! CAP_getEventTimeStamp(),CAP_setDMASource() as the \e event parameter.
//
//*****************************************************************************
typedef enum
{
    CAP_EVENT_1 = 0U,   //!< CAP event 1
    CAP_EVENT_2 = 1U,   //!< CAP event 2
    CAP_EVENT_3 = 2U,   //!< CAP event 3
    CAP_EVENT_4 = 3U    //!< CAP event 4
}CAP_Events;

//*****************************************************************************
//
//! Values that can be passed to CAP_setSyncOutMode() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! sync out on the sync in signal and software force
    CAP_SYNC_OUT_SYNCI         = 0x00U,
    //! sync out on counter equals period
    CAP_SYNC_OUT_COUNTER_PRD   = 0x40U,
    //! Disable sync out signal
    CAP_SYNC_OUT_DISABLED      = 0x80U
}CAP_SyncOutMode;

//*****************************************************************************
//
//! Values that can be passed to CAP_setAPWMPolarity() as the \e polarity
//! parameter.
//
//*****************************************************************************
typedef enum
{
    CAP_APWM_ACTIVE_HIGH   = 0x000, //!< APWM is active high
    CAP_APWM_ACTIVE_LOW    = 0x400  //!< APWM is active low
}CAP_APWMPolarity;

//*****************************************************************************
//
//! Values that can be passed to CAP_setEventPolarity() as the \e polarity
//! parameter.
//
//*****************************************************************************
typedef enum
{
    CAP_EVNT_RISING_EDGE   = 0U, //!< Rising edge polarity
    CAP_EVNT_FALLING_EDGE  = 1U  //!< Falling edge polarity
}CAP_EventPolarity;

//*****************************************************************************
//
//! Values that can be passed to CAP_selectCAPInput() as the \e input
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! GPIO Input Crossbar output signal-1
    CAP_INPUT_INPUTXBAR1 = 0,
    //! GPIO Input Crossbar output signal-2
    CAP_INPUT_INPUTXBAR2 = 1,
    //! GPIO Input Crossbar output signal-3
    CAP_INPUT_INPUTXBAR3 = 2,
    //! GPIO Input Crossbar output signal-4
    CAP_INPUT_INPUTXBAR4 = 3,
    //! GPIO Input Crossbar output signal-5
    CAP_INPUT_INPUTXBAR5 = 4,
    //! GPIO Input Crossbar output signal-6
    CAP_INPUT_INPUTXBAR6 = 5,
    //! GPIO Input Crossbar output signal-7
    CAP_INPUT_INPUTXBAR7 = 6,
    //! GPIO Input Crossbar output signal-8
    CAP_INPUT_INPUTXBAR8 = 7,
    //! GPIO Input Crossbar output signal-9
    CAP_INPUT_INPUTXBAR9 = 8,
    //! GPIO Input Crossbar output signal-10
    CAP_INPUT_INPUTXBAR10 = 9,
    //! GPIO Input Crossbar output signal-11
    CAP_INPUT_INPUTXBAR11 = 10,
    //! GPIO Input Crossbar output signal-12
    CAP_INPUT_INPUTXBAR12 = 11,
    //! GPIO Input Crossbar output signal-13
    CAP_INPUT_INPUTXBAR13 = 12,
    //! GPIO Input Crossbar output signal-14
    CAP_INPUT_INPUTXBAR14 = 13,
    //! GPIO Input Crossbar output signal-15
    CAP_INPUT_INPUTXBAR15 = 14,
    //! GPIO Input Crossbar output signal-16
    CAP_INPUT_INPUTXBAR16 = 15,
    //! CANA INT0 Input
    CAP_INPUT_CANA_INT0 = 20,
    //! CANB INT0 Input
    CAP_INPUT_CANB_INT0 = 21,
    //! Delay clock for measurement
    CAP_INPUT_CAP_DELAY_CLOCK = 23,
    //! Output Xbar Output-1
    CAP_INPUT_OUTPUTXBAR1 = 24,
    //! Output Xbar Output-2
    CAP_INPUT_OUTPUTXBAR2 = 25,
    //! Output Xbar Output-3
    CAP_INPUT_OUTPUTXBAR3 = 26,
    //! Output Xbar Output-4
    CAP_INPUT_OUTPUTXBAR4 = 27,
    //! Output Xbar Output-5
    CAP_INPUT_OUTPUTXBAR5 = 28,
    //! Output Xbar Output-6
    CAP_INPUT_OUTPUTXBAR6 = 29,
    //! Output Xbar Output-7
    CAP_INPUT_OUTPUTXBAR7 = 30,
    //! Output Xbar Output-8
    CAP_INPUT_OUTPUTXBAR8 = 31,
    //! ADCC Event4
    CAP_INPUT_ADC_C_EVENT4 = 36,
    //! ADCC Event3
    CAP_INPUT_ADC_C_EVENT3 = 37,
    //! ADCC Event2
    CAP_INPUT_ADC_C_EVENT2 = 38,
    //! ADCC Event1
    CAP_INPUT_ADC_C_EVENT1 = 39,
    //! ADCB Event4
    CAP_INPUT_ADC_B_EVENT4 = 40,
    //! ADCB Event3
    CAP_INPUT_ADC_B_EVENT3 = 41,
    //! ADCB Event2
    CAP_INPUT_ADC_B_EVENT2 = 42,
    //! ADCB Event1
    CAP_INPUT_ADC_B_EVENT1 = 43,
    //! ADCA Event4
    CAP_INPUT_ADC_A_EVENT4 = 44,
    //! ADCA Event3
    CAP_INPUT_ADC_A_EVENT3 = 45,
    //! ADCA Event2
    CAP_INPUT_ADC_A_EVENT2 = 46,
    //! ADCA Event1
    CAP_INPUT_ADC_A_EVENT1 = 47,
    //! SDFM-1 Filter-1 Compare Low Trip
    CAP_INPUT_SDF1_FLT1_COMPARE_LOW = 64,
    //! SDFM-1 Filter-2 Compare Low Trip
    CAP_INPUT_SDF1_FLT2_COMPARE_LOW = 65,
    //! SDFM-1 Filter-3 Compare Low Trip
    CAP_INPUT_SDF1_FLT3_COMPARE_LOW = 66,
    //! SDFM-1 Filter-4 Compare Low Trip
    CAP_INPUT_SDF1_FLT4_COMPARE_LOW = 67,
    //! SDFM-1 Filter-1 Compare High Trip
    CAP_INPUT_SDF1_FLT1_COMPARE_HIGH = 80,
    //! SDFM-1 Filter-2 Compare High Trip
    CAP_INPUT_SDF1_FLT2_COMPARE_HIGH = 81,
    //! SDFM-1 Filter-3 Compare High Trip
    CAP_INPUT_SDF1_FLT3_COMPARE_HIGH = 82,
    //! SDFM-1 Filter-4 Compare High Trip
    CAP_INPUT_SDF1_FLT4_COMPARE_HIGH = 83,
    //! SDFM-1 Filter-1 Compare High Trip or Low Trip
    CAP_INPUT_SDF1_FLT1_COMPARE_HIGH_OR_LOW = 88,
    //! SDFM-1 Filter-2 Compare High Trip or Low Trip
    CAP_INPUT_SDF1_FLT2_COMPARE_HIGH_OR_LOW = 89,
    //! SDFM-1 Filter-3 Compare High Trip or Low Trip
    CAP_INPUT_SDF1_FLT3_COMPARE_HIGH_OR_LOW = 90,
    //! SDFM-1 Filter-4 Compare High Trip or Low Trip
    CAP_INPUT_SDF1_FLT4_COMPARE_HIGH_OR_LOW = 91,
    //! Compare Subsystem-1 Low Trip
    CAP_INPUT_COMP1_CTRIP_LOW = 96,
    //! Compare Subsystem-2 Low Trip
    CAP_INPUT_COMP2_CTRIP_LOW = 97,
    //! Compare Subsystem-3 Low Trip
    CAP_INPUT_COMP3_CTRIP_LOW = 98,
    //! Compare Subsystem-4 Low Trip
    CAP_INPUT_COMP4_CTRIP_LOW = 99,
    //! Compare Subsystem-5 Low Trip
    CAP_INPUT_COMP5_CTRIP_LOW = 100,
    //! Compare Subsystem-6 Low Trip
    CAP_INPUT_COMP6_CTRIP_LOW = 101,
    //! Compare Subsystem-7 Low Trip
    CAP_INPUT_COMP7_CTRIP_LOW = 102,
    //! Compare Subsystem-1 High Trip
    CAP_INPUT_COMP1_CTRIP_HIGH = 108,
    //! Compare Subsystem-2 High Trip
    CAP_INPUT_COMP2_CTRIP_HIGH = 109,
    //! Compare Subsystem-3 High Trip
    CAP_INPUT_COMP3_CTRIP_HIGH = 110,
    //! Compare Subsystem-4 High Trip
    CAP_INPUT_COMP4_CTRIP_HIGH = 111,
    //! Compare Subsystem-5 High Trip
    CAP_INPUT_COMP5_CTRIP_HIGH = 112,
    //! Compare Subsystem-6 High Trip
    CAP_INPUT_COMP6_CTRIP_HIGH = 113,
    //! Compare Subsystem-7 High Trip
    CAP_INPUT_COMP7_CTRIP_HIGH = 114,
    //! Compare Subsystem-1 High Trip or Low Trip
    CAP_INPUT_COMP1_CTRIP_HIGH_OR_LOW = 120,
    //! Compare Subsystem-2 High Trip or Low Trip
    CAP_INPUT_COMP2_CTRIP_HIGH_OR_LOW = 121,
    //! Compare Subsystem-3 High Trip or Low Trip
    CAP_INPUT_COMP3_CTRIP_HIGH_OR_LOW = 122,
    //! Compare Subsystem-4 High Trip or Low Trip
    CAP_INPUT_COMP4_CTRIP_HIGH_OR_LOW = 123,
    //! Compare Subsystem-5 High Trip or Low Trip
    CAP_INPUT_COMP5_CTRIP_HIGH_OR_LOW = 124,
    //! Compare Subsystem-6 High Trip or Low Trip
    CAP_INPUT_COMP6_CTRIP_HIGH_OR_LOW = 125,
    //! Compare Subsystem-7 High Trip or Low Trip
    CAP_INPUT_COMP7_CTRIP_HIGH_OR_LOW = 126,
    //! Default Reserved Input
    CAP_INPUT_RESERVED = 127,
}CAP_InputCaptureSignals;

//*****************************************************************************
//
//! \internal
//! Checks CAP base address.
//!
//! \param base specifies the CAP module base address.
//!
//! This function determines if an CAP module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool CAP_isBaseValid(uint32_t base)
{
    return(
           (base == CAP1_BASE) ||
           (base == CAP2_BASE) ||
           (base == CAP3_BASE) ||
           (base == CAP4_BASE) ||
           (base == CAP5_BASE) ||
           (base == CAP6_BASE) ||
           (base == CAP7_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Sets the input prescaler.
//!
//! \param base is the base address of the CAP module.
//! \param preScalerValue is the pre scaler value for CAP input
//!
//! This function divides the CAP input scaler. The pre scale value is
//! doubled inside the module. For example a preScalerValue of 5 will divide
//! the scaler by 10. Use a value of 1 to divide the pre scaler by 1.
//! The \e preScalerValue should be less than \b CAP_MAX_PRESCALER_VALUE.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_setEventPrescaler(uint32_t base,
                                          uint16_t preScalerValue)
{
    ASSERT(CAP_isBaseValid(base));

    ASSERT(preScalerValue < CAP_MAX_PRESCALER_VALUE);

    WRPRT_DISABLE;

    //
    // Write to PRESCALE bit
    //
    HWREGH(base + CAP_O_ECCTL1) =
                 ((HWREGH(base + CAP_O_ECCTL1) & (~CAP_ECCTL1_PRESCALE_M)) |
                  (preScalerValue << CAP_ECCTL1_PRESCALE_S));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the Capture event polarity.
//!
//! \param base is the base address of the CAP module.
//! \param event is the event number.
//! \param polarity is the polarity of the event.
//!
//! This function sets the polarity of a given event. The value of event
//! is between \b CAP_EVENT_1 and \b CAP_EVENT_4 inclusive corresponding to
//! the four available events.For each event the polarity value determines the
//! edge on which the capture is activated. For a rising edge use a polarity
//! value of \b CAP_EVNT_RISING_EDGE and for a falling edge use a polarity of
//! \b CAP_EVNT_FALLING_EDGE.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_setEventPolarity(uint32_t base,
                                         CAP_Events event,
                                         CAP_EventPolarity polarity)
{

    uint16_t shift;

    ASSERT(CAP_isBaseValid(base));

    shift = ((uint16_t)event) << 1U;

    WRPRT_DISABLE;

    //
    // Write to CAP1POL, CAP2POL, CAP3POL or CAP4POL
    //
    HWREGH(base + CAP_O_ECCTL1) =
                         (HWREGH(base + CAP_O_ECCTL1) & ~(1U << shift)) |
                         ((uint16_t)polarity << shift);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the capture mode.
//!
//! \param base is the base address of the CAP module.
//! \param mode is the capture mode.
//! \param event is the event number at which the counter stops or wraps.
//!
//! This function sets the CAP module to a continuous or one-shot mode.
//! The value of mode should be either \b CAP_CONTINUOUS_CAPTURE_MODE or
//! \b CAP_ONE_SHOT_CAPTURE_MODE corresponding to continuous or one-shot mode
//! respectively.
//!
//! The value of event determines the event number at which the counter stops
//! (in one-shot mode) or the counter wraps (in continuous mode). The value of
//! event should be between \b CAP_EVENT_1 and \b CAP_EVENT_4 corresponding
//! to the valid event numbers.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_setCaptureMode(uint32_t base,
                                       CAP_CaptureMode mode,
                                       CAP_Events event)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Write to CONT_ONESHT
    //
    HWREGH(base + CAP_O_ECCTL2) =
               ((HWREGH(base + CAP_O_ECCTL2) & (~CAP_ECCTL2_CONT_ONESHT)) |
                (uint16_t)mode);

    //
    // Write to STOP_WRAP
    //
    HWREGH(base + CAP_O_ECCTL2) =
               ((HWREGH(base + CAP_O_ECCTL2) & (~CAP_ECCTL2_STOP_WRAP_M)) |
                (((uint16_t)event) << CAP_ECCTL2_STOP_WRAP_S ));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Re-arms the CAP module.
//!
//! \param base is the base address of the CAP module.
//!
//! This function re-arms the CAP module.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_reArm(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Write to REARM bit
    //
    HWREGH(base + CAP_O_ECCTL2) |= CAP_ECCTL2_REARM;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables interrupt source.
//!
//! \param base is the base address of the CAP module.
//! \param intFlags is the interrupt source to be enabled.
//!
//! This function sets and enables CAP interrupt source. The following are
//! valid interrupt sources.
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - CAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - CAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - CAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_enableInterrupt(uint32_t base,
                                        uint16_t intFlags)
{
    ASSERT(CAP_isBaseValid(base));
    ASSERT((intFlags & ~(CAP_ISR_SOURCE_CAPTURE_EVENT_1 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_2 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_3 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_4 |
                         CAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         CAP_ISR_SOURCE_COUNTER_PERIOD |
                         CAP_ISR_SOURCE_COUNTER_COMPARE)) == 0U);


    WRPRT_DISABLE;

    //
    // Set bits in INTEN register
    //
    HWREGH(base + CAP_O_ECEINT) |= intFlags;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables interrupt source.
//!
//! \param base is the base address of the CAP module.
//! \param intFlags is the interrupt source to be disabled.
//!
//! This function clears and disables CAP interrupt source. The following are
//! valid interrupt sources.
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_1   - Event 1 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_2   - Event 2 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_3   - Event 3 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_4   - Event 4 generates interrupt
//!  - CAP_ISR_SOURCE_COUNTER_OVERFLOW  - Counter overflow generates interrupt
//!  - CAP_ISR_SOURCE_COUNTER_PERIOD    - Counter equal period generates
//!                                        interrupt
//!  - CAP_ISR_SOURCE_COUNTER_COMPARE   - Counter equal compare generates
//!                                        interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_disableInterrupt(uint32_t base,
                                         uint16_t intFlags)
{

    ASSERT(CAP_isBaseValid(base));
    ASSERT((intFlags & ~(CAP_ISR_SOURCE_CAPTURE_EVENT_1 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_2 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_3 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_4 |
                         CAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         CAP_ISR_SOURCE_COUNTER_PERIOD |
                         CAP_ISR_SOURCE_COUNTER_COMPARE)) == 0U);

    WRPRT_DISABLE;

    //
    // Clear bits in INTEN register
    //
    HWREGH(base + CAP_O_ECEINT) &= ~intFlags;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Returns the interrupt flag.
//!
//! \param base is the base address of the CAP module.
//!
//! This function returns the CAP interrupt flag. The following are valid
//! interrupt sources corresponding to the CAP interrupt flag.
//!
//! \return Returns the CAP interrupt that has occurred. The following are
//!  valid return values.
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_1   - Event 1 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_2   - Event 2 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_3   - Event 3 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_4   - Event 4 generates interrupt
//!  - CAP_ISR_SOURCE_COUNTER_OVERFLOW  - Counter overflow generates interrupt
//!  - CAP_ISR_SOURCE_COUNTER_PERIOD    - Counter equal period generates
//!                                        interrupt
//!  - CAP_ISR_SOURCE_COUNTER_COMPARE   - Counter equal compare generates
//!                                        interrupt
//!
//! \note - User can check if a combination of various interrupts have occurred
//!         by ORing the above return values.
//
//*****************************************************************************
static inline uint16_t CAP_getInterruptSource(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    //
    // Return contents of INTFLG register
    //
    return(HWREGH(base + CAP_O_ECFLG) & 0xFEU);
}

//*****************************************************************************
//
//! Returns the Global interrupt status flag.
//!
//! \param base is the base address of the CAP module.
//!
//! This function returns the CAP Global interrupt status flag.
//!
//! \return Returns true if there is a global CAP interrupt, false otherwise.
//
//*****************************************************************************
static inline bool CAP_getGlobalInterruptStatus(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    //
    // Return contents of Global interrupt bit
    //
    return((HWREGH(base + CAP_O_ECFLG) & 0x1U) == 0x1U);
}

//*****************************************************************************
//
//! Clears interrupt flag.
//!
//! \param base is the base address of the CAP module.
//! \param intFlags is the interrupt source.
//!
//! This function clears CAP interrupt flags. The following are valid
//! interrupt sources.
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - CAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - CAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - CAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_clearInterrupt(uint32_t base,
                                       uint16_t intFlags)
{
    ASSERT(CAP_isBaseValid(base));
    ASSERT((intFlags & ~(CAP_ISR_SOURCE_CAPTURE_EVENT_1 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_2 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_3 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_4 |
                         CAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         CAP_ISR_SOURCE_COUNTER_PERIOD |
                         CAP_ISR_SOURCE_COUNTER_COMPARE)) == 0U);

    //
    // Write to INTFLG register
    //
    HWREGH(base + CAP_O_ECCLR) = intFlags;
}

//*****************************************************************************
//
//! Clears global interrupt flag
//!
//! \param base is the base address of the CAP module.
//!
//! This function clears the global interrupt bit.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_clearGlobalInterrupt(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    //
    // Write to INT bit
    //
    HWREGH(base + CAP_O_ECCLR) = CAP_ECCLR_INT;
}

//*****************************************************************************
//
//! Forces interrupt source.
//!
//! \param base is the base address of the CAP module.
//! \param intFlags is the interrupt source.
//!
//! This function forces and enables CAP interrupt source. The following are
//! valid interrupt sources.
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - CAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - CAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - CAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - CAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_forceInterrupt(uint32_t base,
                                       uint16_t intFlags)
{
    ASSERT(CAP_isBaseValid(base));
    ASSERT((intFlags & ~(CAP_ISR_SOURCE_CAPTURE_EVENT_1 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_2 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_3 |
                         CAP_ISR_SOURCE_CAPTURE_EVENT_4 |
                         CAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         CAP_ISR_SOURCE_COUNTER_PERIOD |
                         CAP_ISR_SOURCE_COUNTER_COMPARE)) == 0U);

    WRPRT_DISABLE;

    //
    // Write to INTFRC register
    //
    HWREGH(base + CAP_O_ECFRC) = intFlags;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets CAP in Capture mode.
//!
//! \param base is the base address of the CAP module.
//!
//! This function sets the CAP module to operate in Capture mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_enableCaptureMode(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Clear CAP_APWM bit
    //
    HWREGH(base + CAP_O_ECCTL2) &= ~CAP_ECCTL2_CAP_APWM;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets CAP in APWM mode.
//!
//! \param base is the base address of the CAP module.
//!
//! This function sets the CAP module to operate in APWM mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_enableAPWMMode(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Set CAP_APWM bit
    //
    HWREGH(base + CAP_O_ECCTL2) |= CAP_ECCTL2_CAP_APWM;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables counter reset on an event.
//!
//! \param base is the base address of the CAP module.
//! \param event is the event number the time base gets reset.
//!
//! This function enables the base timer, TSCTR, to be reset on capture
//! event provided by the variable event. Valid inputs for event are
//! \b CAP_EVENT_1 to \b CAP_EVENT_4.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_enableCounterResetOnEvent(uint32_t base,
                                                  CAP_Events event)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Set CTRRST1,CTRRST2,CTRRST3 or CTRRST4 bits
    //
    HWREGH(base + CAP_O_ECCTL1) |= 1U << ((2U * (uint16_t)event) + 1U);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables counter reset on events.
//!
//! \param base is the base address of the CAP module.
//! \param event is the event number the time base gets reset.
//!
//! This function disables the base timer, TSCTR, from being reset on capture
//! event provided by the variable event. Valid inputs for event are
//! \b CAP_EVENT_1 to \b CAP_EVENT_4.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_disableCounterResetOnEvent(uint32_t base,
                                                   CAP_Events event)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Clear CTRRST1,CTRRST2,CTRRST3 or CTRRST4 bits
    //
    HWREGH(base + CAP_O_ECCTL1) &= ~(1U << ((2U * (uint16_t)event) + 1U));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables time stamp capture.
//!
//! \param base is the base address of the CAP module.
//!
//! This function enables time stamp count to be captured
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_enableTimeStampCapture(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Set CAPLDEN bit
    //
    HWREGH(base + CAP_O_ECCTL1) |= CAP_ECCTL1_CAPLDEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables time stamp capture.
//!
//! \param base is the base address of the CAP module.
//!
//! This function disables time stamp count to be captured
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_disableTimeStampCapture(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Clear CAPLDEN bit
    //
    HWREGH(base + CAP_O_ECCTL1) &= ~CAP_ECCTL1_CAPLDEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets a phase shift value count.
//!
//! \param base is the base address of the CAP module.
//! \param shiftCount is the phase shift value.
//!
//! This function writes a phase shift value to be loaded into the main time
//! stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_setPhaseShiftCount(uint32_t base, uint32_t shiftCount)
{
    ASSERT(CAP_isBaseValid(base));

    //
    // Write to CTRPHS register
    //
    HWREG(base + CAP_O_CTRPHS) = shiftCount;
}

//*****************************************************************************
//
//! Enable counter loading with phase shift value.
//!
//! \param base is the base address of the CAP module.
//!
//! This function enables loading of the counter with the value present in the
//! phase shift counter as defined by the CAP_setPhaseShiftCount() function.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_enableLoadCounter(uint32_t base)
{

    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Write to SYNCI_EN
    //
    HWREGH(base + CAP_O_ECCTL2) |= CAP_ECCTL2_SYNCI_EN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable counter loading with phase shift value.
//!
//! \param base is the base address of the CAP module.
//!
//! This function disables loading of the counter with the value present in the
//! phase shift counter as defined by the CAP_setPhaseShiftCount() function.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_disableLoadCounter(uint32_t base)
{

    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Write to SYNCI_EN
    //
    HWREGH(base + CAP_O_ECCTL2) &= ~CAP_ECCTL2_SYNCI_EN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Load time stamp counter
//!
//! \param base is the base address of the CAP module.
//!
//! This function forces the value in the phase shift counter register to be
//! loaded into Time stamp counter register.
//! Make sure to enable loading of Time stamp counter by calling
//! CAP_enableLoadCounter() function before calling this function.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_loadCounter(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Write to SWSYNC
    //
    HWREGH(base + CAP_O_ECCTL2) |= CAP_ECCTL2_SWSYNC;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Configures Sync out signal mode.
//!
//! \param base is the base address of the CAP module.
//! \param mode is the sync out mode.
//!
//! This function sets the sync out mode. Valid parameters for mode are:
//! - CAP_SYNC_OUT_SYNCI - Trigger sync out on sync-in event.
//! - CAP_SYNC_OUT_COUNTER_PRD - Trigger sync out when counter equals period.
//! - CAP_SYNC_OUT_DISABLED - Disable sync out.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_setSyncOutMode(uint32_t base,
                                       CAP_SyncOutMode mode)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Write to SYNCO_SEL
    //
     HWREGH(base + CAP_O_ECCTL2) =
                ((HWREGH(base + CAP_O_ECCTL2) & (~CAP_ECCTL2_SYNCO_SEL_M)) |
                 (uint16_t)mode);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Stops Time stamp counter.
//!
//! \param base is the base address of the CAP module.
//!
//! This function stops the time stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_stopCounter(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Clear TSCTRSTOP bit
    //
    HWREGH(base + CAP_O_ECCTL2) &= ~CAP_ECCTL2_TSCTRSTOP;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Starts Time stamp counter.
//!
//! \param base is the base address of the CAP module.
//!
//! This function starts the time stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_startCounter(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Set TSCTRSTOP bit
    //
    HWREGH(base + CAP_O_ECCTL2) |= CAP_ECCTL2_TSCTRSTOP;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set CAP APWM polarity.
//!
//! \param base is the base address of the CAP module.
//! \param polarity is the polarity of APWM
//!
//! This function sets the polarity of the CAP in APWM mode. Valid inputs for
//! polarity are:
//!  - CAP_APWM_ACTIVE_HIGH - For active high.
//!  - CAP_APWM_ACTIVE_LOW - For active low.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_setAPWMPolarity(uint32_t base,
                                        CAP_APWMPolarity polarity)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;
    HWREGH(base + CAP_O_ECCTL2) =
               ((HWREGH(base + CAP_O_ECCTL2) & ~CAP_ECCTL2_APWMPOL) |
                (uint16_t)polarity);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set CAP APWM period.
//!
//! \param base is the base address of the CAP module.
//! \param periodCount is the period count for APWM.
//!
//! This function sets the period count of the APWM waveform.
//! periodCount takes the actual count which is written to the register. The
//! user is responsible for converting the desired frequency or time into
//! the period count.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_setAPWMPeriod(uint32_t base, uint32_t periodCount)
{
    ASSERT(CAP_isBaseValid(base));

    //
    // Write to CAP1 register
    //
    HWREG(base + CAP_O_CAP1) = periodCount;
}

//*****************************************************************************
//
//! Set CAP APWM on or off time count.
//!
//! \param base is the base address of the CAP module.
//! \param compareCount is the on or off count for APWM.
//!
//! This function sets the on or off time count of the APWM waveform depending
//! on the polarity of the output. If the output , as set by
//! CAP_setAPWMPolarity(), is active high then compareCount determines the on
//! time. If the output is active low then compareCount determines the off
//! time. compareCount takes the actual count which is written to the register.
//! The user is responsible for converting the desired frequency or time into
//! the appropriate count value.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_setAPWMCompare(uint32_t base, uint32_t compareCount)
{
    ASSERT(CAP_isBaseValid(base));

    //
    // Write to CAP2 register
    //
    HWREG(base + CAP_O_CAP2) = compareCount;
}

//*****************************************************************************
//
//! Load CAP APWM shadow period.
//!
//! \param base is the base address of the CAP module.
//! \param periodCount is the shadow period count for APWM.
//!
//! This function sets the shadow period count of the APWM waveform.
//! periodCount takes the actual count which is written to the register. The
//! user is responsible for converting the desired frequency or time into
//! the period count.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_setAPWMShadowPeriod(uint32_t base,
                                            uint32_t periodCount)
{
    ASSERT(CAP_isBaseValid(base));

    //
    // Write to CAP3 register
    //
    HWREG(base + CAP_O_CAP3) = periodCount;
}

//*****************************************************************************
//
//! Set CAP APWM shadow on or off time count.
//!
//! \param base is the base address of the CAP module.
//! \param compareCount is the on or off count for APWM.
//!
//! This function sets the shadow on or off time count of the APWM waveform
//! depending on the polarity of the output. If the output , as set by
//! CAP_setAPWMPolarity() , is active high then compareCount determines the
//! on time. If the output is active low then compareCount determines the off
//! time. compareCount takes the actual count which is written to the register.
//! The user is responsible for converting the desired frequency or time into
//! the appropriate count value.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_setAPWMShadowCompare(uint32_t base,
                                             uint32_t compareCount)
{
    ASSERT(CAP_isBaseValid(base));

    //
    // Write to CAP4 register
    //
    HWREG(base + CAP_O_CAP4) = compareCount;
}

//*****************************************************************************
//
//! Returns the time base counter value.
//!
//! \param base is the base address of the CAP module.
//!
//! This function returns the time base counter value.
//!
//! \return Returns the time base counter value.
//
//*****************************************************************************
static inline uint32_t CAP_getTimeBaseCounter(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    //
    // Read the Time base counter value
    //
    return(HWREG(base + CAP_O_TSCTR));
}

//*****************************************************************************
//
//! Returns event time stamp.
//!
//! \param base is the base address of the CAP module.
//! \param event is the event number.
//!
//! This function returns the current time stamp count of the given event.
//! Valid values for event are \b CAP_EVENT_1 to \b CAP_EVENT_4.
//!
//! \return Event time stamp value or 0 if \e event is invalid.
//
//*****************************************************************************
static inline uint32_t CAP_getEventTimeStamp(uint32_t base, CAP_Events event)
{
    uint32_t count;

    ASSERT(CAP_isBaseValid(base));


    switch(event)
    {
        case CAP_EVENT_1:

            //
            // Read CAP1 register
            //
            count = HWREG(base + CAP_O_CAP1);
        break;

        case CAP_EVENT_2:
            //
            // Read CAP2 register
            //
            count = HWREG(base + CAP_O_CAP2);
        break;

        case CAP_EVENT_3:

            //
            // Read CAP3 register
            //
            count = HWREG(base + CAP_O_CAP3);
        break;

        case CAP_EVENT_4:

            //
            // Read CAP4 register
            //
            count = HWREG(base + CAP_O_CAP4);
        break;

        default:

            //
            // Invalid event parameter
            //
            count = 0U;
        break;
    }

    return(count);
}

//*****************************************************************************
//
//! Select CAP input.
//!
//! \param base is the base address of the CAP module.
//! \param input is the CAP input signal.
//!
//! This function selects the CAP input signal.
//!
//! Please refer to the ::CAP_InputCaptureSignals Enum for the valid values
//! to be passed to \e input parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_selectCAPInput(uint32_t base,
                                        CAP_InputCaptureSignals input)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Write to CTRL0 register
    //
    HWREGH(base + CAP_O_ECCTL0) =
                ((HWREGH(base + CAP_O_ECCTL0) & ~CAP_ECCTL0_INPUTSEL_M) |
                 (uint16_t)input);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Resets CAP counters and flags.
//!
//! \param base is the base address of the CAP module.
//!
//! This function resets the main counter (TSCTR register), event filter,
//! modulo counter, capture events and counter overflow flags
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_resetCounters(uint32_t base)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Write to CTRL2 register
    //
    HWREGH(base + CAP_O_ECCTL2) |= CAP_ECCTL2_CTRFILTRESET;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the CAP DMA source.
//!
//! \param base is the base address of the CAP module.
//! \param event is the CAP event for the DMA
//!
//! This function sets the CAP event source for the DMA trigger.
//! Valid values for \e event are \b CAP_EVENT_1 to \b CAP_EVENT_4.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAP_setDMASource(uint32_t base, CAP_Events event)
{
    ASSERT(CAP_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Write to CTRL2 register
    //
    HWREGH(base + CAP_O_ECCTL2) =
               ((HWREGH(base + CAP_O_ECCTL2) & ~CAP_ECCTL2_DMAEVTSEL_M) |
                ((uint16_t)event << CAP_ECCTL2_DMAEVTSEL_S));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Return the Modulo counter status.
//!
//! \param base is the base address of the CAP module.
//!
//! This function returns the modulo counter status, indicating which register
//! gets loaded on the next capture event.
//!
//! \return Returns an \b CAP_EVENT_n value indicating that CAPn is the
//! register to be loaded on the next event.
//
//*****************************************************************************
static inline CAP_Events CAP_getModuloCounterStatus(uint32_t base)
{
    uint16_t counterStatusValue;

    ASSERT(CAP_isBaseValid(base));

    counterStatusValue = (((HWREGH(base + CAP_O_ECCTL2) &
                          CAP_ECCTL2_MODCNTRSTS_M) >>
                         CAP_ECCTL2_MODCNTRSTS_S));

    //
    // Read MODCNTRSTS bit
    //
    return((CAP_Events)(counterStatusValue));
}

//*****************************************************************************
//
//! Configures emulation mode.
//!
//! \param base is the base address of the CAP module.
//! \param mode is the emulation mode.
//!
//! This function configures the CAP counter, TSCTR,  to the desired emulation
//! mode when emulation suspension occurs. Valid inputs for mode are:
//! - CAP_EMULATION_STOP  - Counter is stopped immediately.
//! - CAP_EMULATION_RUN_TO_ZERO - Counter runs till it reaches 0.
//! - CAP_EMULATION_FREE_RUN - Counter is not affected.
//!
//! \return None.
//
//*****************************************************************************
extern void CAP_setEmulationMode(uint32_t base, CAP_EmulationMode mode);

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

#endif // CAP_H
