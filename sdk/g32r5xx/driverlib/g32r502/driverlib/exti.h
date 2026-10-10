//###########################################################################
//
// FILE:    exti.h
//
// TITLE:   EXTI driver.
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
#ifndef EXTI_H
#define EXTI_H

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
//! \addtogroup exti_api EXTI
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_exti.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
//! Register bit shift and mask
#define EXIT_GPIO_TRI_SELx_SHIFT   4U
#define EXIT_GPIO_TRI_SELx_MASK    0xFU
#define EXIT_INTx_COUNTER_MASK     0xFFFFU

//! Register address step
#define EXIT_INTx_COUNTER_STEP   (EXTI_O_INT5CNT - EXTI_O_INT4CNT)

//*****************************************************************************
//
// Values that can be passed to EXTI_setTriggerSelect() as the select
// parameter.
//
//*****************************************************************************
//! GPIO_TRI_SEL0 Config Macros
#define EXTI_GPIO_TRI_SEL0_GPIO0    0x00U
#define EXTI_GPIO_TRI_SEL0_GPIO1    0x01U
#define EXTI_GPIO_TRI_SEL0_GPIO2    0x02U
#define EXTI_GPIO_TRI_SEL0_GPIO3    0x03U
#define EXTI_GPIO_TRI_SEL0_GPIO4    0x04U
#define EXTI_GPIO_TRI_SEL0_GPIO5    0x05U
#define EXTI_GPIO_TRI_SEL0_GPIO6    0x06U
#define EXTI_GPIO_TRI_SEL0_GPIO7    0x07U
#define EXTI_GPIO_TRI_SEL0_GPIO8    0x08U
#define EXTI_GPIO_TRI_SEL0_GPIO9    0x09U
#define EXTI_GPIO_TRI_SEL0_GPIO10   0x0AU
#define EXTI_GPIO_TRI_SEL0_GPIO11   0x0BU
#define EXTI_GPIO_TRI_SEL0_GPIO12   0x0CU
#define EXTI_GPIO_TRI_SEL0_GPIO13   0x0DU
#define EXTI_GPIO_TRI_SEL0_GPIO14   0x0EU

//! GPIO_TRI_SEL1 Config Macros
#define EXTI_GPIO_TRI_SEL1_GPIO15   0x40U
#define EXTI_GPIO_TRI_SEL1_GPIO16   0x41U
#define EXTI_GPIO_TRI_SEL1_GPIO17   0x42U
#define EXTI_GPIO_TRI_SEL1_GPIO18   0x43U
#define EXTI_GPIO_TRI_SEL1_GPIO19   0x44U
#define EXTI_GPIO_TRI_SEL1_GPIO20   0x45U
#define EXTI_GPIO_TRI_SEL1_GPIO21   0x46U
#define EXTI_GPIO_TRI_SEL1_GPIO22   0x47U
#define EXTI_GPIO_TRI_SEL1_GPIO23   0x48U
#define EXTI_GPIO_TRI_SEL1_GPIO24   0x49U
#define EXTI_GPIO_TRI_SEL1_GPIO25   0x4AU
#define EXTI_GPIO_TRI_SEL1_GPIO26   0x4BU
#define EXTI_GPIO_TRI_SEL1_GPIO27   0x4CU
#define EXTI_GPIO_TRI_SEL1_GPIO28   0x4DU
#define EXTI_GPIO_TRI_SEL1_GPIO29   0x4EU

