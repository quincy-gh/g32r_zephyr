//###########################################################################
//
// FILE:    hw_pwm.h
//
// TITLE:   Definitions for the PWM registers.
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
// 1. Some comments, macro definitions (register and bit-field naming) were changed.
//
//###########################################################################

#ifndef HW_PWM_H
#define HW_PWM_H

//*************************************************************************************************
//
// The following are defines for the PWM register offsets
//
//*************************************************************************************************
#define PWM_O_TBCTL             (0x0U * 2)    // Time Base Control Register
#define PWM_O_TBCTL2            (0x1U * 2)    // Time Base Control Register 2
#define PWM_O_TBCTR             (0x4U * 2)    // Time Base Counter Register
#define PWM_O_TBSTS             (0x5U * 2)    // Time Base Status Register
#define PWM_O_CMPCTL            (0x8U * 2)    // Counter Compare Control Register
#define PWM_O_CMPCTL2           (0x9U * 2)    // Counter Compare Control Register 2
#define PWM_O_DBCTL             (0xCU * 2)    // Dead-Band Generator Control Register
#define PWM_O_DBCTL2            (0xDU * 2)    // Dead-Band Generator Control Register 2
#define PWM_O_AQCTL             (0x10U * 2)   // Action Qualifier Control Register
#define PWM_O_AQTSRCSEL         (0x11U * 2)   // Action Qualifier Trigger Event Source Select Register
#define PWM_O_PCCTL             (0x14U * 2)   // PWM Chopper Control Register
#define PWM_O_VCAPCTL           (0x18U * 2)   // Valley Capture Control Register
#define PWM_O_VCNTCFG           (0x19U * 2)   // Valley Counter Config Register
#define PWM_O_HRCNFG            (0x20U * 2)   // HRPWM Configuration Register
#define PWM_O_HRPWR             (0x21U * 2)   // HRPWM Power Register
#define PWM_O_HRMSTEP           (0x26U * 2)   // HRPWM MEP Step Register
#define PWM_O_HRCNFG2           (0x27U * 2)   // HRPWM Configuration 2 Register
#define PWM_O_HRPCTL            (0x2DU * 2)   // High Resolution Period Control Register
#define PWM_O_TRREM             (0x2EU * 2)   // HRPWM High Resolution Remainder Register
#define PWM_O_GLDCTL            (0x34U * 2)   // Global PWM Load Control Register
#define PWM_O_GLDCFG            (0x35U * 2)   // Global PWM Load Config Register
#define PWM_O_XLINK             (0x38U * 2)   // PWMx Link Register
#define PWM_O_AQCTLA            (0x40U * 2)   // Action Qualifier Control Register For Output A
#define PWM_O_AQCTLA2           (0x41U * 2)   // Additional Action Qualifier Control Register For Output A
#define PWM_O_AQCTLB            (0x42U * 2)   // Action Qualifier Control Register For Output B
#define PWM_O_AQCTLB2           (0x43U * 2)   // Additional Action Qualifier Control Register For Output B
#define PWM_O_AQSFRC            (0x47U * 2)   // Action Qualifier Software Force Register
#define PWM_O_AQCSFRC           (0x49U * 2)   // Action Qualifier Continuous S/W Force Register
#define PWM_O_DBREDHR           (0x50U * 2)   // Dead-Band Generator Rising Edge Delay High Resolution
                                              // Mirror Register
#define PWM_O_DBRED             (0x51U * 2)   // Dead-Band Generator Rising Edge Delay High Resolution
                                              // Mirror Register
#define PWM_O_DBFEDHR           (0x52U * 2)   // Dead-Band Generator Falling Edge Delay High Resolution
                                              // Register
