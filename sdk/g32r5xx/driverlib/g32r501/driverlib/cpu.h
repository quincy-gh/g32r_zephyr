//###########################################################################
//
// FILE:    cpu.h
//
// TITLE:   Useful CPU defines.
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
// 1. Part of the comments, including header files, macro definitions.
//
//###########################################################################

#ifndef CPU_H
#define CPU_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included header file
//
#include "g32r501.h"

//
// Define to enable interrupts
//
#ifndef EINT
#define EINT   __enable_irq()
#endif

//
// Define to disable interrupts
//
#ifndef DINT
#define DINT   __disable_irq()
#endif

//
// Define to enable debug events
//
#ifndef ERTM
#define ERTM   __NOP()
#endif

//
// Define to disable debug events
//
#ifndef DRTM
#define DRTM   __NOP()
#endif

//
// Define to allow writes to protected registers
//
#ifndef WRPRT_DISABLE
#define WRPRT_DISABLE   __wrprt_disable()
#endif // WRPRT_DISABLE

//
// Define to disable writes to protected registers
//
#ifndef WRPRT_ENABLE
#define WRPRT_ENABLE   __wrprt_enable()
#endif // WRPRT_ENABLE

//
// Define for emulation stop
//
#ifndef ESTOP0
#define ESTOP0 do                                                   \
               {                                                    \
                   if((DCB->DHCSR & DCB_DHCSR_C_DEBUGEN_Msk) != 0U) \
                   {                                                \
                       __BKPT(0);                                   \
                   }                                                \
               }                                                    \
               while((_Bool)0)
#endif

//
// Define for emulation stop
//
#ifndef ESTOP1
#define ESTOP1 do                                                   \
               {                                                    \
                   if((DCB->DHCSR & DCB_DHCSR_C_DEBUGEN_Msk) != 0U) \
                   {                                                \
                       __BKPT(1);                                   \
                   }                                                \
               }                                                    \
               while((_Bool)0)
#endif

//
// Define for no operation
//
#ifndef NOP
#define NOP    __NOP()
#endif

//
// Define for putting processor into a low-power mode
//
#ifndef _DUAL_HEADERS
#ifndef IDLE
#define IDLE_ASM __WFI()
//#define IDLE     __WFI()
#endif
#else
#define IDLE_ASM __WFI()
#endif

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // CPU_H
