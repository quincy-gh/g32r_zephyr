//###########################################################################
//
// FILE:    hw_gpio.h
//
// TITLE:   Definitions for the GPIO registers.
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
// 1. Partial comments, macro definitions
// 2. Added some register macro definitions
//
//###########################################################################

#ifndef HW_GPIO_H
#define HW_GPIO_H

//*************************************************************************************************
//
// The following are defines for the GPIO register offsets
//
//*************************************************************************************************
#define GPIO_O_GPACTRL       (0x0*2)     // GPIO A Qualification Sampling Period (GPIO0 to GPIO31)
#define GPIO_O_GPAQSEL1      (0x2*2)     // GPIO A Qualification Type (GPIO0 to GPIO15)
#define GPIO_O_GPAQSEL2      (0x4*2)     // GPIO A Qualification Type (GPIO16 to GPIO31)
#define GPIO_O_GPAMUX1       (0x6*2)     // GPIO A Peripheral Mux (GPIO0 to GPIO15)
#define GPIO_O_GPAMUX2       (0x8*2)     // GPIO A Peripheral Mux (GPIO16 to GPIO31)
#define GPIO_O_GPADIR        (0xA*2)     // GPIO A Direction (GPIO0 to GPIO31)
#define GPIO_O_GPAPUD        (0xC*2)     // GPIO A Pull-Up Disable (GPIO0 to GPIO31)
#define GPIO_O_GPAINV        (0x10*2)    // GPIO A Input Inversion (GPIO0 to GPIO31)
#define GPIO_O_GPAODR        (0x12*2)    // GPIO A Open Drain Output Mode (GPIO0 to GPIO31)
#define GPIO_O_GPAAMSEL      (0x14*2)    // GPIO A Analog Mode Select (GPIO0 to GPIO31)
#define GPIO_O_GPADSEL1      (0x2C)      // GPIO A Driver Capability Select (GPIO0 to GPIO15)
#define GPIO_O_GPADSEL2      (0x30)      // GPIO A Driver Capability Select (GPIO16 to GPIO31)
#define GPIO_O_GPAFEN        (0x34)      // GPIO A Max Output Frequency Enable (GPIO0 to GPIO31)
#define GPIO_O_GPAGMUX1      (0x20*2)    // GPIO A Peripheral Group Mux (GPIO0 to GPIO15)
#define GPIO_O_GPAGMUX2      (0x22*2)    // GPIO A Peripheral Group Mux (GPIO16 to GPIO31)
#define GPIO_O_GPACSEL1      (0x28*2)    // GPIO A Master Core Select (GPIO0 to GPIO7)
#define GPIO_O_GPACSEL2      (0x2A*2)    // GPIO A Master Core Select (GPIO8 to GPIO15)
#define GPIO_O_GPACSEL3      (0x2C*2)    // GPIO A Master Core Select (GPIO16 to GPIO23)
#define GPIO_O_GPACSEL4      (0x2E*2)    // GPIO A Master Core Select (GPIO24 to GPIO31)
#define GPIO_O_GPALOCK       (0x3C*2)    // GPIO A Lock Register (GPIO0 to GPIO31)
#define GPIO_O_GPACR         (0x3E*2)    // GPIO A Lock Commit Register (GPIO0 to GPIO31)
#define GPIO_O_GPBCTRL       (0x40*2)    // GPIO B Qualification Sampling Period (GPIO32 to GPIO59)
#define GPIO_O_GPBQSEL1      (0x42*2)    // GPIO B Qualification Type (GPIO32 to GPIO47)
#define GPIO_O_GPBQSEL2      (0x44*2)    // GPIO B Qualification Type (GPIO48 to GPIO63)
#define GPIO_O_GPBMUX1       (0x46*2)    // GPIO B Peripheral Mux (GPIO32 to GPIO47)
#define GPIO_O_GPBMUX2       (0x48*2)    // GPIO B Peripheral Mux (GPIO48 to GPIO63)
#define GPIO_O_GPBDIR        (0x4A*2)    // GPIO B Direction (GPIO32 to GPIO59)
#define GPIO_O_GPBPUD        (0x4C*2)    // GPIO B Pull-Up Disable (GPIO32 to GPIO59)
#define GPIO_O_GPBINV        (0x50*2)    // GPIO B Input Inversion (GPIO32 to GPIO59)
#define GPIO_O_GPBODR        (0x52*2)    // GPIO B Open Drain Output Mode (GPIO32 to GPIO59)
#define GPIO_O_GPBDSEL1      (0xAC)      // GPIO B Driver capability select (GPIO32 to GPIO47)
#define GPIO_O_GPBDSEL2      (0xB0)      // GPIO B Driver capability select (GPIO48 to GPIO59)
#define GPIO_O_GPBFEN        (0xB4)      // GPIO B Maximum Output Frequency Enable (GPIO32 to GPIO59)
#define GPIO_O_GPBGMUX1      (0x60*2)    // GPIO B Peripheral Group Mux (GPIO32 to GPIO47)
#define GPIO_O_GPBGMUX2      (0x62*2)    // GPIO B Peripheral Group Mux (GPIO48 to GPIO63)
#define GPIO_O_GPBCSEL1      (0x68*2)    // GPIO B Master Core Select (GPIO32 to GPIO39)
#define GPIO_O_GPBCSEL2      (0x6A*2)    // GPIO B Master Core Select (GPIO40 to GPIO47)
#define GPIO_O_GPBCSEL3      (0x6C*2)    // GPIO B Master Core Select (GPIO48 to GPIO55)
#define GPIO_O_GPBCSEL4      (0x6E*2)    // GPIO B Master Core Select (GPIO56 to GPIO63)
#define GPIO_O_GPBLOCK       (0x7C*2)    // GPIO B Lock Register (GPIO32 to GPIO59)
#define GPIO_O_GPBCR         (0x7E*2)    // GPIO B Lock Commit Register (GPIO32 to GPIO59)
#define GPIO_O_GPHCTRL       (0x1C0*2)   // GPIO H Qualification Sampling Period (GPIO224 to GPIO255)
#define GPIO_O_GPHQSEL1      (0x1C2*2)   // GPIO H Qualification Type (GPIO224 to GPIO239)
#define GPIO_O_GPHQSEL2      (0x1C4*2)   // GPIO H Qualification Type (GPIO240 to GPIO255)
#define GPIO_O_GPHPUD        (0x1CC*2)   // GPIO H Pull-Up Disable (GPIO224 to GPIO255)
#define GPIO_O_GPHINV        (0x1D0*2)   // GPIO H Input Inversion (GPIO224 to GPIO255)
#define GPIO_O_GPHAMSEL      (0x1D4*2)   // GPIO H Analog Mode Select (GPIO224 to GPIO255)
#define GPIO_O_GPHLOCK       (0x1FC*2)   // GPIO H Lock Register (GPIO224 to GPIO255)
#define GPIO_O_GPHCR         (0x1FE*2)   // GPIO H Lock Commit Register (GPIO224 to GPIO255)

#define GPIO_O_GPADAT        (0x0*2)     // GPIO A Data Register (GPIO0 to GPIO31)
#define GPIO_O_GPASET        (0x2*2)     // GPIO A Output Set (GPIO0 to GPIO31)
#define GPIO_O_GPACLR        (0x4*2)     // GPIO A Output Clear (GPIO0 to GPIO31)
#define GPIO_O_GPATOGGLE     (0x6*2)     // GPIO A Output Toggle (GPIO0 to GPIO31)
#define GPIO_O_GPBDAT        (0x8*2)     // GPIO B Data Register (GPIO32 to GPIO59)
#define GPIO_O_GPBSET        (0xA*2)     // GPIO B Output Set (GPIO32 to GPIO59)
#define GPIO_O_GPBCLR        (0xC*2)     // GPIO B Output Clear (GPIO32 to GPIO59)
#define GPIO_O_GPBTOGGLE     (0xE*2)     // GPIO B Output Toggle (GPIO32 to GPIO59)
#define GPIO_O_GPHDAT        (0x38*2)    // GPIO H Data Register (GPIO224 to GPIO254)



//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACTRL register
//
//*************************************************************************************************
#define GPIO_GPACTRL_QUALPRD0_S   0U
#define GPIO_GPACTRL_QUALPRD0_M   0xFFU         // GPIO0 to GPIO7 sampling cycle

#define GPIO_GPACTRL_QUALPRD1_S   8U
#define GPIO_GPACTRL_QUALPRD1_M   0xFF00U       // GPIO8 to GPIO15 sampling cycle

#define GPIO_GPACTRL_QUALPRD2_S   16U
#define GPIO_GPACTRL_QUALPRD2_M   0xFF0000U     // GPIO16 to GPIO23 sampling cycle

#define GPIO_GPACTRL_QUALPRD3_S   24U
#define GPIO_GPACTRL_QUALPRD3_M   0xFF000000U   // GPIO24 to GPIO31 sampling cycle


