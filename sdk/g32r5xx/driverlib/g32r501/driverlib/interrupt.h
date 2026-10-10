//###########################################################################
//
// FILE:    interrupt.h
//
// TITLE:   Interrupt software driver.
//
// VERSION: 1.0.1
//
// DATE:    2026-02-25
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

#ifndef INTERRUPT_H
#define INTERRUPT_H

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

//*****************************************************************************
//
//! \addtogroup interrupt_api Interrupt
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

#ifndef __interrupt
#define __interrupt 
#endif
#ifndef interrupt
#define interrupt __interrupt
#endif

//*****************************************************************************
//
// Values that can be passed to Interrupt_setPriorityGroup() as the
// priorityGroup and returned by Interrupt_getPriorityGroup().
//
// NOTE:
// These macros represent the PRIGROUP field value written into SCB->AIRCR.
// The effective split between preempt priority bits and subpriority bits is
// determined by the combination of PRIGROUP and __NVIC_PRIO_BITS inside CMSIS
// NVIC_EncodePriority()/NVIC_DecodePriority().
//
//*****************************************************************************
#define INTERRUPT_PRIGROUP_PREEMPT_3_0_SUB_NO    (0x0U)
#define INTERRUPT_PRIGROUP_PREEMPT_3_1_SUB_0     (0x4U)
#define INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0   (0x5U)
#define INTERRUPT_PRIGROUP_PREEMPT_3_SUB_2_0     (0x6U)
#define INTERRUPT_PRIGROUP_PREEMPT_NO_SUB_3_0    (0x7U)

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! The default interrupt handler.
//!
//! This is the default interrupt handler.  The Interrupt_initVectorTable()
//! function sets all vectors to this function.  Also, when an interrupt is
//! unregistered using the Interrupt_unregister() function, this handler takes
//! its place.  This should never be called during normal operation.
//!
//! The ESTOP0 statement is for debug purposes only. Remove and replace with an
//! appropriate error handling routine for your program.
//!
//! \return None.
//
//*****************************************************************************
static void Interrupt_defaultHandler(void)
{
    uint32_t vectID;

    //
    // Get the vector ID. (bits 8:0 of XPSR.Exception)
    //
    vectID = __get_xPSR() & 0x1FFU;
    
    (void)vectID; 

    //
    // Something has gone wrong. An interrupt without a proper registered
    // handler function has occurred.
    //
    ESTOP0;
    for(;;)
    {
        ;
    }
}

//*****************************************************************************
//
//! Allows the CPU to process interrupts.
//!
//! This function clears the global interrupt mask bit (PRIMASK) in the CPU,
//! allowing the processor to respond to interrupts.
//!
//! \return Returns \b true if interrupts were disabled when the function was
//! called or \b false if they were initially enabled.
//
//*****************************************************************************
static inline bool
Interrupt_enableMaster(void)
{
    uint32_t regPrimask;

    //
    // Get the previous value of PRIMASK
    //
    regPrimask = __get_PRIMASK();

    //
    // Enable processor interrupts
    //
    EINT;

    return(((regPrimask & 0x1U) != 0U) ? true : false);
}

//*****************************************************************************
//
//! Stops the CPU from processing interrupts.
//!
//! This function sets the global interrupt mask bit (PRIMASK) in the CPU,
//! preventing the processor from receiving maskable interrupts.
//!
//! \return Returns \b true if interrupts were already disabled when the
//! function was called or \b false if they were initially disabled.
//
//*****************************************************************************
static inline bool
Interrupt_disableMaster(void)
{
    uint32_t regPrimask;

    //
    // Get the previous value of PRIMASK
    //
    regPrimask = __get_PRIMASK();

    //
    // Disable processor interrupts
    //
    DINT;

    return(((regPrimask & 0x1U) != 0U) ? true : false);
}

//*****************************************************************************
//
//! Registers a function to be called when an interrupt occurs.
//!
//! \param interruptNumber specifies the interrupt in question.
//! \param handler is a pointer to the function to be called.
//!
//! This function is used to specify the handler function to be called when the
//! given interrupt is asserted to the processor.  When the interrupt occurs,
//! if it is enabled (via Interrupt_enable()), the handler function will be
//! called in interrupt context.  Since the handler function can preempt other
//! code, care must be taken to protect memory or peripherals that are accessed
//! by the handler and other non-handler code.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_register(int32_t interruptNumber, void (*handler)(void))
{
    //
    // Copy ISR address into remap table
    //
    NVIC_SetVector((IRQn_Type)interruptNumber, (uint32_t)handler);
}

//*****************************************************************************
//
//! Unregisters the function to be called when an interrupt occurs.
//!
//! \param interruptNumber specifies the interrupt in question.
//!
//! This function is used to indicate that a default handler
//! Interrupt_defaultHandler() should be called when the given interrupt is
//! asserted to the processor.  Call Interrupt_disable() to disable
//! the interrupt before calling this function.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>hw_ints.h</tt>.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_unregister(int32_t interruptNumber)
{
    //
    // Copy default ISR address into remap table
    //
    NVIC_SetVector((IRQn_Type)interruptNumber, (uint32_t)Interrupt_defaultHandler);
}

