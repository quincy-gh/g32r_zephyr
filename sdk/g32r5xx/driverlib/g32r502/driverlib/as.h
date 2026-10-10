//###########################################################################
//
// FILE:    as.h
//
// TITLE:   G32R502 driver for Analog System Control.
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
// 1. Partial comments, macro definitions, module names, enum names,
//   and some function names.
// 2. Deleted some API functions.
//
//###########################################################################

#ifndef AS_H
#define AS_H

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
//! \addtogroup as_api AS
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_as.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "debug.h"
#include "cpu.h"
#include "sysctl.h"

//*****************************************************************************
//
// Defines used for setting AnalogReference functions.
// AS_setAnalogReferenceInternal()
// AS_setAnalogReferenceExternal()
//
//*****************************************************************************
#define AS_VREFHIA  AS_ANAREFCTL_ANAREFASEL_M //!< VREFHIA
#define AS_VREFHIC  AS_ANAREFCTL_ANAREFCSEL_M //!< VREFHIC
#define AS_VREFHIA_2P5  AS_ANAREFCTL_ANAREFA2P5SEL_M //!< VREFHIA 2.5V select mask
#define AS_VREFHIC_2P5  AS_ANAREFCTL_ANAREFC2P5SEL   //!< VREFHIC 2.5V select

//*****************************************************************************
//
// Values used for function AS_selectCMPHNMux() and
// AS_selectCMPHNMuxValue().  These values can be OR-ed together and
// passed to AS_selectCMPHNMux().
//
//*****************************************************************************
#define AS_CMPHNMUX_SELECT_1 0x1U  //!< CMPHNMUX select 1
#define AS_CMPHNMUX_SELECT_2 0x2U  //!< CMPHNMUX select 2
#define AS_CMPHNMUX_SELECT_3 0x4U  //!< CMPHNMUX select 3
#define AS_CMPHNMUX_SELECT_4 0x8U  //!< CMPHNMUX select 4

//*****************************************************************************
//
// Values used for function AS_selectCMPLNMux() and
// AS_selectCMPLNMuxValue().  These values can be OR-ed together and
// passed to AS_selectCMPLNMux().
//
//*****************************************************************************
#define AS_CMPLNMUX_SELECT_1 0x1U  //!< CMPLNMUX select 1
#define AS_CMPLNMUX_SELECT_2 0x2U  //!< CMPLNMUX select 2
#define AS_CMPLNMUX_SELECT_3 0x4U  //!< CMPLNMUX select 3
#define AS_CMPLNMUX_SELECT_4 0x8U  //!< CMPLNMUX select 4

//*****************************************************************************
//
//! AS_CMPHPMuxSelect used for function AS_selectCMPHPMux().
//
//*****************************************************************************
typedef enum
{
    AS_CMPHPMUX_SELECT_1 = 0U,  //!< CMPHPMUX select 1
    AS_CMPHPMUX_SELECT_2 = 3U,  //!< CMPHPMUX select 2
    AS_CMPHPMUX_SELECT_3 = 6U,  //!< CMPHPMUX select 3
    AS_CMPHPMUX_SELECT_4 = 9U,  //!< CMPHPMUX select 4
} AS_CMPHPMuxSelect;