//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAQSEL1 register
//
//*************************************************************************************************
#define GPIO_GPAQSEL1_GPIO0_S    0U
#define GPIO_GPAQSEL1_GPIO0_M    0x3U          // GPIO0 Input type 
#define GPIO_GPAQSEL1_GPIO1_S    2U
#define GPIO_GPAQSEL1_GPIO1_M    0xCU          // GPIO1 Input type 
#define GPIO_GPAQSEL1_GPIO2_S    4U
#define GPIO_GPAQSEL1_GPIO2_M    0x30U         // GPIO2 Input type 
#define GPIO_GPAQSEL1_GPIO3_S    6U
#define GPIO_GPAQSEL1_GPIO3_M    0xC0U         // GPIO3 Input type 
#define GPIO_GPAQSEL1_GPIO4_S    8U
#define GPIO_GPAQSEL1_GPIO4_M    0x300U        // GPIO4 Input type 
#define GPIO_GPAQSEL1_GPIO5_S    10U
#define GPIO_GPAQSEL1_GPIO5_M    0xC00U        // GPIO5 Input type 
#define GPIO_GPAQSEL1_GPIO6_S    12U
#define GPIO_GPAQSEL1_GPIO6_M    0x3000U       // GPIO6 Input type 
#define GPIO_GPAQSEL1_GPIO7_S    14U
#define GPIO_GPAQSEL1_GPIO7_M    0xC000U       // GPIO7 Input type 
#define GPIO_GPAQSEL1_GPIO8_S    16U
#define GPIO_GPAQSEL1_GPIO8_M    0x30000U      // GPIO8 Input type 
#define GPIO_GPAQSEL1_GPIO9_S    18U
#define GPIO_GPAQSEL1_GPIO9_M    0xC0000U      // GPIO9 Input type 
#define GPIO_GPAQSEL1_GPIO10_S   20U
#define GPIO_GPAQSEL1_GPIO10_M   0x300000U     // GPIO10 Input type 
#define GPIO_GPAQSEL1_GPIO11_S   22U
#define GPIO_GPAQSEL1_GPIO11_M   0xC00000U     // GPIO11 Input type 
#define GPIO_GPAQSEL1_GPIO12_S   24U
#define GPIO_GPAQSEL1_GPIO12_M   0x3000000U    // GPIO12 Input type 
#define GPIO_GPAQSEL1_GPIO13_S   26U
#define GPIO_GPAQSEL1_GPIO13_M   0xC000000U    // GPIO13 Input type 
#define GPIO_GPAQSEL1_GPIO14_S   28U
#define GPIO_GPAQSEL1_GPIO14_M   0x30000000U   // GPIO14 Input type 
#define GPIO_GPAQSEL1_GPIO15_S   30U
#define GPIO_GPAQSEL1_GPIO15_M   0xC0000000U   // GPIO15 Input type 

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAQSEL2 register
//
//*************************************************************************************************
#define GPIO_GPAQSEL2_GPIO16_S   0U
#define GPIO_GPAQSEL2_GPIO16_M   0x3U          // GPIO16 Input  type
#define GPIO_GPAQSEL2_GPIO17_S   2U
#define GPIO_GPAQSEL2_GPIO17_M   0xCU          // GPIO17 Input  type
#define GPIO_GPAQSEL2_GPIO18_S   4U
#define GPIO_GPAQSEL2_GPIO18_M   0x30U         // GPIO18 Input  type
#define GPIO_GPAQSEL2_GPIO19_S   6U
#define GPIO_GPAQSEL2_GPIO19_M   0xC0U         // GPIO19 Input  type
#define GPIO_GPAQSEL2_GPIO20_S   8U
#define GPIO_GPAQSEL2_GPIO20_M   0x300U        // GPIO20 Input  type
#define GPIO_GPAQSEL2_GPIO21_S   10U
#define GPIO_GPAQSEL2_GPIO21_M   0xC00U        // GPIO21 Input  type
#define GPIO_GPAQSEL2_GPIO22_S   12U
#define GPIO_GPAQSEL2_GPIO22_M   0x3000U       // GPIO22 Input  type
#define GPIO_GPAQSEL2_GPIO23_S   14U
#define GPIO_GPAQSEL2_GPIO23_M   0xC000U       // GPIO23 Input  type
#define GPIO_GPAQSEL2_GPIO24_S   16U
#define GPIO_GPAQSEL2_GPIO24_M   0x30000U      // GPIO24 Input  type
#define GPIO_GPAQSEL2_GPIO25_S   18U
#define GPIO_GPAQSEL2_GPIO25_M   0xC0000U      // GPIO25 Input  type
#define GPIO_GPAQSEL2_GPIO26_S   20U
#define GPIO_GPAQSEL2_GPIO26_M   0x300000U     // GPIO26 Input  type
#define GPIO_GPAQSEL2_GPIO27_S   22U
#define GPIO_GPAQSEL2_GPIO27_M   0xC00000U     // GPIO27 Input  type
#define GPIO_GPAQSEL2_GPIO28_S   24U
#define GPIO_GPAQSEL2_GPIO28_M   0x3000000U    // GPIO28 Input  type
#define GPIO_GPAQSEL2_GPIO29_S   26U
#define GPIO_GPAQSEL2_GPIO29_M   0xC000000U    // GPIO29 Input  type
#define GPIO_GPAQSEL2_GPIO30_S   28U
#define GPIO_GPAQSEL2_GPIO30_M   0x30000000U   // GPIO30 Input  type
#define GPIO_GPAQSEL2_GPIO31_S   30U
#define GPIO_GPAQSEL2_GPIO31_M   0xC0000000U   // GPIO31 Input  type

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAMUX1 register
//
//*************************************************************************************************
#define GPIO_GPAMUX1_GPIO0_S    0U
#define GPIO_GPAMUX1_GPIO0_M    0x3U          // GPIO0 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO1_S    2U
#define GPIO_GPAMUX1_GPIO1_M    0xCU          // GPIO1 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO2_S    4U
#define GPIO_GPAMUX1_GPIO2_M    0x30U         // GPIO2 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO3_S    6U
#define GPIO_GPAMUX1_GPIO3_M    0xC0U         // GPIO3 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO4_S    8U
#define GPIO_GPAMUX1_GPIO4_M    0x300U        // GPIO4 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO5_S    10U
#define GPIO_GPAMUX1_GPIO5_M    0xC00U        // GPIO5 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO6_S    12U
#define GPIO_GPAMUX1_GPIO6_M    0x3000U       // GPIO6 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO7_S    14U
#define GPIO_GPAMUX1_GPIO7_M    0xC000U       // GPIO7 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO8_S    16U
#define GPIO_GPAMUX1_GPIO8_M    0x30000U      // GPIO8 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO9_S    18U
#define GPIO_GPAMUX1_GPIO9_M    0xC0000U      // GPIO9 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO10_S   20U
#define GPIO_GPAMUX1_GPIO10_M   0x300000U     // GPIO10 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO11_S   22U
#define GPIO_GPAMUX1_GPIO11_M   0xC00000U     // GPIO11 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO12_S   24U
#define GPIO_GPAMUX1_GPIO12_M   0x3000000U    // GPIO12 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO13_S   26U
#define GPIO_GPAMUX1_GPIO13_M   0xC000000U    // GPIO13 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO14_S   28U
#define GPIO_GPAMUX1_GPIO14_M   0x30000000U   // GPIO14 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX1_GPIO15_S   30U
#define GPIO_GPAMUX1_GPIO15_M   0xC0000000U   // GPIO15 peripheral mux configuration in the low 2 bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAMUX2 register
//
//*************************************************************************************************
#define GPIO_GPAMUX2_GPIO16_S   0U
#define GPIO_GPAMUX2_GPIO16_M   0x3U          // GPIO16 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO17_S   2U
#define GPIO_GPAMUX2_GPIO17_M   0xCU          // GPIO17 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO18_S   4U
#define GPIO_GPAMUX2_GPIO18_M   0x30U         // GPIO18 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO19_S   6U
#define GPIO_GPAMUX2_GPIO19_M   0xC0U         // GPIO19 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO20_S   8U
#define GPIO_GPAMUX2_GPIO20_M   0x300U        // GPIO20 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO21_S   10U
#define GPIO_GPAMUX2_GPIO21_M   0xC00U        // GPIO21 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO22_S   12U
#define GPIO_GPAMUX2_GPIO22_M   0x3000U       // GPIO22 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO23_S   14U
#define GPIO_GPAMUX2_GPIO23_M   0xC000U       // GPIO23 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO24_S   16U
#define GPIO_GPAMUX2_GPIO24_M   0x30000U      // GPIO24 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO25_S   18U
#define GPIO_GPAMUX2_GPIO25_M   0xC0000U      // GPIO25 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO26_S   20U
#define GPIO_GPAMUX2_GPIO26_M   0x300000U     // GPIO26 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO27_S   22U
#define GPIO_GPAMUX2_GPIO27_M   0xC00000U     // GPIO27 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO28_S   24U
#define GPIO_GPAMUX2_GPIO28_M   0x3000000U    // GPIO28 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO29_S   26U
#define GPIO_GPAMUX2_GPIO29_M   0xC000000U    // GPIO29 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO30_S   28U
#define GPIO_GPAMUX2_GPIO30_M   0x30000000U   // GPIO30 peripheral mux configuration in the low 2 bits
#define GPIO_GPAMUX2_GPIO31_S   30U
#define GPIO_GPAMUX2_GPIO31_M   0xC0000000U   // GPIO31 peripheral mux configuration in the low 2 bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPADIR register
//
//*************************************************************************************************
#define GPIO_GPADIR_GPIO0    0x1U          // GPIO0 Data direction
#define GPIO_GPADIR_GPIO1    0x2U          // GPIO1 Data direction
#define GPIO_GPADIR_GPIO2    0x4U          // GPIO2 Data direction
#define GPIO_GPADIR_GPIO3    0x8U          // GPIO3 Data direction
#define GPIO_GPADIR_GPIO4    0x10U         // GPIO4 Data direction
#define GPIO_GPADIR_GPIO5    0x20U         // GPIO5 Data direction
#define GPIO_GPADIR_GPIO6    0x40U         // GPIO6 Data direction
#define GPIO_GPADIR_GPIO7    0x80U         // GPIO7 Data direction
#define GPIO_GPADIR_GPIO8    0x100U        // GPIO8 Data direction
#define GPIO_GPADIR_GPIO9    0x200U        // GPIO9 Data direction
#define GPIO_GPADIR_GPIO10   0x400U        // GPIO10 Data direction
#define GPIO_GPADIR_GPIO11   0x800U        // GPIO11 Data direction
#define GPIO_GPADIR_GPIO12   0x1000U       // GPIO12 Data direction
#define GPIO_GPADIR_GPIO13   0x2000U       // GPIO13 Data direction
#define GPIO_GPADIR_GPIO14   0x4000U       // GPIO14 Data direction
#define GPIO_GPADIR_GPIO15   0x8000U       // GPIO15 Data direction
#define GPIO_GPADIR_GPIO16   0x10000U      // GPIO16 Data direction
#define GPIO_GPADIR_GPIO17   0x20000U      // GPIO17 Data direction
#define GPIO_GPADIR_GPIO18   0x40000U      // GPIO18 Data direction
#define GPIO_GPADIR_GPIO19   0x80000U      // GPIO19 Data direction
#define GPIO_GPADIR_GPIO20   0x100000U     // GPIO20 Data direction
#define GPIO_GPADIR_GPIO21   0x200000U     // GPIO21 Data direction
#define GPIO_GPADIR_GPIO22   0x400000U     // GPIO22 Data direction
#define GPIO_GPADIR_GPIO23   0x800000U     // GPIO23 Data direction
#define GPIO_GPADIR_GPIO24   0x1000000U    // GPIO24 Data direction
#define GPIO_GPADIR_GPIO25   0x2000000U    // GPIO25 Data direction
#define GPIO_GPADIR_GPIO26   0x4000000U    // GPIO26 Data direction
#define GPIO_GPADIR_GPIO27   0x8000000U    // GPIO27 Data direction
#define GPIO_GPADIR_GPIO28   0x10000000U   // GPIO28 Data direction
#define GPIO_GPADIR_GPIO29   0x20000000U   // GPIO29 Data direction
#define GPIO_GPADIR_GPIO30   0x40000000U   // GPIO30 Data direction
#define GPIO_GPADIR_GPIO31   0x80000000U   // GPIO31 Data direction

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAPUD register
//
//*************************************************************************************************
#define GPIO_GPAPUD_GPIO0    0x1U          // GPIO0 Pull-up disable
#define GPIO_GPAPUD_GPIO1    0x2U          // GPIO1 Pull-up disable
#define GPIO_GPAPUD_GPIO2    0x4U          // GPIO2 Pull-up disable
#define GPIO_GPAPUD_GPIO3    0x8U          // GPIO3 Pull-up disable
#define GPIO_GPAPUD_GPIO4    0x10U         // GPIO4 Pull-up disable
#define GPIO_GPAPUD_GPIO5    0x20U         // GPIO5 Pull-up disable
#define GPIO_GPAPUD_GPIO6    0x40U         // GPIO6 Pull-up disable
#define GPIO_GPAPUD_GPIO7    0x80U         // GPIO7 Pull-up disable
#define GPIO_GPAPUD_GPIO8    0x100U        // GPIO8 Pull-up disable
#define GPIO_GPAPUD_GPIO9    0x200U        // GPIO9 Pull-up disable
#define GPIO_GPAPUD_GPIO10   0x400U        // GPIO10 Pull-up disable
#define GPIO_GPAPUD_GPIO11   0x800U        // GPIO11 Pull-up disable
#define GPIO_GPAPUD_GPIO12   0x1000U       // GPIO12 Pull-up disable
#define GPIO_GPAPUD_GPIO13   0x2000U       // GPIO13 Pull-up disable
#define GPIO_GPAPUD_GPIO14   0x4000U       // GPIO14 Pull-up disable
#define GPIO_GPAPUD_GPIO15   0x8000U       // GPIO15 Pull-up disable
#define GPIO_GPAPUD_GPIO16   0x10000U      // GPIO16 Pull-up disable
#define GPIO_GPAPUD_GPIO17   0x20000U      // GPIO17 Pull-up disable
#define GPIO_GPAPUD_GPIO18   0x40000U      // GPIO18 Pull-up disable
#define GPIO_GPAPUD_GPIO19   0x80000U      // GPIO19 Pull-up disable
#define GPIO_GPAPUD_GPIO20   0x100000U     // GPIO20 Pull-up disable
#define GPIO_GPAPUD_GPIO21   0x200000U     // GPIO21 Pull-up disable
#define GPIO_GPAPUD_GPIO22   0x400000U     // GPIO22 Pull-up disable
#define GPIO_GPAPUD_GPIO23   0x800000U     // GPIO23 Pull-up disable
#define GPIO_GPAPUD_GPIO24   0x1000000U    // GPIO24 Pull-up disable
#define GPIO_GPAPUD_GPIO25   0x2000000U    // GPIO25 Pull-up disable
#define GPIO_GPAPUD_GPIO26   0x4000000U    // GPIO26 Pull-up disable
#define GPIO_GPAPUD_GPIO27   0x8000000U    // GPIO27 Pull-up disable
#define GPIO_GPAPUD_GPIO28   0x10000000U   // GPIO28 Pull-up disable
#define GPIO_GPAPUD_GPIO29   0x20000000U   // GPIO29 Pull-up disable
#define GPIO_GPAPUD_GPIO30   0x40000000U   // GPIO30 Pull-up disable
#define GPIO_GPAPUD_GPIO31   0x80000000U   // GPIO31 Pull-up disable

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAINV register
//
//*************************************************************************************************
#define GPIO_GPAINV_GPIO0    0x1U          // GPIO0 Input inversion
#define GPIO_GPAINV_GPIO1    0x2U          // GPIO1 Input inversion
#define GPIO_GPAINV_GPIO2    0x4U          // GPIO2 Input inversion
#define GPIO_GPAINV_GPIO3    0x8U          // GPIO3 Input inversion
#define GPIO_GPAINV_GPIO4    0x10U         // GPIO4 Input inversion
#define GPIO_GPAINV_GPIO5    0x20U         // GPIO5 Input inversion
#define GPIO_GPAINV_GPIO6    0x40U         // GPIO6 Input inversion
#define GPIO_GPAINV_GPIO7    0x80U         // GPIO7 Input inversion
#define GPIO_GPAINV_GPIO8    0x100U        // GPIO8 Input inversion
#define GPIO_GPAINV_GPIO9    0x200U        // GPIO9 Input inversion
#define GPIO_GPAINV_GPIO10   0x400U        // GPIO10 Input inversion
#define GPIO_GPAINV_GPIO11   0x800U        // GPIO11 Input inversion
#define GPIO_GPAINV_GPIO12   0x1000U       // GPIO12 Input inversion
#define GPIO_GPAINV_GPIO13   0x2000U       // GPIO13 Input inversion
#define GPIO_GPAINV_GPIO14   0x4000U       // GPIO14 Input inversion
#define GPIO_GPAINV_GPIO15   0x8000U       // GPIO15 Input inversion
#define GPIO_GPAINV_GPIO16   0x10000U      // GPIO16 Input inversion
#define GPIO_GPAINV_GPIO17   0x20000U      // GPIO17 Input inversion
#define GPIO_GPAINV_GPIO18   0x40000U      // GPIO18 Input inversion
#define GPIO_GPAINV_GPIO19   0x80000U      // GPIO19 Input inversion
#define GPIO_GPAINV_GPIO20   0x100000U     // GPIO20 Input inversion
#define GPIO_GPAINV_GPIO21   0x200000U     // GPIO21 Input inversion
#define GPIO_GPAINV_GPIO22   0x400000U     // GPIO22 Input inversion
#define GPIO_GPAINV_GPIO23   0x800000U     // GPIO23 Input inversion
#define GPIO_GPAINV_GPIO24   0x1000000U    // GPIO24 Input inversion
#define GPIO_GPAINV_GPIO25   0x2000000U    // GPIO25 Input inversion
#define GPIO_GPAINV_GPIO26   0x4000000U    // GPIO26 Input inversion
#define GPIO_GPAINV_GPIO27   0x8000000U    // GPIO27 Input inversion
#define GPIO_GPAINV_GPIO28   0x10000000U   // GPIO28 Input inversion
#define GPIO_GPAINV_GPIO29   0x20000000U   // GPIO29 Input inversion
#define GPIO_GPAINV_GPIO30   0x40000000U   // GPIO30 Input inversion
#define GPIO_GPAINV_GPIO31   0x80000000U   // GPIO31 Input inversion

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAODR register
//
//*************************************************************************************************
#define GPIO_GPAODR_GPIO0    0x1U          // GPIO0 Open-drain output mode
#define GPIO_GPAODR_GPIO1    0x2U          // GPIO1 Open-drain output mode
#define GPIO_GPAODR_GPIO2    0x4U          // GPIO2 Open-drain output mode
#define GPIO_GPAODR_GPIO3    0x8U          // GPIO3 Open-drain output mode
#define GPIO_GPAODR_GPIO4    0x10U         // GPIO4 Open-drain output mode
#define GPIO_GPAODR_GPIO5    0x20U         // GPIO5 Open-drain output mode
#define GPIO_GPAODR_GPIO6    0x40U         // GPIO6 Open-drain output mode
#define GPIO_GPAODR_GPIO7    0x80U         // GPIO7 Open-drain output mode
#define GPIO_GPAODR_GPIO8    0x100U        // GPIO8 Open-drain output mode
#define GPIO_GPAODR_GPIO9    0x200U        // GPIO9 Open-drain output mode
#define GPIO_GPAODR_GPIO10   0x400U        // GPIO10 Open-drain output mode
#define GPIO_GPAODR_GPIO11   0x800U        // GPIO11 Open-drain output mode
#define GPIO_GPAODR_GPIO12   0x1000U       // GPIO12 Open-drain output mode
#define GPIO_GPAODR_GPIO13   0x2000U       // GPIO13 Open-drain output mode
#define GPIO_GPAODR_GPIO14   0x4000U       // GPIO14 Open-drain output mode
#define GPIO_GPAODR_GPIO15   0x8000U       // GPIO15 Open-drain output mode
#define GPIO_GPAODR_GPIO16   0x10000U      // GPIO16 Open-drain output mode
#define GPIO_GPAODR_GPIO17   0x20000U      // GPIO17 Open-drain output mode
#define GPIO_GPAODR_GPIO18   0x40000U      // GPIO18 Open-drain output mode
#define GPIO_GPAODR_GPIO19   0x80000U      // GPIO19 Open-drain output mode
#define GPIO_GPAODR_GPIO20   0x100000U     // GPIO20 Open-drain output mode
#define GPIO_GPAODR_GPIO21   0x200000U     // GPIO21 Open-drain output mode
#define GPIO_GPAODR_GPIO22   0x400000U     // GPIO22 Open-drain output mode
#define GPIO_GPAODR_GPIO23   0x800000U     // GPIO23 Open-drain output mode
#define GPIO_GPAODR_GPIO24   0x1000000U    // GPIO24 Open-drain output mode
#define GPIO_GPAODR_GPIO25   0x2000000U    // GPIO25 Open-drain output mode
#define GPIO_GPAODR_GPIO26   0x4000000U    // GPIO26 Open-drain output mode
#define GPIO_GPAODR_GPIO27   0x8000000U    // GPIO27 Open-drain output mode
#define GPIO_GPAODR_GPIO28   0x10000000U   // GPIO28 Open-drain output mode
#define GPIO_GPAODR_GPIO29   0x20000000U   // GPIO29 Open-drain output mode
#define GPIO_GPAODR_GPIO30   0x40000000U   // GPIO30 Open-drain output mode
#define GPIO_GPAODR_GPIO31   0x80000000U   // GPIO31 Open-drain output mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAAMSEL register
//
//*************************************************************************************************
#define GPIO_GPAAMSEL_GPIO22   0x400000U   // Analog mode select for GPIO22
#define GPIO_GPAAMSEL_GPIO23   0x800000U   // Analog mode select for GPIO23

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPADSEL1 register
//
//*************************************************************************************************
#define GPIO_GPADSEL1_GPIO0_S    0U
#define GPIO_GPADSEL1_GPIO0_M    0x3U          // Driver capability select for GPIO0
#define GPIO_GPADSEL1_GPIO1_S    2U
#define GPIO_GPADSEL1_GPIO1_M    0xCU          // Driver capability select for GPIO1
#define GPIO_GPADSEL1_GPIO2_S    4U
#define GPIO_GPADSEL1_GPIO2_M    0x30U         // Driver capability select for GPIO2
#define GPIO_GPADSEL1_GPIO3_S    6U
#define GPIO_GPADSEL1_GPIO3_M    0xC0U         // Driver capability select for GPIO3
#define GPIO_GPADSEL1_GPIO4_S    8U
#define GPIO_GPADSEL1_GPIO4_M    0x300U        // Driver capability select for GPIO4
#define GPIO_GPADSEL1_GPIO5_S    10U
#define GPIO_GPADSEL1_GPIO5_M    0xC00U        // Driver capability select for GPIO5
#define GPIO_GPADSEL1_GPIO6_S    12U
#define GPIO_GPADSEL1_GPIO6_M    0x3000U       // Driver capability select for GPIO6
#define GPIO_GPADSEL1_GPIO7_S    14U
#define GPIO_GPADSEL1_GPIO7_M    0xC000U       // Driver capability select for GPIO7
#define GPIO_GPADSEL1_GPIO8_S    16U
#define GPIO_GPADSEL1_GPIO8_M    0x30000U      // Driver capability select for GPIO8
#define GPIO_GPADSEL1_GPIO9_S    18U
#define GPIO_GPADSEL1_GPIO9_M    0xC0000U      // Driver capability select for GPIO9
#define GPIO_GPADSEL1_GPIO10_S   20U
#define GPIO_GPADSEL1_GPIO10_M   0x300000U     // Driver capability select for GPIO10
#define GPIO_GPADSEL1_GPIO11_S   22U
#define GPIO_GPADSEL1_GPIO11_M   0xC00000U     // Driver capability select for GPIO11
#define GPIO_GPADSEL1_GPIO12_S   24U
#define GPIO_GPADSEL1_GPIO12_M   0x3000000U    // Driver capability select for GPIO12
#define GPIO_GPADSEL1_GPIO13_S   26U
#define GPIO_GPADSEL1_GPIO13_M   0xC000000U    // Driver capability select for GPIO13
#define GPIO_GPADSEL1_GPIO14_S   28U
#define GPIO_GPADSEL1_GPIO14_M   0x30000000U   // Driver capability select for GPIO14
#define GPIO_GPADSEL1_GPIO15_S   30U
#define GPIO_GPADSEL1_GPIO15_M   0xC0000000U   // Driver capability select for GPIO15


