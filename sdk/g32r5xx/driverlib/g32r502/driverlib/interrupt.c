//###########################################################################
//
// FILE:    interrupt.c
//
// TITLE:   Interrupt software driver.
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

#include "interrupt.h"

//
// External references
//
extern const PINT __VECTOR_TABLE[NVIC_RAM_VECTOR_SIZE];

//
// Interrupt vector table in dedicated RAM section (.bss.ram.intvec / ram.intvec)
//
SECTION_RAM_VEC
static PINT Interrupt_vectorTable[NVIC_RAM_VECTOR_SIZE]
    __ALIGNED(NVIC_RAM_VECTOR_ALIGN);

//*****************************************************************************
//
// Interrupt_initModule
//
//*****************************************************************************
void
Interrupt_initModule(void)
{
    uint32_t i;

    //
    // Globally disable interrupts
    //
    (void)Interrupt_disableMaster();

    //
    // Disable and clear all NVIC interrupts
    //
    for(i = 0U; i < 8U; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFFU;
        NVIC->ICPR[i] = 0xFFFFFFFFU;
    }
}

//*****************************************************************************
//
// Interrupt_initVectorTable
//
//*****************************************************************************
void
Interrupt_initVectorTable(void)
{
    int16_t i;

    //
    // Copy 0-15 system exceptions
    //
    for(i = 0; i < 16; i++)
    {
        Interrupt_vectorTable[i] = __VECTOR_TABLE[i];
    }

    //
    // Skip the first 0-15 system exceptions
    //
    for(i = 16; i < (int16_t)NVIC_RAM_VECTOR_SIZE; i++)
    {
        Interrupt_vectorTable[i] = Interrupt_defaultHandler;
    }

    //
    // Configure the vector table location
    //
#if defined(LINKER_VECTOR_REGION_NONE)
    SCB->VTOR = (uint32_t)&__VECTOR_TABLE;
#else
    SCB->VTOR = (uint32_t)&Interrupt_vectorTable;
#endif

    __DSB();
}

//*****************************************************************************
//
// Interrupt_setPriority
//
//*****************************************************************************
void
Interrupt_setPriority(int32_t interruptNumber, uint32_t preemptPriority,
                      uint32_t subPriority)
{
    uint32_t priorityGroup;
    uint32_t priority;

    ASSERT(interruptNumber >= -12);

    //
    // Get NVIC priority group
    //
    priorityGroup = NVIC_GetPriorityGrouping();

    //
    // Combine the preemptive and sub priorities
    //
    priority = NVIC_EncodePriority(priorityGroup, preemptPriority,
                                   subPriority);

    //
    // Set the interrupt priority
    //
    NVIC_SetPriority((IRQn_Type)interruptNumber, priority);
}

//*****************************************************************************
//
// Interrupt_getPriority
//
//*****************************************************************************
void
Interrupt_getPriority(int32_t interruptNumber, uint32_t * const pPreemptPriority,
                      uint32_t * const pSubPriority)
{
    uint32_t priorityGroup;
    uint32_t priority;

    ASSERT(interruptNumber >= -12);

    //
    // Get NVIC priority group
    //
    priorityGroup = NVIC_GetPriorityGrouping();

    //
    // Get the interrupt priority
    //
    priority = NVIC_GetPriority((IRQn_Type)interruptNumber);

    //
    // Separate the preemptive and sub priorities
    //
    NVIC_DecodePriority(priority, priorityGroup, pPreemptPriority, pSubPriority);
}
