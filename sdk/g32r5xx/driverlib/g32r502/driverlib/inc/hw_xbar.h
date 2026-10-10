//###########################################################################
//
// FILE:    hw_xbar.h
//
// TITLE:   Definitions for the XBAR registers.
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
// 1. Some comments, macro definitions (register naming) were changed.
//
//###########################################################################

#ifndef HW_XBAR_H
#define HW_XBAR_H

//*************************************************************************************************
//
// The following are defines for the XBAR register offsets
//
//*************************************************************************************************
#define XBAR_O_FLG1   (0x00U)   // X-Bar Input Flag Register 1
#define XBAR_O_FLG2   (0x04U)   // X-Bar Input Flag Register 2
#define XBAR_O_FLG3   (0x08U)   // X-Bar Input Flag Register 3
#define XBAR_O_FLG4   (0x0CU)   // X-Bar Input Flag Register 4
#define XBAR_O_CLR1   (0x10U)   // X-Bar Input Flag Clear Register 1
#define XBAR_O_CLR2   (0x14U)   // X-Bar Input Flag Clear Register 2
#define XBAR_O_CLR3   (0x18U)   // X-Bar Input Flag Clear Register 3
#define XBAR_O_CLR4   (0x1CU)   // X-Bar Input Flag Clear Register 4

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG1 register
//
//*************************************************************************************************
#define XBAR_FLG1_COMP1_CTRIPL      0x1U          // Input Flag for COMP1.CTRIPL Signal
#define XBAR_FLG1_COMP1_CTRIPH      0x2U          // Input Flag for COMP1.CTRIPH Signal
#define XBAR_FLG1_COMP2_CTRIPL      0x4U          // Input Flag for COMP2.CTRIPL Signal
#define XBAR_FLG1_COMP2_CTRIPH      0x8U          // Input Flag for COMP2.CTRIPH Signal
#define XBAR_FLG1_COMP3_CTRIPL      0x10U         // Input Flag for COMP3.CTRIPL Signal
#define XBAR_FLG1_COMP3_CTRIPH      0x20U         // Input Flag for COMP3.CTRIPH Signal
#define XBAR_FLG1_COMP4_CTRIPL      0x40U         // Input Flag for COMP4.CTRIPL Signal
#define XBAR_FLG1_COMP4_CTRIPH      0x80U         // Input Flag for COMP4.CTRIPH Signal
#define XBAR_FLG1_COMP1_CTRIPOUTL   0x10000U      // Input Flag for COMP1.CTRIPOUTL Signal
#define XBAR_FLG1_COMP1_CTRIPOUTH   0x20000U      // Input Flag for COMP1.CTRIPOUTH Signal
#define XBAR_FLG1_COMP2_CTRIPOUTL   0x40000U      // Input Flag for COMP2.CTRIPOUTL Signal
#define XBAR_FLG1_COMP2_CTRIPOUTH   0x80000U      // Input Flag for COMP2.CTRIPOUTH Signal
#define XBAR_FLG1_COMP3_CTRIPOUTL   0x100000U     // Input Flag for COMP3.CTRIPOUTL Signal
#define XBAR_FLG1_COMP3_CTRIPOUTH   0x200000U     // Input Flag for COMP3.CTRIPOUTH Signal
#define XBAR_FLG1_COMP4_CTRIPOUTL   0x400000U     // Input Flag for COMP4.CTRIPOUTL Signal
#define XBAR_FLG1_COMP4_CTRIPOUTH   0x800000U     // Input Flag for COMP4.CTRIPOUTH Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG2 register
//
//*************************************************************************************************
#define XBAR_FLG2_INPUT1            0x1U          // Input Flag for INPUT1 Signal
#define XBAR_FLG2_INPUT2            0x2U          // Input Flag for INPUT2 Signal
#define XBAR_FLG2_INPUT3            0x4U          // Input Flag for INPUT3 Signal
#define XBAR_FLG2_INPUT4            0x8U          // Input Flag for INPUT4 Signal
#define XBAR_FLG2_INPUT5            0x10U         // Input Flag for INPUT5 Signal
#define XBAR_FLG2_INPUT6            0x20U         // Input Flag for INPUT6 Signal
#define XBAR_FLG2_ADCSOCA           0x40U         // Input Flag for ADCSOCA Signal
#define XBAR_FLG2_ADCSOCB           0x80U         // Input Flag for ADCSOCB Signal
#define XBAR_FLG2_INPUT7            0x100U        // Input Flag for INPUT7 Signal
#define XBAR_FLG2_INPUT8            0x200U        // Input Flag for INPUT8 Signal
#define XBAR_FLG2_INPUT9            0x400U        // Input Flag for INPUT9 Signal
#define XBAR_FLG2_INPUT10           0x800U        // Input Flag for INPUT10 Signal
#define XBAR_FLG2_INPUT11           0x1000U       // Input Flag for INPUT11 Signal
#define XBAR_FLG2_INPUT12           0x2000U       // Input Flag for INPUT12 Signal
#define XBAR_FLG2_INPUT13           0x4000U       // Input Flag for INPUT13 Signal
#define XBAR_FLG2_INPUT14           0x8000U       // Input Flag for INPUT14 Signal
#define XBAR_FLG2_CAP1_OUT          0x10000U      // Input Flag for CAP1.OUT Signal
#define XBAR_FLG2_CAP2_OUT          0x20000U      // Input Flag for CAP2.OUT Signal
#define XBAR_FLG2_CAP3_OUT          0x40000U      // Input Flag for CAP3.OUT Signal
#define XBAR_FLG2_EXTSYNCOUT        0x400000U     // Input Flag for EXTSYNCOUT Signal
#define XBAR_FLG2_ADCAEVT1          0x800000U     // Input Flag for ADCAEVT1 Signal
#define XBAR_FLG2_ADCAEVT2          0x1000000U    // Input Flag for ADCAEVT2 Signal
#define XBAR_FLG2_ADCAEVT3          0x2000000U    // Input Flag for ADCAEVT3 Signal
#define XBAR_FLG2_ADCAEVT4          0x4000000U    // Input Flag for ADCAEVT4 Signal
#define XBAR_FLG2_ADCCEVT1          0x80000000U   // Input Flag for ADCCEVT1 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG3 register
//
//*************************************************************************************************
#define XBAR_FLG3_ADCCEVT2          0x1U          // Input Flag for ADCCEVT2 Signal
#define XBAR_FLG3_ADCCEVT3          0x2U          // Input Flag for ADCCEVT3 Signal
#define XBAR_FLG3_ADCCEVT4          0x4U          // Input Flag for ADCCEVT4 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG4 register
//
//*************************************************************************************************
#define XBAR_FLG4_FLB1_OUT4         0x10000U      // Input Flag for FLB1_OUT4 Signal
#define XBAR_FLG4_FLB1_OUT5         0x20000U      // Input Flag for FLB1_OUT5 Signal
#define XBAR_FLG4_FLB2_OUT4         0x40000U      // Input Flag for FLB2_OUT4 Signal
#define XBAR_FLG4_FLB2_OUT5         0x80000U      // Input Flag for FLB2_OUT5 Signal
#define XBAR_FLG4_FLB3_OUT4         0x100000U     // Input Flag for FLB3_OUT4 Signal
#define XBAR_FLG4_FLB3_OUT5         0x200000U     // Input Flag for FLB3_OUT5 Signal
#define XBAR_FLG4_FLB4_OUT4         0x400000U     // Input Flag for FLB4_OUT4 Signal
#define XBAR_FLG4_FLB4_OUT5         0x800000U     // Input Flag for FLB4_OUT5 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR1 register
//
//*************************************************************************************************
#define XBAR_CLR1_COMP1_CTRIPL      0x1U          // Input Flag Clear for COMP1.CTRIPL Signal
#define XBAR_CLR1_COMP1_CTRIPH      0x2U          // Input Flag Clear for COMP1.CTRIPH Signal
#define XBAR_CLR1_COMP2_CTRIPL      0x4U          // Input Flag Clear for COMP2.CTRIPL Signal
#define XBAR_CLR1_COMP2_CTRIPH      0x8U          // Input Flag Clear for COMP2.CTRIPH Signal
#define XBAR_CLR1_COMP3_CTRIPL      0x10U         // Input Flag Clear for COMP3.CTRIPL Signal
#define XBAR_CLR1_COMP3_CTRIPH      0x20U         // Input Flag Clear for COMP3.CTRIPH Signal
#define XBAR_CLR1_COMP4_CTRIPL      0x40U         // Input Flag Clear for COMP4.CTRIPL Signal
#define XBAR_CLR1_COMP4_CTRIPH      0x80U         // Input Flag Clear for COMP4.CTRIPH Signal
#define XBAR_CLR1_COMP1_CTRIPOUTL   0x10000U      // Input Flag Clear for COMP1.CTRIPOUTL Signal
#define XBAR_CLR1_COMP1_CTRIPOUTH   0x20000U      // Input Flag Clear for COMP1.CTRIPOUTH Signal
#define XBAR_CLR1_COMP2_CTRIPOUTL   0x40000U      // Input Flag Clear for COMP2.CTRIPOUTL Signal
#define XBAR_CLR1_COMP2_CTRIPOUTH   0x80000U      // Input Flag Clear for COMP2.CTRIPOUTH Signal
#define XBAR_CLR1_COMP3_CTRIPOUTL   0x100000U     // Input Flag Clear for COMP3.CTRIPOUTL Signal
#define XBAR_CLR1_COMP3_CTRIPOUTH   0x200000U     // Input Flag Clear for COMP3.CTRIPOUTH Signal
#define XBAR_CLR1_COMP4_CTRIPOUTL   0x400000U     // Input Flag Clear for COMP4.CTRIPOUTL Signal
#define XBAR_CLR1_COMP4_CTRIPOUTH   0x800000U     // Input Flag Clear for COMP4.CTRIPOUTH Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR2 register
//
//*************************************************************************************************
#define XBAR_CLR2_INPUT1       0x1U          // Input Flag Clear for INPUT1 Signal
#define XBAR_CLR2_INPUT2       0x2U          // Input Flag Clear for INPUT2 Signal
#define XBAR_CLR2_INPUT3       0x4U          // Input Flag Clear for INPUT3 Signal
#define XBAR_CLR2_INPUT4       0x8U          // Input Flag Clear for INPUT4 Signal
#define XBAR_CLR2_INPUT5       0x10U         // Input Flag Clear for INPUT5 Signal
#define XBAR_CLR2_INPUT6       0x20U         // Input Flag Clear for INPUT6 Signal
#define XBAR_CLR2_ADCSOCA      0x40U         // Input Flag Clear for ADCSOCA Signal
#define XBAR_CLR2_INPUT7       0x100U        // Input Flag Clear for INPUT7 Signal
#define XBAR_CLR2_INPUT8       0x200U        // Input Flag Clear for INPUT8 Signal
#define XBAR_CLR2_INPUT9       0x400U        // Input Flag Clear for INPUT9 Signal
#define XBAR_CLR2_INPUT10      0x800U        // Input Flag Clear for INPUT10 Signal
#define XBAR_CLR2_INPUT11      0x1000U       // Input Flag Clear for INPUT11 Signal
#define XBAR_CLR2_INPUT12      0x2000U       // Input Flag Clear for INPUT12 Signal
#define XBAR_CLR2_INPUT13      0x4000U       // Input Flag Clear for INPUT13 Signal
#define XBAR_CLR2_INPUT14      0x8000U       // Input Flag Clear for INPUT14 Signal
#define XBAR_CLR2_CAP1_OUT     0x10000U      // Input Flag Clear for CAP1.OUT Signal
#define XBAR_CLR2_CAP2_OUT     0x20000U      // Input Flag Clear for CAP2.OUT Signal
#define XBAR_CLR2_CAP3_OUT     0x40000U      // Input Flag Clear for CAP3.OUT Signal
#define XBAR_CLR2_EXTSYNCOUT   0x400000U     // Input Flag Clear for EXTSYNCOUT Signal
#define XBAR_CLR2_ADCAEVT1     0x800000U     // Input Flag Clear for ADCAEVT1 Signal
#define XBAR_CLR2_ADCAEVT2     0x1000000U    // Input Flag Clear for ADCAEVT2 Signal
#define XBAR_CLR2_ADCAEVT3     0x2000000U    // Input Flag Clear for ADCAEVT3 Signal
#define XBAR_CLR2_ADCAEVT4     0x4000000U    // Input Flag Clear for ADCAEVT4 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR3 register
//
//*************************************************************************************************
#define XBAR_CLR3_ADCCEVT2        0x1U          // Input Flag Clear for ADCCEVT2 Signal
#define XBAR_CLR3_ADCCEVT3        0x2U          // Input Flag Clear for ADCCEVT3 Signal
#define XBAR_CLR3_ADCCEVT4        0x4U          // Input Flag Clear for ADCCEVT4 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR4 register
//
//*************************************************************************************************
#define XBAR_CLR4_FLB1_OUT4       0x10000U      // Input Flag clear for FLB1_OUT4 Signal
#define XBAR_CLR4_FLB1_OUT5       0x20000U      // Input Flag clear for FLB1_OUT5 Signal
#define XBAR_CLR4_FLB2_OUT4       0x40000U      // Input Flag clear for FLB2_OUT4 Signal
#define XBAR_CLR4_FLB2_OUT5       0x80000U      // Input Flag clear for FLB2_OUT5 Signal
#define XBAR_CLR4_FLB3_OUT4       0x100000U     // Input Flag clear for FLB3_OUT4 Signal
#define XBAR_CLR4_FLB3_OUT5       0x200000U     // Input Flag clear for FLB3_OUT5 Signal
#define XBAR_CLR4_FLB4_OUT4       0x400000U     // Input Flag clear for FLB4_OUT4 Signal
#define XBAR_CLR4_FLB4_OUT5       0x800000U     // Input Flag clear for FLB4_OUT5 Signal

#endif
