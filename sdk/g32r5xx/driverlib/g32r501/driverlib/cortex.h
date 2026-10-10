//###########################################################################
//
// FILE:    cortex.h
//
// TITLE:   G32R501 cortex driver.
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

#ifndef CORTEX_H
#define CORTEX_H

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

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "g32r501.h"
#include "debug.h"
#include "sysctl.h"


//! 0 bits for Group priorities priority, 8 bits for subpriority 
#define NVIC_PRIORITYGROUP_0         0x07U    
//! 1 bits for Group priorities priority, 7 bits for subpriority
#define NVIC_PRIORITYGROUP_1         0x06U    
//! 2 bits for Group priorities priority, 6 bits for subpriority
#define NVIC_PRIORITYGROUP_2         0x05U 
//! 3 bits for Group priorities priority, 5 bits for subpriority
#define NVIC_PRIORITYGROUP_3         0x04U
//! 4 bits for Group priorities priority, 4 bits for subpriority
#define NVIC_PRIORITYGROUP_4         0x03U


/**
  * @}
  */

/** @defgroup CORTEX_SysTick_clock_source CORTEX _SysTick clock source 
  * @{
  */
#define SYSTICK_CLKSOURCE_HCLK_DIV8    0x00000000U
#define SYSTICK_CLKSOURCE_HCLK         0x00000004U


#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PRIORITYGROUP_0) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_1) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_2) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_3) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_4))


#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10U)

#define IS_NVIC_SUB_PRIORITY(PRIORITY)         ((PRIORITY) < 0x10U)

#define IS_NVIC_DEVICE_IRQ(IRQ)                ((IRQ) >= (IRQn_Type)0x00U)

#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SYSTICK_CLKSOURCE_HCLK) || \
                                       ((SOURCE) == SYSTICK_CLKSOURCE_HCLK_DIV8))


extern void NVIC_setPriorityGrouping(uint32_t PriorityGroup);
extern void NVIC_setPriority(IRQn_Type IRQn, uint32_t  GroupPriority, uint32_t SubPriority);
extern void NVIC_enableIRQ(IRQn_Type IRQn);
extern void NVIC_disableIRQ(IRQn_Type IRQn);
extern void NVIC_systemReset(void);
extern uint32_t SYSTICK_config(uint32_t TicksNumb);

uint32_t NVIC_getPriorityGrouping(void);
void NVIC_getPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *pPreemptPriority, uint32_t *pSubPriority);
uint32_t NVIC_getPendingIRQ(IRQn_Type IRQn);
void NVIC_setPendingIRQ(IRQn_Type IRQn);
void NVIC_clearPendingIRQ(IRQn_Type IRQn);
uint32_t NVIC_getActive(IRQn_Type IRQn);
void SYSTICK_CLKSourceConfig(uint32_t CLKSource);


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  CORTEX_H
