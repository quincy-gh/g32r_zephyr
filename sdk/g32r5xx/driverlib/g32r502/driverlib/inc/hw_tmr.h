//###########################################################################
//
// FILE:    hw_tmr.h
//
// TITLE:   Definitions for the TMR registers.
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
// 1. Some comments, macro definitions (register and bit-field naming) were changed.
//
//###########################################################################

#ifndef HW_TMR_H
#define HW_TMR_H

//*************************************************************************************************
//
// The following are defines for the TMR register offsets
//
//*************************************************************************************************
#define TMR_O_TIM    (0x0*2U)   // Timer Counter Register
#define TMR_O_PRD    (0x2*2U)   // Timer Period Register
#define TMR_O_TCR    (0x4*2U)   // Timer Control Register
#define TMR_O_TPR    (0x6*2U)   // Timer Prescale Register
#define TMR_O_TPRH   (0x7*2U)   // Timer Prescale Register High

//*************************************************************************************************
//
// The following are defines for the bit fields in the TIM register
//
//*************************************************************************************************
#define TMR_TIM_LSW_S   0U
#define TMR_TIM_LSW_M   0xFFFFU       // Timer Counter Registers
#define TMR_TIM_MSW_S   16U
#define TMR_TIM_MSW_M   0xFFFF0000U   // Timer Counter Registers High

//*************************************************************************************************
//
// The following are defines for the bit fields in the PRD register
//
//*************************************************************************************************
#define TMR_PRD_LSW_S   0U
#define TMR_PRD_LSW_M   0xFFFFU       // Timer Period Registers
#define TMR_PRD_MSW_S   16U
#define TMR_PRD_MSW_M   0xFFFF0000U   // Timer Period Registers High

//*************************************************************************************************
//
// The following are defines for the bit fields in the TCR register
//
//*************************************************************************************************
#define TMR_TCR_TSS     0x10U     // Timer stop status bit
#define TMR_TCR_TRB     0x20U     // Timer reload
#define TMR_TCR_SOFT    0x400U    // Emulation modes
#define TMR_TCR_FREE    0x800U    // Emulation modes
#define TMR_TCR_TIE     0x4000U   // Timer Interrupt Enable
#define TMR_TCR_TIF     0x8000U   // Timer Interrupt Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TPR register
//
//*************************************************************************************************
#define TMR_TPR_TDDR_S    0U
#define TMR_TPR_TDDR_M    0xFFU     // Timer Divide-Down
#define TMR_TPR_PSC_S     8U
#define TMR_TPR_PSC_M     0xFF00U   // Timer Prescale Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the TPRH register
//
//*************************************************************************************************
#define TMR_TPRH_TDDRH_S    0U
#define TMR_TPRH_TDDRH_M    0xFFU     // Timer Divide-Down
#define TMR_TPRH_PSCH_S     8U
#define TMR_TPRH_PSCH_M     0xFF00U   // Timer Prescale Counter



#endif
