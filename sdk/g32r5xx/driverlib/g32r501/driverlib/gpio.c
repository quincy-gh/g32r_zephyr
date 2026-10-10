//###########################################################################
//
// FILE:    gpio.c
//
// TITLE:   G32R501 GPIO driver.
//
// VERSION: 1.0.1
//
// DATE:    2026-03-27
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
// 1. Macro definitions, register naming, function naming
// 2. Content of GPIO_setInterruptPin() function,
//    content of GPIO_setAnalogMode() function
// 3. New functions added: GPIO_setMaxOutputFreqEnable(),
//    GPIO_setDrivingCapability(), GPIO_setInterruptType(),
//    GPIO_getInterruptType(), GPIO_enableInterrupt(),
//    GPIO_disableInterrupt()
//
//###########################################################################

#include "gpio.h"

//*****************************************************************************
//
// GPIO_setDirectionMode
//
//*****************************************************************************
void
GPIO_setDirectionMode(uint32_t pin, GPIO_Direction pinIO)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);
    pinMask = (uint32_t)1U << (pin % 32U);

    WRPRT_DISABLE;


    //
    // Set the data direction
    //
    if(pinIO == GPIO_DIR_MODE_OUT)
    {
        //
        // Output
        //
        gpioBaseAddr[GPIO_GPxDIR_INDEX] |= pinMask;
    }
    else
    {
        //
        // Input
        //
        gpioBaseAddr[GPIO_GPxDIR_INDEX] &= ~pinMask;
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// GPIO_getDirectionMode
//
//*****************************************************************************
GPIO_Direction
GPIO_getDirectionMode(uint32_t pin)
{
    volatile uint32_t *gpioBaseAddr;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);

    return((GPIO_Direction)((gpioBaseAddr[GPIO_GPxDIR_INDEX] >>
                             (pin % 32U)) & 1U));

}

//*****************************************************************************
//
// GPIO_setInterruptPin
//
//*****************************************************************************
void
GPIO_setInterruptPin(uint32_t pin, GPIO_ExternalIntNum extIntNum)
{
    XBAR_InputNum input;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    //
    // Pick the X-BAR input that corresponds to the requested XINT.
    //
    switch(extIntNum)
    {
        case GPIO_INT_XINT1:
            input = XBAR_INPUT4;
            break;

        case GPIO_INT_XINT2:
            input = XBAR_INPUT5;
            break;

        case GPIO_INT_XINT3:
            input = XBAR_INPUT6;
            break;

        case GPIO_INT_XINT4:
            input = XBAR_INPUT13;
            break;

        case GPIO_INT_XINT5:
            input = XBAR_INPUT14;
            break;

        default:
            //
            // Invalid interrupt. Shouldn't happen if enum value is used.
            // XBAR_INPUT1 isn't tied to an XINT, so we'll use it to check for
            // a bad value.
            //
            input = (XBAR_InputNum)0xff;
            break;
    }

    if(input != 0xff)
    {
        XBAR_setInputPin(input, (uint16_t)pin);
    }
    else
    {
        //
        // Check the arguments.
        //
        ASSERT(GPIO_isPinExtiValid(pin));

        uint32_t group  = pin / 0xf;
        uint32_t offset = pin % 0xf;
        uint32_t select = ((group * 0x4) << 0x4) | (offset & 0xf);

        EXTI_setTriggerSelect(select);
    }
}

//*****************************************************************************
//
// GPIO_setPadConfig
//
//*****************************************************************************
void
GPIO_setPadConfig(uint32_t pin, uint32_t pinType)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);
    pinMask = (uint32_t)1U << (pin % 32U);

    WRPRT_DISABLE;

    //
    // Enable open drain if necessary
    //
    if((pinType & GPIO_PIN_TYPE_OD) != 0U)
    {
        gpioBaseAddr[GPIO_GPxODR_INDEX] |= pinMask;
    }
    else
    {
        gpioBaseAddr[GPIO_GPxODR_INDEX] &= ~pinMask;
    }

    //
    // Enable pull-up if necessary
    //
    if((pinType & GPIO_PIN_TYPE_PULLUP) != 0U)
    {
        gpioBaseAddr[GPIO_GPxPUD_INDEX] &= ~pinMask;
    }
    else
    {
        gpioBaseAddr[GPIO_GPxPUD_INDEX] |= pinMask;
    }

    //
    // Invert polarity if necessary
    //
    if((pinType & GPIO_PIN_TYPE_INVERT) != 0U)
    {
        gpioBaseAddr[GPIO_GPxINV_INDEX] |= pinMask;
    }
    else
    {
        gpioBaseAddr[GPIO_GPxINV_INDEX] &= ~pinMask;
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// GPIO_getPadConfig
//
//*****************************************************************************
uint32_t
GPIO_getPadConfig(uint32_t pin)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t pinMask;
    uint32_t pinTypeRes;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);
    pinMask = (uint32_t)1U << (pin % 32U);

    pinTypeRes = GPIO_PIN_TYPE_STD;

    //
    // Get open drain value
    //
    if((gpioBaseAddr[GPIO_GPxODR_INDEX] & pinMask) != 0U)
    {
        pinTypeRes |= GPIO_PIN_TYPE_OD;
    }

    //
    // Get pull-up value
    //
    if((gpioBaseAddr[GPIO_GPxPUD_INDEX] & pinMask) == 0U)
    {
        pinTypeRes |= GPIO_PIN_TYPE_PULLUP;
    }

    //
    // Get polarity value
    //
    if((gpioBaseAddr[GPIO_GPxINV_INDEX] & pinMask) != 0U)
    {
        pinTypeRes |= GPIO_PIN_TYPE_INVERT;
    }

    return(pinTypeRes);
}

