//#############################################################################
//
// FILE:    pwm.h
//
// TITLE:   G32R501 PWM Driver
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
// 1. Module naming
//
//###########################################################################

#ifndef PWM_H
#define PWM_H

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
//! \addtogroup pwm_api PWM
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_pwm.h"
#include "hrpwm.h"
#include "cpu.h"
#include "debug.h"

//
// Time Base Module
//
//*****************************************************************************
//
//! Values that can be passed to PWM_setEmulationMode() as the
//! \e emulationMode parameter.
//
//*****************************************************************************
typedef enum
{
   //! Stop after next Time Base counter increment or decrement
   PWM_EMULATION_STOP_AFTER_NEXT_TB = 0,
   //! Stop when counter completes whole cycle
   PWM_EMULATION_STOP_AFTER_FULL_CYCLE = 1,
   //! Free run
   PWM_EMULATION_FREE_RUN = 2
} PWM_EmulationMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_setCountModeAfterSync() as the
//! \e mode parameter.
//
//*****************************************************************************
typedef enum
{
   PWM_COUNT_MODE_DOWN_AFTER_SYNC = 0, //!< Count down after sync event
   PWM_COUNT_MODE_UP_AFTER_SYNC = 1    //!< Count up after sync event
} PWM_SyncCountMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_setClockPrescaler() as the
//! \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_CLOCK_DIVIDER_1 = 0,     //!< Divide clock by 1
    PWM_CLOCK_DIVIDER_2 = 1,     //!< Divide clock by 2
    PWM_CLOCK_DIVIDER_4 = 2,     //!< Divide clock by 4
    PWM_CLOCK_DIVIDER_8 = 3,     //!< Divide clock by 8
    PWM_CLOCK_DIVIDER_16 = 4,    //!< Divide clock by 16
    PWM_CLOCK_DIVIDER_32 = 5,    //!< Divide clock by 32
    PWM_CLOCK_DIVIDER_64 = 6,    //!< Divide clock by 64
    PWM_CLOCK_DIVIDER_128 = 7    //!< Divide clock by 128
} PWM_ClockDivider;

//*****************************************************************************
//
//! Values that can be passed to PWM_setClockPrescaler() as the
//! \e highSpeedPrescaler parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_HSCLOCK_DIVIDER_1 = 0,     //!< Divide clock by 1
    PWM_HSCLOCK_DIVIDER_2 = 1,     //!< Divide clock by 2
    PWM_HSCLOCK_DIVIDER_4 = 2,     //!< Divide clock by 4
    PWM_HSCLOCK_DIVIDER_6 = 3,     //!< Divide clock by 6
    PWM_HSCLOCK_DIVIDER_8 = 4,     //!< Divide clock by 8
    PWM_HSCLOCK_DIVIDER_10 = 5,    //!< Divide clock by 10
    PWM_HSCLOCK_DIVIDER_12 = 6,    //!< Divide clock by 12
    PWM_HSCLOCK_DIVIDER_14 = 7     //!< Divide clock by 14
} PWM_HSClockDivider;

//*****************************************************************************
//
//! Values that can be passed to PWM_setSyncOutPulseMode() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! Sync pulse is generated by software
    PWM_SYNC_OUT_PULSE_ON_SOFTWARE  = 0,
    //! Sync pulse is passed from PWMxSYNCIN
    PWM_SYNC_OUT_PULSE_ON_PWMxSYNCIN = 0,
    //! Sync pulse is generated when time base counter equals zero
    PWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO = 1,
    //! Sync pulse is generated when time base counter equals compare B value
    PWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_B = 2,
    //! Sync pulse is disabled
    PWM_SYNC_OUT_PULSE_DISABLED = 4,
    //! Sync pulse is generated when time base counter equals compare C value
    PWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_C = 5,
    //! Sync pulse is generated when time base counter equals compare D value
    PWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_D = 6
} PWM_SyncOutPulseMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_setPeriodLoadMode()  as the
//! \e loadMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! PWM Period register access is through shadow register
    PWM_PERIOD_SHADOW_LOAD = 0,
    //! PWM Period register access is directly
    PWM_PERIOD_DIRECT_LOAD = 1
} PWM_PeriodLoadMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_setTimeBaseCounterMode() as the
//! \e counterMode parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_COUNTER_MODE_UP = 0,         //!< Up - count mode
    PWM_COUNTER_MODE_DOWN = 1,       //!< Down - count mode
    PWM_COUNTER_MODE_UP_DOWN = 2,    //!< Up - down - count mode
    PWM_COUNTER_MODE_STOP_FREEZE = 3 //!< Stop - Freeze counter
} PWM_TimeBaseCountMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_selectPeriodLoadEvent() as the
//! \e shadowLoadMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Shadow to active load occurs when time base counter reaches 0
    PWM_SHADOW_LOAD_MODE_COUNTER_ZERO = 0,
    //! Shadow to active load occurs when time base counter reaches 0 and a
    //! SYNC occurs
    PWM_SHADOW_LOAD_MODE_COUNTER_SYNC = 1,
    //! Shadow to active load occurs only when a SYNC occurs
    PWM_SHADOW_LOAD_MODE_SYNC         = 2
} PWM_PeriodShadowLoadMode;

//*****************************************************************************
//
// Values that can be returned by the PWM_getTimeBaseCounterDirection()
//
//*****************************************************************************
//! Time base counter is counting up
//!
#define PWM_TIME_BASE_STATUS_COUNT_UP                1U
//! Time base counter is counting down
//!
#define PWM_TIME_BASE_STATUS_COUNT_DOWN              0U

//*****************************************************************************
//
//! Values that can be passed to PWM_setupPWMLinks() as the \e pwmLink
//! parameter.
//
//*****************************************************************************
typedef enum
{
     PWM_LINK_WITH_PWM_1 = 0,   //!< link current PWM with PWM1
     PWM_LINK_WITH_PWM_2 = 1,   //!< link current PWM with PWM2
     PWM_LINK_WITH_PWM_3 = 2,   //!< link current PWM with PWM3
     PWM_LINK_WITH_PWM_4 = 3,   //!< link current PWM with PWM4
     PWM_LINK_WITH_PWM_5 = 4,   //!< link current PWM with PWM5
     PWM_LINK_WITH_PWM_6 = 5,   //!< link current PWM with PWM6
     PWM_LINK_WITH_PWM_7 = 6,   //!< link current PWM with PWM7
     PWM_LINK_WITH_PWM_8 = 7    //!< link current PWM with PWM8
} PWM_CurrentLink;

//*****************************************************************************
//
//! Values that can be passed to PWM_setupPWMLinks() as the \e linkComp
//! parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_LINK_TBPRD   = 0,  //!< Link TBPRD:TBPRDHR registers
    PWM_LINK_COMP_A  = 4,  //!< Link COMPA registers
    PWM_LINK_COMP_B  = 8,  //!< Link COMPB registers
    PWM_LINK_COMP_C  = 12, //!< Link COMPC registers
    PWM_LINK_COMP_D  = 16, //!< Link COMPD registers
    PWM_LINK_GLDCTL2 = 28  //!< Link GLDCTL2 registers
} PWM_LinkComponent;

//
// Counter Compare Module
//
//*****************************************************************************
//
//! Values that can be passed to the PWM_getCounterCompareShadowStatus(),
//! PWM_setCounterCompareValue(), PWM_setCounterCompareShadowLoadMode(),
//! PWM_disableCounterCompareShadowLoadMode()
//! as the \e compModule parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_COUNTER_COMPARE_A = 0, //!< Counter compare A
    PWM_COUNTER_COMPARE_B = 2, //!< Counter compare B
    PWM_COUNTER_COMPARE_C = 5, //!< Counter compare C
    PWM_COUNTER_COMPARE_D = 7  //!< Counter compare D
} PWM_CounterCompareModule;

//*****************************************************************************
//
//! Values that can be passed to PWM_setCounterCompareShadowLoadMode() as the
//! \e loadMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Load when counter equals zero
    PWM_COMP_LOAD_ON_CNTR_ZERO = 0,
    //! Load when counter equals period
    PWM_COMP_LOAD_ON_CNTR_PERIOD = 1,
    //! Load when counter equals zero or period
    PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    //! Freeze shadow to active load
    PWM_COMP_LOAD_FREEZE = 3,
    //! Load on sync or when counter equals zero
    PWM_COMP_LOAD_ON_SYNC_CNTR_ZERO = 4,
    //! Load on sync or when counter equals period
    PWM_COMP_LOAD_ON_SYNC_CNTR_PERIOD = 5,
    //! Load on sync or when counter equals zero or period
    PWM_COMP_LOAD_ON_SYNC_CNTR_ZERO_PERIOD = 6,
    //! Load on sync only
    PWM_COMP_LOAD_ON_SYNC_ONLY = 8
} PWM_CounterCompareLoadMode;

//
// Action Qualifier Module
//
//*****************************************************************************
//
//! Values that can be passed to PWM_setActionQualifierShadowLoadMode() and
//! PWM_disableActionQualifierShadowLoadMode() as the \e aqModule parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_ACTION_QUALIFIER_A = 0, //!< Action Qualifier A
    PWM_ACTION_QUALIFIER_B = 2  //!< Action Qualifier B
} PWM_ActionQualifierModule;

//*****************************************************************************
//
//! Values that can be passed to PWM_setActionQualifierShadowLoadMode() as the
//! \e loadMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Load when counter equals zero
    PWM_AQ_LOAD_ON_CNTR_ZERO = 0,
    //! Load when counter equals period
    PWM_AQ_LOAD_ON_CNTR_PERIOD = 1,
    //! Load when counter equals zero or period
    PWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    //! Freeze shadow to active load
    PWM_AQ_LOAD_FREEZE = 3,
    //! Load on sync or when counter equals zero
    PWM_AQ_LOAD_ON_SYNC_CNTR_ZERO = 4,
    //! Load on sync or when counter equals period
    PWM_AQ_LOAD_ON_SYNC_CNTR_PERIOD = 5,
    //! Load on sync or when counter equals zero or period
    PWM_AQ_LOAD_ON_SYNC_CNTR_ZERO_PERIOD = 6,
    //! Load on sync only
    PWM_AQ_LOAD_ON_SYNC_ONLY = 8
} PWM_ActionQualifierLoadMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_setActionQualifierT1TriggerSource() and
//! PWM_setActionQualifierT2TriggerSource() as the \e trigger parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1 = 0,      //!< Digital compare event A 1
    PWM_AQ_TRIGGER_EVENT_TRIG_DCA_2 = 1,      //!< Digital compare event A 2
    PWM_AQ_TRIGGER_EVENT_TRIG_DCB_1 = 2,      //!< Digital compare event B 1
    PWM_AQ_TRIGGER_EVENT_TRIG_DCB_2 = 3,      //!< Digital compare event B 2
    PWM_AQ_TRIGGER_EVENT_TRIG_TZ_1  = 4,      //!< Trip zone 1
    PWM_AQ_TRIGGER_EVENT_TRIG_TZ_2  = 5,      //!< Trip zone 2
    PWM_AQ_TRIGGER_EVENT_TRIG_TZ_3  = 6,      //!< Trip zone 3
    PWM_AQ_TRIGGER_EVENT_TRIG_PWM_SYNCIN = 7,//!< PWM sync
    PWM_AQ_TRIGGER_EVENT_TRIG_DC_EVTFILT = 8  //!< Digital compare filter event
} PWM_ActionQualifierTriggerSource;

//*****************************************************************************
//
//! Values that can be passed to PWM_setActionQualifierAction() as the \e
//! event parameter.
//
//*****************************************************************************
typedef enum
{
    //! Time base counter equals zero
    PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO       = 0,
    //! Time base counter equals period
    PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD     = 2,
    //! Time base counter up equals COMPA
    PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA    = 4,
    //! Time base counter down equals COMPA
    PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA  = 6,
    //! Time base counter up equals COMPB
    PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB    = 8,
    //! Time base counter down equals COMPB
    PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB  = 10,
    //! T1 event on count up
    PWM_AQ_OUTPUT_ON_T1_COUNT_UP         = 1,
    //! T1 event on count down
    PWM_AQ_OUTPUT_ON_T1_COUNT_DOWN       = 3,
    //! T2 event on count up
    PWM_AQ_OUTPUT_ON_T2_COUNT_UP         = 5,
    //! T2 event on count down
    PWM_AQ_OUTPUT_ON_T2_COUNT_DOWN       = 7
} PWM_ActionQualifierOutputEvent;

//*****************************************************************************
//
//! Values that can be passed to PWM_setActionQualifierSWAction(),
//! PWM_setActionQualifierAction() as the \e outPut parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_AQ_OUTPUT_NO_CHANGE = 0,  //!< No change in the output pins
    PWM_AQ_OUTPUT_LOW       = 1,  //!< Set output pins to low
    PWM_AQ_OUTPUT_HIGH      = 2,  //!< Set output pins to High
    PWM_AQ_OUTPUT_TOGGLE    = 3   //!< Toggle the output pins
} PWM_ActionQualifierOutput;

//*****************************************************************************
//
//! Values that can be passed to PWM_setActionQualifierContSWForceAction()
//! as the \e outPut parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_AQ_SW_DISABLED         = 0,  //!< Software forcing disabled
    PWM_AQ_SW_OUTPUT_LOW       = 1,  //!< Set output pins to low
    PWM_AQ_SW_OUTPUT_HIGH      = 2   //!< Set output pins to High
} PWM_ActionQualifierSWOutput;

//*****************************************************************************
//
//! Values that can be passed to PWM_setActionQualifierActionComplete()
//! as the \e action parameter.
//
//*****************************************************************************
typedef enum
{
    //! Time base counter equals zero and no change in the output pins
    PWM_AQ_OUTPUT_NO_CHANGE_ZERO = 0x0,
    //! Time base counter equals zero and set output pins to low
    PWM_AQ_OUTPUT_LOW_ZERO = 0x1,
    //! Time base counter equals zero and set output pins to high
    PWM_AQ_OUTPUT_HIGH_ZERO = 0x2,
    //! Time base counter equals zero and toggle the output pins
    PWM_AQ_OUTPUT_TOGGLE_ZERO = 0x3,
    //! Time base counter equals period and no change in the output pins
    PWM_AQ_OUTPUT_NO_CHANGE_PERIOD = 0x0,
    //! Time base counter equals period and set output pins to low
    PWM_AQ_OUTPUT_LOW_PERIOD = 0x4,
    //! Time base counter equals period and set output pins to high
    PWM_AQ_OUTPUT_HIGH_PERIOD = 0x8,
    //! Time base counter equals period and toggle the output pins
    PWM_AQ_OUTPUT_TOGGLE_PERIOD = 0xC,
    //! Time base counter up equals COMPA and no change in the output pins
    PWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA = 0x00,
    //! Time base counter up equals COMPA and set output pins to low
    PWM_AQ_OUTPUT_LOW_UP_CMPA = 0x10,
    //! Time base counter up equals COMPA and set output pins to high
    PWM_AQ_OUTPUT_HIGH_UP_CMPA = 0x20,
    //! Time base counter up equals COMPA and toggle the output pins
    PWM_AQ_OUTPUT_TOGGLE_UP_CMPA = 0x30,
    //! Time base counter down equals COMPA and no change in the output pins
    PWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA = 0x00,
    //! Time base counter down equals COMPA and set output pins to low
    PWM_AQ_OUTPUT_LOW_DOWN_CMPA = 0x40,
    //! Time base counter down equals COMPA and set output pins to high
    PWM_AQ_OUTPUT_HIGH_DOWN_CMPA = 0x80,
    //! Time base counter down equals COMPA and toggle the output pins
    PWM_AQ_OUTPUT_TOGGLE_DOWN_CMPA = 0xC0,
    //! Time base counter up equals COMPB and no change in the output pins
    PWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB = 0x000,
    //! Time base counter up equals COMPB and set output pins to low
    PWM_AQ_OUTPUT_LOW_UP_CMPB = 0x100,
    //! Time base counter up equals COMPB and set output pins to high
    PWM_AQ_OUTPUT_HIGH_UP_CMPB = 0x200,
    //! Time base counter up equals COMPB and toggle the output pins
    PWM_AQ_OUTPUT_TOGGLE_UP_CMPB = 0x300,
    //! Time base counter down equals COMPB and no change in the output pins
    PWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB = 0x000,
    //! Time base counter down equals COMPB and set output pins to low
    PWM_AQ_OUTPUT_LOW_DOWN_CMPB = 0x400,
    //! Time base counter down equals COMPB and set output pins to high
    PWM_AQ_OUTPUT_HIGH_DOWN_CMPB = 0x800,
    //! Time base counter down equals COMPB and toggle the output pins
    PWM_AQ_OUTPUT_TOGGLE_DOWN_CMPB = 0xC00
} PWM_ActionQualifierEventAction;

//*****************************************************************************
//
//! Values that can be passed to
//! PWM_setAdditionalActionQualifierActionComplete()  as the \e action
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! T1 event on count up and no change in the output pins
    PWM_AQ_OUTPUT_NO_CHANGE_UP_T1 = 0x0,
    //! T1 event on count up and set output pins to low
    PWM_AQ_OUTPUT_LOW_UP_T1 = 0x1,
    //! T1 event on count up and set output pins to high
    PWM_AQ_OUTPUT_HIGH_UP_T1 = 0x2,
    //! T1 event on count up and toggle the output pins
    PWM_AQ_OUTPUT_TOGGLE_UP_T1 = 0x3,
    //! T1 event on count down and no change in the output pins
    PWM_AQ_OUTPUT_NO_CHANGE_DOWN_T1 = 0x0,
    //! T1 event on count down and set output pins to low
    PWM_AQ_OUTPUT_LOW_DOWN_T1 = 0x4,
    //! T1 event on count down and set output pins to high
    PWM_AQ_OUTPUT_HIGH_DOWN_T1 = 0x8,
    //! T1 event on count down and toggle the output pins
    PWM_AQ_OUTPUT_TOGGLE_DOWN_T1 = 0xC,
    //! T2 event on count up and no change in the output pins
    PWM_AQ_OUTPUT_NO_CHANGE_UP_T2 = 0x00,
    //! T2 event on count up and set output pins to low
    PWM_AQ_OUTPUT_LOW_UP_T2 = 0x10,
    //! T2 event on count up and set output pins to high
    PWM_AQ_OUTPUT_HIGH_UP_T2 = 0x20,
    //! T2 event on count up and toggle the output pins
    PWM_AQ_OUTPUT_TOGGLE_UP_T2 = 0x30,
    //! T2 event on count down and no change in the output pins
    PWM_AQ_OUTPUT_NO_CHANGE_DOWN_T2 = 0x00,
    //! T2 event on count down and set output pins to low
    PWM_AQ_OUTPUT_LOW_DOWN_T2 = 0x40,
    //! T2 event on count down and set output pins to high
    PWM_AQ_OUTPUT_HIGH_DOWN_T2 = 0x80,
    //! T2 event on count down and toggle the output pins
    PWM_AQ_OUTPUT_TOGGLE_DOWN_T2 = 0xC0
} PWM_AdditionalActionQualifierEventAction;

//*****************************************************************************
//
//! Values that can be passed to PWM_forceActionQualifierSWAction(),
//! PWM_setActionQualifierSWAction(), PWM_setActionQualifierAction()
//! PWM_setActionQualifierContSWForceAction() as the \e pwmOutput parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_AQ_OUTPUT_A = 0, //!< PWMxA output
    PWM_AQ_OUTPUT_B = 2  //!< PWMxB output
} PWM_ActionQualifierOutputModule;

//*****************************************************************************
//
//! Values that can be passed to PWM_setActionQualifierContSWForceShadowMode()
//! as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Shadow mode load when counter equals zero
    PWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO        = 0,
    //! Shadow mode load when counter equals period
    PWM_AQ_SW_SH_LOAD_ON_CNTR_PERIOD      = 1,
    //! Shadow mode load when counter equals zero or period
    PWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    //! No shadow load mode. Immediate mode only.
    PWM_AQ_SW_IMMEDIATE_LOAD   = 3
} PWM_ActionQualifierContForce;

//*****************************************************************************
//
//! Values that can be passed to PWM_setDeadBandOutputSwapMode()
//! as the \e output parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_DB_OUTPUT_A = 1, //!< DB output is PWMA
    PWM_DB_OUTPUT_B = 0  //!< DB output is PWMB
} PWM_DeadBandOutput;

//*****************************************************************************
//
//! Values that can be passed to PWM_setDeadBandDelayPolarity(),
//! PWM_setDeadBandDelayMode() as the \e delayMode parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_DB_RED = 1, //!< DB RED (Rising Edge Delay) mode
    PWM_DB_FED = 0  //!< DB FED (Falling Edge Delay) mode
} PWM_DeadBandDelayMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_setDeadBandDelayPolarity as the
//! \e polarity parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_DB_POLARITY_ACTIVE_HIGH = 0, //!< DB polarity is not inverted
    PWM_DB_POLARITY_ACTIVE_LOW  = 1  //!< DB polarity is inverted
} PWM_DeadBandPolarity;

//*****************************************************************************
//
// Values that can be passed to PWM_setRisingEdgeDeadBandDelayInput(),
// PWM_setFallingEdgeDeadBandDelayInput() as the input parameter.
//
//*****************************************************************************
//! Input signal is PWMA
//!
#define PWM_DB_INPUT_PWMA       0U
//! Input signal is PWMB
//!
#define PWM_DB_INPUT_PWMB       1U
//! Input signal is the output of Rising Edge delay
//!
#define PWM_DB_INPUT_DB_RED      2U

//*****************************************************************************
//
//! Values that can be passed to PWM_setDeadBandControlShadowLoadMode() as
//! the \e loadMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Load when counter equals zero
    PWM_DB_LOAD_ON_CNTR_ZERO        = 0,
    //! Load when counter equals period
    PWM_DB_LOAD_ON_CNTR_PERIOD      = 1,
    //! Load when counter equals zero or period
    PWM_DB_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    //! Freeze shadow to active load
    PWM_DB_LOAD_FREEZE = 3
} PWM_DeadBandControlLoadMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_setRisingEdgeDelayCountShadowLoadMode()
//! as the \e loadMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Load when counter equals zero
    PWM_RED_LOAD_ON_CNTR_ZERO        = 0,
    //! Load when counter equals period
    PWM_RED_LOAD_ON_CNTR_PERIOD      = 1,
    //! Load when counter equals zero or period
    PWM_RED_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    //! Freeze shadow to active load
    PWM_RED_LOAD_FREEZE = 3
} PWM_RisingEdgeDelayLoadMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_setFallingEdgeDelayCountShadowLoadMode()
//! as the \e loadMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Load when counter equals zero
    PWM_FED_LOAD_ON_CNTR_ZERO        = 0,
    //! Load when counter equals period
    PWM_FED_LOAD_ON_CNTR_PERIOD      = 1,
    //! Load when counter equals zero or period
    PWM_FED_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    //! Freeze shadow to active load
    PWM_FED_LOAD_FREEZE = 3
} PWM_FallingEdgeDelayLoadMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_setDeadBandCounterClock() as the
//! \e clockMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Dead band counter runs at TBCLK rate
    PWM_DB_COUNTER_CLOCK_FULL_CYCLE = 0,
    //! Dead band counter runs at 2*TBCLK rate
    PWM_DB_COUNTER_CLOCK_HALF_CYCLE = 1
} PWM_DeadBandClockMode;

//
// Trip Zone
//
//*****************************************************************************
//
// Values that can be passed to PWM_enableTripZoneSignals() and
// PWM_disableTripZoneSignals() as the tzSignal parameter.
//
//*****************************************************************************
//! TZ1 Cycle By Cycle
//!
#define PWM_TZ_SIGNAL_CBC1          0x1U
//! TZ2 Cycle By Cycle
//!
#define PWM_TZ_SIGNAL_CBC2          0x2U
//! TZ3 Cycle By Cycle
//!
#define PWM_TZ_SIGNAL_CBC3          0x4U
//! TZ4 Cycle By Cycle
//!
#define PWM_TZ_SIGNAL_CBC4          0x8U
//! TZ5 Cycle By Cycle
//!
#define PWM_TZ_SIGNAL_CBC5          0x10U
//! TZ6 Cycle By Cycle
//!
#define PWM_TZ_SIGNAL_CBC6          0x20U
//! DCAEVT2 Cycle By Cycle
//!
#define PWM_TZ_SIGNAL_DCAEVT2       0x40U
//! DCBEVT2 Cycle By Cycle
//!
#define PWM_TZ_SIGNAL_DCBEVT2       0x80U
//! One-shot TZ1
//!
#define PWM_TZ_SIGNAL_OSHT1         0x100U
//! One-shot TZ2
//!
#define PWM_TZ_SIGNAL_OSHT2         0x200U
//! One-shot TZ3
//!
#define PWM_TZ_SIGNAL_OSHT3         0x400U
//! One-shot TZ4
//!
#define PWM_TZ_SIGNAL_OSHT4         0x800U
//! One-shot TZ5
//!
#define PWM_TZ_SIGNAL_OSHT5         0x1000U
//! One-shot TZ6
//!
#define PWM_TZ_SIGNAL_OSHT6         0x2000U
//! One-shot DCAEVT1
//!
#define PWM_TZ_SIGNAL_DCAEVT1       0x4000U
//! One-shot DCBEVT1
//!
#define PWM_TZ_SIGNAL_DCBEVT1       0x8000U

//*****************************************************************************
//
//! Values that can be passed to PWM_setTripZoneDigitalCompareEventCondition()
//! as the \e dcType parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_TZ_DC_OUTPUT_A1 = 0, //!< Digital Compare output 1 A
    PWM_TZ_DC_OUTPUT_A2 = 3, //!< Digital Compare output 2 A
    PWM_TZ_DC_OUTPUT_B1 = 6, //!< Digital Compare output 1 B
    PWM_TZ_DC_OUTPUT_B2 = 9  //!< Digital Compare output 2 B
} PWM_TripZoneDigitalCompareOutput;