//! GPIO_TRI_SEL2 Config Macros
#define EXTI_GPIO_TRI_SEL2_GPIO30   0x80U
#define EXTI_GPIO_TRI_SEL2_GPIO31   0x81U
#define EXTI_GPIO_TRI_SEL2_GPIO32   0x82U
#define EXTI_GPIO_TRI_SEL2_GPIO33   0x83U
#define EXTI_GPIO_TRI_SEL2_GPIO34   0x84U
#define EXTI_GPIO_TRI_SEL2_GPIO35   0x85U
#define EXTI_GPIO_TRI_SEL2_GPIO36   0x86U
#define EXTI_GPIO_TRI_SEL2_GPIO37   0x87U
#define EXTI_GPIO_TRI_SEL2_GPIO38   0x88U
#define EXTI_GPIO_TRI_SEL2_GPIO39   0x89U
#define EXTI_GPIO_TRI_SEL2_GPIO40   0x8AU
#define EXTI_GPIO_TRI_SEL2_GPIO41   0x8BU
#define EXTI_GPIO_TRI_SEL2_GPIO42   0x8CU
#define EXTI_GPIO_TRI_SEL2_GPIO43   0x8DU
#define EXTI_GPIO_TRI_SEL2_GPIO44   0x8EU

//! GPIO_TRI_SEL3 Config Macros
#define EXTI_GPIO_TRI_SEL3_GPIO45   0xC0U
#define EXTI_GPIO_TRI_SEL3_GPIO46   0xC1U
#define EXTI_GPIO_TRI_SEL3_GPIO47   0xC2U
#define EXTI_GPIO_TRI_SEL3_GPIO48   0xC3U
#define EXTI_GPIO_TRI_SEL3_GPIO49   0xC4U
#define EXTI_GPIO_TRI_SEL3_GPIO50   0xC5U
#define EXTI_GPIO_TRI_SEL3_GPIO51   0xC6U
#define EXTI_GPIO_TRI_SEL3_GPIO52   0xC7U
#define EXTI_GPIO_TRI_SEL3_GPIO53   0xC8U
#define EXTI_GPIO_TRI_SEL3_GPIO54   0xC9U
#define EXTI_GPIO_TRI_SEL3_GPIO55   0xCAU
#define EXTI_GPIO_TRI_SEL3_GPIO56   0xCBU
#define EXTI_GPIO_TRI_SEL3_GPIO57   0xCCU
#define EXTI_GPIO_TRI_SEL3_GPIO58   0xCDU
#define EXTI_GPIO_TRI_SEL3_GPIO59   0xCEU

//*****************************************************************************
//
//! Values that can be returned by EXTI_getTrigger().
//
//*****************************************************************************
#define GPIO_EXTI_LINE_0 1U
#define GPIO_EXTI_LINE_1 2U
#define GPIO_EXTI_LINE_2 4U
#define GPIO_EXTI_LINE_3 8U

//*****************************************************************************
//
//! Values that can be passed to EXTI_forceTrigger(), EXTI_enableInterrupt(),
//! EXTI_disableInterrupt(), EXTI_enableEvent(), EXTI_disableEvent(),
//! EXTI_getInterruptStatus(), EXTI_clearInterruptStatus(),
//! EXTI_getInterruptCounter(), EXTI_setTriggerEdge() and EXTI_getTriggerEdge()
//! as the \e lineNumber parameter.
//
//*****************************************************************************
typedef enum{
    EXTI_LINE_0  = 0,
    EXTI_LINE_1  = 1,
    EXTI_LINE_2  = 2,
    EXTI_LINE_3  = 3,
    EXTI_LINE_4  = 4,
    EXTI_LINE_5  = 5,
    EXTI_LINE_6  = 6,
    EXTI_LINE_7  = 7,
    EXTI_LINE_8  = 8,
    EXTI_LINE_9  = 9,
    EXTI_LINE_10 = 10,
    EXTI_LINE_11 = 11,
    EXTI_LINE_12 = 12
} EXTI_LineNumber;