//*****************************************************************************
//
// GPIO_setQualificationMode
//
//*****************************************************************************
void
GPIO_setQualificationMode(uint32_t pin, GPIO_QualificationMode qualification)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t qSelIndex;
    uint32_t shiftAmt;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);
    shiftAmt = (uint32_t)GPIO_GPAQSEL1_GPIO1_S * (pin % 16U);
    qSelIndex = GPIO_GPxQSEL_INDEX + ((pin % 32U) / 16U);

    //
    // Write the input qualification mode to the register.
    //
    WRPRT_DISABLE;

    gpioBaseAddr[qSelIndex] &= ~((uint32_t)GPIO_GPAQSEL1_GPIO0_M << shiftAmt);
    gpioBaseAddr[qSelIndex] |= (uint32_t)qualification << shiftAmt;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// GPIO_getQualificationMode
//
//*****************************************************************************
GPIO_QualificationMode
GPIO_getQualificationMode(uint32_t pin)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t qSelIndex;
    uint32_t qualRes;
    uint32_t shiftAmt;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);
    shiftAmt = (uint32_t)GPIO_GPAQSEL1_GPIO1_S * (pin % 16U);
    qSelIndex = GPIO_GPxQSEL_INDEX + ((pin % 32U) / 16U);

    //
    // Read the qualification mode register and shift and mask to get the
    // value for the specified pin.
    //
    qualRes = (gpioBaseAddr[qSelIndex] >> shiftAmt) &
              (uint32_t)GPIO_GPAQSEL1_GPIO0_M;
    return((GPIO_QualificationMode)qualRes);
}

//*****************************************************************************
//
// GPIO_setQualificationPeriod
//
//*****************************************************************************
void
GPIO_setQualificationPeriod(uint32_t pin, uint32_t divider)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t pinMask, regVal, shiftAmt;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));
    ASSERT((divider >= 1U) && (divider <= 510U));

    shiftAmt = (pin % 32U) & ~((uint32_t)0x7U);
    pinMask = (uint32_t)0xFFU << shiftAmt;

    //
    // Divide divider by two to get the value that needs to go into the field.
    // Then shift it into the right place.
    //
    regVal = (divider / 2U) << shiftAmt;

    //
    // Write the divider parameter into the register.
    //
    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);

    WRPRT_DISABLE;
    gpioBaseAddr[GPIO_GPxCTRL_INDEX] &= ~pinMask;
    gpioBaseAddr[GPIO_GPxCTRL_INDEX] |= regVal;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
// GPIO_setMasterCore
//
//*****************************************************************************
void
GPIO_setMasterCore(uint32_t pin, GPIO_CoreSelect core)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t cSelIndex;
    uint32_t shiftAmt;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);
    shiftAmt = (uint32_t)GPIO_GPACSEL1_GPIO1_S * (pin % 8U);
    cSelIndex = GPIO_GPxCSEL_INDEX + ((pin % 32U) / 8U);

    //
    // Write the core parameter into the register.
    //
    WRPRT_DISABLE;
    gpioBaseAddr[cSelIndex] &= ~((uint32_t)GPIO_GPACSEL1_GPIO0_M << shiftAmt);
    gpioBaseAddr[cSelIndex] |= (uint32_t)core << shiftAmt;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
