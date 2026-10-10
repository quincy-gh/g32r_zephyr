//###########################################################################
//
// FILE:    hw_dbgmcu.h
//
// TITLE:   Definitions for the DBGMCU registers.
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

#ifndef HW_DBGMCU_H
#define HW_DBGMCU_H

//*************************************************************************************************
//
// The following are defines for the DBGMCU register offsets
//
//*************************************************************************************************
#define DBGMCU_O_IDCODE          0x0U    // Device ID register
#define DBGMCU_O_CTRL            0x4U    // Debug MCU Control register

#define DBGMCU_O_CONTROL1        0x30U   // Debug MCU configuration register
#define DBGMCU_O_CONTROL2        0x38U   // Debug MCU configuration register
#define DBGMCU_O_CONTROL3        0x40U   // Debug MCU configuration register

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBGMCU_IDCODE register
//
//*************************************************************************************************
#define DBGMCU_IDCODE_EQR_S   0U
#define DBGMCU_IDCODE_EQR_M   0xFFFFU       // Equipment Recognition
#define DBGMCU_IDCODE_WVR_S   16U
#define DBGMCU_IDCODE_WVR_M   0xFFFF0000U   // Wafer Version Recognition

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBGMCU_CTRL register
//
//*************************************************************************************************
#define DBGMCU_CTRL_STOP_CLK_EN          0x1U          // Enable the system clock when MCU is debugged in stop mode
#define DBGMCU_CTRL_HALT_GTS_STOP        0x40U         // The global timestamp is stop when CPU enters HALT mode
#define DBGMCU_CTRL_HALT_INT_REP         0x10000U      // The global timestamp is stop when CPU enters HALT mode
#define DBGMCU_CTRL_REAL_INT             0x40000U      // Interrupt run cannot enter HALT when CPU in real-time mode
#define DBGMCU_CTRL_TRGIODIRSEL          0x10000000U   // TRGIO direction select

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBGMCU_CONTROL1 register
//
//*************************************************************************************************
#define DBGMCU_CONTROL1_HALT_PWM1_STS    0x1U         // Configure PWM1 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL1_HALT_PWM2_STS    0x2U         // Configure PWM2 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL1_HALT_PWM3_STS    0x4U         // Configure PWM3 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL1_HALT_PWM4_STS    0x8U         // Configure PWM4 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL1_HALT_PWM5_STS    0x10U        // Configure PWM5 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL1_HALT_PWM6_STS    0x20U        // Configure PWM6 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL1_HALT_PWM7_STS    0x40U        // Configure PWM7 Work Status When CPU is in HALT mode

#define DBGMCU_CONTROL1_HALT_CAP1_STS    0x100U       // Configure CAP1 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL1_HALT_CAP2_STS    0x200U       // Configure CAP2 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL1_HALT_CAP3_STS    0x400U       // Configure CAP3 Work Status When CPU is in HALT mode

#define DBGMCU_CONTROL1_HALT_COMP1_STS   0x10000U     // Configure COMP1 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL1_HALT_COMP2_STS   0x20000U     // Configure COMP2 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL1_HALT_COMP3_STS   0x40000U     // Configure COMP3 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL1_HALT_COMP4_STS   0x80000U     // Configure COMP4 Work Status When CPU is in HALT mode

#define DBGMCU_CONTROL1_HALT_QEP1_STS    0x1000000U   // Configure QEP1 Work Status When CPU is in HALT mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBGMCU_CONTROL2 register
//
//*************************************************************************************************
#define DBGMCU_CONTROL2_HALT_LINA_STS       0x1U       // Configure LINA Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL2_HALT_UARTA_STS      0x2U       // Configure UARTA Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL2_HALT_SPIA_STS       0x4U       // Configure SPIA Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL2_HALT_I2CA_STS       0x8U       // Configure I2CA Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL2_HALT_CANA_STS       0x10U      // Configure CANA Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL2_HALT_UARTB_STS      0x200U     // Configure UARTB Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL2_HALT_I2CB_STS       0x800U     // Configure I2CB Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL2_HALT_UARTC_STS      0x2000U    // Configure UARTC Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL2_HALT_FLB1_STS       0x10000U   // Configure FLB1 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL2_HALT_FLB2_STS       0x20000U   // Configure FLB2 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL2_HALT_FLB3_STS       0x40000U   // Configure FLB3 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL2_HALT_FLB4_STS       0x80000U   // Configure FLB4 Work Status When CPU is in HALT mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBGMCU_AHB1CFG0 register
//
//*************************************************************************************************
#define DBGMCU_CONTROL3_HALT_WDT_STS    0x1U     // Configure WDT Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL3_HALT_TMR0_STS   0x100U   // Configure TMR0 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL3_HALT_TMR1_STS   0x200U   // Configure TMR1 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL3_HALT_TMR2_STS   0x400U   // Configure TMR2 Work Status When CPU is in HALT mode
#define DBGMCU_CONTROL3_HALT_DMA_STS    0x800U   // Configure DMA Work Status When CPU is in HALT mode

#endif