//*****************************************************************************
//
//! Sets a pending interrupt.
//!
//! \param interruptNumber specifies the relevant interrupt.
//!
//! This function sets the pending bit of a specific interrupt in the NVIC
//! pending register.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_setPending(int32_t interruptNumber)
{
    ASSERT(interruptNumber >= 0);

    NVIC_SetPendingIRQ((IRQn_Type)interruptNumber);
}

//*****************************************************************************
//
//! Gets a pending interrupt.
//!
//! \param interruptNumber specifies the relevant interrupt.
//!
//! This function gets the pending bit of a specific interrupt in the NVIC
//! pending register.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>hw_ints.h</tt>.
//!
//! \return Returns \b true if the interrupt is pending or \b false if it is
//! not.
//
//*****************************************************************************
static inline bool
Interrupt_getPending(int32_t interruptNumber)
{
    ASSERT(interruptNumber >= 0);

    return(NVIC_GetPendingIRQ((IRQn_Type)interruptNumber) != 0U);
}

//*****************************************************************************
//
//! Clears a pending interrupt.
//!
//! \param interruptNumber specifies the relevant interrupt.
//!
//! This function clears the pending bit of a specific interrupt in the NVIC
//! pending register.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>hw_ints.h</tt>.
//!
//! \return None.

//*****************************************************************************
static inline void
Interrupt_clearPending(int32_t interruptNumber)
{
    ASSERT(interruptNumber >= 0);

    NVIC_ClearPendingIRQ((IRQn_Type)interruptNumber);
}

//*****************************************************************************
//
//! Sets NVIC interrupt priority group.
//!
//! \param priorityGroup is the priority group to indicate the preemptive and
//! sub priority bits in priority registers.
//!
//! This function sets NVIC interrupt priority group.
//!
//! The \e priorityGroup parameter can be any one of the following:
//! - \b INTERRUPT_PRIGROUP_PREEMPT_3_0_SUB_NO
//! - \b INTERRUPT_PRIGROUP_PREEMPT_3_1_SUB_0
//! - \b INTERRUPT_PRIGROUP_PREEMPT_3_2_SUB_1_0
//! - \b INTERRUPT_PRIGROUP_PREEMPT_3_SUB_2_0
//! - \b INTERRUPT_PRIGROUP_PREEMPT_NO_SUB_3_0
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_setPriorityGroup(uint32_t priorityGroup)
{
    ASSERT(priorityGroup <= 7U);
    NVIC_SetPriorityGrouping(priorityGroup);
}

//*****************************************************************************
//
//! Gets NVIC interrupt priority group.
//!
//! This function gets NVIC interrupt priority group.
//!
//! \return Return the interrupt priority group, specified as one of
//! \b INTERRUPT_PRIGROUP_PREEMPT_* values in this header.
//
//*****************************************************************************
static inline uint32_t
Interrupt_getPriorityGroup(void)
{
    return(NVIC_GetPriorityGrouping());
}

//*****************************************************************************
//
//! Enables an interrupt.
//!
//! \param interruptNumber specifies the interrupt to be enabled.
//!
//! The specified interrupt is enabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_enable(int32_t interruptNumber)
{
    ASSERT(interruptNumber >= 0);

    NVIC_EnableIRQ((IRQn_Type)interruptNumber);
}

//*****************************************************************************
//
//! Disables an interrupt.
//!
//! \param interruptNumber specifies the interrupt to be disabled.
//!
//! The specified interrupt is disabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_disable(int32_t interruptNumber)
{
    ASSERT(interruptNumber >= 0);

    NVIC_DisableIRQ((IRQn_Type)interruptNumber);
}

//*****************************************************************************
//
//! Initializes the NVIC control registers by setting them to a known state.
//!
//! This function initializes the NVIC control registers. After globally
//! disabling interrupts and enabling the NVIC, it clears all of the NVIC
//! interrupt enable bits and interrupt flags.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_initModule(void);

//*****************************************************************************
//
//! Initializes the NVIC vector table by setting all vectors to a default
//! handler function.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_initVectorTable(void);

//*****************************************************************************
//
//! Sets the preemptive and sub priorities.
//!
//! \param interruptNumber specifies the relevant interrupt.
//! \param preemptPriority is the preemptive priority, and the value is
//! determined by __NVIC_PRIO_BITS and priority group.
//! \param subPriority is the sub-priority, and the value is determined by
//! __NVIC_PRIO_BITS and priority group.
//!
//! This function sets the preemptive and sub priorities.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_setPriority(int32_t interruptNumber, uint32_t preemptPriority,
                      uint32_t subPriority);

//*****************************************************************************
//
//! Gets the preemptive and sub priorities.
//!
//! \param interruptNumber specifies the relevant interrupt.
//! \param pPreemptPriority points to preemptive priority.
//! \param pSubPriority points to sub-priority.
//!
//! This function gets the preemptive and sub priorities.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_getPriority(int32_t interruptNumber, uint32_t * const pPreemptPriority,
                      uint32_t * const pSubPriority);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // INTERRUPT_H