//*****************************************************************************
//
//! Values that can be passed to PWM_setTripZoneDigitalCompareEventCondition()
//! as the \e dcEvent parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_TZ_EVENT_DC_DISABLED = 0,       //!< Event is disabled
    PWM_TZ_EVENT_DCXH_LOW    = 1,       //!< Event when DCxH low
    PWM_TZ_EVENT_DCXH_HIGH   = 2,       //!< Event when DCxH high
    PWM_TZ_EVENT_DCXL_LOW    = 3,       //!< Event when DCxL low
    PWM_TZ_EVENT_DCXL_HIGH   = 4,       //!< Event when DCxL high
    PWM_TZ_EVENT_DCXL_HIGH_DCXH_LOW = 5 //!< Event when DCxL high DCxH low
} PWM_TripZoneDigitalCompareOutputEvent;

//*****************************************************************************
//
//! Values that can be passed to PWM_setTripZoneAction() as the \e tzEvent
//! parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_TZ_ACTION_EVENT_TZA = 0,     //!< TZ1 - TZ6, DCAEVT2, DCAEVT1
    PWM_TZ_ACTION_EVENT_TZB = 2,     //!< TZ1 - TZ6, DCBEVT2, DCBEVT1
    PWM_TZ_ACTION_EVENT_DCAEVT1 = 4, //!< DCAEVT1 (Digital Compare A event 1)
    PWM_TZ_ACTION_EVENT_DCAEVT2 = 6, //!< DCAEVT2 (Digital Compare A event 2)
    PWM_TZ_ACTION_EVENT_DCBEVT1 = 8, //!< DCBEVT1 (Digital Compare B event 1)
    PWM_TZ_ACTION_EVENT_DCBEVT2 = 10 //!< DCBEVT2 (Digital Compare B event 2)
} PWM_TripZoneEvent;

//*****************************************************************************
//
//! Values that can be passed to PWM_setTripZoneAction() as the
//! \e tzAction parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_TZ_ACTION_HIGH_Z  = 0, //!< High impedance output
    PWM_TZ_ACTION_HIGH    = 1, //!< High voltage state
    PWM_TZ_ACTION_LOW     = 2, //!< Low voltage state
    PWM_TZ_ACTION_DISABLE = 3  //!< Disable action
} PWM_TripZoneAction;

//*****************************************************************************
//
//! Values that can be passed to PWM_setTripZoneAdvAction() as the
//! \e tzAdvEvent parameter.
//
//*****************************************************************************
typedef enum
{
    //! TZ1 - TZ6, DCBEVT2, DCBEVT1 while counting down
    PWM_TZ_ADV_ACTION_EVENT_TZB_D = 9,
    //! TZ1 - TZ6, DCBEVT2, DCBEVT1 while counting up
    PWM_TZ_ADV_ACTION_EVENT_TZB_U = 6,
    //! TZ1 - TZ6, DCAEVT2, DCAEVT1 while counting down
    PWM_TZ_ADV_ACTION_EVENT_TZA_D = 3,
    //! TZ1 - TZ6, DCAEVT2, DCAEVT1 while counting up
    PWM_TZ_ADV_ACTION_EVENT_TZA_U = 0
} PWM_TripZoneAdvancedEvent;

//*****************************************************************************
//
//! Values that can be passed to PWM_setTripZoneAdvDigitalCompareActionA(),
//! PWM_setTripZoneAdvDigitalCompareActionB(),PWM_setTripZoneAdvAction()
//! as the \e tzAdvDCAction parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_TZ_ADV_ACTION_HIGH_Z  = 0, //!< High impedance output
    PWM_TZ_ADV_ACTION_HIGH    = 1, //!< High voltage state
    PWM_TZ_ADV_ACTION_LOW     = 2, //!< Low voltage state
    PWM_TZ_ADV_ACTION_TOGGLE  = 3, //!< Toggle the output
    PWM_TZ_ADV_ACTION_DISABLE = 7  //!< Disable action
} PWM_TripZoneAdvancedAction;

//*****************************************************************************
//
//! Values that can be passed to PWM_setTripZoneAdvDigitalCompareActionA() and
//! PWM_setTripZoneAdvDigitalCompareActionB() as the \e tzAdvDCEvent
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! Digital Compare event A/B 1 while counting up
    PWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U = 0,
    //! Digital Compare event A/B 1 while counting down
    PWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D = 3,
    //! Digital Compare event A/B 2 while counting up
    PWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U = 6,
    //! Digital Compare event A/B 2 while counting down
    PWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D =  9
} PWM_TripZoneAdvDigitalCompareEvent;

//*****************************************************************************
//
// Values that can be passed to PWM_enableTripZoneInterrupt()and
// PWM_disableTripZoneInterrupt() as the tzInterrupt parameter .
//
//*****************************************************************************
//! Trip Zones Cycle By Cycle interrupt
//!
#define PWM_TZ_INTERRUPT_CBC      0x2U
//! Trip Zones One Shot interrupt
//!
#define PWM_TZ_INTERRUPT_OST      0x4U
//! Digital Compare A Event 1 interrupt
//!
#define PWM_TZ_INTERRUPT_DCAEVT1  0x8U
//! Digital Compare A Event 2 interrupt
//!
#define PWM_TZ_INTERRUPT_DCAEVT2  0x10U
//! Digital Compare B Event 1 interrupt
//!
#define PWM_TZ_INTERRUPT_DCBEVT1  0x20U
//! Digital Compare B Event 2 interrupt
//!
#define PWM_TZ_INTERRUPT_DCBEVT2  0x40U

//*****************************************************************************
//
// Values that can be returned by PWM_getTripZoneFlagStatus() .
//
//*****************************************************************************
//! Trip Zones Cycle By Cycle flag
//!
#define PWM_TZ_FLAG_CBC      0x2U
//! Trip Zones One Shot flag
//!
#define PWM_TZ_FLAG_OST      0x4U
//! Digital Compare A Event 1 flag
//!
#define PWM_TZ_FLAG_DCAEVT1  0x8U
//! Digital Compare A Event 2 flag
//!
#define PWM_TZ_FLAG_DCAEVT2  0x10U
//! Digital Compare B Event 1 flag
//!
#define PWM_TZ_FLAG_DCBEVT1  0x20U
//! Digital Compare B Event 2 flag
//!
#define PWM_TZ_FLAG_DCBEVT2  0x40U

//*****************************************************************************
//
// Value can be passed to PWM_clearTripZoneFlag() as the
// tzInterrupt parameter and returned by PWM_getTripZoneFlagStatus().
//
//*****************************************************************************
//! Trip Zone interrupt
//!
#define PWM_TZ_INTERRUPT     0x1U

//*****************************************************************************
//
// Values that can be passed to PWM_clearCycleByCycleTripZoneFlag()
// as the tzCbcFlag parameter and returned by
// PWM_getCycleByCycleTripZoneFlagStatus().
//
//*****************************************************************************
//! CBC flag 1
//!
#define PWM_TZ_CBC_FLAG_1  0x1U
//! CBC flag 2
//!
#define PWM_TZ_CBC_FLAG_2  0x2U
//! CBC flag 3
//!
#define PWM_TZ_CBC_FLAG_3  0x4U
//! CBC flag 4
//!
#define PWM_TZ_CBC_FLAG_4  0x8U
//! CBC flag 5
//!
#define PWM_TZ_CBC_FLAG_5  0x10U
//! CBC flag 6
//!
#define PWM_TZ_CBC_FLAG_6   0x20U
//! CBC flag Digital compare event A2
//!
#define PWM_TZ_CBC_FLAG_DCAEVT2  0x40U
//! CBC flag Digital compare event B2
//!
#define PWM_TZ_CBC_FLAG_DCBEVT2  0x80U

//*****************************************************************************
//
// Values that can be passed to PWM_clearOneShotTripZoneFlag() as
// the tzCbcFlag parameter and returned by the
// PWM_getOneShotTripZoneFlagStatus() .
//
//*****************************************************************************
//! OST flag OST1
//!
#define PWM_TZ_OST_FLAG_OST1  0x1U
//! OST flag OST2
//!
#define PWM_TZ_OST_FLAG_OST2  0x2U
//! OST flag OST3
//!
#define PWM_TZ_OST_FLAG_OST3  0x4U
//! OST flag OST4
//!
#define PWM_TZ_OST_FLAG_OST4  0x8U
//! OST flag OST5
//!
#define PWM_TZ_OST_FLAG_OST5  0x10U
//! OST flag OST6
//!
#define PWM_TZ_OST_FLAG_OST6  0x20U
//! OST flag Digital compare event A1
//!
#define PWM_TZ_OST_FLAG_DCAEVT1   0x40U
//! OST flag Digital compare event B1
//!
#define PWM_TZ_OST_FLAG_DCBEVT1   0x80U

//*****************************************************************************
//
//! Values that can be passed to PWM_selectCycleByCycleTripZoneClearEvent() as
//! the \e clearMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Clear CBC pulse when counter equals zero
    PWM_TZ_CBC_PULSE_CLR_CNTR_ZERO = 0,
    //! Clear CBC pulse when counter equals period
    PWM_TZ_CBC_PULSE_CLR_CNTR_PERIOD = 1,
    //! Clear CBC pulse when counter equals zero or period
    PWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD = 2
} PWM_CycleByCycleTripZoneClearMode;

//*****************************************************************************
//
// Values that can be passed to PWM_forceTripZoneEvent() as the
// tzForceEvent parameter.
//
//*****************************************************************************
//! Force Cycle By Cycle trip event
//!
#define PWM_TZ_FORCE_EVENT_CBC  0x2U
//! Force a One-Shot Trip Event
//!
#define PWM_TZ_FORCE_EVENT_OST  0x4U
//! ForceDigital Compare Output A Event 1
//!
#define PWM_TZ_FORCE_EVENT_DCAEVT1  0x8U
//! ForceDigital Compare Output A Event 2
//!
#define PWM_TZ_FORCE_EVENT_DCAEVT2  0x10U
//! ForceDigital Compare Output B Event 1
//!
#define PWM_TZ_FORCE_EVENT_DCBEVT1  0x20U
//! ForceDigital Compare Output B Event 2
//!
#define PWM_TZ_FORCE_EVENT_DCBEVT2  0x40U

//*****************************************************************************
//
// Values that can be passed to PWM_setInterruptSource() as the
// interruptSource parameter.
//
//*****************************************************************************
//! Time-base counter is disabled
//!
#define PWM_INT_TBCTR_DISABLED 0U
//! Time-base counter equal to zero
//!
#define PWM_INT_TBCTR_ZERO  1U
//! Time-base counter equal to period
//!
#define PWM_INT_TBCTR_PERIOD  2U
//! Time-base counter equal to zero or period
//!
#define PWM_INT_TBCTR_ZERO_OR_PERIOD  3U
//! time-base counter equal to CMPA when the timer is incrementing
//!
#define PWM_INT_TBCTR_U_CMPA  4U
//! time-base counter equal to CMPC when the timer is incrementing
//!
#define PWM_INT_TBCTR_U_CMPC  8U
//! time-base counter equal to CMPA when the timer is decrementing
//!
#define PWM_INT_TBCTR_D_CMPA  5U
//! time-base counter equal to CMPC when the timer is decrementing
//!
#define PWM_INT_TBCTR_D_CMPC  10U
//! time-base counter equal to CMPB when the timer is incrementing
//!
#define PWM_INT_TBCTR_U_CMPB  6U
//! time-base counter equal to CMPD when the timer is incrementing
//!
#define PWM_INT_TBCTR_U_CMPD  12U
//! time-base counter equal to CMPB when the timer is decrementing
//!
#define PWM_INT_TBCTR_D_CMPB  7U
//! time-base counter equal to CMPD when the timer is decrementing
//!
#define PWM_INT_TBCTR_D_CMPD  14U

//*****************************************************************************
//
//! Values that can be passed to PWM_enableADCTrigger(),
//! PWM_disableADCTrigger(),PWM_setADCTriggerSource(),
//! PWM_setADCTriggerEventPrescale(),PWM_getADCTriggerFlagStatus(),
//! PWM_clearADCTriggerFlag(),PWM_enableADCTriggerEventCountInit(),
//! PWM_disableADCTriggerEventCountInit(),PWM_forceADCTriggerEventCountInit(),
//! PWM_setADCTriggerEventCountInitValue(),PWM_getADCTriggerEventCount(),
//! PWM_forceADCTrigger() as the \e adcSOCType parameter
//
//*****************************************************************************
typedef enum
{
    PWM_SOC_A = 0,  //!< SOC A
    PWM_SOC_B = 1   //!< SOC B
} PWM_ADCStartOfConversionType;

//*****************************************************************************
//
//! Values that can be passed to PWM_setADCTriggerSource() as the
//! \e socSource parameter.
//
//*****************************************************************************
typedef enum
{
    //! Event is based on DCxEVT1
    PWM_SOC_DCxEVT1 = 0,
    //! Time-base counter equal to zero
    PWM_SOC_TBCTR_ZERO = 1,
    //! Time-base counter equal to period
    PWM_SOC_TBCTR_PERIOD = 2,
    //! Time-base counter equal to zero or period
    PWM_SOC_TBCTR_ZERO_OR_PERIOD = 3,
    //! Time-base counter equal to CMPA when the timer is incrementing
    PWM_SOC_TBCTR_U_CMPA = 4,
    //! Time-base counter equal to CMPC when the timer is incrementing
    PWM_SOC_TBCTR_U_CMPC = 8,
    //! Time-base counter equal to CMPA when the timer is decrementing
    PWM_SOC_TBCTR_D_CMPA = 5,
    //! Time-base counter equal to CMPC when the timer is decrementing
    PWM_SOC_TBCTR_D_CMPC = 10,
    //! Time-base counter equal to CMPB when the timer is incrementing
    PWM_SOC_TBCTR_U_CMPB = 6,
    //! Time-base counter equal to CMPD when the timer is incrementing
    PWM_SOC_TBCTR_U_CMPD = 12,
    //! Time-base counter equal to CMPB when the timer is decrementing
    PWM_SOC_TBCTR_D_CMPB = 7,
    //! Time-base counter equal to CMPD when the timer is decrementing
    PWM_SOC_TBCTR_D_CMPD = 14
} PWM_ADCStartOfConversionSource;

//
// Digital Compare Module
//
//*****************************************************************************
//
//! Values that can be passed to PWM_selectDigitalCompareTripInput(),
//! PWM_enableDigitalCompareTripCombinationInput(),
//! PWM_disableDigitalCompareTripCombinationInput() as the \e dcType
//! parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_DC_TYPE_DCAH = 0,  //!< Digital Compare A High
    PWM_DC_TYPE_DCAL = 1,  //!< Digital Compare A Low
    PWM_DC_TYPE_DCBH = 2,  //!< Digital Compare B High
    PWM_DC_TYPE_DCBL = 3   //!< Digital Compare B Low
} PWM_DigitalCompareType;

//*****************************************************************************
//
//! Values that can be passed to PWM_selectDigitalCompareTripInput() as the
//! \e tripSource parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_DC_TRIP_TRIPIN1 = 0,   //!< Trip 1
    PWM_DC_TRIP_TRIPIN2 = 1,   //!< Trip 2
    PWM_DC_TRIP_TRIPIN3 = 2,   //!< Trip 3
    PWM_DC_TRIP_TRIPIN4 = 3,   //!< Trip 4
    PWM_DC_TRIP_TRIPIN5 = 4,   //!< Trip 5
    PWM_DC_TRIP_TRIPIN6 = 5,   //!< Trip 6
    PWM_DC_TRIP_TRIPIN7 = 6,   //!< Trip 7
    PWM_DC_TRIP_TRIPIN8 = 7,   //!< Trip 8
    PWM_DC_TRIP_TRIPIN9 = 8,   //!< Trip 9
    PWM_DC_TRIP_TRIPIN10 = 9,  //!< Trip 10
    PWM_DC_TRIP_TRIPIN11 = 10, //!< Trip 11
    PWM_DC_TRIP_TRIPIN12 = 11, //!< Trip 12
    PWM_DC_TRIP_TRIPIN14 = 13, //!< Trip 14
    PWM_DC_TRIP_TRIPIN15 = 14, //!< Trip 15
    PWM_DC_TRIP_COMBINATION = 15 //!< All Trips (Trip1 - Trip 15) are selected
} PWM_DigitalCompareTripInput;

//*****************************************************************************
//
// Values that can be passed to PWM_enableDigitalCompareTripCombinationInput(),
// PWM_disableDigitalCompareTripCombinationInput() as the tripInput
// parameter.
//
//*****************************************************************************
//! Combinational Trip 1 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN1   0x1U
//! Combinational Trip 2 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN2   0x2U
//! Combinational Trip 3 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN3   0x4U
//! Combinational Trip 4 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN4   0x8U
//! Combinational Trip 5 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN5   0x10U
//! Combinational Trip 6 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN6   0x20U
//! Combinational Trip 7 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN7   0x40U
//! Combinational Trip 8 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN8   0x80U
//! Combinational Trip 9 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN9   0x100U
//! Combinational Trip 10 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN10  0x200U
//! Combinational Trip 11 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN11  0x400U
//! Combinational Trip 12 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN12  0x800U
//! Combinational Trip 14 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN14  0x2000U
//! Combinational Trip 15 input
//!
#define PWM_DC_COMBINATIONAL_TRIPIN15  0x4000U

//*****************************************************************************
//
//! Values that can be passed to PWM_setDigitalCompareBlankingEvent() as the
//! the \e blankingPulse parameter.
//
//*****************************************************************************
typedef enum
{
    //! Time base counter equals period
    PWM_DC_WINDOW_START_TBCTR_PERIOD = 0,
    //! Time base counter equals zero
    PWM_DC_WINDOW_START_TBCTR_ZERO   = 1,
    //! Time base counter equals zero or period
    PWM_DC_WINDOW_START_TBCTR_ZERO_PERIOD  = 2
} PWM_DigitalCompareBlankingPulse;

//*****************************************************************************
//
//! Values that can be passed to PWM_setDigitalCompareFilterInput()
//! as the \e filterInput parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_DC_WINDOW_SOURCE_DCAEVT1 = 0, //!< DC filter signal source is DCAEVT1
    PWM_DC_WINDOW_SOURCE_DCAEVT2 = 1, //!< DC filter signal source is DCAEVT2
    PWM_DC_WINDOW_SOURCE_DCBEVT1 = 2, //!< DC filter signal source is DCBEVT1
    PWM_DC_WINDOW_SOURCE_DCBEVT2 = 3  //!< DC filter signal source is DCBEVT2
} PWM_DigitalCompareFilterInput;

//*****************************************************************************
//
//! Values that can be assigned to PWM_setDigitalCompareEventSource(),
//! PWM_setDigitalCompareEventSyncMode(),PWM_enableDigitalCompareSyncEvent()
//! PWM_enableDigitalCompareADCTrigger(),PWM_disableDigitalCompareSyncEvent()
//! PWM_disableDigitalCompareADCTrigger() as the \e dcModule parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_DC_MODULE_A = 0, //!< Digital Compare Module A
    PWM_DC_MODULE_B = 1  //!< Digital Compare Module B
} PWM_DigitalCompareModule;

//*****************************************************************************
//
//! Values that can be passed to PWM_setDigitalCompareEventSource(),
//! PWM_setDigitalCompareEventSyncMode as the \e dcEvent parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_DC_EVENT_1 = 0, //!< Digital Compare Event number 1
    PWM_DC_EVENT_2 = 1  //!< Digital Compare Event number 2
} PWM_DigitalCompareEvent;

//*****************************************************************************
//
//! Values that can be passed to PWM_setDigitalCompareEventSource() as the
//! \e dcEventSource parameter.
//
//*****************************************************************************
typedef enum
{
    //! Signal source is unfiltered (DCAEVT1/2)
    PWM_DC_EVENT_SOURCE_ORIG_SIGNAL = 0,
    //! Signal source is filtered (DCEVTFILT)
    PWM_DC_EVENT_SOURCE_FILT_SIGNAL = 1
} PWM_DigitalCompareEventSource;

//*****************************************************************************
//
//! Values that can be passed to PWM_setDigitalCompareEventSyncMode() as the
//! \e syncMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! DC input signal is synced with TBCLK
    PWM_DC_EVENT_INPUT_SYNCED = 0,
    //! DC input signal is not synced with TBCLK
    PWM_DC_EVENT_INPUT_NOT_SYNCED = 1
} PWM_DigitalCompareSyncMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_setGlobalLoadTrigger() as the
//! \e loadTrigger parameter.
//
//*****************************************************************************
typedef enum
{
    //! Load when counter is equal to zero
    PWM_GL_LOAD_PULSE_CNTR_ZERO = 0x0,
    //! Load when counter is equal to period
    PWM_GL_LOAD_PULSE_CNTR_PERIOD = 0x1,
    //! Load when counter is equal to zero or period
    PWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD = 0x2,
    //! Load on sync event
    PWM_GL_LOAD_PULSE_SYNC = 0x3,
    //! Load on sync event or when counter  is equal to zero
    PWM_GL_LOAD_PULSE_SYNC_OR_CNTR_ZERO = 0x4,
    //! Load on sync event or when counter  is equal to period
    PWM_GL_LOAD_PULSE_SYNC_OR_CNTR_PERIOD = 0x5,
    //! Load on sync event or when counter is equal to period or zero
    PWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD = 0x6,
    //! Load on global force
    PWM_GL_LOAD_PULSE_GLOBAL_FORCE = 0xF
} PWM_GlobalLoadTrigger;

//*****************************************************************************
//
// Values that can be passed to PWM_enableGlobalLoadRegisters(),
// PWM_disableGlobalLoadRegisters() as theloadRegister parameter.
//
//*****************************************************************************
//! Global load TBPRD:TBPRDHR
//!
#define PWM_GL_REGISTER_TBPRD_TBPRDHR   0x1U
//! Global load CMPA:CMPAHR
//!
#define PWM_GL_REGISTER_CMPA_CMPAHR     0x2U
//! Global load CMPB:CMPBHR
//!
#define PWM_GL_REGISTER_CMPB_CMPBHR     0x4U
//! Global load CMPC
//!
#define PWM_GL_REGISTER_CMPC            0x8U
//! Global load CMPD
//!
#define PWM_GL_REGISTER_CMPD            0x10U
//! Global load DBRED:DBREDHR
//!
#define PWM_GL_REGISTER_DBRED_DBREDHR   0x20U
//! Global load DBFED:DBFEDHR
//!
#define PWM_GL_REGISTER_DBFED_DBFEDHR   0x40U
//! Global load DBCTL
//!
#define PWM_GL_REGISTER_DBCTL           0x80U
//! Global load AQCTLA/A2
//!
#define PWM_GL_REGISTER_AQCTLA_AQCTLA2  0x100U
//! Global load AQCTLB/B2
//!
#define PWM_GL_REGISTER_AQCTLB_AQCTLB2  0x200U
//! Global load AQCSFRC
//!
#define PWM_GL_REGISTER_AQCSFRC         0x400U

//*****************************************************************************
//
//! Values that can be passed to PWM_setValleyTriggerSource() as the \e
//! trigger parameter.
//
//*****************************************************************************
typedef enum
{
    //! Valley capture trigged by software
    PWM_VALLEY_TRIGGER_EVENT_SOFTWARE = 0U,
    //! Valley capture trigged by when counter is equal to zero
    PWM_VALLEY_TRIGGER_EVENT_CNTR_ZERO = 1U,
    //! Valley capture trigged by when counter is equal period
    PWM_VALLEY_TRIGGER_EVENT_CNTR_PERIOD = 2U,
    //! Valley capture trigged when counter is equal to zero or period
    PWM_VALLEY_TRIGGER_EVENT_CNTR_ZERO_PERIOD = 3U,
    //! Valley capture trigged by DCAEVT1 (Digital Compare A event 1)
    PWM_VALLEY_TRIGGER_EVENT_DCAEVT1 = 4U,
    //! Valley capture trigged by DCAEVT2 (Digital Compare A event 2)
    PWM_VALLEY_TRIGGER_EVENT_DCAEVT2 = 5U,
    //! Valley capture trigged by DCBEVT1 (Digital Compare B event 1)
    PWM_VALLEY_TRIGGER_EVENT_DCBEVT1 = 6U,
    //! Valley capture trigged by DCBEVT2 (Digital Compare B event 2)
    PWM_VALLEY_TRIGGER_EVENT_DCBEVT2 = 7U
} PWM_ValleyTriggerSource;

//*****************************************************************************
//
//! Values that can be passed to PWM_getValleyCountEdgeStatus() as the \e edge
//! parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_VALLEY_COUNT_START_EDGE = 0, //!< Valley count start edge
    PWM_VALLEY_COUNT_STOP_EDGE  = 1  //!< Valley count stop edge
} PWM_ValleyCounterEdge;

//*****************************************************************************
//
//! Values that can be passed to PWM_setValleyDelayValue() as the \e delayMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! Delay value equals the offset value defines by software
    PWM_VALLEY_DELAY_MODE_SW_DELAY   = 0U,
    //! Delay value equals the sum of the Hardware counter value and the offset
    //! value defines by software
    PWM_VALLEY_DELAY_MODE_VCNT_DELAY_SW_DELAY = 1U,
    //! Delay value equals the the Hardware counter shifted by
    //! (1 + the offset value defines by software)
    PWM_VALLEY_DELAY_MODE_VCNT_DELAY_SHIFT_1_SW_DELAY = 2U,
    //! Delay value equals the the Hardware counter shifted by
    //! (2 + the offset value defines by software)
    PWM_VALLEY_DELAY_MODE_VCNT_DELAY_SHIFT_2_SW_DELAY = 3U,
    //! Delay value equals the the Hardware counter shifted by
    //! (4 + the offset value defines by software)
    PWM_VALLEY_DELAY_MODE_VCNT_DELAY_SHIFT_4_SW_DELAY = 4U
} PWM_ValleyDelayMode;

