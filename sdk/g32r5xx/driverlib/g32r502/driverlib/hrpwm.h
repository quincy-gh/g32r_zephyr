//#############################################################################
//
// FILE:    hrpwm.h
//
// TITLE:   G32R502 HRPWM Driver
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
// 1. Some comments, module names, macro definitions, register names
//
//###########################################################################

#ifndef HRPWM_H
#define HRPWM_H

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
//! \addtogroup hrpwm_api HRPWM
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_hrpwm.h"
#include "cpu.h"
#include "debug.h"
#include "pwm.h"
#include "hrpwm.h"

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setMEPEdgeSelect(),
//! HRPWM_setMEPControlMode(), HRPWM_setCounterCompareShadowLoadEvent()
//! as the \e channel parameter.
//
//*****************************************************************************
typedef enum
{
    HRPWM_CHANNEL_A = 0, //!< HRPWM A
    HRPWM_CHANNEL_B = 8  //!< HRPWM B
} HRPWM_Channel;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setMEPEdgeSelect() as the \e mepEdgeMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! HRPWM is disabled
    HRPWM_MEP_CTRL_DISABLE = 0,
    //! MEP controls rising edge
    HRPWM_MEP_CTRL_RISING_EDGE = 1,
    //! MEP controls falling edge
    HRPWM_MEP_CTRL_FALLING_EDGE = 2,
    //! MEP controls both rising and falling edge
    HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE = 3
} HRPWM_MEPEdgeMode;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setHRMEPCtrlMode() as the \e
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! CCOMPAHR/CCOMPBHR or TBPRDHR controls MEP edge
    HRPWM_MEP_DUTY_PERIOD_CTRL = 0,
    //! TBPOFHR controls MEP edge
    HRPWM_MEP_PHASE_CTRL = 1
} HRPWM_MEPCtrlMode;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setCounterCompareShadowLoadEvent(),
//! HRPWM_setRisingEdgeDelayLoadMode() and HRPWM_setFallingEdgeDelayLoadMode
//! as the \e loadEvent parameter.
//
//*****************************************************************************
typedef enum
{
    //! load when counter equals zero
    HRPWM_LOAD_ON_CNTR_ZERO = 0,
    //! load when counter equals period
    HRPWM_LOAD_ON_CNTR_PERIOD = 1,
    //! load when counter equals zero or period
    HRPWM_LOAD_ON_CNTR_ZERO_PERIOD = 2
} HRPWM_LoadMode;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setChannelBOutputPath() as the \e
//! outputOnB parameter.
//
//*****************************************************************************
typedef enum
{
    HRPWM_OUTPUT_ON_B_NORMAL = 0, //!< PWMxB output is normal.
    HRPWM_OUTPUT_ON_B_INV_A  = 1  //!< PWMxB output is inverted
                                  //!< version of PWMxA signal
} HRPWM_ChannelBOutput;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setSyncPulseSource() as the \e
//! syncPulseSource parameter.
//
//*****************************************************************************
typedef enum
{
    //! Counter equals Period
    HRPWM_PWMSYNC_SOURCE_PERIOD = 0,
    //! Counter equals zero
    HRPWM_PWMSYNC_SOURCE_ZERO = 1,
    //! Counter equals COMPC when counting up
    HRPWM_PWMSYNC_SOURCE_COMPC_UP = 4,
    //! Counter equals COMPC when counting down
    HRPWM_PWMSYNC_SOURCE_COMPC_DOWN = 5,
    //! Counter equals COMPD when counting up
    HRPWM_PWMSYNC_SOURCE_COMPD_UP = 6,
    //! Counter equals COMPD when counting down
    HRPWM_PWMSYNC_SOURCE_COMPD_DOWN = 7
} HRPWM_SyncPulseSource;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setCounterCompareValue() as the \e
//! compModule parameter.
//
//*****************************************************************************
typedef enum
{
    HRPWM_COUNTER_COMPARE_A = 0, //!< counter compare A
    HRPWM_COUNTER_COMPARE_B = 4  //!< counter compare B
} HRPWM_CounterCompareModule;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_setDeadbandMEPEdgeSelect() as the \e
//! mepDBEdge.
//
//*****************************************************************************
typedef enum
{
    //! HRPWM is disabled
    HRPWM_DB_MEP_CTRL_DISABLE = 0,
    //! MEP controls Rising Edge Delay
    HRPWM_DB_MEP_CTRL_RED = 1,
    //! MEP controls Falling Edge Delay
    HRPWM_DB_MEP_CTRL_FED = 2,
    //! MEP controls both Falling and Rising edge delay
    HRPWM_DB_MEP_CTRL_RED_FED = 3
} HRPWM_MEPDeadBandEdgeMode;

//*****************************************************************************
//
//! Values that can be passed to HRPWM_lockRegisters() as the \e registerGroup
//! parameter.
//
//*****************************************************************************
typedef enum
{
    HRPWM_REGISTER_GROUP_HRPWM = 0x1,           //!< HRPWM register group
    HRPWM_REGISTER_GROUP_GLOBAL_LOAD = 0x2,     //!< Global load register group
    HRPWM_REGISTER_GROUP_TRIP_ZONE = 0x4,       //!< Trip zone register group
    HRPWM_REGISTER_GROUP_TRIP_ZONE_CLEAR = 0x8, //!< Trip zone clear group
    HRPWM_REGISTER_GROUP_DIGITAL_COMPARE = 0x10 //!< Digital compare group
} HRPWM_LockRegisterGroup;

//*****************************************************************************
//
// Functions APIs shared with PWM module
//
//*****************************************************************************

//
// Time Base Sub Module related APIs
//
#define HRPWM_setTimeBaseCounter                 PWM_setTimeBaseCounter
#define HRPWM_setCountModeAfterSync              PWM_setCountModeAfterSync
#define HRPWM_setClockPrescaler                  PWM_setClockPrescaler
#define HRPWM_swForceSyncPulse                   PWM_forceSyncPulse
#define HRPWM_setSyncOutPulseMode                PWM_setSyncOutPulseMode
#define HRPWM_setPeriodLoadMode                  PWM_setPeriodLoadMode
#define HRPWM_setTimeBaseCounterMode             PWM_setTimeBaseCounterMode
#define HRPWM_selectPeriodLoadEvent              PWM_selectPeriodLoadEvent
#define HRPWM_enableOneShotSync                  PWM_enableOneShotSync
#define HRPWM_disableOneShotSync                 PWM_disableOneShotSync
#define HRPWM_startOneShotSync                   PWM_startOneShotSync
#define HRPWM_getTimeBaseCounterOverflowStatus                                \
                                          PWM_getTimeBaseCounterOverflowStatus