//*****************************************************************************
//
//! Values that can be passed to EXTI_setTriggerEdge() as the \e edge parameter
//! and returned by EXTI_getTriggerEdge().
//
//*****************************************************************************
typedef enum{
    EXTI_TRIGGER_EDGE_NONE,
    EXTI_TRIGGER_EDGE_RISING,
    EXTI_TRIGGER_EDGE_FALLING,
    EXTI_TRIGGER_EDGE_BOTH
} EXTI_TriggerEdge;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Forces the software trigger.
//!
//! \param lineNumber is the line number, specified as \b EXTI_LINE_X where X
//! is a number between 0 and 12.
//!
//! This function forces to trigger interrupt and event.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EXTI_forceTrigger(EXTI_LineNumber lineNumber)
{
    ASSERT(lineNumber <= EXTI_LINE_12);

    WRPRT_DISABLE;
    HWREG(EXTI_BASE + EXTI_O_SWINTE) |= (1U << (uint32_t)lineNumber);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the GPIO trigger select.
//!
//! \param select is the GPIO trigger select, specified as
//! \b EXTI_GPIO_TRI_SEL0_GPIO0, ... or \b EXTI_GPIO_TRI_SEL3_GPIO59.
//!
//! This function sets the GPIO trigger select for external interrupt line 0 to
//! 3.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EXTI_setTriggerSelect(uint32_t select)
{
    uint32_t regValue;
    uint32_t shiftAmt;

    //
    // Get the register value and shift amount
    //
    regValue = select & 0xFU;
    shiftAmt = (select >> 4U) & 0xFU;

    WRPRT_DISABLE;
    HWREG(EXTI_BASE + EXTI_O_GPIOSEL) =
        (HWREG(EXTI_BASE + EXTI_O_GPIOSEL) &
         ~(EXIT_GPIO_TRI_SELx_MASK << shiftAmt)) | (regValue << shiftAmt);
    WRPRT_ENABLE;
}


//*****************************************************************************
//
//! Gets the trigger external interrupe lines.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static inline uint16_t 
EXTI_getTrigger(void)
{
    uint16_t extLine  = 0;
    if((HWREGH(EXTI_BASE + EXTI_O_GPIOSEL) & (EXIT_GPIO_TRI_SELx_MASK << 0)) != 0)
   {
        extLine |= GPIO_EXTI_LINE_0;
    }
    if((HWREGH(EXTI_BASE + EXTI_O_GPIOSEL) & (EXIT_GPIO_TRI_SELx_MASK << 4U)) != 0)
   {
        extLine |= GPIO_EXTI_LINE_1;
    }
    if((HWREGH(EXTI_BASE + EXTI_O_GPIOSEL) & (EXIT_GPIO_TRI_SELx_MASK << 8U)) != 0)
   {
        extLine |= GPIO_EXTI_LINE_2;
    }
    if((HWREGH(EXTI_BASE + EXTI_O_GPIOSEL) & (EXIT_GPIO_TRI_SELx_MASK << 12U)) != 0)
   {
        extLine |= GPIO_EXTI_LINE_3;
    }
    return extLine;
}

//*****************************************************************************
//
//! Enables the external interrupt.
//!
//! \param lineNumber is the line number, specified as \b EXTI_LINE_X where X
//! is a number between 0 and 12.
//!
//! This function enables the interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EXTI_enableInterrupt(EXTI_LineNumber lineNumber)
{
    ASSERT(lineNumber <= EXTI_LINE_12);

    WRPRT_DISABLE;

    HWREG(EXTI_BASE + EXTI_O_IMASK) |= (1U << (uint32_t)lineNumber);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables the external interrupt.
//!
//! \param lineNumber is the line number, specified as \b EXTI_LINE_X where X
//! is a number between 0 and 12.
//!
//! This function disables the external interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EXTI_disableInterrupt(EXTI_LineNumber lineNumber)
{
    ASSERT(lineNumber <= EXTI_LINE_12);

    WRPRT_DISABLE;

    HWREG(EXTI_BASE + EXTI_O_IMASK) &= ~(1U << (uint32_t)lineNumber);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables the external event.
//!
//! \param lineNumber is the line number, specified as \b EXTI_LINE_X where X
//! is a number between 0 and 12.
//!
//! This function enables the external event.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EXTI_enableEvent(EXTI_LineNumber lineNumber)
{
    ASSERT(lineNumber <= EXTI_LINE_12);

    WRPRT_DISABLE;

    HWREG(EXTI_BASE + EXTI_O_EMASK) |= (1U << (uint32_t)lineNumber);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables the external event.
//!
//! \param lineNumber is the line number, specified as \b EXTI_LINE_X where X
//! is a number between 0 and 12.
//!
//! This function disables the external event.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EXTI_disableEvent(EXTI_LineNumber lineNumber)
{
    ASSERT(lineNumber <= EXTI_LINE_12);

    WRPRT_DISABLE;

    HWREG(EXTI_BASE + EXTI_O_EMASK) &= ~(1U << (uint32_t)lineNumber);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the external interrupt status.
//!
//! \param lineNumber is the line number, specified as \b EXTI_LINE_X where X
//! is a number between 0 and 12.
//!
//! This function gets the external interrupt status.
//!
//! \return \b true if the external interrupt status is set and \b false if it
//! is not.
//
//*****************************************************************************
static inline bool
EXTI_getInterruptStatus(EXTI_LineNumber lineNumber)
{
    ASSERT(lineNumber <= EXTI_LINE_12);

    return((HWREG(EXTI_BASE + EXTI_O_IPEND) &
        (1U << (uint32_t)lineNumber)) != 0);

}

//*****************************************************************************
//
//! Clears the external interrupt status.
//!
//! \param lineNumber is the line number, specified as \b EXTI_LINE_X where X
//! is a number between 0 and 12.
//!
//! This function clears the external interrupt status.
//!
//! \return None.
//
//*****************************************************************************
static inline void
EXTI_clearInterruptStatus(EXTI_LineNumber lineNumber)
{
    ASSERT(lineNumber <= EXTI_LINE_12);

    WRPRT_DISABLE;

    HWREG(EXTI_BASE + EXTI_O_IPEND) |= ~(1U << (uint32_t)lineNumber);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the interrupt counter.
//!
//! \param lineNumber is the line number, specified as \b EXTI_LINE_X where X
//! is a number between 4 and 6.
//!
//! This function gets the interrupt counter.
//!
//! \return Returns the interrupt counter.
//
//*****************************************************************************
static inline uint16_t
EXTI_getInterruptCounter(EXTI_LineNumber lineNumber)
{
    uint32_t ctrRegAddr;

    ASSERT((lineNumber == EXTI_LINE_4) ||
           (lineNumber == EXTI_LINE_5) ||
           (lineNumber == EXTI_LINE_6));

    //
    // Get the interrupt counter register address
    //
    ctrRegAddr = EXTI_BASE + EXTI_O_INT4CNT +
                 (((uint32_t)lineNumber - EXTI_LINE_4) *
                  EXIT_INTx_COUNTER_STEP);

    //
    // Return the interrupt counter value
    //
    return((uint16_t)(HWREG(ctrRegAddr) & EXIT_INTx_COUNTER_MASK));
}

//*****************************************************************************
//
//! Sets the trigger edge.
//!
//! \param lineNumber is the line number, specified as \b EXTI_LINE_X where X
//! is a number between 0 and 12.
//! \param edge is the trigger edge, specified as \b EXTI_TRIGGER_EDGE_NONE,
//! \b EXTI_TRIGGER_EDGE_RISING, \b EXTI_TRIGGER_EDGE_FALIING or
//! \b EXTI_TRIGGER_EDGE_BOTH.
//!
//! This function sets the trigger edge.
//!
//! \return None.
//
//*****************************************************************************
extern void
EXTI_setTriggerEdge(EXTI_LineNumber lineNumber, EXTI_TriggerEdge edge);

//*****************************************************************************
//
//! Gets the trigger edge.
//!
//! \param lineNumber is the line number, specified as \b EXTI_LINE_X where X
//! is a number between 0 and 12.
//!
//! This function gets the trigger edge.
//!
//! \return Returns the trigger edge.
//
//*****************************************************************************
extern EXTI_TriggerEdge
EXTI_getTriggerEdge(EXTI_LineNumber lineNumber);

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

#endif
