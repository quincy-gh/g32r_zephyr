//###########################################################################
//
// FILE:    hw_exit.h
//
// TITLE:   Definitions for the EXIT registers.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
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

#ifndef HW_EXTI_H
#define HW_EXTI_H

//*************************************************************************************************
//
// The following are defines for the EXIT register offsets
//
//*************************************************************************************************
#define EXTI_O_RTEN              0x0U    // Enable rising edge trigger selection register
#define EXTI_O_FTEN              0x4U    // Enable falling edge trigger selection register
#define EXTI_O_SWINTE            0x8U    // Software interrupt event register
#define EXTI_O_GPIOSEL           0xCU    // GPIO Trigger signal select register
#define EXTI_O_IMASK             0x10U   // CPU Interrupt mask register
#define EXTI_O_EMASK             0x14U   // CPU Event mask register
#define EXTI_O_IPEND             0x18U   // CPU Interrupt pending register
#define EXTI_O_INT4CNT           0x30U   // Interrupt Line 4 Counter register
#define EXTI_O_INT5CNT           0x34U   // Interrupt Line 5 Counter register
#define EXTI_O_INT6CNT           0x38U   // Interrupt Line 6 Counter register



//*************************************************************************************************
//
// The following are defines for the bit fields in the RTEN register
//
//*************************************************************************************************
#define EXTI_RTEN_RTEN0    0x1U      // Rising Trigger Event and Interrupt of Line0
#define EXTI_RTEN_RTEN1    0x2U      // Rising Trigger Event and Interrupt of Line1
#define EXTI_RTEN_RTEN2    0x4U      // Rising Trigger Event and Interrupt of Line2
#define EXTI_RTEN_RTEN3    0x8U      // Rising Trigger Event and Interrupt of Line3
#define EXTI_RTEN_RTEN4    0x10U     // Rising Trigger Event and Interrupt of Line4
#define EXTI_RTEN_RTEN5    0x20U     // Rising Trigger Event and Interrupt of Line5
#define EXTI_RTEN_RTEN6    0x40U     // Rising Trigger Event and Interrupt of Line6
#define EXTI_RTEN_RTEN7    0x80U     // Rising Trigger Event and Interrupt of Line7
#define EXTI_RTEN_RTEN8    0x100U    // Rising Trigger Event and Interrupt of Line8
#define EXTI_RTEN_RTEN9    0x200U    // Rising Trigger Event and Interrupt of Line9
#define EXTI_RTEN_RTEN10   0x400U    // Rising Trigger Event and Interrupt of Line10
#define EXTI_RTEN_RTEN11   0x800U    // Rising Trigger Event and Interrupt of Line11
#define EXTI_RTEN_RTEN12   0x1000U   // Rising Trigger Event and Interrupt of Line12

//*************************************************************************************************
//
// The following are defines for the bit fields in the EXTI_FTEN register
//
//*************************************************************************************************
#define EXTI_FTEN_FTEN0    0x1U      // Falling Trigger Event and Interrupt of Line0
#define EXTI_FTEN_FTEN1    0x2U      // Falling Trigger Event and Interrupt of Line1
#define EXTI_FTEN_FTEN2    0x4U      // Falling Trigger Event and Interrupt of Line2
#define EXTI_FTEN_FTEN3    0x8U      // Falling Trigger Event and Interrupt of Line3
#define EXTI_FTEN_FTEN4    0x10U     // Falling Trigger Event and Interrupt of Line4
#define EXTI_FTEN_FTEN5    0x20U     // Falling Trigger Event and Interrupt of Line5
#define EXTI_FTEN_FTEN6    0x40U     // Falling Trigger Event and Interrupt of Line6
#define EXTI_FTEN_FTEN7    0x80U     // Falling Trigger Event and Interrupt of Line7
#define EXTI_FTEN_FTEN8    0x100U    // Falling Trigger Event and Interrupt of Line8
#define EXTI_FTEN_FTEN9    0x200U    // Falling Trigger Event and Interrupt of Line9
#define EXTI_FTEN_FTEN10   0x400U    // Falling Trigger Event and Interrupt of Line10
#define EXTI_FTEN_FTEN11   0x800U    // Falling Trigger Event and Interrupt of Line11
#define EXTI_FTEN_FTEN12   0x1000U   // Falling Trigger Event and Interrupt of Line12

