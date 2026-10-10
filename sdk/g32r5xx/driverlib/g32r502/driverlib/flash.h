//###########################################################################
//
// FILE:    flash.h
//
// TITLE:   Flash driver.
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
// 1. SRAM code segment definitions, macro definitions
// 2. Most functions have been modified
//
//###########################################################################

#ifndef FLASH_H
#define FLASH_H

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
//! \addtogroup flash_api Flash
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_flash.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Defines for the Flash_selectLowECCBlock() and Flash_selectHighECCBlock().
// These are not parameters for any function.
// These are not intended for application code.
//
//*****************************************************************************
//! Flash memory and INFO address
#define FLASH_MEMORY_BASE_ADDRESS       0x08000000U
#define FLASH_SINGLE_MODE_MIX_START     0x08000000U
#define FLASH_SINGLE_MODE_MIX_END       0x0803FFFFU
#define FLASH_SINGLE_MODE_BANK1_START   0x08040000U
#define FLASH_SINGLE_MODE_BANK1_END     0x0809FFFFU
#define FLASH_DUAL_MODE_BANK0_START     0x08000000U
#define FLASH_DUAL_MODE_BANK0_END       0x0801FFFFU
#define FLASH_DUAL_MODE_BANK1_START     0x08020000U
#define FLASH_DUAL_MODE_BANK1_END       0x0809FFFFU
#define FLASH_INFO_START                0x08108000U
#define FLASH_INFO_END                  0x0810BFFFU

//! ECC block select
#define FLASH_ECC_BLOCK_SELECT_BANK0_LOW    0x0U
#define FLASH_ECC_BLOCK_SELECT_BANK0_HIGH   0x1U
#define FLASH_ECC_BLOCK_SELECT_BANK1_LOW    0x2U
#define FLASH_ECC_BLOCK_SELECT_BANK1_HIGH   0x3U

//*****************************************************************************
//
// Values that can be passed to Flash_clearLowErrorStatus() and
// Flash_clearHighErrorStatus().
//
//*****************************************************************************
#define FLASH_FAIL_0_CLR    0x1U //!< Fail-0 clear
#define FLASH_FAIL_1_CLR    0x2U //!< Fail-1 clear
#define FLASH_UNC_ERR_CLR   0x4U //!< Uncorrectable error clear

//*****************************************************************************
//
// Values that can be returned from Flash_getInterruptFlag() and
// Flash_getECCTestStatus().
//
//*****************************************************************************
#define FLASH_NO_ERROR       0x0U //!< No error
#define FLASH_SINGLE_ERROR   0x1U //!< Single bit error
#define FLASH_UNC_ERROR      0x2U //!< Uncorrectable error

//*****************************************************************************
//
// Delay instruction that allows for register configuration to complete.
//
//*****************************************************************************
#define FLASH_DELAY_CONFIG   NOP

//*****************************************************************************
//
//! Values that can be passed to Flash_setBankPowerMode() and
//! Flash_isBankReady() as the \e bank parameter.
//
//*****************************************************************************
typedef enum
{
    FLASH_BANK0 = 0x0, //!< Bank 0
    FLASH_BANK1 = 0x1  //!< Bank 1
} Flash_BankNumber;

//*****************************************************************************
//
//! Values that can be passed to Flash_setBankPowerMode() as the \e powerMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    FLASH_BANK_PWR_STANDBY = 0x1, //!< Standby fallback mode
    FLASH_BANK_PWR_ACTIVE  = 0x3  //!< Active fallback mode
} Flash_BankPowerMode;

//*****************************************************************************
//
//! Values that can be returned from Flash_getBankMode().
//
//*****************************************************************************
typedef enum
{
    FLASH_DUAL_BANK   = 0x0, //!< Dual Bank mode
    FLASH_SINGLE_BANK = 0x1  //!< Single Bank mode
} Flash_BankMode;

//*****************************************************************************
//
//! Type that correspond to values returned from Flash_getLowErrorStatus() and
//! Flash_getHighErrorStatus() determining the error status code.
//
//*****************************************************************************
typedef enum
{
    FLASH_NO_ERR  = 0x0, //!< No error
    FLASH_FAIL_0  = 0x1, //!< Fail on 0
    FLASH_FAIL_1  = 0x2, //!< Fail on 1
    FLASH_UNC_ERR = 0x4  //!< Uncorrectable error
} Flash_ErrorStatus;

//*****************************************************************************
//
//! Values that can be returned from Flash_getLowErrorType() and
//! Flash_getHighErrorType() determining the error type.
//
//*****************************************************************************
typedef enum
{
    FLASH_DATA_ERR = 0x0, //!< Data error
    FLASH_ECC_ERR  = 0x1  //!< ECC error
} Flash_ErrorType;

