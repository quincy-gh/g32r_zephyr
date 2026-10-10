//###########################################################################
//
// FILE:    hw_hrpwm.h
//
// TITLE:   Definitions for the HRPWM registers.
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

#ifndef HW_HRPWM_H
#define HW_HRPWM_H

//*************************************************************************************************
//
// The following are defines for the HRPWM register offsets
//
//*************************************************************************************************
#define HRPWM_O_TBCTRL         (0x0*2U)    // Time Base Control Register
#define HRPWM_O_TBCTRL2        (0x1*2U)    // Time Base Control Register 2
#define HRPWM_O_TBCTR          (0x4*2U)    // Time Base Counter Register
#define HRPWM_O_TBSTS          (0x5*2U)    // Time Base Status Register
#define HRPWM_O_CCOMPCTRL      (0x8*2U)    // Counter Compare Control Register
#define HRPWM_O_CCOMPCTRL2     (0x9*2U)    // Counter Compare Control Register 2
#define HRPWM_O_DBCTRL         (0xC*2U)    // Dead-Band Generator Control Register
#define HRPWM_O_DBCTRL2        (0xD*2U)    // Dead-Band Generator Control Register 2
#define HRPWM_O_AQCTRL         (0x10*2U)   // Action Qualifier Control Register
#define HRPWM_O_AQTESRCSEL     (0x11*2U)   // Action Qualifier Trigger Event Source Select Register
#define HRPWM_O_CPCTRL         (0x14*2U)   // PWM Chopper Control Register
#define HRPWM_O_VCAPCTRL       (0x18*2U)   // Valley Capture Control Register
#define HRPWM_O_VCNTCFG        (0x19*2U)   // Valley Counter Config Register
#define HRPWM_O_HRPCFG         (0x20*2U)   // HRPWM Configuration Register
#define HRPWM_O_HRPWM          (0x21*2U)   // HRPWM Power Register
#define HRPWM_O_HRMSTEP        (0x26*2U)   // HRPWM MEP Step Register
#define HRPWM_O_HRCFG2         (0x27*2U)   // HRPWM Configuration 2 Register
#define HRPWM_O_HRPRDCTRL      (0x2D*2U)   // High Resolution Period Control Register
#define HRPWM_O_THRR           (0x2E*2U)   // HRPWM High Resolution Remainder Register
#define HRPWM_O_GLDCTRL        (0x34*2U)   // Global PWM Load Control Register
#define HRPWM_O_GLDECFG        (0x35*2U)   // Global PWM Load Config Register
#define HRPWM_O_LINK           (0x38*2U)   // PWMx Link Register
#define HRPWM_O_AQCTRLA        (0x40*2U)   // Action Qualifier Control Register For Output A
#define HRPWM_O_ADDAQCTRLA2    (0x41*2U)   // Additional Action Qualifier Control Register For Output A
#define HRPWM_O_AQCTRLB        (0x42*2U)   // Action Qualifier Control Register For Output B
#define HRPWM_O_ADDAQCTRLB2    (0x43*2U)   // Additional Action Qualifier Control Register For Output B
#define HRPWM_O_AQSWF          (0x47*2U)   // Action Qualifier Software Force Register
#define HRPWM_O_AQCSWF         (0x49*2U)   // Action Qualifier Continuous S/W Force Register
#define HRPWM_O_DBREDHRM       (0x50*2U)   // Dead-Band Generator Rising Edge Delay High Resolution
                                       // Mirror Register
#define HRPWM_O_DBRED          (0x51*2U)   // Dead-Band Generator Rising Edge Delay High Resolution
                                       // Mirror Register
#define HRPWM_O_DBFEDHRM       (0x52*2U)   // Dead-Band Generator Falling Edge Delay High Resolution
                                       // Register