// GPIO_setAnalogMode
//
//*****************************************************************************
void
GPIO_setAnalogMode(uint32_t pin, GPIO_AnalogMode mode)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(((pin >= 224U) && (pin <= 254U)) || (pin == 22) || (pin == 23));

    pinMask = (uint32_t)1U << (pin % 32U);
    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE +
                   ((pin / 32U) * GPIO_CTRL_REGS_STEP);

    WRPRT_DISABLE;

    //
    // Set the analog mode selection.
    //
    if(mode == GPIO_ANALOG_ENABLED)
    {
        //
        // Enable analog mode
        //
        gpioBaseAddr[GPIO_GPxAMSEL_INDEX] |= pinMask;
    }
    else
    {
        //
        // Disable analog mode
        //
        gpioBaseAddr[GPIO_GPxAMSEL_INDEX] &= ~pinMask;
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
// GPIO_setMaxOutputFreqEnable
//
//*****************************************************************************
void
GPIO_setMaxOutputFreqEnable(uint32_t pin, FunctionalState enable)
{
    uint32_t shift;

    shift = pin % 32U;
    WRPRT_DISABLE;
    switch(pin / 32U)
    {
        //
        //GPIO0-31
        //
        case 0:
            HWREG((uint32_t)GPIOCTRL_BASE + GPIO_O_GPAFEN) = (uint32_t)enable << shift;
        break;
        //
        //GPIO32-59
        //
        case 1:
            HWREG((uint32_t)GPIOCTRL_BASE + GPIO_O_GPBFEN) = (uint32_t)enable << shift;
        break;
        default:
        break;
    }
    WRPRT_ENABLE;
}

//*****************************************************************************
//
// GPIO_setDrivingCapability
//
//*****************************************************************************
void
GPIO_setDrivingCapability(uint32_t pin, GPIO_DRIVING_CAPABILITY driving)
{
    uint32_t shift,pinMask;

    shift = (pin % 16U)*2;
    pinMask = 0x03U << shift;
    WRPRT_DISABLE;
    switch(pin / 16U)
    {
        //
        //GPIO0-15
        //
        case 0:
            HWREG((uint32_t)GPIOCTRL_BASE + GPIO_O_GPADSEL1) =
                    (HWREG((uint32_t)GPIOCTRL_BASE + GPIO_O_GPADSEL1) & ~pinMask) |
                    ((uint32_t)driving << shift);
        break;
        //
        //GPIO16-31
        //
        case 1:
            HWREG((uint32_t)GPIOCTRL_BASE + GPIO_O_GPADSEL2) =
                    (HWREG((uint32_t)GPIOCTRL_BASE + GPIO_O_GPADSEL2) & ~pinMask) |
                    ((uint32_t)driving << shift);
        break;
        //
        //GPIO32-47
        //
        case 2:
            HWREG((uint32_t)GPIOCTRL_BASE + GPIO_O_GPBDSEL1) =
                    (HWREG((uint32_t)GPIOCTRL_BASE + GPIO_O_GPBDSEL1) & ~pinMask) |
                    ((uint32_t)driving << shift);
        break;
        //
        //GPIO48-59
        //
        case 3:
            HWREG((uint32_t)GPIOCTRL_BASE + GPIO_O_GPBDSEL2) =
                    (HWREG((uint32_t)GPIOCTRL_BASE + GPIO_O_GPBDSEL2) & ~pinMask) |
                    ((uint32_t)driving << shift);
        break;
        default:
        break;
    }
    WRPRT_ENABLE;
}
//*****************************************************************************
//
// GPIO_setPinConfig
//
//*****************************************************************************
void
GPIO_setPinConfig(uint32_t pinConfig)
{
    uint32_t muxRegAddr;
    uint32_t pinMask, shiftAmt;

    muxRegAddr = (uint32_t)GPIOCTRL_BASE + (pinConfig >> 16) * 2;
    shiftAmt = ((pinConfig >> 8) & (uint32_t)0xFFU);
    pinMask = (uint32_t)0x3U << shiftAmt;

    WRPRT_DISABLE;

    //
    // Clear fields in MUX register first to avoid glitches
    //
    HWREG(muxRegAddr) &= ~pinMask;

    //
    // Write value into GMUX register
    //
    HWREG(muxRegAddr + GPIO_MUX_TO_GMUX) =
        (HWREG(muxRegAddr + GPIO_MUX_TO_GMUX) & ~pinMask) |
        (((pinConfig >> 2) & (uint32_t)0x3U) << shiftAmt);

    //
    // Write value into MUX register
    //
    HWREG(muxRegAddr) |= ((pinConfig & (uint32_t)0x3U) << shiftAmt);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the interrupt type for the specified pin.
//!
//! \param extIntNum specifies the external interrupt.
//! \param intType specifies the type of interrupt trigger mechanism.
//!
//! This function sets up the various interrupt trigger mechanisms for the
//! specified pin on the selected GPIO port.
//!
//! The following defines can be used to specify the external interrupt for the
//! \e extIntNum parameter:
//!
//! - \b GPIO_INT_XINT1
//! - \b GPIO_INT_XINT2
//! - \b GPIO_INT_XINT3
//! - \b GPIO_INT_XINT4
//! - \b GPIO_INT_XINT5
//! - \b GPIO_INT_EXTI_LINE0
//! - \b GPIO_INT_EXTI_LINE1
//! - \b GPIO_INT_EXTI_LINE2
//! - \b GPIO_INT_EXTI_LINE3
//!
//! One of the following flags can be used to define the \e intType
//! parameter:
//!
//! - \b GPIO_INT_TYPE_FALLING_EDGE sets detection to edge and trigger to
//!   falling
//! - \b GPIO_INT_TYPE_RISING_EDGE sets detection to edge and trigger to rising
//! - \b GPIO_INT_TYPE_BOTH_EDGES sets detection to both edges
//!
//! \return None.
//
//*****************************************************************************
void
GPIO_setInterruptType(GPIO_ExternalIntNum extIntNum, GPIO_IntType intType)
{
    uint16_t extLine  = 0;
    switch(extIntNum)
    {
        case GPIO_INT_XINT1:
            EXTI_setTriggerEdge(EXTI_LINE_4,(EXTI_TriggerEdge)intType);
            break;

        case GPIO_INT_XINT2:
            EXTI_setTriggerEdge(EXTI_LINE_5,(EXTI_TriggerEdge)intType);
            break;

        case GPIO_INT_XINT3:
            EXTI_setTriggerEdge(EXTI_LINE_6,(EXTI_TriggerEdge)intType);
            break;

        case GPIO_INT_XINT4:
            EXTI_setTriggerEdge(EXTI_LINE_7,(EXTI_TriggerEdge)intType);
            break;

        case GPIO_INT_XINT5:
            EXTI_setTriggerEdge(EXTI_LINE_8,(EXTI_TriggerEdge)intType);
            break;

       case GPIO_INT_EXTI_LINE0:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_0) != 0)
            {
                EXTI_setTriggerEdge(EXTI_LINE_0,(EXTI_TriggerEdge)intType);
            }
        break;

        case GPIO_INT_EXTI_LINE1:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_1) != 0)
            {
                EXTI_setTriggerEdge(EXTI_LINE_1,(EXTI_TriggerEdge)intType);
            }
        break;

        case GPIO_INT_EXTI_LINE2:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_2) != 0)
            {
                EXTI_setTriggerEdge(EXTI_LINE_2,(EXTI_TriggerEdge)intType);
            }
        break;

        case GPIO_INT_EXTI_LINE3:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_3) != 0)
            {
                EXTI_setTriggerEdge(EXTI_LINE_3,(EXTI_TriggerEdge)intType);
            }
        break;

        default:
            break;
    }
}

