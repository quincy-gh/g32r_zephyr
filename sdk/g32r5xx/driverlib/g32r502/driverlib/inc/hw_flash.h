//###########################################################################
//
// FILE:    hw_flash.h
//
// TITLE:   Definitions for the FLASH registers.
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
// 1. Some comments, macro definitions (register and bit-field naming) were changed.
//
//###########################################################################

#ifndef HW_FLASH_H
#define HW_FLASH_H

//*************************************************************************************************
//
// The following are defines for the FLASH register offsets
//
//*************************************************************************************************
#define FLASH_O_FRDCNTL                0x0U     // Flash Read Control Register
#define FLASH_O_BANK_SWAP_SOFT         0x4U     // Flash Bank Access Control Register
#define FLASH_O_FBAC                   0x3CU    // Flash Bank Access Control Register
#define FLASH_O_FBFALLBACK             0x40U    // Flash Bank Fallback Power Register
#define FLASH_O_FBPRDY                 0x44U    // Flash Bank Pump Ready Register
#define FLASH_O_FMSTAT                 0x54U    // Flash Module Status Register
#define FLASH_O_FRD_INTF_CTRL          0x300U   // Flash Read Interface Control Register
#define FLASH_O_CR                     0x478U   // Flash Control Register

#define FLASH_O_ECC_ENABLE             0x0U    // ECC Enable
#define FLASH_O_SEADDRL_0              0x4U    // Single Error Address Low 0
#define FLASH_O_SEADDRH_0              0x8U    // Single Error Address High 0
#define FLASH_O_UNCEADDRL_0            0xCU    // Uncorrectable Error Address Low 0
#define FLASH_O_UNCEADDRH_0            0x10U   // Uncorrectable Error Address High 0
#define FLASH_O_ERR_STATUS             0x14U   // Error Status
#define FLASH_O_ERR_POS                0x18U   // Error Position
#define FLASH_O_ERR_STATUS_CLR         0x1CU   // Error Status Clear
#define FLASH_O_ERR_CNT                0x20U   // Error Control
#define FLASH_O_ERR_THRESHOLD          0x24U   // Error Threshold
#define FLASH_O_ERR_INTFLG             0x28U   // Error Interrupt Flag
#define FLASH_O_ERR_INTCLR             0x2CU   // Error Interrupt Flag Clear
#define FLASH_O_DATAH                  0x30U   // Data High Test
#define FLASH_O_DATAL                  0x34U   // Data Low Test
#define FLASH_O_FADDR_TEST             0x38U   // ECC Test Address
#define FLASH_O_FECC_TEST              0x3CU   // ECC Test Address
#define FLASH_O_FECC_CTRL              0x40U   // ECC Control
#define FLASH_O_TESTH                  0x44U   // Test Data Out High
#define FLASH_O_TESTL                  0x48U   // Test Data Out Low
#define FLASH_O_FECC_STATUS            0x4CU   // ECC Status
#define FLASH_O_SEADDRL_1              0x50U   // Single Error Address Low 1
#define FLASH_O_SEADDRH_1              0x54U   // Single Error Address High 1
#define FLASH_O_UNCEADDRL_1            0x58U   // Uncorrectable Error Address Low 1
#define FLASH_O_UNCEADDRH_1            0x5CU   // Uncorrectable Error Address High 1


//*************************************************************************************************
//
// The following are defines for the bit fields in the FRDCNTL register
//
//*************************************************************************************************
#define FLASH_FRDCNTL_RWAIT_S   8U
#define FLASH_FRDCNTL_RWAIT_M   0xFF00U   // Random Read Waitstate

//*************************************************************************************************
//
// The following are defines for the bit fields in the BANK_SWAP_SOFT register
//
//*************************************************************************************************
#define FLASH_BANK_SWAP_SOFT_SWAPSTATUS      0x8U  // SWAP_STATUS bit (bit3)
#define FLASH_BANK_SWAP_SOFT_SWAPSEL         0x4U  // SWAP_SEL bit    (bit2)
#define FLASH_BANK_SWAP_SOFT_SWAP            0x2U  // SWAP bit        (bit1)
#define FLASH_BANK_SWAP_SOFT_BYPASS          0x1U  // SWAP_BYPASS bit (bit0)