//*************************************************************************************************
//
// The following are defines for the bit fields in the EXTI_SWINTE register
//
//*************************************************************************************************
#define EXTI_SWINTE_SWINTE0    0x1U      // Software Interrupt Event on Line0
#define EXTI_SWINTE_SWINTE1    0x2U      // Software Interrupt Event on Line1
#define EXTI_SWINTE_SWINTE2    0x4U      // Software Interrupt Event on Line2
#define EXTI_SWINTE_SWINTE3    0x8U      // Software Interrupt Event on Line3
#define EXTI_SWINTE_SWINTE4    0x10U     // Software Interrupt Event on Line4
#define EXTI_SWINTE_SWINTE5    0x20U     // Software Interrupt Event on Line5
#define EXTI_SWINTE_SWINTE6    0x40U     // Software Interrupt Event on Line6
#define EXTI_SWINTE_SWINTE7    0x80U     // Software Interrupt Event on Line7
#define EXTI_SWINTE_SWINTE8    0x100U    // Software Interrupt Event on Line8
#define EXTI_SWINTE_SWINTE9    0x200U    // Software Interrupt Event on Line9
#define EXTI_SWINTE_SWINTE10   0x400U    // Software Interrupt Event on Line10
#define EXTI_SWINTE_SWINTE11   0x800U    // Software Interrupt Event on Line11
#define EXTI_SWINTE_SWINTE12   0x1000U   // Software Interrupt Event on Line12

//*************************************************************************************************
//
// The following are defines for the bit fields in the EXTI_GPIO_SEL register
//
//*************************************************************************************************
#define EXTI_GPIOSEL_GPIOSEL0_S   0U
#define EXTI_GPIOSEL_GPIOSEL0_M   0xFU      // GPIO Trigger signal select 0
#define EXTI_GPIOSEL_GPIOSEL1_S   4U
#define EXTI_GPIOSEL_GPIOSEL1_M   0xF0U     // GPIO Trigger signal select 1
#define EXTI_GPIOSEL_GPIOSEL2_S   8U
#define EXTI_GPIOSEL_GPIOSEL2_M   0xF00U    // GPIO Trigger signal select 2
#define EXTI_GPIOSEL_GPIOSEL3_S   12U
#define EXTI_GPIOSEL_GPIOSEL3_M   0xF000U   // GPIO Trigger signal select 3

//*************************************************************************************************
//
// The following are defines for the bit fields in the EXTI_IMASK register
//
//*************************************************************************************************
#define EXTI_IMASK_IMASK0    0x1U      // Interrupt Request Mask on Line0
#define EXTI_IMASK_IMASK1    0x2U      // Interrupt Request Mask on Line1
#define EXTI_IMASK_IMASK2    0x4U      // Interrupt Request Mask on Line2
#define EXTI_IMASK_IMASK3    0x8U      // Interrupt Request Mask on Line3
#define EXTI_IMASK_IMASK4    0x10U     // Interrupt Request Mask on Line4
#define EXTI_IMASK_IMASK5    0x20U     // Interrupt Request Mask on Line5
#define EXTI_IMASK_IMASK6    0x40U     // Interrupt Request Mask on Line6
#define EXTI_IMASK_IMASK7    0x80U     // Interrupt Request Mask on Line7
#define EXTI_IMASK_IMASK8    0x100U    // Interrupt Request Mask on Line8
#define EXTI_IMASK_IMASK9    0x200U    // Interrupt Request Mask on Line9
#define EXTI_IMASK_IMASK10   0x400U    // Interrupt Request Mask on Line10
#define EXTI_IMASK_IMASK11   0x800U    // Interrupt Request Mask on Line11
#define EXTI_IMASK_IMASK12   0x1000U   // Interrupt Request Mask on Line12