//
// DC Edge Filter
//
//*****************************************************************************
//
//! Values that can be passed to PWM_setDigitalCompareEdgeFilterMode()
//! as the \e edgeMode parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_DC_EDGEFILT_MODE_RISING  = 0, //!< Digital Compare Edge filter low
                                       //!< to high edge mode
    PWM_DC_EDGEFILT_MODE_FALLING = 1, //!< Digital Compare Edge filter high
                                       //!< to low edge mode
    PWM_DC_EDGEFILT_MODE_BOTH    = 2  //!< Digital Compare Edge filter both
                                       //!< edges mode
} PWM_DigitalCompareEdgeFilterMode;

//*****************************************************************************
//
//! Values that can be passed to PWM_setDigitalCompareEdgeFilterEdgeCount()
//! as the \e edgeCount parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_DC_EDGEFILT_EDGECNT_0  = 0, //!< Digital Compare Edge filter edge
                                     //!< count = 0
    PWM_DC_EDGEFILT_EDGECNT_1  = 1, //!< Digital Compare Edge filter edge
                                     //!< count = 1
    PWM_DC_EDGEFILT_EDGECNT_2  = 2, //!< Digital Compare Edge filter edge
                                     //!< count = 2
    PWM_DC_EDGEFILT_EDGECNT_3  = 3, //!< Digital Compare Edge filter edge
                                     //!< count = 3
    PWM_DC_EDGEFILT_EDGECNT_4  = 4, //!< Digital Compare Edge filter edge
                                     //!< count = 4
    PWM_DC_EDGEFILT_EDGECNT_5  = 5, //!< Digital Compare Edge filter edge
                                     //!< count = 5
    PWM_DC_EDGEFILT_EDGECNT_6  = 6, //!< Digital Compare Edge filter edge
                                     //!< count = 6
    PWM_DC_EDGEFILT_EDGECNT_7  = 7  //!< Digital Compare Edge filter edge
                                     //!< count = 7
} PWM_DigitalCompareEdgeFilterEdgeCount;

//*****************************************************************************
//
//! Values that can be passed to PWM_lockRegisters() as the \e registerGroup
//! parameter.
//
//*****************************************************************************
typedef enum
{
    PWM_REGISTER_GROUP_GLOBAL_LOAD = 0x2,     //!< Global load register group
    PWM_REGISTER_GROUP_TRIP_ZONE = 0x4,       //!< Trip zone register group
    PWM_REGISTER_GROUP_TRIP_ZONE_CLEAR = 0x8, //!< Trip zone clear group
    PWM_REGISTER_GROUP_DIGITAL_COMPARE = 0x10 //!< Digital compare group
} PWM_LockRegisterGroup;

//*****************************************************************************
//
//! Values that can be passed to PWM_configureSignal() as the
//! \e signalParams parameter.
//
//*****************************************************************************
typedef struct
{
    float32_t              freqInHz;    //!< Desired Signal Frequency(in Hz)
    float32_t              dutyValA;    //!< Desired PWMxA Signal Duty
    float32_t              dutyValB;    //!< Desired PWMxB Signal Duty
    bool                   invertSignalB; //!< Invert PWMxB Signal if true
    float32_t              apbClkInHz;  //!< APBCLK Frequency(in Hz)
    PWM_TimeBaseCountMode tbCtrMode;   //!< Time Base Counter Mode
    PWM_ClockDivider      tbClkDiv;    //!< Time Base Counter Clock Divider
    PWM_HSClockDivider    tbHSClkDiv;  //!< Time Base Counter HS Clock Divider
} PWM_SignalParams;

//*****************************************************************************
//
// Functions APIs shared with HRPWM module
//
//*****************************************************************************

//
// Period Control related API
//
#define PWM_setSyncPulseSource                 HRPWM_setSyncPulseSource

//*****************************************************************************
//
// Prototypes for the API.
//
//*****************************************************************************

//*****************************************************************************
//
//! \internal
//! Checks PWM base address.
//!
//! \param base specifies the PWM module base address.
//!
//! This function determines if an PWM module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool PWM_isBaseValid(uint32_t base)
{
    return(
           (base == PWM1_BASE) ||
           (base == PWM2_BASE) ||
           (base == PWM3_BASE) ||
           (base == PWM4_BASE) ||
           (base == PWM5_BASE) ||
           (base == PWM6_BASE) ||
           (base == PWM7_BASE) ||
           (base == PWM8_BASE)
          );
}
#endif

//
// Time Base Sub Module related APIs
//
//*****************************************************************************
//
//! Set the time base count
//!
//! \param base is the base address of the PWM module.
//! \param count is the time base count value.
//!
//! This function sets the 16 bit counter value of the time base counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setTimeBaseCounter(uint32_t base, uint16_t count)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Write to TBCTR register
    //
    HWREGH(base + PWM_O_TBCTR) = count;
}

//*****************************************************************************
//
//! Set count mode after phase shift sync
//!
//! \param base is the base address of the PWM module.
//! \param mode is the count mode.
//!
//! This function sets the time base count to count up or down after a new
//! phase value set by the PWM_setPhaseShift(). The count direction is
//! determined by the variable mode. Valid inputs for mode are:
//!  - PWM_COUNT_MODE_UP_AFTER_SYNC      - Count up after sync
//!  - PWM_COUNT_MODE_DOWN_AFTER_SYNC    - Count down after sync
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setCountModeAfterSync(uint32_t base, PWM_SyncCountMode mode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    if(mode == PWM_COUNT_MODE_UP_AFTER_SYNC)
    {
        //
        // Set PHSDIR bit
        //
        HWREGH(base + PWM_O_TBCTL) |= PWM_TBCTL_PHSDIR;
    }
    else
    {
        //
        // Clear PHSDIR bit
        //
        HWREGH(base + PWM_O_TBCTL) &= ~PWM_TBCTL_PHSDIR;
    }
}

//*****************************************************************************
//
//! Set the time base clock and the high speed time base clock count pre-scaler
//!
//! \param base is the base address of the PWM module.
//! \param prescaler is the time base count pre scale value.
//! \param highSpeedPrescaler is the high speed time base count pre scale
//!        value.
//!
//! This function sets the pre scaler(divider)value for the time base clock
//! counter and the high speed time base clock counter.
//! Valid values for pre-scaler and highSpeedPrescaler are PWM_CLOCK_DIVIDER_X,
//! where X is 1,2,4,8,16, 32,64 or 128.
//! The actual numerical values for these macros represent values 0,1...7.
//! The equation for the output clock is:
//!   TBCLK = PWMCLK/(highSpeedPrescaler * pre-scaler)
//!
//! \b Note: PWMCLK is a scaled version of APBCLK. At reset PWMCLK is half
//!          APBCLK.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setClockPrescaler(uint32_t base, PWM_ClockDivider prescaler,
                       PWM_HSClockDivider highSpeedPrescaler)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Write to CLKDIV and HSPCLKDIV bit
    //
    HWREGH(base + PWM_O_TBCTL) =
                ((HWREGH(base + PWM_O_TBCTL)  &
                ~(PWM_TBCTL_CLKDIV_M | PWM_TBCTL_HSPCLKDIV_M)) |
                (((uint16_t)prescaler << PWM_TBCTL_CLKDIV_S) |
                ((uint16_t)highSpeedPrescaler << PWM_TBCTL_HSPCLKDIV_S)));
}

//*****************************************************************************
//
//! Force a software sync pulse
//!
//! \param base is the base address of the PWM module.
//!
//! This function causes a single software initiated sync pulse. Make sure the
//! appropriate mode is selected using PWM_setupSyncOutputMode() before using
//! this function.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_forceSyncPulse(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set SWFSYNC bit
    //
    HWREGH(base + PWM_O_TBCTL) |= PWM_TBCTL_SWFSYNC;
}

//*****************************************************************************
//
//! Set up the sync out pulse event
//!
//! \param base is the base address of the PWM module.
//! \param mode is the sync out mode.
//!
//! This function set the sync out pulse mode.
//! Valid values for mode are:
//!  - PWM_SYNC_OUT_PULSE_ON_SOFTWARE   - sync pulse is generated by software
//!                                        when PWM_forceSyncPulse()
//!                                        function is called or by PWMxSYNCI
//!                                        signal.
//!  - PWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO - sync pulse is generated when
//!                                          time base counter equals zero.
//!  - PWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_B - sync pulse is generated when
//!                                           time base counter equals compare
//!                                           B value.
//!  - PWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_C - sync pulse is generated when
//!                                           time base counter equals compare
//!                                           C value.
//!  - PWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_D - sync pulse is generated when
//!                                           time base counter equals compare
//!                                           D value.
//!  - PWM_SYNC_OUT_PULSE_DISABLED          - sync pulse is disabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setSyncOutPulseMode(uint32_t base, PWM_SyncOutPulseMode mode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // No extended mode support
    //
    if(mode < PWM_SYNC_OUT_PULSE_DISABLED)
    {
        //
        // Write to SYNCOSEL bits
        //
        HWREGH(base + PWM_O_TBCTL) =
                ((HWREGH(base + PWM_O_TBCTL) & ~(PWM_TBCTL_SYNCOSEL_M)) |
                 ((uint16_t)mode << PWM_TBCTL_SYNCOSEL_S));
    }
    //
    // Extended modes and sync out disable mode
    //
    else
    {
        //
        // Write 0x3 to SYNCOSEL to enable selection from SYNCOSELX
        //
        HWREGH(base + PWM_O_TBCTL) = HWREGH(base + PWM_O_TBCTL) |
                                      PWM_TBCTL_SYNCOSEL_M;

        //
        // Write to SYNCOSELX bit
        //
        HWREGH(base + PWM_O_TBCTL2) =
               ((HWREGH(base + PWM_O_TBCTL2) & ~(PWM_TBCTL2_SYNCOSELX_M)) |
                (((uint16_t)mode & 0x3U) << PWM_TBCTL2_SYNCOSELX_S));
    }
}

//*****************************************************************************
//
//! Set PWM period load mode.
//!
//! \param base is the base address of the PWM module.
//! \param loadMode is the PWM period load mode.
//!
//! This function sets the load mode for the PWM period. If loadMode is set to
//! PWM_PERIOD_SHADOW_LOAD, a write or read to the TBPRD (PWM Period count
//! register) accesses the shadow register. If loadMode is set to
//! PWM_PERIOD_DIRECT_LOAD, a write or read to the TBPRD register accesses the
//! register directly.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setPeriodLoadMode(uint32_t base, PWM_PeriodLoadMode loadMode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    if(loadMode == PWM_PERIOD_SHADOW_LOAD)
    {
        //
        // Clear PRDLD
        //
        HWREGH(base + PWM_O_TBCTL) &= ~PWM_TBCTL_PRDLD;
    }
    else
    {
        //
        // Set PRDLD
        //
        HWREGH(base + PWM_O_TBCTL) |= PWM_TBCTL_PRDLD;
    }
}

//*****************************************************************************
//
//! Enable phase shift load
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables loading of phase shift when the appropriate sync
//! event occurs.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enablePhaseShiftLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set PHSEN bit
    //
    HWREGH(base + PWM_O_TBCTL) |= PWM_TBCTL_PHSEN;
}

//*****************************************************************************
//
//! Disable phase shift load
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables loading of phase shift.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disablePhaseShiftLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Clear PHSEN bit
    //
    HWREGH(base + PWM_O_TBCTL) &= ~PWM_TBCTL_PHSEN;
}

//*****************************************************************************
//
//! Set time base counter mode
//!
//! \param base is the base address of the PWM module.
//! \param counterMode is the time base counter mode.
//!
//! This function sets up the time base counter mode.
//! Valid values for counterMode are:
//!  - PWM_COUNTER_MODE_UP          - Up - count mode.
//!  - PWM_COUNTER_MODE_DOWN        - Down - count mode.
//!  - PWM_COUNTER_MODE_UP_DOWN     - Up - down - count mode.
//!  - PWM_COUNTER_MODE_STOP_FREEZE - Stop - Freeze counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setTimeBaseCounterMode(uint32_t base, PWM_TimeBaseCountMode counterMode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Write to CTRMODE bit
    //
    HWREGH(base + PWM_O_TBCTL) =
            ((HWREGH(base + PWM_O_TBCTL) & ~(PWM_TBCTL_CTRMODE_M)) |
             ((uint16_t)counterMode));
}

//*****************************************************************************
//
//! Set shadow to active period load on sync mode
//!
//! \param base is the base address of the PWM module.
//! \param shadowLoadMode is the shadow to active load mode.
//!
//! This function sets up the shadow to active Period register load mode with
//! respect to a sync event. Valid values for shadowLoadMode are:
//!  - PWM_SHADOW_LOAD_MODE_COUNTER_ZERO - shadow to active load occurs when
//!                                         time base counter reaches 0.
//!  - PWM_SHADOW_LOAD_MODE_COUNTER_SYNC - shadow to active load occurs when
//!                                         time base counter reaches 0 and a
//!                                         SYNC occurs.
//!  - PWM_SHADOW_LOAD_MODE_SYNC         - shadow to active load occurs only
//!                                         when a SYNC occurs.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_selectPeriodLoadEvent(uint32_t base,
                           PWM_PeriodShadowLoadMode shadowLoadMode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Write to PRDLDSYNC bit
    //
    HWREGH(base + PWM_O_TBCTL2) =
                ((HWREGH(base + PWM_O_TBCTL2) & ~(PWM_TBCTL2_PRDLDSYNC_M)) |
                 ((uint16_t)shadowLoadMode << PWM_TBCTL2_PRDLDSYNC_S));
}
//*****************************************************************************
//
//! Enable one shot sync mode
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables one shot sync mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableOneShotSync(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set OSHTSYNCMODE bit
    //
    HWREGH(base + PWM_O_TBCTL2) |= PWM_TBCTL2_OSHTSYNCMODE;
}

//*****************************************************************************
//
//! Disable one shot sync mode
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables one shot sync mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableOneShotSync(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Clear OSHTSYNCMODE bit
    //
    HWREGH(base + PWM_O_TBCTL2) &= ~PWM_TBCTL2_OSHTSYNCMODE;
}

//*****************************************************************************
//
//! Start one shot sync mode
//!
//! \param base is the base address of the PWM module.
//!
//! This function propagates a one shot sync pulse.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_startOneShotSync(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set OSHTSYNC bit
    //
    HWREGH(base + PWM_O_TBCTL2) |= PWM_TBCTL2_OSHTSYNC;
}

//*****************************************************************************
//
//! Returns time base counter value.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the current value of the time base counter.
//!
//! \return returns time base counter value
//
//*****************************************************************************
static inline uint16_t
PWM_getTimeBaseCounterValue(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Returns TBCTR value
    //
    return(HWREGH(base + PWM_O_TBCTR));
}

//*****************************************************************************
//
//! Return time base counter maximum status.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the status of the time base max counter.
//!
//! \return Returns true if the counter has reached 0xFFFF.
//!         Returns false if the counter hasn't reached 0xFFFF.
//
//*****************************************************************************
static inline bool
PWM_getTimeBaseCounterOverflowStatus(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return true if CTRMAX bit is set, false otherwise
    //
    return(((HWREGH(base + PWM_O_TBSTS) & PWM_TBSTS_CTRMAX) ==
            PWM_TBSTS_CTRMAX) ? true : false);
}

//*****************************************************************************
//
//! Clear max time base counter event.
//!
//! \param base is the base address of the PWM module.
//!
//! This function clears the max time base counter latch event. The latch event
//! occurs when the time base counter reaches its maximum value of 0xFFFF.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_clearTimeBaseCounterOverflowEvent(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set CTRMAX bit
    //
    HWREGH(base + PWM_O_TBSTS) = PWM_TBSTS_CTRMAX;
}

//*****************************************************************************
//
//! Return external sync signal status.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the external sync signal status.
//!
//! \return Returns true if if an external sync signal event
//!         Returns false if there is no event.
//
//*****************************************************************************
static inline bool
PWM_getSyncStatus(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return true if SYNCI bit is set, false otherwise
    //
    return(((HWREGH(base + PWM_O_TBSTS) & PWM_TBSTS_SYNCI) ==
            PWM_TBSTS_SYNCI) ? true : false);
}

//*****************************************************************************
//
//! Clear external sync signal event.
//!
//! \param base is the base address of the PWM module.
//!
//! This function clears the external sync signal latch event.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_clearSyncEvent(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set SYNCI bit
    //
    HWREGH(base + PWM_O_TBSTS) = PWM_TBSTS_SYNCI;
}

//*****************************************************************************
//
//! Return time base counter direction.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the direction of the time base counter.
//!
//! \return returns PWM_TIME_BASE_STATUS_COUNT_UP if the counter is counting
//!                 up or PWM_TIME_BASE_STATUS_COUNT_DOWN if the counter is
//!                 counting down.
//
//*****************************************************************************
static inline uint16_t
PWM_getTimeBaseCounterDirection(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return CTRDIR bit
    //
    return(HWREGH(base + PWM_O_TBSTS) & PWM_TBSTS_CTRDIR);
}

//*****************************************************************************
//
//! Sets the phase shift offset counter value.
//!
//! \param base is the base address of the PWM module.
//! \param phaseCount is the phase shift count value.
//!
//! This function sets the 16 bit time-base counter phase of the PWM relative
//! to the time-base that is supplying the synchronization input signal. Call
//! the PWM_enablePhaseShiftLoad() function to enable loading of the
//! phaseCount phase shift value when a sync event occurs.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setPhaseShift(uint32_t base, uint16_t phaseCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Write to TBPHS bit
    //
    HWREG(base + PWM_O_TBPHS) =
                   ((HWREG(base + PWM_O_TBPHS) &
                    ~((uint32_t)PWM_TBPHS_TBPHS_M)) |
                    ((uint32_t)phaseCount << PWM_TBPHS_TBPHS_S));
}

//*****************************************************************************
//
//! Sets the PWM period count.
//!
//! \param base is the base address of the PWM module.
//! \param periodCount is period count value.
//!
//! This function sets the period of the PWM count. The value of periodCount is
//! the value written to the register. User should map the desired period or
//! frequency of the waveform into the correct periodCount.
//! Invoke the function PWM_selectPeriodLoadEvent() with the appropriate
//! parameter to set the load mode of the Period count. periodCount has a
//! maximum valid value of 0xFFFF
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setTimeBasePeriod(uint32_t base, uint16_t periodCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Write to TBPRD bit
    //
    HWREGH(base + PWM_O_TBPRD) = periodCount;
}

//*****************************************************************************
//
//! Gets the PWM period count.
//!
//! \param base is the base address of the PWM module.
//!
//! This function gets the period of the PWM count.
//!
//! \return The period count value.
//
//*****************************************************************************
static inline uint16_t
PWM_getTimeBasePeriod(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Read from TBPRD bit
    //
    return(HWREGH(base + PWM_O_TBPRD));
}

//*****************************************************************************
//
//! Sets the PWM links.
//!
//! \param base is the base address of the PWM module.
//! \param pwmLink is the PWM instance to link with.
//! \param linkComp is the PWM component to link.
//!
//! This function links the component defined in linkComp in the current PWM
//! instance with the linkComp component of the PWM instance defined by
//! pwmLink. A change (a write) in the value of linkComp component of pwmLink
//! instance, causes a change in the current PWM linkComp component.
//! For example if the current PWM is PWM3 and the values of pwmLink and
//! linkComp are PWM_LINK_WITH_PWM_1 and PWM_LINK_COMP_C respectively,
//! then a write to COMPC register in PWM1, will result in a simultaneous
//! write to COMPC register in PWM3.
//! Valid values for pwmLink are:
//!   - PWM_LINK_WITH_PWM_1  - link current PWM with PWM1
//!   - PWM_LINK_WITH_PWM_2  - link current PWM with PWM2
//!   - PWM_LINK_WITH_PWM_3  - link current PWM with PWM3
//!   - PWM_LINK_WITH_PWM_4  - link current PWM with PWM4
//!   - PWM_LINK_WITH_PWM_5  - link current PWM with PWM5
//!   - PWM_LINK_WITH_PWM_6  - link current PWM with PWM6
//!   - PWM_LINK_WITH_PWM_7  - link current PWM with PWM7
//!   - PWM_LINK_WITH_PWM_8  - link current PWM with PWM8
//!
//! Valid values for linkComp are:
//!   - PWM_LINK_TBPRD   - link TBPRD:TBPRDHR registers
//!   - PWM_LINK_COMP_A   - link COMPA registers
//!   - PWM_LINK_COMP_B   - link COMPB registers
//!   - PWM_LINK_COMP_C   - link COMPC registers
//!   - PWM_LINK_COMP_D   - link COMPD registers
//!   - PWM_LINK_GLDCTL2  - link GLDCTL2 registers
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setupPWMLinks(uint32_t base, PWM_CurrentLink pwmLink,
                    PWM_LinkComponent linkComp)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Configure PWM links
    //
    HWREG(base + PWM_O_XLINK) =
              ((HWREG(base + PWM_O_XLINK) & ~((uint32_t)0xFU << linkComp)) |
               ((uint32_t)pwmLink << linkComp));
}

//*****************************************************************************
//
//! Sets up the Counter Compare shadow load mode
//!
//! \param base is the base address of the PWM module.
//! \param compModule is the counter compare module.
//! \param loadMode is the shadow to active load mode.
//!
//! This function enables and sets up the counter compare shadow load mode.
//! Valid values for the variables are:
//!  - compModule
//!      - PWM_COUNTER_COMPARE_A - counter compare A.
//!      - PWM_COUNTER_COMPARE_B - counter compare B.
//!      - PWM_COUNTER_COMPARE_C - counter compare C.
//!      - PWM_COUNTER_COMPARE_D - counter compare D.
//!  - loadMode
//!      - PWM_COMP_LOAD_ON_CNTR_ZERO - load when counter equals zero
//!      - PWM_COMP_LOAD_ON_CNTR_PERIOD - load when counter equals period
//!      - PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals
//!                                             zero or period
//!      - PWM_COMP_LOAD_FREEZE  - Freeze shadow to active load
//!      - PWM_COMP_LOAD_ON_SYNC_CNTR_ZERO - load when counter equals zero
//!      - PWM_COMP_LOAD_ON_SYNC_CNTR_PERIOD -load when counter equals period
//!      - PWM_COMP_LOAD_ON_SYNC_CNTR_ZERO_PERIOD - load when counter equals
//!                                                  zero or period
//!      - PWM_COMP_LOAD_ON_SYNC_ONLY - load on sync only
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setCounterCompareShadowLoadMode(uint32_t base,
                                     PWM_CounterCompareModule compModule,
                                     PWM_CounterCompareLoadMode loadMode)
{
    uint16_t syncModeOffset;
    uint16_t loadModeOffset;
    uint16_t shadowModeOffset;
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    if((compModule == PWM_COUNTER_COMPARE_A) ||
       (compModule == PWM_COUNTER_COMPARE_C))
    {
        syncModeOffset = 10U;
        loadModeOffset = 0U;
        shadowModeOffset = 4U;
    }
    else
    {
        syncModeOffset = 12U;
        loadModeOffset = 2U;
        shadowModeOffset = 6U;
    }

    //
    // Get the register offset.  PWM_O_CMPCTL for A&B or
    // PWM_O_CMPCTL2 for C&D
    //
    registerOffset = base + PWM_O_CMPCTL + (((uint32_t)compModule & 0x1U)) * 2;

    //
    // Set the appropriate sync and load mode bits and also enable shadow
    // load mode. Shadow to active load can also be frozen.
    //
    HWREGH(registerOffset) = ((HWREGH(registerOffset) &
                         ~((0x3U << syncModeOffset) | // Clear sync mode
                           (0x3U << loadModeOffset) | // Clear load mode
                           (0x1U << shadowModeOffset))) | // shadow mode
                         ((((uint16_t)loadMode >> 2U) << syncModeOffset) |
                         (((uint16_t)loadMode & 0x3U) << loadModeOffset)));
}

//*****************************************************************************
//
//! Disable Counter Compare shadow load mode
//!
//! \param base is the base address of the PWM module.
//! \param compModule is the counter compare module.
//!
//! This function disables counter compare shadow load mode.
//! Valid values for the variables are:
//!  - compModule
//!      - PWM_COUNTER_COMPARE_A - counter compare A.
//!      - PWM_COUNTER_COMPARE_B - counter compare B.
//!      - PWM_COUNTER_COMPARE_C - counter compare C.
//!      - PWM_COUNTER_COMPARE_D - counter compare D.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableCounterCompareShadowLoadMode(uint32_t base,
                                         PWM_CounterCompareModule compModule)
{
    uint16_t shadowModeOffset;
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    if((compModule == PWM_COUNTER_COMPARE_A) ||
       (compModule == PWM_COUNTER_COMPARE_C))
    {
        shadowModeOffset = 4U;
    }
    else
    {
        shadowModeOffset = 6U;
    }

    //
    // Get the register offset.  PWM_O_CMPCTL for A&B or
    // PWM_O_CMPCTL2 for C&D
    //
    registerOffset = base + PWM_O_CMPCTL + (((uint32_t)compModule & 0x1U)) * 2;

    //
    // Disable shadow load mode.
    //
    HWREGH(registerOffset) = (HWREGH(registerOffset) |
                             (0x1U << shadowModeOffset));
}

//*****************************************************************************
//
//! Set counter compare values.
//!
//! \param base is the base address of the PWM module.
//! \param compModule is the Counter Compare value module.
//! \param compCount is the counter compare count value.
//!
//! This function sets the counter compare value for counter compare registers.
//! The maximum value for compCount is 0xFFFF.
//! Valid values for compModule are:
//!   - PWM_COUNTER_COMPARE_A - counter compare A.
//!   - PWM_COUNTER_COMPARE_B - counter compare B.
//!   - PWM_COUNTER_COMPARE_C - counter compare C.
//!   - PWM_COUNTER_COMPARE_D - counter compare D.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setCounterCompareValue(uint32_t base, PWM_CounterCompareModule compModule,
                            uint16_t compCount)
{
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Get the register offset for the Counter compare
    //
    registerOffset = PWM_O_CMPA + (uint32_t)compModule * 2; 

    //
    // Write to the counter compare registers.
    //
    if((compModule == PWM_COUNTER_COMPARE_A) ||
        (compModule == PWM_COUNTER_COMPARE_B))
    {
        //
        // Write to COMPA or COMPB bits
        //
        HWREGH(base + registerOffset + 0x1U * 2) = compCount; 
    }
    else
    {
        //
        // Write to COMPC or COMPD bits
        //
        HWREGH(base + registerOffset) = compCount;
    }
}

