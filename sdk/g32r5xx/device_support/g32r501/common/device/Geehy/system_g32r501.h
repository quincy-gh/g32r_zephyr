//###########################################################################
//
// FILE:    system_g32r501.h
//
// TITLE:   CMSIS-Core(M) Device System Header File for G32R501.
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

#ifndef SYSTEM_G32R501_H
#define SYSTEM_G32R501_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
// Exception / Interrupt Handler Function Prototype
//
//*****************************************************************************
typedef void(*PINT)(void);

//*****************************************************************************
//
// System Clock Frequency (Core Clock)
//
//*****************************************************************************
extern uint32_t SystemCoreClock;

//*****************************************************************************
//
// CMSIS Device System Function Prototype
//
//*****************************************************************************
//*****************************************************************************
//
//! Setup the microcontroller system.
//!
//! This function initializes the system and disables the watchdog.
//!
//! \return None.
//
//*****************************************************************************
extern void SystemInit(void);

//*****************************************************************************
//
//! Update SystemCoreClock variable.
//!
//! This function updates the SystemCoreClock with current core clock retrieved
//! from registers.
//!
//! Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
//! SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//!
//! \return None.
//
//*****************************************************************************
extern void SystemCoreClockUpdate(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // SYSTEM_G32R501_H

//
// End of file
//