//*************************************************************************************************
//
// The following are defines for the bit fields in the FBAC register
//
//*************************************************************************************************
#define FLASH_FBAC_BAGP_S   8U
#define FLASH_FBAC_BAGP_M   0xFF00U   // Bank Active Grace Period

//*************************************************************************************************
//
// The following are defines for the bit fields in the FBFALLBACK register
//
//*************************************************************************************************
#define FLASH_FBFALLBACK_BNKPWR0_S   0U
#define FLASH_FBFALLBACK_BNKPWR0_M   0x3U   // Bank Power Mode of BANK0
#define FLASH_FBFALLBACK_BNKPWR1_S   2U
#define FLASH_FBFALLBACK_BNKPWR1_M   0xCU   // Bank Power Mode of BANK1

//*************************************************************************************************
//
// The following are defines for the bit fields in the FBPRDY register
//
//*************************************************************************************************
#define FLASH_FBPRDY_BANK0RDY   0x1U      // Flash Bank Active Power State
#define FLASH_FBPRDY_BANK1RDY   0x2U      // Flash Bank Active Power State

//*************************************************************************************************
//
// The following are defines for the bit fields in the FMSTAT register
//
//*************************************************************************************************
#define FLASH_FMSTAT_PSUSP              0x2U      // Program Suspend Status
#define FLASH_FMSTAT_ESUSP              0x4U      // Erase Suspend Status
#define FLASH_FMSTAT_CSTAT              0x10U     // Command Fail Status
#define FLASH_FMSTAT_INVDAT             0x20U     // Invalid Data
#define FLASH_FMSTAT_PGM                0x40U     // Program Operation Status
#define FLASH_FMSTAT_ERS                0x80U     // Erase Operation Status
#define FLASH_FMSTAT_BUSY               0x100U    // Busy Bit
#define FLASH_FMSTAT_EV                 0x400U    // Erase Verify Status
#define FLASH_FMSTAT_PGV                0x1000U   // Programming Verify Status
#define FLASH_FMSTAT_REG_NOT_WRITABLE   0x2000U   // NVMC Registers Not Writable Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the FRD_INTF_CTRL register
//
//*************************************************************************************************
#define FLASH_FRD_INTF_CTRL_Bus_prften     0x400U   // busmatrix interface Prefetch enable
#define FLASH_FRD_INTF_CTRL_Bus_buf_clr    0x800U   // busmatrix interface buffer ClearClear Busmatrix Buffer

//*************************************************************************************************
//
// The following are defines for the bit fields in the CR register
//
//*************************************************************************************************
#define FLASH_CR_NDBANK   0x1U   // Not Dual Bank


//*************************************************************************************************
//
// The following are defines for the bit fields in the ECC_ENABLE register
//
//*************************************************************************************************
#define FLASH_ECC_ENABLE_DECODE_ENABLE_S   0U
#define FLASH_ECC_ENABLE_DECODE_ENABLE_M   0xFU    // Enable ECC Decode
#define FLASH_ECC_ENABLE_ENCODE_ENABLE_S   4U
#define FLASH_ECC_ENABLE_ENCODE_ENABLE_M   0xF0U   // Enable ECC Encode

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_STATUS register
//
//*************************************************************************************************
#define FLASH_ERR_STATUS_FLASH0_FAIL_0_L    0x1U         // Lower 64bits Single Bit Error Corrected
                                                         // Value 0 for bank0
#define FLASH_ERR_STATUS_FLASH0_FAIL_1_L    0x2U         // Lower 64bits Single Bit Error Corrected
                                                         // Value 1 for bank0
#define FLASH_ERR_STATUS_FLASH0_UNC_ERR_L   0x4U         // Lower 64 bits Uncorrectable error
                                                         // occurred for bank0
#define FLASH_ERR_STATUS_FLASH0_FAIL_0_H    0x100U       // Upper 64bits Single Bit Error Corrected
                                                         // Value 0 for bank0
#define FLASH_ERR_STATUS_FLASH0_FAIL_1_H    0x200U       // Upper 64bits Single Bit Error Corrected
                                                         // Value 1 for bank0