//*************************************************************************************************
//
// The following are defines for the bit fields in the GPADSEL2 register
//
//*************************************************************************************************
#define GPIO_GPADSEL2_GPIO16_S   0U
#define GPIO_GPADSEL2_GPIO16_M   0x3U          // Driver capability select for GPIO16
#define GPIO_GPADSEL2_GPIO17_S   2U
#define GPIO_GPADSEL2_GPIO17_M   0xCU          // Driver capability select for GPIO17
#define GPIO_GPADSEL2_GPIO18_S   4U
#define GPIO_GPADSEL2_GPIO18_M   0x30U         // Driver capability select for GPIO18
#define GPIO_GPADSEL2_GPIO19_S   6U
#define GPIO_GPADSEL2_GPIO19_M   0xC0U         // Driver capability select for GPIO19
#define GPIO_GPADSEL2_GPIO20_S   8U
#define GPIO_GPADSEL2_GPIO20_M   0x300U        // Driver capability select for GPIO20
#define GPIO_GPADSEL2_GPIO21_S   10U
#define GPIO_GPADSEL2_GPIO21_M   0xC00U        // Driver capability select for GPIO21
#define GPIO_GPADSEL2_GPIO22_S   12U
#define GPIO_GPADSEL2_GPIO22_M   0x3000U       // Driver capability select for GPIO22
#define GPIO_GPADSEL2_GPIO23_S   14U
#define GPIO_GPADSEL2_GPIO23_M   0xC000U       // Driver capability select for GPIO23
#define GPIO_GPADSEL2_GPIO24_S   16U
#define GPIO_GPADSEL2_GPIO24_M   0x30000U      // Driver capability select for GPIO24
#define GPIO_GPADSEL2_GPIO25_S   18U
#define GPIO_GPADSEL2_GPIO25_M   0xC0000U      // Driver capability select for GPIO25
#define GPIO_GPADSEL2_GPIO26_S   20U
#define GPIO_GPADSEL2_GPIO26_M   0x300000U     // Driver capability select for GPIO26
#define GPIO_GPADSEL2_GPIO27_S   22U
#define GPIO_GPADSEL2_GPIO27_M   0xC00000U     // Driver capability select for GPIO27
#define GPIO_GPADSEL2_GPIO28_S   24U
#define GPIO_GPADSEL2_GPIO28_M   0x3000000U    // Driver capability select for GPIO28
#define GPIO_GPADSEL2_GPIO29_S   26U
#define GPIO_GPADSEL2_GPIO29_M   0xC000000U    // Driver capability select for GPIO29
#define GPIO_GPADSEL2_GPIO30_S   28U
#define GPIO_GPADSEL2_GPIO30_M   0x30000000U   // Driver capability select for GPIO30
#define GPIO_GPADSEL2_GPIO31_S   30U
#define GPIO_GPADSEL2_GPIO31_M   0xC0000000U   // Driver capability select for GPIO31

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAFEN register
//
//*************************************************************************************************
#define GPIO_GPAFEN_GPIO0    0x1U          // GPIO0 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO1    0x2U          // GPIO1 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO2    0x4U          // GPIO2 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO3    0x8U          // GPIO3 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO4    0x10U         // GPIO4 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO5    0x20U         // GPIO5 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO6    0x40U         // GPIO6 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO7    0x80U         // GPIO7 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO8    0x100U        // GPIO8 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO9    0x200U        // GPIO9 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO10   0x400U        // GPIO10 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO11   0x800U        // GPIO11 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO12   0x1000U       // GPIO12 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO13   0x2000U       // GPIO13 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO14   0x4000U       // GPIO14 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO15   0x8000U       // GPIO15 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO16   0x10000U      // GPIO16 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO17   0x20000U      // GPIO17 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO18   0x40000U      // GPIO18 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO19   0x80000U      // GPIO19 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO20   0x100000U     // GPIO20 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO21   0x200000U     // GPIO21 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO22   0x400000U     // GPIO22 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO23   0x800000U     // GPIO23 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO24   0x1000000U    // GPIO24 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO25   0x2000000U    // GPIO25 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO26   0x4000000U    // GPIO26 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO27   0x8000000U    // GPIO27 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO28   0x10000000U   // GPIO28 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO29   0x20000000U   // GPIO29 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO30   0x40000000U   // GPIO30 Maximum Output Frequency Enable
#define GPIO_GPAFEN_GPIO31   0x80000000U   // GPIO31 Maximum Output Frequency Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAGMUX1 register
//
//*************************************************************************************************
#define GPIO_GPAGMUX1_GPIO0_S    0U
#define GPIO_GPAGMUX1_GPIO0_M    0x3U          // GPIO0 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO1_S    2U
#define GPIO_GPAGMUX1_GPIO1_M    0xCU          // GPIO1 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO2_S    4U
#define GPIO_GPAGMUX1_GPIO2_M    0x30U         // GPIO2 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO3_S    6U
#define GPIO_GPAGMUX1_GPIO3_M    0xC0U         // GPIO3 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO4_S    8U
#define GPIO_GPAGMUX1_GPIO4_M    0x300U        // GPIO4 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO5_S    10U
#define GPIO_GPAGMUX1_GPIO5_M    0xC00U        // GPIO5 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO6_S    12U
#define GPIO_GPAGMUX1_GPIO6_M    0x3000U       // GPIO6 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO7_S    14U
#define GPIO_GPAGMUX1_GPIO7_M    0xC000U       // GPIO7 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO8_S    16U
#define GPIO_GPAGMUX1_GPIO8_M    0x30000U      // GPIO8 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO9_S    18U
#define GPIO_GPAGMUX1_GPIO9_M    0xC0000U      // GPIO9 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO10_S   20U
#define GPIO_GPAGMUX1_GPIO10_M   0x300000U     // GPIO10 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO11_S   22U
#define GPIO_GPAGMUX1_GPIO11_M   0xC00000U     // GPIO11 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO12_S   24U
#define GPIO_GPAGMUX1_GPIO12_M   0x3000000U    // GPIO12 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO13_S   26U
#define GPIO_GPAGMUX1_GPIO13_M   0xC000000U    // GPIO13 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO14_S   28U
#define GPIO_GPAGMUX1_GPIO14_M   0x30000000U   // GPIO14 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX1_GPIO15_S   30U
#define GPIO_GPAGMUX1_GPIO15_M   0xC0000000U   // GPIO15 peripheral mux configuration in the High 2 bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAGMUX2 register
//
//*************************************************************************************************
#define GPIO_GPAGMUX2_GPIO16_S   0U
#define GPIO_GPAGMUX2_GPIO16_M   0x3U          //  GPIO16 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO17_S   2U
#define GPIO_GPAGMUX2_GPIO17_M   0xCU          //  GPIO17 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO18_S   4U
#define GPIO_GPAGMUX2_GPIO18_M   0x30U         //  GPIO18 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO19_S   6U
#define GPIO_GPAGMUX2_GPIO19_M   0xC0U         //  GPIO19 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO20_S   8U
#define GPIO_GPAGMUX2_GPIO20_M   0x300U        //  GPIO20 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO21_S   10U
#define GPIO_GPAGMUX2_GPIO21_M   0xC00U        //  GPIO21 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO22_S   12U
#define GPIO_GPAGMUX2_GPIO22_M   0x3000U       //  GPIO22 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO23_S   14U
#define GPIO_GPAGMUX2_GPIO23_M   0xC000U       //  GPIO23 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO24_S   16U
#define GPIO_GPAGMUX2_GPIO24_M   0x30000U      //  GPIO24 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO25_S   18U
#define GPIO_GPAGMUX2_GPIO25_M   0xC0000U      //  GPIO25 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO26_S   20U
#define GPIO_GPAGMUX2_GPIO26_M   0x300000U     //  GPIO26 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO27_S   22U
#define GPIO_GPAGMUX2_GPIO27_M   0xC00000U     //  GPIO27 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO28_S   24U
#define GPIO_GPAGMUX2_GPIO28_M   0x3000000U    //  GPIO28 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO29_S   26U
#define GPIO_GPAGMUX2_GPIO29_M   0xC000000U    //  GPIO29 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO30_S   28U
#define GPIO_GPAGMUX2_GPIO30_M   0x30000000U   //  GPIO30 peripheral mux configuration in the High 2 bits
#define GPIO_GPAGMUX2_GPIO31_S   30U
#define GPIO_GPAGMUX2_GPIO31_M   0xC0000000U   //  GPIO31 peripheral mux configuration in the High 2 bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACSEL1 register
//
//*************************************************************************************************
#define GPIO_GPACSEL1_GPIO0_S   0U
#define GPIO_GPACSEL1_GPIO0_M   0xFU          // GPIO0 Master core select
#define GPIO_GPACSEL1_GPIO1_S   4U
#define GPIO_GPACSEL1_GPIO1_M   0xF0U         // GPIO1 Master core Select
#define GPIO_GPACSEL1_GPIO2_S   8U
#define GPIO_GPACSEL1_GPIO2_M   0xF00U        // GPIO2 Master core Select
#define GPIO_GPACSEL1_GPIO3_S   12U
#define GPIO_GPACSEL1_GPIO3_M   0xF000U       // GPIO3 Master core Select
#define GPIO_GPACSEL1_GPIO4_S   16U
#define GPIO_GPACSEL1_GPIO4_M   0xF0000U      // GPIO4 Master core Select
#define GPIO_GPACSEL1_GPIO5_S   20U
#define GPIO_GPACSEL1_GPIO5_M   0xF00000U     // GPIO5 Master core Select
#define GPIO_GPACSEL1_GPIO6_S   24U
#define GPIO_GPACSEL1_GPIO6_M   0xF000000U    // GPIO6 Master core Select
#define GPIO_GPACSEL1_GPIO7_S   28U
#define GPIO_GPACSEL1_GPIO7_M   0xF0000000U   // GPIO7 Master core Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACSEL2 register
//
//*************************************************************************************************
#define GPIO_GPACSEL2_GPIO8_S    0U
#define GPIO_GPACSEL2_GPIO8_M    0xFU          // GPIO8 Master core Select
#define GPIO_GPACSEL2_GPIO9_S    4U
#define GPIO_GPACSEL2_GPIO9_M    0xF0U         // GPIO9 Master core select
#define GPIO_GPACSEL2_GPIO10_S   8U
#define GPIO_GPACSEL2_GPIO10_M   0xF00U        // GPIO10 Master core select
#define GPIO_GPACSEL2_GPIO11_S   12U
#define GPIO_GPACSEL2_GPIO11_M   0xF000U       // GPIO11 Master core select
#define GPIO_GPACSEL2_GPIO12_S   16U
#define GPIO_GPACSEL2_GPIO12_M   0xF0000U      // GPIO12 Master core select
#define GPIO_GPACSEL2_GPIO13_S   20U
#define GPIO_GPACSEL2_GPIO13_M   0xF00000U     // GPIO13 Master core select
#define GPIO_GPACSEL2_GPIO14_S   24U
#define GPIO_GPACSEL2_GPIO14_M   0xF000000U    // GPIO14 Master core select
#define GPIO_GPACSEL2_GPIO15_S   28U
#define GPIO_GPACSEL2_GPIO15_M   0xF0000000U   // GPIO15 Master core select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACSEL3 register
//
//*************************************************************************************************
#define GPIO_GPACSEL3_GPIO16_S   0U
#define GPIO_GPACSEL3_GPIO16_M   0xFU          // GPIO16 Master core select
#define GPIO_GPACSEL3_GPIO17_S   4U
#define GPIO_GPACSEL3_GPIO17_M   0xF0U         // GPIO17 Master core select
#define GPIO_GPACSEL3_GPIO18_S   8U
#define GPIO_GPACSEL3_GPIO18_M   0xF00U        // GPIO18 Master core select
#define GPIO_GPACSEL3_GPIO19_S   12U
#define GPIO_GPACSEL3_GPIO19_M   0xF000U       // GPIO19 Master core select
#define GPIO_GPACSEL3_GPIO20_S   16U
#define GPIO_GPACSEL3_GPIO20_M   0xF0000U      // GPIO20 Master core select
#define GPIO_GPACSEL3_GPIO21_S   20U
#define GPIO_GPACSEL3_GPIO21_M   0xF00000U     // GPIO21 Master core select
#define GPIO_GPACSEL3_GPIO22_S   24U
#define GPIO_GPACSEL3_GPIO22_M   0xF000000U    // GPIO22 Master core select
#define GPIO_GPACSEL3_GPIO23_S   28U
#define GPIO_GPACSEL3_GPIO23_M   0xF0000000U   // GPIO23 Master core select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACSEL4 register
//
//*************************************************************************************************
#define GPIO_GPACSEL4_GPIO24_S   0U
#define GPIO_GPACSEL4_GPIO24_M   0xFU          // GPIO24 Master core select
#define GPIO_GPACSEL4_GPIO25_S   4U
#define GPIO_GPACSEL4_GPIO25_M   0xF0U         // GPIO25 Master core select
#define GPIO_GPACSEL4_GPIO26_S   8U
#define GPIO_GPACSEL4_GPIO26_M   0xF00U        // GPIO26 Master core select
#define GPIO_GPACSEL4_GPIO27_S   12U
#define GPIO_GPACSEL4_GPIO27_M   0xF000U       // GPIO27 Master core select
#define GPIO_GPACSEL4_GPIO28_S   16U
#define GPIO_GPACSEL4_GPIO28_M   0xF0000U      // GPIO28 Master core select
#define GPIO_GPACSEL4_GPIO29_S   20U
#define GPIO_GPACSEL4_GPIO29_M   0xF00000U     // GPIO29 Master core select
#define GPIO_GPACSEL4_GPIO30_S   24U
#define GPIO_GPACSEL4_GPIO30_M   0xF000000U    // GPIO30 Master core select
#define GPIO_GPACSEL4_GPIO31_S   28U
#define GPIO_GPACSEL4_GPIO31_M   0xF0000000U   // GPIO31 Master core select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPALOCK register
//
//*************************************************************************************************
#define GPIO_GPALOCK_GPIO0    0x1U          // GPIO0 Configuration lock
#define GPIO_GPALOCK_GPIO1    0x2U          // GPIO1 Configuration lock
#define GPIO_GPALOCK_GPIO2    0x4U          // GPIO2 Configuration lock
#define GPIO_GPALOCK_GPIO3    0x8U          // GPIO3 Configuration lock
#define GPIO_GPALOCK_GPIO4    0x10U         // GPIO4 Configuration lock
#define GPIO_GPALOCK_GPIO5    0x20U         // GPIO5 Configuration lock
#define GPIO_GPALOCK_GPIO6    0x40U         // GPIO6 Configuration lock
#define GPIO_GPALOCK_GPIO7    0x80U         // GPIO7 Configuration lock
#define GPIO_GPALOCK_GPIO8    0x100U        // GPIO8 Configuration lock
#define GPIO_GPALOCK_GPIO9    0x200U        // GPIO9 Configuration lock
#define GPIO_GPALOCK_GPIO10   0x400U        // GPIO10 Configuration lock
#define GPIO_GPALOCK_GPIO11   0x800U        // GPIO11 Configuration lock
#define GPIO_GPALOCK_GPIO12   0x1000U       // GPIO12 Configuration lock
#define GPIO_GPALOCK_GPIO13   0x2000U       // GPIO13 Configuration lock
#define GPIO_GPALOCK_GPIO14   0x4000U       // GPIO14 Configuration lock
#define GPIO_GPALOCK_GPIO15   0x8000U       // GPIO15 Configuration lock
#define GPIO_GPALOCK_GPIO16   0x10000U      // GPIO16 Configuration lock
#define GPIO_GPALOCK_GPIO17   0x20000U      // GPIO17 Configuration lock
#define GPIO_GPALOCK_GPIO18   0x40000U      // GPIO18 Configuration lock
#define GPIO_GPALOCK_GPIO19   0x80000U      // GPIO19 Configuration lock
#define GPIO_GPALOCK_GPIO20   0x100000U     // GPIO20 Configuration lock
#define GPIO_GPALOCK_GPIO21   0x200000U     // GPIO21 Configuration lock
#define GPIO_GPALOCK_GPIO22   0x400000U     // GPIO22 Configuration lock
#define GPIO_GPALOCK_GPIO23   0x800000U     // GPIO23 Configuration lock
#define GPIO_GPALOCK_GPIO24   0x1000000U    // GPIO24 Configuration lock
#define GPIO_GPALOCK_GPIO25   0x2000000U    // GPIO25 Configuration lock
#define GPIO_GPALOCK_GPIO26   0x4000000U    // GPIO26 Configuration lock
#define GPIO_GPALOCK_GPIO27   0x8000000U    // GPIO27 Configuration lock
#define GPIO_GPALOCK_GPIO28   0x10000000U   // GPIO28 Configuration lock
#define GPIO_GPALOCK_GPIO29   0x20000000U   // GPIO29 Configuration lock
#define GPIO_GPALOCK_GPIO30   0x40000000U   // GPIO30 Configuration lock
#define GPIO_GPALOCK_GPIO31   0x80000000U   // GPIO31 Configuration lock

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACR register
//
//*************************************************************************************************
#define GPIO_GPACR_GPIO0    0x1U          //  GPIO0 lock is locked
#define GPIO_GPACR_GPIO1    0x2U          //  GPIO1 lock is locked
#define GPIO_GPACR_GPIO2    0x4U          //  GPIO2 lock is locked
#define GPIO_GPACR_GPIO3    0x8U          //  GPIO3 lock is locked
#define GPIO_GPACR_GPIO4    0x10U         //  GPIO4 lock is locked
#define GPIO_GPACR_GPIO5    0x20U         //  GPIO5 lock is locked
#define GPIO_GPACR_GPIO6    0x40U         //  GPIO6 lock is locked
#define GPIO_GPACR_GPIO7    0x80U         //  GPIO7 lock is locked
#define GPIO_GPACR_GPIO8    0x100U        //  GPIO8 lock is locked
#define GPIO_GPACR_GPIO9    0x200U        //  GPIO9 lock is locked
#define GPIO_GPACR_GPIO10   0x400U        //  GPIO10 lock is locked
#define GPIO_GPACR_GPIO11   0x800U        //  GPIO11 lock is locked
#define GPIO_GPACR_GPIO12   0x1000U       //  GPIO12 lock is locked
#define GPIO_GPACR_GPIO13   0x2000U       //  GPIO13 lock is locked
#define GPIO_GPACR_GPIO14   0x4000U       //  GPIO14 lock is locked
#define GPIO_GPACR_GPIO15   0x8000U       //  GPIO15 lock is locked
#define GPIO_GPACR_GPIO16   0x10000U      //  GPIO16 lock is locked
#define GPIO_GPACR_GPIO17   0x20000U      //  GPIO17 lock is locked
#define GPIO_GPACR_GPIO18   0x40000U      //  GPIO18 lock is locked
#define GPIO_GPACR_GPIO19   0x80000U      //  GPIO19 lock is locked
#define GPIO_GPACR_GPIO20   0x100000U     //  GPIO20 lock is locked
#define GPIO_GPACR_GPIO21   0x200000U     //  GPIO21 lock is locked
#define GPIO_GPACR_GPIO22   0x400000U     //  GPIO22 lock is locked
#define GPIO_GPACR_GPIO23   0x800000U     //  GPIO23 lock is locked
#define GPIO_GPACR_GPIO24   0x1000000U    //  GPIO24 lock is locked
#define GPIO_GPACR_GPIO25   0x2000000U    //  GPIO25 lock is locked
#define GPIO_GPACR_GPIO26   0x4000000U    //  GPIO26 lock is locked
#define GPIO_GPACR_GPIO27   0x8000000U    //  GPIO27 lock is locked
#define GPIO_GPACR_GPIO28   0x10000000U   //  GPIO28 lock is locked
#define GPIO_GPACR_GPIO29   0x20000000U   //  GPIO29 lock is locked
#define GPIO_GPACR_GPIO30   0x40000000U   //  GPIO30 lock is locked
#define GPIO_GPACR_GPIO31   0x80000000U   //  GPIO31 lock is locked

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCTRL register
//
//*************************************************************************************************
#define GPIO_GPBCTRL_QUALPRD0_S   0U
#define GPIO_GPBCTRL_QUALPRD0_M   0xFFU         // GPIO32 to GPIO39 sampling cycle