//*****************************************************************************
//
//! Get counter compare values.
//!
//! \param base is the base address of the PWM module.
//! \param compModule is the Counter Compare value module.
//!
//! This function gets the counter compare value for counter compare registers.
//! Valid values for compModule are:
//!   - PWM_COUNTER_COMPARE_A - counter compare A.
//!   - PWM_COUNTER_COMPARE_B - counter compare B.
//!   - PWM_COUNTER_COMPARE_C - counter compare C.
//!   - PWM_COUNTER_COMPARE_D - counter compare D.
//!
//! \return The counter compare count value.
//
//*****************************************************************************
static inline uint16_t
PWM_getCounterCompareValue(uint32_t base, PWM_CounterCompareModule compModule)
{
    uint32_t registerOffset;
    uint16_t compCount;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Get the register offset for the Counter compare
    //
    registerOffset = PWM_O_CMPA + (uint32_t)compModule * 2;

    //
    // Read from the counter compare registers.
    //
    if((compModule == PWM_COUNTER_COMPARE_A) ||
        (compModule == PWM_COUNTER_COMPARE_B))
    {
        //
        // Read COMPA or COMPB bits
        //
        compCount = (uint16_t)((HWREG(base + registerOffset) &
                     (uint32_t)0xFFFF0000U) >> 16U);
    }
    else
    {
        //
        // Read COMPC or COMPD bits
        //
        compCount = HWREGH(base + registerOffset);
    }
    return(compCount);
}

//*****************************************************************************
//
//! Return the counter compare shadow register full status.
//!
//! \param base is the base address of the PWM module.
//! \param compModule is the Counter Compare value module.
//!
//! This function returns the counter Compare shadow register full status flag.
//! Valid values for compModule are:
//!   - PWM_COUNTER_COMPARE_A - counter compare A.
//!   - PWM_COUNTER_COMPARE_B - counter compare B.
//!
//! \return Returns true if the shadow register is full.
//!         Returns false if the shadow register is not full.
//
//*****************************************************************************
static inline bool
PWM_getCounterCompareShadowStatus(uint32_t base,
                                   PWM_CounterCompareModule compModule)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Check the validity of input.
    // COMPA and COMPB are valid input arguments.
    //
    ASSERT((compModule == PWM_COUNTER_COMPARE_A) ||
            (compModule == PWM_COUNTER_COMPARE_B));

    //
    // Read the value of SHDWAFULL or SHDWBFULL bit
    //
    return((((HWREG(base + PWM_O_CMPCTL) >>
              ((((uint16_t)compModule >> 1U) & 0x1U) + 8U)) &
              0x1U) == 0x1U) ? true:false);
}

//
// Action Qualifier module related APIs
//
//*****************************************************************************
//
//! Sets the Action Qualifier shadow load mode
//!
//! \param base is the base address of the PWM module.
//! \param aqModule is the Action Qualifier module value.
//! \param loadMode is the shadow to active load mode.
//!
//! This function enables and sets the Action Qualifier shadow load mode.
//! Valid values for the variables are:
//!  - aqModule
//!      - PWM_ACTION_QUALIFIER_A - Action Qualifier A.
//!      - PWM_ACTION_QUALIFIER_B - Action Qualifier B.
//!  - loadMode
//!      - PWM_AQ_LOAD_ON_CNTR_ZERO - load when counter equals zero
//!      - PWM_AQ_LOAD_ON_CNTR_PERIOD - load when counter equals period
//!      - PWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals
//!                                               zero or period
//!      - PWM_AQ_LOAD_FREEZE  - Freeze shadow to active load
//!      - PWM_AQ_LOAD_ON_SYNC_CNTR_ZERO - load on sync or when counter
//!                                          equals zero
//!      - PWM_AQ_LOAD_ON_SYNC_CNTR_PERIOD - load on sync or when counter
//!                                           equals period
//!      - PWM_AQ_LOAD_ON_SYNC_CNTR_ZERO_PERIOD - load on sync or when
//!                                               counter equals zero or period
//!      - PWM_AQ_LOAD_ON_SYNC_ONLY - load on sync only
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setActionQualifierShadowLoadMode(uint32_t base,
                                      PWM_ActionQualifierModule aqModule,
                                      PWM_ActionQualifierLoadMode loadMode)
{
    uint16_t syncModeOffset;
    uint16_t shadowModeOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    syncModeOffset = 8U + (uint16_t)aqModule;
    shadowModeOffset = 4U + (uint16_t)aqModule;

    //
    // Set the appropriate sync and load mode bits and also enable shadow
    // load mode. Shadow to active load can also be frozen.
    //
    HWREGH(base + PWM_O_AQCTL) = (((HWREGH(base + PWM_O_AQCTL) &
                                   (~((0x3U << (uint16_t)aqModule) |
                                   (0x3U << (uint16_t)syncModeOffset)))) |
                                   (0x1U << shadowModeOffset)) |
                                   ((((uint16_t)loadMode >> 2U) <<
                                     syncModeOffset) | (((uint16_t)loadMode &
                                    0x3U) << (uint16_t)aqModule)));
}

//*****************************************************************************
//
//! Disable Action Qualifier shadow load mode
//!
//! \param base is the base address of the PWM module.
//! \param aqModule is the Action Qualifier module value.
//!
//! This function disables the Action Qualifier  shadow load mode.
//! Valid values for the variables are:
//!  - aqModule
//!      - PWM_ACTION_QUALIFIER_A - Action Qualifier A.
//!      - PWM_ACTION_QUALIFIER_B - Action Qualifier B.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableActionQualifierShadowLoadMode(uint32_t base,
                                          PWM_ActionQualifierModule aqModule)
{
    uint16_t shadowModeOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    shadowModeOffset = 4U + (uint16_t)aqModule;

    //
    // Disable shadow load mode. Action qualifier is loaded on
    // immediate mode only.
    //
    HWREGH(base + PWM_O_AQCTL) &= ~(1U << shadowModeOffset);
}

//*****************************************************************************
//
//! Set up Action qualifier trigger source for event T1
//!
//! \param base is the base address of the PWM module.
//! \param trigger sources for Action Qualifier triggers.
//!
//! This function sets up the sources for Action Qualifier event T1.
//! Valid values for trigger are:
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1       - Digital compare event A 1
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_DCA_2       - Digital compare event A 2
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_DCB_1       - Digital compare event B 1
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_DCB_2       - Digital compare event B 2
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_TZ_1        - Trip zone 1
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_TZ_2        - Trip zone 2
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_TZ_3        - Trip zone 3
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_PWM_SYNCIN - PWM sync
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_DC_EVTFILT  - Digital compare filter event
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setActionQualifierT1TriggerSource(uint32_t base,
                                     PWM_ActionQualifierTriggerSource trigger)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set T1 trigger source
    //
    HWREGH(base + PWM_O_AQTSRCSEL) =
         ((HWREGH(base + PWM_O_AQTSRCSEL) & (~PWM_AQTSRCSEL_T1SEL_M)) |
          ((uint16_t)trigger));
}

//*****************************************************************************
//
//! Set up Action qualifier trigger source for event T2
//!
//! \param base is the base address of the PWM module.
//! \param trigger sources for Action Qualifier triggers.
//!
//! This function sets up the sources for Action Qualifier event T2.
//! Valid values for trigger are:
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1       - Digital compare event A 1
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_DCA_2       - Digital compare event A 2
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_DCB_1       - Digital compare event B 1
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_DCB_2       - Digital compare event B 2
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_TZ_1        - Trip zone 1
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_TZ_2        - Trip zone 2
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_TZ_3        - Trip zone 3
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_PWM_SYNCIN - PWM sync
//!   - PWM_AQ_TRIGGER_EVENT_TRIG_DC_EVTFILT  - Digital compare filter event
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setActionQualifierT2TriggerSource(uint32_t base,
                                      PWM_ActionQualifierTriggerSource trigger)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set T2 trigger source
    //
    HWREGH(base + PWM_O_AQTSRCSEL) =
          ((HWREGH(base + PWM_O_AQTSRCSEL) & (~PWM_AQTSRCSEL_T2SEL_M)) |
           ((uint16_t)trigger << PWM_AQTSRCSEL_T2SEL_S));
}

//*****************************************************************************
//
//! Set up Action qualifier outputs
//!
//! \param base is the base address of the PWM module.
//! \param pwmOutput is the PWM pin type.
//! \param output is the Action Qualifier output.
//! \param event is the event that causes a change in output.
//!
//! This function sets up the Action Qualifier output on PWM A or PWMB,
//! depending on the value of pwmOutput, to a value specified by outPut based
//! on the input events - specified by event.
//! The following are valid values for the parameters.
//!   - pwmOutput
//!       - PWM_AQ_OUTPUT_A          - PWMxA output
//!       - PWM_AQ_OUTPUT_B          - PWMxB output
//!   - output
//!       - PWM_AQ_OUTPUT_NO_CHANGE  - No change in the output pins
//!       - PWM_AQ_OUTPUT_LOW        - Set output pins to low
//!       - PWM_AQ_OUTPUT_HIGH       - Set output pins to High
//!       - PWM_AQ_OUTPUT_TOGGLE     - Toggle the output pins
//!   - event
//!       - PWM_AQ_OUTPUT_ON_TIMEBASE_ZERO       - Time base counter equals
//!                                                 zero
//!       - PWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD     - Time base counter equals
//!                                                 period
//!       - PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA    - Time base counter up equals
//!                                                 COMPA
//!       - PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA  - Time base counter down
//!                                                 equals COMPA
//!       - PWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB    - Time base counter up equals
//!                                                 COMPB
//!       - PWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB  - Time base counter down
//!                                                 equals COMPB
//!       - PWM_AQ_OUTPUT_ON_T1_COUNT_UP         - T1 event on count up
//!       - PWM_AQ_OUTPUT_ON_T1_COUNT_DOWN       - T1 event on count down
//!       - PWM_AQ_OUTPUT_ON_T2_COUNT_UP         - T2 event on count up
//!       - PWM_AQ_OUTPUT_ON_T2_COUNT_DOWN       - T2 event on count down
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setActionQualifierAction(uint32_t base,
                              PWM_ActionQualifierOutputModule pwmOutput,
                              PWM_ActionQualifierOutput output,
                              PWM_ActionQualifierOutputEvent event)
{
    uint32_t registerOffset;
    uint32_t registerTOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Get the register offset
    //
    registerOffset = PWM_O_AQCTLA + (uint32_t)pwmOutput * 2;
    registerTOffset = PWM_O_AQCTLA2 + (uint32_t)pwmOutput * 2;

    //
    // If the event occurs on T1 or T2 events
    //
    if(((uint16_t)event & 0x1U) == 1U)
    {
        //
        // Write to T1U,T1D,T2U or T2D of AQCTLA2 register
        //
        HWREGH(base + registerTOffset) =
         ((HWREGH(base + registerTOffset) & ~(3U << ((uint16_t)event - 1U))) |
          ((uint16_t)output << ((uint16_t)event - 1U)));
    }
    else
    {
        //
        // Write to ZRO,PRD,CAU,CAD,CBU or CBD bits of AQCTLA register
        //
        HWREGH(base + registerOffset) =
                ((HWREGH(base + registerOffset) & ~(3U << (uint16_t)event)) |
                 ((uint16_t)output << (uint16_t)event));
    }
}

//*****************************************************************************
//
//! Set up Action qualifier event outputs
//!
//! \param base is the base address of the PWM module.
//! \param pwmOutput is the PWM pin type.
//! \param action is the desired action when the specified event occurs
//!
//! This function sets up the Action Qualifier output on PWMA or PWMB,
//! depending on the value of pwmOutput, to a value specified by action.
//! Valid action param values from different time base counter scenarios
//! should be OR'd together to configure complete action for a pwm output.
//! The following are valid values for the parameters.
//!   - pwmOutput
//!       - PWM_AQ_OUTPUT_A          - PWMxA output
//!       - PWM_AQ_OUTPUT_B          - PWMxB output
//!
//!   - action
//!       - When time base counter equals zero
//!         - PWM_AQ_OUTPUT_NO_CHANGE_ZERO   - Time base counter equals zero
//!                                             and no change in output pins
//!         - PWM_AQ_OUTPUT_LOW_ZERO         - Time base counter equals zero
//!                                             and set output pins to low
//!         - PWM_AQ_OUTPUT_HIGH_ZERO        - Time base counter equals zero
//!                                             and set output pins to high
//!         - PWM_AQ_OUTPUT_TOGGLE_ZERO      - Time base counter equals zero
//!                                             and toggle the output pins
//!       - When time base counter equals period
//!         - PWM_AQ_OUTPUT_NO_CHANGE_PERIOD - Time base counter equals period
//!                                             and no change in output pins
//!         - PWM_AQ_OUTPUT_LOW_PERIOD       - Time base counter equals period
//!                                             and set output pins to low
//!         - PWM_AQ_OUTPUT_HIGH_PERIOD      - Time base counter equals period
//!                                             and set output pins to high
//!         - PWM_AQ_OUTPUT_TOGGLE_PERIOD    - Time base counter equals period
//!                                             and toggle the output pins
//!       - When time base counter equals CMPA during up-count
//!         - PWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA  - Time base counter up equals
//!                                               COMPA and no change in the
//!                                               output pins
//!         - PWM_AQ_OUTPUT_LOW_UP_CMPA        - Time base counter up equals
//!                                               COMPA and set output pins low
//!         - PWM_AQ_OUTPUT_HIGH_UP_CMPA       - Time base counter up equals
//!                                               COMPA and set output pins high
//!         - PWM_AQ_OUTPUT_TOGGLE_UP_CMPA     - Time base counter up equals
//!                                               COMPA and toggle output pins
//!       - When time base counter equals CMPA during down-count
//!         - PWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA - Time base counter down equals
//!                                                COMPA and no change in the
//!                                                output pins
//!         - PWM_AQ_OUTPUT_LOW_DOWN_CMPA      - Time base counter down equals
//!                                               COMPA and set output pins low
//!         - PWM_AQ_OUTPUT_HIGH_DOWN_CMPA     - Time base counter down equals
//!                                               COMPA and set output pins high
//!         - PWM_AQ_OUTPUT_TOGGLE_DOWN_CMPA   - Time base counter down equals
//!                                               COMPA and toggle output pins
//!       - When time base counter equals CMPB during up-count
//!         - PWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB  - Time base counter up equals
//!                                               COMPB and no change in the
//!                                               output pins
//!         - PWM_AQ_OUTPUT_LOW_UP_CMPB        - Time base counter up equals
//!                                               COMPB and set output pins low
//!         - PWM_AQ_OUTPUT_HIGH_UP_CMPB       - Time base counter up equals
//!                                               COMPB and set output pins high
//!         - PWM_AQ_OUTPUT_TOGGLE_UP_CMPB     - Time base counter up equals
//!                                               COMPB and toggle output pins
//!       - When time base counter equals CMPB during down-count
//!         - PWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB- Time base counter down equals
//!                                               COMPB and no change in the
//!                                               output pins
//!         - PWM_AQ_OUTPUT_LOW_DOWN_CMPB      - Time base counter down equals
//!                                               COMPB and set output pins low
//!         - PWM_AQ_OUTPUT_HIGH_DOWN_CMPB     - Time base counter down equals
//!                                               COMPB and set output pins high
//!         - PWM_AQ_OUTPUT_TOGGLE_DOWN_CMPB   - Time base counter down equals
//!                                               COMPB and toggle output pins
//!
//! \b note:  A logical OR of the valid values should be passed as the action
//!           parameter. Single action should be configured for each time base
//!           counter scenario.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setActionQualifierActionComplete(uint32_t base,
                                   PWM_ActionQualifierOutputModule pwmOutput,
                                   uint16_t action)
{
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Get the register offset
    //
    registerOffset = PWM_O_AQCTLA + (uint32_t)pwmOutput * 2;

    //
    // Write to ZRO, PRD, CAU, CAD, CBU or CBD bits of AQCTLA register
    //
    HWREGH(base + registerOffset) = (uint16_t)action;
}

//*****************************************************************************
//
//! Set up Additional action qualifier event outputs
//!
//! \param base is the base address of the PWM module.
//! \param pwmOutput is the PWM pin type.
//! \param action is the desired action when the specified event occurs
//!
//! This function sets up the Additional Action Qualifier output on PWMA or
//! PWMB depending on the value of pwmOutput, to a value specified by action.
//! Valid action param values from different event scenarios should be OR'd
//! together to configure complete action for a pwm output.
//! The following are valid values for the parameters.
//!   - pwmOutput
//!       - PWM_AQ_OUTPUT_A          - PWMxA output
//!       - PWM_AQ_OUTPUT_B          - PWMxB output
//!   - action
//!       - When T1 event occurs during up-count
//!         - PWM_AQ_OUTPUT_NO_CHANGE_UP_T1  - T1 event on count up
//!                                             and no change in output pins
//!         - PWM_AQ_OUTPUT_LOW_UP_T1        - T1 event on count up
//!                                           and set output pins to low
//!         - PWM_AQ_OUTPUT_HIGH_UP_T1       - T1 event on count up
//!                                           and set output pins to high
//!         - PWM_AQ_OUTPUT_TOGGLE_UP_T1     - T1 event on count up
//!                                           and toggle the output pins
//!       - When T1 event occurs during down-count
//!         - PWM_AQ_OUTPUT_NO_CHANGE_DOWN_T1- T1 event on count down
//!                                           and no change in output pins
//!         - PWM_AQ_OUTPUT_LOW_DOWN_T1      - T1 event on count down
//!                                           and set output pins to low
//!         - PWM_AQ_OUTPUT_HIGH_DOWN_T1     - T1 event on count down
//!                                           and set output pins to high
//!         - PWM_AQ_OUTPUT_TOGGLE_DOWN_T1   - T1 event on count down
//!                                           and toggle the output pins
//!       - When T2 event occurs during up-count
//!         - PWM_AQ_OUTPUT_NO_CHANGE_UP_T2  - T2 event on count up
//!                                             and no change in output pins
//!         - PWM_AQ_OUTPUT_LOW_UP_T2        - T2 event on count up
//!                                             and set output pins to low
//!         - PWM_AQ_OUTPUT_HIGH_UP_T2       - T2 event on count up
//!                                             and set output pins to high
//!         - PWM_AQ_OUTPUT_TOGGLE_UP_T2     - T2 event on count up
//!                                             and toggle the output pins
//!       - When T2 event occurs during down-count
//!         - PWM_AQ_OUTPUT_NO_CHANGE_DOWN_T2 - T2 event on count down
//!                                              and no change in output pins
//!         - PWM_AQ_OUTPUT_LOW_DOWN_T2       - T2 event on count down
//!                                              and set output pins to low
//!         - PWM_AQ_OUTPUT_HIGH_DOWN_T2      - T2 event on count down
//!                                              and set output pins to high
//!         - PWM_AQ_OUTPUT_TOGGLE_DOWN_T2    - T2 event on count down
//!                                              and toggle the output pins
//!
//! \b note:  A logical OR of the valid values should be passed as the action
//!           parameter. Single action should be configured for each event
//!           scenario.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setAdditionalActionQualifierActionComplete(uint32_t base,
                               PWM_ActionQualifierOutputModule pwmOutput,
                               uint16_t action)
{
    uint32_t registerTOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Get the register offset
    //
    registerTOffset = (uint32_t)(PWM_O_AQCTLA2 + (uint16_t)pwmOutput * 2);

    //
    // Write to T1U, T1D, T2U or T2D of AQCTLA2 register
    //
    HWREGH(base + registerTOffset) = (uint16_t)action;
}

//*****************************************************************************
//
//! Sets up Action qualifier continuous software load mode.
//!
//! \param base is the base address of the PWM module.
//! \param mode is the mode for shadow to active load mode.
//!
//! This function sets up the AQCFRSC register load mode for continuous
//! software force reload mode. The software force actions are determined by
//! the PWM_setActionQualifierContSWForceAction() function.
//! Valid values for mode are:
//!   - PWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO        - shadow mode load when counter
//!                                               equals zero
//!   - PWM_AQ_SW_SH_LOAD_ON_CNTR_PERIOD      - shadow mode load when counter
//!                                               equals period
//!   - PWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO_PERIOD - shadow mode load when counter
//!                                               equals zero or period
//!   - PWM_AQ_SW_IMMEDIATE_LOAD               - immediate mode load only
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setActionQualifierContSWForceShadowMode(uint32_t base,
                                             PWM_ActionQualifierContForce mode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the Action qualifier software action reload mode.
    // Write to RLDCSF bit
    //
    HWREGH(base + PWM_O_AQSFRC) =
            ((HWREGH(base + PWM_O_AQSFRC) & ~PWM_AQSFRC_RLDCSF_M) |
             ((uint16_t)mode << PWM_AQSFRC_RLDCSF_S));
}

//*****************************************************************************
//
//! Triggers a continuous software forced event.
//!
//! \param base is the base address of the PWM module.
//! \param pwmOutput is the PWM pin type.
//! \param output is the Action Qualifier output.
//!
//! This function triggers a continuous software forced Action Qualifier output
//! on PWM A or B based on the value of pwmOutput.
//! Valid values for the parameters are:
//!   - pwmOutput
//!       - PWM_AQ_OUTPUT_A          - PWMxA output
//!       - PWM_AQ_OUTPUT_B          - PWMxB output
//!   - output
//!       - PWM_AQ_SW_DISABLED       - Software forcing disabled.
//!       - PWM_AQ_SW_OUTPUT_LOW     - Set output pins to low
//!       - PWM_AQ_SW_OUTPUT_HIGH    - Set output pins to High
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setActionQualifierContSWForceAction(uint32_t base,
                                    PWM_ActionQualifierOutputModule pwmOutput,
                                    PWM_ActionQualifierSWOutput output)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Initiate a continuous software forced output
    //
    if(pwmOutput == PWM_AQ_OUTPUT_A)
    {
        HWREGH(base + PWM_O_AQCSFRC) =
                ((HWREGH(base + PWM_O_AQCSFRC) & ~PWM_AQCSFRC_CSFA_M) |
                 ((uint16_t)output));
    }
    else
    {
        HWREGH(base + PWM_O_AQCSFRC) =
                ((HWREGH(base + PWM_O_AQCSFRC) & ~PWM_AQCSFRC_CSFB_M) |
                 ((uint16_t)output << PWM_AQCSFRC_CSFB_S)) ;
    }
}

//*****************************************************************************
//
//! Set up one time software forced Action qualifier outputs
//!
//! \param base is the base address of the PWM module.
//! \param pwmOutput is the PWM pin type.
//! \param output is the Action Qualifier output.
//!
//! This function sets up the one time software forced Action Qualifier output
//! on PWM A or PWMB, depending on the value of pwmOutput to a value
//! specified by outPut.
//! The following are valid values for the parameters.
//!   - pwmOutput
//!       - PWM_AQ_OUTPUT_A          - PWMxA output
//!       - PWM_AQ_OUTPUT_B          - PWMxB output
//!   - output
//!       - PWM_AQ_OUTPUT_NO_CHANGE  - No change in the output pins
//!       - PWM_AQ_OUTPUT_LOW        - Set output pins to low
//!       - PWM_AQ_OUTPUT_HIGH       - Set output pins to High
//!       - PWM_AQ_OUTPUT_TOGGLE     - Toggle the output pins
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setActionQualifierSWAction(uint32_t base,
                                PWM_ActionQualifierOutputModule pwmOutput,
                                PWM_ActionQualifierOutput output)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the one time software forced action
    //
    if(pwmOutput == PWM_AQ_OUTPUT_A)
    {
        HWREGH(base + PWM_O_AQSFRC) =
                    ((HWREGH(base + PWM_O_AQSFRC) & ~PWM_AQSFRC_ACTSFA_M) |
                     ((uint16_t)output));
    }
    else
    {
        HWREGH(base + PWM_O_AQSFRC) =
                    ((HWREGH(base + PWM_O_AQSFRC) & ~PWM_AQSFRC_ACTSFB_M) |
                     ((uint16_t)output << PWM_AQSFRC_ACTSFB_S));
    }
}

//*****************************************************************************
//
//! Triggers a one time software forced event on Action qualifier
//!
//! \param base is the base address of the PWM module.
//! \param pwmOutput is the PWM pin type.
//!
//! This function triggers a one time software forced Action Qualifier event
//! on PWM A or B based on the value of pwmOutput.
//! Valid values for pwmOutput are:
//!   - PWM_AQ_OUTPUT_A          - PWMxA output
//!   - PWM_AQ_OUTPUT_B          - PWMxB output
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_forceActionQualifierSWAction(uint32_t base,
                                  PWM_ActionQualifierOutputModule pwmOutput)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Initiate a software forced event
    //
    if(pwmOutput == PWM_AQ_OUTPUT_A)
    {
        HWREGH(base + PWM_O_AQSFRC) |= PWM_AQSFRC_OTSFA;
    }
    else
    {
        HWREGH(base + PWM_O_AQSFRC) |= PWM_AQSFRC_OTSFB;
    }
}

//
// Dead Band Module related APIs
//
//*****************************************************************************
//
//! Sets Dead Band signal output swap mode.
//!
//! \param base is the base address of the PWM module.
//! \param output is the PWM Dead Band output.
//! \param enableSwapMode is the output swap mode.
//!
//! This function sets up the output signal swap mode. For example if the
//! output variable is set to PWM_DB_OUTPUT_A and enableSwapMode is true, then
//! the PWM A output gets its signal from the PWM B signal path. Valid values
//! for the input variables are:
//!  - output
//!      - PWM_DB_OUTPUT_A   - PWM output A
//!      - PWM_DB_OUTPUT_B   - PWM output B
//!  - enableSwapMode
//!      - true     - the output is swapped
//!      - false    - the output and the signal path are the same.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setDeadBandOutputSwapMode(uint32_t base, PWM_DeadBandOutput output,
                               bool enableSwapMode)
{
    uint16_t mask;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    mask = (uint16_t)1U << ((uint16_t)output + PWM_DBCTL_OUTSWAP_S);

    if(enableSwapMode)
    {
        //
        // Set the appropriate outswap bit to swap output
        //
        HWREGH(base + PWM_O_DBCTL) = (HWREGH(base + PWM_O_DBCTL) | mask);
    }
    else
    {
        //
        // Clear the appropriate outswap bit to disable output swap
        //
        HWREGH(base + PWM_O_DBCTL) = (HWREGH(base + PWM_O_DBCTL) & ~mask);
    }
}