//*****************************************************************************
//
//! Gets the interrupt type for a pin.
//!
//! \param extIntNum specifies the external interrupt.
//!
//! This function gets the interrupt type for a interrupt. The interrupt can be
//! configured as a falling-edge, rising-edge, or both-edges detected
//! interrupt.
//!
//! The following defines can be used to specify the external interrupt for the
//! \e extIntNum parameter:
//!
//! - \b GPIO_INT_XINT1
//! - \b GPIO_INT_XINT2
//! - \b GPIO_INT_XINT3
//! - \b GPIO_INT_XINT4
//! - \b GPIO_INT_XINT5
//! - \b GPIO_INT_EXTI_LINE0
//! - \b GPIO_INT_EXTI_LINE1
//! - \b GPIO_INT_EXTI_LINE2
//! - \b GPIO_INT_EXTI_LINE3
//!
//! \return Returns one of the flags described for GPIO_setInterruptType().
//
//*****************************************************************************
GPIO_IntType
GPIO_getInterruptType(GPIO_ExternalIntNum extIntNum)
{
    uint16_t extLine  = 0;
     switch(extIntNum)
    {
        case GPIO_INT_XINT1:
            return (GPIO_IntType) EXTI_getTriggerEdge(EXTI_LINE_4);

        case GPIO_INT_XINT2:
            return (GPIO_IntType) EXTI_getTriggerEdge(EXTI_LINE_5);

        case GPIO_INT_XINT3:
            return (GPIO_IntType) EXTI_getTriggerEdge(EXTI_LINE_6);

        case GPIO_INT_XINT4:
            return (GPIO_IntType) EXTI_getTriggerEdge(EXTI_LINE_7);

        case GPIO_INT_XINT5:
            return (GPIO_IntType) EXTI_getTriggerEdge(EXTI_LINE_8);

        case GPIO_INT_EXTI_LINE0:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_0) != 0)
            {
                return  (GPIO_IntType) EXTI_getTriggerEdge(EXTI_LINE_0);
            }

        case GPIO_INT_EXTI_LINE1:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_1) != 0)
            {
                return  (GPIO_IntType) EXTI_getTriggerEdge(EXTI_LINE_1);
            }

        case GPIO_INT_EXTI_LINE2:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_2) != 0)
            {
                return  (GPIO_IntType) EXTI_getTriggerEdge(EXTI_LINE_2);
            }

        case GPIO_INT_EXTI_LINE3:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_3) != 0)
            {
                return  (GPIO_IntType) EXTI_getTriggerEdge(EXTI_LINE_3);
            }

        default:
            return (GPIO_IntType)0xff;
    }

}