#define FLASH_ERR_STATUS_FLASH0_UNC_ERR_H   0x400U       // Upper 64 bits Uncorrectable error
                                                         // occurred for bank0
#define FLASH_ERR_STATUS_FLASH1_FAIL_0_L    0x10000U     // Lower 64bits Single Bit Error Corrected
                                                         // Value 0 for bank1
#define FLASH_ERR_STATUS_FLASH1_FAIL_1_L    0x20000U     // Lower 64bits Single Bit Error Corrected
                                                         // Value 1 for bank1
#define FLASH_ERR_STATUS_FLASH1_UNC_ERR_L   0x40000U     // Lower 64 bits Uncorrectable error
                                                         // occurred for bank1
#define FLASH_ERR_STATUS_FLASH1_FAIL_0_H    0x1000000U   // Upper 64bits Single Bit Error Corrected
                                                         // Value 0 for bank1
#define FLASH_ERR_STATUS_FLASH1_FAIL_1_H    0x2000000U   // Upper 64bits Single Bit Error Corrected
                                                         // Value 1 for bank1
#define FLASH_ERR_STATUS_FLASH1_UNC_ERR_H   0x4000000U   // Upper 64 bits Uncorrectable error
                                                         // occurred for bank1

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_POS register
//
//*************************************************************************************************
#define FLASH_ERR_POS_Flash0_ERR_POS_L_S   0U
#define FLASH_ERR_POS_Flash0_ERR_POS_L_M   0x3FU         // Bit Position of Single bit Error in
                                                         // lower 64 bits for bank0
#define FLASH_ERR_POS_FLASH0_ERR_TYPE_L    0x80U         // Error Type in lower 64 bits for bank0
#define FLASH_ERR_POS_Flash0_ERR_POS_H_S   8U
#define FLASH_ERR_POS_Flash0_ERR_POS_H_M   0x3F00U       // Bit Position of Single bit Error in
                                                         // upper 64 bits for bank0
#define FLASH_ERR_POS_FLASH0_ERR_TYPE_H    0x8000U       // Error Type in upper 64 bits for bank0
#define FLASH_ERR_POS_Flash1_ERR_POS_L_S   16U
#define FLASH_ERR_POS_Flash1_ERR_POS_L_M   0x3F0000U     // Bit Position of Single bit Error in
                                                         // lower 64 bits for bank1
#define FLASH_ERR_POS_FLASH1_ERR_TYPE_L    0x800000U     // Error Type in lower 64 bits for bank1
#define FLASH_ERR_POS_Flash1_ERR_POS_H_S   24U
#define FLASH_ERR_POS_Flash1_ERR_POS_H_M   0x3F000000U   // Bit Position of Single bit Error in
                                                         // upper 64 bits for bank1
#define FLASH_ERR_POS_FLASH1_ERR_TYPE_H    0x80000000U   // Error Type in upper 64 bits for bank1

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_STATUS_CLR register
//
//*************************************************************************************************
#define FLASH_ERR_STATUS_CLR_FLASH0_FAIL_0_L_CLR    0x1U         // Lower 64bits Single Bit Error
                                                                 // Corrected Value 0 Clear for bank0
#define FLASH_ERR_STATUS_CLR_FLASH0_FAIL_1_L_CLR    0x2U         // Lower 64bits Single Bit Error
                                                                 // Corrected Value 1 Clear for bank0
#define FLASH_ERR_STATUS_CLR_FLASH0_UNC_ERR_L_CLR   0x4U         // Lower 64 bits Uncorrectable
                                                                 // error occurred Clear for bank0
#define FLASH_ERR_STATUS_CLR_FLASH0_FAIL_0_H_CLR    0x100U       // Upper 64bits Single Bit Error
                                                                 // Corrected Value 0 Clear for bank0
#define FLASH_ERR_STATUS_CLR_FLASH0_FAIL_1_H_CLR    0x200U       // Upper 64bits Single Bit Error
                                                                 // Corrected Value 1 Clear for bank0
#define FLASH_ERR_STATUS_CLR_FLASH0_UNC_ERR_H_CLR   0x400U       // Upper 64 bits Uncorrectable
                                                                 // error occurred Clear for bank0