//*****************************************************************************
//
//! Values that can be returned from Flash_getECCTestSingleBitErrorType().
//
//*****************************************************************************
typedef enum
{
    FLASH_DATA_BITS  = 0x0, //!< Data bits
    FLASH_CHECK_BITS = 0x1  //!< ECC bits
} Flash_SingleBitErrorIndicator;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks a flash wrapper base address for the control registers.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! This function determines if a flash wrapper control base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
Flash_isCtrlBaseValid(uint32_t ctrlBase)
{
    return((ctrlBase == FLASH0CTRL_BASE));
}
#endif

//*****************************************************************************
//
//! \internal
//! Checks a flash wrapper base address for the ECC registers.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function determines if a flash wrapper ECC base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
Flash_isECCBaseValid(uint32_t eccBase)
{
    return((eccBase == FLASH0ECC_BASE));
}
#endif

//*****************************************************************************
//
//! Sets the random read wait state amount.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//! \param waitstates is the wait-state value.
//!
//! This function sets the number of wait states for a flash read access. The
//! \e waitstates parameter is a number between 0 and 255. It is important to
//! look at your device's datasheet for information about what the required
//! minimum flash wait-state is for your selected SYSCLK frequency.
//!
//! By default the wait state amount is configured to 6.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_setWaitstates(uint32_t ctrlBase, uint16_t waitstates)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    //
    // waitstates is 8 bits wide.
    //
    ASSERT(waitstates <= 0xFFU);

    WRPRT_DISABLE;

    //
    // Write flash read wait-state amount to appropriate register.
    //
    HWREG(ctrlBase + FLASH_O_FRDCNTL) =
        (HWREG(ctrlBase + FLASH_O_FRDCNTL) &
         ~(uint32_t)FLASH_FRDCNTL_RWAIT_M) |
         ((uint32_t)waitstates << FLASH_FRDCNTL_RWAIT_S);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the SWAP_STATUS bit in the BANK_SWAP_SOFT register.
