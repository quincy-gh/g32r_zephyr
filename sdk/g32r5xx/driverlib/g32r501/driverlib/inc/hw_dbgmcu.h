//###########################################################################
//
// FILE:    hw_dbgmcu.h
//
// TITLE:   Definitions for the DBGMCU registers.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
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
#define DBGMCU_O_APB1CFG0        0x30U   // CPU0 APB1 Debug MCU configuration register
#define DBGMCU_O_APB1CFG1        0x34U   // CPU1 APB1 Debug MCU configuration register
#define DBGMCU_O_APB2CFG0        0x38U   // CPU0 APB2 Debug MCU configuration register
#define DBGMCU_O_APB2CFG1        0x3CU   // CPU1 APB2 Debug MCU configuration register
#define DBGMCU_O_AHB1CFG0        0x40U   // CPU0 AHB1 Debug MCU configuration register
#define DBGMCU_O_AHB1CFG1        0x44U   // CPU1 AHB1 Debug MCU configuration register


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
#define DBGMCU_CTRL_HALT_GTS_STOP0       0x40U         // The global timestamp is stop when CPU0 enters HALT mode
#define DBGMCU_CTRL_HALT_GTS_STOP1       0x80U         // The global timestamp is stop when CPU1 enters HALT mode
#define DBGMCU_CTRL_HALT_INT_REP0        0x10000U      // The global timestamp is stop when CPU0 enters HALT mode
#define DBGMCU_CTRL_HALT_INT_REP1        0x20000U      // The global timestamp is stop when CPU1 enters HALT mode
#define DBGMCU_CTRL_REAL_INT0            0x40000U      // Interrupt run cannot enter HALT when CPU0 in real-time mode
#define DBGMCU_CTRL_REAL_INT1            0x80000U      // CPU1 Interrupt Run Mode
#define DBGMCU_CTRL_TRGIODIRSEL          0x10000000U   // TRGIO direction select

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBGMCU_APB1CFG0 register
//
//*************************************************************************************************
#define DBGMCU_APB1CFG0_HALT_PWM1_STS0    0x1U         // Configure PWM1 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_PWM2_STS0    0x2U         // Configure PWM2 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_PWM3_STS0    0x4U         // Configure PWM3 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_PWM4_STS0    0x8U         // Configure PWM4 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_PWM5_STS0    0x10U        // Configure PWM5 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_PWM6_STS0    0x20U        // Configure PWM6 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_PWM7_STS0    0x40U        // Configure PWM7 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_PWM8_STS0    0x80U        // Configure PWM8 Work Status When CPU0 is in HALT mode

#define DBGMCU_APB1CFG0_HALT_CAP1_STS0    0x100U       // Configure CAP1 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_CAP2_STS0    0x200U       // Configure CAP2 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_CAP3_STS0    0x400U       // Configure CAP3 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_CAP4_STS0    0x800U       // Configure CAP4 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_CAP5_STS0    0x1000U      // Configure CAP5 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_CAP6_STS0    0x2000U      // Configure CAP6 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_CAP7_STS0    0x4000U      // Configure CAP7 Work Status When CPU0 is in HALT mode

#define DBGMCU_APB1CFG0_HALT_COMP1_STS0   0x10000U     // Configure COMP1 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_COMP2_STS0   0x20000U     // Configure COMP2 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_COMP3_STS0   0x40000U     // Configure COMP3 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_COMP4_STS0   0x80000U     // Configure COMP4 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_COMP5_STS0   0x100000U    // Configure COMP5 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_COMP6_STS0   0x200000U    // Configure COMP6 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_COMP7_STS0   0x400000U    // Configure COMP7 Work Status When CPU0 is in HALT mode

#define DBGMCU_APB1CFG0_HALT_QEP1_STS0    0x1000000U   // Configure QEP1 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB1CFG0_HALT_QEP2_STS0    0x2000000U   // Configure QEP2 Work Status When CPU0 is in HALT mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBGMCU_APB1CFG1 register
//
//*************************************************************************************************
#define DBGMCU_APB1CFG1_HALT_PWM1_STS1    0x1U         // Configure PWM1 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_PWM2_STS1    0x2U         // Configure PWM2 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_PWM3_STS1    0x4U         // Configure PWM3 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_PWM4_STS1    0x8U         // Configure PWM4 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_PWM5_STS1    0x10U        // Configure PWM5 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_PWM6_STS1    0x20U        // Configure PWM6 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_PWM7_STS1    0x40U        // Configure PWM7 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_PWM8_STS1    0x80U        // Configure PWM8 Work Status When CPU1 is in HALT mode

#define DBGMCU_APB1CFG1_HALT_CAP1_STS1    0x100U       // Configure CAP1 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_CAP2_STS1    0x200U       // Configure CAP2 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_CAP3_STS1    0x400U       // Configure CAP3 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_CAP4_STS1    0x800U       // Configure CAP4 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_CAP5_STS1    0x1000U      // Configure CAP5 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_CAP6_STS1    0x2000U      // Configure CAP6 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_CAP7_STS1    0x4000U      // Configure CAP7 Work Status When CPU1 is in HALT mode

#define DBGMCU_APB1CFG1_HALT_COMP1_STS1   0x10000U     // Configure COMP1 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_COMP2_STS1   0x20000U     // Configure COMP2 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_COMP3_STS1   0x40000U     // Configure COMP3 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_COMP4_STS1   0x80000U     // Configure COMP4 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_COMP5_STS1   0x100000U    // Configure COMP5 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_COMP6_STS1   0x200000U    // Configure COMP6 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_COMP7_STS1   0x400000U    // Configure COMP7 Work Status When CPU1 is in HALT mode