#define HRPWM_clearTimeBaseCounterOverflowEvent                               \
                                         PWM_clearTimeBaseCounterOverflowEvent
#define HRPWM_getSyncStatus                      PWM_getSyncStatus
#define HRPWM_clearSyncEvent                     PWM_clearSyncEvent
#define HRPWM_getTimeBaseCounterDirection     PWM_getTimeBaseCounterDirection
#define HRPWM_setupPWMLinks                     PWM_setupPWMLinks
#define HRPWM_setCounterCompareShadowLoadMode                                 \
                                           PWM_setCounterCompareShadowLoadMode
#define HRPWM_disableCounterCompareShadowLoadMode                             \
                                       PWM_disableCounterCompareShadowLoadMode
#define HRPWM_getCounterCompareShadowStatus                                   \
                                            PWM_getCounterCompareShadowStatus

//
// Action Qualifier module related APIs
//
#define HRPWM_setActionQualifierShadowLoadMode                                \
                                       PWM_setActionQualifierShadowLoadMode
#define HRPWM_disableActionQualifierShadowLoadMode                            \
                                      PWM_disableActionQualifierShadowLoadMode
#define HRPWM_setActionQualifierT1TriggerSource                               \
                                        PWM_setActionQualifierT1TriggerSource
#define HRPWM_setActionQualifierT2TriggerSource                               \
                                        PWM_setActionQualifierT2TriggerSource
#define HRPWM_setActionQualifierAction           PWM_setActionQualifierAction
#define HRPWM_setActionQualifierContSWForceShadowMode                         \
                                  PWM_setActionQualifierContSWForceShadowMode
#define HRPWM_setActionQualifierContSWForceAction                             \
                                  PWM_setActionQualifierContSWForceAction
/* HRPWM_setActionQualifierSwAction is kept for compatibility,
use HRPWM_setActionQualifierSWAction*/
#define HRPWM_setActionQualifierSwAction        PWM_setActionQualifierSwAction
#define HRPWM_setActionQualifierSWAction        PWM_setActionQualifierSWAction
/* HRPWM_forceActionQualifierSwAction  is kept for compatibility,
use HRPWM_forceActionQualifierSWAction*/
#define HRPWM_forceActionQualifierSwAction    PWM_forceActionQualifierSwAction
#define HRPWM_forceActionQualifierSWAction    PWM_forceActionQualifierSWAction
//
// Dead Band Module related APIs
//
#define HRPWM_setDeadBandOutputSwapMode          PWM_setDeadBandOutputSwapMode
#define HRPWM_setDeadBandDelayMode               PWM_setDeadBandDelayMode
#define HRPWM_setDeadBandDelayPolarity           PWM_setDeadBandDelayPolarity
#define HRPWM_setRisingEdgeDeadBandDelayInput                                 \
                                         PWM_setRisingEdgeDeadBandDelayInput
#define HRPWM_setFallingEdgeDeadBandDelayInput                                \
                                         PWM_setFallingEdgeDeadBandDelayInput
#define HRPWM_setDeadBandControlShadowLoadMode                                \
                                         PWM_setDeadBandControlShadowLoadMode
#define HRPWM_disableDeadBandControlShadowLoadMode                            \
                                      PWM_disableDeadBandControlShadowLoadMode
#define HRPWM_setRisingEdgeDelayCountShadowLoadMode                           \
                                   PWM_setRisingEdgeDelayCountShadowLoadMode
#define HRPWM_disableRisingEdgeDelayCountShadowLoadMode                       \
                                 PWM_disableRisingEdgeDelayCountShadowLoadMode
#define HRPWM_setFallingEdgeDelayCountShadowLoadMode                          \
                                   PWM_setFallingEdgeDelayCountShadowLoadMode
#define HRPWM_disableFallingEdgeDelayCountShadowLoadMode                      \
                                PWM_disableFallingEdgeDelayCountShadowLoadMode
#define HRPWM_setDeadBandCounterClock            PWM_setDeadBandCounterClock
#define HRPWM_setRisingEdgeDelayCount            PWM_setRisingEdgeDelayCount
#define HRPWM_setFallingEdgeDelayCount           PWM_setFallingEdgeDelayCount

//
// Chopper module related APIs
//
#define HRPWM_enableChopper                      PWM_enableChopper
#define HRPWM_disableChopper                     PWM_disableChopper
#define HRPWM_setChopperDutyCycle                PWM_setChopperDutyCycle
#define HRPWM_setChopperFreq                     PWM_setChopperFreq
#define HRPWM_setChopperFirstPulseWidt           PWM_setChopperFirstPulseWidth

//
// Trip Zone module related APIs
//
#define HRPWM_enableTripZoneSignals              PWM_enableTripZoneSignals
#define HRPWM_disableTripZoneSignals             PWM_disableTripZoneSignals
#define HRPWM_setTripZoneDigitalCompareEventCondition                         \
                                   PWM_setTripZoneDigitalCompareEventCondition
#define HRPWM_enableTripZoneAdvAction             PWM_enableTripZoneAdvAction
#define HRPWM_disableTripZoneAdvAction            PWM_disableTripZoneAdvAction
#define HRPWM_setTripZoneAction                   PWM_setTripZoneAction
#define HRPWM_setTripZoneAdvAction                PWM_setTripZoneAdvAction
#define HRPWM_setTripZoneAdvDigitalCompareActionA                             \
                                   PWM_setTripZoneAdvDigitalCompareActionA
#define HRPWM_setTripZoneAdvDigitalCompareActionB                             \
                                   PWM_setTripZoneAdvDigitalCompareActionB
#define HRPWM_enableTripZoneInterrupt           PWM_enableTripZoneInterrupt
#define HRPWM_disableTripZoneInterrupt          PWM_disableTripZoneInterrupt

//
// HRPWM_getTripZoneInterruptStatus API define is obsolete please use
// HRPWM_getTripZoneFlagStatus going forward.
//
#define HRPWM_getTripZoneInterruptStatus        PWM_getTripZoneFlagStatus
#define HRPWM_getTripZoneFlagStatus             PWM_getTripZoneFlagStatus

