//###########################################################################
//
// FILE:    exti.c
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

#include "exti.h"

//*****************************************************************************
//
// EXTI_setTriggerEdge
//
//*****************************************************************************
void
EXTI_setTriggerEdge(EXTI_LineNumber lineNumber, EXTI_TriggerEdge edge)
{
    uint32_t bitMask;

    ASSERT(lineNumber <= EXTI_LINE_12);

    //
    // Get the register bit mask
    //
    bitMask = 1U << (uint32_t)lineNumber;

    WRPRT_DISABLE;
    if(edge == EXTI_TRIGGER_EDGE_NONE)
    {
        HWREG(EXTI_BASE + EXTI_O_RTEN) &= ~bitMask;
        HWREG(EXTI_BASE + EXTI_O_FTEN) &= ~bitMask;
    }
    else if(edge == EXTI_TRIGGER_EDGE_RISING)
    {
        HWREG(EXTI_BASE + EXTI_O_RTEN) |= bitMask;
        HWREG(EXTI_BASE + EXTI_O_FTEN) &= ~bitMask;
    }
    else if(edge == EXTI_TRIGGER_EDGE_FALLING)
    {
        HWREG(EXTI_BASE + EXTI_O_RTEN) &= ~bitMask;
        HWREG(EXTI_BASE + EXTI_O_FTEN) |= bitMask;
    }
    else
    {
        HWREG(EXTI_BASE + EXTI_O_RTEN) |= bitMask;
        HWREG(EXTI_BASE + EXTI_O_FTEN) |= bitMask;
    }
    WRPRT_ENABLE;
}

//*****************************************************************************
//
// EXTI_getTriggerEdge
//
//*****************************************************************************
EXTI_TriggerEdge
EXTI_getTriggerEdge(EXTI_LineNumber lineNumber)
{
    uint32_t bitMask;

    ASSERT(lineNumber <= EXTI_LINE_12);

    //
    // Get the register bit mask
    //
    bitMask = 1U << (uint32_t)lineNumber;

    if(((HWREG(EXTI_BASE + EXTI_O_RTEN) & bitMask) != 0U) &&
       ((HWREG(EXTI_BASE + EXTI_O_FTEN) & bitMask) != 0U))
    {
        return(EXTI_TRIGGER_EDGE_BOTH);
    }
    else if((HWREG(EXTI_BASE + EXTI_O_RTEN) & bitMask) != 0U)
    {
        return(EXTI_TRIGGER_EDGE_RISING);
    }
    else if((HWREG(EXTI_BASE + EXTI_O_FTEN) & bitMask) != 0U)
    {
        return(EXTI_TRIGGER_EDGE_FALLING);
    }
    else
    {
        return(EXTI_TRIGGER_EDGE_NONE);
    }
}