#define GPIO_GPBCTRL_QUALPRD1_S   8U
#define GPIO_GPBCTRL_QUALPRD1_M   0xFF00U       // GPIO40 to GPIO47 sampling cycle

#define GPIO_GPBCTRL_QUALPRD2_S   16U
#define GPIO_GPBCTRL_QUALPRD2_M   0xFF0000U     // GPIO48 to GPIO55 sampling cycle

#define GPIO_GPBCTRL_QUALPRD3_S   24U
#define GPIO_GPBCTRL_QUALPRD3_M   0xFF000000U   // GPIO56 to GPIO59 sampling cycle

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBQSEL1 register
//
//*************************************************************************************************
#define GPIO_GPBQSEL1_GPIO32_S   0U
#define GPIO_GPBQSEL1_GPIO32_M   0x3U          // GPIO32 Input type
#define GPIO_GPBQSEL1_GPIO33_S   2U
#define GPIO_GPBQSEL1_GPIO33_M   0xCU          // GPIO33 Input type
#define GPIO_GPBQSEL1_GPIO34_S   4U
#define GPIO_GPBQSEL1_GPIO34_M   0x30U         // GPIO34 Input type
#define GPIO_GPBQSEL1_GPIO35_S   6U
#define GPIO_GPBQSEL1_GPIO35_M   0xC0U         // GPIO35 Input type
#define GPIO_GPBQSEL1_GPIO37_S   10U
#define GPIO_GPBQSEL1_GPIO37_M   0xC00U        // GPIO37 Input type
#define GPIO_GPBQSEL1_GPIO39_S   14U
#define GPIO_GPBQSEL1_GPIO39_M   0xC000U       // GPIO39 Input type
#define GPIO_GPBQSEL1_GPIO40_S   16U
#define GPIO_GPBQSEL1_GPIO40_M   0x30000U      // GPIO40 Input type
#define GPIO_GPBQSEL1_GPIO41_S   18U
#define GPIO_GPBQSEL1_GPIO41_M   0xC0000U      // GPIO41 Input type
#define GPIO_GPBQSEL1_GPIO42_S   20U
#define GPIO_GPBQSEL1_GPIO42_M   0x300000U     // GPIO42 Input type
#define GPIO_GPBQSEL1_GPIO43_S   22U
#define GPIO_GPBQSEL1_GPIO43_M   0xC00000U     // GPIO43 Input type
#define GPIO_GPBQSEL1_GPIO44_S   24U
#define GPIO_GPBQSEL1_GPIO44_M   0x3000000U    // GPIO44 Input type
#define GPIO_GPBQSEL1_GPIO45_S   26U
#define GPIO_GPBQSEL1_GPIO45_M   0xC000000U    // GPIO45 Input type
#define GPIO_GPBQSEL1_GPIO46_S   28U
#define GPIO_GPBQSEL1_GPIO46_M   0x30000000U   // GPIO46 Input type
#define GPIO_GPBQSEL1_GPIO47_S   30U
#define GPIO_GPBQSEL1_GPIO47_M   0xC0000000U   // GPIO47 Input type

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBQSEL2 register
//
//*************************************************************************************************
#define GPIO_GPBQSEL2_GPIO48_S   0U
#define GPIO_GPBQSEL2_GPIO48_M   0x3U        // GPIO48 Input type
#define GPIO_GPBQSEL2_GPIO49_S   2U
#define GPIO_GPBQSEL2_GPIO49_M   0xCU        // GPIO49 Input type
#define GPIO_GPBQSEL2_GPIO50_S   4U
#define GPIO_GPBQSEL2_GPIO50_M   0x30U       // GPIO50 Input type
#define GPIO_GPBQSEL2_GPIO51_S   6U
#define GPIO_GPBQSEL2_GPIO51_M   0xC0U       // GPIO51 Input type
#define GPIO_GPBQSEL2_GPIO52_S   8U
#define GPIO_GPBQSEL2_GPIO52_M   0x300U      // GPIO52 Input type
#define GPIO_GPBQSEL2_GPIO53_S   10U
#define GPIO_GPBQSEL2_GPIO53_M   0xC00U      // GPIO53 Input type
#define GPIO_GPBQSEL2_GPIO54_S   12U
#define GPIO_GPBQSEL2_GPIO54_M   0x3000U     // GPIO54 Input type
#define GPIO_GPBQSEL2_GPIO55_S   14U
#define GPIO_GPBQSEL2_GPIO55_M   0xC000U     // GPIO55 Input type
#define GPIO_GPBQSEL2_GPIO56_S   16U
#define GPIO_GPBQSEL2_GPIO56_M   0x30000U    // GPIO56 Input type
#define GPIO_GPBQSEL2_GPIO57_S   18U
#define GPIO_GPBQSEL2_GPIO57_M   0xC0000U    // GPIO57 Input type
#define GPIO_GPBQSEL2_GPIO58_S   20U
#define GPIO_GPBQSEL2_GPIO58_M   0x300000U   // GPIO58 Input type
#define GPIO_GPBQSEL2_GPIO59_S   22U
#define GPIO_GPBQSEL2_GPIO59_M   0xC00000U   // GPIO59 Input type

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBMUX1 register
//
//*************************************************************************************************
#define GPIO_GPBMUX1_GPIO32_S   0U
#define GPIO_GPBMUX1_GPIO32_M   0x3U          // GPIO32 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO33_S   2U
#define GPIO_GPBMUX1_GPIO33_M   0xCU          // GPIO33 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO34_S   4U
#define GPIO_GPBMUX1_GPIO34_M   0x30U         // GPIO34 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO35_S   6U
#define GPIO_GPBMUX1_GPIO35_M   0xC0U         // GPIO35 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO37_S   10U
#define GPIO_GPBMUX1_GPIO37_M   0xC00U        // GPIO37 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO39_S   14U
#define GPIO_GPBMUX1_GPIO39_M   0xC000U       // GPIO39 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO40_S   16U
#define GPIO_GPBMUX1_GPIO40_M   0x30000U      // GPIO40 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO41_S   18U
#define GPIO_GPBMUX1_GPIO41_M   0xC0000U      // GPIO41 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO42_S   20U
#define GPIO_GPBMUX1_GPIO42_M   0x300000U     // GPIO42 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO43_S   22U
#define GPIO_GPBMUX1_GPIO43_M   0xC00000U     // GPIO43 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO44_S   24U
#define GPIO_GPBMUX1_GPIO44_M   0x3000000U    // GPIO44 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO45_S   26U
#define GPIO_GPBMUX1_GPIO45_M   0xC000000U    // GPIO45 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO46_S   28U
#define GPIO_GPBMUX1_GPIO46_M   0x30000000U   // GPIO46 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX1_GPIO47_S   30U
#define GPIO_GPBMUX1_GPIO47_M   0xC0000000U   // GPIO47 peripheral mux configuration in the low 2 bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBMUX2 register
//
//*************************************************************************************************
#define GPIO_GPBMUX2_GPIO48_S   0U
#define GPIO_GPBMUX2_GPIO48_M   0x3U        // GPIO48 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX2_GPIO49_S   2U
#define GPIO_GPBMUX2_GPIO49_M   0xCU        // GPIO49 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX2_GPIO50_S   4U
#define GPIO_GPBMUX2_GPIO50_M   0x30U       // GPIO50 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX2_GPIO51_S   6U
#define GPIO_GPBMUX2_GPIO51_M   0xC0U       // GPIO51 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX2_GPIO52_S   8U
#define GPIO_GPBMUX2_GPIO52_M   0x300U      // GPIO52 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX2_GPIO53_S   10U
#define GPIO_GPBMUX2_GPIO53_M   0xC00U      // GPIO53 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX2_GPIO54_S   12U
#define GPIO_GPBMUX2_GPIO54_M   0x3000U     // GPIO54 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX2_GPIO55_S   14U
#define GPIO_GPBMUX2_GPIO55_M   0xC000U     // GPIO55 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX2_GPIO56_S   16U
#define GPIO_GPBMUX2_GPIO56_M   0x30000U    // GPIO56 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX2_GPIO57_S   18U
#define GPIO_GPBMUX2_GPIO57_M   0xC0000U    // GPIO57 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX2_GPIO58_S   20U
#define GPIO_GPBMUX2_GPIO58_M   0x300000U   // GPIO58 peripheral mux configuration in the low 2 bits
#define GPIO_GPBMUX2_GPIO59_S   22U
#define GPIO_GPBMUX2_GPIO59_M   0xC00000U   // GPIO59 peripheral mux configuration in the low 2 bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBDIR register
//
//*************************************************************************************************
#define GPIO_GPBDIR_GPIO32   0x1U         // GPIO32 Data direction
#define GPIO_GPBDIR_GPIO33   0x2U         // GPIO33 Data direction
#define GPIO_GPBDIR_GPIO34   0x4U         // GPIO34 Data direction
#define GPIO_GPBDIR_GPIO35   0x8U         // GPIO35 Data direction
#define GPIO_GPBDIR_GPIO37   0x20U        // GPIO37 Data direction
#define GPIO_GPBDIR_GPIO39   0x80U        // GPIO39 Data direction
#define GPIO_GPBDIR_GPIO40   0x100U       // GPIO40 Data direction
#define GPIO_GPBDIR_GPIO41   0x200U       // GPIO41 Data direction
#define GPIO_GPBDIR_GPIO42   0x400U       // GPIO42 Data direction
#define GPIO_GPBDIR_GPIO43   0x800U       // GPIO43 Data direction
#define GPIO_GPBDIR_GPIO44   0x1000U      // GPIO44 Data direction
#define GPIO_GPBDIR_GPIO45   0x2000U      // GPIO45 Data direction
#define GPIO_GPBDIR_GPIO46   0x4000U      // GPIO46 Data direction
#define GPIO_GPBDIR_GPIO47   0x8000U      // GPIO47 Data direction
#define GPIO_GPBDIR_GPIO48   0x10000U     // GPIO48 Data direction
#define GPIO_GPBDIR_GPIO49   0x20000U     // GPIO49 Data direction
#define GPIO_GPBDIR_GPIO50   0x40000U     // GPIO50 Data direction
#define GPIO_GPBDIR_GPIO51   0x80000U     // GPIO51 Data direction
#define GPIO_GPBDIR_GPIO52   0x100000U    // GPIO52 Data direction
#define GPIO_GPBDIR_GPIO53   0x200000U    // GPIO53 Data direction
#define GPIO_GPBDIR_GPIO54   0x400000U    // GPIO54 Data direction
#define GPIO_GPBDIR_GPIO55   0x800000U    // GPIO55 Data direction
#define GPIO_GPBDIR_GPIO56   0x1000000U   // GPIO56 Data direction
#define GPIO_GPBDIR_GPIO57   0x2000000U   // GPIO57 Data direction
#define GPIO_GPBDIR_GPIO58   0x4000000U   // GPIO58 Data direction
#define GPIO_GPBDIR_GPIO59   0x8000000U   // GPIO59 Data direction

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBPUD register
//
//*************************************************************************************************
#define GPIO_GPBPUD_GPIO32   0x1U         // GPIO32 Pull-up disable
#define GPIO_GPBPUD_GPIO33   0x2U         // GPIO33 Pull-up disable
#define GPIO_GPBPUD_GPIO34   0x4U         // GPIO34 Pull-up disable
#define GPIO_GPBPUD_GPIO35   0x8U         // GPIO35 Pull-up disable
#define GPIO_GPBPUD_GPIO37   0x20U        // GPIO37 Pull-up disable
#define GPIO_GPBPUD_GPIO39   0x80U        // GPIO39 Pull-up disable
#define GPIO_GPBPUD_GPIO40   0x100U       // GPIO40 Pull-up disable
#define GPIO_GPBPUD_GPIO41   0x200U       // GPIO41 Pull-up disable
#define GPIO_GPBPUD_GPIO42   0x400U       // GPIO42 Pull-up disable
#define GPIO_GPBPUD_GPIO43   0x800U       // GPIO43 Pull-up disable
#define GPIO_GPBPUD_GPIO44   0x1000U      // GPIO44 Pull-up disable
#define GPIO_GPBPUD_GPIO45   0x2000U      // GPIO45 Pull-up disable
#define GPIO_GPBPUD_GPIO46   0x4000U      // GPIO46 Pull-up disable
#define GPIO_GPBPUD_GPIO47   0x8000U      // GPIO47 Pull-up disable
#define GPIO_GPBPUD_GPIO48   0x10000U     // GPIO48 Pull-up disable
#define GPIO_GPBPUD_GPIO49   0x20000U     // GPIO49 Pull-up disable
#define GPIO_GPBPUD_GPIO50   0x40000U     // GPIO50 Pull-up disable
#define GPIO_GPBPUD_GPIO51   0x80000U     // GPIO51 Pull-up disable
#define GPIO_GPBPUD_GPIO52   0x100000U    // GPIO52 Pull-up disable
#define GPIO_GPBPUD_GPIO53   0x200000U    // GPIO53 Pull-up disable
#define GPIO_GPBPUD_GPIO54   0x400000U    // GPIO54 Pull-up disable
#define GPIO_GPBPUD_GPIO55   0x800000U    // GPIO55 Pull-up disable
#define GPIO_GPBPUD_GPIO56   0x1000000U   // GPIO56 Pull-up disable
#define GPIO_GPBPUD_GPIO57   0x2000000U   // GPIO57 Pull-up disable
#define GPIO_GPBPUD_GPIO58   0x4000000U   // GPIO58 Pull-up disable
#define GPIO_GPBPUD_GPIO59   0x8000000U   // GPIO59 Pull-up disable

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBINV register
//
//*************************************************************************************************
#define GPIO_GPBINV_GPIO32   0x1U         //GPIO32 Input inversion
#define GPIO_GPBINV_GPIO33   0x2U         //GPIO33 Input inversion
#define GPIO_GPBINV_GPIO34   0x4U         //GPIO34 Input inversion
#define GPIO_GPBINV_GPIO35   0x8U         //GPIO35 Input inversion
#define GPIO_GPBINV_GPIO37   0x20U        //GPIO37 Input inversion
#define GPIO_GPBINV_GPIO39   0x80U        //GPIO39 Input inversion
#define GPIO_GPBINV_GPIO40   0x100U       //GPIO40 Input inversion
#define GPIO_GPBINV_GPIO41   0x200U       //GPIO41 Input inversion
#define GPIO_GPBINV_GPIO42   0x400U       //GPIO42 Input inversion
#define GPIO_GPBINV_GPIO43   0x800U       //GPIO43 Input inversion
#define GPIO_GPBINV_GPIO44   0x1000U      //GPIO44 Input inversion
#define GPIO_GPBINV_GPIO45   0x2000U      //GPIO45 Input inversion
#define GPIO_GPBINV_GPIO46   0x4000U      //GPIO46 Input inversion
#define GPIO_GPBINV_GPIO47   0x8000U      //GPIO47 Input inversion
#define GPIO_GPBINV_GPIO48   0x10000U     //GPIO48 Input inversion
#define GPIO_GPBINV_GPIO49   0x20000U     //GPIO49 Input inversion
#define GPIO_GPBINV_GPIO50   0x40000U     //GPIO50 Input inversion
#define GPIO_GPBINV_GPIO51   0x80000U     //GPIO51 Input inversion
#define GPIO_GPBINV_GPIO52   0x100000U    //GPIO52 Input inversion
#define GPIO_GPBINV_GPIO53   0x200000U    //GPIO53 Input inversion
#define GPIO_GPBINV_GPIO54   0x400000U    //GPIO54 Input inversion
#define GPIO_GPBINV_GPIO55   0x800000U    //GPIO55 Input inversion
#define GPIO_GPBINV_GPIO56   0x1000000U   //GPIO56 Input inversion
#define GPIO_GPBINV_GPIO57   0x2000000U   //GPIO57 Input inversion
#define GPIO_GPBINV_GPIO58   0x4000000U   //GPIO58 Input inversion
#define GPIO_GPBINV_GPIO59   0x8000000U   //GPIO59 Input inversion

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBODR register
//
//*************************************************************************************************
#define GPIO_GPBODR_GPIO32   0x1U         // GPIO32 Open-drain output mode
#define GPIO_GPBODR_GPIO33   0x2U         // GPIO33 Open-drain output mode
#define GPIO_GPBODR_GPIO34   0x4U         // GPIO34 Open-drain output mode
#define GPIO_GPBODR_GPIO35   0x8U         // GPIO35 Open-drain output mode
#define GPIO_GPBODR_GPIO37   0x20U        // GPIO37 Open-drain output mode
#define GPIO_GPBODR_GPIO39   0x80U        // GPIO39 Open-drain output mode
#define GPIO_GPBODR_GPIO40   0x100U       // GPIO40 Open-drain output mode
#define GPIO_GPBODR_GPIO41   0x200U       // GPIO41 Open-drain output mode
#define GPIO_GPBODR_GPIO42   0x400U       // GPIO42 Open-drain output mode
#define GPIO_GPBODR_GPIO43   0x800U       // GPIO43 Open-drain output mode
#define GPIO_GPBODR_GPIO44   0x1000U      // GPIO44 Open-drain output mode
#define GPIO_GPBODR_GPIO45   0x2000U      // GPIO45 Open-drain output mode
#define GPIO_GPBODR_GPIO46   0x4000U      // GPIO46 Open-drain output mode
#define GPIO_GPBODR_GPIO47   0x8000U      // GPIO47 Open-drain output mode
#define GPIO_GPBODR_GPIO48   0x10000U     // GPIO48 Open-drain output mode
#define GPIO_GPBODR_GPIO49   0x20000U     // GPIO49 Open-drain output mode
#define GPIO_GPBODR_GPIO50   0x40000U     // GPIO50 Open-drain output mode
#define GPIO_GPBODR_GPIO51   0x80000U     // GPIO51 Open-drain output mode
#define GPIO_GPBODR_GPIO52   0x100000U    // GPIO52 Open-drain output mode
#define GPIO_GPBODR_GPIO53   0x200000U    // GPIO53 Open-drain output mode
#define GPIO_GPBODR_GPIO54   0x400000U    // GPIO54 Open-drain output mode
#define GPIO_GPBODR_GPIO55   0x800000U    // GPIO55 Open-drain output mode
#define GPIO_GPBODR_GPIO56   0x1000000U   // GPIO56 Open-drain output mode
#define GPIO_GPBODR_GPIO57   0x2000000U   // GPIO57 Open-drain output mode
#define GPIO_GPBODR_GPIO58   0x4000000U   // GPIO58 Open-drain output mode
#define GPIO_GPBODR_GPIO59   0x8000000U   // GPIO59 Open-drain output mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBDSEL1 register
//
//*************************************************************************************************
#define GPIO_GPBDSEL1_GPIO32_S   0U
#define GPIO_GPBDSEL1_GPIO32_M   0x3U          // Driver capability select for GPIO32
#define GPIO_GPBDSEL1_GPIO33_S   2U
#define GPIO_GPBDSEL1_GPIO33_M   0xCU          // Driver capability select for GPIO33
#define GPIO_GPBDSEL1_GPIO34_S   4U
#define GPIO_GPBDSEL1_GPIO34_M   0x30U         // Driver capability select for GPIO34
#define GPIO_GPBDSEL1_GPIO35_S   6U
#define GPIO_GPBDSEL1_GPIO35_M   0xC0U         // Driver capability select for GPIO35
#define GPIO_GPBDSEL1_GPIO37_S   10U
#define GPIO_GPBDSEL1_GPIO37_M   0xC00U        // Driver capability select for GPIO37
#define GPIO_GPBDSEL1_GPIO39_S   14U
#define GPIO_GPBDSEL1_GPIO39_M   0xC000U       // Driver capability select for GPIO39
#define GPIO_GPBDSEL1_GPIO40_S   16U
#define GPIO_GPBDSEL1_GPIO40_M   0x30000U      // Driver capability select for GPIO40
#define GPIO_GPBDSEL1_GPIO41_S   18U
#define GPIO_GPBDSEL1_GPIO41_M   0xC0000U      // Driver capability select for GPIO41
#define GPIO_GPBDSEL1_GPIO42_S   20U
#define GPIO_GPBDSEL1_GPIO42_M   0x300000U     // Driver capability select for GPIO42
#define GPIO_GPBDSEL1_GPIO43_S   22U
#define GPIO_GPBDSEL1_GPIO43_M   0xC00000U     // Driver capability select for GPIO43
#define GPIO_GPBDSEL1_GPIO44_S   24U
#define GPIO_GPBDSEL1_GPIO44_M   0x3000000U    // Driver capability select for GPIO44
#define GPIO_GPBDSEL1_GPIO45_S   26U
#define GPIO_GPBDSEL1_GPIO45_M   0xC000000U    // Driver capability select for GPIO45
#define GPIO_GPBDSEL1_GPIO46_S   28U
#define GPIO_GPBDSEL1_GPIO46_M   0x30000000U   // Driver capability select for GPIO46
#define GPIO_GPBDSEL1_GPIO47_S   30U
#define GPIO_GPBDSEL1_GPIO47_M   0xC0000000U   // Driver capability select for GPIO47

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBDSEL2 register
//
//*************************************************************************************************
#define GPIO_GPBDSEL2_GPIO48_S   0U
#define GPIO_GPBDSEL2_GPIO48_M   0x3U        // Driver capability select for GPIO48
#define GPIO_GPBDSEL2_GPIO49_S   2U
#define GPIO_GPBDSEL2_GPIO49_M   0xCU        // Driver capability select for GPIO49
#define GPIO_GPBDSEL2_GPIO50_S   4U
#define GPIO_GPBDSEL2_GPIO50_M   0x30U       // Driver capability select for GPIO50
#define GPIO_GPBDSEL2_GPIO51_S   6U
#define GPIO_GPBDSEL2_GPIO51_M   0xC0U       // Driver capability select for GPIO51
#define GPIO_GPBDSEL2_GPIO52_S   8U
#define GPIO_GPBDSEL2_GPIO52_M   0x300U      // Driver capability select for GPIO52
#define GPIO_GPBDSEL2_GPIO53_S   10U
#define GPIO_GPBDSEL2_GPIO53_M   0xC00U      // Driver capability select for GPIO53
#define GPIO_GPBDSEL2_GPIO54_S   12U
#define GPIO_GPBDSEL2_GPIO54_M   0x3000U     // Driver capability select for GPIO54
#define GPIO_GPBDSEL2_GPIO55_S   14U
#define GPIO_GPBDSEL2_GPIO55_M   0xC000U     // Driver capability select for GPIO55
#define GPIO_GPBDSEL2_GPIO56_S   16U
#define GPIO_GPBDSEL2_GPIO56_M   0x30000U    // Driver capability select for GPIO56
#define GPIO_GPBDSEL2_GPIO57_S   18U
#define GPIO_GPBDSEL2_GPIO57_M   0xC0000U    // Driver capability select for GPIO57
#define GPIO_GPBDSEL2_GPIO58_S   20U
#define GPIO_GPBDSEL2_GPIO58_M   0x300000U   // Driver capability select for GPIO58
#define GPIO_GPBDSEL2_GPIO59_S   22U
#define GPIO_GPBDSEL2_GPIO59_M   0xC00000U   // Driver capability select for GPIO59

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBFEN register
//
//*************************************************************************************************
#define GPIO_GPBFEN_GPIO32   0x1U         // GPIO32 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO33   0x2U         // GPIO33 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO34   0x4U         // GPIO34 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO35   0x8U         // GPIO35 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO37   0x20U        // GPIO37 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO39   0x80U        // GPIO39 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO40   0x100U       // GPIO40 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO41   0x200U       // GPIO41 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO42   0x400U       // GPIO42 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO43   0x800U       // GPIO43 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO44   0x1000U      // GPIO44 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO45   0x2000U      // GPIO45 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO46   0x4000U      // GPIO46 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO47   0x8000U      // GPIO47 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO48   0x10000U     // GPIO48 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO49   0x20000U     // GPIO49 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO50   0x40000U     // GPIO50 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO51   0x80000U     // GPIO51 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO52   0x100000U    // GPIO52 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO53   0x200000U    // GPIO53 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO54   0x400000U    // GPIO54 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO55   0x800000U    // GPIO55 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO56   0x1000000U   // GPIO56 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO57   0x2000000U   // GPIO57 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO58   0x4000000U   // GPIO58 Maximum Output Frequency Enable
#define GPIO_GPBFEN_GPIO59   0x8000000U   // GPIO59 Maximum Output Frequency Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBGMUX1 register
//
//*************************************************************************************************
#define GPIO_GPBGMUX1_GPIO32_S   0U
#define GPIO_GPBGMUX1_GPIO32_M   0x3U          // GPIO32 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO33_S   2U
#define GPIO_GPBGMUX1_GPIO33_M   0xCU          // GPIO33 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO34_S   4U
#define GPIO_GPBGMUX1_GPIO34_M   0x30U         // GPIO34 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO35_S   6U
#define GPIO_GPBGMUX1_GPIO35_M   0xC0U         // GPIO35 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO37_S   10U
#define GPIO_GPBGMUX1_GPIO37_M   0xC00U        // GPIO37 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO39_S   14U
#define GPIO_GPBGMUX1_GPIO39_M   0xC000U       // GPIO39 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO40_S   16U
#define GPIO_GPBGMUX1_GPIO40_M   0x30000U      // GPIO40 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO41_S   18U
#define GPIO_GPBGMUX1_GPIO41_M   0xC0000U      // GPIO41 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO42_S   20U
#define GPIO_GPBGMUX1_GPIO42_M   0x300000U     // GPIO42 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO43_S   22U
#define GPIO_GPBGMUX1_GPIO43_M   0xC00000U     // GPIO43 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO44_S   24U
#define GPIO_GPBGMUX1_GPIO44_M   0x3000000U    // GPIO44 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO45_S   26U
#define GPIO_GPBGMUX1_GPIO45_M   0xC000000U    // GPIO45 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO46_S   28U
#define GPIO_GPBGMUX1_GPIO46_M   0x30000000U   // GPIO46 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX1_GPIO47_S   30U
#define GPIO_GPBGMUX1_GPIO47_M   0xC0000000U   // GPIO47 peripheral mux configuration in the High 2 bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBGMUX2 register
//
//*************************************************************************************************
#define GPIO_GPBGMUX2_GPIO48_S   0U
#define GPIO_GPBGMUX2_GPIO48_M   0x3U        // GPIO48 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX2_GPIO49_S   2U
#define GPIO_GPBGMUX2_GPIO49_M   0xCU        // GPIO49 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX2_GPIO50_S   4U
#define GPIO_GPBGMUX2_GPIO50_M   0x30U       // GPIO50 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX2_GPIO51_S   6U
#define GPIO_GPBGMUX2_GPIO51_M   0xC0U       // GPIO51 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX2_GPIO52_S   8U
#define GPIO_GPBGMUX2_GPIO52_M   0x300U      // GPIO52 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX2_GPIO53_S   10U
#define GPIO_GPBGMUX2_GPIO53_M   0xC00U      // GPIO53 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX2_GPIO54_S   12U
#define GPIO_GPBGMUX2_GPIO54_M   0x3000U     // GPIO54 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX2_GPIO55_S   14U
#define GPIO_GPBGMUX2_GPIO55_M   0xC000U     // GPIO55 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX2_GPIO56_S   16U
#define GPIO_GPBGMUX2_GPIO56_M   0x30000U    // GPIO56 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX2_GPIO57_S   18U
#define GPIO_GPBGMUX2_GPIO57_M   0xC0000U    // GPIO57 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX2_GPIO58_S   20U
#define GPIO_GPBGMUX2_GPIO58_M   0x300000U   // GPIO58 peripheral mux configuration in the High 2 bits
#define GPIO_GPBGMUX2_GPIO59_S   22U
#define GPIO_GPBGMUX2_GPIO59_M   0xC00000U   // GPIO59 peripheral mux configuration in the High 2 bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL1 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL1_GPIO32_S   0U
#define GPIO_GPBCSEL1_GPIO32_M   0xFU          // GPIO32 Master core select
#define GPIO_GPBCSEL1_GPIO33_S   4U
#define GPIO_GPBCSEL1_GPIO33_M   0xF0U         // GPIO33 Master core select
#define GPIO_GPBCSEL1_GPIO34_S   8U
#define GPIO_GPBCSEL1_GPIO34_M   0xF00U        // GPIO34 Master core select
#define GPIO_GPBCSEL1_GPIO35_S   12U
#define GPIO_GPBCSEL1_GPIO35_M   0xF000U       // GPIO35 Master core select
#define GPIO_GPBCSEL1_GPIO37_S   20U
#define GPIO_GPBCSEL1_GPIO37_M   0xF00000U     // GPIO37 Master core select
#define GPIO_GPBCSEL1_GPIO39_S   28U
#define GPIO_GPBCSEL1_GPIO39_M   0xF0000000U   // GPIO39 Master core select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL2 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL2_GPIO40_S   0U
#define GPIO_GPBCSEL2_GPIO40_M   0xFU          // GPIO40 Master core select
#define GPIO_GPBCSEL2_GPIO41_S   4U
#define GPIO_GPBCSEL2_GPIO41_M   0xF0U         // GPIO41 Master core select
#define GPIO_GPBCSEL2_GPIO42_S   8U
#define GPIO_GPBCSEL2_GPIO42_M   0xF00U        // GPIO42 Master core select
#define GPIO_GPBCSEL2_GPIO43_S   12U
#define GPIO_GPBCSEL2_GPIO43_M   0xF000U       // GPIO43 Master core select
#define GPIO_GPBCSEL2_GPIO44_S   16U
#define GPIO_GPBCSEL2_GPIO44_M   0xF0000U      // GPIO44 Master core select
#define GPIO_GPBCSEL2_GPIO45_S   20U
#define GPIO_GPBCSEL2_GPIO45_M   0xF00000U     // GPIO45 Master core select
#define GPIO_GPBCSEL2_GPIO46_S   24U
#define GPIO_GPBCSEL2_GPIO46_M   0xF000000U    // GPIO46 Master core select
#define GPIO_GPBCSEL2_GPIO47_S   28U
#define GPIO_GPBCSEL2_GPIO47_M   0xF0000000U   // GPIO47 Master core select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL3 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL3_GPIO48_S   0U
#define GPIO_GPBCSEL3_GPIO48_M   0xFU          // GPIO48 Master core select
#define GPIO_GPBCSEL3_GPIO49_S   4U
#define GPIO_GPBCSEL3_GPIO49_M   0xF0U         // GPIO49 Master core select
#define GPIO_GPBCSEL3_GPIO50_S   8U
#define GPIO_GPBCSEL3_GPIO50_M   0xF00U        // GPIO50 Master core select
#define GPIO_GPBCSEL3_GPIO51_S   12U
#define GPIO_GPBCSEL3_GPIO51_M   0xF000U       // GPIO51 Master core select
#define GPIO_GPBCSEL3_GPIO52_S   16U
#define GPIO_GPBCSEL3_GPIO52_M   0xF0000U      // GPIO52 Master core select
#define GPIO_GPBCSEL3_GPIO53_S   20U
#define GPIO_GPBCSEL3_GPIO53_M   0xF00000U     // GPIO53 Master core select
#define GPIO_GPBCSEL3_GPIO54_S   24U
#define GPIO_GPBCSEL3_GPIO54_M   0xF000000U    // GPIO54 Master core select
#define GPIO_GPBCSEL3_GPIO55_S   28U
#define GPIO_GPBCSEL3_GPIO55_M   0xF0000000U   // GPIO55 Master core select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL4 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL4_GPIO56_S   0U
#define GPIO_GPBCSEL4_GPIO56_M   0xFU      // GPIO56 Master core select
#define GPIO_GPBCSEL4_GPIO57_S   4U
#define GPIO_GPBCSEL4_GPIO57_M   0xF0U     // GPIO57 Master core select
#define GPIO_GPBCSEL4_GPIO58_S   8U
#define GPIO_GPBCSEL4_GPIO58_M   0xF00U    // GPIO58 Master core select
#define GPIO_GPBCSEL4_GPIO59_S   12U
#define GPIO_GPBCSEL4_GPIO59_M   0xF000U   // GPIO59 Master core select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBLOCK register
//
//*************************************************************************************************
#define GPIO_GPBLOCK_GPIO32   0x1U         // GPIO32 Configuration lock
#define GPIO_GPBLOCK_GPIO33   0x2U         // GPIO33 Configuration lock
#define GPIO_GPBLOCK_GPIO34   0x4U         // GPIO34 Configuration lock
#define GPIO_GPBLOCK_GPIO35   0x8U         // GPIO35 Configuration lock
#define GPIO_GPBLOCK_GPIO37   0x20U        // GPIO37 Configuration lock
#define GPIO_GPBLOCK_GPIO39   0x80U        // GPIO39 Configuration lock
#define GPIO_GPBLOCK_GPIO40   0x100U       // GPIO40 Configuration lock
#define GPIO_GPBLOCK_GPIO41   0x200U       // GPIO41 Configuration lock
#define GPIO_GPBLOCK_GPIO42   0x400U       // GPIO42 Configuration lock
#define GPIO_GPBLOCK_GPIO43   0x800U       // GPIO43 Configuration lock
#define GPIO_GPBLOCK_GPIO44   0x1000U      // GPIO44 Configuration lock
#define GPIO_GPBLOCK_GPIO45   0x2000U      // GPIO45 Configuration lock
#define GPIO_GPBLOCK_GPIO46   0x4000U      // GPIO46 Configuration lock
#define GPIO_GPBLOCK_GPIO47   0x8000U      // GPIO47 Configuration lock
#define GPIO_GPBLOCK_GPIO48   0x10000U     // GPIO48 Configuration lock
#define GPIO_GPBLOCK_GPIO49   0x20000U     // GPIO49 Configuration lock
#define GPIO_GPBLOCK_GPIO50   0x40000U     // GPIO50 Configuration lock
#define GPIO_GPBLOCK_GPIO51   0x80000U     // GPIO51 Configuration lock
#define GPIO_GPBLOCK_GPIO52   0x100000U    // GPIO52 Configuration lock
#define GPIO_GPBLOCK_GPIO53   0x200000U    // GPIO53 Configuration lock
#define GPIO_GPBLOCK_GPIO54   0x400000U    // GPIO54 Configuration lock
#define GPIO_GPBLOCK_GPIO55   0x800000U    // GPIO55 Configuration lock
#define GPIO_GPBLOCK_GPIO56   0x1000000U   // GPIO56 Configuration lock
#define GPIO_GPBLOCK_GPIO57   0x2000000U   // GPIO57 Configuration lock
#define GPIO_GPBLOCK_GPIO58   0x4000000U   // GPIO58 Configuration lock
#define GPIO_GPBLOCK_GPIO59   0x8000000U   // GPIO59 Configuration lock

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCR register
//
//*************************************************************************************************
#define GPIO_GPBCR_GPIO32   0x1U         // GPIO32 lock is locked
#define GPIO_GPBCR_GPIO33   0x2U         // GPIO33 lock is locked
#define GPIO_GPBCR_GPIO34   0x4U         // GPIO34 lock is locked
#define GPIO_GPBCR_GPIO35   0x8U         // GPIO35 lock is locked
#define GPIO_GPBCR_GPIO37   0x20U        // GPIO37 lock is locked
#define GPIO_GPBCR_GPIO39   0x80U        // GPIO39 lock is locked
#define GPIO_GPBCR_GPIO40   0x100U       // GPIO40 lock is locked
#define GPIO_GPBCR_GPIO41   0x200U       // GPIO41 lock is locked
#define GPIO_GPBCR_GPIO42   0x400U       // GPIO42 lock is locked
#define GPIO_GPBCR_GPIO43   0x800U       // GPIO43 lock is locked
#define GPIO_GPBCR_GPIO44   0x1000U      // GPIO44 lock is locked
#define GPIO_GPBCR_GPIO45   0x2000U      // GPIO45 lock is locked
#define GPIO_GPBCR_GPIO46   0x4000U      // GPIO46 lock is locked
#define GPIO_GPBCR_GPIO47   0x8000U      // GPIO47 lock is locked
#define GPIO_GPBCR_GPIO48   0x10000U     // GPIO48 lock is locked
#define GPIO_GPBCR_GPIO49   0x20000U     // GPIO49 lock is locked
#define GPIO_GPBCR_GPIO50   0x40000U     // GPIO50 lock is locked
#define GPIO_GPBCR_GPIO51   0x80000U     // GPIO51 lock is locked
#define GPIO_GPBCR_GPIO52   0x100000U    // GPIO52 lock is locked
#define GPIO_GPBCR_GPIO53   0x200000U    // GPIO53 lock is locked
#define GPIO_GPBCR_GPIO54   0x400000U    // GPIO54 lock is locked
#define GPIO_GPBCR_GPIO55   0x800000U    // GPIO55 lock is locked
#define GPIO_GPBCR_GPIO56   0x1000000U   // GPIO56 lock is locked
#define GPIO_GPBCR_GPIO57   0x2000000U   // GPIO57 lock is locked
#define GPIO_GPBCR_GPIO58   0x4000000U   // GPIO58 lock is locked
#define GPIO_GPBCR_GPIO59   0x8000000U   // GPIO59 lock is locked

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHCTRL register
//
//*************************************************************************************************
#define GPIO_GPHCTRL_QUALPRD0_S   0U
#define GPIO_GPHCTRL_QUALPRD0_M   0xFFU       // GPIO224 to GPIO231 sampling cycle