//
// HRPWM_getCycleByCycleTripZoneInterruptStatus API define is obsolete
// please use HRPWM_getCycleByCycleTripZoneFlagStatus going forward.
//
#define HRPWM_getCycleByCycleTripZoneInterruptStatus                          \
                                   HRPWM_getCycleByCycleTripZoneFlagStatus
#define HRPWM_getCycleByCycleTripZoneFlagStatus                               \
                                   PWM_getCycleByCycleTripZoneFlagStatus

//
// HRPWM_getOneShotTripZoneInterruptStatus is obsolete please use
// HRPWM_getOneShotTripZoneFlagStatus going forward.
//
#define HRPWM_getOneShotTripZoneInterruptStatus                               \
                                   HRPWM_getOneShotTripZoneFlagStatus
#define HRPWM_getOneShotTripZoneFlagStatus                                    \
                                   PWM_getOneShotTripZoneFlagStatus
#define HRPWM_selectCycleByCycleTripZoneClearEvent                            \
                                   PWM_selectCycleByCycleTripZoneClearEvent

//
// HRPWM_clearTripZoneInterruptFlag is obsolete please use
// HRPWM_clearTripZoneFlag going forward.
//
#define HRPWM_clearTripZoneInterruptFlag        HRPWM_clearTripZoneFlag
#define HRPWM_clearTripZoneFlag                 PWM_clearTripZoneFlag

//
// HRPWM_clearCycleByCycleTripZoneInterruptFlag is obsolete please use
// HRPWM_clearCycleByCycleTripZoneFlag going forward.
//
#define HRPWM_clearCycleByCycleTripZoneInterruptFlag                          \
                                   HRPWM_clearCycleByCycleTripZoneFlag
#define HRPWM_clearCycleByCycleTripZoneFlag                                   \
                                   PWM_clearCycleByCycleTripZoneFlag

//
// HRPWM_clearOneShotTripZoneInterruptFlag is obsolete please use
// HRPWM_clearOneShotTripZoneFlag going forward.
//
#define HRPWM_clearOneShotTripZoneInterruptFlag                               \
                                   HRPWM_clearOneShotTripZoneFlag
#define HRPWM_clearOneShotTripZoneFlag                                        \
                                   PWM_clearOneShotTripZoneFlag
#define HRPWM_forceTripZoneEvent                  PWM_forceTripZoneEvent

//
// Event Trigger related APIs
//
#define HRPWM_enableInterrupt                     PWM_enableInterrupt
#define HRPWM_disableInterrupt                    PWM_disableInterrupt
#define HRPWM_setInterruptSource                  PWM_setInterruptSource
#define HRPWM_setInterruptEventCount              PWM_setInterruptEventCount
#define HRPWM_getEventTriggerInterruptStatus                                  \
                                           PWM_getEventTriggerInterruptStatus
#define HRPWM_clearEventTriggerInterruptFlag                                  \
                                           PWM_clearEventTriggerInterruptFlag
#define HRPWM_enableInterruptEventCountInit                                   \
                                           PWM_enableInterruptEventCountInit
#define HRPWM_disableInterruptEventCountInit                                  \
                                            PWM_disableInterruptEventCountInit
#define HRPWM_forceInterruptEventCountInit                                    \
                                              PWM_forceInterruptEventCountInit
#define HRPWM_setInterruptEventCountInitValue                                 \
                                           PWM_setInterruptEventCountInitValue
#define HRPWM_getInterruptEventCount            PWM_getInterruptEventCount
#define HRPWM_forceEventTriggerInterrupt        PWM_forceEventTriggerInterrupt

//
// ADC SOC configuration related APIs
//
#define HRPWM_enableADCTrigger                  PWM_enableADCTrigger
#define HRPWM_disableADCTrigger                 PWM_disableADCTrigger
#define HRPWM_setADCTriggerSource               PWM_setADCTriggerSource
#define HRPWM_setADCTriggerEventPrescale        PWM_setADCTriggerEventPrescale
#define HRPWM_getADCTriggerFlagStatus           PWM_getADCTriggerFlagStatus
#define HRPWM_clearADCTriggerFlag               PWM_clearADCTriggerFlag
#define HRPWM_enableADCTriggerEventCountInit                                  \
                                          PWM_enableADCTriggerEventCountInit
#define HRPWM_disableADCTriggerEventCountInit                                 \
                                          PWM_disableADCTriggerEventCountInit
#define HRPWM_forceADCTriggerEventCountInit                                   \
                                          PWM_forceADCTriggerEventCountInit
#define HRPWM_setADCTriggerEventCountInitValue                                \
                                         PWM_setADCTriggerEventCountInitValue
#define HRPWM_getADCTriggerEventCount             PWM_getADCTriggerEventCount
#define HRPWM_forceADCTrigger                     PWM_forceADCTrigger

//
// Digital Compare Module related APIs
//
#define HRPWM_selectDigitalCompareTripInput                                   \
                                            PWM_selectDigitalCompareTripInput
#define HRPWM_enableDigitalCompareBlankingWindow                              \
                                   PWM_enableDigitalCompareBlankingWindow
#define HRPWM_disableDigitalCompareBlankingWindow                             \
                                   PWM_disableDigitalCompareBlankingWindow
#define HRPWM_enableDigitalCompareWindowInverseMode                           \
                                   PWM_enableDigitalCompareWindowInverseMode
#define HRPWM_disableDigitalCompareWindowInverseMode                          \
                                   PWM_disableDigitalCompareWindowInverseMode
#define HRPWM_setDigitalCompareBlankingEvent                                  \
                                        PWM_setDigitalCompareBlankingEvent
#define HRPWM_setDigitalCompareFilterInput                                    \
                                        PWM_setDigitalCompareFilterInput
#define HRPWM_setDigitalCompareWindowOffset                                   \
                                        PWM_setDigitalCompareWindowOffset
#define HRPWM_setDigitalCompareWindowLength                                   \
                                         PWM_setDigitalCompareWindowLength
#define HRPWM_getDigitalCompareBlankingWindowOffsetCount                      \
                               PWM_getDigitalCompareBlankingWindowOffsetCount
