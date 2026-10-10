//###########################################################################
//
// FILE:    hw_memmap.h
//
// TITLE:   Macros defining the memory map of the G32R502.
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
// 1. Part of comments and macro definitions
// 2. Align peripheral base addresses with G32R502 product brief Table 12
//    (section 4.3.3); add manual-name aliases (SPI, CAN, CANFDA, SYSC, etc.)
//
//###########################################################################

#ifndef HW_MEMMAP_H
#define HW_MEMMAP_H

//*****************************************************************************
//
// The following are defines for the base address of the memories and
// peripherals.
//
//*****************************************************************************
#define DCCOMP0_BASE             0x40000000U
#define LINA_BASE                0x40000400U
#define UARTA_BASE               0x40000800U
#define UARTB_BASE               0x40000C00U
#define UARTC_BASE               0x40001000U
#define SPIA_BASE                0x40001400U
#define I2CA_BASE                0x40001800U
#define I2CB_BASE                0x40001C00U
#define PMBUSA_BASE              0x40002000U
#define CANA_BASE                0x40002400U
#define CANFD_BASE               0x40002C00U
#define CANFD_SRAM_BASE          0x40003400U

#define SPI_BASE                 SPIA_BASE
#define CAN_BASE                 CANA_BASE
#define CANFDA_BASE              CANFD_BASE
#define CANFDA_SRAM_BASE         CANFD_SRAM_BASE

#define CANFDA_DRIVER_BASE       CANFD_BASE
#define CANFDA_MSG_RAM_BASE      CANFD_SRAM_BASE

#define WDT_BASE                 0x40010000U
#define NMI_BASE                 0x400100C0U
#define EXTI_BASE                0x40010400U

#define NMIWDT_BASE              NMI_BASE

#define DCS_B0Z1_OTP_BASE        0x0810A000U
#define DCS_B0Z2_OTP_BASE        0x0810A400U
#define DCS_B0Z1_BASE            0x40010800U
#define DCS_B0Z2_BASE            0x40010880U
#define DCS_COMMON_BASE          0x400108E0U
#define DCS_B1Z1_BASE            0x40010A00U
#define DCS_B1Z2_BASE            0x40010A80U

#define CFGSMS_BASE              0x40012800U

#define SYSCTL_BASE              0x40012C00U
#define DMACHSEL_BASE            0x40013000U
#define DEVCFG_BASE              0x40013100U
#define CLKCFG_BASE              0x40013400U
#define CPUSYS_BASE              0x40013600U
#define PERIPHAC_BASE            0x40013800U
#define ROM_PREFETCH_BASE        0x40013C00U
#define ROM_WAIT_BASE            0x40013D00U

#define SYSC_BASE                SYSCTL_BASE

#define ANALOGSUBSYS_BASE        0x40016C00U
#define AS_BASE                  ANALOGSUBSYS_BASE

#define TMR0_BASE                0x40017000U
#define TMR1_BASE                0x40017400U
#define TMR2_BASE                0x40017800U

#define FLASH0CTRL_BASE          0x40017C00U
#define FLASH0ECC_BASE           0x40018200U  // ECC registers at +0x600 from FLASH0CTRL

#define NVMC_BASE                FLASH0CTRL_BASE

#define DMA_BASE                 0x40018400U
#define DMA_CH1_BASE             0x40018440U
#define DMA_CH2_BASE             0x40018480U
#define DMA_CH3_BASE             0x400184C0U
#define DMA_CH4_BASE             0x40018500U
#define DMA_CH5_BASE             0x40018540U
#define DMA_CH6_BASE             0x40018580U
#define DBGMCU_BASE              0xE0059000U

#define QEP1_BASE                0x40020000U
#define CAP1_BASE                0x40020400U
#define CAP2_BASE                0x40020800U
#define CAP3_BASE                0x40020C00U
#define COMP1_BASE               0x40021000U
#define COMP2_BASE               0x40021400U
#define COMP3_BASE               0x40021800U
#define COMP4_BASE               0x40021C00U

#define QEP_BASE                 QEP1_BASE

#define FLB1_BASE                0x40022000U
#define FLB1_LOGICCFG_BASE       0x40022000U
#define FLB1_LOGICCTL_BASE       0x40022200U
#define FLB1_DATAEXCH_BASE       0x40022400U
#define FLB2_BASE                0x40022800U
#define FLB2_LOGICCFG_BASE       0x40022800U
#define FLB2_LOGICCTL_BASE       0x40022A00U
#define FLB2_DATAEXCH_BASE       0x40022C00U
#define FLB3_BASE                0x40023000U
#define FLB3_LOGICCFG_BASE       0x40023000U
#define FLB3_LOGICCTL_BASE       0x40023200U
#define FLB3_DATAEXCH_BASE       0x40023400U
#define FLB4_BASE                0x40023800U
#define FLB4_LOGICCFG_BASE       0x40023800U
#define FLB4_LOGICCTL_BASE       0x40023A00U
#define FLB4_DATAEXCH_BASE       0x40023C00U
#define DACA_BASE                0x40024000U
#define DACB_BASE                0x40024400U

#define GPIOCTRL_BASE            0x40030000U
#define GPIODATA_BASE            0x40030800U
#define GPIODATAREAD_BASE        0x40030900U
#define INPUTXBAR_BASE           0x40030C00U
#define SYNCSOC_BASE             0x40030C80U
#define XBAR_BASE                0x40031000U
#define PWMXBAR_BASE             0x400311C0U
#define FLBXBAR_BASE             0x40031240U
#define OUTPUTXBAR_BASE          0x400312C0U

#define PWM1_BASE                0x50000000U
#define PWM2_BASE                0x50000400U
#define PWM3_BASE                0x50000800U
#define PWM4_BASE                0x50000C00U
#define PWM5_BASE                0x50001000U
#define PWM6_BASE                0x50001400U
#define PWM7_BASE                0x50001800U
#define ADCA_BASE                0x50001C00U
#define ADCARESULT_BASE          0x50001D00U
#define ADCC_BASE                0x50002000U
#define ADCCRESULT_BASE          0x50002100U

#endif