#define GPIO_GPHCTRL_QUALPRD1_S   8U
#define GPIO_GPHCTRL_QUALPRD1_M   0xFF00U     // GPIO232 to GPIO239 sampling cycle

#define GPIO_GPHCTRL_QUALPRD2_S   16U
#define GPIO_GPHCTRL_QUALPRD2_M   0xFF0000U   // GPIO240 to GPIO247 sampling cycle

#define GPIO_GPHCTRL_QUALPRD3_S   24U
#define GPIO_GPHCTRL_QUALPRD3_M   0xFF000000U   // GPIO248 to GPIO254 sampling cycle

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHQSEL1 register
//
//*************************************************************************************************
#define GPIO_GPHQSEL1_GPIO224_S   0U
#define GPIO_GPHQSEL1_GPIO224_M   0x3U          // GPIO224 Input  type

#define GPIO_GPHQSEL1_GPIO225_S   2U
#define GPIO_GPHQSEL1_GPIO225_M   0xCU          // GPIO225 Input  type

#define GPIO_GPHQSEL1_GPIO226_S   4U
#define GPIO_GPHQSEL1_GPIO226_M   0x30U         // GPIO226 Input  type

#define GPIO_GPHQSEL1_GPIO227_S   6U
#define GPIO_GPHQSEL1_GPIO227_M   0xC0U         // GPIO227 Input  type