#define HRPWM_getDigitalCompareBlankingWindowLengthCount                      \
                               PWM_getDigitalCompareBlankingWindowLengthCount
#define HRPWM_setDigitalCompareEventSource                                    \
                                            PWM_setDigitalCompareEventSource
#define HRPWM_setDigitalCompareEventSyncMode                                  \
                                           PWM_setDigitalCompareEventSyncMode
#define HRPWM_enableDigitalCompareADCTrigger                                  \
                                           PWM_enableDigitalCompareADCTrigger
#define HRPWM_disableDigitalCompareADCTrigger                                 \
                                          PWM_disableDigitalCompareADCTrigger
#define HRPWM_enableDigitalCompareSyncEvent                                   \
                                            PWM_enableDigitalCompareSyncEvent
#define HRPWM_disableDigitalCompareSyncEvent                                  \
                                           PWM_disableDigitalCompareSyncEvent
#define HRPWM_enableDigitalCompareCounterCapture                              \
                                PWM_enableDigitalCompareCounterCapture
#define HRPWM_disableDigitalCompareCounterCapture                             \
                                PWM_disableDigitalCompareCounterCapture
#define HRPWM_setDigitalCompareCounterShadowMode                              \
                                PWM_setDigitalCompareCounterShadowMode
#define HRPWM_getDigitalCompareCaptureStatus                                  \
                                 PWM_getDigitalCompareCaptureStatus
#define HRPWM_getDigitalCompareCaptureCount                                   \
                                 PWM_getDigitalCompareCaptureCount
#define HRPWM_enableDigitalCompareTripCombinationInput                        \
                                PWM_enableDigitalCompareTripCombinationInput
#define HRPWM_disableDigitalCompareTripCombinationInput                       \
                                PWM_disableDigitalCompareTripCombinationInput

//
// Valley switching related APIs
//
#define HRPWM_enableValleyCapture             PWM_enableValleyCapture
#define HRPWM_disableValleyCapture            PWM_disableValleyCapture
#define HRPWM_startValleyCapture              PWM_startValleyCapture
#define HRPWM_setValleyTriggerSource          PWM_setValleyTriggerSource
#define HRPWM_setValleyTriggerEdgeCounts      PWM_setValleyTriggerEdgeCounts
#define HRPWM_enableValleyHWDelay             PWM_enableValleyHWDelay
#define HRPWM_disableValleyHWDelay            PWM_disableValleyHWDelay
#define HRPWM_setValleySWDelayValue           PWM_setValleySWDelayValue
#define HRPWM_setValleyDelayDivider           PWM_setValleyDelayDivider
#define HRPWM_getValleyEdgeStatus             PWM_getValleyEdgeStatus
#define HRPWM_getValleyCount                  PWM_getValleyCount
#define HRPWM_getValleyHWDelay                PWM_getValleyHWDelay

//
// Global Load feature related APIs
//
#define HRPWM_enableGlobalLoad                PWM_enableGlobalLoad
#define HRPWM_disableGlobalLoad               PWM_disableGlobalLoad
#define HRPWM_setGlobalLoadTrigger            PWM_setGlobalLoadTrigger
#define HRPWM_setGlobalLoadEventPrescale      PWM_setGlobalLoadEventPrescale
#define HRPWM_getGlobalLoadEventCount         PWM_getGlobalLoadEventCount
#define HRPWM_disableGlobalLoadOneShotMode    PWM_disableGlobalLoadOneShotMode
#define HRPWM_enableGlobalLoadOneShotMode     PWM_enableGlobalLoadOneShotMode
#define HRPWM_setGlobalLoadOneShotLatch       PWM_setGlobalLoadOneShotLatch
#define HRPWM_forceGlobalLoadOneShotEvent     PWM_forceGlobalLoadOneShotEvent
#define HRPWM_enableGlobalLoadRegisters       PWM_enableGlobalLoadRegisters
#define HRPWM_disableGlobalLoadRegisters      PWM_disableGlobalLoadRegisters
#define HRPWM_setEmulationMode                PWM_setEmulationMode

//*****************************************************************************
//
// Prototypes for the API.
//
//*****************************************************************************

//*****************************************************************************
//
//! \internal
//! Checks HRPWM base address.
//!
//! \param base specifies the HRPWM module base address.
//!
//! This function determines if an HRPWM module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool HRPWM_isBaseValid(uint32_t base)
{
    return((base == PWM1_BASE) || (base == PWM2_BASE) ||
           (base == PWM3_BASE) || (base == PWM4_BASE) ||
           (base == PWM5_BASE) || (base == PWM6_BASE) ||
           (base == PWM7_BASE));
}
#endif
//*****************************************************************************
//
//! Sets the consolidated phase shift value in high resolution mode.
//!
//! \param base is the base address of the PWM module.
//! \param phaseCount is the consolidated phase shift count value.
//!
//! This function sets the consolidated phase shift value, that is, both TBPOF
//! and TBPOFHR values are configured together.
//!
//! Call PWM_enablePhaseShiftLoad & HRPWM_enableHRPhaseShiftLoad() functions
//! to enable loading of the phaseCount in high resolution mode.
//!
//! \b Note: phaseCount is a 24-bit value.
//! \b Note: For configuring TBPOF = 0x3C, TBPOFHR = 0x2;
//!          phaseCount = 0x3C02
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setPhaseShift(uint32_t base, uint32_t phaseCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(phaseCount < 0x1000000U);

    //
    // Write to TBPOF:TBPOFHR bits
    //
    HWREG(base + HRPWM_O_TBPOF) = phaseCount << 8U;
}

//*****************************************************************************
//
//! Sets only the high resolution phase shift value.
//!
//! \param base is the base address of the PWM module.
//! \param hrPhaseCount is the high resolution phase shift count value.
//!
//! This function sets only the high resolution phase shift(TBPOFHR) value.
//! Call the HRPWM_enableHRPhaseShiftLoad() function to enable loading of
//! the hrPhaseCount.
//!
//! \b Note: hrPhaseCount is an 8-bit value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setHiResPhaseShiftOnly(uint32_t base, uint16_t hrPhaseCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(hrPhaseCount < 256U);

    //
    // Write to TBPOFHR bits
    //
    HWREGH(base + HRPWM_O_TBPOF) = hrPhaseCount << 8U;
}