//*****************************************************************************
//
//! Sets Dead Band signal output mode.
//!
//! \param base is the base address of the PWM module.
//! \param delayMode is the Dead Band delay type.
//! \param enableDelayMode is the dead band delay mode.
//!
//! This function sets up the dead band delay mode. The delayMode variable
//! determines if the applied delay is Rising Edge or Falling Edge. The
//! enableDelayMode determines if a dead band delay should be applied.
//! Valid values for the variables are:
//!  - delayMode
//!      - PWM_DB_RED   - Rising Edge delay
//!      - PWM_DB_FED   - Falling Edge delay
//!  - enableDelayMode
//!      - true     - Falling edge or Rising edge delay is applied.
//!      - false    - Dead Band delay is bypassed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setDeadBandDelayMode(uint32_t base, PWM_DeadBandDelayMode delayMode,
                          bool enableDelayMode)
{
    uint16_t mask;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    mask = (uint16_t)1U << ((uint16_t)delayMode + PWM_DBCTL_OUT_MODE_S);

    if(enableDelayMode)
    {
         //
         // Set the appropriate outmode bit to enable Dead Band delay
         //
         HWREGH(base + PWM_O_DBCTL) = (HWREGH(base + PWM_O_DBCTL) | mask);
    }
    else
    {
        //
        // Clear the appropriate outswap bit to disable output swap
        //
        HWREGH(base + PWM_O_DBCTL) = (HWREGH(base + PWM_O_DBCTL) & ~ mask);
    }
}

//*****************************************************************************
//
//! Sets Dead Band delay polarity.
//!
//! \param base is the base address of the PWM module.
//! \param delayMode is the Dead Band delay type.
//! \param polarity is the polarity of the delayed signal.
//!
//! This function sets up the polarity as determined by the variable polarity
//! of the Falling Edge or Rising Edge delay depending on the value of
//! delayMode. Valid values for the variables are:
//!   - delayMode
//!       - PWM_DB_RED   - Rising Edge delay
//!       - PWM_DB_FED   - Falling Edge delay
//!   - polarity
//!       - PWM_DB_POLARITY_ACTIVE_HIGH   - polarity is not inverted.
//!       - PWM_DB_POLARITY_ACTIVE_LOW    - polarity is inverted.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setDeadBandDelayPolarity(uint32_t base,
                              PWM_DeadBandDelayMode delayMode,
                              PWM_DeadBandPolarity polarity)
{
    uint16_t shift;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    shift = (((uint16_t)delayMode ^ 0x1U) + PWM_DBCTL_POLSEL_S);

    //
    // Set the appropriate polsel bits for dead band polarity
    //
    HWREGH(base + PWM_O_DBCTL) =
                       ((HWREGH(base + PWM_O_DBCTL) & ~ (1U << shift)) |
                        ((uint16_t)polarity << shift));
}

//*****************************************************************************
//
//! Sets Rising Edge Dead Band delay input.
//!
//! \param base is the base address of the PWM module.
//! \param input is the input signal to the dead band.
//!
//! This function sets up the rising Edge delay input signal.
//! Valid values for input are:
//!     - PWM_DB_INPUT_PWMA   - Input signal is PWMA( Valid for both Falling
//!                                  Edge and Rising Edge)
//!     - PWM_DB_INPUT_PWMB   - Input signal is PWMB( Valid for both Falling
//!                                  Edge and Rising Edge)
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setRisingEdgeDeadBandDelayInput(uint32_t base, uint16_t input)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT((input == PWM_DB_INPUT_PWMA) ||
           (input == PWM_DB_INPUT_PWMB));

    //
    // Set the Rising Edge Delay input
    //
    HWREGH(base + PWM_O_DBCTL) =
            ((HWREGH(base + PWM_O_DBCTL) & ~(1U << (PWM_DBCTL_IN_MODE_S))) |
             (input << PWM_DBCTL_IN_MODE_S));
}

//*****************************************************************************
//
//! Sets Dead Band delay input.
//!
//! \param base is the base address of the PWM module.
//! \param input is the input signal to the dead band.
//!
//! This function sets up the rising Edge delay input signal.
//! Valid values for input are:
//!   - PWM_DB_INPUT_PWMA   - Input signal is PWMA(Valid for both Falling
//!                                Edge and Rising Edge)
//!   - PWM_DB_INPUT_PWMB   - Input signal is PWMB(Valid for both Falling
//!                                Edge and Rising Edge)
//!   - PWM_DB_INPUT_DB_RED  - Input signal is the output of Rising
//!                                Edge delay.
//!                               (Valid only for Falling Edge delay)
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setFallingEdgeDeadBandDelayInput(uint32_t base, uint16_t input)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT((input == PWM_DB_INPUT_PWMA) ||
           (input == PWM_DB_INPUT_PWMB) ||
           (input == PWM_DB_INPUT_DB_RED));

    if(input == PWM_DB_INPUT_DB_RED)
    {
        //
        // Set the Falling Edge Delay input
        //
        HWREGH(base + PWM_O_DBCTL) |= PWM_DBCTL_DEDB_MODE;
    }
    else
    {
        //
        // Set the Falling Edge Delay input
        //
        HWREGH(base + PWM_O_DBCTL) &= ~PWM_DBCTL_DEDB_MODE;

        //
        // Set the Rising Edge Delay input
        //
        HWREGH(base + PWM_O_DBCTL) =
        ((HWREGH(base + PWM_O_DBCTL) & ~(1U << (PWM_DBCTL_IN_MODE_S + 1U))) |
         (input << (PWM_DBCTL_IN_MODE_S + 1U)));
    }
}

//*****************************************************************************
//
//! Set the Dead Band control shadow load mode.
//!
//! \param base is the base address of the PWM module.
//! \param loadMode is the shadow to active load mode.
//!
//! This function enables and sets the Dead Band control register shadow
//! load mode.
//! Valid values for the \e loadMode parameter are:
//!     - PWM_DB_LOAD_ON_CNTR_ZERO         - load when counter equals zero.
//!     - PWM_DB_LOAD_ON_CNTR_PERIOD       - load when counter equals period.
//!     - PWM_DB_LOAD_ON_CNTR_ZERO_PERIOD  - load when counter equals zero or
//!                                            period.
//!     - PWM_DB_LOAD_FREEZE                - Freeze shadow to active load.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setDeadBandControlShadowLoadMode(uint32_t base,
                                      PWM_DeadBandControlLoadMode loadMode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable the shadow mode and setup the load event
    //
    HWREGH(base + PWM_O_DBCTL2) =
          ((HWREGH(base + PWM_O_DBCTL2) & ~PWM_DBCTL2_LOADDBCTLMODE_M) |
           (PWM_DBCTL2_SHDWDBCTLMODE | (uint16_t)loadMode));
}

//*****************************************************************************
//
//! Disable Dead Band control shadow load mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables the Dead Band control register shadow
//! load mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableDeadBandControlShadowLoadMode(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable the shadow load mode. Only immediate load mode only.
    //
    HWREGH(base + PWM_O_DBCTL2) =
                 (HWREGH(base + PWM_O_DBCTL2) & ~PWM_DBCTL2_SHDWDBCTLMODE);
}

//*****************************************************************************
//
//! Set the RED (Rising Edge Delay) shadow load mode.
//!
//! \param base is the base address of the PWM module.
//! \param loadMode is the shadow to active load event.
//!
//! This function sets the Rising Edge Delay register shadow load mode.
//! Valid values for the \e loadMode parameter are:
//!     - PWM_RED_LOAD_ON_CNTR_ZERO        - load when counter equals zero.
//!     - PWM_RED_LOAD_ON_CNTR_PERIOD      - load when counter equals period.
//!     - PWM_RED_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals zero or
//!                                           period.
//!     - PWM_RED_LOAD_FREEZE               - Freeze shadow to active load.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setRisingEdgeDelayCountShadowLoadMode(uint32_t base,
                                         PWM_RisingEdgeDelayLoadMode loadMode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable the shadow mode. Set-up the load mode
    //
    HWREGH(base + PWM_O_DBCTL) =
               ((HWREGH(base + PWM_O_DBCTL) & ~PWM_DBCTL_LOADREDMODE_M) |
                ((uint16_t)PWM_DBCTL_SHDWDBREDMODE |
                ((uint16_t)loadMode << PWM_DBCTL_LOADREDMODE_S)));

}

//*****************************************************************************
//
//! Disable the RED (Rising Edge Delay) shadow load mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables the Rising Edge Delay register shadow load mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableRisingEdgeDelayCountShadowLoadMode(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable the shadow mode.
    //
    HWREGH(base + PWM_O_DBCTL) =
                   (HWREGH(base + PWM_O_DBCTL) & ~PWM_DBCTL_SHDWDBREDMODE);

}

//*****************************************************************************
//
//! Set the FED (Falling Edge Delay) shadow load mode.
//!
//! \param base is the base address of the PWM module.
//! \param loadMode is the shadow to active load event.
//!
//! This function enables and sets the Falling Edge Delay register shadow load
//! mode. Valid values for the \e loadMode parameters are:
//!     - PWM_FED_LOAD_ON_CNTR_ZERO        - load when counter equals zero.
//!     - PWM_FED_LOAD_ON_CNTR_PERIOD      - load when counter equals period.
//!     - PWM_FED_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals zero or
//!                                            period.
//!     - PWM_FED_LOAD_FREEZE               - Freeze shadow to active load.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setFallingEdgeDelayCountShadowLoadMode(uint32_t base,
                                        PWM_FallingEdgeDelayLoadMode loadMode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable the shadow mode. Setup the load mode.
    //
    HWREGH(base + PWM_O_DBCTL) =
            ((HWREGH(base + PWM_O_DBCTL) & ~PWM_DBCTL_LOADFEDMODE_M) |
                (PWM_DBCTL_SHDWDBFEDMODE |
                ((uint16_t)loadMode << PWM_DBCTL_LOADFEDMODE_S)));

}

//*****************************************************************************
//
//! Disables the FED (Falling Edge Delay) shadow load mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables the Falling Edge Delay register shadow load mode.
//! Valid values for the parameters are:
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableFallingEdgeDelayCountShadowLoadMode(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable the shadow mode.
    //
    HWREGH(base + PWM_O_DBCTL) =
              (HWREGH(base + PWM_O_DBCTL) & ~PWM_DBCTL_SHDWDBFEDMODE);
}

//*****************************************************************************
//
//! Sets Dead Band Counter clock rate.
//!
//! \param base is the base address of the PWM module.
//! \param clockMode is the Dead Band counter clock mode.
//!
//! This function sets up the Dead Band counter clock rate with respect to
//! TBCLK (PWM time base counter).
//! Valid values for clockMode are:
//!   - PWM_DB_COUNTER_CLOCK_FULL_CYCLE  -Dead band counter runs at TBCLK
//!                                           (PWM Time Base Counter) rate.
//!   - PWM_DB_COUNTER_CLOCK_HALF_CYCLE  -Dead band counter runs at 2*TBCLK
//!                                         (twice PWM Time Base Counter)rate.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setDeadBandCounterClock(uint32_t base,
                             PWM_DeadBandClockMode clockMode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the DB clock mode
    //
    HWREGH(base + PWM_O_DBCTL) =
                ((HWREGH(base + PWM_O_DBCTL) & ~PWM_DBCTL_HALFCYCLE) |
                 ((uint16_t)clockMode << 15U));
}

//*****************************************************************************
//
//! Set PWM RED count
//!
//! \param base is the base address of the PWM module.
//! \param redCount is the RED(Rising Edge Delay) count.
//!
//! This function sets the RED (Rising Edge Delay) count value.
//! The value of redCount should be less than 0x4000U.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setRisingEdgeDelayCount(uint32_t base, uint16_t redCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(redCount < 0x4000U);

    //
    // Set the RED (Rising Edge Delay) count
    //
    HWREGH(base + PWM_O_DBRED) = redCount;
}

//*****************************************************************************
//
//! Set PWM FED count
//!
//! \param base is the base address of the PWM module.
//! \param fedCount is the FED(Falling Edge Delay) count.
//!
//! This function sets the FED (Falling Edge Delay) count value.
//! The value of fedCount should be less than 0x4000U.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setFallingEdgeDelayCount(uint32_t base, uint16_t fedCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(fedCount < 0x4000U);

    //
    // Set the RED (Rising Edge Delay) count
    //
    HWREGH(base + PWM_O_DBFED) = fedCount;
}

//
// Chopper module related APIs
//
//*****************************************************************************
//
//! Enable chopper mode
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables PWM chopper module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableChopper(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set CHPEN bit. Enable Chopper
    //
    HWREGH(base + PWM_O_PCCTL) |= PWM_PCCTL_CHPEN;
}

//*****************************************************************************
//
//! Disable chopper mode
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables PWM chopper module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableChopper(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Clear CHPEN bit. Disable Chopper
    //
    HWREGH(base + PWM_O_PCCTL) &= ~PWM_PCCTL_CHPEN;
}

//*****************************************************************************
//
//! Set chopper duty cycle.
//!
//! \param base is the base address of the PWM module.
//! \param dutyCycleCount is the chopping clock duty cycle count.
//!
//! This function sets the chopping clock duty cycle. The value of
//! dutyCycleCount should be less than 7. The dutyCycleCount value is converted
//! to the actual chopper duty cycle value base on the following equation:
//!   chopper duty cycle = (dutyCycleCount + 1) / 8
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setChopperDutyCycle(uint32_t base, uint16_t dutyCycleCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(dutyCycleCount < 7U);

    //
    // Set the chopper duty cycle
    //
    HWREGH(base + PWM_O_PCCTL) =
               ((HWREGH(base + PWM_O_PCCTL) & ~PWM_PCCTL_CHPDUTY_M) |
                (dutyCycleCount << PWM_PCCTL_CHPDUTY_S));
}

//*****************************************************************************
//
//! Set chopper clock frequency scaler.
//!
//! \param base is the base address of the PWM module.
//! \param freqDiv is the chopping clock frequency divider.
//!
//! This function sets the scaler for the chopping clock frequency. The value
//! of freqDiv should be less than 8. The chopping clock frequency is altered
//! based on the following equation.
//!   chopper clock frequency = APBCLKOUT / ( 1 + freqDiv)
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setChopperFreq(uint32_t base, uint16_t freqDiv)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(freqDiv < 8U);

    //
    // Set the chopper clock
    //
    HWREGH(base + PWM_O_PCCTL) =
                    ((HWREGH(base + PWM_O_PCCTL) &
                      ~(uint16_t)PWM_PCCTL_CHPFREQ_M) |
                       (freqDiv << PWM_PCCTL_CHPFREQ_S));
}

//*****************************************************************************
//
//! Set chopper clock frequency scaler.
//!
//! \param base is the base address of the PWM module.
//! \param firstPulseWidth is the width of the first pulse.
//!
//! This function sets the first pulse width of chopper output waveform. The
//! value of firstPulseWidth should be less than 0x10. The value of the first
//! pulse width in seconds is given using the following equation:
//!     first pulse width = 1 / (((firstPulseWidth + 1) * APBCLKOUT)/8)
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setChopperFirstPulseWidth(uint32_t base, uint16_t firstPulseWidth)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(firstPulseWidth < 16U);

    //
    // Set the chopper clock
    //
    HWREGH(base + PWM_O_PCCTL) =
              ((HWREGH(base + PWM_O_PCCTL) &
               ~(uint16_t)PWM_PCCTL_OSHTWTH_M) |
               (firstPulseWidth << PWM_PCCTL_OSHTWTH_S));
}

//
// Trip Zone module related APIs
//
//*****************************************************************************
//
//! Enables Trip Zone signal.
//!
//! \param base is the base address of the PWM module.
//! \param tzSignal is the Trip Zone signal.
//!
//! This function enables the Trip Zone signals specified by tzSignal as a
//! source for the Trip Zone module.
//! Valid values for tzSignal are:
//!   - PWM_TZ_SIGNAL_CBC1       - TZ1 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_CBC2       - TZ2 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_CBC3       - TZ3 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_CBC4       - TZ4 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_CBC5       - TZ5 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_CBC6       - TZ6 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_DCAEVT2    - DCAEVT2 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_DCBEVT2    - DCBEVT2 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_OSHT1      - One-shot TZ1
//!   - PWM_TZ_SIGNAL_OSHT2      - One-shot TZ2
//!   - PWM_TZ_SIGNAL_OSHT3      - One-shot TZ3
//!   - PWM_TZ_SIGNAL_OSHT4      - One-shot TZ4
//!   - PWM_TZ_SIGNAL_OSHT5      - One-shot TZ5
//!   - PWM_TZ_SIGNAL_OSHT6      - One-shot TZ6
//!   - PWM_TZ_SIGNAL_DCAEVT1    - One-shot DCAEVT1
//!   - PWM_TZ_SIGNAL_DCBEVT1    - One-shot DCBEVT1
//!
//! \b note:  A logical OR of the valid values can be passed as the tzSignal
//!           parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableTripZoneSignals(uint32_t base, uint16_t tzSignal)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the trip zone bits
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZSEL) |= tzSignal;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables Trip Zone signal.
//!
//! \param base is the base address of the PWM module.
//! \param tzSignal is the Trip Zone signal.
//!
//! This function disables the Trip Zone signal specified by tzSignal as a
//! source for the Trip Zone module.
//! Valid values for tzSignal are:
//!   - PWM_TZ_SIGNAL_CBC1       - TZ1 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_CBC2       - TZ2 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_CBC3       - TZ3 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_CBC4       - TZ4 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_CBC5       - TZ5 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_CBC6       - TZ6 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_DCAEVT2    - DCAEVT2 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_DCBEVT2    - DCBEVT2 Cycle By Cycle
//!   - PWM_TZ_SIGNAL_OSHT1      - One-shot TZ1
//!   - PWM_TZ_SIGNAL_OSHT2      - One-shot TZ2
//!   - PWM_TZ_SIGNAL_OSHT3      - One-shot TZ3
//!   - PWM_TZ_SIGNAL_OSHT4      - One-shot TZ4
//!   - PWM_TZ_SIGNAL_OSHT5      - One-shot TZ5
//!   - PWM_TZ_SIGNAL_OSHT6      - One-shot TZ6
//!   - PWM_TZ_SIGNAL_DCAEVT1    - One-shot DCAEVT1
//!   - PWM_TZ_SIGNAL_DCBEVT1    - One-shot DCBEVT1
//!
//! \b note:  A logical OR of the valid values can be passed as the tzSignal
//!           parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableTripZoneSignals(uint32_t base, uint16_t tzSignal)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Clear the trip zone bits
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZSEL) &= ~tzSignal;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Digital compare conditions that cause Trip Zone event.
//!
//! \param base is the base address of the PWM module.
//! \param dcType is the Digital compare output type.
//! \param dcEvent is the Digital Compare output event.
//!
//! This function sets up the Digital Compare output Trip Zone event sources.
//! The dcType variable specifies the event source to be whether Digital
//! Compare output A or Digital Compare output B. The dcEvent parameter
//! specifies the event that causes Trip Zone.
//! Valid values for the parameters are:
//!  - dcType
//!      - PWM_TZ_DC_OUTPUT_A1     - Digital Compare output 1 A
//!      - PWM_TZ_DC_OUTPUT_A2     - Digital Compare output 2 A
//!      - PWM_TZ_DC_OUTPUT_B1     - Digital Compare output 1 B
//!      - PWM_TZ_DC_OUTPUT_B2     - Digital Compare output 2 B
//!  - dcEvent
//!      - PWM_TZ_EVENT_DC_DISABLED         - Event Trigger is disabled
//!      - PWM_TZ_EVENT_DCXH_LOW            - Trigger event when DCxH low
//!      - PWM_TZ_EVENT_DCXH_HIGH           - Trigger event when DCxH high
//!      - PWM_TZ_EVENT_DCXL_LOW            - Trigger event when DCxL low
//!      - PWM_TZ_EVENT_DCXL_HIGH           - Trigger event when DCxL high
//!      - PWM_TZ_EVENT_DCXL_HIGH_DCXH_LOW  - Trigger event when DCxL high
//!                                            DCxH low
//!
//!  \note x in DCxH/DCxL represents DCAH/DCAL or DCBH/DCBL
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setTripZoneDigitalCompareEventCondition(uint32_t base,
                                 PWM_TripZoneDigitalCompareOutput dcType,
                                 PWM_TripZoneDigitalCompareOutputEvent dcEvent)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set Digital Compare Events conditions that cause a Digital Compare trip
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZDCSEL) =
           ((HWREGH(base + PWM_O_TZDCSEL) & ~(0x7U << (uint16_t)dcType)) |
            ((uint16_t)dcEvent << (uint16_t)dcType));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable advanced Trip Zone event Action.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables the advanced actions of the Trip Zone events. The
//! advanced features combine the trip zone events with the direction of the
//! counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableTripZoneAdvAction(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable Advanced feature. Set ETZE bit
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZCTL2) |= PWM_TZCTL2_ETZE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable advanced Trip Zone event Action.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables the advanced actions of the Trip Zone events.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableTripZoneAdvAction(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable Advanced feature. clear ETZE bit
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZCTL2) &= ~PWM_TZCTL2_ETZE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Trip Zone Action.
//!
//! \param base is the base address of the PWM module.
//! \param tzEvent is the Trip Zone event type.
//! \param tzAction is the Trip zone Action.
//!
//! This function sets the Trip Zone Action to be taken when a Trip Zone event
//! occurs.
//! Valid values for the parameters are:
//!  - tzEvent
//!      - PWM_TZ_ACTION_EVENT_DCBEVT2  - DCBEVT2 (Digital Compare B event 2)
//!      - PWM_TZ_ACTION_EVENT_DCBEVT1  - DCBEVT1 (Digital Compare B event 1)
//!      - PWM_TZ_ACTION_EVENT_DCAEVT2  - DCAEVT2 (Digital Compare A event 2)
//!      - PWM_TZ_ACTION_EVENT_DCAEVT1  - DCAEVT1 (Digital Compare A event 1)
//!      - PWM_TZ_ACTION_EVENT_TZB      - TZ1 - TZ6, DCBEVT2, DCBEVT1
//!      - PWM_TZ_ACTION_EVENT_TZA      - TZ1 - TZ6, DCAEVT2, DCAEVT1
//!  - tzAction
//!      - PWM_TZ_ACTION_HIGH_Z         - high impedance output
//!      - PWM_TZ_ACTION_HIGH           - high output
//!      - PWM_TZ_ACTION_LOW            - low low
//!      - PWM_TZ_ACTION_DISABLE        - disable action
//!
//! \note Disable the advanced Trip Zone event using
//!       PWM_disableTripZoneAdvAction()  before calling this function.
//! \note This function operates on both PWMA and PWMB depending on the
//!       tzEvent parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setTripZoneAction(uint32_t base, PWM_TripZoneEvent tzEvent,
                       PWM_TripZoneAction tzAction)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the Action for Trip Zone events
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZCTL) =
         ((HWREGH(base + PWM_O_TZCTL) & ~(0x3U << (uint16_t)tzEvent)) |
          ((uint16_t)tzAction << (uint16_t)tzEvent)) ;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Advanced Trip Zone Action.
//!
//! \param base is the base address of the PWM module.
//! \param tzAdvEvent is the Trip Zone event type.
//! \param tzAdvAction is the Trip zone Action.
//!
//! This function sets the Advanced Trip Zone Action to be taken when an
//! advanced Trip Zone event occurs.
//!
//! Valid values for the parameters are:
//!  - tzAdvEvent
//!      - PWM_TZ_ADV_ACTION_EVENT_TZB_D  - TZ1 - TZ6, DCBEVT2, DCBEVT1 while
//!                                             counting down
//!      - PWM_TZ_ADV_ACTION_EVENT_TZB_U  - TZ1 - TZ6, DCBEVT2, DCBEVT1 while
//!                                             counting up
//!      - PWM_TZ_ADV_ACTION_EVENT_TZA_D  - TZ1 - TZ6, DCAEVT2, DCAEVT1 while
//!                                             counting down
//!      - PWM_TZ_ADV_ACTION_EVENT_TZA_U  - TZ1 - TZ6, DCAEVT2, DCAEVT1 while
//!                                             counting up
//!  - tzAdvAction
//!      - PWM_TZ_ADV_ACTION_HIGH_Z    - high impedance output
//!      - PWM_TZ_ADV_ACTION_HIGH      - high voltage state
//!      - PWM_TZ_ADV_ACTION_LOW       - low voltage state
//!      - PWM_TZ_ADV_ACTION_TOGGLE    - Toggle output
//!      - PWM_TZ_ADV_ACTION_DISABLE   - disable action
//!
//! \note This function enables the advanced Trip Zone event.
//!
//! \note This function operates on both PWMA and PWMB depending on the
//!       tzAdvEvent  parameter.
//! \note Advanced Trip Zone events take into consideration the direction of
//!       the counter in addition to Trip Zone events.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setTripZoneAdvAction(uint32_t base, PWM_TripZoneAdvancedEvent tzAdvEvent,
                          PWM_TripZoneAdvancedAction tzAdvAction)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the Advanced Action for Trip Zone events
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZCTL2) =
       ((HWREGH(base + PWM_O_TZCTL2) & ~(0x7U << (uint16_t)tzAdvEvent)) |
        ((uint16_t)tzAdvAction << (uint16_t)tzAdvEvent));

    HWREGH(base + PWM_O_TZCTL2) |= PWM_TZCTL2_ETZE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Advanced Digital Compare Trip Zone Action on PWMA.
