//###########################################################################
//
// FILE:    flash.c
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
// 1. SRAM code segment definitions
// 2. Most functions have been modified
//
//###########################################################################

#include "flash.h"

//*****************************************************************************
//
// Flash_initModule
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
void
Flash_initModule(uint32_t ctrlBase, uint32_t eccBase, uint16_t waitstates)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));
    ASSERT(Flash_isECCBaseValid(eccBase));
    ASSERT(waitstates <= 0xFFU);

    //
    // Set the bank fallback power modes to active.
    //
    Flash_setBankPowerMode(ctrlBase, FLASH_BANK0, FLASH_BANK_PWR_ACTIVE);
    Flash_setBankPowerMode(ctrlBase, FLASH_BANK1, FLASH_BANK_PWR_ACTIVE);

    //
    // Disable prefetch mechanism before changing wait states
    //
    Flash_disablePrefetch(ctrlBase);

    //
    // Set waitstates according to frequency.
    //
    Flash_setWaitstates(ctrlBase, waitstates);

    //
    // Enableprefetch mechanism to improve performance of code
    // executed from flash.
    //
    Flash_enablePrefetch(ctrlBase);
    
    //
    // Enable the BANK SWAP bypass feature, forcing the default address mapping.
    // When 'Enable' is passed, the SWAP_BYPASS bit is set, ensuring the device
    // always uses the default mapping regardless of the SWAP or SWAP_SEL bits.
    //
    Flash_enableBankSwapBypass(ctrlBase);

    //
    // At reset, ECC is enabled.  If it is disabled by application software and
    // if application again wants to enable ECC.
    //
    Flash_enableECC(eccBase);

    //
    // Force a pipeline flush to ensure that the write to the last register
    // configured occurs before returning.
    //
    FLASH_DELAY_CONFIG;
}

//*****************************************************************************
//
// Flash_powerDown
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
void
Flash_powerDown(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    //
    // Power down the flash banks.
    //
    Flash_setBankPowerMode(ctrlBase, FLASH_BANK0, FLASH_BANK_PWR_STANDBY);
    Flash_setBankPowerMode(ctrlBase, FLASH_BANK1, FLASH_BANK_PWR_STANDBY);
}

//*****************************************************************************
//
// Flash_wakeFromLPM
//
//*****************************************************************************
SECTION_ITCM_RAMFUNC
void
Flash_wakeFromLPM(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    //
    // Set the bank fallback power modes to active.
    //
    Flash_setBankPowerMode(ctrlBase, FLASH_BANK0, FLASH_BANK_PWR_ACTIVE);
    Flash_setBankPowerMode(ctrlBase, FLASH_BANK1, FLASH_BANK_PWR_ACTIVE);
}

//*****************************************************************************
//
// Flash_selectLowECCBlock
//
//*****************************************************************************
void
Flash_selectLowECCBlock(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    uint32_t ctrlBase = FLASH0CTRL_BASE;
    uint32_t eccTestAddr = FLASH_MEMORY_BASE_ADDRESS +
                  HWREG(eccBase + FLASH_O_FADDR_TEST);

    WRPRT_DISABLE;

    //
    // Clear the ECC_SELECT field.
    //
    HWREG(eccBase + FLASH_O_FECC_CTRL) &= ~FLASH_FECC_CTRL_ECC_SELECT_M;

    //
    // Select the ECC block on FLASH bank1 bits [63:0] if ECC test address
    // is flash INFO.
    //
    if((eccTestAddr >= FLASH_INFO_START) && (eccTestAddr <= FLASH_INFO_END))
    {
        HWREG(eccBase + FLASH_O_FECC_CTRL) |=
            (FLASH_ECC_BLOCK_SELECT_BANK1_LOW <<
             FLASH_FECC_CTRL_ECC_SELECT_S);
    }
    else
    {
        //
        // Single bank mode
        //
        if(Flash_getBankMode(ctrlBase) == FLASH_SINGLE_BANK)
        {
            //
            // Mixed region of band0 and bank1
            //
            if((eccTestAddr >= FLASH_SINGLE_MODE_MIX_START) &&
               (eccTestAddr <= FLASH_SINGLE_MODE_MIX_END))
            {
                if((eccTestAddr & (uint32_t)0x10U) == 0U)
                {
                    HWREG(eccBase + FLASH_O_FECC_CTRL) |=
                        (FLASH_ECC_BLOCK_SELECT_BANK0_LOW <<
                         FLASH_FECC_CTRL_ECC_SELECT_S);
                }
                else
                {
                    HWREG(eccBase + FLASH_O_FECC_CTRL) |=
                        (FLASH_ECC_BLOCK_SELECT_BANK1_LOW <<
                         FLASH_FECC_CTRL_ECC_SELECT_S);
                }
            }
            else if((eccTestAddr >= FLASH_SINGLE_MODE_BANK1_START) &&
                    (eccTestAddr <= FLASH_SINGLE_MODE_BANK1_END))
            {
                HWREG(eccBase + FLASH_O_FECC_CTRL) |=
                    (FLASH_ECC_BLOCK_SELECT_BANK1_LOW <<
                     FLASH_FECC_CTRL_ECC_SELECT_S);
            }
        }
        //
        // Dual bank mode
        //
        else
        {
            if((eccTestAddr >= FLASH_DUAL_MODE_BANK0_START) &&
               (eccTestAddr <= FLASH_DUAL_MODE_BANK0_END))
            {
                HWREG(eccBase + FLASH_O_FECC_CTRL) |=
                    (FLASH_ECC_BLOCK_SELECT_BANK0_LOW <<
                     FLASH_FECC_CTRL_ECC_SELECT_S);
            }
            else if((eccTestAddr >= FLASH_DUAL_MODE_BANK1_START) &&
                    (eccTestAddr <= FLASH_DUAL_MODE_BANK1_END))
            {
                HWREG(eccBase + FLASH_O_FECC_CTRL) |=
                    (FLASH_ECC_BLOCK_SELECT_BANK1_LOW <<
                     FLASH_FECC_CTRL_ECC_SELECT_S);
            }
        }
    }
    WRPRT_ENABLE;
}