//*****************************************************************************
//
//! Sets the consolidated period of time base counter used in HR mode.
//!
//! \param base is the base address of the PWM module.
//! \param periodCount is the consolidated period count value.
//!
//! This function sets the consolidated period of time base counter value
//! (TBPRD:TBPRDHR) required in high resolution mode.
//!
//! User should map the desired period or frequency of the waveform into
//! the correct periodCount.
//!
//! \b Note: periodCount is a 24 bit value.
//! \b Note: For configuring TBPRD = 0x3C, TBPRDHR = 0xA;
//!          periodCount = 0x3C0A
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setTimeBasePeriod(uint32_t base, uint32_t periodCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(periodCount < 0x1000000U);

    //
    // Write to TBPRD:TBPRDHR bits
    //
    HWREG(base + HRPWM_O_TBPRDHR) = periodCount << 8U;
}

//*****************************************************************************
//
//! Sets only the high resolution time base counter.
//!
//! \param base is the base address of the PWM module.
//! \param hrPeriodCount is the high resolution period count value.
//!
//! This function sets only the high resolution time base counter(TBPRDHR)
//! value.
//!
//! User should map the desired period or frequency of the waveform into
//! the correct hrPeriodCount.
//!
//! \b Note: hrPeriodCount is an 8-bit value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setHiResTimeBasePeriodOnly(uint32_t base, uint16_t hrPeriodCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(hrPeriodCount < 256U);

    //
    // Write to TBPRDHR bits
    //
    HWREGH(base + HRPWM_O_TBPRDHR) = hrPeriodCount << 8U;
}

//*****************************************************************************
//
//! Gets the consolidated time base period count used in HR mode
//!
//! \param base is the base address of the PWM module.
//!
//! This function gets the consolidated time base period(TBPRD:TBPRDHR) value
//! used in high resolution mode.
//!
//! \return The consolidated time base period count value.
//
//*****************************************************************************
static inline uint32_t
HRPWM_getTimeBasePeriod(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Read from TBPRD:TBPRDHR bit
    //
    return(HWREG(base + HRPWM_O_TBPRDHR) >> 8U);
}

//*****************************************************************************
//
//! Gets the only the high resolution time base period count.
//!
//! \param base is the base address of the PWM module.
//!
//! This function gets only the high resolution time base period(TBPRDHR) value.
//!
//! \return The high resolution time base period count value.
//
//*****************************************************************************
static inline uint16_t
HRPWM_getHiResTimeBasePeriodOnly(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Read from TBPRDHR bit
    //
    return(HWREGH(base + HRPWM_O_TBPRDHR) >> 8U);
}

//*****************************************************************************
//
//! Sets the high resolution edge controlled by MEP (Micro Edge Positioner).
//!
//! \param base is the base address of the PWM module.
//! \param channel is high resolution period module.
//! \param mepEdgeMode edge of the PWM that is controlled by MEP (Micro Edge
//!        Positioner).
//!
//! This function sets the edge of the PWM that is controlled by MEP (Micro
//! Edge Positioner). Valid values for the parameters are:
//!  - channel
//!      - HRPWM_CHANNEL_A  - HRPWM A
//!      - HRPWM_CHANNEL_B  - HRPWM B
//!  - mepEdgeMode
//!      - HRPWM_MEP_CTRL_DISABLE                 - HRPWM is disabled
//!      - HRPWM_MEP_CTRL_RISING_EDGE             - MEP (Micro Edge Positioner)
//!                                                 controls rising edge.
//!      - HRPWM_MEP_CTRL_FALLING_EDGE            - MEP (Micro Edge Positioner)
//!                                                 controls falling edge.
//!      - HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE - MEP (Micro Edge Positioner)
//!                                                 controls both edges.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setMEPEdgeSelect(uint32_t base, HRPWM_Channel channel,
                       HRPWM_MEPEdgeMode mepEdgeMode)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the edge mode
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRPCFG) =
             ((HWREGH(base + HRPWM_O_HRPCFG) & ~(0x3U << (uint16_t)channel )) |
              ((uint16_t)mepEdgeMode << (uint16_t)channel));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the MEP (Micro Edge Positioner) control mode.
//!
//! \param base is the base address of the PWM module.
//! \param channel is high resolution period module.
//! \param mepCtrlMode is the MEP (Micro Edge Positioner) control mode.
//!
//! This function sets the mode (register type) the MEP (Micro Edge Positioner)
//! will control. Valid values for the parameters are:
//!  - channel
//!      - HRPWM_CHANNEL_A  - HRPWM A
//!      - HRPWM_CHANNEL_B  - HRPWM B
//!  - mepCtrlMode
//!      - HRPWM_MEP_DUTY_PERIOD_CTRL      - MEP (Micro Edge Positioner) is
//!                                          controlled by value of CCOMPAHR/
//!                                          CCOMPBHR(depending on the value of
//!                                          channel) or TBPRDHR.
//!      - HRPWM_MEP_PHASE_CTRL            - MEP (Micro Edge Positioner) is
//!                                          controlled by TBPOFHR.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setMEPControlMode(uint32_t base, HRPWM_Channel channel,
                        HRPWM_MEPCtrlMode mepCtrlMode)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the MEP control
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRPCFG) =
       ((HWREGH(base + HRPWM_O_HRPCFG) & ~(0x1U << ((uint16_t)channel + 2U))) |
         ((uint16_t)mepCtrlMode << ((uint16_t)channel + 2U)));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the high resolution comparator load mode.
//!
//! \param base is the base address of the PWM module.
//! \param channel is high resolution period module.
//! \param loadEvent is the MEP (Micro Edge Positioner) control mode.
//!
//! This function sets the shadow load mode of the high resolution comparator.
//! The function sets the COMPA or COMPB register depending on the channel
//! variable.
//! Valid values for the parameters are:
//!  - channel
//!      - HRPWM_CHANNEL_A  - HRPWM A
//!      - HRPWM_CHANNEL_B  - HRPWM B
//!  - loadEvent
//!      - HRPWM_LOAD_ON_CNTR_ZERO         - load when counter equals zero
//!      - HRPWM_LOAD_ON_CNTR_PERIOD       - load when counter equals period
//!      - HRPWM_LOAD_ON_CNTR_ZERO_PERIOD  - load when counter equals zero or
//!                                          period
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setCounterCompareShadowLoadEvent(uint32_t base, HRPWM_Channel channel,
                                       HRPWM_LoadMode loadEvent)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the CCOMPAHR or CCOMPBHR load mode
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRPCFG) =
       ((HWREGH(base + HRPWM_O_HRPCFG) & ~(0x3U << ((uint16_t)channel + 3U))) |
         ((uint16_t)loadEvent << ((uint16_t)channel + 3U)));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the high resolution output swap mode.
