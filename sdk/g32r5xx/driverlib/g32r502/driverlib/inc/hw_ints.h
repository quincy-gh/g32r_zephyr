//###########################################################################
//
// FILE:    hw_ints.h
//
// TITLE:   Definitions of interrupt numbers for use with interrupt.c.
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
// 2. Add INT_WWDT_WAKE, INT_LINA_INT1/2, and interrupt symbol aliases; fix INT_DEBUG_MONITOR
// 3. Align IRQ39 primary symbol INT_WWDT_WAKE with SVD WDT.WWDT_WAKE; update LPM/watchdog examples
// 4. Clarify IRQ39: WWDT interrupt and LPM wake share one NVIC vector
// 5. Remove typo alias INT_DEBUG_MONITIR; keep INT_DEBUG_MONITOR only
// 6. Remove legacy INT_WWDT/INT_WAKE/INT_LINA_1/2; unify WWDT and LINA INT naming
// 7. Align IRQ symbol names with G32R502 user manual vector table
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
#define INT_DEBUG_MONITOR       (-4)  // Debug Monitor Exception
#define INT_PENDSV              (-2)  // PendSV Exception
#define INT_SYSTICK             (-1)  // System Tick Exception

//*****************************************************************************
//
// NVIC Interrupt Numbers
//
//*****************************************************************************
#define INT_DCCOMP           11    // DCCOMP Interrupt
#define INT_TMR1             13    // CPU Timer 1 Interrupt
#define INT_TMR2             14    // CPU Timer 2 Interrupt
#define INT_RAM              16    // System Memory Interrupt
#define INT_ADCA1            32    // ADCA Interrupt 1
#define INT_ADCC1            34    // ADCC Interrupt 1
#define INT_TMR0             38    // Timer 0 Interrupt
#define INT_WWDT_WAKE        39    // WWDT interrupt & LPM wakeup Interrupt
#define INT_PWM1_TRIP_ZONE   40    // PWM1 TRIP ZONE Interrupt
#define INT_PWM2_TRIP_ZONE   41    // PWM2 TRIP ZONE Interrupt
#define INT_PWM3_TRIP_ZONE   42    // PWM3 TRIP ZONE Interrupt
#define INT_PWM4_TRIP_ZONE   43    // PWM4 TRIP ZONE Interrupt
#define INT_PWM5_TRIP_ZONE   44    // PWM5 TRIP ZONE Interrupt
#define INT_PWM6_TRIP_ZONE   45    // PWM6 TRIP ZONE Interrupt
#define INT_PWM7_TRIP_ZONE   46    // PWM7 TRIP ZONE Interrupt
#define INT_PWM1             48    // PWM1 Interrupt
#define INT_PWM2             49    // PWM2 Interrupt
#define INT_PWM3             50    // PWM3 Interrupt
#define INT_PWM4             51    // PWM4 Interrupt
#define INT_PWM5             52    // PWM5 Interrupt
#define INT_PWM6             53    // PWM6 Interrupt
#define INT_PWM7             54    // PWM7 Interrupt
#define INT_CAP1             56    // CAP1 Interrupt
#define INT_CAP2             57    // CAP2 Interrupt
#define INT_CAP3             58    // CAP3 Interrupt
#define INT_QEP1             64    // QEP1 Interrupt
#define INT_FLB1             68    // FLB1 Interrupt
#define INT_FLB2             69    // FLB2 Interrupt
#define INT_FLB3             70    // FLB3 Interrupt
#define INT_FLB4             71    // FLB4 Interrupt
#define INT_SPIA_RX          72    // SPIA Receive Interrupt
#define INT_SPIA_TX          73    // SPIA Transmit Interrupt
#define INT_DMA_CH1          80    // DMA Channel 1 Interrupt
#define INT_DMA_CH2          81    // DMA Channel 2 Interrupt
#define INT_DMA_CH3          82    // DMA Channel 3 Interrupt
#define INT_DMA_CH4          83    // DMA Channel 4 Interrupt
#define INT_DMA_CH5          84    // DMA Channel 5 Interrupt
#define INT_DMA_CH6          85    // DMA Channel 6 Interrupt
#define INT_I2CA             88    // I2CA Interrupt
#define INT_I2CA_FIFO        89    // I2CA FIFO Interrupt
#define INT_I2CB             91    // I2CB Interrupt
#define INT_I2CB_FIFO        92    // I2CB FIFO Interrupt
#define INT_UARTA_RX         96    // UARTA Receive Interrupt
#define INT_UARTA_TX         97    // UARTA Transmit Interrupt
#define INT_UARTB_RX         98    // UARTB Receive Interrupt
#define INT_UARTB_TX         99    // UARTB Transmit Interrupt
#define INT_CANA_INT0        100   // CANA INT0
#define INT_CANA_INT1        101   // CANA INT1
#define INT_ADCA_EVENT       104   // ADCA EVENT Interrupt
#define INT_ADCA2            105   // ADCA Interrupt 2
#define INT_ADCA3            106   // ADCA Interrupt 3
#define INT_ADCA4            107   // ADCA Interrupt 4
#define INT_EXTI_LINE0       112   // EXTI LINE0 Interrupt
#define INT_EXTI_LINE1       113   // EXTI LINE1 Interrupt
#define INT_EXTI_LINE2       114   // EXTI LINE2 Interrupt
#define INT_EXTI_LINE3       115   // EXTI LINE3 Interrupt
#define INT_EXTI_LINE4       116   // EXTI LINE4 Interrupt
#define INT_EXTI_LINE5       117   // EXTI LINE5 Interrupt
#define INT_EXTI_LINE6       118   // EXTI LINE6 Interrupt
#define INT_EXTI_LINE7       119   // EXTI LINE7 Interrupt
#define INT_EXTI_LINE8       120   // EXTI LINE8 Interrupt
#define INT_EXTI_LINE9       121   // EXTI LINE9 Interrupt
#define INT_EXTI_LINE10      122   // EXTI LINE10 Interrupt
#define INT_EXTI_LINE11      123   // EXTI LINE11 Interrupt
#define INT_EXTI_LINE12      124   // EXTI LINE12 Interrupt
#define INT_FPU_DZC          129   // FPU DZC Interrupt
#define INT_FPU_IDC          130   // FPU IDC Interrupt
#define INT_FPU_IOC          131   // FPU IOC Interrupt
#define INT_FPU_OFC          132   // FPU OFC Interrupt
#define INT_FPU_UFC          133   // FPU UFC Interrupt
#define INT_FPU_IXC          134   // FPU IXC Interrupt
#define INT_CANFDA_INT0      169   // CANFDA INT0
#define INT_CANFDA_INT1      170   // CANFDA INT1
#define INT_CANFDA_BEC_INT   171   // CANFDA BEC INT
#define INT_CANFDA_BEU_INT   172   // CANFDA BEU INT
#define INT_CANFDA_WAKE_UP_INT 173 // CANFDA WAKE UP INT
#define INT_LINA_INT1        184   // LINA INT1
#define INT_LINA_INT2        185   // LINA INT2
#define INT_UARTC_RX         186   // UARTC RX Interrupt
#define INT_UARTC_TX         187   // UARTC TX Interrupt
#define INT_PMBUSA           188   // PMBUSA Interrupt
#define INT_ADCC_EVENT       200   // ADCC EVENT Interrupt
#define INT_ADCC2            201   // ADCC2 Interrupt
#define INT_ADCC3            202   // ADCC3 Interrupt
#define INT_ADCC4            203   // ADCC4 Interrupt
#define INT_FLASH_ECC_ERR    218   // FLASH ECC ERR Interrupt
#define INT_SYS_PLL_SLIP     220   // System PLL Slip Interrupt
#define INT_CTI_INT0         225   // CTI INT0
#define INT_CTI_INT1         226   // CTI INT1

//*****************************************************************************
//
// Legacy interrupt numbers (XINTn aliases)
//
//*****************************************************************************
// XINTn share IRQ numbers with EXTI_LINE4..8; do not enable both for one channel.
#define INT_XINT1               116   // XINT1 (alias of INT_EXTI_LINE4)
#define INT_XINT2               117   // XINT2 (alias of INT_EXTI_LINE5)
#define INT_XINT3               118   // XINT3 (alias of INT_EXTI_LINE6)
#define INT_XINT4               119   // XINT4 (alias of INT_EXTI_LINE7)
#define INT_XINT5               120   // XINT5 (alias of INT_EXTI_LINE8)

#endif // HW_INTS_H