#define GPIO_GPHQSEL1_GPIO228_S   8U
#define GPIO_GPHQSEL1_GPIO228_M   0x300U        // GPIO228 Input  type

#define GPIO_GPHQSEL1_GPIO229_S   10U
#define GPIO_GPHQSEL1_GPIO229_M   0xC00U        // GPIO229 Input  type

#define GPIO_GPHQSEL1_GPIO230_S   12U
#define GPIO_GPHQSEL1_GPIO230_M   0x3000U       // GPIO230 Input  type

#define GPIO_GPHQSEL1_GPIO231_S   14U
#define GPIO_GPHQSEL1_GPIO231_M   0xC000U       // GPIO231 Input  type

#define GPIO_GPHQSEL1_GPIO232_S   16U
#define GPIO_GPHQSEL1_GPIO232_M   0x30000U      // GPIO232 Input  type

#define GPIO_GPHQSEL1_GPIO233_S   18U
#define GPIO_GPHQSEL1_GPIO233_M   0xC0000U      // GPIO233 Input  type

#define GPIO_GPHQSEL1_GPIO234_S   20U
#define GPIO_GPHQSEL1_GPIO234_M   0x300000U     // GPIO234 Input  type

#define GPIO_GPHQSEL1_GPIO235_S   22U
#define GPIO_GPHQSEL1_GPIO235_M   0xC00000U     // GPIO235 Input  type

#define GPIO_GPHQSEL1_GPIO236_S   24U
#define GPIO_GPHQSEL1_GPIO236_M   0x3000000U    // GPIO236 Input  type

#define GPIO_GPHQSEL1_GPIO237_S   26U
#define GPIO_GPHQSEL1_GPIO237_M   0xC000000U    // GPIO237 Input  type

#define GPIO_GPHQSEL1_GPIO238_S   28U
#define GPIO_GPHQSEL1_GPIO238_M   0x30000000U   // GPIO238 Input  type

#define GPIO_GPHQSEL1_GPIO239_S   30U
#define GPIO_GPHQSEL1_GPIO239_M   0xC0000000U   // GPIO239 Input  type

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHQSEL2 register
//
//*************************************************************************************************
#define GPIO_GPHQSEL2_GPIO240_S   0U
#define GPIO_GPHQSEL2_GPIO240_M   0x3U      // GPIO240 Input type
#define GPIO_GPHQSEL2_GPIO241_S   2U
#define GPIO_GPHQSEL2_GPIO241_M   0xCU      // GPIO241 Input type
#define GPIO_GPHQSEL2_GPIO242_S   4U
#define GPIO_GPHQSEL2_GPIO242_M   0x30U     // GPIO242 Input type
#define GPIO_GPHQSEL2_GPIO243_S   6U
#define GPIO_GPHQSEL2_GPIO243_M   0xC0U     // GPIO243 Input type
#define GPIO_GPHQSEL2_GPIO244_S   8U
#define GPIO_GPHQSEL2_GPIO244_M   0x300U    // GPIO244 Input type
#define GPIO_GPHQSEL2_GPIO245_S   10U
#define GPIO_GPHQSEL2_GPIO245_M   0xC00U    // GPIO245 Input type
#define GPIO_GPHQSEL2_GPIO246_S   12U
#define GPIO_GPHQSEL2_GPIO246_M   0x3000U   // GPIO246 Input type
#define GPIO_GPHQSEL2_GPIO247_S   14U
#define GPIO_GPHQSEL2_GPIO247_M   0xC000U   // GPIO247 Input type
#define GPIO_GPHQSEL2_GPIO248_S   16U
#define GPIO_GPHQSEL2_GPIO248_M   0x30000U   // GPIO248 Input type
#define GPIO_GPHQSEL2_GPIO249_S   18U
#define GPIO_GPHQSEL2_GPIO249_M   0xC0000U   // GPIO249 Input type
#define GPIO_GPHQSEL2_GPIO250_S   20U
#define GPIO_GPHQSEL2_GPIO250_M   0x300000U   // GPIO250 Input type
#define GPIO_GPHQSEL2_GPIO251_S   22U
#define GPIO_GPHQSEL2_GPIO251_M   0xC00000U   // GPIO251 Input type
#define GPIO_GPHQSEL2_GPIO252_S   24U
#define GPIO_GPHQSEL2_GPIO252_M   0x3000000U   // GPIO252 Input type
#define GPIO_GPHQSEL2_GPIO253_S   26U
#define GPIO_GPHQSEL2_GPIO253_M   0xC000000U   // GPIO253 Input type
#define GPIO_GPHQSEL2_GPIO254_S   28U
#define GPIO_GPHQSEL2_GPIO254_M   0x30000000U   // GPIO254 Input type

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHPUD register
//
//*************************************************************************************************
#define GPIO_GPHPUD_GPIO224   0x1U        // GPIO224 Pull-up disable
#define GPIO_GPHPUD_GPIO225   0x2U        // GPIO225 Pull-up disable
#define GPIO_GPHPUD_GPIO226   0x4U        // GPIO226 Pull-up disable
#define GPIO_GPHPUD_GPIO227   0x8U        // GPIO227 Pull-up disable
#define GPIO_GPHPUD_GPIO228   0x10U       // GPIO228 Pull-up disable
#define GPIO_GPHPUD_GPIO229   0x20U       // GPIO229 Pull-up disable
#define GPIO_GPHPUD_GPIO230   0x40U       // GPIO230 Pull-up disable
#define GPIO_GPHPUD_GPIO231   0x80U       // GPIO231 Pull-up disable
#define GPIO_GPHPUD_GPIO232   0x100U      // GPIO232 Pull-up disable
#define GPIO_GPHPUD_GPIO233   0x200U      // GPIO233 Pull-up disable
#define GPIO_GPHPUD_GPIO234   0x400U      // GPIO234 Pull-up disable
#define GPIO_GPHPUD_GPIO235   0x800U      // GPIO235 Pull-up disable
#define GPIO_GPHPUD_GPIO236   0x1000U     // GPIO236 Pull-up disable
#define GPIO_GPHPUD_GPIO237   0x2000U     // GPIO237 Pull-up disable
#define GPIO_GPHPUD_GPIO238   0x4000U     // GPIO238 Pull-up disable
#define GPIO_GPHPUD_GPIO239   0x8000U     // GPIO239 Pull-up disable
#define GPIO_GPHPUD_GPIO240   0x10000U    // GPIO240 Pull-up disable
#define GPIO_GPHPUD_GPIO241   0x20000U    // GPIO241 Pull-up disable
#define GPIO_GPHPUD_GPIO242   0x40000U    // GPIO242 Pull-up disable
#define GPIO_GPHPUD_GPIO243   0x80000U    // GPIO243 Pull-up disable
#define GPIO_GPHPUD_GPIO244   0x100000U   // GPIO244 Pull-up disable
#define GPIO_GPHPUD_GPIO245   0x200000U   // GPIO245 Pull-up disable
#define GPIO_GPHPUD_GPIO246   0x400000U   // GPIO246 Pull-up disable
#define GPIO_GPHPUD_GPIO247   0x800000U   // GPIO247 Pull-up disable
#define GPIO_GPHPUD_GPIO248   0x1000000U   // GPIO248 Pull-up disable
#define GPIO_GPHPUD_GPIO249   0x2000000U   // GPIO249 Pull-up disable
#define GPIO_GPHPUD_GPIO250   0x4000000U   // GPIO250 Pull-up disable
#define GPIO_GPHPUD_GPIO251   0x8000000U   // GPIO251 Pull-up disable
#define GPIO_GPHPUD_GPIO252   0x10000000U   // GPIO252 Pull-up disable
#define GPIO_GPHPUD_GPIO253   0x20000000U   // GPIO253 Pull-up disable
#define GPIO_GPHPUD_GPIO254   0x40000000U   // GPIO254 Pull-up disable

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHINV register
//
//*************************************************************************************************
#define GPIO_GPHINV_GPIO224   0x1U        // GPIO224 Input inversion
#define GPIO_GPHINV_GPIO225   0x2U        // GPIO225 Input inversion
#define GPIO_GPHINV_GPIO226   0x4U        // GPIO226 Input inversion
#define GPIO_GPHINV_GPIO227   0x8U        // GPIO227 Input inversion
#define GPIO_GPHINV_GPIO228   0x10U       // GPIO228 Input inversion
#define GPIO_GPHINV_GPIO229   0x20U       // GPIO229 Input inversion
#define GPIO_GPHINV_GPIO230   0x40U       // GPIO230 Input inversion
#define GPIO_GPHINV_GPIO231   0x80U       // GPIO231 Input inversion
#define GPIO_GPHINV_GPIO232   0x100U      // GPIO232 Input inversion
#define GPIO_GPHINV_GPIO233   0x200U      // GPIO233 Input inversion
#define GPIO_GPHINV_GPIO234   0x400U      // GPIO234 Input inversion
#define GPIO_GPHINV_GPIO235   0x800U      // GPIO235 Input inversion
#define GPIO_GPHINV_GPIO236   0x1000U     // GPIO236 Input inversion
#define GPIO_GPHINV_GPIO237   0x2000U     // GPIO237 Input inversion
#define GPIO_GPHINV_GPIO238   0x4000U     // GPIO238 Input inversion
#define GPIO_GPHINV_GPIO239   0x8000U     // GPIO239 Input inversion
#define GPIO_GPHINV_GPIO240   0x10000U    // GPIO240 Input inversion
#define GPIO_GPHINV_GPIO241   0x20000U    // GPIO241 Input inversion
#define GPIO_GPHINV_GPIO242   0x40000U    // GPIO242 Input inversion
#define GPIO_GPHINV_GPIO243   0x80000U    // GPIO243 Input inversion
#define GPIO_GPHINV_GPIO244   0x100000U   // GPIO244 Input inversion
#define GPIO_GPHINV_GPIO245   0x200000U   // GPIO245 Input inversion
#define GPIO_GPHINV_GPIO246   0x400000U   // GPIO246 Input inversion
#define GPIO_GPHINV_GPIO247   0x800000U   // GPIO247 Input inversion
#define GPIO_GPHINV_GPIO248   0x1000000U   // GPIO248 Input inversion
#define GPIO_GPHINV_GPIO249   0x2000000U   // GPIO249 Input inversion
#define GPIO_GPHINV_GPIO250   0x4000000U   // GPIO250 Input inversion
#define GPIO_GPHINV_GPIO251   0x8000000U   // GPIO251 Input inversion
#define GPIO_GPHINV_GPIO252   0x10000000U   // GPIO252 Input inversion
#define GPIO_GPHINV_GPIO253   0x20000000U   // GPIO253 Input inversion
#define GPIO_GPHINV_GPIO254   0x40000000U   // GPIO254 Input inversion

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHAMSEL register
//
//*************************************************************************************************
#define GPIO_GPHAMSEL_GPIO224   0x1U        // Analog mode select for GPIO224
#define GPIO_GPHAMSEL_GPIO225   0x2U        // Analog mode select for GPIO225
#define GPIO_GPHAMSEL_GPIO226   0x4U        // Analog mode select for GPIO226
#define GPIO_GPHAMSEL_GPIO227   0x8U        // Analog mode select for GPIO227
#define GPIO_GPHAMSEL_GPIO228   0x10U       // Analog mode select for GPIO228
#define GPIO_GPHAMSEL_GPIO229   0x20U       // Analog mode select for GPIO229
#define GPIO_GPHAMSEL_GPIO230   0x40U       // Analog mode select for GPIO230
#define GPIO_GPHAMSEL_GPIO231   0x80U       // Analog mode select for GPIO231
#define GPIO_GPHAMSEL_GPIO232   0x100U      // Analog mode select for GPIO232
#define GPIO_GPHAMSEL_GPIO233   0x200U      // Analog mode select for GPIO233
#define GPIO_GPHAMSEL_GPIO234   0x400U      // Analog mode select for GPIO234
#define GPIO_GPHAMSEL_GPIO235   0x800U      // Analog mode select for GPIO235
#define GPIO_GPHAMSEL_GPIO236   0x1000U     // Analog mode select for GPIO236
#define GPIO_GPHAMSEL_GPIO237   0x2000U     // Analog mode select for GPIO237
#define GPIO_GPHAMSEL_GPIO238   0x4000U     // Analog mode select for GPIO238
#define GPIO_GPHAMSEL_GPIO239   0x8000U     // Analog mode select for GPIO239
#define GPIO_GPHAMSEL_GPIO240   0x10000U    // Analog mode select for GPIO240
#define GPIO_GPHAMSEL_GPIO241   0x20000U    // Analog mode select for GPIO241
#define GPIO_GPHAMSEL_GPIO242   0x40000U    // Analog mode select for GPIO242
#define GPIO_GPHAMSEL_GPIO243   0x80000U    // Analog mode select for GPIO243
#define GPIO_GPHAMSEL_GPIO244   0x100000U   // Analog mode select for GPIO244
#define GPIO_GPHAMSEL_GPIO245   0x200000U   // Analog mode select for GPIO245
#define GPIO_GPHAMSEL_GPIO246   0x400000U   // Analog mode select for GPIO246
#define GPIO_GPHAMSEL_GPIO247   0x800000U   // Analog mode select for GPIO247
#define GPIO_GPHAMSEL_GPIO248   0x1000000U   // Analog Mode select for GPIO248
#define GPIO_GPHAMSEL_GPIO249   0x2000000U   // Analog Mode select for GPIO249
#define GPIO_GPHAMSEL_GPIO250   0x4000000U   // Analog Mode select for GPIO250
#define GPIO_GPHAMSEL_GPIO251   0x8000000U   // Analog Mode select for GPIO251
#define GPIO_GPHAMSEL_GPIO252   0x10000000U   // Analog Mode select for GPIO252
#define GPIO_GPHAMSEL_GPIO253   0x20000000U   // Analog Mode select for GPIO253
#define GPIO_GPHAMSEL_GPIO254   0x40000000U   // Analog Mode select for GPIO254