//!
//! \param base is the base address of the PWM module.
//! \param enableOutputSwap is the output swap flag.
//!
//! This function sets the HRPWM output swap mode. If enableOutputSwap is true,
//! PWMxA signal appears on PWMxB output and PWMxB signal appears on PWMxA
//! output. If it is false PWMxA and PWMxB outputs are unchanged.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setOutputSwapMode(uint32_t base, bool enableOutputSwap)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set output swap mode
    //
    WRPRT_DISABLE;
    if(enableOutputSwap)
    {
        HWREGH(base + HRPWM_O_HRPCFG) |= HRPWM_HRPCFG_ABOSSWAP;
    }
    else
    {
        HWREGH(base + HRPWM_O_HRPCFG) &= ~HRPWM_HRPCFG_ABOSSWAP;
    }
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the high resolution output on PWMxB
//!
//! \param base is the base address of the PWM module.
//! \param outputOnB is the output signal on PWMxB.
//!
//! This function sets the HRPWM output signal on PWMxB. If outputOnB is
//! HRPWM_OUTPUT_ON_B_INV_A, PWMxB output is an inverted version of
//! PWMxA. If outputOnB is HRPWM_OUTPUT_ON_B_NORMAL, PWMxB output is
//! PWMxB.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setChannelBOutputPath(uint32_t base, HRPWM_ChannelBOutput outputOnB)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the output on PWM B
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRPCFG) =
            ((HWREGH(base + HRPWM_O_HRPCFG) & ~(HRPWM_HRPCFG_BOINVCFG)) |
             ((uint16_t)outputOnB << 5U));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables MEP (Micro Edge Positioner) automatic scale mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables the MEP (Micro Edge Positioner) to automatically
//! scale HRMSTEP.
//!
//! The SFO library will calculate required MEP steps per coarse steps and
//! feed it to HRMSTEP register. The MEP calibration module will use the value
//! in HRMSTEP to determine appropriate number of MEP steps represented by
//! fractional duty cycle.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_enableAutoConversion(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Enable MEP automatic scale
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRPCFG) |= HRPWM_HRPCFG_AUTOCEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables MEP automatic scale mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables the MEP (Micro Edge Positioner) from automatically
//! scaling HRMSTEP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_disableAutoConversion(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Disable MEP automatic scale
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRPCFG) &= ~HRPWM_HRPCFG_AUTOCEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable high resolution period feature.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables the high resolution period feature.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_enablePeriodControl(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set HRPRDEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRPRDCTRL) |= HRPWM_HRPRDCTRL_HRPRDEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable high resolution period feature.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables the high resolution period feature.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_disablePeriodControl(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Clear HRPRDEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRPRDCTRL) &= ~HRPWM_HRPRDCTRL_HRPRDEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable high resolution phase load
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables loading of high resolution phase shift value which is
//! set by the function HRPWM_setPhaseShift().
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_enablePhaseShiftLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set HRPHSEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRPRDCTRL) |= HRPWM_HRPRDCTRL_HRPHSEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable high resolution phase load
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables loading of high resolution phase shift value.
//!
//! \return
//
//*****************************************************************************
static inline void
HRPWM_disablePhaseShiftLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Clear HRPHSEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRPRDCTRL) &= ~HRPWM_HRPRDCTRL_HRPHSEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set high resolution PWMSYNC source.
//!
//! \param base is the base address of the PWM module.
//! \param syncPulseSource is the PWMSYNC source.
//!
//! This function sets the high resolution PWMSYNC pulse source.
//! Valid values for syncPulseSource are:
//!  - HRPWM_PWMSYNC_SOURCE_PERIOD      - Counter equals Period.
//!  - HRPWM_PWMSYNC_SOURCE_ZERO        - Counter equals zero.
//!  - HRPWM_PWMSYNC_SOURCE_COMPC_UP    - Counter equals COMPC when
//!                                       counting up.
//!  - HRPWM_PWMSYNC_SOURCE_COMPC_DOWN  - Counter equals COMPC when
//!                                       counting down.
//!  - HRPWM_PWMSYNC_SOURCE_COMPD_UP    - Counter equals COMPD when
//!                                       counting up.
//!  - HRPWM_PWMSYNC_SOURCE_COMPD_DOWN  - Counter equals COMPD when
//!                                       counting down.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setSyncPulseSource(uint32_t base, HRPWM_SyncPulseSource syncPulseSource)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the PWMSYNC source
    //
    WRPRT_DISABLE;

    //
    // Configuration for sync pulse source equal to HRPWM_PWMSYNC_SOURCE_PERIOD
    // or HRPWM_PWMSYNC_SOURCE_ZERO
    //
    if(syncPulseSource < HRPWM_PWMSYNC_SOURCE_COMPC_UP)
    {
        HWREGH(base + HRPWM_O_HRPRDCTRL) =
          ((HWREGH(base + HRPWM_O_HRPRDCTRL) &
          ~(HRPWM_HRPRDCTRL_ESSEL_M | HRPWM_HRPRDCTRL_SYNCPER_SRCSEL)) |
           ((uint16_t)syncPulseSource << 1U));
    }
    else
    {
        HWREGH(base + HRPWM_O_HRPRDCTRL) =
          ((HWREGH(base + HRPWM_O_HRPRDCTRL) & ~HRPWM_HRPRDCTRL_ESSEL_M) |
           ((uint16_t)syncPulseSource << HRPWM_HRPRDCTRL_ESSEL_S));
    }
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the Translator Remainder value.
//!
//! \param base is the base address of the PWM module.
//! \param trremVal is the translator remainder value.
//!
//! This function sets the Translator Remainder value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setTranslatorRemainder(uint32_t base, uint16_t trremVal)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(trremVal < 2048U);

    //
    // Set Translator Remainder value
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_THRR) = (trremVal & HRPWM_THRR_TRP_M);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the consolidated counter compare values in HR mode.
//!
//! \param base is the base address of the PWM module.
//! \param compModule is the Counter Compare module.
//! \param compCount is the consolidated counter compare count value.
//!
//! This function sets the consolidated counter compare(CMPx:CMPxHR) value
//! required in high resolution mode for counter compare registers.
//! Valid values for compModule are:
//!  - HRPWM_COUNTER_COMPARE_A - counter compare A.
//!  - HRPWM_COUNTER_COMPARE_B - counter compare B.
//!
//! \b Note: compCount is a 24 bit value.
//! \b Note: For configuring CCOMPA = 0xB4, CCOMPAHR = 0x64; value of
//!          compCount = 0xB464
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setCounterCompareValue(uint32_t base,
                             HRPWM_CounterCompareModule compModule,
                             uint32_t compCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(compCount < 0x1000000U);

    //
    // Write to counter compare registers
    //
    if(compModule == HRPWM_COUNTER_COMPARE_A)
    {
        //
        // Write to CCOMPA:CCOMPAHR
        //
        HWREG(base + HRPWM_O_CCOMPA) = compCount << 8U;
    }
    else
    {
        //
        // Write to CCOMPB:CCOMPBHR
        //
        HWREG(base + HRPWM_O_CCOMPB) = compCount << 8U;
    }
}

