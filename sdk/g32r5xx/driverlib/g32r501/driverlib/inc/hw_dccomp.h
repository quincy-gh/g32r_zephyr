//###########################################################################
//
// FILE:    hw_DCCOMP.h
//
// TITLE:   Definitions for the DCCOMP registers.
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

#ifndef HW_DCCOMP_H
#define HW_DCCOMP_H

//*************************************************************************************************
//
// The following are defines for the DCCOMP register offsets
//
//*************************************************************************************************
#define DCCOMP_O_DCCOMPCTRL         (0x0*2U)    // Global Control Register
#define DCCOMP_O_DCCOMPREV          (0x4*2U)    // DCCOMP Revision Register
#define DCCOMP_O_DCCOMPCNTSEED0     (0x8*2U)    // Counter 0 Seed Value
#define DCCOMP_O_DCCOMPVALSEED0     (0xC*2U)    // Valid 0 Seed Value
#define DCCOMP_O_DCCOMPCNTSEED1     (0x10*2U)   // Counter 1 Seed Value
#define DCCOMP_O_DCCOMPFLG          (0x14*2U)   // DCCOMP Status
#define DCCOMP_O_DCCOMPCLKSRCCNT0   (0x18*2U)   // Counter 0 Value
#define DCCOMP_O_DCCOMPCLKSRCVAL0   (0x1C*2U)   // Valid Value 0
#define DCCOMP_O_DCCOMPCLKSRCCNT1   (0x20*2U)   // Counter 1 Value
#define DCCOMP_O_DCCOMPCLKSRCSEL1   (0x24*2U)   // Clock Source 1
#define DCCOMP_O_DCCOMPCLKSRCSEL0   (0x28*2U)   // Clock Source 0


//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCOMPCTRL register
//
//*************************************************************************************************
#define DCCOMP_DCCOMPCTRL_DCCOMPEN_S    0U
#define DCCOMP_DCCOMPCTRL_DCCOMPEN_M    0xFU      // DCCOMP Enable
#define DCCOMP_DCCOMPCTRL_ERREN_S       4U
#define DCCOMP_DCCOMPCTRL_ERREN_M       0xF0U     // Error Enable
#define DCCOMP_DCCOMPCTRL_SIGEN_S       8U
#define DCCOMP_DCCOMPCTRL_SIGEN_M       0xF00U    // Single Shot Mode Enable
#define DCCOMP_DCCOMPCTRL_DONEEN_S      12U
#define DCCOMP_DCCOMPCTRL_DONEEN_M      0xF000U   // DONE Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCOMPREV register
//
//*************************************************************************************************
#define DCCOMP_DCCOMPREV_MINOR_S   0U
#define DCCOMP_DCCOMPREV_MINOR_M   0x3FU    // Minor Revision Number
#define DCCOMP_DCCOMPREV_MAJOR_S   8U
#define DCCOMP_DCCOMPREV_MAJOR_M   0x700U   // Major Revision Number

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCOMPCNTSEED0 register
//
//*************************************************************************************************
#define DCCOMP_DCCOMPCNTSEED0_CNTSEED0_S   0U
#define DCCOMP_DCCOMPCNTSEED0_CNTSEED0_M   0xFFFFFU   // Counter 0 Seed Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCOMPVALSEED0 register
//
//*************************************************************************************************
#define DCCOMP_DCCOMPVALSEED0_VALSEED0_S   0U
#define DCCOMP_DCCOMPVALSEED0_VALSEED0_M   0xFFFFU   // Valid Duration Counter 0 Seed Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCOMPCNTSEED1 register
//
//*************************************************************************************************
#define DCCOMP_DCCOMPCNTSEED1_CNTSEED1_S   0U
#define DCCOMP_DCCOMPCNTSEED1_CNTSEED1_M   0xFFFFFU   // Counter 1 Seed Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCOMPFLG register
//
//*************************************************************************************************
#define DCCOMP_DCCOMPFLG_ERRFLG       0x1U      // Error Flag
#define DCCOMP_DCCOMPFLG_SIGDONEFLG   0x2U      // Single-Shot Done Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCOMPCLKSRCCNT0 register
//
//*************************************************************************************************
#define DCCOMP_DCCOMPCLKSRCCNT0_CLKSRCCNT0_S   0U
#define DCCOMP_DCCOMPCLKSRCCNT0_CLKSRCCNT0_M   0xFFFFFU   // Current Value of Counter 0

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCOMPCLKSRCVAL0 register
//
//*************************************************************************************************
#define DCCOMP_DCCOMPCLKSRCVAL0_CLKSRCVAL0_S   0U
#define DCCOMP_DCCOMPCLKSRCVAL0_CLKSRCVAL0_M   0xFFFFU   // Current Value of Valid 0

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCOMPCLKSRCCNT1 register
//
//*************************************************************************************************
#define DCCOMP_DCCOMPCLKSRCCNT1_CLKSRCCNT1_S   0U
#define DCCOMP_DCCOMPCLKSRCCNT1_CLKSRCCNT1_M   0xFFFFFU   // Current Value of Counter 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCOMPCLKSRCSEL1 register
//
//*************************************************************************************************
#define DCCOMP_DCCOMPCLKSRCSEL1_CLKSRCSEL1_S      0U
#define DCCOMP_DCCOMPCLKSRCSEL1_CLKSRCSEL1_M      0xFU      // Clock Source Select for Counter 1
#define DCCOMP_DCCOMPCLKSRCSEL1_CLKSRCWEN_S       12U
#define DCCOMP_DCCOMPCLKSRCSEL1_CLKSRCWEN_M       0xF000U   // Enables or Disables Clock Source Selection for COUNT1

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCOMPCLKSRCSEL0 register
//
//*************************************************************************************************
#define DCCOMP_DCCOMPCLKSRCSEL0_CLKSRCSEL0_S   0U
#define DCCOMP_DCCOMPCLKSRCSEL0_CLKSRCSEL0_M   0xFU   // Clock Source Select for Counter 0



#endif