//*****************************************************************************
//
// Flash_selectHighECCBlock
//
//*****************************************************************************
void
Flash_selectHighECCBlock(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    uint32_t ctrlBase = FLASH0CTRL_BASE;
    uint32_t eccTestAddr = FLASH_MEMORY_BASE_ADDRESS +
                  HWREG(eccBase + FLASH_O_FADDR_TEST);

    WRPRT_DISABLE;

    //
    // Clear the ECC_SELECT field.
    //
    HWREG(eccBase + FLASH_O_FECC_CTRL) &= ~FLASH_FECC_CTRL_ECC_SELECT_M;

    //
    // Select the ECC block on FLASH bank1 bits [127:64] if ECC test address
    // is flash INFO.
    //
    if((eccTestAddr >= FLASH_INFO_START) && (eccTestAddr <= FLASH_INFO_END))
    {
        HWREG(eccBase + FLASH_O_FECC_CTRL) |=
            (FLASH_ECC_BLOCK_SELECT_BANK1_HIGH <<
             FLASH_FECC_CTRL_ECC_SELECT_S);
    }
    else
    {
        //
        // Single bank mode
        //
        if(Flash_getBankMode(ctrlBase) == FLASH_SINGLE_BANK)
        {
            //
            // Mixed region of band0 and bank1
            //
            if((eccTestAddr >= FLASH_SINGLE_MODE_MIX_START) &&
               (eccTestAddr <= FLASH_SINGLE_MODE_MIX_END))
            {
                if((eccTestAddr & (uint32_t)0x10U) == 0U)
                {
                    HWREG(eccBase + FLASH_O_FECC_CTRL) |=
                        (FLASH_ECC_BLOCK_SELECT_BANK0_HIGH <<
                         FLASH_FECC_CTRL_ECC_SELECT_S);
                }
                else
                {
                    HWREG(eccBase + FLASH_O_FECC_CTRL) |=
                        (FLASH_ECC_BLOCK_SELECT_BANK1_HIGH <<
                         FLASH_FECC_CTRL_ECC_SELECT_S);
                }
            }
            else if((eccTestAddr >= FLASH_SINGLE_MODE_BANK1_START) &&
                    (eccTestAddr <= FLASH_SINGLE_MODE_BANK1_END))
            {
                HWREG(eccBase + FLASH_O_FECC_CTRL) |=
                    (FLASH_ECC_BLOCK_SELECT_BANK1_HIGH <<
                     FLASH_FECC_CTRL_ECC_SELECT_S);
            }
        }
        //
        // Dual bank mode
        //
        else
        {
            if((eccTestAddr >= FLASH_DUAL_MODE_BANK0_START) &&
               (eccTestAddr <= FLASH_DUAL_MODE_BANK0_END))
            {
                HWREG(eccBase + FLASH_O_FECC_CTRL) |=
                    (FLASH_ECC_BLOCK_SELECT_BANK0_HIGH <<
                     FLASH_FECC_CTRL_ECC_SELECT_S);
            }
            else if((eccTestAddr >= FLASH_DUAL_MODE_BANK1_START) &&
                    (eccTestAddr <= FLASH_DUAL_MODE_BANK1_END))
            {
                HWREG(eccBase + FLASH_O_FECC_CTRL) |=
                    (FLASH_ECC_BLOCK_SELECT_BANK1_HIGH <<
                     FLASH_FECC_CTRL_ECC_SELECT_S);
            }
        }
    }
    WRPRT_ENABLE;
}