//*****************************************************************************
//
//! Sets only the high resolution counter compare value.
//!
//! \param base is the base address of the PWM module.
//! \param compModule is the Counter Compare module.
//! \param hrCompCount is the high resolution counter compare count value.
//!
//! This function sets the high resolution counter compare value(CMPxHR) for
//! counter compare registers.
//! Valid values for compModule are:
//!  - HRPWM_COUNTER_COMPARE_A - counter compare A.
//!  - HRPWM_COUNTER_COMPARE_B - counter compare B.
//!
//! \b Note: hrCompCount is an 8-bit value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setHiResCounterCompareValueOnly(uint32_t base,
                                      HRPWM_CounterCompareModule compModule,
                                      uint16_t hrCompCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(hrCompCount < 256U);

    //
    // Write to the high resolution counter compare registers
    //
    if(compModule == HRPWM_COUNTER_COMPARE_A)
    {
        //
        // Write to CCOMPAHR
        //
        HWREGH(base + HRPWM_O_CCOMPA) = hrCompCount << 8U;
    }
    else
    {
        //
        // Write to CCOMPBHR
        //
        HWREGH(base + HRPWM_O_CCOMPB) = hrCompCount << 8U;
    }
}

//*****************************************************************************
//
//! Gets the consolidated counter compare values.
//!
//! \param base is the base address of the PWM module.
//! \param compModule is the Counter Compare module value.
//!
//! This function gets the consolidated counter compare(CMPx:CMPxHR) value
//! used in high resolution for the counter compare module specified.
//! Valid values for compModule are:
//!  - HRPWM_COUNTER_COMPARE_A - counter compare A.
//!  - HRPWM_COUNTER_COMPARE_B - counter compare B.
//!
//!
//! \return None.
//
//*****************************************************************************
static inline uint32_t
HRPWM_getCounterCompareValue(uint32_t base,
                             HRPWM_CounterCompareModule compModule)
{
    uint32_t compCount;

    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Get counter compare value for selected module
    //
    if(compModule == HRPWM_COUNTER_COMPARE_A)
    {
        //
        // Read from CCOMPAHR
        //
        compCount = HWREG(base + HRPWM_O_CCOMPA) >> 8U;
    }
    else
    {
        //
        // Read from CCOMPBHR
        //
        compCount = HWREG(base + HRPWM_O_CCOMPB) >> 8U;
    }
    return(compCount);
}

//*****************************************************************************
//
//! Gets only the high resolution counter compare values.
//!
//! \param base is the base address of the PWM module.
//! \param compModule is the Counter Compare module value.
//!
//! This function gets only the high resolution counter compare(CMPxHR) value
//! for the counter compare module specified.
//! Valid values for compModule are:
//!  - HRPWM_COUNTER_COMPARE_A - counter compare A.
//!  - HRPWM_COUNTER_COMPARE_B - counter compare B.
//!
//! \return None.
//
//*****************************************************************************
static inline uint16_t
HRPWM_getHiResCounterCompareValueOnly(uint32_t base,
                                      HRPWM_CounterCompareModule compModule)
{
    uint16_t hrCompCount;

    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Get counter compare value for selected module
    //
    if(compModule == HRPWM_COUNTER_COMPARE_A)
    {
        //
        // Read from CCOMPAHR
        //
        hrCompCount = HWREGH(base + HRPWM_O_CCOMPA) >> 8U;
    }
    else
    {
        //
        // Read from CCOMPBHR
        //
        hrCompCount = HWREGH(base + HRPWM_O_CCOMPB) >> 8U;
    }
    return(hrCompCount);
}

//*****************************************************************************
//
//! Sets the consolidated RED count in high resolution mode.
//!
//! \param base is the base address of the PWM module.
//! \param redCount is the high resolution RED count.
//!
//! This function sets the consolidated RED (Rising Edge Delay) count
//! (DBRED:DBREDHR) value used in high resolution mode. The value of
//! redCount should be less than 0x200000.
//!
//! \b Note: redCount is a 21 bit value.
//! \b Note: For configuring DBRED = 0x4, DBREDHR = 0x1; value of
//!          redCount = ((0x4 << 7) | 0x1) = 0x201
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setRisingEdgeDelay(uint32_t base, uint32_t redCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(redCount < 0x200000U);

    //
    // Set the consolidated RED (Rising Edge Delay) count
    //
    HWREG(base + HRPWM_O_DBREDHRM) = redCount << 9U;
}

//*****************************************************************************
//
//! Sets the high resolution RED count only.
//!
//! \param base is the base address of the PWM module.
//! \param hrRedCount is the high resolution RED count.
//!
//! This function sets only the high resolution RED (Rising Edge Delay)
//! count(DBREDHR) value.
//! The value of hrRedCount should be less than 128.
//!
//! \b Note: hrRedCount is a 7-bit value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setHiResRisingEdgeDelayOnly(uint32_t base, uint16_t hrRedCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(hrRedCount < 128U);

    //
    // Set the High Resolution RED (Rising Edge Delay) count only
    //
    HWREGH(base + HRPWM_O_DBREDHRM) = hrRedCount << 9U;
}