//*****************************************************************************
//
//! Enables the specified external interrupt.
//!
//! \param extIntNum specifies the external interrupt.
//!
//! This function enables the indicated external interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! The following defines can be used to specify the external interrupt for the
//! \e extIntNum parameter:
//!
//! - \b GPIO_INT_XINT1
//! - \b GPIO_INT_XINT2
//! - \b GPIO_INT_XINT3
//! - \b GPIO_INT_XINT4
//! - \b GPIO_INT_XINT5
//!
//! \return None.
//
//*****************************************************************************
void
GPIO_enableInterrupt(GPIO_ExternalIntNum extIntNum)
{
    uint16_t extLine  = 0;
    switch(extIntNum)
    {
        case GPIO_INT_XINT1:
            EXTI_enableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_4);
            break;

        case GPIO_INT_XINT2:
             EXTI_enableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_5);
            break;

        case GPIO_INT_XINT3:
             EXTI_enableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_6);
            break;

        case GPIO_INT_XINT4:
             EXTI_enableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_7);
            break;

        case GPIO_INT_XINT5:
             EXTI_enableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_8);
            break;

        case GPIO_INT_EXTI_LINE0:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_0) != 0)
            {
                EXTI_enableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_0);
            }
        break;

        case GPIO_INT_EXTI_LINE1:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_1) != 0)
            {
                EXTI_enableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_1);
            }
        break;

        case GPIO_INT_EXTI_LINE2:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_2) != 0)
            {
                EXTI_enableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_2);
            }
        break;

        case GPIO_INT_EXTI_LINE3:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_3) != 0)
            {
                EXTI_enableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_3);
            }
        break;

        default:
            break;
    }


}

//*****************************************************************************
//
//! Disables the specified external interrupt.
//!
//! \param extIntNum specifies the external interrupt.
//!
//! This function disables the indicated external interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! The following defines can be used to specify the external interrupt for the
//! \e extIntNum parameter:
//!
//! - \b GPIO_INT_XINT1
//! - \b GPIO_INT_XINT2
//! - \b GPIO_INT_XINT3
//! - \b GPIO_INT_XINT4
//! - \b GPIO_INT_XINT5
//!
//! \return None.
//
//*****************************************************************************
void
GPIO_disableInterrupt(GPIO_ExternalIntNum extIntNum)
{
    uint16_t extLine  = 0;
    switch(extIntNum)
    {
        case GPIO_INT_XINT1:
            EXTI_disableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_4);
        break;

        case GPIO_INT_XINT2:
            EXTI_disableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_5);
        break;

        case GPIO_INT_XINT3:
            EXTI_disableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_6);
        break;

        case GPIO_INT_XINT4:
            EXTI_disableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_7);
        break;

        case GPIO_INT_XINT5:
            EXTI_disableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_8);
        break;

        case GPIO_INT_EXTI_LINE0:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_0) != 0)
            {
                EXTI_disableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_0);
            }
        break;

        case GPIO_INT_EXTI_LINE1:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_1) != 0)
            {
                EXTI_disableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_1);
            }
        break;

        case GPIO_INT_EXTI_LINE2:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_2) != 0)
            {
                EXTI_disableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_2);
            }
        break;

        case GPIO_INT_EXTI_LINE3:
            extLine = EXTI_getTrigger();
            if((extLine & GPIO_EXTI_LINE_3) != 0)
            {
                EXTI_disableInterrupt(EXTI_CORE_CPU0,EXTI_LINE_3);
            }
        break;

        default:

        break;
    }


}


