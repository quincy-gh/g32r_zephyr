//###########################################################################
//
// FILE:    hw_ints.h
//
// TITLE:   Definitions of interrupt numbers for use with interrupt.c.
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

#ifndef HW_INTS_H
#define HW_INTS_H

//*****************************************************************************
//
// NVIC Exception Numbers
//
//*****************************************************************************
#define INT_NMI                 (-14) // Non-Maskable Interrupt Exception
#define INT_HARD_FAULT          (-13) // Hard Fault Exception
#define INT_MEM_MANAGE          (-12) // Memory Management Exception
#define INT_BUS_FAULT           (-11) // Bus Fault Exception
#define INT_USAGE_FAULT         (-10) // Usage Fault Exception
#define INT_SECURE_FAULT        (-9)  // Secure Fault Exception
#define INT_SVCALL              (-5)  // SVCall Exception
#define INT_DEBUG_MONITIR       (-4)  // Debug Monitor Exception
#define INT_PENDSV              (-2)  // PendSV Exception
#define INT_SYSTICK             (-1)  // System Tick Exception

//*****************************************************************************
//
// NVIC Interrupt Numbers
//
//*****************************************************************************
#define INT_DCCOMP             11    // DCCOMP0 Interrupt
#define INT_TMR1               13    // CPU Timer 1 Interrupt
#define INT_TMR2               14    // CPU Timer 2 Interrupt
#define INT_CFGSMS             16    // CFGSMS Interrupt
#define INT_IPC_COP_TE0        17    // IPC TE0 Interrupt
#define INT_IPC_COP_TE1        18    // IPC TE1 Interrupt
#define INT_IPC_COP_TE2        19    // IPC TE2 Interrupt
#define INT_IPC_COP_TE3        20    // IPC TE3 Interrupt
#define INT_IPC_COP_RF0        21    // IPC RF0 Interrupt
#define INT_IPC_COP_RF1        22    // IPC RF1 Interrupt
#define INT_IPC_COP_RF2        23    // IPC RF2 Interrupt
#define INT_IPC_COP_RF3        24    // IPC RF3 Interrupt
#define INT_IPC_COP_GP0        25    // IPC GP0 Interrupt
#define INT_IPC_COP_GP1        26    // IPC GP1 Interrupt
#define INT_IPC_COP_GP2        27    // IPC GP2 Interrupt
#define INT_IPC_COP_GP3        28    // IPC GP3 Interrupt
#define INT_ADCA1              32    // ADCA Interrupt 1
#define INT_ADCB1              33    // ADCB Interrupt 1
#define INT_ADCC1              34    // ADCC Interrupt 1
#define INT_TMR0               38    // Timer 0 Interrupt
#define INT_WAKE               39    // Halt Wakeup/Watchdog Interrupt
#define INT_PWM1_TZ            40    // PWM1 Trip Zone Interrupt
#define INT_PWM2_TZ            41    // PWM2 Trip Zone Interrupt
#define INT_PWM3_TZ            42    // PWM3 Trip Zone Interrupt
#define INT_PWM4_TZ            43    // PWM4 Trip Zone Interrupt
#define INT_PWM5_TZ            44    // PWM5 Trip Zone Interrupt
#define INT_PWM6_TZ            45    // PWM6 Trip Zone Interrupt
#define INT_PWM7_TZ            46    // PWM7 Trip Zone Interrupt
#define INT_PWM8_TZ            47    // PWM8 Trip Zone Interrupt
#define INT_PWM1               48    // PWM1 Interrupt
#define INT_PWM2               49    // PWM2 Interrupt
#define INT_PWM3               50    // PWM3 Interrupt
#define INT_PWM4               51    // PWM4 Interrupt
#define INT_PWM5               52    // PWM5 Interrupt
#define INT_PWM6               53    // PWM6 Interrupt
#define INT_PWM7               54    // PWM7 Interrupt
#define INT_PWM8               55    // PWM8 Interrupt
#define INT_CAP1               56    // CAP1 Interrupt
#define INT_CAP2               57    // CAP2 Interrupt
#define INT_CAP3               58    // CAP3 Interrupt
#define INT_CAP4               59    // CAP4 Interrupt
#define INT_CAP5               60    // CAP5 Interrupt
#define INT_CAP6               61    // CAP6 Interrupt 
#define INT_CAP7               62    // CAP7 Interrupt
#define INT_QEP1               64    // QEP1 Interrupt
#define INT_QEP2               65    // QEP2 Interrupt
#define INT_FLB1               68    // FLB1 (Reconfigurable Logic) Interrupt
#define INT_FLB2               69    // FLB2 (Reconfigurable Logic) Interrupt
#define INT_FLB3               70    // FLB3 (Reconfigurable Logic) Interrupt
#define INT_FLB4               71    // FLB4 (Reconfigurable Logic) Interrupt
#define INT_SPIA_RX            72    // SPIA Receive Interrupt
#define INT_SPIA_TX            73    // SPIA Transmit Interrupt
#define INT_SPIB_RX            74    // SPIB Receive Interrupt
#define INT_SPIB_TX            75    // SPIB Transmit Interrupt
#define INT_DMA_CH1            80    // DMA Channel 1 Interrupt
#define INT_DMA_CH2            81    // DMA Channel 2 Interrupt
#define INT_DMA_CH3            82    // DMA Channel 3 Interrupt
#define INT_DMA_CH4            83    // DMA Channel 4 Interrupt
#define INT_DMA_CH5            84    // DMA Channel 5 Interrupt
#define INT_DMA_CH6            85    // DMA Channel 6 Interrupt
#define INT_I2CA               88    // I2CA Interrupt 1
#define INT_I2CA_FIFO          89    // I2CA Interrupt 2
#define INT_QSPI               90    // QSPI Interrupt
#define INT_UARTA_RX           96    // UARTA Receive Interrupt
#define INT_UARTA_TX           97    // UARTA Transmit Interrupt
#define INT_UARTB_RX           98    // UARTB Receive Interrupt
#define INT_UARTB_TX           99    // UARTB Transmit Interrupt
#define INT_CANA0              100   // CANA Interrupt 0
#define INT_CANA1              101   // CANA Interrupt 1
#define INT_CANB0              102   // CANB Interrupt 0
#define INT_CANB1              103   // CANB Interrupt 1
#define INT_ADCA_EVT           104   // ADCA Event Interrupt
#define INT_ADCA2              105   // ADCA Interrupt 2
#define INT_ADCA3              106   // ADCA Interrupt 3
#define INT_ADCA4              107   // ADCA Interrupt 4
#define INT_ADCB_EVT           108   // ADCB Event Interrupt
#define INT_ADCB2              109   // ADCB Interrupt 2
#define INT_ADCB3              110   // ADCB Interrupt 3
#define INT_ADCB4              111   // ADCB Interrupt 4
#define INT_EXTI_LINE0         112   // EXTI LINE0 Interrupt
#define INT_EXTI_LINE1         113   // EXTI LINE1 Interrupt
#define INT_EXTI_LINE2         114   // EXTI LINE2 Interrupt
#define INT_EXTI_LINE3         115   // EXTI LINE3 Interrupt
#define INT_EXTI_LINE4         116   // EXTI LINE4 Interrupt
#define INT_EXTI_LINE5         117   // EXTI LINE5 Interrupt
#define INT_EXTI_LINE6         118   // EXTI LINE6 Interrupt
#define INT_EXTI_LINE7         119   // EXTI LINE7 Interrupt
#define INT_EXTI_LINE8         120   // EXTI LINE8 Interrupt
#define INT_EXTI_LINE9         121   // EXTI LINE9 Interrupt
#define INT_EXTI_LINE10        122   // EXTI LINE10 Interrupt
#define INT_EXTI_LINE11        123   // EXTI LINE11 Interrupt
#define INT_EXTI_LINE12        124   // EXTI LINE12 Interrupt
#define INT_EXTI_LINE13        125   // EXTI LINE13 Interrupt
#define INT_EXTI_LINE14        126   // EXTI LINE14 Interrupt
#define INT_EXTI_LINE15        127   // EXTI LINE15 Interrupt
#define INT_FPU_DZC            129   // FPU DZC Interrupt
#define INT_FPU_IDC            130   // FPU IDC Interrupt
#define INT_FPU_IOC            131   // FPU IOC Interrupt
#define INT_FPU_OFC            132   // FPU OFC Interrupt
#define INT_FPU_UFC            133   // FPU UFC Interrupt
#define INT_FPU_IXC            134   // FPU IXC Interrupt
#define INT_CAP6_2             157   // CAP6_2 Interrupt
#define INT_CAP7_2             158   // CAP7_2 Interrupt
#define INT_SDF1               160   // SDF1 Interrupt
#define INT_SDF1DR1            164   // SDF1DR1 Interrupt
#define INT_SDF1DR2            165   // SDF1DR2 Interrupt
#define INT_SDF1DR3            166   // SDF1DR3 Interrupt
#define INT_SDF1DR4            167   // SDF1DR4 Interrupt
#define INT_LINA_1             184   // LINA INT1
#define INT_LINA_2             185   // LINA INT2
#define INT_PMBUSA             188   // PMBUSA Interrupt
#define INT_ADCC_EVT           200   // ADCC Event Interrupt
#define INT_ADCC2              201   // ADCC Interrupt 2
#define INT_ADCC3              202   // ADCC Interrupt 3
#define INT_ADCC4              203   // ADCC Interrupt 4
#define INT_FLASH_CORR_ERR     218   // Flash Correctable Error Interrupt
#define INT_SYS_PLL_SLIP       220   // System PLL Slip Interrupt
#define INT_CTI_0              225   // CTI Interrupt 0
#define INT_CTI_1              226   // CTI Interrupt 1

//*****************************************************************************
//
// Legacy Interrupt Numbers
//
//*****************************************************************************
#define INT_XINT1               116   // XINT1 Interrupt
#define INT_XINT2               117   // XINT2 Interrupt
#define INT_XINT3               118   // XINT3 Interrupt
#define INT_XINT4               119   // XINT4 Interrupt
#define INT_XINT5               120   // XINT5 Interrupt

#endif // HW_INTS_H