#define PWM_O_DBFED             (0x53U * 2)   // Dead-Band Generator Falling Edge Delay Count Register
#define PWM_O_TBPHS             (0x60U * 2)   // Time Base Phase High
#define PWM_O_TBPRDHR           (0x62U * 2)   // Time Base Period High Resolution Register
#define PWM_O_TBPRD             (0x63U * 2)   // Time Base Period Register
#define PWM_O_CMPA              (0x6AU * 2)   // Counter Compare A Register
#define PWM_O_CMPB              (0x6CU * 2)   // Compare B Register
#define PWM_O_CMPC              (0x6FU * 2)   // Counter Compare C Register
#define PWM_O_CMPD              (0x71U * 2)   // Counter Compare D Register
#define PWM_O_GLDCTL2           (0x74U * 2)   // Global PWM Load Control Register 2
#define PWM_O_SWVDELVAL         (0x77U * 2)   // Software Valley Mode Delay Register
#define PWM_O_TZSEL             (0x80U * 2)   // Trip Zone Select Register
#define PWM_O_TZDCSEL           (0x82U * 2)   // Trip Zone Digital Comparator Select Register
#define PWM_O_TZCTL             (0x84U * 2)   // Trip Zone Control Register
#define PWM_O_TZCTL2            (0x85U * 2)   // Additional Trip Zone Control Register
#define PWM_O_TZCTLDCA          (0x86U * 2)   // Trip Zone Control Register Digital Compare A
#define PWM_O_TZCTLDCB          (0x87U * 2)   // Trip Zone Control Register Digital Compare B
#define PWM_O_TZEINT            (0x8DU * 2)   // Trip Zone Enable Interrupt Register
#define PWM_O_TZFLG             (0x93U * 2)   // Trip Zone Flag Register
#define PWM_O_TZCBCFLG          (0x94U * 2)   // Trip Zone CBC Flag Register
#define PWM_O_TZOSTFLG          (0x95U * 2)   // Trip Zone OST Flag Register
#define PWM_O_TZCLR             (0x97U * 2)   // Trip Zone Clear Register
#define PWM_O_TZCBCCLR          (0x98U * 2)   // Trip Zone CBC Clear Register
#define PWM_O_TZOSTCLR          (0x99U * 2)   // Trip Zone OST Clear Register
#define PWM_O_TZFRC             (0x9BU * 2)   // Trip Zone Force Register
#define PWM_O_ETSEL             (0xA4U * 2)   // Event Trigger Selection Register
#define PWM_O_ETPS              (0xA6U * 2)   // Event Trigger Pre-Scale Register
#define PWM_O_ETFLG             (0xA8U * 2)   // Event Trigger Flag Register
#define PWM_O_ETCLR             (0xAAU * 2)   // Event Trigger Clear Register
#define PWM_O_ETFRC             (0xACU * 2)   // Event Trigger Force Register
#define PWM_O_ETINTPS           (0xAEU * 2)   // Event-Trigger Interrupt Pre-Scale Register
#define PWM_O_ETSOCPS           (0xB0U * 2)   // Event-Trigger SOC Pre-Scale Register
#define PWM_O_ETCNTINITCTL      (0xB2U * 2)   // Event-Trigger Counter Initialization Control Register
#define PWM_O_ETCNTINIT         (0xB4U * 2)   // Event-Trigger Counter Initialization Register
#define PWM_O_DCTRIPSEL         (0xC0U * 2)   // Digital Compare Trip Select Register
#define PWM_O_DCACTL            (0xC3U * 2)   // Digital Compare A Control Register
#define PWM_O_DCBCTL            (0xC4U * 2)   // Digital Compare B Control Register
#define PWM_O_DCFCTL            (0xC7U * 2)   // Digital Compare Filter Control Register
#define PWM_O_DCCAPCTL          (0xC8U * 2)   // Digital Compare Capture Control Register
#define PWM_O_DCFOFFSET         (0xC9U * 2)   // Digital Compare Filter Offset Register
#define PWM_O_DCFOFFSETCNT      (0xCAU * 2)   // Digital Compare Filter Offset Counter Register
#define PWM_O_DCFWINDOW         (0xCBU * 2)   // Digital Compare Filter Window Register
#define PWM_O_DCFWINDOWCNT      (0xCCU * 2)   // Digital Compare Filter Window Counter Register
#define PWM_O_DCCAP             (0xCFU * 2)   // Digital Compare Counter Capture Register
#define PWM_O_DCAHTRIPSEL       (0xD2U * 2)   // Digital Compare AH Trip Select
#define PWM_O_DCALTRIPSEL       (0xD3U * 2)   // Digital Compare AL Trip Select
#define PWM_O_DCBHTRIPSEL       (0xD4U * 2)   // Digital Compare BH Trip Select
#define PWM_O_DCBLTRIPSEL       (0xD5U * 2)   // Digital Compare BL Trip Select
#define PWM_O_LOCK              (0xFAU * 2)   // PWM Lock Register
#define PWM_O_HWVDELVAL         (0xFDU * 2)   // Hardware Valley Mode Delay Register
#define PWM_O_VCNTVAL           (0xFEU * 2)   // Hardware Valley Counter Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the TBCTL register
//
//*************************************************************************************************
#define PWM_TBCTL_CTRMODE_S     0U
#define PWM_TBCTL_CTRMODE_M     0x3U      // Counter Mode
#define PWM_TBCTL_PHSEN         0x4U      // Phase Load Enable
#define PWM_TBCTL_PRDLD         0x8U      // Active Period Load
#define PWM_TBCTL_SYNCOSEL_S    4U
#define PWM_TBCTL_SYNCOSEL_M    0x30U     // Sync Output Select
#define PWM_TBCTL_SWFSYNC       0x40U     // Software Force Sync Pulse
#define PWM_TBCTL_HSPCLKDIV_S   7U
#define PWM_TBCTL_HSPCLKDIV_M   0x380U    // High Speed TBCLK Pre-scaler
#define PWM_TBCTL_CLKDIV_S      10U
#define PWM_TBCTL_CLKDIV_M      0x1C00U   // Time Base Clock Pre-scaler
#define PWM_TBCTL_PHSDIR        0x2000U   // Phase Direction Bit
#define PWM_TBCTL_FREE_SOFT_S   14U
#define PWM_TBCTL_FREE_SOFT_M   0xC000U   // Emulation Mode Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBCTL2 register
//
//*************************************************************************************************
#define PWM_TBCTL2_OSHTSYNCMODE   0x40U     // One shot sync mode
#define PWM_TBCTL2_OSHTSYNC       0x80U     // One shot sync
#define PWM_TBCTL2_SYNCOSELX_S    12U
#define PWM_TBCTL2_SYNCOSELX_M    0x3000U   // Syncout selection
#define PWM_TBCTL2_PRDLDSYNC_S    14U
#define PWM_TBCTL2_PRDLDSYNC_M    0xC000U   // PRD Shadow to Active Load on SYNC Event

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBSTS register
//
//*************************************************************************************************
#define PWM_TBSTS_CTRDIR   0x1U   // Counter Direction Status
#define PWM_TBSTS_SYNCI    0x2U   // External Input Sync Status
#define PWM_TBSTS_CTRMAX   0x4U   // Counter Max Latched Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPCTL register
//
//*************************************************************************************************
#define PWM_CMPCTL_LOADAMODE_S   0U
#define PWM_CMPCTL_LOADAMODE_M   0x3U      // Active Compare A Load
#define PWM_CMPCTL_LOADBMODE_S   2U
#define PWM_CMPCTL_LOADBMODE_M   0xCU      // Active Compare B Load
#define PWM_CMPCTL_SHDWAMODE     0x10U     // Compare A Register Block Operating Mode
#define PWM_CMPCTL_SHDWBMODE     0x40U     // Compare B Register Block Operating Mode
#define PWM_CMPCTL_SHDWAFULL     0x100U    // Compare A Shadow Register Full Status
#define PWM_CMPCTL_SHDWBFULL     0x200U    // Compare B Shadow Register Full Status
#define PWM_CMPCTL_LOADASYNC_S   10U
#define PWM_CMPCTL_LOADASYNC_M   0xC00U    // Active Compare A Load on SYNC
#define PWM_CMPCTL_LOADBSYNC_S   12U
#define PWM_CMPCTL_LOADBSYNC_M   0x3000U   // Active Compare B Load on SYNC

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPCTL2 register
//
//*************************************************************************************************
#define PWM_CMPCTL2_LOADCMODE_S   0U
#define PWM_CMPCTL2_LOADCMODE_M   0x3U      // Active Compare C Load
#define PWM_CMPCTL2_LOADDMODE_S   2U
#define PWM_CMPCTL2_LOADDMODE_M   0xCU      // Active Compare D load
#define PWM_CMPCTL2_SHDWCMODE     0x10U     // Compare C Block Operating Mode
#define PWM_CMPCTL2_SHDWDMODE     0x40U     // Compare D Block Operating Mode
#define PWM_CMPCTL2_LOADCSYNC_S   10U
#define PWM_CMPCTL2_LOADCSYNC_M   0xC00U    // Active Compare C Load on SYNC
#define PWM_CMPCTL2_LOADDSYNC_S   12U
#define PWM_CMPCTL2_LOADDSYNC_M   0x3000U   // Active Compare D Load on SYNC

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBCTL register
//
//*************************************************************************************************
#define PWM_DBCTL_OUT_MODE_S      0U
#define PWM_DBCTL_OUT_MODE_M      0x3U      // Dead Band Output Mode Control
#define PWM_DBCTL_POLSEL_S        2U
#define PWM_DBCTL_POLSEL_M        0xCU      // Polarity Select Control
#define PWM_DBCTL_IN_MODE_S       4U
#define PWM_DBCTL_IN_MODE_M       0x30U     // Dead Band Input Select Mode Control
#define PWM_DBCTL_LOADREDMODE_S   6U
#define PWM_DBCTL_LOADREDMODE_M   0xC0U     // Active DBRED Load Mode
#define PWM_DBCTL_LOADFEDMODE_S   8U
#define PWM_DBCTL_LOADFEDMODE_M   0x300U    // Active DBFED Load Mode
#define PWM_DBCTL_SHDWDBREDMODE   0x400U    // DBRED Block Operating Mode
#define PWM_DBCTL_SHDWDBFEDMODE   0x800U    // DBFED Block Operating Mode
#define PWM_DBCTL_OUTSWAP_S       12U
#define PWM_DBCTL_OUTSWAP_M       0x3000U   // Dead Band Output Swap Control
#define PWM_DBCTL_DEDB_MODE       0x4000U   // Dead Band Dual-Edge B Mode Control
#define PWM_DBCTL_HALFCYCLE       0x8000U   // Half Cycle Clocking Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBCTL2 register
//
//*************************************************************************************************
#define PWM_DBCTL2_LOADDBCTLMODE_S   0U
#define PWM_DBCTL2_LOADDBCTLMODE_M   0x3U   // DBCTL Load from Shadow Mode Select
#define PWM_DBCTL2_SHDWDBCTLMODE     0x4U   // DBCTL Load mode Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTL register
//
//*************************************************************************************************
#define PWM_AQCTL_LDAQAMODE_S   0U
#define PWM_AQCTL_LDAQAMODE_M   0x3U     // Action Qualifier A Load Select
#define PWM_AQCTL_LDAQBMODE_S   2U
#define PWM_AQCTL_LDAQBMODE_M   0xCU     // Action Qualifier B Load Select
#define PWM_AQCTL_SHDWAQAMODE   0x10U    // Action Qualifer A Operating Mode
#define PWM_AQCTL_SHDWAQBMODE   0x40U    // Action Qualifier B Operating Mode
#define PWM_AQCTL_LDAQASYNC_S   8U
#define PWM_AQCTL_LDAQASYNC_M   0x300U   // AQCTLA Register Load on SYNC
#define PWM_AQCTL_LDAQBSYNC_S   10U
#define PWM_AQCTL_LDAQBSYNC_M   0xC00U   // AQCTLB Register Load on SYNC

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQTSRCSEL register
//
//*************************************************************************************************
#define PWM_AQTSRCSEL_T1SEL_S   0U
#define PWM_AQTSRCSEL_T1SEL_M   0xFU    // T1 Event Source Select Bits
#define PWM_AQTSRCSEL_T2SEL_S   4U
#define PWM_AQTSRCSEL_T2SEL_M   0xF0U   // T2 Event Source Select Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCCTL register
//
//*************************************************************************************************
#define PWM_PCCTL_CHPEN       0x1U     // PWM chopping enable
#define PWM_PCCTL_OSHTWTH_S   1U
#define PWM_PCCTL_OSHTWTH_M   0x1EU    // One-shot pulse width
#define PWM_PCCTL_CHPFREQ_S   5U
#define PWM_PCCTL_CHPFREQ_M   0xE0U    // Chopping clock frequency
#define PWM_PCCTL_CHPDUTY_S   8U
#define PWM_PCCTL_CHPDUTY_M   0x700U   // Chopping clock Duty cycle