//!
//! \param base is the base address of the PWM module.
//! \param tzAdvDCEvent is the Digital Compare Trip Zone event type.
//! \param tzAdvDCAction is the Digital Compare Trip zone Action.
//!
//! This function sets the Digital Compare (DC) Advanced Trip Zone Action to be
//! taken on PWMA when an advanced Digital Compare Trip Zone A event occurs.
//! Valid values for the parameters are:
//!  - tzAdvDCEvent
//!      - PWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D  - Digital Compare event A2 while
//!                                                 counting down
//!      - PWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U  - Digital Compare event A2 while
//!                                                 counting up
//!      - PWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D  - Digital Compare event A1 while
//!                                                 counting down
//!      - PWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U  - Digital Compare event A1 while
//!                                                 counting up
//!  - tzAdvDCAction
//!      - PWM_TZ_ADV_ACTION_HIGH_Z    - high impedance output
//!      - PWM_TZ_ADV_ACTION_HIGH      - high voltage state
//!      - PWM_TZ_ADV_ACTION_LOW       - low voltage state
//!      - PWM_TZ_ADV_ACTION_TOGGLE    - Toggle output
//!      - PWM_TZ_ADV_ACTION_DISABLE   - disable action
//!
//! \note This function enables the advanced Trip Zone event.
//!
//! \note Advanced Trip Zone events take into consideration the direction of
//!       the counter in addition to Digital Compare Trip Zone events.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setTripZoneAdvDigitalCompareActionA(uint32_t base,
                              PWM_TripZoneAdvDigitalCompareEvent tzAdvDCEvent,
                              PWM_TripZoneAdvancedAction tzAdvDCAction)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the Advanced Action for Trip Zone events
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZCTLDCA) =
      ((HWREGH(base + PWM_O_TZCTLDCA) & ~(0x7U << (uint16_t)tzAdvDCEvent)) |
       ((uint16_t)tzAdvDCAction << (uint16_t)tzAdvDCEvent));

    HWREGH(base + PWM_O_TZCTL2) |= PWM_TZCTL2_ETZE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Advanced Digital Compare Trip Zone Action on PWMB.
//!
//! \param base is the base address of the PWM module.
//! \param tzAdvDCEvent is the Digital Compare Trip Zone event type.
//! \param tzAdvDCAction is the Digital Compare Trip zone Action.
//!
//! This function sets the Digital Compare (DC) Advanced Trip Zone Action to be
//! taken on PWMB when an advanced Digital Compare Trip Zone B event occurs.
//! Valid values for the parameters are:
//!  - tzAdvDCEvent
//!      - PWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D  - Digital Compare event B2 while
//!                                                 counting down
//!      - PWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U  - Digital Compare event B2 while
//!                                                 counting up
//!      - PWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D  - Digital Compare event B1 while
//!                                                 counting down
//!      - PWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U  - Digital Compare event B1 while
//!                                                 counting up
//!  - tzAdvDCAction
//!      - PWM_TZ_ADV_ACTION_HIGH_Z    - high impedance output
//!      - PWM_TZ_ADV_ACTION_HIGH      - high voltage state
//!      - PWM_TZ_ADV_ACTION_LOW       - low voltage state
//!      - PWM_TZ_ADV_ACTION_TOGGLE    - Toggle output
//!      - PWM_TZ_ADV_ACTION_DISABLE   - disable action
//!
//! \note This function enables the advanced Trip Zone event.
//!
//! \note Advanced Trip Zone events take into consideration the direction of
//!       the counter in addition to Digital Compare Trip Zone events.
//!
//! \return None.
//
//*****************************************************************************
static inline void PWM_setTripZoneAdvDigitalCompareActionB(uint32_t base,
                              PWM_TripZoneAdvDigitalCompareEvent tzAdvDCEvent,
                              PWM_TripZoneAdvancedAction tzAdvDCAction)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the Advanced Action for Trip Zone events
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZCTLDCB) =
     ((HWREGH(base + PWM_O_TZCTLDCB) & ~(0x7U << (uint16_t)tzAdvDCEvent)) |
      ((uint16_t)tzAdvDCAction << (uint16_t)tzAdvDCEvent));

    HWREGH(base + PWM_O_TZCTL2) |= PWM_TZCTL2_ETZE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable Trip Zone interrupts.
//!
//! \param base is the base address of the PWM module.
//! \param tzInterrupt is the Trip Zone interrupt.
//!
//! This function enables the Trip Zone interrupts.
//! Valid values for tzInterrupt are:
//!   - PWM_TZ_INTERRUPT_CBC     - Trip Zones Cycle By Cycle interrupt
//!   - PWM_TZ_INTERRUPT_OST     - Trip Zones One Shot interrupt
//!   - PWM_TZ_INTERRUPT_DCAEVT1 - Digital Compare A Event 1 interrupt
//!   - PWM_TZ_INTERRUPT_DCAEVT2 - Digital Compare A Event 2 interrupt
//!   - PWM_TZ_INTERRUPT_DCBEVT1 - Digital Compare B Event 1 interrupt
//!   - PWM_TZ_INTERRUPT_DCBEVT2 - Digital Compare B Event 2 interrupt
//!
//! \b note:  A logical OR of the valid values can be passed as the tzInterrupt
//!           parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableTripZoneInterrupt(uint32_t base, uint16_t tzInterrupt)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT((tzInterrupt > 0U) && (tzInterrupt < 0x80U));

    //
    // Enable Trip zone interrupts
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZEINT) |= tzInterrupt;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable Trip Zone interrupts.
//!
//! \param base is the base address of the PWM module.
//! \param tzInterrupt is the Trip Zone interrupt.
//!
//! This function disables the Trip Zone interrupts.
//! Valid values for tzInterrupt are:
//!   - PWM_TZ_INTERRUPT_CBC     - Trip Zones Cycle By Cycle interrupt
//!   - PWM_TZ_INTERRUPT_OST    - Trip Zones One Shot interrupt
//!   - PWM_TZ_INTERRUPT_DCAEVT1 - Digital Compare A Event 1 interrupt
//!   - PWM_TZ_INTERRUPT_DCAEVT2 - Digital Compare A Event 2 interrupt
//!   - PWM_TZ_INTERRUPT_DCBEVT1 - Digital Compare B Event 1 interrupt
//!   - PWM_TZ_INTERRUPT_DCBEVT2 - Digital Compare B Event 2 interrupt
//!
//! \b note:  A logical OR of the valid values can be passed as the tzInterrupt
//!           parameter.
//!
//! \return None.
//
//***************************************************************************
static inline void
PWM_disableTripZoneInterrupt(uint32_t base, uint16_t tzInterrupt)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT((tzInterrupt > 0U) && (tzInterrupt < 0x80U));

    //
    // Disable Trip zone interrupts
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZEINT) &= ~tzInterrupt;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the Trip Zone status flag
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the Trip Zone status flag.
//!
//! \return The function returns the following or the bitwise OR value
//!         of the following values.
//!         - PWM_TZ_INTERRUPT    - Trip Zone interrupt was generated
//!                                  due to the following TZ events.
//!         - PWM_TZ_FLAG_CBC     - Trip Zones Cycle By Cycle event status flag
//!         - PWM_TZ_FLAG_OST     - Trip Zones One Shot event status flag
//!         - PWM_TZ_FLAG_DCAEVT1 - Digital Compare A Event 1 status flag
//!         - PWM_TZ_FLAG_DCAEVT2 - Digital Compare A Event 2 status flag
//!         - PWM_TZ_FLAG_DCBEVT1 - Digital Compare B Event 1 status flag
//!         - PWM_TZ_FLAG_DCBEVT2 - Digital Compare B Event 2 status flag
//
//***************************************************************************
static inline uint16_t
PWM_getTripZoneFlagStatus(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return the Trip zone flag status
    //
    return(HWREGH(base + PWM_O_TZFLG) & 0x7FU);
}

//*****************************************************************************
//
//! Gets the Trip Zone Cycle by Cycle flag status
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the specific Cycle by Cycle Trip Zone flag
//! status.
//!
//! \return The function returns the following values.
//!           - PWM_TZ_CBC_FLAG_1     - CBC 1 status flag
//!           - PWM_TZ_CBC_FLAG_2     - CBC 2 status flag
//!           - PWM_TZ_CBC_FLAG_3     - CBC 3 status flag
//!           - PWM_TZ_CBC_FLAG_4     - CBC 4 status flag
//!           - PWM_TZ_CBC_FLAG_5     - CBC 5 status flag
//!           - PWM_TZ_CBC_FLAG_6     - CBC 6 status flag
//!           - PWM_TZ_CBC_FLAG_DCAEVT2  - CBC status flag for Digital compare
//!                                                event A2
//!           - PWM_TZ_CBC_FLAG_DCBEVT2  - CBC status flag for Digital compare
//!                                                event B2
//
//***************************************************************************
static inline uint16_t
PWM_getCycleByCycleTripZoneFlagStatus(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return the Cycle By Cycle Trip zone flag status
    //
    return(HWREGH(base + PWM_O_TZCBCFLG) & 0xFFU);
}

//*****************************************************************************
//
//! Gets the Trip Zone One Shot flag status
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the specific One Shot Trip Zone flag status.
//!
//! \return The function returns the bitwise OR of the following flags.
//!           - PWM_TZ_OST_FLAG_OST1     - OST status flag for OST1
//!           - PWM_TZ_OST_FLAG_OST2     - OST status flag for OST2
//!           - PWM_TZ_OST_FLAG_OST3     - OST status flag for OST3
//!           - PWM_TZ_OST_FLAG_OST4     - OST status flag for OST4
//!           - PWM_TZ_OST_FLAG_OST5     - OST status flag for OST5
//!           - PWM_TZ_OST_FLAG_OST6     - OST status flag for OST6
//!           - PWM_TZ_OST_FLAG_DCAEVT1  - OST status flag for Digital
//!                                                 compare event A1
//!           - PWM_TZ_OST_FLAG_DCBEVT1  - OST status flag for Digital
//!                                                 compare event B1
//
//***************************************************************************
static inline uint16_t
PWM_getOneShotTripZoneFlagStatus(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return the One Shot Trip zone flag status
    //
    return(HWREGH(base + PWM_O_TZOSTFLG) & 0xFFU);
}

//*****************************************************************************
//
//! Set the Trip Zone CBC pulse clear event.
//!
//! \param base is the base address of the PWM module.
//! \param clearEvent is the CBC trip zone clear event.
//!
//! This function set the event which automatically clears the
//! CBC (Cycle by Cycle) latch.
//! Valid values for clearEvent are:
//!   - PWM_TZ_CBC_PULSE_CLR_CNTR_ZERO         - Clear CBC pulse when counter
//!                                                  equals zero
//!   - PWM_TZ_CBC_PULSE_CLR_CNTR_PERIOD       - Clear CBC pulse when counter
//!                                                  equals period
//!   - PWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD  - Clear CBC pulse when counter
//!                                                  equals zero or period
//!
//!  \return None.
//
//**************************************************************************
static inline void
PWM_selectCycleByCycleTripZoneClearEvent(uint32_t base,
                                 PWM_CycleByCycleTripZoneClearMode clearEvent)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the Cycle by Cycle Trip Latch mode
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZCLR) =
                 ((HWREGH(base + PWM_O_TZCLR) & ~PWM_TZCLR_CBCPULSE_M) |
                  ((uint16_t)clearEvent << PWM_TZCLR_CBCPULSE_S));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Clear Trip Zone flag
//!
//! \param base is the base address of the PWM module.
//! \param tzFlags is the Trip Zone flags.
//!
//! This function clears the Trip Zone flags
//! Valid values for tzFlags are:
//!   - PWM_TZ_INTERRUPT    - Global Trip Zone interrupt flag
//!   - PWM_TZ_FLAG_CBC     - Trip Zones Cycle By Cycle flag
//!   - PWM_TZ_FLAG_OST     - Trip Zones One Shot flag
//!   - PWM_TZ_FLAG_DCAEVT1 - Digital Compare A Event 1 flag
//!   - PWM_TZ_FLAG_DCAEVT2 - Digital Compare A Event 2 flag
//!   - PWM_TZ_FLAG_DCBEVT1 - Digital Compare B Event 1 flag
//!   - PWM_TZ_FLAG_DCBEVT2 - Digital Compare B Event 2 flag
//!
//! \b note: A bitwise OR of the valid values can be passed as the tzFlags
//! parameter.
//!
//! \return None.
//
//***************************************************************************
static inline void
PWM_clearTripZoneFlag(uint32_t base, uint16_t tzFlags)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(tzFlags < 0x80U);

    //
    // Clear Trip zone event flag
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZCLR) |= tzFlags;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Clear the Trip Zone Cycle by Cycle flag.
//!
//! \param base is the base address of the PWM module.
//! \param tzCBCFlags is the CBC flag to be cleared.
//!
//! This function clears the specific Cycle by Cycle Trip Zone flag.
//! The following are valid values for tzCBCFlags.
//!   - PWM_TZ_CBC_FLAG_1     - CBC 1 flag
//!   - PWM_TZ_CBC_FLAG_2     - CBC 2 flag
//!   - PWM_TZ_CBC_FLAG_3     - CBC 3 flag
//!   - PWM_TZ_CBC_FLAG_4     - CBC 4 flag
//!   - PWM_TZ_CBC_FLAG_5     - CBC 5 flag
//!   - PWM_TZ_CBC_FLAG_6     - CBC 6 flag
//!   - PWM_TZ_CBC_FLAG_DCAEVT2  - CBC flag Digital compare
//!                                         event A2
//!   - PWM_TZ_CBC_FLAG_DCBEVT2  - CBC flag Digital compare
//!                                         event B2
//!
//! \return None.
//
//***************************************************************************
static inline void
PWM_clearCycleByCycleTripZoneFlag(uint32_t base, uint16_t tzCBCFlags)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(tzCBCFlags < 0x800U);

    //
    // Clear the Cycle By Cycle Trip zone flag
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZCBCCLR) |= tzCBCFlags;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Clear the Trip Zone One Shot flag.
//!
//! \param base is the base address of the PWM module.
//! \param tzOSTFlags is the OST flags to be cleared.
//!
//! This function clears the specific One Shot (OST) Trip Zone flag.
//! The following are valid values for tzOSTFlags.
//!  - PWM_TZ_OST_FLAG_OST1      - OST flag for OST1
//!  - PWM_TZ_OST_FLAG_OST2      - OST flag for OST2
//!  - PWM_TZ_OST_FLAG_OST3      - OST flag for OST3
//!  - PWM_TZ_OST_FLAG_OST4      - OST flag for OST4
//!  - PWM_TZ_OST_FLAG_OST5      - OST flag for OST5
//!  - PWM_TZ_OST_FLAG_OST6      - OST flag for OST6
//!  - PWM_TZ_OST_FLAG_DCAEVT1   - OST flag for Digital compare event A1
//!  - PWM_TZ_OST_FLAG_DCBEVT1   - OST flag for Digital compare event B1
//!
//! \return None.
//
//***************************************************************************
static inline void
PWM_clearOneShotTripZoneFlag(uint32_t base, uint16_t tzOSTFlags)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(tzOSTFlags < 0x800U);

    //
    // Clear the Cycle By Cycle Trip zone flag
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZOSTCLR) |= tzOSTFlags;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Force Trip Zone events.
//!
//! \param base is the base address of the PWM module.
//! \param tzForceEvent is the forced Trip Zone event.
//!
//! This function forces a Trip Zone event.
//! Valid values for tzForceEvent are:
//!   - PWM_TZ_FORCE_EVENT_CBC     - Force Trip Zones Cycle By Cycle event
//!   - PWM_TZ_FORCE_EVENT_OST     - Force Trip Zones One Shot Event
//!   - PWM_TZ_FORCE_EVENT_DCAEVT1 - Force Digital Compare A Event 1
//!   - PWM_TZ_FORCE_EVENT_DCAEVT2 - Force Digital Compare A Event 2
//!   - PWM_TZ_FORCE_EVENT_DCBEVT1 - Force Digital Compare B Event 1
//!   - PWM_TZ_FORCE_EVENT_DCBEVT2 - Force Digital Compare B Event 2
//!
//! \return None.
//
//***************************************************************************
static inline void
PWM_forceTripZoneEvent(uint32_t base, uint16_t tzForceEvent)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT((tzForceEvent & 0xFF81U)== 0U);

    //
    // Force a Trip Zone event
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_TZFRC) |= tzForceEvent;
    WRPRT_ENABLE;
}

//
// Event Trigger related APIs
//
//*****************************************************************************
//
//! Enable PWM interrupt.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables the PWM interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableInterrupt(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable PWM interrupt
    //
    HWREGH(base + PWM_O_ETSEL) |= PWM_ETSEL_INTEN;
}

//*****************************************************************************
//
//! disable PWM interrupt.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables the PWM interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableInterrupt(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable PWM interrupt
    //
    HWREGH(base + PWM_O_ETSEL) &= ~PWM_ETSEL_INTEN;
}

//*****************************************************************************
//
//! Sets the PWM interrupt source.
//!
//! \param base is the base address of the PWM module.
//! \param interruptSource is the PWM interrupt source.
//!
//! This function sets the PWM interrupt source.
//! Valid values for interruptSource are:
//!   - PWM_INT_TBCTR_DISABLED       - Time-base counter is disabled
//!   - PWM_INT_TBCTR_ZERO           - Time-base counter equal to zero
//!   - PWM_INT_TBCTR_PERIOD         - Time-base counter equal to period
//!   - PWM_INT_TBCTR_ZERO_OR_PERIOD - Time-base counter equal to zero or
//!                                     period
//!   - PWM_INT_TBCTR_ZERO_OR_PERIOD - Time-base counter equal to zero or
//!                                     period
//!   - PWM_INT_TBCTR_U_CMPx         - Where x is A,B,C or D
//!                                     Time-base counter equal to CMPA, CMPB,
//!                                     CMPC or CMPD (depending the value of x)
//!                                     when the timer is incrementing
//!   - PWM_INT_TBCTR_D_CMPx         - Where x is A,B,C or D
//!                                     Time-base counter equal to CMPA, CMPB,
//!                                     CMPC or CMPD (depending the value of x)
//!                                     when the timer is decrementing
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setInterruptSource(uint32_t base, uint16_t interruptSource)
{
    uint16_t intSource;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(((interruptSource > 0U) && (interruptSource < 9U)) ||
           (interruptSource == 10U) || (interruptSource == 12U) ||
           (interruptSource == 14U));

    if((interruptSource == PWM_INT_TBCTR_U_CMPC) ||
       (interruptSource == PWM_INT_TBCTR_U_CMPD) ||
       (interruptSource == PWM_INT_TBCTR_D_CMPC) ||
       (interruptSource == PWM_INT_TBCTR_D_CMPD))
    {
          //
          // Shift the interrupt source by 1
          //
          intSource = interruptSource >> 1U;

          //
          // Enable events based on comp C or comp D
          //
          HWREGH(base + PWM_O_ETSEL) |= PWM_ETSEL_INTSELCMP;
    }
    else if((interruptSource == PWM_INT_TBCTR_U_CMPA) ||
            (interruptSource == PWM_INT_TBCTR_U_CMPB) ||
            (interruptSource == PWM_INT_TBCTR_D_CMPA) ||
            (interruptSource == PWM_INT_TBCTR_D_CMPB))
    {
        intSource = interruptSource;

        //
        // Enable events based on comp A or comp B
        //
        HWREGH(base + PWM_O_ETSEL) &= ~PWM_ETSEL_INTSELCMP;
    }
    else
    {
        intSource = interruptSource;
    }

    //
    // Set the interrupt source
    //
    HWREGH(base + PWM_O_ETSEL) =
            ((HWREGH(base + PWM_O_ETSEL) & ~PWM_ETSEL_INTSEL_M) | intSource);
}

//*****************************************************************************
//
//! Sets the PWM interrupt event counts.
//!
//! \param base is the base address of the PWM module.
//! \param eventCount is the event count for interrupt scale
//!
//! This function sets the interrupt event count that determines the number of
//! events that have to occur before an interrupt is issued.
//! Maximum value for eventCount is 15.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setInterruptEventCount(uint32_t base, uint16_t eventCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(eventCount < 16U);

    //
    // Enable advanced feature of interrupt every up to 15 events
    //
    HWREGH(base + PWM_O_ETPS) |= PWM_ETPS_INTPSSEL;
    HWREGH(base + PWM_O_ETINTPS) =
         ((HWREGH(base + PWM_O_ETINTPS) & ~PWM_ETINTPS_INTPRD2_M) |
           eventCount);
}

//*****************************************************************************
//
//! Return the interrupt status.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the PWM interrupt status.
//! \b Note This function doesn't return the Trip Zone status.
//!
//! \return Returns true if PWM interrupt was generated.
//!         Returns false if no interrupt was generated
//
//*****************************************************************************
static inline bool
PWM_getEventTriggerInterruptStatus(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return INT bit of ETFLG register
    //
    return(((HWREGH(base + PWM_O_ETFLG) & 0x1U) == 0x1U) ? true : false);
}

//*****************************************************************************
//
//! Clear interrupt flag.
//!
//! \param base is the base address of the PWM module.
//!
//! This function clears the PWM interrupt flag.
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_clearEventTriggerInterruptFlag(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Clear INT bit of ETCLR register
    //
    HWREGH(base + PWM_O_ETCLR) |= PWM_ETCLR_INT;
}

//*****************************************************************************
//
//! Enable Pre-interrupt count load.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables the PWM interrupt counter to be pre-interrupt loaded
//! with a count value.
//!
//! \note This is valid only for advanced/expanded interrupt mode
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableInterruptEventCountInit(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable interrupt event count initializing/loading
    //
    HWREGH(base + PWM_O_ETCNTINITCTL) |= PWM_ETCNTINITCTL_INTINITEN;
}

//*****************************************************************************
//
//! Disable interrupt count load.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables the PWM interrupt counter from being loaded with
//! pre-interrupt count value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableInterruptEventCountInit(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable interrupt event count initializing/loading
    //
    HWREGH(base + PWM_O_ETCNTINITCTL) &= ~PWM_ETCNTINITCTL_INTINITEN;
}

//*****************************************************************************
//
//! Force a software pre interrupt event counter load.
//!
//! \param base is the base address of the PWM module.
//!
//! This function forces the PWM interrupt counter to be loaded with the
//! contents set by PWM_setPreInterruptEventCount().
//!
//! \note make sure the PWM_enablePreInterruptEventCountLoad() function is
//!       is called before invoking this function.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_forceInterruptEventCountInit(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Load the Interrupt Event counter value
    //
    HWREGH(base + PWM_O_ETCNTINITCTL) |= PWM_ETCNTINITCTL_INTINITFRC;
}

//*****************************************************************************
//
//! Set interrupt count.
//!
//! \param base is the base address of the PWM module.
//! \param eventCount is the PWM interrupt count value.
//!
//! This function sets the PWM interrupt count. eventCount is the value of the
//! pre-interrupt value that is to be loaded. The maximum value of eventCount
//! is 15.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setInterruptEventCountInitValue(uint32_t base, uint16_t eventCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(eventCount < 16U);

    //
    // Set the Pre-interrupt event count
    //
    HWREGH(base + PWM_O_ETCNTINIT) =
         ((HWREGH(base + PWM_O_ETCNTINIT) & ~PWM_ETCNTINIT_INTINIT_M) |
          (uint16_t)(eventCount & 0xFU));
}

//*****************************************************************************
//
//! Get the interrupt count.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the PWM interrupt event count.
//!
//! \return The interrupt event counts that have occurred.
//
//*****************************************************************************
static inline uint16_t
PWM_getInterruptEventCount(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return the interrupt event count
    //
    return(((HWREGH(base + PWM_O_ETINTPS) & PWM_ETINTPS_INTCNT2_M) >>
             PWM_ETINTPS_INTCNT2_S));
}

//*****************************************************************************
//
//! Force PWM interrupt.
//!
//! \param base is the base address of the PWM module.
//!
//! This function forces an PWM interrupt.
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_forceEventTriggerInterrupt(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set INT bit of ETFRC register
    //
    HWREGH(base + PWM_O_ETFRC) |= PWM_ETFRC_INT;
}

//
// ADC SOC configuration related APIs
//
//*****************************************************************************
//
//! Enable ADC SOC event.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function enables the PWM module to trigger an ADC SOC event.
//! Valid values for adcSOCType are:
//!   - PWM_SOC_A  - SOC A
//!   - PWM_SOC_B  - SOC B
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableADCTrigger(uint32_t base, PWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable an SOC
    //
    if(adcSOCType == PWM_SOC_A)
    {
         HWREGH(base + PWM_O_ETSEL) |= PWM_ETSEL_SOCAEN;
    }
    else
    {
         HWREGH(base + PWM_O_ETSEL) |= PWM_ETSEL_SOCBEN;
    }
}

//*****************************************************************************
//
//! Disable ADC SOC event.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function disables the PWM module from triggering an ADC SOC event.
//! Valid values for adcSOCType are:
//!   - PWM_SOC_A  - SOC A
//!   - PWM_SOC_B  - SOC B
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableADCTrigger(uint32_t base, PWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable an SOC
    //
    if(adcSOCType == PWM_SOC_A)
    {
         HWREGH(base + PWM_O_ETSEL) &= ~PWM_ETSEL_SOCAEN;
    }
    else
    {
         HWREGH(base + PWM_O_ETSEL) &= ~PWM_ETSEL_SOCBEN;
    }
}