//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHLOCK register
//
//*************************************************************************************************
#define GPIO_GPHLOCK_GPIO224   0x1U        // GPIO224 Configuration lock
#define GPIO_GPHLOCK_GPIO225   0x2U        // GPIO225 Configuration lock
#define GPIO_GPHLOCK_GPIO226   0x4U        // GPIO226 Configuration lock
#define GPIO_GPHLOCK_GPIO227   0x8U        // GPIO227 Configuration lock
#define GPIO_GPHLOCK_GPIO228   0x10U       // GPIO228 Configuration lock
#define GPIO_GPHLOCK_GPIO229   0x20U       // GPIO229 Configuration lock
#define GPIO_GPHLOCK_GPIO230   0x40U       // GPIO230 Configuration lock
#define GPIO_GPHLOCK_GPIO231   0x80U       // GPIO231 Configuration lock
#define GPIO_GPHLOCK_GPIO232   0x100U      // GPIO232 Configuration lock
#define GPIO_GPHLOCK_GPIO233   0x200U      // GPIO233 Configuration lock
#define GPIO_GPHLOCK_GPIO234   0x400U      // GPIO234 Configuration lock
#define GPIO_GPHLOCK_GPIO235   0x800U      // GPIO235 Configuration lock
#define GPIO_GPHLOCK_GPIO236   0x1000U     // GPIO236 Configuration lock
#define GPIO_GPHLOCK_GPIO237   0x2000U     // GPIO237 Configuration lock
#define GPIO_GPHLOCK_GPIO238   0x4000U     // GPIO238 Configuration lock
#define GPIO_GPHLOCK_GPIO239   0x8000U     // GPIO239 Configuration lock
#define GPIO_GPHLOCK_GPIO240   0x10000U    // GPIO240 Configuration lock
#define GPIO_GPHLOCK_GPIO241   0x20000U    // GPIO241 Configuration lock
#define GPIO_GPHLOCK_GPIO242   0x40000U    // GPIO242 Configuration lock
#define GPIO_GPHLOCK_GPIO243   0x80000U    // GPIO243 Configuration lock
#define GPIO_GPHLOCK_GPIO244   0x100000U   // GPIO244 Configuration lock
#define GPIO_GPHLOCK_GPIO245   0x200000U   // GPIO245 Configuration lock
#define GPIO_GPHLOCK_GPIO246   0x400000U   // GPIO246 Configuration lock
#define GPIO_GPHLOCK_GPIO247   0x800000U   // GPIO247 Configuration lock
#define GPIO_GPHLOCK_GPIO248   0x1000000U   // GPIO248 Configuration lock
#define GPIO_GPHLOCK_GPIO249   0x2000000U   // GPIO249 Configuration lock
#define GPIO_GPHLOCK_GPIO250   0x4000000U   // GPIO250 Configuration lock
#define GPIO_GPHLOCK_GPIO251   0x8000000U   // GPIO251 Configuration lock
#define GPIO_GPHLOCK_GPIO252   0x10000000U   // GPIO252 Configuration lock
#define GPIO_GPHLOCK_GPIO253   0x20000000U   // GPIO253 Configuration lock
#define GPIO_GPHLOCK_GPIO254   0x40000000U   // GPIO254 Configuration lock

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHCR register
//
//*************************************************************************************************
#define GPIO_GPHCR_GPIO224   0x1U        // GPIO224 lock is locked
#define GPIO_GPHCR_GPIO225   0x2U        // GPIO225 lock is locked
#define GPIO_GPHCR_GPIO226   0x4U        // GPIO226 lock is locked
#define GPIO_GPHCR_GPIO227   0x8U        // GPIO227 lock is locked
#define GPIO_GPHCR_GPIO228   0x10U       // GPIO228 lock is locked
#define GPIO_GPHCR_GPIO229   0x20U       // GPIO229 lock is locked
#define GPIO_GPHCR_GPIO230   0x40U       // GPIO230 lock is locked
#define GPIO_GPHCR_GPIO231   0x80U       // GPIO231 lock is locked
#define GPIO_GPHCR_GPIO232   0x100U      // GPIO232 lock is locked
#define GPIO_GPHCR_GPIO233   0x200U      // GPIO233 lock is locked
#define GPIO_GPHCR_GPIO234   0x400U      // GPIO234 lock is locked
#define GPIO_GPHCR_GPIO235   0x800U      // GPIO235 lock is locked
#define GPIO_GPHCR_GPIO236   0x1000U     // GPIO236 lock is locked
#define GPIO_GPHCR_GPIO237   0x2000U     // GPIO237 lock is locked
#define GPIO_GPHCR_GPIO238   0x4000U     // GPIO238 lock is locked
#define GPIO_GPHCR_GPIO239   0x8000U     // GPIO239 lock is locked
#define GPIO_GPHCR_GPIO240   0x10000U    // GPIO240 lock is locked
#define GPIO_GPHCR_GPIO241   0x20000U    // GPIO241 lock is locked
#define GPIO_GPHCR_GPIO242   0x40000U    // GPIO242 lock is locked
#define GPIO_GPHCR_GPIO243   0x80000U    // GPIO243 lock is locked
#define GPIO_GPHCR_GPIO244   0x100000U   // GPIO244 lock is locked
#define GPIO_GPHCR_GPIO245   0x200000U   // GPIO245 lock is locked
#define GPIO_GPHCR_GPIO246   0x400000U   // GPIO246 lock is locked
#define GPIO_GPHCR_GPIO247   0x800000U   // GPIO247 lock is locked
#define GPIO_GPHCR_GPIO248   0x1000000U   // GPIO248 lock is locked
#define GPIO_GPHCR_GPIO249   0x2000000U   // GPIO249 lock is locked
#define GPIO_GPHCR_GPIO250   0x4000000U   // GPIO250 lock is locked
#define GPIO_GPHCR_GPIO251   0x8000000U   // GPIO251 lock is locked
#define GPIO_GPHCR_GPIO252   0x10000000U   // GPIO252 lock is locked
#define GPIO_GPHCR_GPIO253   0x20000000U   // GPIO253 lock is locked
#define GPIO_GPHCR_GPIO254   0x40000000U   // GPIO254 lock is locked

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPADAT register
//
//*************************************************************************************************
#define GPIO_GPADAT_GPIO0    0x1U          // GPIO0 Read/Write Data Bit
#define GPIO_GPADAT_GPIO1    0x2U          // GPIO1 Read/Write Data Bit
#define GPIO_GPADAT_GPIO2    0x4U          // GPIO2 Read/Write Data Bit
#define GPIO_GPADAT_GPIO3    0x8U          // GPIO3 Read/Write Data Bit
#define GPIO_GPADAT_GPIO4    0x10U         // GPIO4 Read/Write Data Bit
#define GPIO_GPADAT_GPIO5    0x20U         // GPIO5 Read/Write Data Bit
#define GPIO_GPADAT_GPIO6    0x40U         // GPIO6 Read/Write Data Bit
#define GPIO_GPADAT_GPIO7    0x80U         // GPIO7 Read/Write Data Bit
#define GPIO_GPADAT_GPIO8    0x100U        // GPIO8 Read/Write Data Bit
#define GPIO_GPADAT_GPIO9    0x200U        // GPIO9 Read/Write Data Bit
#define GPIO_GPADAT_GPIO10   0x400U        // GPIO10 Read/Write Data Bit
#define GPIO_GPADAT_GPIO11   0x800U        // GPIO11 Read/Write Data Bit
#define GPIO_GPADAT_GPIO12   0x1000U       // GPIO12 Read/Write Data Bit
#define GPIO_GPADAT_GPIO13   0x2000U       // GPIO13 Read/Write Data Bit
#define GPIO_GPADAT_GPIO14   0x4000U       // GPIO14 Read/Write Data Bit
#define GPIO_GPADAT_GPIO15   0x8000U       // GPIO15 Read/Write Data Bit
#define GPIO_GPADAT_GPIO16   0x10000U      // GPIO16 Read/Write Data Bit
#define GPIO_GPADAT_GPIO17   0x20000U      // GPIO17 Read/Write Data Bit
#define GPIO_GPADAT_GPIO18   0x40000U      // GPIO18 Read/Write Data Bit
#define GPIO_GPADAT_GPIO19   0x80000U      // GPIO19 Read/Write Data Bit
#define GPIO_GPADAT_GPIO20   0x100000U     // GPIO20 Read/Write Data Bit
#define GPIO_GPADAT_GPIO21   0x200000U     // GPIO21 Read/Write Data Bit
#define GPIO_GPADAT_GPIO22   0x400000U     // GPIO22 Read/Write Data Bit
#define GPIO_GPADAT_GPIO23   0x800000U     // GPIO23 Read/Write Data Bit
#define GPIO_GPADAT_GPIO24   0x1000000U    // GPIO24 Read/Write Data Bit
#define GPIO_GPADAT_GPIO25   0x2000000U    // GPIO25 Read/Write Data Bit
#define GPIO_GPADAT_GPIO26   0x4000000U    // GPIO26 Read/Write Data Bit
#define GPIO_GPADAT_GPIO27   0x8000000U    // GPIO27 Read/Write Data Bit
#define GPIO_GPADAT_GPIO28   0x10000000U   // GPIO28 Read/Write Data Bit
#define GPIO_GPADAT_GPIO29   0x20000000U   // GPIO29 Read/Write Data Bit
#define GPIO_GPADAT_GPIO30   0x40000000U   // GPIO30 Read/Write Data Bit
#define GPIO_GPADAT_GPIO31   0x80000000U   // GPIO31 Read/Write Data Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPASET register
//
//*************************************************************************************************
#define GPIO_GPASET_GPIO0    0x1U          // Set the GPIO0 output data latch
#define GPIO_GPASET_GPIO1    0x2U          // Set the GPIO1 output data latch
#define GPIO_GPASET_GPIO2    0x4U          // Set the GPIO2 output data latch
#define GPIO_GPASET_GPIO3    0x8U          // Set the GPIO3 output data latch
#define GPIO_GPASET_GPIO4    0x10U         // Set the GPIO4 output data latch
#define GPIO_GPASET_GPIO5    0x20U         // Set the GPIO5 output data latch
#define GPIO_GPASET_GPIO6    0x40U         // Set the GPIO6 output data latch
#define GPIO_GPASET_GPIO7    0x80U         // Set the GPIO7 output data latch
#define GPIO_GPASET_GPIO8    0x100U        // Set the GPIO8 output data latch
#define GPIO_GPASET_GPIO9    0x200U        // Set the GPIO9 output data latch
#define GPIO_GPASET_GPIO10   0x400U        // Set the GPIO10 output data latch
#define GPIO_GPASET_GPIO11   0x800U        // Set the GPIO11 output data latch
#define GPIO_GPASET_GPIO12   0x1000U       // Set the GPIO12 output data latch
#define GPIO_GPASET_GPIO13   0x2000U       // Set the GPIO13 output data latch
#define GPIO_GPASET_GPIO14   0x4000U       // Set the GPIO14 output data latch
#define GPIO_GPASET_GPIO15   0x8000U       // Set the GPIO15 output data latch
#define GPIO_GPASET_GPIO16   0x10000U      // Set the GPIO16 output data latch
#define GPIO_GPASET_GPIO17   0x20000U      // Set the GPIO17 output data latch
#define GPIO_GPASET_GPIO18   0x40000U      // Set the GPIO18 output data latch
#define GPIO_GPASET_GPIO19   0x80000U      // Set the GPIO19 output data latch
#define GPIO_GPASET_GPIO20   0x100000U     // Set the GPIO20 output data latch
#define GPIO_GPASET_GPIO21   0x200000U     // Set the GPIO21 output data latch
#define GPIO_GPASET_GPIO22   0x400000U     // Set the GPIO22 output data latch
#define GPIO_GPASET_GPIO23   0x800000U     // Set the GPIO23 output data latch
#define GPIO_GPASET_GPIO24   0x1000000U    // Set the GPIO24 output data latch
#define GPIO_GPASET_GPIO25   0x2000000U    // Set the GPIO25 output data latch
#define GPIO_GPASET_GPIO26   0x4000000U    // Set the GPIO26 output data latch
#define GPIO_GPASET_GPIO27   0x8000000U    // Set the GPIO27 output data latch
#define GPIO_GPASET_GPIO28   0x10000000U   // Set the GPIO28 output data latch
#define GPIO_GPASET_GPIO29   0x20000000U   // Set the GPIO29 output data latch
#define GPIO_GPASET_GPIO30   0x40000000U   // Set the GPIO30 output data latch
#define GPIO_GPASET_GPIO31   0x80000000U   // Set the GPIO31 output data latch

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACLR register
//
//*************************************************************************************************
#define GPIO_GPACLR_GPIO0    0x1U          // Clear the GPIO0 output data latch
#define GPIO_GPACLR_GPIO1    0x2U          // Clear the GPIO1 output data latch
#define GPIO_GPACLR_GPIO2    0x4U          // Clear the GPIO2 output data latch
#define GPIO_GPACLR_GPIO3    0x8U          // Clear the GPIO3 output data latch
#define GPIO_GPACLR_GPIO4    0x10U         // Clear the GPIO4 output data latch
#define GPIO_GPACLR_GPIO5    0x20U         // Clear the GPIO5 output data latch
#define GPIO_GPACLR_GPIO6    0x40U         // Clear the GPIO6 output data latch
#define GPIO_GPACLR_GPIO7    0x80U         // Clear the GPIO7 output data latch
#define GPIO_GPACLR_GPIO8    0x100U        // Clear the GPIO8 output data latch
#define GPIO_GPACLR_GPIO9    0x200U        // Clear the GPIO9 output data latch
#define GPIO_GPACLR_GPIO10   0x400U        // Clear the GPIO10 output data latch
#define GPIO_GPACLR_GPIO11   0x800U        // Clear the GPIO11 output data latch
#define GPIO_GPACLR_GPIO12   0x1000U       // Clear the GPIO12 output data latch
#define GPIO_GPACLR_GPIO13   0x2000U       // Clear the GPIO13 output data latch
#define GPIO_GPACLR_GPIO14   0x4000U       // Clear the GPIO14 output data latch
#define GPIO_GPACLR_GPIO15   0x8000U       // Clear the GPIO15 output data latch
#define GPIO_GPACLR_GPIO16   0x10000U      // Clear the GPIO16 output data latch
#define GPIO_GPACLR_GPIO17   0x20000U      // Clear the GPIO17 output data latch
#define GPIO_GPACLR_GPIO18   0x40000U      // Clear the GPIO18 output data latch
#define GPIO_GPACLR_GPIO19   0x80000U      // Clear the GPIO19 output data latch
#define GPIO_GPACLR_GPIO20   0x100000U     // Clear the GPIO20 output data latch
#define GPIO_GPACLR_GPIO21   0x200000U     // Clear the GPIO21 output data latch
#define GPIO_GPACLR_GPIO22   0x400000U     // Clear the GPIO22 output data latch
#define GPIO_GPACLR_GPIO23   0x800000U     // Clear the GPIO23 output data latch
#define GPIO_GPACLR_GPIO24   0x1000000U    // Clear the GPIO24 output data latch
#define GPIO_GPACLR_GPIO25   0x2000000U    // Clear the GPIO25 output data latch
#define GPIO_GPACLR_GPIO26   0x4000000U    // Clear the GPIO26 output data latch
#define GPIO_GPACLR_GPIO27   0x8000000U    // Clear the GPIO27 output data latch
#define GPIO_GPACLR_GPIO28   0x10000000U   // Clear the GPIO28 output data latch
#define GPIO_GPACLR_GPIO29   0x20000000U   // Clear the GPIO29 output data latch
#define GPIO_GPACLR_GPIO30   0x40000000U   // Clear the GPIO30 output data latch
#define GPIO_GPACLR_GPIO31   0x80000000U   // Clear the GPIO31 output data latch

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPATOGGLE register
//
//*************************************************************************************************
#define GPIO_GPATOGGLE_GPIO0    0x1U          // Toggle the GPIO0 output data latch
#define GPIO_GPATOGGLE_GPIO1    0x2U          // Toggle the GPIO1 output data latch
#define GPIO_GPATOGGLE_GPIO2    0x4U          // Toggle the GPIO2 output data latch
#define GPIO_GPATOGGLE_GPIO3    0x8U          // Toggle the GPIO3 output data latch
#define GPIO_GPATOGGLE_GPIO4    0x10U         // Toggle the GPIO4 output data latch
#define GPIO_GPATOGGLE_GPIO5    0x20U         // Toggle the GPIO5 output data latch
#define GPIO_GPATOGGLE_GPIO6    0x40U         // Toggle the GPIO6 output data latch
#define GPIO_GPATOGGLE_GPIO7    0x80U         // Toggle the GPIO7 output data latch
#define GPIO_GPATOGGLE_GPIO8    0x100U        // Toggle the GPIO8 output data latch
#define GPIO_GPATOGGLE_GPIO9    0x200U        // Toggle the GPIO9 output data latch
#define GPIO_GPATOGGLE_GPIO10   0x400U        // Toggle the GPIO10 output data latch
#define GPIO_GPATOGGLE_GPIO11   0x800U        // Toggle the GPIO11 output data latch
#define GPIO_GPATOGGLE_GPIO12   0x1000U       // Toggle the GPIO12 output data latch
#define GPIO_GPATOGGLE_GPIO13   0x2000U       // Toggle the GPIO13 output data latch
#define GPIO_GPATOGGLE_GPIO14   0x4000U       // Toggle the GPIO14 output data latch
#define GPIO_GPATOGGLE_GPIO15   0x8000U       // Toggle the GPIO15 output data latch
#define GPIO_GPATOGGLE_GPIO16   0x10000U      // Toggle the GPIO16 output data latch
#define GPIO_GPATOGGLE_GPIO17   0x20000U      // Toggle the GPIO17 output data latch
#define GPIO_GPATOGGLE_GPIO18   0x40000U      // Toggle the GPIO18 output data latch
#define GPIO_GPATOGGLE_GPIO19   0x80000U      // Toggle the GPIO19 output data latch
#define GPIO_GPATOGGLE_GPIO20   0x100000U     // Toggle the GPIO20 output data latch
#define GPIO_GPATOGGLE_GPIO21   0x200000U     // Toggle the GPIO21 output data latch
#define GPIO_GPATOGGLE_GPIO22   0x400000U     // Toggle the GPIO22 output data latch
#define GPIO_GPATOGGLE_GPIO23   0x800000U     // Toggle the GPIO23 output data latch
#define GPIO_GPATOGGLE_GPIO24   0x1000000U    // Toggle the GPIO24 output data latch
#define GPIO_GPATOGGLE_GPIO25   0x2000000U    // Toggle the GPIO25 output data latch
#define GPIO_GPATOGGLE_GPIO26   0x4000000U    // Toggle the GPIO26 output data latch
#define GPIO_GPATOGGLE_GPIO27   0x8000000U    // Toggle the GPIO27 output data latch
#define GPIO_GPATOGGLE_GPIO28   0x10000000U   // Toggle the GPIO28 output data latch
#define GPIO_GPATOGGLE_GPIO29   0x20000000U   // Toggle the GPIO29 output data latch
#define GPIO_GPATOGGLE_GPIO30   0x40000000U   // Toggle the GPIO30 output data latch
#define GPIO_GPATOGGLE_GPIO31   0x80000000U   // Toggle the GPIO31 output data latch

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBDAT register
//
//*************************************************************************************************
#define GPIO_GPBDAT_GPIO32   0x1U         // GPIO32 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO33   0x2U         // GPIO33 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO34   0x4U         // GPIO34 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO35   0x8U         // GPIO35 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO37   0x20U        // GPIO37 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO39   0x80U        // GPIO39 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO40   0x100U       // GPIO40 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO41   0x200U       // GPIO41 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO42   0x400U       // GPIO42 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO43   0x800U       // GPIO43 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO44   0x1000U      // GPIO44 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO45   0x2000U      // GPIO45 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO46   0x4000U      // GPIO46 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO47   0x8000U      // GPIO47 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO48   0x10000U     // GPIO48 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO49   0x20000U     // GPIO49 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO50   0x40000U     // GPIO50 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO51   0x80000U     // GPIO51 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO52   0x100000U    // GPIO52 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO53   0x200000U    // GPIO53 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO54   0x400000U    // GPIO54 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO55   0x800000U    // GPIO55 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO56   0x1000000U   // GPIO56 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO57   0x2000000U   // GPIO57 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO58   0x4000000U   // GPIO58 Read/Write Data Bit
#define GPIO_GPBDAT_GPIO59   0x8000000U   // GPIO59 Read/Write Data Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBSET register
//
//*************************************************************************************************
#define GPIO_GPBSET_GPIO32   0x1U         // Set the GPIO32 output data latch
#define GPIO_GPBSET_GPIO33   0x2U         // Set the GPIO33 output data latch
#define GPIO_GPBSET_GPIO34   0x4U         // Set the GPIO34 output data latch
#define GPIO_GPBSET_GPIO35   0x8U         // Set the GPIO35 output data latch
#define GPIO_GPBSET_GPIO37   0x20U        // Set the GPIO37 output data latch
#define GPIO_GPBSET_GPIO39   0x80U        // Set the GPIO39 output data latch
#define GPIO_GPBSET_GPIO40   0x100U       // Set the GPIO40 output data latch
#define GPIO_GPBSET_GPIO41   0x200U       // Set the GPIO41 output data latch
#define GPIO_GPBSET_GPIO42   0x400U       // Set the GPIO42 output data latch
#define GPIO_GPBSET_GPIO43   0x800U       // Set the GPIO43 output data latch
#define GPIO_GPBSET_GPIO44   0x1000U      // Set the GPIO44 output data latch
#define GPIO_GPBSET_GPIO45   0x2000U      // Set the GPIO45 output data latch
#define GPIO_GPBSET_GPIO46   0x4000U      // Set the GPIO46 output data latch
#define GPIO_GPBSET_GPIO47   0x8000U      // Set the GPIO47 output data latch
#define GPIO_GPBSET_GPIO48   0x10000U     // Set the GPIO48 output data latch
#define GPIO_GPBSET_GPIO49   0x20000U     // Set the GPIO49 output data latch
#define GPIO_GPBSET_GPIO50   0x40000U     // Set the GPIO50 output data latch
#define GPIO_GPBSET_GPIO51   0x80000U     // Set the GPIO51 output data latch
#define GPIO_GPBSET_GPIO52   0x100000U    // Set the GPIO52 output data latch
#define GPIO_GPBSET_GPIO53   0x200000U    // Set the GPIO53 output data latch
#define GPIO_GPBSET_GPIO54   0x400000U    // Set the GPIO54 output data latch
#define GPIO_GPBSET_GPIO55   0x800000U    // Set the GPIO55 output data latch
#define GPIO_GPBSET_GPIO56   0x1000000U   // Set the GPIO56 output data latch
#define GPIO_GPBSET_GPIO57   0x2000000U   // Set the GPIO57 output data latch
#define GPIO_GPBSET_GPIO58   0x4000000U   // Set the GPIO58 output data latch
#define GPIO_GPBSET_GPIO59   0x8000000U   // Set the GPIO59 output data latch

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCLR register
//
//*************************************************************************************************
#define GPIO_GPBCLR_GPIO32   0x1U         // Clear the GPIO32 output data latch
#define GPIO_GPBCLR_GPIO33   0x2U         // Clear the GPIO33 output data latch
#define GPIO_GPBCLR_GPIO34   0x4U         // Clear the GPIO34 output data latch
#define GPIO_GPBCLR_GPIO35   0x8U         // Clear the GPIO35 output data latch
#define GPIO_GPBCLR_GPIO37   0x20U        // Clear the GPIO37 output data latch
#define GPIO_GPBCLR_GPIO39   0x80U        // Clear the GPIO39 output data latch
#define GPIO_GPBCLR_GPIO40   0x100U       // Clear the GPIO40 output data latch
#define GPIO_GPBCLR_GPIO41   0x200U       // Clear the GPIO41 output data latch
#define GPIO_GPBCLR_GPIO42   0x400U       // Clear the GPIO42 output data latch
#define GPIO_GPBCLR_GPIO43   0x800U       // Clear the GPIO43 output data latch
#define GPIO_GPBCLR_GPIO44   0x1000U      // Clear the GPIO44 output data latch
#define GPIO_GPBCLR_GPIO45   0x2000U      // Clear the GPIO45 output data latch
#define GPIO_GPBCLR_GPIO46   0x4000U      // Clear the GPIO46 output data latch
#define GPIO_GPBCLR_GPIO47   0x8000U      // Clear the GPIO47 output data latch
#define GPIO_GPBCLR_GPIO48   0x10000U     // Clear the GPIO48 output data latch
#define GPIO_GPBCLR_GPIO49   0x20000U     // Clear the GPIO49 output data latch
#define GPIO_GPBCLR_GPIO50   0x40000U     // Clear the GPIO50 output data latch
#define GPIO_GPBCLR_GPIO51   0x80000U     // Clear the GPIO51 output data latch
#define GPIO_GPBCLR_GPIO52   0x100000U    // Clear the GPIO52 output data latch
#define GPIO_GPBCLR_GPIO53   0x200000U    // Clear the GPIO53 output data latch
#define GPIO_GPBCLR_GPIO54   0x400000U    // Clear the GPIO54 output data latch
#define GPIO_GPBCLR_GPIO55   0x800000U    // Clear the GPIO55 output data latch
#define GPIO_GPBCLR_GPIO56   0x1000000U   // Clear the GPIO56 output data latch
#define GPIO_GPBCLR_GPIO57   0x2000000U   // Clear the GPIO57 output data latch
#define GPIO_GPBCLR_GPIO58   0x4000000U   // Clear the GPIO58 output data latch
#define GPIO_GPBCLR_GPIO59   0x8000000U   // Clear the GPIO59 output data latch

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBTOGGLE register
//
//*************************************************************************************************
#define GPIO_GPBTOGGLE_GPIO32   0x1U         // Toggle  the GPIO32 output data latch
#define GPIO_GPBTOGGLE_GPIO33   0x2U         // Toggle  the GPIO33 output data latch
#define GPIO_GPBTOGGLE_GPIO34   0x4U         // Toggle  the GPIO34 output data latch
#define GPIO_GPBTOGGLE_GPIO35   0x8U         // Toggle  the GPIO35 output data latch
#define GPIO_GPBTOGGLE_GPIO37   0x20U        // Toggle  the GPIO37 output data latch
#define GPIO_GPBTOGGLE_GPIO39   0x80U        // Toggle  the GPIO39 output data latch
#define GPIO_GPBTOGGLE_GPIO40   0x100U       // Toggle  the GPIO40 output data latch
#define GPIO_GPBTOGGLE_GPIO41   0x200U       // Toggle  the GPIO41 output data latch
#define GPIO_GPBTOGGLE_GPIO42   0x400U       // Toggle  the GPIO42 output data latch
#define GPIO_GPBTOGGLE_GPIO43   0x800U       // Toggle  the GPIO43 output data latch
#define GPIO_GPBTOGGLE_GPIO44   0x1000U      // Toggle  the GPIO44 output data latch
#define GPIO_GPBTOGGLE_GPIO45   0x2000U      // Toggle  the GPIO45 output data latch
#define GPIO_GPBTOGGLE_GPIO46   0x4000U      // Toggle  the GPIO46 output data latch
#define GPIO_GPBTOGGLE_GPIO47   0x8000U      // Toggle  the GPIO47 output data latch
#define GPIO_GPBTOGGLE_GPIO48   0x10000U     // Toggle  the GPIO48 output data latch
#define GPIO_GPBTOGGLE_GPIO49   0x20000U     // Toggle  the GPIO49 output data latch
#define GPIO_GPBTOGGLE_GPIO50   0x40000U     // Toggle  the GPIO50 output data latch
#define GPIO_GPBTOGGLE_GPIO51   0x80000U     // Toggle  the GPIO51 output data latch
#define GPIO_GPBTOGGLE_GPIO52   0x100000U    // Toggle  the GPIO52 output data latch
#define GPIO_GPBTOGGLE_GPIO53   0x200000U    // Toggle  the GPIO53 output data latch
#define GPIO_GPBTOGGLE_GPIO54   0x400000U    // Toggle  the GPIO54 output data latch
#define GPIO_GPBTOGGLE_GPIO55   0x800000U    // Toggle  the GPIO55 output data latch
#define GPIO_GPBTOGGLE_GPIO56   0x1000000U   // Toggle  the GPIO56 output data latch
#define GPIO_GPBTOGGLE_GPIO57   0x2000000U   // Toggle  the GPIO57 output data latch
#define GPIO_GPBTOGGLE_GPIO58   0x4000000U   // Toggle  the GPIO58 output data latch
#define GPIO_GPBTOGGLE_GPIO59   0x8000000U   // Toggle  the GPIO59 output data latch

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHDAT register
//
//*************************************************************************************************
#define GPIO_GPHDAT_GPIO224   0x1U        // GPIO224 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO225   0x2U        // GPIO225 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO226   0x4U        // GPIO226 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO227   0x8U        // GPIO227 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO228   0x10U       // GPIO228 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO229   0x20U       // GPIO229 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO230   0x40U       // GPIO230 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO231   0x80U       // GPIO231 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO232   0x100U      // GPIO232 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO233   0x200U      // GPIO233 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO234   0x400U      // GPIO234 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO235   0x800U      // GPIO235 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO236   0x1000U     // GPIO236 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO237   0x2000U     // GPIO237 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO238   0x4000U     // GPIO238 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO239   0x8000U     // GPIO239 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO240   0x10000U    // GPIO240 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO241   0x20000U    // GPIO241 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO242   0x40000U    // GPIO242 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO243   0x80000U    // GPIO243 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO244   0x100000U   // GPIO244 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO245   0x200000U   // GPIO245 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO246   0x400000U   // GPIO246 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO247   0x800000U   // GPIO247 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO248   0x1000000U   // GPIO248 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO249   0x2000000U   // GPIO249 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO250   0x4000000U   // GPIO250 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO251   0x8000000U   // GPIO251 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO252   0x10000000U   // GPIO252 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO253   0x20000000U   // GPIO253 Read/Write Data Bit
#define GPIO_GPHDAT_GPIO254   0x40000000U   // GPIO254 Read/Write Data Bit

#endif