//*************************************************************************************************
//
// The following are defines for the bit fields in the VCAPCTL register
//
//*************************************************************************************************
#define PWM_VCAPCTL_VCAPE            0x1U     // Valley  Capture mode
#define PWM_VCAPCTL_VCAPSTART        0x2U     // Valley  Capture Start
#define PWM_VCAPCTL_TRIGSEL_S        2U
#define PWM_VCAPCTL_TRIGSEL_M        0x1CU    // Capture Trigger Select
#define PWM_VCAPCTL_VDELAYDIV_S      7U
#define PWM_VCAPCTL_VDELAYDIV_M      0x380U   // Valley Delay Mode Divide Enable
#define PWM_VCAPCTL_EDGEFILTDLYSEL   0x400U   // Valley Switching Mode Delay Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the VCNTCFG register
//
//*************************************************************************************************
#define PWM_VCNTCFG_STARTEDGE_S    0U
#define PWM_VCNTCFG_STARTEDGE_M    0xFU      // Counter Start Edge Selection
#define PWM_VCNTCFG_STARTEDGESTS   0x80U     // Start Edge Status Bit
#define PWM_VCNTCFG_STOPEDGE_S     8U
#define PWM_VCNTCFG_STOPEDGE_M     0xF00U    // Counter Start Edge Selection
#define PWM_VCNTCFG_STOPEDGESTS    0x8000U   // Stop Edge Status Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRCNFG register
//
//*************************************************************************************************
#define PWM_HRCNFG_EDGMODE_S    0U
#define PWM_HRCNFG_EDGMODE_M    0x3U      // PWMxA Edge Mode Select Bits
#define PWM_HRCNFG_CTLMODE      0x4U      // PWMxA Control Mode Select Bits
#define PWM_HRCNFG_HRLOAD_S     3U
#define PWM_HRCNFG_HRLOAD_M     0x18U     // PWMxA Shadow Mode Select Bits
#define PWM_HRCNFG_SELOUTB      0x20U     // PWMB Output Selection Bit
#define PWM_HRCNFG_AUTOCONV     0x40U     // Autoconversion Bit
#define PWM_HRCNFG_SWAPAB       0x80U     // Swap PWMA and PWMB Outputs Bit
#define PWM_HRCNFG_EDGMODEB_S   8U
#define PWM_HRCNFG_EDGMODEB_M   0x300U    // PWMxB Edge Mode Select Bits
#define PWM_HRCNFG_CTLMODEB     0x400U    // PWMxB Control Mode Select Bits
#define PWM_HRCNFG_HRLOADB_S    11U
#define PWM_HRCNFG_HRLOADB_M    0x1800U   // PWMxB Shadow Mode Select Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRPWR register
//
//*************************************************************************************************
#define PWM_HRPWR_CALPWRON   0x8000U   // Calibration Power On

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRMSTEP register
//
//*************************************************************************************************
#define PWM_HRMSTEP_HRMSTEP_S   0U
#define PWM_HRMSTEP_HRMSTEP_M   0xFFU   // High Resolution Micro Step Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRCNFG2 register
//
//*************************************************************************************************
#define PWM_HRCNFG2_EDGMODEDB_S      0U
#define PWM_HRCNFG2_EDGMODEDB_M      0x3U    // Dead-Band Edge-Mode Select Bits
#define PWM_HRCNFG2_CTLMODEDBRED_S   2U
#define PWM_HRCNFG2_CTLMODEDBRED_M   0xCU    // DBRED Control Mode Select Bits
#define PWM_HRCNFG2_CTLMODEDBFED_S   4U
#define PWM_HRCNFG2_CTLMODEDBFED_M   0x30U   // DBFED Control Mode Select Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRPCTL register
//
//*************************************************************************************************
#define PWM_HRPCTL_HRPE            0x1U    // High Resolution Period Enable
#define PWM_HRPCTL_PWMSYNCSEL      0x2U    // PWMSYNCPER Source Select
#define PWM_HRPCTL_TBPHSHRLOADE    0x4U    // TBPHSHR Load Enable
#define PWM_HRPCTL_PWMSYNCSELX_S   4U
#define PWM_HRPCTL_PWMSYNCSELX_M   0x70U   // PWMSYNCPER Extended Source Select Bit:

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRREM register
//
//*************************************************************************************************
#define PWM_TRREM_TRREM_S   0U
#define PWM_TRREM_TRREM_M   0x7FFU   // HRPWM Remainder Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDCTL register
//
//*************************************************************************************************
#define PWM_GLDCTL_GLD         0x1U      // Global Shadow to Active load event control
#define PWM_GLDCTL_GLDMODE_S   1U
#define PWM_GLDCTL_GLDMODE_M   0x1EU     // Shadow to Active Global Load Pulse Selection
#define PWM_GLDCTL_OSHTMODE    0x20U     // One Shot Load mode control bit
#define PWM_GLDCTL_GLDPRD_S    7U
#define PWM_GLDCTL_GLDPRD_M    0x380U    // Global Load Strobe Period Select Register
#define PWM_GLDCTL_GLDCNT_S    10U
#define PWM_GLDCTL_GLDCNT_M    0x1C00U   // Global Load Strobe Counter Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDCFG register
//
//*************************************************************************************************
#define PWM_GLDCFG_TBPRD_TBPRDHR    0x1U     // Global load event configuration for TBPRD:TBPRDHR
#define PWM_GLDCFG_CMPA_CMPAHR      0x2U     // Global load event configuration for CMPA:CMPAHR
#define PWM_GLDCFG_CMPB_CMPBHR      0x4U     // Global load event configuration for CMPB:CMPBHR
#define PWM_GLDCFG_CMPC             0x8U     // Global load event configuration for CMPC
#define PWM_GLDCFG_CMPD             0x10U    // Global load event configuration for CMPD
#define PWM_GLDCFG_DBRED_DBREDHR    0x20U    // Global load event configuration for DBRED:DBREDHR
#define PWM_GLDCFG_DBFED_DBFEDHR    0x40U    // Global load event configuration for DBFED:DBFEDHR
#define PWM_GLDCFG_DBCTL            0x80U    // Global load event configuration for DBCTL
#define PWM_GLDCFG_AQCTLA_AQCTLA2   0x100U   // Global load event configuration for AQCTLA/A2
#define PWM_GLDCFG_AQCTLB_AQCTLB2   0x200U   // Global load event configuration for AQCTLB/B2
#define PWM_GLDCFG_AQCSFRC          0x400U   // Global load event configuration for AQCSFRC

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWMXLINK register
//
//*************************************************************************************************
#define PWM_XLINK_TBPRDLINK_S     0U
#define PWM_XLINK_TBPRDLINK_M     0xFU          // TBPRD:TBPRDHR  Link
#define PWM_XLINK_CMPALINK_S      4U
#define PWM_XLINK_CMPALINK_M      0xF0U         // CMPA:CMPAHR Link
#define PWM_XLINK_CMPBLINK_S      8U
#define PWM_XLINK_CMPBLINK_M      0xF00U        // CMPB:CMPBHR Link
#define PWM_XLINK_CMPCLINK_S      12U
#define PWM_XLINK_CMPCLINK_M      0xF000U       // CMPC Link
#define PWM_XLINK_CMPDLINK_S      16U
#define PWM_XLINK_CMPDLINK_M      0xF0000U      // CMPD Link
#define PWM_XLINK_GLDCTL2LINK_S   28U
#define PWM_XLINK_GLDCTL2LINK_M   0xF0000000U   // GLDCTL2 Link

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTLA register
//
//*************************************************************************************************
#define PWM_AQCTLA_ZRO_S   0U
#define PWM_AQCTLA_ZRO_M   0x3U     // Action Counter = Zero
#define PWM_AQCTLA_PRD_S   2U
#define PWM_AQCTLA_PRD_M   0xCU     // Action Counter = Period
#define PWM_AQCTLA_CAU_S   4U
#define PWM_AQCTLA_CAU_M   0x30U    // Action Counter = Compare A Up
#define PWM_AQCTLA_CAD_S   6U
#define PWM_AQCTLA_CAD_M   0xC0U    // Action Counter = Compare A Down
#define PWM_AQCTLA_CBU_S   8U
#define PWM_AQCTLA_CBU_M   0x300U   // Action Counter = Compare B Up
#define PWM_AQCTLA_CBD_S   10U
#define PWM_AQCTLA_CBD_M   0xC00U   // Action Counter = Compare B Down

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTLA2 register
//
//*************************************************************************************************
#define PWM_AQCTLA2_T1U_S   0U
#define PWM_AQCTLA2_T1U_M   0x3U    // Action when event occurs on T1 in UP-Count
#define PWM_AQCTLA2_T1D_S   2U
#define PWM_AQCTLA2_T1D_M   0xCU    // Action when event occurs on T1 in DOWN-Count
#define PWM_AQCTLA2_T2U_S   4U
#define PWM_AQCTLA2_T2U_M   0x30U   // Action when event occurs on T2 in UP-Count
#define PWM_AQCTLA2_T2D_S   6U
#define PWM_AQCTLA2_T2D_M   0xC0U   // Action when event occurs on T2 in DOWN-Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTLB register
//
//*************************************************************************************************
#define PWM_AQCTLB_ZRO_S   0U
#define PWM_AQCTLB_ZRO_M   0x3U     // Action Counter = Zero
#define PWM_AQCTLB_PRD_S   2U
#define PWM_AQCTLB_PRD_M   0xCU     // Action Counter = Period
#define PWM_AQCTLB_CAU_S   4U
#define PWM_AQCTLB_CAU_M   0x30U    // Action Counter = Compare A Up
#define PWM_AQCTLB_CAD_S   6U
#define PWM_AQCTLB_CAD_M   0xC0U    // Action Counter = Compare A Down
#define PWM_AQCTLB_CBU_S   8U
#define PWM_AQCTLB_CBU_M   0x300U   // Action Counter = Compare B Up
#define PWM_AQCTLB_CBD_S   10U
#define PWM_AQCTLB_CBD_M   0xC00U   // Action Counter = Compare B Down

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTLB2 register
//
//*************************************************************************************************
#define PWM_AQCTLB2_T1U_S   0U
#define PWM_AQCTLB2_T1U_M   0x3U    // Action when event occurs on T1 in UP-Count
#define PWM_AQCTLB2_T1D_S   2U
#define PWM_AQCTLB2_T1D_M   0xCU    // Action when event occurs on T1 in DOWN-Count
#define PWM_AQCTLB2_T2U_S   4U
#define PWM_AQCTLB2_T2U_M   0x30U   // Action when event occurs on T2 in UP-Count
#define PWM_AQCTLB2_T2D_S   6U
#define PWM_AQCTLB2_T2D_M   0xC0U   // Action when event occurs on T2 in DOWN-Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQSFRC register
//
//*************************************************************************************************
#define PWM_AQSFRC_ACTSFA_S   0U
#define PWM_AQSFRC_ACTSFA_M   0x3U    // Action when One-time SW Force A Invoked
#define PWM_AQSFRC_OTSFA      0x4U    // One-time SW Force A Output
#define PWM_AQSFRC_ACTSFB_S   3U
#define PWM_AQSFRC_ACTSFB_M   0x18U   // Action when One-time SW Force B Invoked
#define PWM_AQSFRC_OTSFB      0x20U   // One-time SW Force A Output
#define PWM_AQSFRC_RLDCSF_S   6U
#define PWM_AQSFRC_RLDCSF_M   0xC0U   // Reload from Shadow Options

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCSFRC register
//
//*************************************************************************************************
#define PWM_AQCSFRC_CSFA_S   0U
#define PWM_AQCSFRC_CSFA_M   0x3U   // Continuous Software Force on output A
#define PWM_AQCSFRC_CSFB_S   2U
#define PWM_AQCSFRC_CSFB_M   0xCU   // Continuous Software Force on output B

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBREDHR register
//
//*************************************************************************************************
#define PWM_DBREDHR_DBREDHR_S   9U
#define PWM_DBREDHR_DBREDHR_M   0xFE00U   // DBREDHR High Resolution Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBRED register
//
//*************************************************************************************************
#define PWM_DBRED_DBRED_S   0U
#define PWM_DBRED_DBRED_M   0x3FFFU   // Rising edge delay value

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBFEDHR register
//
//*************************************************************************************************
#define PWM_DBFEDHR_DBFEDHR_S   9U
#define PWM_DBFEDHR_DBFEDHR_M   0xFE00U   // DBFEDHR High Resolution Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBFED register
//
//*************************************************************************************************
#define PWM_DBFED_DBFED_S   0U
#define PWM_DBFED_DBFED_M   0x3FFFU   // Falling edge delay value

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBPHS register
//
//*************************************************************************************************
#define PWM_TBPHS_TBPHSHR_S   0U
#define PWM_TBPHS_TBPHSHR_M   0xFFFFU       // Extension Register for HRPWM Phase (8-bits)
#define PWM_TBPHS_TBPHS_S     16U
#define PWM_TBPHS_TBPHS_M     0xFFFF0000U   // Phase Offset Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPA register
//
//*************************************************************************************************
#define PWM_CMPA_CMPAHR_S   0U
#define PWM_CMPA_CMPAHR_M   0xFFFFU       // Compare A HRPWM Extension Register
#define PWM_CMPA_CMPA_S     16U
#define PWM_CMPA_CMPA_M     0xFFFF0000U   // Compare A Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPB register
//
//*************************************************************************************************
#define PWM_CMPB_CMPBHR_S   0U
#define PWM_CMPB_CMPBHR_M   0xFFFFU       // Compare B High Resolution Bits
#define PWM_CMPB_CMPB_S     16U
#define PWM_CMPB_CMPB_M     0xFFFF0000U   // Compare B Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDCTL2 register
//
//*************************************************************************************************
#define PWM_GLDCTL2_OSHTLD   0x1U   // Enable reload event in one shot mode
#define PWM_GLDCTL2_GFRCLD   0x2U   // Force reload event in one shot mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZSEL register
//
//*************************************************************************************************
#define PWM_TZSEL_CBC1      0x1U      // TZ1 CBC select
#define PWM_TZSEL_CBC2      0x2U      // TZ2 CBC select
#define PWM_TZSEL_CBC3      0x4U      // TZ3 CBC select
#define PWM_TZSEL_CBC4      0x8U      // TZ4 CBC select
#define PWM_TZSEL_CBC5      0x10U     // TZ5 CBC select
#define PWM_TZSEL_CBC6      0x20U     // TZ6 CBC select
#define PWM_TZSEL_DCAEVT2   0x40U     // DCAEVT2 CBC select
#define PWM_TZSEL_DCBEVT2   0x80U     // DCBEVT2 CBC select
#define PWM_TZSEL_OSHT1     0x100U    // One-shot TZ1 select
#define PWM_TZSEL_OSHT2     0x200U    // One-shot TZ2 select
#define PWM_TZSEL_OSHT3     0x400U    // One-shot TZ3 select
#define PWM_TZSEL_OSHT4     0x800U    // One-shot TZ4 select
#define PWM_TZSEL_OSHT5     0x1000U   // One-shot TZ5 select
#define PWM_TZSEL_OSHT6     0x2000U   // One-shot TZ6 select
#define PWM_TZSEL_DCAEVT1   0x4000U   // One-shot DCAEVT1 select
#define PWM_TZSEL_DCBEVT1   0x8000U   // One-shot DCBEVT1 select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZDCSEL register
//
//*************************************************************************************************
#define PWM_TZDCSEL_DCAEVT1_S   0U
#define PWM_TZDCSEL_DCAEVT1_M   0x7U     // Digital Compare Output A Event 1
#define PWM_TZDCSEL_DCAEVT2_S   3U
#define PWM_TZDCSEL_DCAEVT2_M   0x38U    // Digital Compare Output A Event 2
#define PWM_TZDCSEL_DCBEVT1_S   6U
#define PWM_TZDCSEL_DCBEVT1_M   0x1C0U   // Digital Compare Output B Event 1
#define PWM_TZDCSEL_DCBEVT2_S   9U
#define PWM_TZDCSEL_DCBEVT2_M   0xE00U   // Digital Compare Output B Event 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTL register
//
//*************************************************************************************************
#define PWM_TZCTL_TZA_S       0U
#define PWM_TZCTL_TZA_M       0x3U     // TZ1 to TZ6 Trip Action On PWMxA
#define PWM_TZCTL_TZB_S       2U
#define PWM_TZCTL_TZB_M       0xCU     // TZ1 to TZ6 Trip Action On PWMxB
#define PWM_TZCTL_DCAEVT1_S   4U
#define PWM_TZCTL_DCAEVT1_M   0x30U    // PWMxA action on DCAEVT1
#define PWM_TZCTL_DCAEVT2_S   6U
#define PWM_TZCTL_DCAEVT2_M   0xC0U    // PWMxA action on DCAEVT2
#define PWM_TZCTL_DCBEVT1_S   8U
#define PWM_TZCTL_DCBEVT1_M   0x300U   // PWMxB action on DCBEVT1
#define PWM_TZCTL_DCBEVT2_S   10U
#define PWM_TZCTL_DCBEVT2_M   0xC00U   // PWMxB action on DCBEVT2

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTL2 register
//
//*************************************************************************************************
#define PWM_TZCTL2_TZAU_S   0U
#define PWM_TZCTL2_TZAU_M   0x7U      // Trip Action On PWMxA while Count direction is UP
#define PWM_TZCTL2_TZAD_S   3U
#define PWM_TZCTL2_TZAD_M   0x38U     // Trip Action On PWMxA while Count direction is DOWN
#define PWM_TZCTL2_TZBU_S   6U
#define PWM_TZCTL2_TZBU_M   0x1C0U    // Trip Action On PWMxB while Count direction is UP
#define PWM_TZCTL2_TZBD_S   9U
#define PWM_TZCTL2_TZBD_M   0xE00U    // Trip Action On PWMxB while Count direction is DOWN
#define PWM_TZCTL2_ETZE     0x8000U   // TZCTL2 Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTLDCA register
//
//*************************************************************************************************
#define PWM_TZCTLDCA_DCAEVT1U_S   0U
#define PWM_TZCTLDCA_DCAEVT1U_M   0x7U     // DCAEVT1 Action On PWMxA while Count direction is UP
#define PWM_TZCTLDCA_DCAEVT1D_S   3U
#define PWM_TZCTLDCA_DCAEVT1D_M   0x38U    // DCAEVT1 Action On PWMxA while Count direction is
                                            // DOWN