//*****************************************************************************
//
//! Sets the PWM SOC source.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type.
//! \param socSource is the SOC source.
//!
//! This function sets the PWM ADC SOC source.
//! Valid values for socSource are:
//!  - adcSOCType
//!     - PWM_SOC_A  - SOC A
//!     - PWM_SOC_B  - SOC B
//!  - socSource
//!     - PWM_SOC_DCxEVT1              - Event is based on DCxEVT1
//!     - PWM_SOC_TBCTR_ZERO           - Time-base counter equal to zero
//!     - PWM_SOC_TBCTR_PERIOD         - Time-base counter equal to period
//!     - PWM_SOC_TBCTR_ZERO_OR_PERIOD - Time-base counter equal to zero or
//!                                       period
//!     - PWM_SOC_TBCTR_U_CMPx         - Where x is A,B,C or D
//!                                       Time-base counter equal to CMPA, CMPB,
//!                                       CMPC or CMPD(depending the value of x)
//!                                       when the timer is incrementing
//!     - PWM_SOC_TBCTR_D_CMPx         - Where x is A,B,C or D
//!                                       Time-base counter equal to CMPA, CMPB,
//!                                       CMPC or CMPD(depending the value of x)
//!                                       when the timer is decrementing
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setADCTriggerSource(uint32_t base,
                         PWM_ADCStartOfConversionType adcSOCType,
                         PWM_ADCStartOfConversionSource socSource)
{
    uint16_t source;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    if((socSource == PWM_SOC_TBCTR_U_CMPC) ||
       (socSource == PWM_SOC_TBCTR_U_CMPD) ||
       (socSource == PWM_SOC_TBCTR_D_CMPC) ||
       (socSource == PWM_SOC_TBCTR_D_CMPD))
    {
        source = (uint16_t)socSource >> 1U;
    }
    else
    {
        source = (uint16_t)socSource;
    }

    if(adcSOCType == PWM_SOC_A)
    {
        //
        // Set the SOC source
        //
        HWREGH(base + PWM_O_ETSEL) =
                ((HWREGH(base + PWM_O_ETSEL) & ~PWM_ETSEL_SOCASEL_M) |
                 (source << PWM_ETSEL_SOCASEL_S));

        //
        // Enable the comparator selection
        //
        if((socSource == PWM_SOC_TBCTR_U_CMPA) ||
           (socSource == PWM_SOC_TBCTR_U_CMPB) ||
           (socSource == PWM_SOC_TBCTR_D_CMPA) ||
           (socSource == PWM_SOC_TBCTR_D_CMPB))
        {
            //
            // Enable events based on comp A or comp B
            //
            HWREGH(base + PWM_O_ETSEL) &= ~PWM_ETSEL_SOCASELCMP;
        }
        else if((socSource == PWM_SOC_TBCTR_U_CMPC) ||
                (socSource == PWM_SOC_TBCTR_U_CMPD) ||
                (socSource == PWM_SOC_TBCTR_D_CMPC) ||
                (socSource == PWM_SOC_TBCTR_D_CMPD))
        {
            //
            // Enable events based on comp C or comp D
            //
            HWREGH(base + PWM_O_ETSEL) |= PWM_ETSEL_SOCASELCMP;
        }
        else
        {
            //
            // No action required for the other socSource options
            //
        }
    }
    else
    {
        //
        // Enable the comparator selection
        //
        HWREGH(base + PWM_O_ETSEL) =
                ((HWREGH(base + PWM_O_ETSEL) & ~PWM_ETSEL_SOCBSEL_M) |
                 (source << PWM_ETSEL_SOCBSEL_S));

        //
        // Enable the comparator selection
        //
        if((socSource == PWM_SOC_TBCTR_U_CMPA) ||
           (socSource == PWM_SOC_TBCTR_U_CMPB) ||
           (socSource == PWM_SOC_TBCTR_D_CMPA) ||
           (socSource == PWM_SOC_TBCTR_D_CMPB))
        {
            //
            // Enable events based on comp A or comp B
            //
            HWREGH(base + PWM_O_ETSEL) &= ~PWM_ETSEL_SOCBSELCMP;
        }
        else if((socSource == PWM_SOC_TBCTR_U_CMPC) ||
                (socSource == PWM_SOC_TBCTR_U_CMPD) ||
                (socSource == PWM_SOC_TBCTR_D_CMPC) ||
                (socSource == PWM_SOC_TBCTR_D_CMPD))
        {
            //
            // Enable events based on comp C or comp D
            //
            HWREGH(base + PWM_O_ETSEL) |= PWM_ETSEL_SOCBSELCMP;
        }
        else
        {
            //
            // No action required for the other socSource options
            //
        }
    }
}

//*****************************************************************************
//
//! Sets the PWM SOC event counts.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type.
//! \param preScaleCount is the event count number.
//!
//! This function sets the SOC event count that determines the number of
//! events that have to occur before an SOC is issued.
//!  Valid values for the parameters are:
//!   - adcSOCType
//!       - PWM_SOC_A  - SOC A
//!       - PWM_SOC_B  - SOC B
//!   - preScaleCount
//!        - [1 - 15]  -  Generate SOC pulse every preScaleCount
//!                       up to 15 events.
//!
//! \note A preScaleCount value of 0 disables the prescale.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setADCTriggerEventPrescale(uint32_t base,
                                PWM_ADCStartOfConversionType adcSOCType,
                                uint16_t preScaleCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(preScaleCount < 16U);

    //
    // Enable advanced feature of SOC every up to 15 events
    //
    HWREGH(base + PWM_O_ETPS) |= PWM_ETPS_SOCPSSEL;
    if(adcSOCType == PWM_SOC_A)
    {
        //
        // Set the count for SOC A
        //
        HWREGH(base + PWM_O_ETSOCPS) =
           ((HWREGH(base + PWM_O_ETSOCPS) & ~PWM_ETSOCPS_SOCAPRD2_M) |
             preScaleCount);
    }
    else
    {
        //
        // Set the count for SOC B
        //
        HWREGH(base + PWM_O_ETSOCPS) =
             ((HWREGH(base + PWM_O_ETSOCPS) & ~PWM_ETSOCPS_SOCBPRD2_M) |
              (preScaleCount << PWM_ETSOCPS_SOCBPRD2_S));
    }
}

//*****************************************************************************
//
//! Return the SOC event status.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function returns the PWM SOC status.
//! Valid values for adcSOCType are:
//!   - PWM_SOC_A  - SOC A
//!   - PWM_SOC_B  - SOC B
//!
//! \return Returns true if the selected adcSOCType SOC was generated.
//!         Returns false if the selected adcSOCType SOC was not generated.
//
//*****************************************************************************
static inline bool
PWM_getADCTriggerFlagStatus(uint32_t base,
                             PWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return the SOC A/ B status
    //
    return((((HWREGH(base + PWM_O_ETFLG) >>
              ((uint16_t)adcSOCType + 2U)) & 0x1U) == 0x1U) ? true : false);
}

//*****************************************************************************
//
//! Clear SOC flag.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function clears the PWM SOC flag.
//! Valid values for adcSOCType are:
//!   - PWM_SOC_A  - SOC A
//!   - PWM_SOC_B  - SOC B
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_clearADCTriggerFlag(uint32_t base,
                         PWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Clear SOC A/B bit of ETCLR register
    //
    HWREGH(base + PWM_O_ETCLR) |= 1U << ((uint16_t)adcSOCType + 2U);
}

//*****************************************************************************
//
//! Enable Pre-SOC event count load.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function enables the PWM SOC event counter which is set by the
//! PWM_setADCTriggerEventCountInitValue() function to be loaded before
//! an SOC event.
//! Valid values for adcSOCType are:
//!   - PWM_SOC_A  - SOC A
//!   - PWM_SOC_B  - SOC B
//!
//! \note This is valid only for advanced/expanded SOC mode
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableADCTriggerEventCountInit(uint32_t base,
                                    PWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable SOC event count initializing/loading
    //
    HWREGH(base + PWM_O_ETCNTINITCTL) |= 1U << ((uint16_t)adcSOCType + 14U);
}

//*****************************************************************************
//
//! Disable Pre-SOC event count load.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function disables the PWM SOC event counter from being loaded before
//! an SOC event (only an SOC event causes an increment of the counter value).
//! Valid values for adcSOCType are:
//!   - PWM_SOC_A  - SOC A
//!   - PWM_SOC_B  - SOC B
//!
//! \note This is valid only for advanced/expanded SOC mode
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableADCTriggerEventCountInit(uint32_t base,
                                     PWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable SOC event count initializing/loading
    //
    HWREGH(base + PWM_O_ETCNTINITCTL) &=
                                  ~(1U << ((uint16_t)adcSOCType + 14U));
}

//*****************************************************************************
//
//! Force a software pre SOC event counter load.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type
//!
//! This function forces the PWM SOC counter to be loaded with the
//! contents set by PWM_setPreADCStartOfConversionEventCount().
//!
//! \note make sure the PWM_enableADCTriggerEventCountInit()
//!       function is called before invoking this function.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_forceADCTriggerEventCountInit(uint32_t base,
                                   PWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Load the Interrupt Event counter value
    //
    HWREGH(base + PWM_O_ETCNTINITCTL) |= 1U << ((uint16_t)adcSOCType + 11U);
}

//*****************************************************************************
//
//! Set ADC Trigger count values.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type.
//! \param eventCount is the PWM interrupt count value.
//!
//! This function sets the PWM ADC Trigger count values.
//! Valid values for adcSOCType are:
//!   - PWM_SOC_A  - SOC A
//!   - PWM_SOC_B  - SOC B
//! The eventCount has a maximum value of 15.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setADCTriggerEventCountInitValue(uint32_t base,
                                      PWM_ADCStartOfConversionType adcSOCType,
                                      uint16_t eventCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(eventCount < 16U);

    //
    // Set the ADC Trigger event count
    //
    if(adcSOCType == PWM_SOC_A)
    {
        HWREGH(base + PWM_O_ETCNTINIT) =
            ((HWREGH(base + PWM_O_ETCNTINIT) & ~PWM_ETCNTINIT_SOCAINIT_M) |
             (uint16_t)(eventCount << PWM_ETCNTINIT_SOCAINIT_S));
    }
    else
    {
        HWREGH(base + PWM_O_ETCNTINIT) =
             ((HWREGH(base + PWM_O_ETCNTINIT) & ~PWM_ETCNTINIT_SOCBINIT_M) |
              (eventCount << PWM_ETCNTINIT_SOCBINIT_S));
    }
}

//*****************************************************************************
//
//! Get the SOC event count.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function returns the PWM SOC event count.
//! Valid values for adcSOCType are:
//!   - PWM_SOC_A  - SOC A
//!   - PWM_SOC_B  - SOC B
//!
//! \return The SOC event counts that have occurred.
//
//*****************************************************************************
static inline uint16_t
PWM_getADCTriggerEventCount(uint32_t base,
                             PWM_ADCStartOfConversionType adcSOCType)
{
    uint16_t eventCount;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return the SOC event count
    //
    if(adcSOCType == PWM_SOC_A)
    {
        eventCount = (HWREGH(base + PWM_O_ETSOCPS) >>
                                         PWM_ETSOCPS_SOCACNT2_S) & 0xFU;
    }
    else
    {
        eventCount = (HWREGH(base + PWM_O_ETSOCPS) >>
                                        PWM_ETSOCPS_SOCBCNT2_S) & 0xFU;
    }
    return(eventCount);
}

//*****************************************************************************
//
//! Force SOC event.
//!
//! \param base is the base address of the PWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function forces an PWM SOC event.
//! Valid values for adcSOCType are:
//!   - PWM_SOC_A  - SOC A
//!   - PWM_SOC_B  - SOC B
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_forceADCTrigger(uint32_t base, PWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set SOC A/B bit of ETFRC register
    //
    HWREGH(base + PWM_O_ETFRC) |= 1U << ((uint16_t)adcSOCType + 2U);
}

//
// Digital Compare module related APIs
//
//*****************************************************************************
//
//! Set the DC trip input.
//!
//! \param base is the base address of the PWM module.
//! \param tripSource is the tripSource.
//! \param dcType is the Digital Compare type.
//!
//! This function sets the trip input to the Digital Compare (DC). For a given
//! dcType the function sets the tripSource to be the input to the DC.
//! Valid values for the parameter are:
//!  - tripSource
//!     - PWM_DC_TRIP_TRIPINx - Trip x,where x ranges from 1 to 15 excluding 13
//!     - PWM_DC_TRIP_COMBINATION - selects all the Trip signals whose input
//!                                  is enabled by the following function
//!                              PWM_enableDigitalCompareTripCombinationInput()
//!  - dcType
//!     - PWM_DC_TYPE_DCAH  - Digital Compare A High
//!     - PWM_DC_TYPE_DCAL  - Digital Compare A Low
//!     - PWM_DC_TYPE_DCBH  - Digital Compare B High
//!     - PWM_DC_TYPE_DCBL  - Digital Compare B Low
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_selectDigitalCompareTripInput(uint32_t base,
                                   PWM_DigitalCompareTripInput tripSource,
                                   PWM_DigitalCompareType dcType)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the DC trip input
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCTRIPSEL) =
     ((HWREGH(base + PWM_O_DCTRIPSEL) & ~(0xFU << ((uint16_t)dcType << 2U))) |
      ((uint16_t)tripSource << ((uint16_t)dcType << 2U)));
    WRPRT_ENABLE;
}

//
// DCFILT
//
//*****************************************************************************
//
//! Enable DC filter blanking window.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables the DC filter blanking window.
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_enableDigitalCompareBlankingWindow(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable DC filter blanking window
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCFCTL) |= PWM_DCFCTL_BLANKE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable DC filter blanking window.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables the DC filter blanking window.
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_disableDigitalCompareBlankingWindow(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable DC filter blanking window
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCFCTL) &= ~PWM_DCFCTL_BLANKE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable Digital Compare Window inverse mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables the Digital Compare Window inverse mode. This will
//! invert the blanking window.
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_enableDigitalCompareWindowInverseMode(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable DC window inverse mode.
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCFCTL) |= PWM_DCFCTL_BLANKINV;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable Digital Compare Window inverse mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables the Digital Compare Window inverse mode.
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_disableDigitalCompareWindowInverseMode(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable DC window inverse mode.
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCFCTL) &= ~PWM_DCFCTL_BLANKINV;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the Digital Compare filter blanking pulse.
//!
//! \param base is the base address of the PWM module.
//! \param blankingPulse is Pulse that starts blanking window.
//!
//! This function sets the input pulse that starts the Digital Compare blanking
//! window.
//! Valid values for blankingPulse are:
//!   - PWM_DC_WINDOW_START_TBCTR_PERIOD - Time base counter equals period
//!   - PWM_DC_WINDOW_START_TBCTR_ZERO   - Time base counter equals zero
//!   - PWM_DC_WINDOW_START_TBCTR_ZERO_PERIOD - Time base counter equals zero
//!                                              or period.
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_setDigitalCompareBlankingEvent(uint32_t base,
                                PWM_DigitalCompareBlankingPulse blankingPulse)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set DC blanking event
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCFCTL) =
            ((HWREGH(base + PWM_O_DCFCTL) & ~PWM_DCFCTL_PULSESEL_M) |
             ((uint16_t)((uint32_t)blankingPulse << PWM_DCFCTL_PULSESEL_S)));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set up the Digital Compare filter input.
//!
//! \param base is the base address of the PWM module.
//! \param filterInput is Digital Compare signal source.
//!
//! This function sets the signal input source that will be filtered by the
//! Digital Compare module.
//! Valid values for filterInput are:
//!   - PWM_DC_WINDOW_SOURCE_DCAEVT1  - DC filter signal source is DCAEVT1
//!   - PWM_DC_WINDOW_SOURCE_DCAEVT2  - DC filter signal source is DCAEVT2
//!   - PWM_DC_WINDOW_SOURCE_DCBEVT1  - DC filter signal source is DCBEVT1
//!   - PWM_DC_WINDOW_SOURCE_DCBEVT2  - DC filter signal source is DCBEVT2
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_setDigitalCompareFilterInput(uint32_t base,
                                  PWM_DigitalCompareFilterInput filterInput)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the signal source that will be filtered
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCFCTL) =
                  ((HWREGH(base + PWM_O_DCFCTL) & ~PWM_DCFCTL_SRCSEL_M) |
                   ((uint16_t)filterInput));
    WRPRT_ENABLE;
}

//
// DC Edge Filter
//
//*****************************************************************************
//
//! Enable Digital Compare Edge Filter.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables the Digital Compare Edge filter to generate event
//! after configured number of edges.
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_enableDigitalCompareEdgeFilter(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable DC Edge Filter
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCFCTL) |= PWM_DCFCTL_EDGEFILTSEL;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable Digital Compare Edge Filter.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables the Digital Compare Edge filter.
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_disableDigitalCompareEdgeFilter(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable DC Edge Filter
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCFCTL) &= ~PWM_DCFCTL_EDGEFILTSEL;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the Digital Compare Edge Filter Mode.
//!
//! \param base is the base address of the PWM module.
//! \param edgeMode is Digital Compare Edge filter mode.
//!
//! This function sets the Digital Compare Event filter mode. Valid values
//! for edgeMode are:
//!   - PWM_DC_EDGEFILT_MODE_RISING  - DC edge filter mode is rising edge
//!   - PWM_DC_EDGEFILT_MODE_FALLING - DC edge filter mode is falling edge
//!   - PWM_DC_EDGEFILT_MODE_BOTH    - DC edge filter mode is both edges
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_setDigitalCompareEdgeFilterMode(uint32_t base,
                                     PWM_DigitalCompareEdgeFilterMode edgeMode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set DC Edge filter mode
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCFCTL) = (HWREGH(base + PWM_O_DCFCTL) &
                                    ~PWM_DCFCTL_EDGEMODE_M) |
                                   ((uint16_t)edgeMode << PWM_DCFCTL_EDGEMODE_S);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the Digital Compare Edge Filter Edge Count.
//!
//! \param base is the base address of the PWM module.
//! \param edgeCount is Digital Compare event filter count
//!
//! This function sets the Digital Compare Event filter Edge Count to generate
//! events. Valid values for edgeCount can be:
//!  - PWM_DC_EDGEFILT_EDGECNT_0 - No edge is required to generate event
//!  - PWM_DC_EDGEFILT_EDGECNT_1 - 1 edge is required for event generation
//!  - PWM_DC_EDGEFILT_EDGECNT_2 - 2 edges are required for event generation
//!  - PWM_DC_EDGEFILT_EDGECNT_3 - 3 edges are required for event generation
//!  - PWM_DC_EDGEFILT_EDGECNT_4 - 4 edges are required for event generation
//!  - PWM_DC_EDGEFILT_EDGECNT_5 - 5 edges are required for event generation
//!  - PWM_DC_EDGEFILT_EDGECNT_6 - 6 edges are required for event generation
//!  - PWM_DC_EDGEFILT_EDGECNT_7 - 7 edges are required for event generation
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_setDigitalCompareEdgeFilterEdgeCount(uint32_t base, uint16_t edgeCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set DC Edge filter edge count
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCFCTL) = (HWREGH(base + PWM_O_DCFCTL) &
                                    ~PWM_DCFCTL_EDGECOUNT_M) |
                                   (edgeCount << PWM_DCFCTL_EDGECOUNT_S);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Returns the Digital Compare Edge Filter Edge Count.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the configured Digital Compare Edge filter edge
//! count required to generate events. It can return values from 0-7.
//!
//! \return Returns the configured DigitalCompare Edge filter edge count.
//
//*****************************************************************************
static inline uint16_t
PWM_getDigitalCompareEdgeFilterEdgeCount(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return configured DC edge filter edge count
    //
    return((HWREGH(base + PWM_O_DCFCTL) & PWM_DCFCTL_EDGECOUNT_M) >>
           PWM_DCFCTL_EDGECOUNT_S);
}

//*****************************************************************************
//
//! Returns the Digital Compare Edge filter captured edge count status.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the count of edges captured by Digital Compare Edge
//! filter. It can return values from 0-7.
//!
//! \return Returns the count of captured edges
//
//*****************************************************************************
static inline uint16_t
PWM_getDigitalCompareEdgeFilterEdgeStatus(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return captured edge count by DC Edge filter
    //
    return((HWREGH(base + PWM_O_DCFCTL) & PWM_DCFCTL_EDGESTATUS_M) >>
           PWM_DCFCTL_EDGESTATUS_S);
}

//*****************************************************************************
//
//! Set up the Digital Compare filter window offset
//!
//! \param base is the base address of the PWM module.
//! \param windowOffsetCount is blanking window offset length.
//!
//! This function sets the offset between window start pulse and blanking
//! window in TBCLK count.
//! The function take a 16bit count value for the offset value.
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_setDigitalCompareWindowOffset(uint32_t base, uint16_t windowOffsetCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the blanking window offset in TBCLK counts
    //
    HWREGH(base + PWM_O_DCFOFFSET) = windowOffsetCount;
}

//*****************************************************************************
//
//! Set up the Digital Compare filter window length
//!
//! \param base is the base address of the PWM module.
//! \param windowLengthCount is blanking window length.
//!
//! This function sets up the Digital Compare filter blanking window length in
//! TBCLK count.The function takes a 16bit count value for the window length.
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_setDigitalCompareWindowLength(uint32_t base, uint16_t windowLengthCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the blanking window length in TBCLK counts
    //
    HWREGH(base + PWM_O_DCFWINDOW) = windowLengthCount;
}

//*****************************************************************************
//
//! Return DC filter blanking window offset count.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns DC filter blanking window offset count.
//!
//! \return None
//
//*****************************************************************************
static inline uint16_t
PWM_getDigitalCompareBlankingWindowOffsetCount(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return the Blanking Window Offset count
    //
    return(HWREGH(base + PWM_O_DCFOFFSETCNT));
}

//*****************************************************************************
//
//! Return DC filter blanking window length count.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns DC filter blanking window length count.
//!
//! \return None
//
//*****************************************************************************
static inline uint16_t
PWM_getDigitalCompareBlankingWindowLengthCount(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return the Blanking Window Length count
    //
    return(HWREGH(base + PWM_O_DCFWINDOWCNT));
}