//!
//! \param ctrlBase is the base address of the flash control registers.
//!
//! This function returns the SWAP_STATUS of the BANK_SWAP_SOFT register,
//! indicating whether the device has completed the active BANK SWAP.
//! If the SWAP_STATUS bit (bit3) is set, it typically indicates an ongoing
//! or completed swap state as determined by hardware. If the bit is clear,
//! no ongoing or completed swap operation is reported.
//!
//! \return Returns true if the SWAP_STATUS bit is set, otherwise false.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline bool
Flash_getBankSwapStatus(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    //
    // Read the BANK_SWAP_SOFT register and check if the SWAP_STATUS bit (bit3) is set.
    // Return "true" if the bit is set, else "false".
    //
    if((HWREG(ctrlBase + FLASH_O_BANK_SWAP_SOFT) & FLASH_BANK_SWAP_SOFT_SWAPSTATUS) 
            == FLASH_BANK_SWAP_SOFT_SWAPSTATUS)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

//*****************************************************************************
//
//! Enables software control of BANK SWAP.
//!
//! \param ctrlBase is the base address of the flash control registers.
//!
//! This function sets the SWAP_SEL bit in the BANK_SWAP_SOFT register, 
//! so that BANK SWAP is governed by software rather than the option byte.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_enableSoftwareBankSwapControl(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    WRPRT_DISABLE;

    HWREG(ctrlBase + FLASH_O_BANK_SWAP_SOFT) |= FLASH_BANK_SWAP_SOFT_SWAPSEL;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables software control of BANK SWAP.
//!
//! \param ctrlBase is the base address of the flash control registers.
//!
//! This function clears the SWAP_SEL bit in the BANK_SWAP_SOFT register,
//! meaning the BANK SWAP feature is determined by the option byte rather 
//! than software.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_disableSoftwareBankSwapControl(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    WRPRT_DISABLE;

    //
    // Set the SWAP_SEL bit (bit2) to enable software control of BANK SWAP.
    //
    HWREG(ctrlBase + FLASH_O_BANK_SWAP_SOFT) &= ~FLASH_BANK_SWAP_SOFT_SWAPSEL;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Configures the SWAP bit in the BANK_SWAP_SOFT register.
//!
//! \param ctrlBase is the base address of the flash control registers.
//! \param enable indicates whether to enable or disable BANK swap mapping.
//!
//! When \e enable is true, the SWAP bit is set, meaning BANK0/1 address 
//! mapping is swapped. When false, it is cleared, retaining the default mapping.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_setBankSwap(uint32_t ctrlBase, bool enable)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    WRPRT_DISABLE;

    if(enable)
    {
        //
        // Set the SWAP bit (bit1) to swap BANK0 and BANK1 addresses.
        //
        HWREG(ctrlBase + FLASH_O_BANK_SWAP_SOFT) |= FLASH_BANK_SWAP_SOFT_SWAP;
    }
    else
    {
        //
        // Clear the SWAP bit to restore the default mapping.
        //
        HWREG(ctrlBase + FLASH_O_BANK_SWAP_SOFT) &= ~FLASH_BANK_SWAP_SOFT_SWAP;
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables bypass for BANK SWAP.
//!
//! \param ctrlBase is the base address of the flash control registers.
//!
//! This function sets the SWAP_BYPASS bit (bit0) to force the default bank
//! address mapping, regardless of the SWAP or SWAP_SEL bits. This effectively
//! bypasses the BANK SWAP feature.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_enableBankSwapBypass(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    WRPRT_DISABLE;

    //
    // Set the SWAP_BYPASS bit (bit0) to always use default mapping.
    //
    HWREG(ctrlBase + FLASH_O_BANK_SWAP_SOFT) |= FLASH_BANK_SWAP_SOFT_BYPASS;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables bypass for BANK SWAP.
//!
//! \param ctrlBase is the base address of the flash control registers.
//!
//! This function clears the SWAP_BYPASS bit (bit0), allowing the normal BANK
//! SWAP feature to operate. The final mapping is governed by the SWAP and
//! SWAP_SEL bits, if configured.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_disableBankSwapBypass(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    WRPRT_DISABLE;

    //
    // Clear the SWAP_BYPASS bit to enable normal BANK SWAP operation.
    //
    HWREG(ctrlBase + FLASH_O_BANK_SWAP_SOFT) &= ~FLASH_BANK_SWAP_SOFT_BYPASS;

    WRPRT_ENABLE;
}


//*****************************************************************************
//
//! Sets the fallback power mode of a flash bank.
//!
//! \param ctrlBase is the base address of the flash wrapper registers.
//! \param bank is the flash bank that is being configured.
//! \param powerMode is the power mode to be entered.
//!
//! This function sets the fallback power mode of the flash bank specified by
//! them \e bank parameter. The power mode is specified by the \e powerMode
//! parameter with one of the following values:
//!
//! - \b FLASH_BANK_PWR_STANDBY - Sense amplifiers disabled but sense reference
//!   enabled.
//! - \b FLASH_BANK_PWR_ACTIVE - Sense amplifiers and sense reference enabled.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_setBankPowerMode(uint32_t ctrlBase, Flash_BankNumber bank,
                       Flash_BankPowerMode powerMode)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    WRPRT_DISABLE;

    //
    // Write the power mode to the appropriate register.
    //
    HWREG(ctrlBase + FLASH_O_FBFALLBACK) =
        (HWREG(ctrlBase + FLASH_O_FBFALLBACK) &
         ~(FLASH_FBFALLBACK_BNKPWR0_M << ((uint32_t)bank * 2U))) |
        ((uint32_t)powerMode << ((uint32_t)bank * 2U));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables prefetch mechanism.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_enablePrefetch(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    WRPRT_DISABLE;

    //
    // Set the prefetch enable bit.
    //
    HWREG(ctrlBase + FLASH_O_FRD_INTF_CTRL) |= FLASH_FRD_INTF_CTRL_Bus_prften;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables prefetch mechanism.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_disablePrefetch(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    WRPRT_DISABLE;

    //
    // Clear the prefetch enable bit.
    //
    HWREG(ctrlBase + FLASH_O_FRD_INTF_CTRL) &= ~(FLASH_FRD_INTF_CTRL_Bus_prften);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Flushes buffer.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_flushBuffer(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    WRPRT_DISABLE;

    //
    // Clear the busmatrix's buffer.
    //
    HWREG(ctrlBase + FLASH_O_FRD_INTF_CTRL) |=
        FLASH_FRD_INTF_CTRL_Bus_buf_clr;
    HWREG(ctrlBase + FLASH_O_FRD_INTF_CTRL) &=
        ~FLASH_FRD_INTF_CTRL_Bus_buf_clr;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables flash error correction code (ECC) protection.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_enableECC(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;

    //
    // Write the key value 0xA to ECC_ENABLE register.
    //
    HWREG(eccBase + FLASH_O_ECC_ENABLE) =
        (HWREG(eccBase + FLASH_O_ECC_ENABLE) &
         ~(uint32_t)FLASH_ECC_ENABLE_DECODE_ENABLE_M) | 0xAU;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables flash error correction code (ECC) protection.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
static inline void
Flash_disableECC(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;

    //
    // Clear ECC enable field with the one's complement of the key.
    //
    HWREG(eccBase + FLASH_O_ECC_ENABLE) =
        (HWREG(eccBase + FLASH_O_ECC_ENABLE) &
         ~(uint32_t)FLASH_ECC_ENABLE_DECODE_ENABLE_M) | 0x5U;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the bank active grace period.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//! \param period is the starting count value for the BAGP down counter.
//!
//! This function sets the bank active grace period specified by the
//! \e period parameter. The \e period is a value between 0 and 255. This
//! value must be greater than 1 when the fallback mode is not Active.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_setBankActiveGracePeriod(uint32_t ctrlBase, uint32_t period)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));
    ASSERT(period <= 255U);

    WRPRT_DISABLE;

    //
    // Write period to the BAGP of the FBAC register.
    //
    HWREG(ctrlBase + FLASH_O_FBAC) =
        (HWREG(ctrlBase + FLASH_O_FBAC) & ~(uint32_t)FLASH_FBAC_BAGP_M) |
        (period << FLASH_FBAC_BAGP_S);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Reads the bank active power state.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//! \param bank is the flash bank that is being used.
//!
//! \return Returns \b true if the Bank is in Active power state and \b false
//! otherwise.
//
//*****************************************************************************
static inline bool
Flash_isBankReady(uint32_t ctrlBase, Flash_BankNumber bank)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    bool ready;
    uint32_t bitMask = FLASH_FBPRDY_BANK0RDY << (uint32_t)bank;

    //
    // Return the BANKXRDY bit in FBPRDY.
    //
    if((HWREG(ctrlBase + FLASH_O_FBPRDY) & bitMask) == bitMask)
    {
        ready = true;
    }
    else
    {
        ready = false;
    }
    return(ready);
}

//*****************************************************************************
//
//! Gets current bank mode.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! \return Returns value of the nDBANK bit which can be used with
//! Flash_BankMode type.
//
//*****************************************************************************
static inline Flash_BankMode
Flash_getBankMode(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    return((Flash_BankMode)(HWREG(ctrlBase + FLASH_O_CR) & FLASH_CR_NDBANK));
}

//*****************************************************************************
//
//! Gets the single error address low.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function returns the 32-bit address of the single bit error that
//! occurred in the lower 64-bits of a 128-bit memory-aligned data. The
//! returned address is to that 64-bit aligned data.
//!
//! \return Returns the 32 bits of a 64-bit aligned address where a single bit
//! error occurred.
//
//*****************************************************************************
static inline uint32_t
Flash_getSingleBitErrorAddressLow(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    if((HWREG(eccBase + FLASH_O_ERR_STATUS) &
        (FLASH_ERR_STATUS_FLASH0_FAIL_0_L | FLASH_ERR_STATUS_FLASH0_FAIL_1_L))
       != 0U)
    {
        return(HWREG(eccBase + FLASH_O_SEADDRL_0));
    }
    else
    {
        return(HWREG(eccBase + FLASH_O_SEADDRL_1));
    }
}

//*****************************************************************************
//
//! Gets the single error address high.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function returns the 32-bit address of the single bit error that
//! occurred in the upper 64-bits of a 128-bit memory-aligned data. The
//! returned address is to that 64-bit aligned data.
//!
//! \return Returns the 32 bits of a 64-bit aligned address where a single bit
//! error occurred.
//
//*****************************************************************************
static inline uint32_t
Flash_getSingleBitErrorAddressHigh(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    if((HWREG(eccBase + FLASH_O_ERR_STATUS) &
        (FLASH_ERR_STATUS_FLASH0_FAIL_0_H | FLASH_ERR_STATUS_FLASH0_FAIL_1_H))
       != 0U)
    {
        return(HWREG(eccBase + FLASH_O_SEADDRH_0));
    }
    else
    {
        return(HWREG(eccBase + FLASH_O_SEADDRH_1));
    }
}

//*****************************************************************************
//
//! Gets the uncorrectable error address low.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function returns the 32-bit address of the uncorrectable error that
//! occurred in the lower 64-bits of a 128-bit memory-aligned data. The
//! returned address is to that 64-bit aligned data.
//!
//! \return Returns the 32 bits of a 64-bit aligned address where an
//! uncorrectable error occurred.
//
//*****************************************************************************
static inline uint32_t
Flash_getUncorrectableErrorAddressLow(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    if((HWREG(eccBase + FLASH_O_ERR_STATUS) & FLASH_ERR_STATUS_FLASH0_UNC_ERR_L)
                                == FLASH_ERR_STATUS_FLASH0_UNC_ERR_L)
    {
        return(HWREG(eccBase + FLASH_O_UNCEADDRL_0));
    }
    else
    {
        return(HWREG(eccBase + FLASH_O_UNCEADDRL_1));
    }
}

//*****************************************************************************
//
//! Gets the uncorrectable error address high.
//!
//! \param eccBase is the base address of the flash wrapper ECC base.
//!
//! This function returns the 32-bit address of the uncorrectable error that
//! occurred in the upper 64-bits of a 128-bit memory-aligned data. The
//! returned address is to that 64-bit aligned data.
//!
//! \return Returns the 32 bits of a 64-bit aligned address where an
//! uncorrectable error occurred.
//
//*****************************************************************************
static inline uint32_t
Flash_getUncorrectableErrorAddressHigh(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    if((HWREG(eccBase + FLASH_O_ERR_STATUS) & FLASH_ERR_STATUS_FLASH0_UNC_ERR_H)
                                == FLASH_ERR_STATUS_FLASH0_UNC_ERR_H)
    {
        return(HWREG(eccBase + FLASH_O_UNCEADDRH_0));
    }
    else
    {
        return(HWREG(eccBase + FLASH_O_UNCEADDRH_1));
    }
}

//*****************************************************************************
//
//! Gets the error status of the Lower 64-bits.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function returns the error status of the lower 64-bits of a 128-bit
//! aligned address.
//!
//! \return Returns value of the low error status bits which can be used with
//! Flash_ErrorStatus type.
//
//*****************************************************************************
static inline Flash_ErrorStatus
Flash_getLowErrorStatus(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    if((HWREG(eccBase + FLASH_O_ERR_STATUS) &
        (FLASH_ERR_STATUS_FLASH0_FAIL_0_L | FLASH_ERR_STATUS_FLASH0_FAIL_1_L |
         FLASH_ERR_STATUS_FLASH0_UNC_ERR_L)) != 0U)
    {
        return((Flash_ErrorStatus)(HWREG(eccBase + FLASH_O_ERR_STATUS) &
                (uint32_t)0x7U));
    }
    else
    {
        return((Flash_ErrorStatus)((HWREG(eccBase + FLASH_O_ERR_STATUS) >>
                16U) & (uint32_t)0x7U));
    }
}

//*****************************************************************************
//
//! Gets the error status of the Upper 64-bits.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function returns the error status of the upper 64-bits of a 128-bit
//! aligned address.
//!
//! \return Returns value of the high error status bits which can be used with
//! Flash_ErrorStatus type.
//
//*****************************************************************************
static inline Flash_ErrorStatus
Flash_getHighErrorStatus(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    if((HWREG(eccBase + FLASH_O_ERR_STATUS) &
        (FLASH_ERR_STATUS_FLASH0_FAIL_0_H | FLASH_ERR_STATUS_FLASH0_FAIL_1_H |
         FLASH_ERR_STATUS_FLASH0_UNC_ERR_H)) != 0U)
    {
        return((Flash_ErrorStatus)((HWREG(eccBase + FLASH_O_ERR_STATUS) >>
                8U) & (uint32_t)0x7U));
    }
    else
    {
        return((Flash_ErrorStatus)((HWREG(eccBase + FLASH_O_ERR_STATUS) >>
                24U) & (uint32_t)0x7U));
    }
}

//*****************************************************************************
//
//! Gets the error position of the lower 64-bits for a single bit error.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function returns the error position of the lower 64-bits. If the
//! error type is FLASH_ECC_ERR, the position ranges from 0-7 else it ranges
//! from 0-63 for FLASH_DATA_ERR.
//!
//! \return Returns the position of the lower error bit.
//
//*****************************************************************************
static inline uint32_t
Flash_getLowErrorPosition(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    if((HWREG(eccBase + FLASH_O_ERR_STATUS) &
        (FLASH_ERR_STATUS_FLASH0_FAIL_0_L |FLASH_ERR_STATUS_FLASH0_FAIL_1_L))
       != 0U)
    {
        return(HWREG(eccBase + FLASH_O_ERR_POS) &
               (uint32_t)FLASH_ERR_POS_Flash0_ERR_POS_L_M);
    }
    else
    {
        return((HWREG(eccBase + FLASH_O_ERR_POS) &
                (uint32_t)FLASH_ERR_POS_Flash1_ERR_POS_L_M) >>
               FLASH_ERR_POS_Flash1_ERR_POS_L_S);
    }
}

//*****************************************************************************
//
//! Gets the error position of the upper 64-bits for a single bit error.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function returns the error position of the upper 64-bits. If the
//! error type is FLASH_ECC_ERR, the position ranges from 0-7 else it ranges
//! from 0-63 for FLASH_DATA_ERR.
//!
//! \return Returns the position of the upper error bit.
//
//*****************************************************************************
static inline uint32_t
Flash_getHighErrorPosition(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    if((HWREG(eccBase + FLASH_O_ERR_STATUS) &
        (FLASH_ERR_STATUS_FLASH0_FAIL_0_H |FLASH_ERR_STATUS_FLASH0_FAIL_1_H))
       != 0U)
    {
        return((HWREG(eccBase + FLASH_O_ERR_POS) &
                (uint32_t)FLASH_ERR_POS_Flash0_ERR_POS_H_M) >>
               FLASH_ERR_POS_Flash0_ERR_POS_H_S);
    }
    else
    {
        return((HWREG(eccBase + FLASH_O_ERR_POS) &
                (uint32_t)FLASH_ERR_POS_Flash0_ERR_POS_H_M) >>
               FLASH_ERR_POS_Flash1_ERR_POS_H_S);
    }
}

//*****************************************************************************
//
//! Clears the error position bit of the lower 64-bits for a single bit error.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function clears the error position bit of the lower 64-bits.
//!
//! \return None
//
//*****************************************************************************
static inline void
Flash_clearLowErrorPosition(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_ERR_POS) &= ~(FLASH_ERR_POS_Flash0_ERR_POS_L_M |
                                          FLASH_ERR_POS_Flash1_ERR_POS_L_M);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Clears the error position of the upper 64-bits for a single bit error.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function clears the error position bit of the upper 64-bits.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_clearHighErrorPosition(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_ERR_POS) &= ~(FLASH_ERR_POS_Flash0_ERR_POS_H_M |
                                          FLASH_ERR_POS_Flash1_ERR_POS_H_M);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the error type of the lower 64-bits.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function returns the error type of the lower 64-bits. The error type
//! can be FLASH_ECC_ERR or FLASH_DATA_ERR.
//!
//! \return Returns the type of the lower 64-bit error.
//
//*****************************************************************************
static inline Flash_ErrorType
Flash_getLowErrorType(uint32_t eccBase)
{
    Flash_ErrorType errorType;

    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    //
    // Check which error type.
    // If bit is 1 then ECC error, else it is a Data error.
    //
    if((HWREG(eccBase + FLASH_O_ERR_STATUS) &
        (FLASH_ERR_STATUS_FLASH0_FAIL_0_L | FLASH_ERR_STATUS_FLASH0_FAIL_1_L))
       != 0U)
    {
        if((HWREG(eccBase + FLASH_O_ERR_POS) & FLASH_ERR_POS_FLASH0_ERR_TYPE_L)
                                    == FLASH_ERR_POS_FLASH0_ERR_TYPE_L)
            errorType = FLASH_ECC_ERR;
        else
            errorType = FLASH_DATA_ERR;
    }
    else
    {
        if((HWREG(eccBase + FLASH_O_ERR_POS) & FLASH_ERR_POS_FLASH1_ERR_TYPE_L)
                                    == FLASH_ERR_POS_FLASH1_ERR_TYPE_L)
            errorType = FLASH_ECC_ERR;
        else
            errorType = FLASH_DATA_ERR;
    }
    return(errorType);
}

//*****************************************************************************
//
//! Gets the error type of the upper 64-bits.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function returns the error type of the upper 64-bits. The error type
//! can be FLASH_ECC_ERR or FLASH_DATA_ERR.
//!
//! \return Returns the type of the upper 64-bit error.
//
//*****************************************************************************
static inline Flash_ErrorType
Flash_getHighErrorType(uint32_t eccBase)
{
    Flash_ErrorType errorType;

    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    //
    // Check which error type.
    // If bit is 1 then ECC error, else it is a Data error.
    //
    if((HWREG(eccBase + FLASH_O_ERR_STATUS) &
        (FLASH_ERR_STATUS_FLASH0_FAIL_0_H | FLASH_ERR_STATUS_FLASH0_FAIL_1_H))
       != 0U)
    {
        if((HWREG(eccBase + FLASH_O_ERR_POS) & FLASH_ERR_POS_FLASH0_ERR_TYPE_H)
                                    == FLASH_ERR_POS_FLASH0_ERR_TYPE_H)
            errorType = FLASH_ECC_ERR;
        else
            errorType = FLASH_DATA_ERR;
    }
    else
    {
        if((HWREG(eccBase + FLASH_O_ERR_POS) & FLASH_ERR_POS_FLASH1_ERR_TYPE_H)
                                    == FLASH_ERR_POS_FLASH1_ERR_TYPE_H)
            errorType = FLASH_ECC_ERR;
        else
            errorType = FLASH_DATA_ERR;
    }
    return(errorType);
}

//*****************************************************************************
//
//! Clears the errors status of the lower 64-bits.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//! \param errorStatus is the error status to clear. errorStatus is a uint16_t.
//! errorStatus is a bitwise OR of the following value:
//!
//! - \b FLASH_FAIL_0_CLR
//! - \b FLASH_FAIL_1_CLR
//! - \b FLASH_UNC_ERR_CLR
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_clearLowErrorStatus(uint32_t eccBase, uint16_t errorStatus)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_ERR_STATUS_CLR) |=
        ((uint32_t)errorStatus | ((uint32_t)errorStatus << 16U));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Clears the errors status of the upper 64-bits.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//! \param errorStatus is the error status to clear. errorStatus is a uint16_t.
//! errorStatus is a bitwise OR of the following value:
//!
//! - \b FLASH_FAIL_0_CLR
//! - \b FLASH_FAIL_1_CLR
//! - \b FLASH_UNC_ERR_CLR
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_clearHighErrorStatus(uint32_t eccBase, uint16_t errorStatus)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_ERR_STATUS_CLR) |=
        (((uint32_t)errorStatus << 8U) | ((uint32_t)errorStatus << 24U));
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the single bit error count.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return Returns the single bit error count.
//
//*****************************************************************************
static inline uint32_t
Flash_getErrorCount(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    return(HWREG(eccBase + FLASH_O_ERR_CNT) &
           (uint32_t)FLASH_ERR_CNT_ERR_CNT_M);
}

//*****************************************************************************
//
//! Sets the single bit error threshold.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//! \param threshold is the single bit error threshold. Valid ranges are from
//! 0-65535.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_setErrorThreshold(uint32_t eccBase, uint16_t threshold)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_ERR_THRESHOLD) = ((uint32_t)threshold &
        (uint32_t)FLASH_ERR_THRESHOLD_ERR_THRESHOLD_M);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the error interrupt.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function returns the type of error interrupt that occurred.  The
//! values can be used with
//! - \b FLASH_NO_ERROR
//! - \b FLASH_SINGLE_ERROR
//! - \b FLASH_UNC_ERROR
//!
//! \return Returns the interrupt flag.
//
//*****************************************************************************
static inline uint32_t
Flash_getInterruptFlag(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    //
    // Read which type of error occurred.
    //
    return(HWREG(eccBase + FLASH_O_ERR_INTFLG) & (uint32_t)0x3U);
}

//*****************************************************************************
//
//! Clears the single error interrupt flag.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_clearSingleErrorInterruptFlag(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_ERR_INTCLR) |=
        FLASH_ERR_INTCLR_SINGLE_ERR_INTCLR;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Clears the uncorrectable error interrupt flag.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_clearUncorrectableInterruptFlag(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_ERR_INTCLR) |=
        FLASH_ERR_INTCLR_UNC_ERR_INTCLR ;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the Data Low Test register for ECC testing.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//! \param data is a 32-bit value that is the low double word of selected
//! 64-bit data
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_setDataLowECCTest(uint32_t eccBase, uint32_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_DATAL) = data;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the Data High Test register for ECC testing.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//! \param data is a 32-bit value that is the high double word of selected
//! 64-bit data
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_setDataHighECCTest(uint32_t eccBase, uint32_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_DATAH) = data;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the test address register for ECC testing.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//! \param address is a 32-bit value containing an address. Bits 21-3 will be
//! used as the flash word (128-bit) address.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_setECCTestAddress(uint32_t eccBase, uint32_t address)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;

    //
    // Write bits 21-3 to the register.
    //
    HWREG(eccBase + FLASH_O_FADDR_TEST) = address;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the ECC test bits for ECC testing.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//! \param ecc is a 32-bit value. The least significant 8 bits are used as
//! the ECC Control Bits in the ECC Test.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_setECCTestECCBits(uint32_t eccBase, uint16_t ecc)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));
    ASSERT(ecc <= 255U);

    WRPRT_DISABLE;

    //
    // Write the 8 ECC Control Bits.
    //
    HWREG(eccBase + FLASH_O_FECC_TEST) =
        ((uint32_t)ecc & (uint32_t)FLASH_FECC_TEST_ECC_M);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables ECC Test mode.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_enableECCTestMode(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_FECC_CTRL) |= FLASH_FECC_CTRL_ECC_TEST_EN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables ECC Test mode.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_disableECCTestMode(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_FECC_CTRL) &=
        ~(uint32_t)FLASH_FECC_CTRL_ECC_TEST_EN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Performs the ECC calculation on the test block.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_performECCCalculation(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    WRPRT_DISABLE;
    HWREG(eccBase + FLASH_O_FECC_CTRL) |= FLASH_FECC_CTRL_DO_ECC_CALC;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the ECC Test data out high 63:32 bits.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return Returns the ECC TEst data out High.
//
//*****************************************************************************
static inline uint32_t
Flash_getTestDataOutHigh(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    return(HWREG(eccBase + FLASH_O_TESTH));
}

//*****************************************************************************
//
//! Gets the ECC Test data out low 31:0 bits.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return Returns the ECC Test data out Low.
//
//*****************************************************************************
static inline uint32_t
Flash_getTestDataOutLow(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    return(HWREG(eccBase + FLASH_O_TESTL));
}

//*****************************************************************************
//
//! Gets the ECC Test status.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function returns the ECC test status. The values can be used with
//! - \b FLASH_NO_ERROR
//! - \b FLASH_SINGLE_ERROR
//! - \b FLASH_UNC_ERROR
//!
//! \return Returns the ECC test status.
//
//*****************************************************************************
static inline uint32_t
Flash_getECCTestStatus(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    //
    // Read which type of error occurred.
    //
    return(HWREG(eccBase + FLASH_O_FECC_STATUS) & ((uint32_t)0x3U));
}

//*****************************************************************************
//
//! Gets the ECC Test single bit error position.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return Returns the ECC Test single bit error position. If the error type
//! is check bits than the position can range from 0 to 7. If the error type
//! is data bits than the position can range from 0 to 63.
//
//*****************************************************************************
static inline uint32_t
Flash_getECCTestErrorPosition(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    //
    // Read the position bits and shift it to the right.
    //
    return((HWREG(eccBase + FLASH_O_FECC_STATUS) &
            (uint32_t)FLASH_FECC_STATUS_TSEPOS_M) >>
           FLASH_FECC_STATUS_TSEPOS_S);
}

//*****************************************************************************
//
//! Gets the single bit error type.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return Returns the single bit error type as a
//!  Flash_SingleBitErrorIndicator. FLASH_DATA_BITS and FLASH_CHECK_BITS
//! indicate where the single bit error occurred.
//
//*****************************************************************************
static inline Flash_SingleBitErrorIndicator
Flash_getECCTestSingleBitErrorType(uint32_t eccBase)
{
    uint32_t errorType;

    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    //
    // Read the ERR_TYPE bit to see where the single bit error was.
    //
    errorType = ((HWREG(eccBase + FLASH_O_FECC_STATUS) &
                  (uint32_t)FLASH_FECC_STATUS_TSETYPE) >> 8U);
    return((Flash_SingleBitErrorIndicator)errorType);
}

//*****************************************************************************
//
//! Initializes the flash control registers.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//! \param eccBase is the base address of the flash wrapper ECC registers.
//! \param waitstates is the wait-state value.
//!
//! This function initializes the flash control registers. A flash access will
//! power up the bank automatically. This function will set the fallback mode
//! of flash as active.
//!
//! This function also sets the number of wait-states for a flash access
//! (see Flash_setWaitstates() for more details), and enables cache, the
//! prefetch mechanism, and ECC.
//!
//! \return None.
//
//*****************************************************************************
extern void
Flash_initModule(uint32_t ctrlBase, uint32_t eccBase, uint16_t waitstates);

//*****************************************************************************
//
//! Powers down the flash.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! This function powers down the flash bank(s).
//!
//! \return None.
//
//*****************************************************************************
extern void
Flash_powerDown(uint32_t ctrlBase);

//*****************************************************************************
//
//! Wakes the flash from low power mode.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! This function will power up Flash bank and set the fallback mode of flash
//! as active.
//!
//! \return None.
//
//*****************************************************************************
extern void
Flash_wakeFromLPM(uint32_t ctrlBase);

//*****************************************************************************
//
//! Selects the ECC block on bits [63:0] of bank data.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
extern void
Flash_selectLowECCBlock(uint32_t eccBase);

//*****************************************************************************
//
//! Selects the ECC block on bits [127:64] of bank data.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
extern void
Flash_selectHighECCBlock(uint32_t eccBase);

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

#endif // FLASH_H