#define DBGMCU_APB1CFG1_HALT_QEP1_STS1    0x1000000U   // Configure QEP1 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB1CFG1_HALT_QEP2_STS1    0x2000000U   // Configure QEP2 Work Status When CPU1 is in HALT mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBGMCU_APB2CFG0 register
//
//*************************************************************************************************
#define DBGMCU_APB2CFG0_HALT_LINA_STS0       0x1U       // Configure LINA Work Status When CPU0 is in HALT mode
#define DBGMCU_APB2CFG0_HALT_UARTA_STS0      0x2U       // Configure UARTA Work Status When CPU0 is in HALT mode
#define DBGMCU_APB2CFG0_HALT_SPIA_STS0       0x4U       // Configure SPIA Work Status When CPU0 is in HALT mode
#define DBGMCU_APB2CFG0_HALT_I2CA_STS0       0x8U       // Configure I2CA Work Status When CPU0 is in HALT mode
#define DBGMCU_APB2CFG0_HALT_CANA_STS0       0x10U      // Configure CANA Work Status When CPU0 is in HALT mode
#define DBGMCU_APB2CFG0_HALT_UARTB_STS0      0x200U     // Configure UARTB Work Status When CPU0 is in HALT mode
#define DBGMCU_APB2CFG0_HALT_SPIB_STS0       0x400U     // Configure SPIB Work Status When CPU0 is in HALT mode
#define DBGMCU_APB2CFG0_HALT_CANB_STS0       0x1000U    // Configure CANB Work Status When CPU0 is in HALT mode
#define DBGMCU_APB2CFG0_HALT_FLB1_STS0       0x10000U   // Configure FLB1 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB2CFG0_HALT_FLB2_STS0       0x20000U   // Configure FLB2 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB2CFG0_HALT_FLB3_STS0       0x40000U   // Configure FLB3 Work Status When CPU0 is in HALT mode
#define DBGMCU_APB2CFG0_HALT_FLB4_STS0       0x80000U   // Configure FLB4 Work Status When CPU0 is in HALT mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBGMCU_APB2CFG1 register
//
//*************************************************************************************************
#define DBGMCU_APB2CFG1_HALT_LINA_STS1       0x1U       // Configure LINA Work Status When CPU1 is in HALT mode
#define DBGMCU_APB2CFG1_HALT_UARTA_STS1      0x2U       // Configure UARTA Work Status When CPU1 is in HALT mode
#define DBGMCU_APB2CFG1_HALT_SPIA_STS1       0x4U       // Configure SPIA Work Status When CPU1 is in HALT mode
#define DBGMCU_APB2CFG1_HALT_I2CA_STS1       0x8U       // Configure I2CA Work Status When CPU1 is in HALT mode
#define DBGMCU_APB2CFG1_HALT_CANA_STS1       0x10U      // Configure CANA Work Status When CPU1 is in HALT mode
#define DBGMCU_APB2CFG1_HALT_UARTB_STS1      0x200U     // Configure UARTB Work Status When CPU1 is in HALT mode
#define DBGMCU_APB2CFG1_HALT_SPIB_STS1       0x400U     // Configure SPIB Work Status When CPU1 is in HALT mode
#define DBGMCU_APB2CFG1_HALT_CANB_STS1       0x1000U    // Configure CANB Work Status When CPU1 is in HALT mode
#define DBGMCU_APB2CFG1_HALT_FLB1_STS1       0x10000U   // Configure FLB1 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB2CFG1_HALT_FLB2_STS1       0x20000U   // Configure FLB2 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB2CFG1_HALT_FLB3_STS1       0x40000U   // Configure FLB3 Work Status When CPU1 is in HALT mode
#define DBGMCU_APB2CFG1_HALT_FLB4_STS1       0x80000U   // Configure FLB4 Work Status When CPU1 is in HALT mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBGMCU_AHB1CFG0 register
//
//*************************************************************************************************
#define DBGMCU_AHB1CFG0_HALT_WDT_STS0    0x1U     // Configure WDT Work Status When CPU0 is in HALT mode
#define DBGMCU_AHB1CFG0_HALT_TMR0_STS0   0x100U   // Configure TMR0 Work Status When CPU0 is in HALT mode
#define DBGMCU_AHB1CFG0_HALT_TMR1_STS0   0x200U   // Configure TMR1 Work Status When CPU0 is in HALT mode
#define DBGMCU_AHB1CFG0_HALT_TMR2_STS0   0x400U   // Configure TMR2 Work Status When CPU0 is in HALT mode
#define DBGMCU_AHB1CFG0_HALT_DMA_STS0    0x800U   // Configure DMA Work Status When CPU0 is in HALT mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBGMCU_AHB1CFG1 register
//
//*************************************************************************************************
#define DBGMCU_AHB1CFG1_HALT_WDT_STS1    0x1U     // Configure WDT Work Status When CPU1 is in HALT mode
#define DBGMCU_AHB1CFG1_HALT_TMR0_STS1   0x100U   // Configure TMR0 Work Status When CPU1 is in HALT mode
#define DBGMCU_AHB1CFG1_HALT_TMR1_STS1   0x200U   // Configure TMR1 Work Status When CPU1 is in HALT mode
#define DBGMCU_AHB1CFG1_HALT_TMR2_STS1   0x400U   // Configure TMR2 Work Status When CPU1 is in HALT mode
#define DBGMCU_AHB1CFG1_HALT_DMA_STS1    0x800U   // Configure DMA Work Status When CPU1 is in HALT mode

#endif