//*****************************************************************************
//
//! Sets the consolidated FED value in high resolution mode.
//!
//! \param base is the base address of the PWM module.
//! \param fedCount is the high resolution FED count.
//!
//! This function sets the consolidated FED (Falling Edge Delay) count
//! (DBFED: DBFEDHR) value used in high resolution mode. The value of fedCount
//! should be less than 0x200000.
//!
//! \b Note: fedCount is a 21 bit value.
//! \b Note: For configuring DBFED = 0x4, DBFEDHR = 0x1; value of
//!          fedCount = ((0x4 << 7) | 0x1) = 0x201
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setFallingEdgeDelay(uint32_t base, uint32_t fedCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(fedCount < 0x200000U);

    //
    // Set the High Resolution FED (Falling Edge Delay) count
    //
    HWREG(base + HRPWM_O_DBFEDHRM) = fedCount << 9U;
}

//*****************************************************************************
//
//! Sets high resolution FED count only.
//!
//! \param base is the base address of the PWM module.
//! \param hrFedCount is the high resolution FED count.
//!
//! This function sets only the high resolution FED (Falling Edge Delay) count
//! (DBFEDHR)value. The value of hrFedCount should be less than 128.
//!
//! \b Note: hrFedCount is a 7-bit value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setHiResFallingEdgeDelayOnly(uint32_t base, uint16_t hrFedCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(hrFedCount < 128U);

    //
    // Set the high resolution FED (Falling Edge Delay) count
    //
    HWREGH(base + HRPWM_O_DBFEDHRM) = hrFedCount << 9U;
}

//*****************************************************************************
//
//! Set high resolution MEP (Micro Edge Positioner) step.
//!
//! \param base is the base address of the PWM module.
//! \param mepCount is the high resolution MEP (Micro Edge Positioner) step
//!        count.
//!
//! This function sets the high resolution MEP (Micro Edge Positioner) step
//! count. The maximum value for the MEP count step is 255.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setMEPStep(uint32_t base, uint16_t mepCount)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));
    ASSERT(mepCount < 256U);

    //
    // Set HRPWM MEP count
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRMSTEP) =
             ((HWREGH(base + HRPWM_O_HRMSTEP) & ~HRPWM_HRMSTEP_MEPNUM_M) |
               mepCount);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set high resolution Dead Band MEP (Micro Edge Positioner) control.
//!
//! \param base is the base address of the PWM module.
//! \param mepDBEdge is the high resolution MEP (Micro Edge Positioner) control
//!        edge.
//!
//! This function sets the high resolution Dead Band edge that the MEP (Micro
//! Edge Positioner) controls Valid values for mepDBEdge are:
//!   - HRPWM_DB_MEP_CTRL_DISABLE  - HRPWM is disabled
//!   - HRPWM_DB_MEP_CTRL_RED      - MEP (Micro Edge Positioner) controls
//!                                  Rising Edge Delay
//!   - HRPWM_DB_MEP_CTRL_FED      - MEP (Micro Edge Positioner) controls
//!                                  Falling Edge Delay
//!   - HRPWM_DB_MEP_CTRL_RED_FED  - MEP (Micro Edge Positioner) controls both
//!                                  Falling and Rising edge delays
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setDeadbandMEPEdgeSelect(uint32_t base,
                               HRPWM_MEPDeadBandEdgeMode mepDBEdge)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the HRPWM DB edge mode
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRCFG2) =
       ((HWREGH(base + HRPWM_O_HRCFG2) & ~HRPWM_HRCFG2_DBEMSEL_M) |
         ((uint16_t)mepDBEdge));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the high resolution Dead Band RED load mode.
//!
//! \param base is the base address of the PWM module.
//! \param loadEvent is the shadow to active load event.
//!
//! This function sets the high resolution Rising Edge Delay(RED)Dead Band
//! count load mode.
//! Valid values for loadEvent are:
//!   - HRPWM_LOAD_ON_CNTR_ZERO        - load when counter equals zero.
//!   - HRPWM_LOAD_ON_CNTR_PERIOD      - load when counter equals period
//!   - HRPWM_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals zero
//!                                             or period.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setRisingEdgeDelayLoadMode(uint32_t base,
                                 HRPWM_LoadMode loadEvent)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the HRPWM RED load mode
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRCFG2) =
      ((HWREGH(base + HRPWM_O_HRCFG2) & ~HRPWM_HRCFG2_DBREDHR_LDEVTSEL_M) |
       ((uint16_t)loadEvent << HRPWM_HRCFG2_DBREDHR_LDEVTSEL_S));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the high resolution Dead Band FED load mode.
//!
//! \param base is the base address of the PWM module.
//! \param loadEvent is the shadow to active load event.
//!
//! This function sets the high resolution Falling Edge Delay(FED) Dead Band
//! count load mode.
//! Valid values for loadEvent are:
//!   - HRPWM_LOAD_ON_CNTR_ZERO        - load when counter equals zero.
//!   - HRPWM_LOAD_ON_CNTR_PERIOD      - load when counter equals period
//!   - HRPWM_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals zero
//!                                             or period.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_setFallingEdgeDelayLoadMode(uint32_t base, HRPWM_LoadMode loadEvent)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Set the HRPWM FED load mode
    //
    WRPRT_DISABLE;
    HWREGH(base + HRPWM_O_HRCFG2) =
       ((HWREGH(base + HRPWM_O_HRCFG2) & ~HRPWM_HRCFG2_DBFEDHR_LDEVTSEL_M) |
        ((uint16_t)loadEvent << HRPWM_HRCFG2_DBFEDHR_LDEVTSEL_S));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Lock WRPRT_DISABLE protected register groups
//!
//! \param base is the base address of the PWM module.
//! \param registerGroup is the WRPRT_DISABLE register groups.
//!
//! This functions locks the WRPRT_DISABLE protected register groups specified by
//! the registerGroup variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void
HRPWM_lockRegisters(uint32_t base, HRPWM_LockRegisterGroup registerGroup)
{
    //
    // Check the arguments
    //
    ASSERT(HRPWM_isBaseValid(base));

    //
    // Write the Key to PWMLOCK register
    //
    HWREG(base + HRPWM_O_PWMLOCK) =
                           ((uint32_t)0xA5A50000U | ((uint32_t)registerGroup));
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

#endif // HRPWM_H