//*****************************************************************************
//
//! AS_CMPLPMuxSelect used for function AS_selectCMPLPMux().
//
//*****************************************************************************
typedef enum
{
    AS_CMPLPMUX_SELECT_1 = 0U,  //!< CMPLPMUX select 1
    AS_CMPLPMUX_SELECT_2 = 3U,  //!< CMPLPMUX select 2
    AS_CMPLPMUX_SELECT_3 = 6U,  //!< CMPLPMUX select 3
    AS_CMPLPMUX_SELECT_4 = 9U,  //!< CMPLPMUX select 4
} AS_CMPLPMuxSelect;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! Lock all AGPIOCTRL registers.
//!
//! Setting this bit will prevent any subsequent writes to the AGPIOCTRL register.
//! This bit can only be cleared by a reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
AS_lockAGPIOCTRL(void)
{
    WRPRT_DISABLE;

    //
    // Set the AGPIOCTRL lock bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_CONFIGLOCK) |= AS_CONFIGLOCK_AGPIOCTRL;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable temperature sensor.
//!
//! This function enables the temperature sensor output to the ADC.
//!
//! \return None.
//
//*****************************************************************************
static inline void
AS_enableTemperatureSensor(void)
{
    WRPRT_DISABLE;

    //
    // Set the temperature sensor enable bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_TSNSCTL) |= AS_TSNSCTL_ENABLE;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable temperature sensor.
//!
//! This function disables the temperature sensor output to the ADC.
//!
//! \return None.
//
//*****************************************************************************
static inline void
AS_disableTemperatureSensor(void)
{
    WRPRT_DISABLE;

    //
    // Clear the temperature sensor enable bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_TSNSCTL) &= ~(AS_TSNSCTL_ENABLE);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the analog voltage reference selection to internal.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b AS_VREFHIA
//! - \b AS_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void
AS_setAnalogReferenceInternal(uint16_t reference)
{
    ASSERT((reference & (
                         AS_VREFHIA |
                         AS_VREFHIC
                        )) == reference);

    WRPRT_DISABLE;

    //
    // Write selection to the Analog Internal Reference Select field.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_ANAREFCTL) &= ~reference;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the analog voltage reference selection to external.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b AS_VREFHIA
//! - \b AS_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void
AS_setAnalogReferenceExternal(uint16_t reference)
{
    ASSERT((reference & (
                         AS_VREFHIA |
                         AS_VREFHIC
                        )) == reference);

    WRPRT_DISABLE;

    //
    // Write selection to the Analog External Reference Select field.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_ANAREFCTL) |= reference;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Select the value for CMPHNMXSEL.
//!
//! \param select is a combination of CMPHNMXSEL values.
//!
//! The parameter \e select can be a bitwise OR of the below values:
//!
//! - \b AS_CMPHNMUX_SELECT_1
//! - \b AS_CMPHNMUX_SELECT_2
//! - \b AS_CMPHNMUX_SELECT_3
//! - \b AS_CMPHNMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void AS_selectCMPHNMux(uint16_t select)
{
    ASSERT(select <= 0x7FU);

    WRPRT_DISABLE;

    //
    // Write a select to the mux select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_CMPHNMXSEL) = select;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Select the value for individual CMPxHNMXSEL.
//!
//! \param select is the CMPxHNMXSEL to be set.
//! \param value is 0 or 1.
//!
//! The parameter \e select can be one of the below values:
//!
//! - \b AS_CMPHNMUX_SELECT_1
//! - \b AS_CMPHNMUX_SELECT_2
//! - \b AS_CMPHNMUX_SELECT_3
//! - \b AS_CMPHNMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void AS_selectCMPHNMuxValue(uint16_t select, uint16_t value)
{
    ASSERT(select <= 0x7FU);
    ASSERT(value <= 1U);

    WRPRT_DISABLE;

    //
    // Write a select to the mux select bit.
    //
    if(value == 0U)
    {
        HWREGH(ANALOGSUBSYS_BASE + AS_O_CMPHNMXSEL) &= ~select;
    }
    else if(value == 1U)
    {
        HWREGH(ANALOGSUBSYS_BASE + AS_O_CMPHNMXSEL) |= select;
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Select the value for individual CMPxLNMXSEL.
//!
//! \param select is a combination of CMPLNMXSEL values.
//!
//! The parameter \e select can be the bitwise OR of the below values:
//!
//! - \b AS_CMPLNMUX_SELECT_1
//! - \b AS_CMPLNMUX_SELECT_2
//! - \b AS_CMPLNMUX_SELECT_3
//! - \b AS_CMPLNMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void AS_selectCMPLNMux(uint16_t select)
{
    ASSERT(select <= 0x7FU);

    WRPRT_DISABLE;

    //
    // Write a select to the mux select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_CMPLNMXSEL) = select;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Select the value for CMPLNMXSEL.
//!
//! \param select is the CMPxHNMXSEL to be set.
//! \param value is 0 or 1.
//!
//! The parameter \e select can be one of the below values:
//!
//! - \b AS_CMPLNMUX_SELECT_1
//! - \b AS_CMPLNMUX_SELECT_2
//! - \b AS_CMPLNMUX_SELECT_3
//! - \b AS_CMPLNMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void AS_selectCMPLNMuxValue(uint16_t select, uint16_t value)
{
    ASSERT(select <= 0x7FU);
    ASSERT(value <= 1U);

    WRPRT_DISABLE;

    //
    // Write a select to the mux select bit.
    //
    if(value == 0U)
    {
        HWREGH(ANALOGSUBSYS_BASE + AS_O_CMPLNMXSEL) &= ~select;
    }
    else if(value == 1U)
    {
        HWREGH(ANALOGSUBSYS_BASE + AS_O_CMPLNMXSEL) |= select;
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Select the value for CMPHPMXSEL.
//!
//! \param select is of type AS_CMPHPMuxSelect.
//! \param value is the mux select for the chosen COMP HP input:
//! - For \b AS_CMPHPMUX_SELECT_1, \b AS_CMPHPMUX_SELECT_3, and
//!   \b AS_CMPHPMUX_SELECT_4: valid values are 0, 1, 2, 3, or 4.
//! - For \b AS_CMPHPMUX_SELECT_2: valid values are 0, 1, 2, 3, 4, or 5.
//!   Value 5 selects the internal temperature sensor on the COMP2_HP input
//!   (see the analog pin and internal connection table; ADC channel C12).
//!
//! This function is used to write a value to one mux select at a time.
//! The parameter \e select can be one of the following values:
//!
//! - \b AS_CMPHPMUX_SELECT_1
//! - \b AS_CMPHPMUX_SELECT_2
//! - \b AS_CMPHPMUX_SELECT_3
//! - \b AS_CMPHPMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void
AS_selectCMPHPMux(AS_CMPHPMuxSelect select, uint32_t value)
{
    if(select == AS_CMPHPMUX_SELECT_2)
    {
        ASSERT(value <= 5U);
    }
    else
    {
        ASSERT(value <= 4U);
    }

    WRPRT_DISABLE;

    //
    // Set the value for the appropriate Mux Select.
    //
    HWREG(ANALOGSUBSYS_BASE + AS_O_CMPHPMXSEL) =
    (HWREG(ANALOGSUBSYS_BASE + AS_O_CMPHPMXSEL) &
    ~((uint32_t)AS_CMPHPMXSEL_CMP1HPMXSEL_M << (uint32_t)select)) |
    (value << (uint32_t)select);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Select the value for CMPLPMXSEL.
//!
//! \param select is of type AS_CMPLPMuxSelect.
//! \param value is 0, 1, 2, 3, or 4.
//!
//! This function is used to write a value to one mux select at a time.
//! The parameter \e select can be one of the following values:
//!
//! - \b AS_CMPLPMUX_SELECT_1
//! - \b AS_CMPLPMUX_SELECT_2
//! - \b AS_CMPLPMUX_SELECT_3
//! - \b AS_CMPLPMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void
AS_selectCMPLPMux(AS_CMPLPMuxSelect select, uint32_t value)
{
    ASSERT(value <= 4);

    WRPRT_DISABLE;

    //
    // Set the value for the appropriate Mux Select.
    //
    HWREG(ANALOGSUBSYS_BASE + AS_O_CMPLPMXSEL) =
    (HWREG(ANALOGSUBSYS_BASE + AS_O_CMPLPMXSEL) &
    ~((uint32_t)AS_CMPLPMXSEL_CMP1LPMXSEL_M << (uint32_t)select)) |
    (value << (uint32_t)select);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks the temperature sensor control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void AS_lockTemperatureSensor(void)
{
    WRPRT_DISABLE;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_LOCK) |= AS_LOCK_TSNSCTL;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks the analog reference control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void AS_lockANAREF(void)
{
    WRPRT_DISABLE;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_LOCK) |= AS_LOCK_ANAREFCTL;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks the voltage monitor control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void AS_lockVMON(void)
{
    WRPRT_DISABLE;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_LOCK) |= AS_LOCK_VMONCTL;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks the CMPHPMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void AS_lockCMPHPMux(void)
{
    WRPRT_DISABLE;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_LOCK) |= AS_LOCK_CMPHPMXSEL;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks the CMPLPMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void AS_lockCMPLPMux(void)
{
    WRPRT_DISABLE;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_LOCK) |= AS_LOCK_CMPLPMXSEL;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks the CMPHNMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void AS_lockCMPHNMux(void)
{
    WRPRT_DISABLE;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_LOCK) |= AS_LOCK_CMPHNMXSEL;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks the CMPLNMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void AS_lockCMPLNMux(void)
{
    WRPRT_DISABLE;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + AS_O_LOCK) |= AS_LOCK_CMPLNMXSEL;

    WRPRT_ENABLE;
}

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

#endif // AS_H
