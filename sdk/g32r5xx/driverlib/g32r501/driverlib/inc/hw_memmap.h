//###########################################################################
//
// FILE:    hw_memmap.h
//
// TITLE:   Macros defining the memory map of the G32R501.
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
// 1. Part of comments and macro definitions
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
#define PWM1_BASE                0x40000000U
#define PWM2_BASE                0x40000400U
#define PWM3_BASE                0x40000800U
#define PWM4_BASE                0x40000C00U
#define PWM5_BASE                0x40001000U
#define PWM6_BASE                0x40001400U
#define PWM7_BASE                0x40001800U
#define PWM8_BASE                0x40001C00U
#define CAP1_BASE                0x40002000U
#define CAP2_BASE                0x40002400U
#define CAP3_BASE                0x40002800U
#define CAP4_BASE                0x40002C00U
#define CAP5_BASE                0x40003000U
#define CAP6_BASE                0x40003400U
#define HRCAP6_BASE              0x40003440U
#define CAP7_BASE                0x40003800U
#define HRCAP7_BASE              0x40003840U
#define SDF1_BASE                0x40003C00U

#define COMP1_BASE               0x40011C00U
#define COMP2_BASE               0x40012000U
#define COMP3_BASE               0x40012400U
#define COMP4_BASE               0x40012800U
#define COMP5_BASE               0x40012C00U
#define COMP6_BASE               0x40013000U
#define COMP7_BASE               0x40013400U
#define QEP1_BASE                0x40013800U
#define QEP2_BASE                0x40013C00U

#define ADCA_BASE                0x40020000U
#define ADCB_BASE                0x40020400U
#define ADCC_BASE                0x40020800U
#define ADCARESULT_BASE          0x40020100U
#define ADCBRESULT_BASE          0x40020500U
#define ADCCRESULT_BASE          0x40020900U

#define GPIOCTRL_BASE            0x40030000U
#define GPIODATA_BASE            0x40030800U
#define INPUTXBAR_BASE           0x40030C00U
#define SYNCSOC_BASE             0x40030C80U
#define XBAR_BASE                0x40031000U
#define PWMXBAR_BASE             0x400311C0U
#define FLBXBAR_BASE             0x40031240U
#define OUTPUTXBAR_BASE          0x400312C0U

#define LINA_BASE                0x50000000U
#define UARTA_BASE              0x50000C00U
#define SPIA_BASE                0x50001000U
#define I2CA_BASE                0x50001400U
#define DACA_BASE                0x50001800U
#define DACB_BASE                0x50001C00U
#define CANA_BASE                0x50002000U

#define CFGSMS_BASE              0x50010800U

#define SYSCTL_BASE              0x50020000U
#define DMACHSEL_BASE            0x50020400U
#define DEVCFG_BASE              0x50020500U
#define CLKCFG_BASE              0x50020800U
#define CPUSYS_BASE              0x50020A00U
#define PERIPHAC_BASE            0x50020C00U
#define ROM_PREFETCH_BASE        0x50021000U
#define ROM_WAIT_BASE            0x50021100U

#define DCS_B0Z1_OTP_BASE        0x0810A000U
#define DCS_B0Z2_OTP_BASE        0x0810A400U
#define DCS_B0Z1_BASE            0x50024000U
#define DCS_B0Z2_BASE            0x50024080U
#define DCS_COMMON_BASE          0x500240E0U
#define DCS_B1Z1_BASE            0x50024200U
#define DCS_B1Z2_BASE            0x50024280U
#define QSPI_BASE                0x50026000U
#define WDT_BASE                 0x50026400U
#define NMI_BASE                 0x500264C0U
#define ANALOGSUBSYS_BASE        0x50028000U

#define UARTB_BASE              0x50100000U
#define SPIB_BASE                0x50100400U
#define PMBUSA_BASE              0x50100800U
#define DCCOMP0_BASE             0x50101400U
#define CANB_BASE                0x50101800U

#define FLB1_BASE                0x50102000U
#define FLB1_LOGICCFG_BASE       0x50102000U
#define FLB1_LOGICCTL_BASE       0x50102200U
#define FLB1_DATAEXCH_BASE       0x50102400U
#define FLB2_BASE                0x50102800U
#define FLB2_LOGICCFG_BASE       0x50102800U
#define FLB2_LOGICCTL_BASE       0x50102A00U
#define FLB2_DATAEXCH_BASE       0x50102C00U
#define FLB3_BASE                0x50103000U
#define FLB3_LOGICCFG_BASE       0x50103000U
#define FLB3_LOGICCTL_BASE       0x50103200U
#define FLB3_DATAEXCH_BASE       0x50103400U
#define FLB4_BASE                0x50103800U
#define FLB4_LOGICCFG_BASE       0x50103800U
#define FLB4_LOGICCTL_BASE       0x50103A00U
#define FLB4_DATAEXCH_BASE       0x50103C00U

#define TMR0_BASE                0x50110000U
#define TMR1_BASE                0x50110400U
#define TMR2_BASE                0x50110800U
#define DMA_BASE                 0x50110C00U
#define DMA_CH1_BASE             0x50110C40U
#define DMA_CH2_BASE             0x50110C80U
#define DMA_CH3_BASE             0x50110CC0U
#define DMA_CH4_BASE             0x50110D00U
#define DMA_CH5_BASE             0x50110D40U
#define DMA_CH6_BASE             0x50110D80U
#define EXTI_BASE                0x50111000U
#define FLASH0CTRL_BASE          0x50010000U
#define FLASH0ECC_BASE           0x50010600U
#define DBGMCU_BASE              0xE0059000U

#endif