//*****************************************************************************
//
//! Set up the Digital Compare Event source.
//!
//! \param base is the base address of the PWM module.
//! \param dcModule is the Digital Compare module.
//! \param dcEvent is the Digital Compare Event number.
//! \param dcEventSource is the - Digital Compare Event source.
//!
//! This function sets up the Digital Compare module Event sources.
//! The following are valid values for the parameters.
//!  - dcModule
//!      - PWM_DC_MODULE_A  - Digital Compare Module A
//!      - PWM_DC_MODULE_B  - Digital Compare Module B
//!  - dcEvent
//!      - PWM_DC_EVENT_1   - Digital Compare Event number 1
//!      - PWM_DC_EVENT_2   - Digital Compare Event number 2
//!  - dcEventSource
//!      - PWM_DC_EVENT_SOURCE_FILT_SIGNAL  - signal source is filtered
//!            \note The signal source for this option is DCxEVTy, where the
//!                  value of x is dependent on dcModule and the value of y is
//!                  dependent on dcEvent. Possible signal sources are DCAEVT1,
//!                  DCBEVT1, DCAEVT2 or DCBEVT2 depending on the value of both
//!                  dcModule and dcEvent.
//!      - PWM_DC_EVENT_SOURCE_ORIG_SIGNAL  - signal source is unfiltered
//!                   The signal source for this option is DCxEVTy.
//! \return None
//
//*****************************************************************************
static inline void
PWM_setDigitalCompareEventSource(uint32_t base,
                                  PWM_DigitalCompareModule dcModule,
                                  PWM_DigitalCompareEvent dcEvent,
                                  PWM_DigitalCompareEventSource dcEventSource)
{
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    registerOffset = PWM_O_DCACTL + ((uint32_t)dcModule) * 2;

    //
    // Set the DC event 1 source source
    //
    WRPRT_DISABLE;
    if(dcEvent == PWM_DC_EVENT_1)
    {
        HWREGH(base + registerOffset) =
                ((HWREGH(base + registerOffset) & ~PWM_DCACTL_EVT1SRCSEL) |
                 (uint16_t)dcEventSource);
    }
    else
    {
        HWREGH(base + registerOffset) =
                 ((HWREGH(base + registerOffset) & ~PWM_DCACTL_EVT2SRCSEL) |
                  ((uint16_t)dcEventSource << 8U));
    }
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set up the Digital Compare input sync mode.
//!
//! \param base is the base address of the PWM module.
//! \param dcModule is the Digital Compare module.
//! \param dcEvent is the Digital Compare Event number.
//! \param syncMode is the Digital Compare Event sync mode.
//!
//! This function sets up the Digital Compare module Event sources.
//! The following are valid values for the parameters.
//!  - dcModule
//!      - PWM_DC_MODULE_A  - Digital Compare Module A
//!      - PWM_DC_MODULE_B  - Digital Compare Module B
//!  - dcEvent
//!      - PWM_DC_EVENT_1   - Digital Compare Event number 1
//!      - PWM_DC_EVENT_2   - Digital Compare Event number 2
//!  - syncMode
//!      - PWM_DC_EVENT_INPUT_SYNCED      - DC input signal is synced with
//!                                          TBCLK
//!      - PWM_DC_EVENT_INPUT_NOT SYNCED  - DC input signal is not synced with
//!                                          TBCLK
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_setDigitalCompareEventSyncMode(uint32_t base,
                                    PWM_DigitalCompareModule dcModule,
                                    PWM_DigitalCompareEvent dcEvent,
                                    PWM_DigitalCompareSyncMode syncMode)
{
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    registerOffset = PWM_O_DCACTL + ((uint32_t)dcModule) * 2;

    //
    // Set the DC event sync mode
    //
    WRPRT_DISABLE;
    if(dcEvent == PWM_DC_EVENT_1)
    {
        HWREGH(base + registerOffset) =
           ((HWREGH(base + registerOffset) & ~PWM_DCACTL_EVT1FRCSYNCSEL) |
            ((uint16_t)syncMode << 1U));
    }
    else
    {
        HWREGH(base + registerOffset) =
            ((HWREGH(base + registerOffset) & ~PWM_DCACTL_EVT2FRCSYNCSEL) |
             ((uint16_t)syncMode << 9U));
    }
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable Digital Compare to generate Start of Conversion.
//!
//! \param base is the base address of the PWM module.
//! \param dcModule is the Digital Compare module.
//!
//! This function enables the Digital Compare Event 1 to generate Start of
//! Conversion.
//! The following are valid values for the \e dcModule parameter.
//!     - PWM_DC_MODULE_A  - Digital Compare Module A
//!     - PWM_DC_MODULE_B  - Digital Compare Module B
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_enableDigitalCompareADCTrigger(uint32_t base,
                                    PWM_DigitalCompareModule dcModule)
{
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //registerOffset = PWM_O_DCACTL + (uint32_t)dcModule;
    registerOffset = PWM_O_DCACTL + ((uint32_t)dcModule) *2;

    //
    // Enable Digital Compare start of conversion generation
    //
    WRPRT_DISABLE;
    HWREGH(base + registerOffset) =
                       (HWREGH(base + registerOffset) | PWM_DCACTL_EVT1SOCE);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable Digital Compare from generating Start of Conversion.
//!
//! \param base is the base address of the PWM module.
//! \param dcModule is the Digital Compare module.
//!
//! This function disables the Digital Compare Event 1 from generating Start of
//! Conversion.
//! The following are valid values for the \e dcModule parameter.
//!     - PWM_DC_MODULE_A  - Digital Compare Module A
//!     - PWM_DC_MODULE_B  - Digital Compare Module B
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_disableDigitalCompareADCTrigger(uint32_t base,
                                     PWM_DigitalCompareModule dcModule)
{
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    registerOffset = PWM_O_DCACTL + ((uint32_t)dcModule) *2;

    //
    // Disable Digital Compare start of conversion generation
    //
    WRPRT_DISABLE;
    HWREGH(base + registerOffset) =
                      (HWREGH(base + registerOffset) & ~PWM_DCACTL_EVT1SOCE);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable Digital Compare to generate sync out pulse.
//!
//! \param base is the base address of the PWM module.
//! \param dcModule is the Digital Compare module.
//!
//! This function enables the Digital Compare Event 1 to generate sync out
//! pulse
//! The following are valid values for the \e dcModule parameter.
//!     - PWM_DC_MODULE_A  - Digital Compare Module A
//!     - PWM_DC_MODULE_B  - Digital Compare Module B
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_enableDigitalCompareSyncEvent(uint32_t base,
                                   PWM_DigitalCompareModule dcModule)
{
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    registerOffset = PWM_O_DCACTL + ((uint32_t)dcModule) *2;

    //
    // Enable Digital Compare sync out pulse generation
    //
    WRPRT_DISABLE;
    HWREGH(base + registerOffset) =
                     (HWREGH(base + registerOffset) | PWM_DCACTL_EVT1SYNCE);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable Digital Compare from generating Start of Conversion.
//!
//! \param base is the base address of the PWM module.
//! \param dcModule is the Digital Compare module.
//!
//! This function disables the Digital Compare Event 1 from generating synch
//! out pulse.
//! The following are valid values for the \e dcModule parameters.
//!     - PWM_DC_MODULE_A  - Digital Compare Module A
//!     - PWM_DC_MODULE_B  - Digital Compare Module B
//!
//! \return None
//
//*****************************************************************************
static inline void
PWM_disableDigitalCompareSyncEvent(uint32_t base,
                                    PWM_DigitalCompareModule dcModule)
{
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    registerOffset = PWM_O_DCACTL + ((uint32_t)dcModule) *2;

    //
    // Disable Digital Compare sync out pulse generation
    //
    WRPRT_DISABLE;
    HWREGH(base + registerOffset) =
                      (HWREGH(base + registerOffset) & ~PWM_DCACTL_EVT1SYNCE);
    WRPRT_ENABLE;
}

//
// DC capture mode
//
//*****************************************************************************
//
//! Enables the Time Base Counter Capture controller.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables the time Base Counter Capture.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableDigitalCompareCounterCapture(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable Time base counter capture
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCCAPCTL) |= PWM_DCCAPCTL_CAPE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables the Time Base Counter Capture controller.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disable the time Base Counter Capture.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableDigitalCompareCounterCapture(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Disable Time base counter capture
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCCAPCTL) &= ~PWM_DCCAPCTL_CAPE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the Time Base Counter Capture mode.
//!
//! \param base is the base address of the PWM module.
//! \param enableShadowMode is the shadow read mode flag.
//!
//! This function sets the mode the Time Base Counter value is read from. If
//! enableShadowMode is true, CPU reads of the DCCAP register will return the
//! shadow register contents.If enableShadowMode is false, CPU reads of the
//! DCCAP register will return the active register contents.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setDigitalCompareCounterShadowMode(uint32_t base, bool enableShadowMode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    WRPRT_DISABLE;
    if(enableShadowMode)
    {
        //
        // Enable DC counter shadow mode
        //
        HWREGH(base + PWM_O_DCCAPCTL) &= ~PWM_DCCAPCTL_SHDWMODE;
    }
    else
    {
       //
       // Disable DC counter shadow mode
       //
       HWREGH(base + PWM_O_DCCAPCTL) |= PWM_DCCAPCTL_SHDWMODE;
    }
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Return the DC Capture event status.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the DC capture event status.
//!
//! \return Returns true if a DC capture event has occurs.
//!         Returns false if no DC Capture event has occurred.
//!
//! \return None.
//
//*****************************************************************************
static inline bool
PWM_getDigitalCompareCaptureStatus(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return the DC compare status
    //
    return((HWREGH(base + PWM_O_DCCAPCTL) & PWM_DCCAPCTL_CAPSTS) ==
                                                        PWM_DCCAPCTL_CAPSTS);
}

//*****************************************************************************
//
//! Clears DC capture latched status flag
//!
//! \param base is the base address of the PWM module.
//! This function is used to clear the CAPSTS (set) condition.
//!
//! \return None.
//*****************************************************************************
static inline void
PWM_clearDigitalCompareCaptureStatusFlag(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Clear digital compare capture status flag
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_DCCAPCTL) |= PWM_DCCAPCTL_CAPCLR;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Configures DC capture operating mode
//!
//! \param base is the base address of the PWM module.
//! \param disableClearMode is the clear mode bit.
//!
//! This function is used to configure the DC capture operating mode. If
//! \e disableClearMode is false, the TBCNT value is captured in active register
//! on occurance of DCEVTFILT event. The trip events are ignored until next
//! PRD or ZRO event re-triggers the capture mechanism.
//! If \e disableClearMode is true, the TBCNT value is captured, CAPSTS flag is
//! set and further trips are ignored until CAPSTS bit is cleared.
//!
//! \return None.
//*****************************************************************************
static inline void
PWM_configureDigitalCompareCounterCaptureMode(uint32_t base,
                                               bool disableClearMode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    WRPRT_DISABLE;
    if(disableClearMode)
    {
        //
        // Disable DC counter auto-clear on PULSESEL event
        //
        HWREGH(base + PWM_O_DCCAPCTL) |= PWM_DCCAPCTL_CAPMODE;
    }
    else
    {
       //
       // Enable DC counter clear on PULSESEL events
       //
       HWREGH(base + PWM_O_DCCAPCTL) &= ~PWM_DCCAPCTL_CAPMODE;
    }
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Return the DC Time Base Counter capture value.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the DC Time Base Counter capture value. The value
//! read is determined by the mode as set in the
//! PWM_setTimeBaseCounterReadMode() function.
//!
//! \return Returns the DC Time Base Counter Capture count value.
//
//*****************************************************************************
static inline uint16_t
PWM_getDigitalCompareCaptureCount(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return the DC Time Base Counter Capture count value
    //
    return(HWREGH(base + PWM_O_DCCAP));
}

//*****************************************************************************
//
//! Enable DC TRIP combinational input.
//!
//! \param base is the base address of the PWM module.
//! \param tripInput is the Trip number.
//! \param dcType is the Digital Compare module.
//!
//! This function enables the specified Trip input.
//! Valid values for the parameters are:
//!  - tripInput
//!      - PWM_DC_COMBINATIONAL_TRIPINx, where x is 1,2,...12,14,15
//!  - dcType
//!      - PWM_DC_TYPE_DCAH  - Digital Compare A High
//!      - PWM_DC_TYPE_DCAL  - Digital Compare A Low
//!      - PWM_DC_TYPE_DCBH  - Digital Compare B High
//!      - PWM_DC_TYPE_DCBL  - Digital Compare B Low
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableDigitalCompareTripCombinationInput(uint32_t base,
                                              uint16_t tripInput,
                                              PWM_DigitalCompareType dcType)
{
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Get the DCAHTRIPSEL, DCALTRIPSEL, DCBHTRIPSEL, DCBLTRIPSEL register
    // offset with respect to DCAHTRIPSEL
    
    registerOffset = PWM_O_DCAHTRIPSEL + ((uint32_t)dcType) * 2;

    //
    // Set the DC trip input
    //
    WRPRT_DISABLE;
    HWREGH(base + registerOffset) =
                           (HWREGH(base + registerOffset) | tripInput);

    //
    // Enable the combination input
    //
    HWREGH(base + PWM_O_DCTRIPSEL) =
      (HWREGH(base + PWM_O_DCTRIPSEL) | (0xFU << ((uint16_t)dcType << 2U)));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable DC TRIP combinational input.
//!
//! \param base is the base address of the PWM module.
//! \param tripInput is the Trip number.
//! \param dcType is the Digital Compare module.
//!
//! This function disables the specified Trip input.
//! Valid values for the parameters are:
//!  - tripInput
//!      - PWM_DC_COMBINATIONAL_TRIPINx, where x is 1,2,...12,14,15
//!  - dcType
//!      - PWM_DC_TYPE_DCAH  - Digital Compare A High
//!      - PWM_DC_TYPE_DCAL  - Digital Compare A Low
//!      - PWM_DC_TYPE_DCBH  - Digital Compare B High
//!      - PWM_DC_TYPE_DCBL  - Digital Compare B Low
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableDigitalCompareTripCombinationInput(uint32_t base,
                                               uint16_t tripInput,
                                               PWM_DigitalCompareType dcType)
{
    uint32_t registerOffset;

    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Get the DCAHTRIPSEL, DCALTRIPSEL, DCBHTRIPSEL, DCBLTRIPSEL register
    // offset with respect to DCAHTRIPSEL
    //

    registerOffset = PWM_O_DCAHTRIPSEL + ((uint32_t)dcType) * 2;

    //
    // Set the DC trip input
    //
    WRPRT_DISABLE;
    HWREGH(base + registerOffset) =
                           (HWREGH(base + registerOffset) & ~tripInput);
    WRPRT_ENABLE;
}

//
// Valley switching
//
//*****************************************************************************
//
//! Enable valley capture mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables Valley Capture mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableValleyCapture(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set VCAPE bit
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_VCAPCTL) |= PWM_VCAPCTL_VCAPE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable valley capture mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables Valley Capture mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableValleyCapture(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Clear VCAPE bit
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_VCAPCTL) &= ~PWM_VCAPCTL_VCAPE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Start valley capture mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function starts Valley Capture sequence.
//!
//! \b Make sure you invoke PWM_setValleyTriggerSource with the trigger
//!    variable set to PWM_VALLEY_TRIGGER_EVENT_SOFTWARE before calling this
//!    function.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_startValleyCapture(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set VCAPSTART bit
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_VCAPCTL) |= PWM_VCAPCTL_VCAPSTART;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set valley capture trigger.
//!
//! \param base is the base address of the PWM module.
//! \param trigger is the Valley counter trigger.
//!
//! This function sets the trigger value that initiates Valley Capture sequence
//!
//! \b Set the number of Trigger source events for starting and stopping the
//!    valley capture using PWM_setValleyTriggerEdgeCounts().
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setValleyTriggerSource(uint32_t base, PWM_ValleyTriggerSource trigger)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Write to TRIGSEL bits
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_VCAPCTL) =
             ((HWREGH(base + PWM_O_VCAPCTL) & ~PWM_VCAPCTL_TRIGSEL_M) |
              ((uint16_t)trigger << 2U));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set valley capture trigger source count.
//!
//! \param base is the base address of the PWM module.
//! \param startCount
//! \param stopCount
//!
//! This function sets the number of trigger events required to start and stop
//! the valley capture count.
//! Maximum values for both startCount and stopCount is 15 corresponding to the
//! 15th edge of the trigger event.
//!
//! \b Note:
//!    A startCount value of 0 prevents starting the valley counter.
//!    A stopCount value of 0 prevents the valley counter from stopping.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setValleyTriggerEdgeCounts(uint32_t base, uint16_t startCount,
                                uint16_t stopCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT((startCount < 16U) && (stopCount < 16U));

    //
    // Write to STARTEDGE and STOPEDGE bits
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_VCNTCFG) =
                    ((HWREGH(base + PWM_O_VCNTCFG) &
                      ~(PWM_VCNTCFG_STARTEDGE_M | PWM_VCNTCFG_STOPEDGE_M)) |
                      (startCount | (stopCount << 8U)));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable valley switching delay.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables Valley switching delay.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableValleyHWDelay(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set EDGEFILTDLYSEL bit
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_VCAPCTL) |= PWM_VCAPCTL_EDGEFILTDLYSEL;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable valley switching delay.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables Valley switching delay.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableValleyHWDelay(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Clear EDGEFILTDLYSEL bit
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_VCAPCTL) &= ~PWM_VCAPCTL_EDGEFILTDLYSEL;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Valley delay values.
//!
//! \param base is the base address of the PWM module.
//! \param delayOffsetValue is the software defined delay offset value.
//!
//! This function sets the Valley delay value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setValleySWDelayValue(uint32_t base, uint16_t delayOffsetValue)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Write to SWVDELVAL bits
    //
    HWREGH(base + PWM_O_SWVDELVAL) = delayOffsetValue;
}

//*****************************************************************************
//
//! Set Valley delay mode.
//!
//! \param base is the base address of the PWM module.
//! \param delayMode is the Valley delay mode.
//!
//! This function sets the Valley delay mode values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setValleyDelayDivider(uint32_t base, PWM_ValleyDelayMode delayMode)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Write to VDELAYDIV bits
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_VCAPCTL) =
         ((HWREGH(base + PWM_O_VCAPCTL) & ~PWM_VCAPCTL_VDELAYDIV_M) |
          ((uint16_t)delayMode << 7U));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Get the valley edge status bit.
//!
//! \param base is the base address of the PWM module.
//! \param edge is the start or stop edge.
//!
//! This function returns the status of the start or stop valley status
//! depending on the value of edge.
//! If a start or stop edge has occurred, the function returns true, if not it
//! returns false.
//!
//! \return Returns true if the specified edge has occurred,
//!         Returns false if the specified edge has not occurred.
//
//*****************************************************************************
static inline bool
PWM_getValleyEdgeStatus(uint32_t base, PWM_ValleyCounterEdge edge)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    if(edge == PWM_VALLEY_COUNT_START_EDGE)
    {
        //
        // Returns STARTEDGESTS status
        //
        return(((HWREGH(base + PWM_O_VCNTCFG) & PWM_VCNTCFG_STARTEDGESTS) ==
                   PWM_VCNTCFG_STARTEDGESTS ) ? true : false);
    }
    else
    {
        //
        // Returns STOPEDGESTS status
        //
        return(((HWREGH(base + PWM_O_VCNTCFG) & PWM_VCNTCFG_STOPEDGESTS) ==
                PWM_VCNTCFG_STOPEDGESTS) ? true : false);
    }
}

//*****************************************************************************
//
//! Get the Valley Counter value.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the valley time base count value which is captured
//! upon occurrence of the stop edge condition selected by
//! PWM_setValleyTriggerSource() and by the stopCount variable of the
//! PWM_setValleyTriggerEdgeCounts() function.
//!
//! \return Returns the valley base time count.
//
//*****************************************************************************
static inline uint16_t
PWM_getValleyCount(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Read VCNTVAL register
    //
    return(HWREGH(base + PWM_O_VCNTVAL));
}

//*****************************************************************************
//
//! Get the Valley delay value.
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the hardware valley delay count.
//!
//! \return Returns the valley delay count.
//
//*****************************************************************************
static inline uint16_t
PWM_getValleyHWDelay(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Read HWVDELVAL  register
    //
    return(HWREGH(base + PWM_O_HWVDELVAL));
}

//*****************************************************************************
//
//! Enable Global shadow load mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables Global shadow to active load mode of registers.
//! The trigger source for loading shadow to active is determined by
//! PWM_setGlobalLoadTrigger() function.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableGlobalLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Shadow to active load is controlled globally
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_GLDCTL) |= PWM_GLDCTL_GLD;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable Global shadow load mode.
//!
//! \param base is the base address of the PWM module.
//!
//! This function disables Global shadow to active load mode of registers.
//! Loading shadow to active is determined individually.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableGlobalLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Shadow to active load is controlled individually
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_GLDCTL) &= ~PWM_GLDCTL_GLD;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the Global shadow load pulse.
//!
//! \param base is the base address of the PWM module.
//! \param loadTrigger is the pulse that causes global shadow load.
//!
//! This function sets the pulse that causes Global shadow to active load.
//! Valid values for the loadTrigger parameter are:
//!
//!   - PWM_GL_LOAD_PULSE_CNTR_ZERO              - load when counter is equal
//!                                                 to zero
//!   - PWM_GL_LOAD_PULSE_CNTR_PERIOD            - load when counter is equal
//!                                                 to period
//!   - PWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD       - load when counter is equal
//!                                                 to zero or period
//!   - PWM_GL_LOAD_PULSE_SYNC                    - load on sync event
//!   - PWM_GL_LOAD_PULSE_SYNC_OR_CNTR_ZERO      - load on sync event or when
//!                                                 counter is equal to zero
//!   - PWM_GL_LOAD_PULSE_SYNC_OR_CNTR_PERIOD    - load on sync event or when
//!                                                 counter is equal to period
//!   - PWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD  - load on sync event or when
//!                                                 counter is equal to period
//!                                                 or zero
//!   - PWM_GL_LOAD_PULSE_GLOBAL_FORCE            - load on global force
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setGlobalLoadTrigger(uint32_t base, PWM_GlobalLoadTrigger loadTrigger)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set the Global shadow to active load pulse
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_GLDCTL) =
               ((HWREGH(base + PWM_O_GLDCTL) & ~PWM_GLDCTL_GLDMODE_M) |
                ((uint16_t)loadTrigger << PWM_GLDCTL_GLDMODE_S));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the number of Global load pulse event counts
//!
//! \param base is the base address of the PWM module.
//! \param prescalePulseCount is the pulse event counts.
//!
//! This function sets the number of Global Load pulse events that have to
//! occurred before a global load pulse is issued. Valid values for
//! prescaleCount range from 0 to 7. 0 being no event (disables counter), and 7
//! representing 7 events.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setGlobalLoadEventPrescale(uint32_t base, uint16_t prescalePulseCount)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT(prescalePulseCount < 8U);

    //
    // Set the number of counts that have to occur before
    // a load strobe is issued
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_GLDCTL) =
                ((HWREGH(base + PWM_O_GLDCTL) & ~PWM_GLDCTL_GLDPRD_M) |
                 (prescalePulseCount << PWM_GLDCTL_GLDPRD_S));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Return the number of Global load pulse event counts
//!
//! \param base is the base address of the PWM module.
//!
//! This function returns the number of Global Load pulse events that have
//! occurred. These pulse events are set by the PWM_setGlobalLoadTrigger()
//! function.
//!
//! \return None.
//
//*****************************************************************************
static inline uint16_t
PWM_getGlobalLoadEventCount(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Return the number of events that have occurred
    //
    return((HWREGH(base + PWM_O_GLDCTL) >> PWM_GLDCTL_GLDCNT_S) & 0x7U);
}

//*****************************************************************************
//
//! Enable continuous global shadow to active load.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables global continuous shadow to active load. Register
//! load happens every time the event set by the
//! PWM_setGlobalLoadTrigger() occurs.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableGlobalLoadOneShotMode(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable global continuous shadow to active load
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_GLDCTL) &= ~PWM_GLDCTL_OSHTMODE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable One shot global shadow to active load.
//!
//! \param base is the base address of the PWM module.
//!
//! This function enables a one time global shadow to active load. Register
//! load happens every time the event set by the
//! PWM_setGlobalLoadTrigger() occurs.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableGlobalLoadOneShotMode(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Enable global continuous shadow to active load
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_GLDCTL) |= PWM_GLDCTL_OSHTMODE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set One shot global shadow to active load pulse.
//!
//! \param base is the base address of the PWM module.
//!
//! This function sets a one time global shadow to active load pulse. The pulse
//! propagates to generate a load signal if any of the events set by
//! PWM_setGlobalLoadTrigger() occur.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_setGlobalLoadOneShotLatch(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Set a one shot Global shadow load pulse.
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_GLDCTL2) |= PWM_GLDCTL2_OSHTLD;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Force a software One shot global shadow to active load pulse.
//!
//! \param base is the base address of the PWM module.
//!
//! This function forces a software a one time global shadow to active load
//! pulse.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_forceGlobalLoadOneShotEvent(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Force a Software Global shadow load pulse
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_GLDCTL2) |= PWM_GLDCTL2_GFRCLD;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable a register to be loaded Globally.
//!
//! \param base is the base address of the PWM module.
//! \param loadRegister is the register.
//!
//! This function enables the register specified by loadRegister to be globally
//! loaded.
//! Valid values for loadRegister are:
//!  - PWM_GL_REGISTER_TBPRD_TBPRDHR  - Register TBPRD:TBPRDHR
//!  - PWM_GL_REGISTER_CMPA_CMPAHR    - Register CMPA:CMPAHR
//!  - PWM_GL_REGISTER_CMPB_CMPBHR    - Register CMPB:CMPBHR
//!  - PWM_GL_REGISTER_CMPC           - Register CMPC
//!  - PWM_GL_REGISTER_CMPD           - Register CMPD
//!  - PWM_GL_REGISTER_DBRED_DBREDHR  - Register DBRED:DBREDHR
//!  - PWM_GL_REGISTER_DBFED_DBFEDHR  - Register DBFED:DBFEDHR
//!  - PWM_GL_REGISTER_DBCTL          - Register DBCTL
//!  - PWM_GL_REGISTER_AQCTLA_AQCTLA2 - Register AQCTLA/A2
//!  - PWM_GL_REGISTER_AQCTLB_AQCTLB2 - Register AQCTLB/B2
//!  - PWM_GL_REGISTER_AQCSFRC        - Register AQCSFRC
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_enableGlobalLoadRegisters(uint32_t base, uint16_t loadRegister)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT((loadRegister > 0x0000U) && (loadRegister < 0x0800U));

    //
    // The register specified by loadRegister is loaded globally
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_GLDCFG) |= loadRegister;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable a register to be loaded Globally.
//!
//! \param base is the base address of the PWM module.
//! \param loadRegister is the register.
//!
//! This function disables the register specified by loadRegister from being
//! loaded globally. The shadow to active load happens as specified by the
//! register control
//! Valid values for loadRegister are:
//!  - PWM_GL_REGISTER_TBPRD_TBPRDHR  - Register TBPRD:TBPRDHR
//!  - PWM_GL_REGISTER_CMPA_CMPAHR    - Register CMPA:CMPAHR
//!  - PWM_GL_REGISTER_CMPB_CMPBHR    - Register CMPB:CMPBHR
//!  - PWM_GL_REGISTER_CMPC           - Register CMPC
//!  - PWM_GL_REGISTER_CMPD           - Register CMPD
//!  - PWM_GL_REGISTER_DBRED_DBREDHR  - Register DBRED:DBREDHR
//!  - PWM_GL_REGISTER_DBFED_DBFEDHR  - Register DBFED:DBFEDHR
//!  - PWM_GL_REGISTER_DBCTL          - Register DBCTL
//!  - PWM_GL_REGISTER_AQCTLA_AQCTLA2 - Register AQCTLA/A2
//!  - PWM_GL_REGISTER_AQCTLB_AQCTLB2 - Register AQCTLB/B2
//!  - PWM_GL_REGISTER_AQCSFRC        - Register AQCSFRC
//!
//! \return None.
//
//*****************************************************************************
static inline void
PWM_disableGlobalLoadRegisters(uint32_t base, uint16_t loadRegister)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));
    ASSERT((loadRegister > 0x0000U) && (loadRegister < 0x0800U));

    //
    // The register specified by loadRegister is loaded by individual
    // register configuration setting
    //
    WRPRT_DISABLE;
    HWREGH(base + PWM_O_GLDCFG) &= ~loadRegister;
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
PWM_lockRegisters(uint32_t base, PWM_LockRegisterGroup registerGroup)
{
    //
    // Check the arguments
    //
    ASSERT(PWM_isBaseValid(base));

    //
    // Write the Key to LOCK register
    //
    HWREG(base + PWM_O_LOCK) =
            ((uint32_t)0xA5A50000U | ((uint32_t)registerGroup));
}

//*****************************************************************************
//
//! Set emulation mode
//!
//! \param base is the base address of the PWM module.
//! \param emulationMode is the emulation mode.
//!
//! This function sets the emulation behaviours of the time base counter. Valid
//! values for emulationMode are:
//!  - PWM_EMULATION_STOP_AFTER_NEXT_TB    - Stop after next Time Base counter
//!                                           increment or decrement.
//!  - PWM_EMULATION_STOP_AFTER_FULL_CYCLE - Stop when counter completes whole
//!                                           cycle.
//!  - PWM_EMULATION_FREE_RUN               - Free run.
//!
//! \return None.
//
//*****************************************************************************
extern void
PWM_setEmulationMode(uint32_t base, PWM_EmulationMode emulationMode);

//*****************************************************************************
//
//! Configures PWM signal with desired frequency & duty
//!
//! \param base is the base address of the PWM module.
//! \param signalParams is the desired signal parameters.
//!
//! This function configures the PWM module to generate a signal with
//! desired frequency & duty.
//!
//! \return None.
//
//*****************************************************************************
extern void
PWM_configureSignal(uint32_t base, const PWM_SignalParams *signalParams);

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

#endif // PWM_H