#define HRPWM_O_DBFED          (0x53*2U)   // Dead-Band Generator Falling Edge Delay Count Register
#define HRPWM_O_TBPOF          (0x60*2U)   // Time Base Phase High
#define HRPWM_O_TBPRDHR        (0x62*2U)   // Time Base Period High Resolution Register
#define HRPWM_O_TBPRD          (0x63*2U)   // Time Base Period Register
#define HRPWM_O_CCOMPA         (0x6A*2U)   // Counter Compare A Register
#define HRPWM_O_CCOMPB         (0x6C*2U)   // Compare B Register
#define HRPWM_O_CMPC           (0x6F*2U)   // Counter Compare C Register
#define HRPWM_O_CMPD           (0x71*2U)   // Counter Compare D Register
#define HRPWM_O_GLDCTRL2       (0x74*2U)   // Global PWM Load Control Register 2
#define HRPWM_O_SWVDELVAL      (0x77*2U)   // Software Valley Mode Delay Register
#define HRPWM_O_TZSEL          (0x80*2U)   // Trip Zone Select Register
#define HRPWM_O_TZDCCFG        (0x82*2U)   // Trip Zone Digital Comparator Select Register
#define HRPWM_O_TZCTRL         (0x84*2U)   // Trip Zone Control Register
#define HRPWM_O_TZCTRL2        (0x85*2U)   // Additional Trip Zone Control Register
#define HRPWM_O_TZCTRLDCA      (0x86*2U)   // Trip Zone Control Register Digital Compare A
#define HRPWM_O_TZCTRLDCB      (0x87*2U)   // Trip Zone Control Register Digital Compare B
#define HRPWM_O_TZINTEN        (0x8D*2U)   // Trip Zone Enable Interrupt Register
#define HRPWM_O_TZFLG          (0x93*2U)   // Trip Zone Flag Register
#define HRPWM_O_TZCCTFLG       (0x94*2U)   // Trip Zone CBC Flag Register
#define HRPWM_O_TZOSTFLG       (0x95*2U)   // Trip Zone OST Flag Register
#define HRPWM_O_TZCLR          (0x97*2U)   // Trip Zone Clear Register
#define HRPWM_O_TZCCTCLR       (0x98*2U)   // Trip Zone CBC Clear Register
#define HRPWM_O_TZCOSTCLR      (0x99*2U)   // Trip Zone OST Clear Register
#define HRPWM_O_TZF            (0x9B*2U)   // Trip Zone Force Register
#define HRPWM_O_ETRSEL         (0xA4*2U)   // Event Trigger Selection Register
#define HRPWM_O_ETRPSC         (0xA6*2U)   // Event Trigger Pre-Scale Register
#define HRPWM_O_ETRFLG         (0xA8*2U)   // Event Trigger Flag Register
#define HRPWM_O_ETRCLR         (0xAA*2U)   // Event Trigger Clear Register
#define HRPWM_O_ETRF           (0xAC*2U)   // Event Trigger Force Register
#define HRPWM_O_ETRINTPSC      (0xAE*2U)   // Event-Trigger Interrupt Pre-Scale Register
#define HRPWM_O_ETRSOCPSC      (0xB0*2U)   // Event-Trigger SOC Pre-Scale Register
#define HRPWM_O_ETRCNTICTRL    (0xB2*2U)   // Event-Trigger Counter Initialization Control Register
#define HRPWM_O_ETRCNTI        (0xB4*2U)   // Event-Trigger Counter Initialization Register
#define HRPWM_O_DCTSEL         (0xC0*2U)   // Digital Compare Trip Select Register
#define HRPWM_O_DCACTRL        (0xC3*2U)   // Digital Compare A Control Register
#define HRPWM_O_DCBCTRL        (0xC4*2U)   // Digital Compare B Control Register
#define HRPWM_O_DCFCTRL        (0xC7*2U)   // Digital Compare Filter Control Register
#define HRPWM_O_DCCAPCTL       (0xC8*2U)   // Digital Compare Capture Control Register
#define HRPWM_O_DCFOFFSET      (0xC9*2U)   // Digital Compare Filter Offset Register
#define HRPWM_O_DCFOFFSETCNT   (0xCA*2U)   // Digital Compare Filter Offset Counter Register
#define HRPWM_O_DCFWINDOW      (0xCB*2U)   // Digital Compare Filter Window Register
#define HRPWM_O_DCFWINDOWCNT   (0xCC*2U)   // Digital Compare Filter Window Counter Register
#define HRPWM_O_DCCAP          (0xCF*2U)   // Digital Compare Counter Capture Register
#define HRPWM_O_DCAHTSEL       (0xD2*2U)   // Digital Compare AH Trip Select
#define HRPWM_O_DCALTSEL       (0xD3*2U)   // Digital Compare AL Trip Select
#define HRPWM_O_DCBHTSEL       (0xD4*2U)   // Digital Compare BH Trip Select
#define HRPWM_O_DCBLTSEL       (0xD5*2U)   // Digital Compare BL Trip Select
#define HRPWM_O_PWMLOCK        (0xFA*2U)   // PWM Lock Register
#define HRPWM_O_HWVDELVAL      (0xFD*2U)   // Hardware Valley Mode Delay Register
#define HRPWM_O_VCNTVAL        (0xFE*2U)   // Hardware Valley Counter Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the TBCTRL register
//
//*************************************************************************************************
#define HRPWM_TBCTRL_CNTMSEL_S        0U
#define HRPWM_TBCTRL_CNTMSEL_M        0x3U      // Counter Mode
#define HRPWM_TBCTRL_PHSEN            0x4U      // Phase Load Enable
#define HRPWM_TBCTRL_TBPRDLDMSEL      0x8U      // Active Period Load
#define HRPWM_TBCTRL_SYNCOSRCSEL_S    4U
#define HRPWM_TBCTRL_SYNCOSRCSEL_M    0x30U     // Sync Output Select
#define HRPWM_TBCTRL_SPFSW            0x40U     // Software Force Sync Pulse
#define HRPWM_TBCTRL_HSTBCLKPSC_S     7U
#define HRPWM_TBCTRL_HSTBCLKPSC_M     0x380U    // High Speed TBCLK Pre-scaler
#define HRPWM_TBCTRL_TBCLKPSCCFG_S    10U
#define HRPWM_TBCTRL_TBCLKPSCCFG_M    0x1C00U   // Time Base Clock Pre-scaler
#define HRPWM_TBCTRL_CNTDIRCFG        0x2000U   // Phase Direction Bit
#define HRPWM_TBCTRL_EMCFG_S          14U
#define HRPWM_TBCTRL_EMCFG_M          0xC000U   // Emulation Mode Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBCTRL2 register
//
//*************************************************************************************************
#define HRPWM_TBCTRL2_OSSMEN           0x40U     // One shot sync mode
#define HRPWM_TBCTRL2_OSP              0x80U     // One shot sync
#define HRPWM_TBCTRL2_ESOSEL_S         12U
#define HRPWM_TBCTRL2_ESOSEL_M         0x3000U   // Syncout selection
#define HRPWM_TBCTRL2_PRDLDEVTSEL_S    14U
#define HRPWM_TBCTRL2_PRDLDEVTSEL_M    0xC000U   // PRD Shadow to Active Load on SYNC Event

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBSTS register
//
//*************************************************************************************************
#define HRPWM_TBSTS_CNTDIRFLG        0x1U   // Counter Direction Status
#define HRPWM_TBSTS_ESYNCEVTFLG      0x2U   // External Input Sync Status
#define HRPWM_TBSTS_TBCNT_RMAXVFLG   0x4U   // Counter Max Latched Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the CCOMPCTRL register
//
//*************************************************************************************************
#define HRPWM_CCOMPCTRL_CCOMPA_LDEVTSEL_S   0U
#define HRPWM_CCOMPCTRL_CCOMPA_LDEVTSEL_M   0x3U      // Active Compare A Load
#define HRPWM_CCOMPCTRL_CCOMPB_LDEVTSEL_S   2U
#define HRPWM_CCOMPCTRL_CCOMPB_LDEVTSEL_M   0xCU      // Active Compare B Load
#define HRPWM_CCOMPCTRL_CCOMPA_LDMOD        0x10U     // Compare A Register Block Operating Mode
#define HRPWM_CCOMPCTRL_CCOMPB_LDMOD        0x40U     // Compare B Register Block Operating Mode
#define HRPWM_CCOMPCTRL_CCOMPA_SFULLSTS     0x100U    // Compare A Shadow Register Full Status
#define HRPWM_CCOMPCTRL_CCOMPB_SFULLSTS     0x200U    // Compare B Shadow Register Full Status
#define HRPWM_CCOMPCTRL_CCOMPA_LDCCFG_S     10U
#define HRPWM_CCOMPCTRL_CCOMPA_LDCCFG_M     0xC00U    // Active Compare A Load on SYNC
#define HRPWM_CCOMPCTRL_CCOMPB_LDCCFG_S     12U
#define HRPWM_CCOMPCTRL_CCOMPB_LDCCFG_M     0x3000U   // Active Compare B Load on SYNC

//*************************************************************************************************
//
// The following are defines for the bit fields in the CCOMPCTRL2 register
//
//*************************************************************************************************
#define HRPWM_CCOMPCTRL2_CCOMPC_LDEVTSEL_S   0U
#define HRPWM_CCOMPCTRL2_CCOMPC_LDEVTSEL_M   0x3U      // Active Compare C Load
#define HRPWM_CCOMPCTRL2_CCOMPD_LDEVTSEL_S   2U
#define HRPWM_CCOMPCTRL2_CCOMPD_LDEVTSEL_M   0xCU      // Active Compare D load
#define HRPWM_CCOMPCTRL2_CCOMPC_LDMOD        0x10U     // Compare C Block Operating Mode
#define HRPWM_CCOMPCTRL2_CCOMPD_LDMOD        0x40U     // Compare D Block Operating Mode
#define HRPWM_CCOMPCTRL2_CCOMPC_LDCCFG_S     10U
#define HRPWM_CCOMPCTRL2_CCOMPC_LDCCFG_M     0xC00U    // Active Compare C Load on SYNC
#define HRPWM_CCOMPCTRL2_CCOMPD_LDCCFG_S     12U
#define HRPWM_CCOMPCTRL2_CCOMPD_LDCCFG_M     0x3000U   // Active Compare D Load on SYNC

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBCTRL register
//
//*************************************************************************************************
#define HRPWM_DBCTRL_DBOSEL_S         0U
#define HRPWM_DBCTRL_DBOSEL_M         0x3U      // Dead Band Output Mode Control
#define HRPWM_DBCTRL_IDSSEL_S         2U
#define HRPWM_DBCTRL_IDSSEL_M         0xCU      // Polarity Select Control
#define HRPWM_DBCTRL_DBISEL_S         4U
#define HRPWM_DBCTRL_DBISEL_M         0x30U     // Dead Band Input Select Mode Control
#define HRPWM_DBCTRL_RED_LDEVTSEL_S   6U
#define HRPWM_DBCTRL_RED_LDEVTSEL_M   0xC0U     // Active DBRED Load Mode
#define HRPWM_DBCTRL_FED_LDEVTSEL_S   8U
#define HRPWM_DBCTRL_FED_LDEVTSEL_M   0x300U    // Active DBFED Load Mode
#define HRPWM_DBCTRL_RED_LDMOD        0x400U    // DBRED Block Operating Mode
#define HRPWM_DBCTRL_FED_LDMOD        0x800U    // DBFED Block Operating Mode
#define HRPWM_DBCTRL_DBOSCTRL_S       12U
#define HRPWM_DBCTRL_DBOSCTRL_M       0x3000U   // Dead Band Output Swap Control
#define HRPWM_DBCTRL_DBDE_BMCTRL      0x4000U   // Dead Band Dual-Edge B Mode Control
#define HRPWM_DBCTRL_HCCLKEN          0x8000U   // Half Cycle Clocking Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBCTRL2 register
//
//*************************************************************************************************
#define HRPWM_DBCTRL2_DBCTRL_LDEVTSEL_S   0U
#define HRPWM_DBCTRL2_DBCTRL_LDEVTSEL_M   0x3U   // DBCTRL Load from Shadow Mode Select
#define HRPWM_DBCTRL2_DBCTRL_LDMOD        0x4U   // DBCTRL Load mode Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTRL register
//
//*************************************************************************************************
#define HRPWM_AQCTRL_AQB_LDEVTSEL_S     0U
#define HRPWM_AQCTRL_AQB_LDEVTSEL_M     0x3U     // Action Qualifier A Load Select
#define HRPWM_AQCTRL_AQA_LDEVTSEL_S     2U
#define HRPWM_AQCTRL_AQA_LDEVTSEL_M     0xCU     // Action Qualifier B Load Select
#define HRPWM_AQCTRL_AQA_LDMOD          0x10U    // Action Qualifer A Operating Mode
#define HRPWM_AQCTRL_AQB_LDMOD          0x40U    // Action Qualifier B Operating Mode
#define HRPWM_AQCTRL_AQCTRLA_LDCCFG_S   8U
#define HRPWM_AQCTRL_AQCTRLA_LDCCFG_M   0x300U   // AQCTRLA Register Load on SYNC
#define HRPWM_AQCTRL_AQCTRLB_LDCCFG_S   10U
#define HRPWM_AQCTRL_AQCTRLB_LDCCFG_M   0xC00U   // AQCTRLB Register Load on SYNC

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQTESRCSEL register
//
//*************************************************************************************************
#define HRPWM_AQTESRCSEL_T1EVTSRC_S   0U
#define HRPWM_AQTESRCSEL_T1EVTSRC_M   0xFU    // T1 Event Source Select Bits
#define HRPWM_AQTESRCSEL_T2EVTSRC_S   4U
#define HRPWM_AQTESRCSEL_T2EVTSRC_M   0xF0U   // T2 Event Source Select Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPCTRL register
//
//*************************************************************************************************
#define HRPWM_CPCTRL_CPFEN          0x1U     // HRPWM chopping enable
#define HRPWM_CPCTRL_OSPWCFG_S      1U
#define HRPWM_CPCTRL_OSPWCFG_M      0x1EU    // One-shot pulse width
#define HRPWM_CPCTRL_CPCLKPSC_S     5U
#define HRPWM_CPCTRL_CPCLKPSC_M     0xE0U    // Chopping clock frequency
#define HRPWM_CPCTRL_CPCLKDCCFG_S   8U
#define HRPWM_CPCTRL_CPCLKDCCFG_M   0x700U   // Chopping clock Duty cycle