#define FLASH_ERR_STATUS_CLR_FLASH1_FAIL_0_L_CLR    0x10000U     // Lower 64bits Single Bit Error
                                                                 // Corrected Value 0 Clear for bank1
#define FLASH_ERR_STATUS_CLR_FLASH1_FAIL_1_L_CLR    0x20000U     // Lower 64bits Single Bit Error
                                                                 // Corrected Value 1 Clear for bank1
#define FLASH_ERR_STATUS_CLR_FLASH1_UNC_ERR_L_CLR   0x40000U     // Lower 64 bits Uncorrectable
                                                                 // error occurred Clear for bank1
#define FLASH_ERR_STATUS_CLR_FLASH1_FAIL_0_H_CLR    0x1000000U   // Upper 64bits Single Bit Error
                                                                 // Corrected Value 0 Clear for bank1
#define FLASH_ERR_STATUS_CLR_FLASH1_FAIL_1_H_CLR    0x2000000U   // Upper 64bits Single Bit Error
                                                                 // Corrected Value 1 Clear for bank1
#define FLASH_ERR_STATUS_CLR_FLASH1_UNC_ERR_H_CLR   0x4000000U   // Upper 64 bits Uncorrectable
                                                                 // error occurred Clear for bank1

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_CNT register
//
//*************************************************************************************************
#define FLASH_ERR_CNT_ERR_CNT_S   0U
#define FLASH_ERR_CNT_ERR_CNT_M   0xFFFFU   // Error counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_THRESHOLD register
//
//*************************************************************************************************
#define FLASH_ERR_THRESHOLD_ERR_THRESHOLD_S   0U
#define FLASH_ERR_THRESHOLD_ERR_THRESHOLD_M   0xFFFFU   // Error Threshold

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_INTFLG register
//
//*************************************************************************************************
#define FLASH_ERR_INTFLG_SINGLE_ERR_INTFLG    0x1U   // Single Error Interrupt Flag
#define FLASH_ERR_INTFLG_UNC_ERR_INTFLG       0x2U   // Uncorrectable Interrupt Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_INTCLR register
//
//*************************************************************************************************
#define FLASH_ERR_INTCLR_SINGLE_ERR_INTCLR    0x1U   // Single Error Interrupt Flag Clear
#define FLASH_ERR_INTCLR_UNC_ERR_INTCLR       0x2U   // Uncorrectable Interrupt Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the FADDR_TEST register
//
//*************************************************************************************************
#define FLASH_FADDR_TEST_ADDRL_S   3U
#define FLASH_FADDR_TEST_ADDRL_M   0xFFF8U     // ECC Address Low
#define FLASH_FADDR_TEST_ADDRH_S   16U
#define FLASH_FADDR_TEST_ADDRH_M   0x3F0000U   // ECC Address High

//*************************************************************************************************
//
// The following are defines for the bit fields in the FECC_TEST register
//
//*************************************************************************************************
#define FLASH_FECC_TEST_ECC_S   0U
#define FLASH_FECC_TEST_ECC_M   0xFFU   // ECC Control Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the FECC_CTRL register
//
//*************************************************************************************************
#define FLASH_FECC_CTRL_ECC_TEST_EN    0x1U   // Enable ECC Test Logic
#define FLASH_FECC_CTRL_ECC_SELECT_S   1U
#define FLASH_FECC_CTRL_ECC_SELECT_M   0x6U   // ECC Block Select
#define FLASH_FECC_CTRL_DO_ECC_CALC    0x8U   // Enable ECC Calculation

//*************************************************************************************************
//
// The following are defines for the bit fields in the FECC_STATUS register
//
//*************************************************************************************************
#define FLASH_FECC_STATUS_TSEFLG        0x1U     // Test Result is Single Bit Error
#define FLASH_FECC_STATUS_TUNCEFLG      0x2U     // Test Result is Uncorrectable Error
#define FLASH_FECC_STATUS_TSEPOS_S      2U
#define FLASH_FECC_STATUS_TSEPOS_M      0xFCU    // Holds Bit Position of Error
#define FLASH_FECC_STATUS_TSETYPE       0x100U   // Holds Bit Position of 8 Check Bits of Error



#endif