#define PWM_TZCTLDCA_DCAEVT2U_S   6U
#define PWM_TZCTLDCA_DCAEVT2U_M   0x1C0U   // DCAEVT2 Action On PWMxA while Count direction is UP
#define PWM_TZCTLDCA_DCAEVT2D_S   9U
#define PWM_TZCTLDCA_DCAEVT2D_M   0xE00U   // DCAEVT2 Action On PWMxA while Count direction is
                                            // DOWN

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTLDCB register
//
//*************************************************************************************************
#define PWM_TZCTLDCB_DCBEVT1U_S   0U
#define PWM_TZCTLDCB_DCBEVT1U_M   0x7U     // DCBEVT1 Action On PWMxA while Count direction is UP
#define PWM_TZCTLDCB_DCBEVT1D_S   3U
#define PWM_TZCTLDCB_DCBEVT1D_M   0x38U    // DCBEVT1 Action On PWMxA while Count direction is
                                            // DOWN
#define PWM_TZCTLDCB_DCBEVT2U_S   6U
#define PWM_TZCTLDCB_DCBEVT2U_M   0x1C0U   // DCBEVT2 Action On PWMxA while Count direction is UP
#define PWM_TZCTLDCB_DCBEVT2D_S   9U
#define PWM_TZCTLDCB_DCBEVT2D_M   0xE00U   // DCBEVT2 Action On PWMxA while Count direction is
                                            // DOWN

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZEINT register
//
//*************************************************************************************************
#define PWM_TZEINT_CBC       0x2U    // Trip Zones Cycle By Cycle Int Enable
#define PWM_TZEINT_OST       0x4U    // Trip Zones One Shot Int Enable
#define PWM_TZEINT_DCAEVT1   0x8U    // Digital Compare A Event 1 Int Enable
#define PWM_TZEINT_DCAEVT2   0x10U   // Digital Compare A Event 2 Int Enable
#define PWM_TZEINT_DCBEVT1   0x20U   // Digital Compare B Event 1 Int Enable
#define PWM_TZEINT_DCBEVT2   0x40U   // Digital Compare B Event 2 Int Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZFLG register
//
//*************************************************************************************************
#define PWM_TZFLG_INT       0x1U    // Global Int Status Flag
#define PWM_TZFLG_CBC       0x2U    // Trip Zones Cycle By Cycle Flag
#define PWM_TZFLG_OST       0x4U    // Trip Zones One Shot Flag
#define PWM_TZFLG_DCAEVT1   0x8U    // Digital Compare A Event 1 Flag
#define PWM_TZFLG_DCAEVT2   0x10U   // Digital Compare A Event 2 Flag
#define PWM_TZFLG_DCBEVT1   0x20U   // Digital Compare B Event 1 Flag
#define PWM_TZFLG_DCBEVT2   0x40U   // Digital Compare B Event 2 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCBCFLG register
//
//*************************************************************************************************
#define PWM_TZCBCFLG_CBC1      0x1U    // Latched Status Flag for CBC1 Trip Latch
#define PWM_TZCBCFLG_CBC2      0x2U    // Latched Status Flag for CBC2 Trip Latch
#define PWM_TZCBCFLG_CBC3      0x4U    // Latched Status Flag for CBC3 Trip Latch
#define PWM_TZCBCFLG_CBC4      0x8U    // Latched Status Flag for CBC4 Trip Latch
#define PWM_TZCBCFLG_CBC5      0x10U   // Latched Status Flag for CBC5 Trip Latch
#define PWM_TZCBCFLG_CBC6      0x20U   // Latched Status Flag for CBC6 Trip Latch
#define PWM_TZCBCFLG_DCAEVT2   0x40U   // Latched Status Flag for Digital Compare Output A Event 2
#define PWM_TZCBCFLG_DCBEVT2   0x80U   // Latched Status Flag for Digital Compare Output B Event 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZOSTFLG register
//
//*************************************************************************************************
#define PWM_TZOSTFLG_OST1      0x1U    // Latched Status Flag for OST1 Trip Latch
#define PWM_TZOSTFLG_OST2      0x2U    // Latched Status Flag for OST2 Trip Latch
#define PWM_TZOSTFLG_OST3      0x4U    // Latched Status Flag for OST3 Trip Latch
#define PWM_TZOSTFLG_OST4      0x8U    // Latched Status Flag for OST4 Trip Latch
#define PWM_TZOSTFLG_OST5      0x10U   // Latched Status Flag for OST5 Trip Latch
#define PWM_TZOSTFLG_OST6      0x20U   // Latched Status Flag for OST6 Trip Latch
#define PWM_TZOSTFLG_DCAEVT1   0x40U   // Latched Status Flag for Digital Compare Output A Event 1
#define PWM_TZOSTFLG_DCBEVT1   0x80U   // Latched Status Flag for Digital Compare Output B Event 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCLR register
//
//*************************************************************************************************
#define PWM_TZCLR_INT          0x1U      // Global Interrupt Clear Flag
#define PWM_TZCLR_CBC          0x2U      // Cycle-By-Cycle Flag Clear
#define PWM_TZCLR_OST          0x4U      // One-Shot Flag Clear
#define PWM_TZCLR_DCAEVT1      0x8U      // DCAVET1 Flag Clear
#define PWM_TZCLR_DCAEVT2      0x10U     // DCAEVT2 Flag Clear
#define PWM_TZCLR_DCBEVT1      0x20U     // DCBEVT1 Flag Clear
#define PWM_TZCLR_DCBEVT2      0x40U     // DCBEVT2 Flag Clear
#define PWM_TZCLR_CBCPULSE_S   14U
#define PWM_TZCLR_CBCPULSE_M   0xC000U   // Clear Pulse for CBC Trip Latch

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCBCCLR register
//
//*************************************************************************************************
#define PWM_TZCBCCLR_CBC1      0x1U    // Clear Flag for Cycle-By-Cycle (CBC1) Trip Latch
#define PWM_TZCBCCLR_CBC2      0x2U    // Clear Flag for Cycle-By-Cycle (CBC2) Trip Latch
#define PWM_TZCBCCLR_CBC3      0x4U    // Clear Flag for Cycle-By-Cycle (CBC3) Trip Latch
#define PWM_TZCBCCLR_CBC4      0x8U    // Clear Flag for Cycle-By-Cycle (CBC4) Trip Latch
#define PWM_TZCBCCLR_CBC5      0x10U   // Clear Flag for Cycle-By-Cycle (CBC5) Trip Latch
#define PWM_TZCBCCLR_CBC6      0x20U   // Clear Flag for Cycle-By-Cycle (CBC6) Trip Latch
#define PWM_TZCBCCLR_DCAEVT2   0x40U   // Clear Flag forDCAEVT2 selected for CBC
#define PWM_TZCBCCLR_DCBEVT2   0x80U   // Clear Flag for DCBEVT2 selected for CBC

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZOSTCLR register
//
//*************************************************************************************************
#define PWM_TZOSTCLR_OST1      0x1U    // Clear Flag for Oneshot (OST1) Trip Latch
#define PWM_TZOSTCLR_OST2      0x2U    // Clear Flag for Oneshot (OST2) Trip Latch
#define PWM_TZOSTCLR_OST3      0x4U    // Clear Flag for Oneshot (OST3) Trip Latch
#define PWM_TZOSTCLR_OST4      0x8U    // Clear Flag for Oneshot (OST4) Trip Latch
#define PWM_TZOSTCLR_OST5      0x10U   // Clear Flag for Oneshot (OST5) Trip Latch
#define PWM_TZOSTCLR_OST6      0x20U   // Clear Flag for Oneshot (OST6) Trip Latch
#define PWM_TZOSTCLR_DCAEVT1   0x40U   // Clear Flag for DCAEVT1 selected for OST
#define PWM_TZOSTCLR_DCBEVT1   0x80U   // Clear Flag for DCBEVT1 selected for OST

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZFRC register
//
//*************************************************************************************************
#define PWM_TZFRC_CBC       0x2U    // Force Trip Zones Cycle By Cycle Event
#define PWM_TZFRC_OST       0x4U    // Force Trip Zones One Shot Event
#define PWM_TZFRC_DCAEVT1   0x8U    // Force Digital Compare A Event 1
#define PWM_TZFRC_DCAEVT2   0x10U   // Force Digital Compare A Event 2
#define PWM_TZFRC_DCBEVT1   0x20U   // Force Digital Compare B Event 1
#define PWM_TZFRC_DCBEVT2   0x40U   // Force Digital Compare B Event 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETSEL register
//
//*************************************************************************************************
#define PWM_ETSEL_INTSEL_S     0U
#define PWM_ETSEL_INTSEL_M     0x7U      // PWMxINTn Select
#define PWM_ETSEL_INTEN        0x8U      // PWMxINTn Enable
#define PWM_ETSEL_SOCASELCMP   0x10U     // PWMxSOCA Compare Select
#define PWM_ETSEL_SOCBSELCMP   0x20U     // PWMxSOCB Compare Select
#define PWM_ETSEL_INTSELCMP    0x40U     // PWMxINT Compare Select
#define PWM_ETSEL_SOCASEL_S    8U
#define PWM_ETSEL_SOCASEL_M    0x700U    // Start of Conversion A Select
#define PWM_ETSEL_SOCAEN       0x800U    // Start of Conversion A Enable
#define PWM_ETSEL_SOCBSEL_S    12U
#define PWM_ETSEL_SOCBSEL_M    0x7000U   // Start of Conversion B Select
#define PWM_ETSEL_SOCBEN       0x8000U   // Start of Conversion B Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETPS register
//
//*************************************************************************************************
#define PWM_ETPS_INTPRD_S    0U
#define PWM_ETPS_INTPRD_M    0x3U      // PWMxINTn Period Select
#define PWM_ETPS_INTCNT_S    2U
#define PWM_ETPS_INTCNT_M    0xCU      // PWMxINTn Counter Register
#define PWM_ETPS_INTPSSEL    0x10U     // PWMxINTn Pre-Scale Selection Bits
#define PWM_ETPS_SOCPSSEL    0x20U     // PWMxSOC A/B  Pre-Scale Selection Bits
#define PWM_ETPS_SOCAPRD_S   8U
#define PWM_ETPS_SOCAPRD_M   0x300U    // PWMxSOCA Period Select
#define PWM_ETPS_SOCACNT_S   10U
#define PWM_ETPS_SOCACNT_M   0xC00U    // PWMxSOCA Counter Register
#define PWM_ETPS_SOCBPRD_S   12U
#define PWM_ETPS_SOCBPRD_M   0x3000U   // PWMxSOCB Period Select
#define PWM_ETPS_SOCBCNT_S   14U
#define PWM_ETPS_SOCBCNT_M   0xC000U   // PWMxSOCB Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETFLG register
//
//*************************************************************************************************
#define PWM_ETFLG_INT    0x1U   // PWMxINTn Flag
#define PWM_ETFLG_SOCA   0x4U   // PWMxSOCA Flag
#define PWM_ETFLG_SOCB   0x8U   // PWMxSOCB Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETCLR register
//
//*************************************************************************************************
#define PWM_ETCLR_INT    0x1U   // PWMxINTn Clear
#define PWM_ETCLR_SOCA   0x4U   // PWMxSOCA Clear
#define PWM_ETCLR_SOCB   0x8U   // PWMxSOCB Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETFRC register
//
//*************************************************************************************************
#define PWM_ETFRC_INT    0x1U   // PWMxINTn Force
#define PWM_ETFRC_SOCA   0x4U   // PWMxSOCA Force
#define PWM_ETFRC_SOCB   0x8U   // PWMxSOCB Force

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETINTPS register
//
//*************************************************************************************************
#define PWM_ETINTPS_INTPRD2_S   0U
#define PWM_ETINTPS_INTPRD2_M   0xFU    // PWMxINTn Period Select
#define PWM_ETINTPS_INTCNT2_S   4U
#define PWM_ETINTPS_INTCNT2_M   0xF0U   // PWMxINTn Counter Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETSOCPS register
//
//*************************************************************************************************
#define PWM_ETSOCPS_SOCAPRD2_S   0U
#define PWM_ETSOCPS_SOCAPRD2_M   0xFU      // PWMxSOCA Period Select
#define PWM_ETSOCPS_SOCACNT2_S   4U
#define PWM_ETSOCPS_SOCACNT2_M   0xF0U     // PWMxSOCA Counter Register
#define PWM_ETSOCPS_SOCBPRD2_S   8U
#define PWM_ETSOCPS_SOCBPRD2_M   0xF00U    // PWMxSOCB Period Select
#define PWM_ETSOCPS_SOCBCNT2_S   12U
#define PWM_ETSOCPS_SOCBCNT2_M   0xF000U   // PWMxSOCB Counter Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETCNTINITCTL register
//
//*************************************************************************************************
#define PWM_ETCNTINITCTL_INTINITFRC    0x400U    // PWMxINT Counter Initialization Force
#define PWM_ETCNTINITCTL_SOCAINITFRC   0x800U    // PWMxSOCA Counter Initialization Force
#define PWM_ETCNTINITCTL_SOCBINITFRC   0x1000U   // PWMxSOCB Counter Initialization Force
#define PWM_ETCNTINITCTL_INTINITEN     0x2000U   // PWMxINT Counter Initialization Enable
#define PWM_ETCNTINITCTL_SOCAINITEN    0x4000U   // PWMxSOCA Counter Initialization Enable
#define PWM_ETCNTINITCTL_SOCBINITEN    0x8000U   // PWMxSOCB Counter Initialization Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETCNTINIT register
//
//*************************************************************************************************
#define PWM_ETCNTINIT_INTINIT_S    0U
#define PWM_ETCNTINIT_INTINIT_M    0xFU     // PWMxINT Counter Initialization Bits
#define PWM_ETCNTINIT_SOCAINIT_S   4U
#define PWM_ETCNTINIT_SOCAINIT_M   0xF0U    // PWMxSOCA Counter Initialization Bits
#define PWM_ETCNTINIT_SOCBINIT_S   8U
#define PWM_ETCNTINIT_SOCBINIT_M   0xF00U   // PWMxSOCB Counter Initialization Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCTRIPSEL register
//
//*************************************************************************************************
#define PWM_DCTRIPSEL_DCAHCOMPSEL_S   0U
#define PWM_DCTRIPSEL_DCAHCOMPSEL_M   0xFU      // Digital Compare A High COMP Input Select
#define PWM_DCTRIPSEL_DCALCOMPSEL_S   4U
#define PWM_DCTRIPSEL_DCALCOMPSEL_M   0xF0U     // Digital Compare A Low COMP Input Select
#define PWM_DCTRIPSEL_DCBHCOMPSEL_S   8U
#define PWM_DCTRIPSEL_DCBHCOMPSEL_M   0xF00U    // Digital Compare B High COMP Input Select
#define PWM_DCTRIPSEL_DCBLCOMPSEL_S   12U
#define PWM_DCTRIPSEL_DCBLCOMPSEL_M   0xF000U   // Digital Compare B Low COMP Input Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCACTL register
//
//*************************************************************************************************
#define PWM_DCACTL_EVT1SRCSEL       0x1U     // DCAEVT1 Source Signal
#define PWM_DCACTL_EVT1FRCSYNCSEL   0x2U     // DCAEVT1 Force Sync Signal
#define PWM_DCACTL_EVT1SOCE         0x4U     // DCAEVT1 SOC Enable
#define PWM_DCACTL_EVT1SYNCE        0x8U     // DCAEVT1 SYNC Enable
#define PWM_DCACTL_EVT2SRCSEL       0x100U   // DCAEVT2 Source Signal
#define PWM_DCACTL_EVT2FRCSYNCSEL   0x200U   // DCAEVT2 Force Sync Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCBCTL register
//
//*************************************************************************************************
#define PWM_DCBCTL_EVT1SRCSEL       0x1U     // DCBEVT1 Source Signal
#define PWM_DCBCTL_EVT1FRCSYNCSEL   0x2U     // DCBEVT1 Force Sync Signal
#define PWM_DCBCTL_EVT1SOCE         0x4U     // DCBEVT1 SOC Enable
#define PWM_DCBCTL_EVT1SYNCE        0x8U     // DCBEVT1 SYNC Enable
#define PWM_DCBCTL_EVT2SRCSEL       0x100U   // DCBEVT2 Source Signal
#define PWM_DCBCTL_EVT2FRCSYNCSEL   0x200U   // DCBEVT2 Force Sync Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCFCTL register
//
//*************************************************************************************************
#define PWM_DCFCTL_SRCSEL_S       0U
#define PWM_DCFCTL_SRCSEL_M       0x3U      // Filter Block Signal Source Select
#define PWM_DCFCTL_BLANKE         0x4U      // Blanking Enable/Disable
#define PWM_DCFCTL_BLANKINV       0x8U      // Blanking Window Inversion
#define PWM_DCFCTL_PULSESEL_S     4U
#define PWM_DCFCTL_PULSESEL_M     0x30U     // Pulse Select for Blanking & Capture Alignment
#define PWM_DCFCTL_EDGEFILTSEL    0x40U     // Edge Filter Select
#define PWM_DCFCTL_EDGEMODE_S     8U
#define PWM_DCFCTL_EDGEMODE_M     0x300U    // Edge Mode
#define PWM_DCFCTL_EDGECOUNT_S    10U
#define PWM_DCFCTL_EDGECOUNT_M    0x1C00U   // Edge Count
#define PWM_DCFCTL_EDGESTATUS_S   13U
#define PWM_DCFCTL_EDGESTATUS_M   0xE000U   // Edge Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCAPCTL register
//
//*************************************************************************************************
#define PWM_DCCAPCTL_CAPE       0x1U      // Counter Capture Enable
#define PWM_DCCAPCTL_SHDWMODE   0x2U      // Counter Capture Mode
#define PWM_DCCAPCTL_CAPSTS     0x2000U   // Latched Status Flag for Capture Event
#define PWM_DCCAPCTL_CAPCLR     0x4000U   // DC Capture Latched Status Clear Flag
#define PWM_DCCAPCTL_CAPMODE    0x8000U   // Counter Capture Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCAHTRIPSEL register
//
//*************************************************************************************************
#define PWM_DCAHTRIPSEL_TRIPINPUT1    0x1U      // Trip Input 1 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT2    0x2U      // Trip Input 2 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT3    0x4U      // Trip Input 3 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT4    0x8U      // Trip Input 4 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT5    0x10U     // Trip Input 5 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT6    0x20U     // Trip Input 6 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT7    0x40U     // Trip Input 7 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT8    0x80U     // Trip Input 8 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT9    0x100U    // Trip Input 9 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT10   0x200U    // Trip Input 10 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT11   0x400U    // Trip Input 11 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT12   0x800U    // Trip Input 12 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT14   0x2000U   // Trip Input 14 Select to DCAH Mux
#define PWM_DCAHTRIPSEL_TRIPINPUT15   0x4000U   // Trip Input 15 Select to DCAH Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCALTRIPSEL register
//
//*************************************************************************************************
#define PWM_DCALTRIPSEL_TRIPINPUT1    0x1U      // Trip Input 1 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT2    0x2U      // Trip Input 2 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT3    0x4U      // Trip Input 3 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT4    0x8U      // Trip Input 4 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT5    0x10U     // Trip Input 5 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT6    0x20U     // Trip Input 6 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT7    0x40U     // Trip Input 7 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT8    0x80U     // Trip Input 8 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT9    0x100U    // Trip Input 9 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT10   0x200U    // Trip Input 10 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT11   0x400U    // Trip Input 11 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT12   0x800U    // Trip Input 12 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT14   0x2000U   // Trip Input 14 Select to DCAL Mux
#define PWM_DCALTRIPSEL_TRIPINPUT15   0x4000U   // Trip Input 15 Select to DCAL Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCBHTRIPSEL register
//
//*************************************************************************************************
#define PWM_DCBHTRIPSEL_TRIPINPUT1    0x1U      // Trip Input 1 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT2    0x2U      // Trip Input 2 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT3    0x4U      // Trip Input 3 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT4    0x8U      // Trip Input 4 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT5    0x10U     // Trip Input 5 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT6    0x20U     // Trip Input 6 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT7    0x40U     // Trip Input 7 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT8    0x80U     // Trip Input 8 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT9    0x100U    // Trip Input 9 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT10   0x200U    // Trip Input 10 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT11   0x400U    // Trip Input 11 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT12   0x800U    // Trip Input 12 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT14   0x2000U   // Trip Input 14 Select to DCBH Mux
#define PWM_DCBHTRIPSEL_TRIPINPUT15   0x4000U   // Trip Input 15 Select to DCBH Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCBLTRIPSEL register
//
//*************************************************************************************************
#define PWM_DCBLTRIPSEL_TRIPINPUT1    0x1U      // Trip Input 1 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT2    0x2U      // Trip Input 2 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT3    0x4U      // Trip Input 3 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT4    0x8U      // Trip Input 4 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT5    0x10U     // Trip Input 5 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT6    0x20U     // Trip Input 6 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT7    0x40U     // Trip Input 7 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT8    0x80U     // Trip Input 8 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT9    0x100U    // Trip Input 9 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT10   0x200U    // Trip Input 10 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT11   0x400U    // Trip Input 11 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT12   0x800U    // Trip Input 12 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT14   0x2000U   // Trip Input 14 Select to DCBL Mux
#define PWM_DCBLTRIPSEL_TRIPINPUT15   0x4000U   // Trip Input 15 Select to DCBL Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWMLOCK register
//
//*************************************************************************************************
#define PWM_LOCK_HRLOCK      0x1U          // HRPWM Register Set Lock
#define PWM_LOCK_GLLOCK      0x2U          // Global Load Register Set Lock
#define PWM_LOCK_TZCFGLOCK   0x4U          // TripZone Register Set Lock
#define PWM_LOCK_TZCLRLOCK   0x8U          // TripZone Clear Register Set Lock
#define PWM_LOCK_DCLOCK      0x10U         // Digital Compare Register Set Lock
#define PWM_LOCK_KEY_S       16U
#define PWM_LOCK_KEY_M       0xFFFF0000U   // Key to write to this register



#endif