//*************************************************************************************************
//
// The following are defines for the bit fields in the VCAPCTRL register
//
//*************************************************************************************************
#define HRPWM_VCAPCTRL_VCEN             0x1U     // Valley  Capture mode
#define HRPWM_VCAPCTRL_VCSTA            0x2U     // Valley  Capture Start
#define HRPWM_VCAPCTRL_CSEQTRGSEL_S     2U
#define HRPWM_VCAPCTRL_CSEQTRGSEL_M     0x1CU    // Capture Trigger Select
#define HRPWM_VCAPCTRL_VDMDIVCFG_S      7U
#define HRPWM_VCAPCTRL_VDMDIVCFG_M      0x380U   // Valley Delay Mode Divide Enable
#define HRPWM_VCAPCTRL_EDGFLTODLY       0x400U   // Valley Switching Mode Delay Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the VCNTCFG register
//
//*************************************************************************************************
#define HRPWM_VCNTCFG_STACNTESEL_S    0U
#define HRPWM_VCNTCFG_STACNTESEL_M    0xFU      // Counter Start Edge Selection
#define HRPWM_VCNTCFG_STACNTESTS      0x80U     // Start Edge Status Bit
#define HRPWM_VCNTCFG_STOPCNTESEL_S   8U
#define HRPWM_VCNTCFG_STOPCNTESEL_M   0xF00U    // Counter Start Edge Selection
#define HRPWM_VCNTCFG_STOPCNTESTS     0x8000U   // Stop Edge Status Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRPCFG register
//
//*************************************************************************************************
#define HRPWM_HRPCFG_AEMSEL_S           0U
#define HRPWM_HRPCFG_AEMSEL_M           0x3U      // PWMxA Edge Mode Select Bits
#define HRPWM_HRPCFG_ACTRLMSEL          0x4U      // PWMxA Control Mode Select Bits
#define HRPWM_HRPCFG_AHR_LDEVTSEL_S     3U
#define HRPWM_HRPCFG_AHR_LDEVTSEL_M     0x18U     // PWMxA Shadow Mode Select Bits
#define HRPWM_HRPCFG_BOINVCFG           0x20U     // PWMB Output Selection Bit
#define HRPWM_HRPCFG_AUTOCEN            0x40U     // Autoconversion Bit
#define HRPWM_HRPCFG_ABOSSWAP           0x80U     // Swap PWMA and PWMB Outputs Bit
#define HRPWM_HRPCFG_BEMSEL_S           8U
#define HRPWM_HRPCFG_BEMSEL_M           0x300U    // PWMxB Edge Mode Select Bits
#define HRPWM_HRPCFG_BCTRLMSEL          0x400U    // PWMxB Control Mode Select Bits
#define HRPWM_HRPCFG_BHR_LDEVTSEL_S     11U
#define HRPWM_HRPCFG_BHR_LDEVTSEL_M     0x1800U   // PWMxB Shadow Mode Select Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRPWM register
//
//*************************************************************************************************
#define HRPWM_HRPWM_MEPCALLEN   0x8000U   // Calibration Power On

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRMSTEP register
//
//*************************************************************************************************
#define HRPWM_HRMSTEP_MEPNUM_S   0U
#define HRPWM_HRMSTEP_MEPNUM_M   0xFFU   // High Resolution Micro Step Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRCFG2 register
//
//*************************************************************************************************
#define HRPWM_HRCFG2_DBEMSEL_S            0U
#define HRPWM_HRCFG2_DBEMSEL_M            0x3U    // Dead-Band Edge-Mode Select Bits
#define HRPWM_HRCFG2_DBREDHR_LDEVTSEL_S   2U
#define HRPWM_HRCFG2_DBREDHR_LDEVTSEL_M   0xCU    // DBRED Control Mode Select Bits
#define HRPWM_HRCFG2_DBFEDHR_LDEVTSEL_S   4U
#define HRPWM_HRCFG2_DBFEDHR_LDEVTSEL_M   0x30U   // DBFED Control Mode Select Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRPRDCTRL register
//
//*************************************************************************************************
#define HRPWM_HRPRDCTRL_HRPRDEN             0x1U    // High Resolution Period Enable
#define HRPWM_HRPRDCTRL_SYNCPER_SRCSEL      0x2U    // PWMSYNCPER Source Select
#define HRPWM_HRPRDCTRL_HRPHSEN             0x4U    // TBPOFHR Load Enable
#define HRPWM_HRPRDCTRL_ESSEL_S             4U
#define HRPWM_HRPRDCTRL_ESSEL_M             0x70U   // PWMSYNCPER Extended Source Select Bit:

//*************************************************************************************************
//
// The following are defines for the bit fields in the THRR register
//
//*************************************************************************************************
#define HRPWM_THRR_TRP_S   0U
#define HRPWM_THRR_TRP_M   0x7FFU   // HRPWM Remainder Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDCTRL register
//
//*************************************************************************************************
#define HRPWM_GLDCTRL_GLDEN            0x1U      // Global Shadow to Active load event control
#define HRPWM_GLDCTRL_GLD_LDEVTSEL_S   1U
#define HRPWM_GLDCTRL_GLD_LDEVTSEL_M   0x1EU     // Shadow to Active Global Load Pulse Selection
#define HRPWM_GLDCTRL_OSLDMCTRL        0x20U     // One Shot Load mode control bit
#define HRPWM_GLDCTRL_GLDPSC_S         7U
#define HRPWM_GLDCTRL_GLDPSC_M         0x380U    // Global Load Strobe Period Select Register
#define HRPWM_GLDCTRL_GLDEVTCNT_S      10U
#define HRPWM_GLDCTRL_GLDEVTCNT_M      0x1C00U   // Global Load Strobe Counter Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDECFG register
//
//*************************************************************************************************
#define HRPWM_GLDCFG_TBPRD_TBPRDHR        0x1U     // Global load event configuration for TBPRD:TBPRDHR
#define HRPWM_GLDCFG_CCOMPA_CCOMPAHR      0x2U     // Global load event configuration for CCOMPA:CCOMPAHR
#define HRPWM_GLDCFG_CCOMPB_CCOMPBHR      0x4U     // Global load event configuration for CCOMPB:CCOMPBHR
#define HRPWM_GLDCFG_CCOMPC               0x8U     // Global load event configuration for CCOMPC
#define HRPWM_GLDCFG_CCOMPD               0x10U    // Global load event configuration for CCOMPD
#define HRPWM_GLDCFG_DBRED_DBREDHR        0x20U    // Global load event configuration for DBRED:DBREDHR
#define HRPWM_GLDCFG_DBFED_DBFEDHR        0x40U    // Global load event configuration for DBFED:DBFEDHR
#define HRPWM_GLDCFG_DBCTRL               0x80U    // Global load event configuration for DBCTRL
#define HRPWM_GLDCFG_AQCTRLA_AQCTRLA2     0x100U   // Global load event configuration for AQCTRLA/A2
#define HRPWM_GLDCFG_AQCTRLB_AQCTRLB2     0x200U   // Global load event configuration for AQCTRLB/B2
#define HRPWM_GLDCFG_AQCSWF               0x400U   // Global load event configuration for AQCSWF

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINK register
//
//*************************************************************************************************
#define HRPWM_XLINK_TBPRD_TBPRDHR_LINK_S        0U
#define HRPWM_XLINK_TBPRD_TBPRDHR_LINK_M        0xFU          // TBPRD:TBPRDHR  Link
#define HRPWM_XLINK_CCOMPA_CCOMPAHR_LINK_S      4U
#define HRPWM_XLINK_CCOMPA_CCOMPAHR_LINK_M      0xF0U         // CCOMPA:CCOMPAHR Link
#define HRPWM_XLINK_CCOMPB_CCOMPBHR_LINK_S      8U
#define HRPWM_XLINK_CCOMPB_CCOMPBHR_LINK_M      0xF00U        // CCOMPB:CCOMPBHR Link
#define HRPWM_XLINK_CCOMPC_LINK_S               12U
#define HRPWM_XLINK_CCOMPC_LINK_M               0xF000U       // CCOMPC Link
#define HRPWM_XLINK_CCOMPD_LINK_S               16U
#define HRPWM_XLINK_CCOMPD_LINK_M               0xF0000U      // CCOMPD Link
#define HRPWM_XLINK_GLDCTRL2_LINK_S             28U
#define HRPWM_XLINK_GLDCTRL2_LINK_M             0xF0000000U   // GLDCTRL2 Link

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTRLA register
//
//*************************************************************************************************
#define HRPWM_AQCTRLA_ZEROCFG_S     0U
#define HRPWM_AQCTRLA_ZEROCFG_M     0x3U     // Action Counter = Zero
#define HRPWM_AQCTRLA_TBPRDCFG_S    2U
#define HRPWM_AQCTRLA_TBPRDCFG_M    0xCU     // Action Counter = Period
#define HRPWM_AQCTRLA_CAUPCFG_S     4U
#define HRPWM_AQCTRLA_CAUPCFG_M     0x30U    // Action Counter = Compare A Up
#define HRPWM_AQCTRLA_CADOWNCFG_S   6U
#define HRPWM_AQCTRLA_CADOWNCFG_M   0xC0U    // Action Counter = Compare A Down
#define HRPWM_AQCTRLA_CBUPCFG_S     8U
#define HRPWM_AQCTRLA_CBUPCFG_M     0x300U   // Action Counter = Compare B Up
#define HRPWM_AQCTRLA_CBDOWNCFG_S   10U
#define HRPWM_AQCTRLA_CBDOWNCFG_M   0xC00U   // Action Counter = Compare B Down

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADDAQCTRLA2 register
//
//*************************************************************************************************
#define HRPWM_ADDAQCTRLA2_T1UPCFG_S     0U
#define HRPWM_ADDAQCTRLA2_T1UPCFG_M     0x3U    // Action when event occurs on T1 in UP-Count
#define HRPWM_ADDAQCTRLA2_T1DOWMCFG_S   2U
#define HRPWM_ADDAQCTRLA2_T1DOWMCFG_M   0xCU    // Action when event occurs on T1 in DOWN-Count
#define HRPWM_ADDAQCTRLA2_T2UPCFG_S     4U
#define HRPWM_ADDAQCTRLA2_T2UPCFG_M     0x30U   // Action when event occurs on T2 in UP-Count
#define HRPWM_ADDAQCTRLA2_T2DOWMCFG_S   6U
#define HRPWM_ADDAQCTRLA2_T2DOWMCFG_M   0xC0U   // Action when event occurs on T2 in DOWN-Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTRLB register
//
//*************************************************************************************************
#define HRPWM_AQCTRLB_ZEROCFG_S    0U
#define HRPWM_AQCTRLB_ZEROCFG_M    0x3U     // Action Counter = Zero
#define HRPWM_AQCTRLB_TBPRDCFG_S   2U
#define HRPWM_AQCTRLB_TBPRDCFG_M   0xCU     // Action Counter = Period
#define HRPWM_AQCTRLB_CAUPCFG_S    4U
#define HRPWM_AQCTRLB_CAUPCFG_M    0x30U    // Action Counter = Compare A Up
#define HRPWM_AQCTRLB_CADOWNCFG_S  6U
#define HRPWM_AQCTRLB_CADOWNCFG_M  0xC0U    // Action Counter = Compare A Down
#define HRPWM_AQCTRLB_CBUPCFG_S    8U
#define HRPWM_AQCTRLB_CBUPCFG_M    0x300U   // Action Counter = Compare B Up
#define HRPWM_AQCTRLB_CBDOWNCFG_S  10U
#define HRPWM_AQCTRLB_CBDOWNCFG_M  0xC00U   // Action Counter = Compare B Down

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADDAQCTRLB2 register
//
//*************************************************************************************************
#define HRPWM_ADDAQCTRLB2_T1UPCFG_S     0U
#define HRPWM_ADDAQCTRLB2_T1UPCFG_M     0x3U    // Action when event occurs on T1 in UP-Count
#define HRPWM_ADDAQCTRLB2_T1DOWMCFG_S   2U
#define HRPWM_ADDAQCTRLB2_T1DOWMCFG_M   0xCU    // Action when event occurs on T1 in DOWN-Count
#define HRPWM_ADDAQCTRLB2_T2UPCFG_S     4U
#define HRPWM_ADDAQCTRLB2_T2UPCFG_M     0x30U   // Action when event occurs on T2 in UP-Count
#define HRPWM_ADDAQCTRLB2_T2DOWMCFG_S   6U
#define HRPWM_ADDAQCTRLB2_T2DOWMCFG_M   0xC0U   // Action when event occurs on T2 in DOWN-Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQSWF register
//
//*************************************************************************************************
#define HRPWM_AQSWF_AOTSWFCFG_S   0U
#define HRPWM_AQSWF_AOTSWFCFG_M   0x3U    // Action when One-time SW Force A Invoked
#define HRPWM_AQSWF_AOTSWFEN      0x4U    // One-time SW Force A Output
#define HRPWM_AQSWF_BOTSWFCFG_S   3U
#define HRPWM_AQSWF_BOTSWFCFG_M   0x18U   // Action when One-time SW Force B Invoked
#define HRPWM_AQSWF_BOTSWFEN      0x20U   // One-time SW Force A Output
#define HRPWM_AQSWF_RLDMSEL_S     6U
#define HRPWM_AQSWF_RLDMSEL_M     0xC0U   // Reload from Shadow Options

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCSWF register
//
//*************************************************************************************************
#define HRPWM_AQCSWF_ACSWFCFG_S   0U
#define HRPWM_AQCSWF_ACSWFCFG_M   0x3U   // Continuous Software Force on output A
#define HRPWM_AQCSWF_BCSWFCFG_S   2U
#define HRPWM_AQCSWF_BCSWFCFG_M   0xCU   // Continuous Software Force on output B

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBREDHRM register
//
//*************************************************************************************************
#define HRPWM_DBREDHRM_DBREDHR_S   9U
#define HRPWM_DBREDHRM_DBREDHR_M   0xFE00U   // DBREDHRM High Resolution Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBRED register
//
//*************************************************************************************************
#define HRPWM_DBRED_DBRED_S   0U
#define HRPWM_DBRED_DBRED_M   0x3FFFU   // Rising edge delay value

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBFEDHRM register
//
//*************************************************************************************************
#define HRPWM_DBFEDHRM_DBFEDHR_S   9U
#define HRPWM_DBFEDHRM_DBFEDHR_M   0xFE00U   // DBFEDHRM High Resolution Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBFED register
//
//*************************************************************************************************
#define HRPWM_DBFED_DBFED_S   0U
#define HRPWM_DBFED_DBFED_M   0x3FFFU   // Falling edge delay value

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBPOF register
//
//*************************************************************************************************
#define HRPWM_TBPOF_TBPOFHR_S   0U
#define HRPWM_TBPOF_TBPOFHR_M   0xFFFFU       // Extension Register for HRPWM Phase (8-bits)
#define HRPWM_TBPOF_TBPOF_S     16U
#define HRPWM_TBPOF_TBPOF_M     0xFFFF0000U   // Phase Offset Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CCOMPA register
//
//*************************************************************************************************
#define HRPWM_CCOMPA_CCOMPAHR_S   0U
#define HRPWM_CCOMPA_CCOMPAHR_M   0xFFFFU       // Compare A HRPWM Extension Register
#define HRPWM_CCOMPA_CCOMPA_S     16U
#define HRPWM_CCOMPA_CCOMPA_M     0xFFFF0000U   // Compare A Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CCOMPB register
//
//*************************************************************************************************
#define HRPWM_CCOMPB_CCOMPBHR_S   0U
#define HRPWM_CCOMPB_CCOMPBHR_M   0xFFFFU       // Compare B High Resolution Bits
#define HRPWM_CCOMPB_CCOMPB_S     16U
#define HRPWM_CCOMPB_CCOMPB_M     0xFFFF0000U   // Compare B Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDCTRL2 register
//
//*************************************************************************************************
#define HRPWM_GLDCTRL2_RLDEOSMEN   0x1U   // Enable reload event in one shot mode
#define HRPWM_GLDCTRL2_FLDEOSMEN   0x2U   // Force reload event in one shot mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZSEL register
//
//*************************************************************************************************
#define HRPWM_TZSEL_CCT1SEL      0x1U      // TZ1 CBC select
#define HRPWM_TZSEL_CCT2SEL      0x2U      // TZ2 CBC select
#define HRPWM_TZSEL_CCT3SEL      0x4U      // TZ3 CBC select
#define HRPWM_TZSEL_CCT4SEL      0x8U      // TZ4 CBC select
#define HRPWM_TZSEL_CCT5SEL      0x10U     // TZ5 CBC select
#define HRPWM_TZSEL_CCT6SEL      0x20U     // TZ6 CBC select
#define HRPWM_TZSEL_DCAE2SEL     0x40U     // DCAEVT2 CBC select
#define HRPWM_TZSEL_DCBE2SEL     0x80U     // DCBEVT2 CBC select
#define HRPWM_TZSEL_OST1SEL      0x100U    // One-shot TZ1 select
#define HRPWM_TZSEL_OST2SEL      0x200U    // One-shot TZ2 select
#define HRPWM_TZSEL_OST3SEL      0x400U    // One-shot TZ3 select
#define HRPWM_TZSEL_OST4SEL      0x800U    // One-shot TZ4 select
#define HRPWM_TZSEL_OST5SEL      0x1000U   // One-shot TZ5 select
#define HRPWM_TZSEL_OST6SEL      0x2000U   // One-shot TZ6 select
#define HRPWM_TZSEL_DCAE1SEL     0x4000U   // One-shot DCAEVT1 select
#define HRPWM_TZSEL_DCBE1SEL     0x8000U   // One-shot DCBEVT1 select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZDCCFG register
//
//*************************************************************************************************
#define HRPWM_TZDCCFG_DCAE1CFG_S   0U
#define HRPWM_TZDCCFG_DCAE1CFG_M   0x7U     // Digital Compare Output A Event 1
#define HRPWM_TZDCCFG_DCAE2CFG_S   3U
#define HRPWM_TZDCCFG_DCAE2CFG_M   0x38U    // Digital Compare Output A Event 2
#define HRPWM_TZDCCFG_DCBE1CFG_S   6U
#define HRPWM_TZDCCFG_DCBE1CFG_M   0x1C0U   // Digital Compare Output B Event 1
#define HRPWM_TZDCCFG_DCBE2CFG_S   9U
#define HRPWM_TZDCCFG_DCBE2CFG_M   0xE00U   // Digital Compare Output B Event 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTRL register
//
//*************************************************************************************************
#define HRPWM_TZCTRL_TZACFG_S       0U
#define HRPWM_TZCTRL_TZACFG_M       0x3U     // TZ1 to TZ6 Trip Action On HRPWMxA
#define HRPWM_TZCTRL_TZBCFG_S       2U
#define HRPWM_TZCTRL_TZBCFG_M       0xCU     // TZ1 to TZ6 Trip Action On HRPWMxB
#define HRPWM_TZCTRL_DCAE1CFG_S     4U
#define HRPWM_TZCTRL_DCAE1CFG_M     0x30U    // HRPWMxA action on DCAEVT1
#define HRPWM_TZCTRL_DCAE2CFG_S     6U
#define HRPWM_TZCTRL_DCAE2CFG_M     0xC0U    // HRPWMxA action on DCAEVT2
#define HRPWM_TZCTRL_DCBE1CFG_S     8U
#define HRPWM_TZCTRL_DCBE1CFG_M     0x300U   // HRPWMxB action on DCBEVT1
#define HRPWM_TZCTRL_DCBE2CFG_S     10U
#define HRPWM_TZCTRL_DCBE2CFG       0xC00U   // HRPWMxB action on DCBEVT2

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTRL2 register
//
//*************************************************************************************************
#define HRPWM_TZCTRL2_TZAUPCFG_S     0U
#define HRPWM_TZCTRL2_TZAUPCFG_M     0x7U      // Trip Action On HRPWMxA while Count direction is UP
#define HRPWM_TZCTRL2_TZADOWNCFG_S   3U
#define HRPWM_TZCTRL2_TZADOWNCFG_M   0x38U     // Trip Action On HRPWMxA while Count direction is DOWN
#define HRPWM_TZCTRL2_TZBUPCFG_S     6U
#define HRPWM_TZCTRL2_TZBUPCFG_M     0x1C0U    // Trip Action On HRPWMxB while Count direction is UP
#define HRPWM_TZCTRL2_TZBDOWNCFG_S   9U
#define HRPWM_TZCTRL2_TZBDOWNCFG_M   0xE00U    // Trip Action On HRPWMxB while Count direction is DOWN
#define HRPWM_TZCTRL2_TZCTRL2EN      0x8000U   // TZCTRL2 Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTRLDCA register
//
//*************************************************************************************************
#define HRPWM_TZCTRLDCA_DCAE1UPCFG_S     0U
#define HRPWM_TZCTRLDCA_DCAE1UPCFG_M     0x7U     // DCAE1 Action On HRPWMxA while Count direction is UP
#define HRPWM_TZCTRLDCA_DCAE1DOWNCFG_S   3U
#define HRPWM_TZCTRLDCA_DCAE1DOWNCFG_M   0x38U    // DCAE1 Action On HRPWMxA while Count direction is
                                            // DOWN