//*************************************************************************************************
//
// The following are defines for the bit fields in the EXTI_EMASK register
//
//*************************************************************************************************
#define EXTI_EMASK_EMASK0    0x1U      // Event Request Mask on Line0
#define EXTI_EMASK_EMASK1    0x2U      // Event Request Mask on Line1
#define EXTI_EMASK_EMASK2    0x4U      // Event Request Mask on Line2
#define EXTI_EMASK_EMASK3    0x8U      // Event Request Mask on Line3
#define EXTI_EMASK_EMASK4    0x10U     // Event Request Mask on Line4
#define EXTI_EMASK_EMASK5    0x20U     // Event Request Mask on Line5
#define EXTI_EMASK_EMASK6    0x40U     // Event Request Mask on Line6
#define EXTI_EMASK_EMASK7    0x80U     // Event Request Mask on Line7
#define EXTI_EMASK_EMASK8    0x100U    // Event Request Mask on Line8
#define EXTI_EMASK_EMASK9    0x200U    // Event Request Mask on Line9
#define EXTI_EMASK_EMASK10   0x400U    // Event Request Mask on Line10
#define EXTI_EMASK_EMASK11   0x800U    // Event Request Mask on Line11
#define EXTI_EMASK_EMASK12   0x1000U   // Event Request Mask on Line12

//*************************************************************************************************
//
// The following are defines for the bit fields in the EXTI_IPEND register
//
//*************************************************************************************************
#define EXTI_IPEND_IPEND0    0x1U      // Interrupt Pending Occur of Line0 Flag
#define EXTI_IPEND_IPEND1    0x2U      // Interrupt Pending Occur of Line1 Flag
#define EXTI_IPEND_IPEND2    0x4U      // Interrupt Pending Occur of Line2 Flag
#define EXTI_IPEND_IPEND3    0x8U      // Interrupt Pending Occur of Line3 Flag
#define EXTI_IPEND_IPEND4    0x10U     // Interrupt Pending Occur of Line4 Flag
#define EXTI_IPEND_IPEND5    0x20U     // Interrupt Pending Occur of Line5 Flag
#define EXTI_IPEND_IPEND6    0x40U     // Interrupt Pending Occur of Line6 Flag
#define EXTI_IPEND_IPEND7    0x80U     // Interrupt Pending Occur of Line7 Flag
#define EXTI_IPEND_IPEND8    0x100U    // Interrupt Pending Occur of Line8 Flag
#define EXTI_IPEND_IPEND9    0x200U    // Interrupt Pending Occur of Line9 Flag
#define EXTI_IPEND_IPEND10   0x400U    // Interrupt Pending Occur of Line10 Flag
#define EXTI_IPEND_IPEND11   0x800U    // Interrupt Pending Occur of Line11 Flag
#define EXTI_IPEND_IPEND12   0x1000U   // Interrupt Pending Occur of Line12 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the EXTI_INT4CNT register
//
//*************************************************************************************************
#define EXTI_INT4CNT_INT4CNT_S   0U
#define EXTI_INT4CNT_INT4CNT_M   0xFFFFU   // Interrupt Line 6 Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the EXTI_INT5CNT register
//
//*************************************************************************************************
#define EXTI_INT5CNT_INT5CNT_S   0U
#define EXTI_INT5CNT_INT5CNT_M   0xFFFFU   // Interrupt Line 6 Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the EXTI_INT6CNT register
//
//*************************************************************************************************
#define EXTI_INT6CNT_INT6CNT_S   0U
#define EXTI_INT6CNT_INT6CNT_M   0xFFFFU   // Interrupt Line 6 Counter



#endif