#define HRPWM_TZCTRLDCA_DCAE2UPCFG_S     6U
#define HRPWM_TZCTRLDCA_DCAE2UPCFG_M     0x1C0U   // DCAE2 Action On HRPWMxA while Count direction is UP
#define HRPWM_TZCTRLDCA_DCAE2DOWNCFG_S   9U
#define HRPWM_TZCTRLDCA_DCAE2DOWNCFG_M   0xE00U   // DCAE2 Action On HRPWMxA while Count direction is
                                            // DOWN

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTRLDCB register
//
//*************************************************************************************************
#define HRPWM_TZCTRLDCB_DCAE1UPCFG_S     0U
#define HRPWM_TZCTRLDCB_DCAE1UPCFG_M     0x7U     // DCBEVT1 Action On HRPWMxA while Count direction is UP
#define HRPWM_TZCTRLDCB_DCAE1DOWNCFG_S   3U
#define HRPWM_TZCTRLDCB_DCAE1DOWNCFG_M   0x38U    // DCBEVT1 Action On HRPWMxA while Count direction is
                                            // DOWN
#define HRPWM_TZCTRLDCB_DCAE2UPCFG_S     6U
#define HRPWM_TZCTRLDCB_DCAE2UPCFG_M     0x1C0U   // DCBEVT2 Action On HRPWMxA while Count direction is UP
#define HRPWM_TZCTRLDCB_DCAE2DOWNCFG_S   9U
#define HRPWM_TZCTRLDCB_DCAE2DOWNCFG_M   0xE00U   // DCBEVT2 Action On HRPWMxA while Count direction is
                                            // DOWN

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZINTEN register
//
//*************************************************************************************************
#define HRPWM_TZINTEN_CCTEN        0x2U    // Trip Zones Cycle By Cycle Int Enable
#define HRPWM_TZINTEN_OSTEN        0x4U    // Trip Zones One Shot Int Enable
#define HRPWM_TZINTEN_DCAE1INTEN   0x8U    // Digital Compare A Event 1 Int Enable
#define HRPWM_TZINTEN_DCAE2INTEN   0x10U   // Digital Compare A Event 2 Int Enable
#define HRPWM_TZINTEN_DCBE1INTEN   0x20U   // Digital Compare B Event 1 Int Enable
#define HRPWM_TZINTEN_DCBE2INTEN   0x40U   // Digital Compare B Event 2 Int Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZFLG register
//
//*************************************************************************************************
#define HRPWM_TZFLG_TINTSTS    0x1U    // Global Int Status Flag
#define HRPWM_TZFLG_CCTESTS    0x2U    // Trip Zones Cycle By Cycle Flag
#define HRPWM_TZFLG_OSTESTS    0x4U    // Trip Zones One Shot Flag
#define HRPWM_TZFLG_DCAE1STS   0x8U    // Digital Compare A Event 1 Flag
#define HRPWM_TZFLG_DCAE2STS   0x10U   // Digital Compare A Event 2 Flag
#define HRPWM_TZFLG_DCBE1STS   0x20U   // Digital Compare B Event 1 Flag
#define HRPWM_TZFLG_DCBE2STS   0x40U   // Digital Compare B Event 2 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCCTFLG register
//
//*************************************************************************************************
#define HRPWM_TZCCTFLG_CCT1FLG      0x1U    // Latched Status Flag for CBC1 Trip Latch
#define HRPWM_TZCCTFLG_CCT2FLG      0x2U    // Latched Status Flag for CBC2 Trip Latch
#define HRPWM_TZCCTFLG_CCT3FLG      0x4U    // Latched Status Flag for CBC3 Trip Latch
#define HRPWM_TZCCTFLG_CCT4FLG      0x8U    // Latched Status Flag for CBC4 Trip Latch
#define HRPWM_TZCCTFLG_CCT5FLG      0x10U   // Latched Status Flag for CBC5 Trip Latch
#define HRPWM_TZCCTFLG_CCT6FLG      0x20U   // Latched Status Flag for CBC6 Trip Latch
#define HRPWM_TZCCTFLG_DCAE2FLG     0x40U   // Latched Status Flag for Digital Compare Output A Event 2
#define HRPWM_TZCCTFLG_DCBE2FLG     0x80U   // Latched Status Flag for Digital Compare Output B Event 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZOSTFLG register
//
//*************************************************************************************************
#define HRPWM_TZOSTFLG_OST1FLG      0x1U    // Latched Status Flag for OST1 Trip Latch
#define HRPWM_TZOSTFLG_OST2FLG      0x2U    // Latched Status Flag for OST2 Trip Latch
#define HRPWM_TZOSTFLG_OST3FLG      0x4U    // Latched Status Flag for OST3 Trip Latch
#define HRPWM_TZOSTFLG_OST4FLG      0x8U    // Latched Status Flag for OST4 Trip Latch
#define HRPWM_TZOSTFLG_OST5FLG      0x10U   // Latched Status Flag for OST5 Trip Latch
#define HRPWM_TZOSTFLG_OST6FLG      0x20U   // Latched Status Flag for OST6 Trip Latch
#define HRPWM_TZOSTFLG_DCAE1FLG     0x40U   // Latched Status Flag for Digital Compare Output A Event 1
#define HRPWM_TZOSTFLG_DCBE1FLG     0x80U   // Latched Status Flag for Digital Compare Output B Event 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCLR register
//
//*************************************************************************************************
#define HRPWM_TZCLR_GINTCLR       0x1U      // Global Interrupt Clear Flag
#define HRPWM_TZCLR_CCTCLR        0x2U      // Cycle-By-Cycle Flag Clear
#define HRPWM_TZCLR_OSTCLR        0x4U      // One-Shot Flag Clear
#define HRPWM_TZCLR_DCAE1CLR      0x8U      // DCAE1 Flag Clear
#define HRPWM_TZCLR_DCAE2CLR      0x10U     // DCAE2 Flag Clear
#define HRPWM_TZCLR_DCBE1CLR      0x20U     // DCBE1 Flag Clear
#define HRPWM_TZCLR_DCBE2CLR      0x40U     // DCBE2 Flag Clear
#define HRPWM_TZCLR_CCTPCLR_S     14U
#define HRPWM_TZCLR_CCTPCLR_M     0xC000U   // Clear Pulse for CBC Trip Latch

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCCTCLR register
//
//*************************************************************************************************
#define HRPWM_TZCCTCLR_CCT1CLR      0x1U    // Clear Flag for Cycle-By-Cycle (CCT1) Trip Latch
#define HRPWM_TZCCTCLR_CCT2CLR      0x2U    // Clear Flag for Cycle-By-Cycle (CCT2) Trip Latch
#define HRPWM_TZCCTCLR_CCT3CLR      0x4U    // Clear Flag for Cycle-By-Cycle (CCT3) Trip Latch
#define HRPWM_TZCCTCLR_CCT4CLR      0x8U    // Clear Flag for Cycle-By-Cycle (CCT4) Trip Latch
#define HRPWM_TZCCTCLR_CCT5CLR      0x10U   // Clear Flag for Cycle-By-Cycle (CCT5) Trip Latch
#define HRPWM_TZCCTCLR_CCT6CLR      0x20U   // Clear Flag for Cycle-By-Cycle (CCT6) Trip Latch
#define HRPWM_TZCCTCLR_DCAE2CLR     0x40U   // Clear Flag forDCAE2 selected for CCT
#define HRPWM_TZCCTCLR_DCBE2CLR     0x80U   // Clear Flag for DCBE2 selected for CCT

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCOSTCLR register
//
//*************************************************************************************************
#define HRPWM_TZCOSTCLR_OST1CLR      0x1U    // Clear Flag for Oneshot (OST1) Trip Latch
#define HRPWM_TZCOSTCLR_OST2CLR      0x2U    // Clear Flag for Oneshot (OST2) Trip Latch
#define HRPWM_TZCOSTCLR_OST3CLR      0x4U    // Clear Flag for Oneshot (OST3) Trip Latch
#define HRPWM_TZCOSTCLR_OST4CLR      0x8U    // Clear Flag for Oneshot (OST4) Trip Latch
#define HRPWM_TZCOSTCLR_OST5CLR      0x10U   // Clear Flag for Oneshot (OST5) Trip Latch
#define HRPWM_TZCOSTCLR_OST6CLR      0x20U   // Clear Flag for Oneshot (OST6) Trip Latch
#define HRPWM_TZCOSTCLR_DCAE1CLR     0x40U   // Clear Flag for DCAE1 selected for OST
#define HRPWM_TZCOSTCLR_DCBE1CLR     0x80U   // Clear Flag for DCBE1 selected for OST

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZF register
//
//*************************************************************************************************
#define HRPWM_TZF_CCT      0x2U    // Force Trip Zones Cycle By Cycle Event
#define HRPWM_TZF_OST      0x4U    // Force Trip Zones One Shot Event
#define HRPWM_TZF_DCAE1F   0x8U    // Force Digital Compare A Event 1
#define HRPWM_TZF_DCAE2F   0x10U   // Force Digital Compare A Event 2
#define HRPWM_TZF_DCBE1F   0x20U   // Force Digital Compare B Event 1
#define HRPWM_TZF_DCBE2F   0x40U   // Force Digital Compare B Event 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETRSEL register
//
//*************************************************************************************************
#define HRPWM_ETRSEL_INTSEL_S       0U
#define HRPWM_ETRSEL_INTSEL_M       0x7U      // HRPWMxINTn Select
#define HRPWM_ETRSEL_INTGEN         0x8U      // HRPWMxINTn Enable
#define HRPWM_ETRSEL_SOCA_COMPSEL   0x10U     // HRPWMxSOCA Compare Select
#define HRPWM_ETRSEL_SOCB_COMPSEL   0x20U     // HRPWMxSOCB Compare Select
#define HRPWM_ETRSEL_INT_COMPSEL    0x40U     // HRPWMxINT Compare Select
#define HRPWM_ETRSEL_SOCAESEL_S     8U
#define HRPWM_ETRSEL_SOCAESEL_M     0x700U    // Start of Conversion A Select
#define HRPWM_ETRSEL_SOCAEN         0x800U    // Start of Conversion A Enable
#define HRPWM_ETRSEL_SOCBESEL_S     12U
#define HRPWM_ETRSEL_SOCBESEL_M     0x7000U   // Start of Conversion B Select
#define HRPWM_ETRSEL_SOCBEN         0x8000U   // Start of Conversion B Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETRPSC register
//
//*************************************************************************************************
#define HRPWM_ETRPSC_INTPRDSEL_S    0U
#define HRPWM_ETRPSC_INTPRDSEL_M    0x3U      // HRPWMxINTn Period Select
#define HRPWM_ETRPSC_INTECNT_S      2U
#define HRPWM_ETRPSC_INTECNT_M      0xCU      // HRPWMxINTn Counter Register
#define HRPWM_ETRPSC_INTPSCSEL      0x10U     // HRPWMxINTn Pre-Scale Selection Bits
#define HRPWM_ETRPSC_SOCPSCSEL      0x20U     // HRPWMxSOC A/B  Pre-Scale Selection Bits
#define HRPWM_ETRPSC_SOCAPRDSEL_S   8U
#define HRPWM_ETRPSC_SOCAPRDSEL_M   0x300U    // HRPWMxSOCA Period Select
#define HRPWM_ETRPSC_SOCAECNT_S     10U
#define HRPWM_ETRPSC_SOCAECNT_M     0xC00U    // HRPWMxSOCA Counter Register
#define HRPWM_ETRPSC_SOCBPRDSEL_S   12U
#define HRPWM_ETRPSC_SOCBPRDSEL_M   0x3000U   // HRPWMxSOCB Period Select
#define HRPWM_ETRPSC_SOCBECNT_S     14U
#define HRPWM_ETRPSC_SOCBECNT_M     0xC000U   // HRPWMxSOCB Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETRFLG register
//
//*************************************************************************************************
#define HRPWM_ETRFLG_INTFLG    0x1U   // HRPWMxINTn Flag
#define HRPWM_ETRFLG_SOCAFLG   0x4U   // HRPWMxSOCA Flag
#define HRPWM_ETRFLG_SOCBFLG   0x8U   // HRPWMxSOCB Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETRCLR register
//
//*************************************************************************************************
#define HRPWM_ETRCLR_INTCLR    0x1U   // HRPWMxINTn Clear
#define HRPWM_ETRCLR_SOCACLR   0x4U   // HRPWMxSOCA Clear
#define HRPWM_ETRCLR_SOCBCLR   0x8U   // HRPWMxSOCB Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETRF register
//
//*************************************************************************************************
#define HRPWM_ETRF_INTF    0x1U   // HRPWMxINTn Force
#define HRPWM_ETRF_SOCAF   0x4U   // HRPWMxSOCA Force
#define HRPWM_ETRF_SOCBF   0x8U   // HRPWMxSOCB Force

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETRINTPSC register
//
//*************************************************************************************************
#define HRPWM_ETRINTPSC_INTPRD2SEL_S   0U
#define HRPWM_ETRINTPSC_INTPRD2SEL_M   0xFU    // HRPWMxINTn Period Select
#define HRPWM_ETRINTPSC_INTECNT2_S     4U
#define HRPWM_ETRINTPSC_INTECNT2_M     0xF0U   // HRPWMxINTn Counter Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETRSOCPSC register
//
//*************************************************************************************************
#define HRPWM_ETRSOCPSC_SOCAPRD2SEL_S   0U
#define HRPWM_ETRSOCPSC_SOCAPRD2SEL_M   0xFU      // HRPWMxSOCA Period Select
#define HRPWM_ETRSOCPSC_SOCAECNT2_S     4U
#define HRPWM_ETRSOCPSC_SOCAECNT2_M     0xF0U     // HRPWMxSOCA Counter Register
#define HRPWM_ETRSOCPSC_SOCBPRD2SEL_S   8U
#define HRPWM_ETRSOCPSC_SOCBPRD2SEL_M   0xF00U    // HRPWMxSOCB Period Select
#define HRPWM_ETRSOCPSC_SOCBECNT2_S     12U
#define HRPWM_ETRSOCPSC_SOCBECNT2_M     0xF000U   // HRPWMxSOCB Counter Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETRCNTICTRL register
//
//*************************************************************************************************
#define HRPWM_ETRCNTICTRL_INTCNT2IF      0x400U    // HRPWMxINT Counter Initialization Force
#define HRPWM_ETRCNTICTRL_SOCACNT2IF     0x800U    // HRPWMxSOCA Counter Initialization Force
#define HRPWM_ETRCNTICTRL_SOCBCNT2IF     0x1000U   // HRPWMxSOCB Counter Initialization Force
#define HRPWM_ETRCNTICTRL_INTCNT2IEN     0x2000U   // HRPWMxINT Counter Initialization Enable
#define HRPWM_ETRCNTICTRL_SOCACNT2IEN    0x4000U   // HRPWMxSOCA Counter Initialization Enable
#define HRPWM_ETRCNTICTRL_SOCBCNT2IEN    0x8000U   // HRPWMxSOCB Counter Initialization Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETRCNTI register
//
//*************************************************************************************************
#define HRPWM_ETRCNTI_INTCNT2I_S    0U
#define HRPWM_ETRCNTI_INTCNT2I_M    0xFU     // HRPWMxINT Counter Initialization Bits
#define HRPWM_ETRCNTI_SOCACNT2I_S   4U
#define HRPWM_ETRCNTI_SOCACNT2I_M   0xF0U    // HRPWMxSOCA Counter Initialization Bits
#define HRPWM_ETRCNTI_SOCBCNT2I_S   8U
#define HRPWM_ETRCNTI_SOCBCNT2I_M   0xF00U   // HRPWMxSOCB Counter Initialization Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCTSEL register
//
//*************************************************************************************************
#define HRPWM_DCTSEL_DCAHISEL_S   0U
#define HRPWM_DCTSEL_DCAHISEL_M   0xFU      // Digital Compare A High COMP Input Select
#define HRPWM_DCTSEL_DCALISEL_S   4U
#define HRPWM_DCTSEL_DCALISEL_M   0xF0U     // Digital Compare A Low COMP Input Select
#define HRPWM_DCTSEL_DCBHISEL_S   8U
#define HRPWM_DCTSEL_DCBHISEL_M   0xF00U    // Digital Compare B High COMP Input Select
#define HRPWM_DCTSEL_DCBLISEL_S   12U
#define HRPWM_DCTSEL_DCBLISEL_M   0xF000U   // Digital Compare B Low COMP Input Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCACTRL register
//
//*************************************************************************************************
#define HRPWM_DCACTRL_DCAE1_SRCSEL       0x1U     // DCAE1 Source Signal
#define HRPWM_DCACTRL_DCAE1_FSSEL        0x2U     // DCAE1 Force Sync Signal
#define HRPWM_DCACTRL_DCAE1_SOCEN        0x4U     // DCAE1 SOC Enable
#define HRPWM_DCACTRL_DCAE1_SYNCEN       0x8U     // DCAE1 SYNC Enable
#define HRPWM_DCACTRL_DCAE2_SRCSEL       0x100U   // DCAE2 Source Signal
#define HRPWM_DCACTRL_DCAE2_FSSEL        0x200U   // DCAE2 Force Sync Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCBCTRL register
//
//*************************************************************************************************
#define HRPWM_DCBCTRL_DCBE1_SRCSEL       0x1U     // DCBE1 Source Signal
#define HRPWM_DCBCTRL_DCBE1_FSSEL        0x2U     // DCBE1 Force Sync Signal
#define HRPWM_DCBCTRL_DCBE1_SOCEN        0x4U     // DCBE1 SOC Enable
#define HRPWM_DCBCTRL_DCBE1_SYNCEN       0x8U     // DCBE1 SYNC Enable
#define HRPWM_DCBCTRL_DCBE2_SRCSEL       0x100U   // DCBE2 Source Signal
#define HRPWM_DCBCTRL_DCBE2_FSSEL        0x200U   // DCBE2 Force Sync Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCFCTRL register
//
//*************************************************************************************************
#define HRPWM_DCFCTRL_FBSRCSEL_S       0U
#define HRPWM_DCFCTRL_FBSRCSEL_M       0x3U      // Filter Block Signal Source Select
#define HRPWM_DCFCTRL_BLANKWEN         0x4U      // Blanking Enable/Disable
#define HRPWM_DCFCTRL_BLANKWINV        0x8U      // Blanking Window Inversion
#define HRPWM_DCFCTRL_BCAPSEL_S        4U
#define HRPWM_DCFCTRL_BCAPSEL_M        0x30U     // Pulse Select for Blanking & Capture Alignment
#define HRPWM_DCFCTRL_EFSEL            0x40U     // Edge Filter Select
#define HRPWM_DCFCTRL_EMSEL_S          8U
#define HRPWM_DCFCTRL_EMSEL_M          0x300U    // Edge Mode
#define HRPWM_DCFCTRL_ECNTSEL_S        10U
#define HRPWM_DCFCTRL_ECNTSEL_M        0x1C00U   // Edge Count
#define HRPWM_DCFCTRL_ESTS_S           13U
#define HRPWM_DCFCTRL_ESTS_M           0xE000U   // Edge Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCAPCTL register
//
//*************************************************************************************************
#define HRPWM_DCCAPCTL_CNTCEN       0x1U      // Counter Capture Enable
#define HRPWM_DCCAPCTL_CNTCSMSEL    0x2U      // Counter Capture Mode
#define HRPWM_DCCAPCTL_CELFLG       0x2000U   // Latched Status Flag for Capture Event
#define HRPWM_DCCAPCTL_DCCLFLGCLR   0x4000U   // DC Capture Latched Status Clear Flag
#define HRPWM_DCCAPCTL_CNTCM        0x8000U   // Counter Capture Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCAHTSEL register
//
//*************************************************************************************************
#define HRPWM_DCAHTSEL_TRIPIN1    0x1U      // Trip Input 1 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN2    0x2U      // Trip Input 2 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN3    0x4U      // Trip Input 3 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN4    0x8U      // Trip Input 4 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN5    0x10U     // Trip Input 5 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN6    0x20U     // Trip Input 6 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN7    0x40U     // Trip Input 7 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN8    0x80U     // Trip Input 8 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN9    0x100U    // Trip Input 9 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN10   0x200U    // Trip Input 10 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN11   0x400U    // Trip Input 11 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN12   0x800U    // Trip Input 12 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN14   0x2000U   // Trip Input 14 Select to DCAH Mux
#define HRPWM_DCAHTSEL_TRIPIN15   0x4000U   // Trip Input 15 Select to DCAH Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCALTSEL register
//
//*************************************************************************************************
#define HRPWM_DCALTSEL_TRIPIN1    0x1U      // Trip Input 1 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN2    0x2U      // Trip Input 2 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN3    0x4U      // Trip Input 3 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN4    0x8U      // Trip Input 4 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN5    0x10U     // Trip Input 5 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN6    0x20U     // Trip Input 6 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN7    0x40U     // Trip Input 7 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN8    0x80U     // Trip Input 8 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN9    0x100U    // Trip Input 9 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN10   0x200U    // Trip Input 10 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN11   0x400U    // Trip Input 11 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN12   0x800U    // Trip Input 12 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN14   0x2000U   // Trip Input 14 Select to DCAL Mux
#define HRPWM_DCALTSEL_TRIPIN15   0x4000U   // Trip Input 15 Select to DCAL Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCBHTSEL register
//
//*************************************************************************************************
#define HRPWM_DCBHTSEL_TRIPIN1    0x1U      // Trip Input 1 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN2    0x2U      // Trip Input 2 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN3    0x4U      // Trip Input 3 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN4    0x8U      // Trip Input 4 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN5    0x10U     // Trip Input 5 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN6    0x20U     // Trip Input 6 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN7    0x40U     // Trip Input 7 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN8    0x80U     // Trip Input 8 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN9    0x100U    // Trip Input 9 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN10   0x200U    // Trip Input 10 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN11   0x400U    // Trip Input 11 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN12   0x800U    // Trip Input 12 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN14   0x2000U   // Trip Input 14 Select to DCBH Mux
#define HRPWM_DCBHTSEL_TRIPIN15   0x4000U   // Trip Input 15 Select to DCBH Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCBLTSEL register
//
//*************************************************************************************************
#define HRPWM_DCBLTSEL_TRIPIN1    0x1U      // Trip Input 1 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN2    0x2U      // Trip Input 2 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN3    0x4U      // Trip Input 3 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN4    0x8U      // Trip Input 4 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN5    0x10U     // Trip Input 5 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN6    0x20U     // Trip Input 6 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN7    0x40U     // Trip Input 7 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN8    0x80U     // Trip Input 8 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN9    0x100U    // Trip Input 9 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN10   0x200U    // Trip Input 10 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN11   0x400U    // Trip Input 11 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN12   0x800U    // Trip Input 12 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN14   0x2000U   // Trip Input 14 Select to DCBL Mux
#define HRPWM_DCBLTSEL_TRIPIN15   0x4000U   // Trip Input 15 Select to DCBL Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRPWMLOCK register
//
//*************************************************************************************************
#define HRPWM_HRPWMLOCK_HRLOCK      0x1U          // HRHRPWM Register Set Lock
#define HRPWM_HRPWMLOCK_GLDLOCK     0x2U          // Global Load Register Set Lock
#define HRPWM_HRPWMLOCK_TZCFGLOCK   0x4U          // TripZone Register Set Lock
#define HRPWM_HRPWMLOCK_TZCLRLOCK   0x8U          // TripZone Clear Register Set Lock
#define HRPWM_HRPWMLOCK_DCLOCK      0x10U         // Digital Compare Register Set Lock
#define HRPWM_HRPWMLOCK_KEY_S       16U
#define HRPWM_HRPWMLOCK_KEY_M       0xFFFF0000U   // Key to write to this register



#endif
