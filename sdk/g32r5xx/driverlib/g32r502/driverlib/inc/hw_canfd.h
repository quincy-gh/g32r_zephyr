//###########################################################################
//
// FILE:    hw_canfd.h
//
// TITLE:   Definitions for the canfd registers.
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

#ifndef HW_CANFD_H
#define HW_CANFD_H

//*************************************************************************************************
// The following are defines for the CANFD register offsets
//*************************************************************************************************
#define CANFD_O_CREL                0x00       // Core Release Register
#define CANFD_O_ENDN                0x04       // Endian Register
#define CANFD_O_DBTP                0x0C       // Data Bit Timing & Prescaler Register
#define CANFD_O_TEST                0x10       // Test Register
#define CANFD_O_RWD                 0x14       // RAM Watchdog
#define CANFD_O_CCCR                0x18       // CC Control Register
#define CANFD_O_NBTP                0x1C       // Nominal Bit Timing & Prescaler Register
#define CANFD_O_TSCC                0x20       // Timestamp Counter Configuration
#define CANFD_O_TSCV                0x24       // Timestamp Counter Value
#define CANFD_O_TOCC                0x28       // Timeout Counter Configuration
#define CANFD_O_TOCV                0x2C       // Timeout Counter Value
#define CANFD_O_ECR                 0x40       // Error Counter Register
#define CANFD_O_PSR                 0x44       // Protocol Status Register
#define CANFD_O_TDCR                0x48       // Transmitter Delay Compensation Register
#define CANFD_O_IR                  0x50       // Interrupt Register
#define CANFD_O_IE                  0x54       // Interrupt Enable
#define CANFD_O_ILS                 0x58       // Interrupt Line Select
#define CANFD_O_ILE                 0x5C       // Interrupt Line Enable
#define CANFD_O_GFC                 0x80       // Global Filter Configuration
#define CANFD_O_SIDFC               0x84       // Standard ID Filter Configuration
#define CANFD_O_XIDFC               0x88       // Extended ID Filter Configuration
#define CANFD_O_XIDAM               0x90       // Extended ID AND Mask
#define CANFD_O_HPMS                0x94       // High Priority Message Status
#define CANFD_O_NDAT1               0x98       // New Data 1
#define CANFD_O_NDAT2               0x9C       // New Data 2
#define CANFD_O_RXF0C               0xA0       // Rx FIFO 0 Configuration
#define CANFD_O_RXF0S               0xA4       // Rx FIFO 0 Status
#define CANFD_O_RXF0A               0xA8       // Rx FIFO 0 Acknowledge
#define CANFD_O_RXBC                0xAC       // Rx Buffer Configuration
#define CANFD_O_RXF1C               0xB0       // Rx FIFO 1 Configuration
#define CANFD_O_RXF1S               0xB4       // Rx FIFO 1 Status
#define CANFD_O_RXF1A               0xB8       // Rx FIFO 1 Acknowledge
#define CANFD_O_RXESC               0xBC       // Rx Buffer / FIFO Element Size Config
#define CANFD_O_TXBC                0xC0       // Tx Buffer Configuration
#define CANFD_O_TXFQS               0xC4       // Tx FIFO/Queue Status
#define CANFD_O_TXESC               0xC8       // Tx Buffer Element Size Config
#define CANFD_O_TXBRP               0xCC       // Tx Buffer Request Pending
#define CANFD_O_TXBAR               0xD0       // Tx Buffer Add Request
#define CANFD_O_TXBCR               0xD4       // Tx Buffer Cancellation Request
#define CANFD_O_TXBTO               0xD8       // Tx Buffer Transmission Occurred
#define CANFD_O_TXBCF               0xDC       // Tx Buffer Cancellation Finished
#define CANFD_O_TXBTIE              0xE0       // Tx Buffer Transmission Int Enable
#define CANFD_O_TXBCIE              0xE4       // Tx Buffer Cancellation Finished Int Enable
#define CANFD_O_TXEFC               0xF0       // Tx Event FIFO Configuration
#define CANFD_O_TXEFS               0xF4       // Tx Event FIFO Status
#define CANFD_O_TXEFA               0xF8       // Tx Event FIFO Acknowledge


#define CANFD_O_ERM_CTRL            (0x100U + 0x00U)
#define CANFD_O_ERM_STS             (0x100U + 0x04U)
#define CANFD_O_ERM_ECC_ADDR_LOG    (0x100U + 0x08U)
#define CANFD_O_ERM_ECC_DATA_LOG    (0x100U + 0x0CU)
#define CANFD_O_ERM_RAM_INIT        (0x100U + 0x10U)
#define CANFD_O_ERM_EXTC_CTRL       (0x100U + 0x14U)
#define CANFD_O_ERM_EXTC_VAL        (0x100U + 0x18U)

//*************************************************************************************************
//
// The following are defines for the bit fields in the CREL register
//
//*************************************************************************************************
#define CANFD_CREL_DAY_S             0U
#define CANFD_CREL_DAY_M             0xFFU           // Day field
#define CANFD_CREL_MON_S             8U
#define CANFD_CREL_MON_M             0xFF00U         // Month field
#define CANFD_CREL_YEAR_S            16U
#define CANFD_CREL_YEAR_M            0xF0000U        // Year field
#define CANFD_CREL_SUBSTEP_S         20U
#define CANFD_CREL_SUBSTEP_M         0xF00000U       // Sub-Step field
#define CANFD_CREL_STEP_S            24U
#define CANFD_CREL_STEP_M            0xF000000U      // Step field
#define CANFD_CREL_REL_S             28U
#define CANFD_CREL_REL_M             0xF0000000U     // Core Release field

//*************************************************************************************************
//
// The following are defines for the bit fields in the ENDN register
//
//*************************************************************************************************
#define CANFD_ENDN_ETV_S             0U
#define CANFD_ENDN_ETV_M             0xFFFFFFFFU     // Endianness Test Value field

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBTP register
//
//*************************************************************************************************
#define CANFD_DBTP_DSJW_S            0U
#define CANFD_DBTP_DSJW_M            0xFU            // DSJW bits
#define CANFD_DBTP_DTSEG2_S          4U
#define CANFD_DBTP_DTSEG2_M          0xF0U           // DTSEG2 bits
#define CANFD_DBTP_DTSEG1_S          8U
#define CANFD_DBTP_DTSEG1_M          0x1F00U         // DTSEG1 bits
#define CANFD_DBTP_DBRP_S            16U
#define CANFD_DBTP_DBRP_M            0x1F0000U       // DBRP bits
#define CANFD_DBTP_TDC               0x800000U        // TDC bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the TEST register
//
//*************************************************************************************************
#define CANFD_TEST_LBCK              0x10U           // Loop Back Mode bit
#define CANFD_TEST_TX_S              5U
#define CANFD_TEST_TX_M              0x60U           // TX bits
#define CANFD_TEST_RX                0x80U           // RX bit
#define CANFD_TEST_TXBNP_S           8U
#define CANFD_TEST_TXBNP_M           0x1F00U         // TX Buffer Number Prepared
#define CANFD_TEST_PVAL              0x2000U         // Prepared Valid bit
#define CANFD_TEST_TXBNS_S           16U
#define CANFD_TEST_TXBNS_M           0x1F0000U       // TX Buffer Number Started
#define CANFD_TEST_SVAL              0x200000U       // Started Valid bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the RWD register
//
//*************************************************************************************************
#define CANFD_RWD_WDC_S              0U
#define CANFD_RWD_WDC_M              0xFFU           // Watchdog Configuration
#define CANFD_RWD_WDV_S              8U
#define CANFD_RWD_WDV_M              0xFF00U         // Watchdog Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the CCCR register
//
//*************************************************************************************************
#define CANFD_CCCR_INIT              0x1U            // Initialization
#define CANFD_CCCR_CCE               0x2U            // Configuration Change Enable
#define CANFD_CCCR_ASM               0x4U            // Restricted Operation Mode
#define CANFD_CCCR_CSA               0x8U            // Clock Stop Acknowledge
#define CANFD_CCCR_CSR               0x10U           // Clock Stop Request
#define CANFD_CCCR_MON               0x20U           // Bus Monitoring Mode
#define CANFD_CCCR_DAR               0x40U           // Disable Automatic Retransmission
#define CANFD_CCCR_TEST              0x80U           // Test Mode Enable
#define CANFD_CCCR_FDOE              0x100U          // FD Operation Enable
#define CANFD_CCCR_BRSE              0x200U          // Bit Rate Switch Enable
#define CANFD_CCCR_WMM               0x800U          // Wide Message Marker
#define CANFD_CCCR_PXHD              0x1000U         // Protocol Exception Handling Disable
#define CANFD_CCCR_EFBI              0x2000U         // Edge Filtering during Bus Integration
#define CANFD_CCCR_TXP               0x4000U         // Transmit Pause
#define CANFD_CCCR_NISO              0x8000U         // Non-ISO Operation

//*************************************************************************************************
//
// The following are defines for the bit fields in the NBTP register
//
//*************************************************************************************************
#define CANFD_NBTP_NTSEG2_S          0U
#define CANFD_NBTP_NTSEG2_M          0x7FU           // Nominal Time segment after sample point
#define CANFD_NBTP_NTSEG1_S          8U
#define CANFD_NBTP_NTSEG1_M          0xFF00U         // Nominal Time segment before sample point
#define CANFD_NBTP_NBRP_S            16U
#define CANFD_NBTP_NBRP_M            0x1FF0000U      // Nominal Bit Rate Prescaler
#define CANFD_NBTP_NSJW_S            25U
#define CANFD_NBTP_NSJW_M            0xFE000000U     // Nominal (Re)Synchronization Jump Width

//*************************************************************************************************
//
// The following are defines for the bit fields in the TSCC register
//
//*************************************************************************************************
#define CANFD_TSCC_TSS_S           0U
#define CANFD_TSCC_TSS_M           0x3U         // Timestamp Select
#define CANFD_TSCC_TCP_S           16U
#define CANFD_TSCC_TCP_M           0xF0000U        // Timestamp Counter Prescaler

//*************************************************************************************************
//
// The following are defines for the bit fields in the TSCV register
//
//*************************************************************************************************
#define CANFD_TSCV_TSC_S           0U
#define CANFD_TSCV_TSC_M           0xFFFFU         // Timestamp Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the TOCC register
//
//*************************************************************************************************
#define CANFD_TOCC_ETOC            0x1U            // Enable Timeout Counter
#define CANFD_TOCC_TOS_S           1U
#define CANFD_TOCC_TOS_M           0x6U            // Timeout Select
#define CANFD_TOCC_TOP_S           16U
#define CANFD_TOCC_TOP_M           0xFFFF0000U     // Timeout Period

//*************************************************************************************************
//
// The following are defines for the bit fields in the TOCV register
//
//*************************************************************************************************
#define CANFD_TOCV_TOC_S           0U
#define CANFD_TOCV_TOC_M           0xFFFFU         // Timeout Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECR register
//
//*************************************************************************************************
#define CANFD_ECR_TEC_S            0U
#define CANFD_ECR_TEC_M            0xFFU           // Transmit Error Counter
#define CANFD_ECR_REC_S            8U
#define CANFD_ECR_REC_M            0x7F00U         // Receive Error Counter
#define CANFD_ECR_RP               0x8000U         // Receive Error Passive
#define CANFD_ECR_CEL_S            16U
#define CANFD_ECR_CEL_M            0xFF0000U       // CAN Error Logging

//*************************************************************************************************
//
// The following are defines for the bit fields in the PSR register
//
//*************************************************************************************************
#define CANFD_PSR_LEC_S            0U
#define CANFD_PSR_LEC_M            0x7U            // Last Error Code
#define CANFD_PSR_ACT_S            3U
#define CANFD_PSR_ACT_M            0x18U           // Activity
#define CANFD_PSR_EP               0x20U           // Error Passive
#define CANFD_PSR_EW               0x40U           // Warning Status
#define CANFD_PSR_BO               0x80U           // Bus_Off Status
#define CANFD_PSR_DLEC_S           8U
#define CANFD_PSR_DLEC_M           0x700U          // Data Phase Last Error Code
#define CANFD_PSR_RESI             0x800U          // ESI flag of last received CAN FD Message
#define CANFD_PSR_RBRS             0x1000U         // BRS flag of last received CAN FD Message
#define CANFD_PSR_RFDF             0x2000U         // Received a CAN FD Message
#define CANFD_PSR_PXE              0x4000U         // Protocol Exception Event
#define CANFD_PSR_TDCV_S           16U
#define CANFD_PSR_TDCV_M           0x7F0000U       // Transmitter Delay Compensation Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the TDCR register
//
//*************************************************************************************************
#define CANFD_TDCR_TDCF_S          0U
#define CANFD_TDCR_TDCF_M          0x7FU           // TDC Filter Window
#define CANFD_TDCR_TDCO_S          8U
#define CANFD_TDCR_TDCO_M          0x7F00U         // TDC SSP Offset

//*************************************************************************************************
//
// The following are defines for the bit fields in the IR register
//
//*************************************************************************************************
#define CANFD_IR_RF0N              0x1U            // Rx FIFO 0 New Message
#define CANFD_IR_RF0W              0x2U            // Rx FIFO 0 Watermark Reached
#define CANFD_IR_RF0F              0x4U            // Rx FIFO 0 Full
#define CANFD_IR_RF0L              0x8U            // Rx FIFO 0 Message Lost
#define CANFD_IR_RF1N              0x10U           // Rx FIFO 1 New Message
#define CANFD_IR_RF1W              0x20U           // Rx FIFO 1 Watermark Reached
#define CANFD_IR_RF1F              0x40U           // Rx FIFO 1 Full
#define CANFD_IR_RF1L              0x80U           // Rx FIFO 1 Message Lost
#define CANFD_IR_HPM               0x100U          // High Priority Message
#define CANFD_IR_TC                0x200U          // Transmission Completed
#define CANFD_IR_TCF               0x400U          // Transmission Cancellation Finished
#define CANFD_IR_TFE               0x800U          // Tx FIFO Empty
#define CANFD_IR_TEFN              0x1000U         // Tx Event FIFO New Entry
#define CANFD_IR_TEFW              0x2000U         // Tx Event FIFO Watermark Reached
#define CANFD_IR_TEFF              0x4000U         // Tx Event FIFO Full
#define CANFD_IR_TEFL              0x8000U         // Tx Event FIFO Element Lost
#define CANFD_IR_TSW               0x10000U        // Timestamp Wraparound
#define CANFD_IR_MRAF              0x20000U        // Message RAM Access Failure
#define CANFD_IR_TOO               0x40000U        // Timeout Occurred
#define CANFD_IR_DRX               0x80000U        // Message stored to Dedicated Rx Buffer
#define CANFD_IR_ELO               0x400000U       // Error Logging Overflow
#define CANFD_IR_EP                0x800000U       // Error Passive
#define CANFD_IR_EW                0x1000000U      // Warning Status
#define CANFD_IR_BO                0x2000000U      // Bus_Off Status
#define CANFD_IR_WDI               0x4000000U      // Watchdog Interrupt
#define CANFD_IR_PEA               0x8000000U      // Protocol Error in Arbitration Phase
#define CANFD_IR_PED               0x10000000U     // Protocol Error in Data Phase
#define CANFD_IR_ARA               0x20000000U     // Access to Reserved Address

//*************************************************************************************************
//
// The following are defines for the bit fields in the IE register
//
//*************************************************************************************************
#define CANFD_IE_RF0NE             0x1U            // Rx FIFO 0 New Message IE
#define CANFD_IE_RF0WE             0x2U            // Rx FIFO 0 Watermark IE
#define CANFD_IE_RF0FE             0x4U            // Rx FIFO 0 Full IE
#define CANFD_IE_RF0LE             0x8U            // Rx FIFO 0 Message Lost IE
#define CANFD_IE_RF1NE             0x10U           // Rx FIFO 1 New Message IE
#define CANFD_IE_RF1WE             0x20U           // Rx FIFO 1 Watermark IE
#define CANFD_IE_RF1FE             0x40U           // Rx FIFO 1 Full IE
#define CANFD_IE_RF1LE             0x80U           // Rx FIFO 1 Message Lost IE
#define CANFD_IE_HPME              0x100U          // High Priority Message IE
#define CANFD_IE_TCE               0x200U          // Transmission Completed IE
#define CANFD_IE_TCFE              0x400U          // Transmission Cancellation Finished IE
#define CANFD_IE_TFEE              0x800U          // Tx FIFO Empty IE
#define CANFD_IE_TEFNE             0x1000U         // Tx Event FIFO New Entry IE
#define CANFD_IE_TEFWE             0x2000U         // Tx Event FIFO Watermark IE
#define CANFD_IE_TEFFE             0x4000U         // Tx Event FIFO Full IE
#define CANFD_IE_TEFLE             0x8000U         // Tx Event FIFO Element Lost IE
#define CANFD_IE_TSWE              0x10000U        // Timestamp Wraparound IE
#define CANFD_IE_MRAFE             0x20000U        // Message RAM Access Failure IE
#define CANFD_IE_TOOE              0x40000U        // Timeout Occurred IE
#define CANFD_IE_DRXE              0x80000U        // Dedicated Rx Buffer IE
#define CANFD_IE_ELOE              0x400000U       // Error Logging Overflow IE
#define CANFD_IE_EPE               0x800000U       // Error Passive IE
#define CANFD_IE_EWE               0x1000000U      // Warning Status IE
#define CANFD_IE_BOE               0x2000000U      // Bus_Off Status IE
#define CANFD_IE_WDIE              0x4000000U      // Watchdog IE
#define CANFD_IE_PEAE              0x8000000U      // Protocol Error in Arbitration Phase IE
#define CANFD_IE_PEDE              0x10000000U     // Protocol Error in Data Phase IE
#define CANFD_IE_ARAE              0x20000000U     // Access to Reserved Address IE

//*************************************************************************************************
//
// The following are defines for the bit fields in the ILS register
//
//*************************************************************************************************
#define CANFD_ILS_RF0NL            0x1U            // Rx FIFO 0 New Message Interrupt Line
#define CANFD_ILS_RF0WL            0x2U            // Rx FIFO 0 Watermark Interrupt Line
#define CANFD_ILS_RF0FL            0x4U            // Rx FIFO 0 Full Interrupt Line
#define CANFD_ILS_RF0LL            0x8U            // Rx FIFO 0 Message Lost Interrupt Line
#define CANFD_ILS_RF1NL            0x10U           // Rx FIFO 1 New Message Interrupt Line
#define CANFD_ILS_RF1WL            0x20U           // Rx FIFO 1 Watermark Interrupt Line
#define CANFD_ILS_RF1FL            0x40U           // Rx FIFO 1 Full Interrupt Line
#define CANFD_ILS_RF1LL            0x80U           // Rx FIFO 1 Message Lost Interrupt Line
#define CANFD_ILS_HPML             0x100U          // High Priority Message Interrupt Line
#define CANFD_ILS_TCL              0x200U          // Transmission Completed Interrupt Line
#define CANFD_ILS_TCFL             0x400U          // Transmission Cancellation Finished Interrupt Line
#define CANFD_ILS_TFEL             0x800U          // Tx FIFO Empty Interrupt Line
#define CANFD_ILS_TEFNL            0x1000U         // Tx Event FIFO New Entry Interrupt Line
#define CANFD_ILS_TEFWL            0x2000U         // Tx Event FIFO Watermark Interrupt Line
#define CANFD_ILS_TEFFL            0x4000U         // Tx Event FIFO Full Interrupt Line
#define CANFD_ILS_TEFLL            0x8000U         // Tx Event FIFO Event Lost Interrupt Line
#define CANFD_ILS_TSWL             0x10000U        // Timestamp Wraparound Interrupt Line
#define CANFD_ILS_MRAFL            0x20000U        // Message RAM Access Failure Interrupt Line
#define CANFD_ILS_TOOL             0x40000U        // Timeout Occurred Interrupt Line
#define CANFD_ILS_DRXL             0x80000U        // Dedicated Rx Buffer Interrupt Line
#define CANFD_ILS_ELOL             0x400000U       // Error Logging Overflow Interrupt Line
#define CANFD_ILS_EPL              0x800000U       // Error Passive Interrupt Line
#define CANFD_ILS_EWL              0x1000000U      // Warning Status Interrupt Line
#define CANFD_ILS_BOL              0x2000000U      // Bus_Off Status Interrupt Line
#define CANFD_ILS_WDIL             0x4000000U      // Watchdog Interrupt Line
#define CANFD_ILS_PEAL             0x8000000U      // Protocol Error in Arbitration Phase Line
#define CANFD_ILS_PEDL             0x10000000U     // Protocol Error in Data Phase Line
#define CANFD_ILS_ARAL             0x20000000U     // Access to Reserved Address Line

//*************************************************************************************************
//
// The following are defines for the bit fields in the ILS register
//
//*************************************************************************************************
#define CANFD_ILS_EINT0            0x1U            // Enable Interrupt Line 0
#define CANFD_ILS_EINT1            0x2U            // Enable Interrupt Line 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the ILE register
//
//*************************************************************************************************
#define CANFD_ILE_EINT0            0x1U            // Enable Interrupt Line 0
#define CANFD_ILE_EINT1            0x2U            // Enable Interrupt Line 1


//*************************************************************************************************
//
// The following are defines for the bit fields in the GFC register
//
//*************************************************************************************************
#define CANFD_GFC_RRFE             0x1U            // Reject Remote Frames Extended
#define CANFD_GFC_RRFS             0x2U            // Reject Remote Frames Standard
#define CANFD_GFC_ANFE_S           2U
#define CANFD_GFC_ANFE_M           0xCU            // Accept Non-matching Frames Extended
#define CANFD_GFC_ANFS_S           4U
#define CANFD_GFC_ANFS_M           0x30U           // Accept Non-matching Frames Standard


//*************************************************************************************************
//
// The following are defines for the bit fields in the SIDFC register
//
//*************************************************************************************************
#define CANFD_SIDFC_FLSSA_S        2U
#define CANFD_SIDFC_FLSSA_M        0xFFFCU         // Filter List Standard Start Address
#define CANFD_SIDFC_LSS_S          16U
#define CANFD_SIDFC_LSS_M          0xFF0000U       // List Size Standard

//*************************************************************************************************
//
// The following are defines for the bit fields in the XIDFC register
//
//*************************************************************************************************
#define CANFD_XIDFC_FLESA_S        2U
#define CANFD_XIDFC_FLESA_M        0xFFFCU         // Filter List Extended Start Address
#define CANFD_XIDFC_LSE_S          16U
#define CANFD_XIDFC_LSE_M          0x7F0000U       // List Size Extended

//*************************************************************************************************
//
// The following are defines for the bit fields in the XIDAM register
//
//*************************************************************************************************
#define CANFD_XIDAM_EIDM_S         0U
#define CANFD_XIDAM_EIDM_M         0x1FFFFFFFU     // Extended ID Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the HPMS register
//
//*************************************************************************************************
#define CANFD_HPMS_BIDX_S          0U
#define CANFD_HPMS_BIDX_M          0x3FU           // Buffer Index
#define CANFD_HPMS_MSI_S           6U
#define CANFD_HPMS_MSI_M           0xC0U           // Message Storage Indicator
#define CANFD_HPMS_FIDX_S          8U
#define CANFD_HPMS_FIDX_M          0x7F00U         // Filter Index
#define CANFD_HPMS_FLST            0x8000U         // Filter List

//*************************************************************************************************
//
// The following are defines for the bit fields in the NDAT1 register
//
//*************************************************************************************************
#define CANFD_NDAT1_ND0    0x1U          // New Data RX Buffer 0
#define CANFD_NDAT1_ND1    0x2U          // New Data RX Buffer 1
#define CANFD_NDAT1_ND2    0x4U          // New Data RX Buffer 2
#define CANFD_NDAT1_ND3    0x8U          // New Data RX Buffer 3
#define CANFD_NDAT1_ND4    0x10U         // New Data RX Buffer 4
#define CANFD_NDAT1_ND5    0x20U         // New Data RX Buffer 5
#define CANFD_NDAT1_ND6    0x40U         // New Data RX Buffer 6
#define CANFD_NDAT1_ND7    0x80U         // New Data RX Buffer 7
#define CANFD_NDAT1_ND8    0x100U        // New Data RX Buffer 8
#define CANFD_NDAT1_ND9    0x200U        // New Data RX Buffer 9
#define CANFD_NDAT1_ND10   0x400U        // New Data RX Buffer 10
#define CANFD_NDAT1_ND11   0x800U        // New Data RX Buffer 11
#define CANFD_NDAT1_ND12   0x1000U       // New Data RX Buffer 12
#define CANFD_NDAT1_ND13   0x2000U       // New Data RX Buffer 13
#define CANFD_NDAT1_ND14   0x4000U       // New Data RX Buffer 14
#define CANFD_NDAT1_ND15   0x8000U       // New Data RX Buffer 15
#define CANFD_NDAT1_ND16   0x10000U      // New Data RX Buffer 16
#define CANFD_NDAT1_ND17   0x20000U      // New Data RX Buffer 17
#define CANFD_NDAT1_ND18   0x40000U      // New Data RX Buffer 18
#define CANFD_NDAT1_ND19   0x80000U      // New Data RX Buffer 19
#define CANFD_NDAT1_ND20   0x100000U     // New Data RX Buffer 20
#define CANFD_NDAT1_ND21   0x200000U     // New Data RX Buffer 21
#define CANFD_NDAT1_ND22   0x400000U     // New Data RX Buffer 22
#define CANFD_NDAT1_ND23   0x800000U     // New Data RX Buffer 23
#define CANFD_NDAT1_ND24   0x1000000U    // New Data RX Buffer 24
#define CANFD_NDAT1_ND25   0x2000000U    // New Data RX Buffer 25
#define CANFD_NDAT1_ND26   0x4000000U    // New Data RX Buffer 26
#define CANFD_NDAT1_ND27   0x8000000U    // New Data RX Buffer 27
#define CANFD_NDAT1_ND28   0x10000000U   // New Data RX Buffer 28
#define CANFD_NDAT1_ND29   0x20000000U   // New Data RX Buffer 29
#define CANFD_NDAT1_ND30   0x40000000U   // New Data RX Buffer 30
#define CANFD_NDAT1_ND31   0x80000000U   // New Data RX Buffer 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the NDAT2 register
//
//*************************************************************************************************
#define CANFD_NDAT2_ND32   0x1U          // New Data RX Buffer 32
#define CANFD_NDAT2_ND33   0x2U          // New Data RX Buffer 33
#define CANFD_NDAT2_ND34   0x4U          // New Data RX Buffer 34
#define CANFD_NDAT2_ND35   0x8U          // New Data RX Buffer 35
#define CANFD_NDAT2_ND36   0x10U         // New Data RX Buffer 36
#define CANFD_NDAT2_ND37   0x20U         // New Data RX Buffer 37
#define CANFD_NDAT2_ND38   0x40U         // New Data RX Buffer 38
#define CANFD_NDAT2_ND39   0x80U         // New Data RX Buffer 39
#define CANFD_NDAT2_ND40   0x100U        // New Data RX Buffer 40
#define CANFD_NDAT2_ND41   0x200U        // New Data RX Buffer 41
#define CANFD_NDAT2_ND42   0x400U        // New Data RX Buffer 42
#define CANFD_NDAT2_ND43   0x800U        // New Data RX Buffer 43
#define CANFD_NDAT2_ND44   0x1000U       // New Data RX Buffer 44
#define CANFD_NDAT2_ND45   0x2000U       // New Data RX Buffer 45
#define CANFD_NDAT2_ND46   0x4000U       // New Data RX Buffer 46
#define CANFD_NDAT2_ND47   0x8000U       // New Data RX Buffer 47
#define CANFD_NDAT2_ND48   0x10000U      // New Data RX Buffer 48
#define CANFD_NDAT2_ND49   0x20000U      // New Data RX Buffer 49
#define CANFD_NDAT2_ND50   0x40000U      // New Data RX Buffer 50
#define CANFD_NDAT2_ND51   0x80000U      // New Data RX Buffer 51
#define CANFD_NDAT2_ND52   0x100000U     // New Data RX Buffer 52
#define CANFD_NDAT2_ND53   0x200000U     // New Data RX Buffer 53
#define CANFD_NDAT2_ND54   0x400000U     // New Data RX Buffer 54
#define CANFD_NDAT2_ND55   0x800000U     // New Data RX Buffer 55
#define CANFD_NDAT2_ND56   0x1000000U    // New Data RX Buffer 56
#define CANFD_NDAT2_ND57   0x2000000U    // New Data RX Buffer 57
#define CANFD_NDAT2_ND58   0x4000000U    // New Data RX Buffer 58
#define CANFD_NDAT2_ND59   0x8000000U    // New Data RX Buffer 59
#define CANFD_NDAT2_ND60   0x10000000U   // New Data RX Buffer 60
#define CANFD_NDAT2_ND61   0x20000000U   // New Data RX Buffer 61
#define CANFD_NDAT2_ND62   0x40000000U   // New Data RX Buffer 62
#define CANFD_NDAT2_ND63   0x80000000U   // New Data RX Buffer 63

//*************************************************************************************************
//
// The following are defines for the bit fields in the RXF0C register
//
//*************************************************************************************************
#define CANFD_RXF0C_F0SA_S         2U
#define CANFD_RXF0C_F0SA_M         0xFFFCU         // Rx FIFO 0 Start Address
#define CANFD_RXF0C_F0S_S          16U
#define CANFD_RXF0C_F0S_M          0x7F0000U       // Rx FIFO 0 Size
#define CANFD_RXF0C_F0WM_S         24U
#define CANFD_RXF0C_F0WM_M         0x7F000000U     // Rx FIFO 0 Watermark
#define CANFD_RXF0C_F0OM           0x80000000U     // FIFO 0 Operation Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the RXF0S register
//
//*************************************************************************************************
#define CANFD_RXF0S_F0FL_S         0U
#define CANFD_RXF0S_F0FL_M         0x7FU           // Rx FIFO 0 Fill Level
#define CANFD_RXF0S_F0GI_S         8U
#define CANFD_RXF0S_F0GI_M         0x3F00U         // Rx FIFO 0 Get Index
#define CANFD_RXF0S_F0PI_S         16U
#define CANFD_RXF0S_F0PI_M         0x3F0000U       // Rx FIFO 0 Put Index
#define CANFD_RXF0S_F0F            0x1000000U      // Rx FIFO 0 Full
#define CANFD_RXF0S_RF0L           0x2000000U      // Rx FIFO 0 Message Lost

//*************************************************************************************************
//
// The following are defines for the bit fields in the RXF0A register
//
//*************************************************************************************************
#define CANFD_RXF0A_F0AI_S         0U
#define CANFD_RXF0A_F0AI_M         0x3FU           // Rx FIFO 0 Acknowledge Index

//*************************************************************************************************
//
// The following are defines for the bit fields in the RXBC register
//
//*************************************************************************************************
#define CANFD_RXBC_RBSA_S          2U
#define CANFD_RXBC_RBSA_M          0xFFFCU         // Rx Buffer Start Address

//*************************************************************************************************
//
// The following are defines for the bit fields in the RXF1C register
//
//*************************************************************************************************
#define CANFD_RXF1C_F1SA_S         2U
#define CANFD_RXF1C_F1SA_M         0xFFFCU         // Rx FIFO 1 Start Address
#define CANFD_RXF1C_F1S_S          16U
#define CANFD_RXF1C_F1S_M          0x7F0000U       // Rx FIFO 1 Size
#define CANFD_RXF1C_F1WM_S         24U
#define CANFD_RXF1C_F1WM_M         0x7F000000U     // Rx FIFO 1 Watermark
#define CANFD_RXF1C_F1OM           0x80000000U     // FIFO 1 Operation Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the RXF1S register
//
//*************************************************************************************************
#define CANFD_RXF1S_F1FL_S         0U
#define CANFD_RXF1S_F1FL_M         0x7FU           // Rx FIFO 1 Fill Level
#define CANFD_RXF1S_F1GI_S         8U
#define CANFD_RXF1S_F1GI_M         0x3F00U         // Rx FIFO 1 Get Index
#define CANFD_RXF1S_F1PI_S         16U
#define CANFD_RXF1S_F1PI_M         0x3F0000U       // Rx FIFO 1 Put Index
#define CANFD_RXF1S_F1F            0x1000000U      // Rx FIFO 1 Full
#define CANFD_RXF1S_RF1L           0x2000000U      // Rx FIFO 1 Message Lost
#define CANFD_RXF1S_DMS_S          30U
#define CANFD_RXF1S_DMS_M          0xC0000000U     // Debug Message Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the RXF1A register
//
//*************************************************************************************************
#define CANFD_RXF1A_F1AI_S         0U
#define CANFD_RXF1A_F1AI_M         0x3FU           // Rx FIFO 1 Acknowledge Index

//*************************************************************************************************
//
// The following are defines for the bit fields in the RXESC register
//
//*************************************************************************************************
#define CANFD_RXESC_F0DS_S         0U
#define CANFD_RXESC_F0DS_M         0x7U            // Rx FIFO 0 Data Field Size
#define CANFD_RXESC_F1DS_S         4U
#define CANFD_RXESC_F1DS_M         0x70U           // Rx FIFO 1 Data Field Size
#define CANFD_RXESC_RBDS_S         8U
#define CANFD_RXESC_RBDS_M         0x700U          // Rx Buffer Data Field Size

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXBC register
//
//*************************************************************************************************
#define CANFD_TXBC_TBSA_S          2U
#define CANFD_TXBC_TBSA_M          0xFFFCU         // Tx Buffers Start Address
#define CANFD_TXBC_NDTB_S          16U
#define CANFD_TXBC_NDTB_M          0x3F0000U       // Number of Dedicated Tx Buffers
#define CANFD_TXBC_TFQS_S          24U
#define CANFD_TXBC_TFQS_M          0x3F000000U     // Tx FIFO/Queue Size
#define CANFD_TXBC_TFQM            0x40000000U     // Tx FIFO/Queue Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXFQS register
//
//*************************************************************************************************
#define CANFD_TXFQS_TFFL_S         0U
#define CANFD_TXFQS_TFFL_M         0x3FU           // Tx FIFO Free Level
#define CANFD_TXFQS_TFGI_S         8U
#define CANFD_TXFQS_TFGI_M         0x1F00U         // Tx FIFO Get Index
#define CANFD_TXFQS_TFQPI_S        16U
#define CANFD_TXFQS_TFQPI_M        0x1F0000U       // Tx FIFO/Queue Put Index
#define CANFD_TXFQS_TFQF           0x200000U       // Tx FIFO/Queue Full

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXESC register
//
//*************************************************************************************************
#define CANFD_TXESC_TBDS_S         0U
#define CANFD_TXESC_TBDS_M         0x7U           // Tx Buffer Data Field Size

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXBRP register
//
//*************************************************************************************************
#define CNAFD_TXBRP_TRP0    0x1U          // Transmission Request Pending 0
#define CNAFD_TXBRP_TRP1    0x2U          // Transmission Request Pending 1
#define CNAFD_TXBRP_TRP2    0x4U          // Transmission Request Pending 2
#define CNAFD_TXBRP_TRP3    0x8U          // Transmission Request Pending 3
#define CNAFD_TXBRP_TRP4    0x10U         // Transmission Request Pending 4
#define CNAFD_TXBRP_TRP5    0x20U         // Transmission Request Pending 5
#define CNAFD_TXBRP_TRP6    0x40U         // Transmission Request Pending 6
#define CNAFD_TXBRP_TRP7    0x80U         // Transmission Request Pending 7
#define CNAFD_TXBRP_TRP8    0x100U        // Transmission Request Pending 8
#define CNAFD_TXBRP_TRP9    0x200U        // Transmission Request Pending 9
#define CNAFD_TXBRP_TRP10   0x400U        // Transmission Request Pending 10
#define CNAFD_TXBRP_TRP11   0x800U        // Transmission Request Pending 11
#define CNAFD_TXBRP_TRP12   0x1000U       // Transmission Request Pending 12
#define CNAFD_TXBRP_TRP13   0x2000U       // Transmission Request Pending 13
#define CNAFD_TXBRP_TRP14   0x4000U       // Transmission Request Pending 14
#define CNAFD_TXBRP_TRP15   0x8000U       // Transmission Request Pending 15
#define CNAFD_TXBRP_TRP16   0x10000U      // Transmission Request Pending 16
#define CNAFD_TXBRP_TRP17   0x20000U      // Transmission Request Pending 17
#define CNAFD_TXBRP_TRP18   0x40000U      // Transmission Request Pending 18
#define CNAFD_TXBRP_TRP19   0x80000U      // Transmission Request Pending 19
#define CNAFD_TXBRP_TRP20   0x100000U     // Transmission Request Pending 20
#define CNAFD_TXBRP_TRP21   0x200000U     // Transmission Request Pending 21
#define CNAFD_TXBRP_TRP22   0x400000U     // Transmission Request Pending 22
#define CNAFD_TXBRP_TRP23   0x800000U     // Transmission Request Pending 23
#define CNAFD_TXBRP_TRP24   0x1000000U    // Transmission Request Pending 24
#define CNAFD_TXBRP_TRP25   0x2000000U    // Transmission Request Pending 25
#define CNAFD_TXBRP_TRP26   0x4000000U    // Transmission Request Pending 26
#define CNAFD_TXBRP_TRP27   0x8000000U    // Transmission Request Pending 27
#define CNAFD_TXBRP_TRP28   0x10000000U   // Transmission Request Pending 28
#define CNAFD_TXBRP_TRP29   0x20000000U   // Transmission Request Pending 29
#define CNAFD_TXBRP_TRP30   0x40000000U   // Transmission Request Pending 30
#define CNAFD_TXBRP_TRP31   0x80000000U   // Transmission Request Pending 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXBAR register
//
//*************************************************************************************************
#define CANFD_TXBAR_AR0    0x1U          // Add Request 0
#define CANFD_TXBAR_AR1    0x2U          // Add Request 1
#define CANFD_TXBAR_AR2    0x4U          // Add Request 2
#define CANFD_TXBAR_AR3    0x8U          // Add Request 3
#define CANFD_TXBAR_AR4    0x10U         // Add Request 4
#define CANFD_TXBAR_AR5    0x20U         // Add Request 5
#define CANFD_TXBAR_AR6    0x40U         // Add Request 6
#define CANFD_TXBAR_AR7    0x80U         // Add Request 7
#define CANFD_TXBAR_AR8    0x100U        // Add Request 8
#define CANFD_TXBAR_AR9    0x200U        // Add Request 9
#define CANFD_TXBAR_AR10   0x400U        // Add Request 10
#define CANFD_TXBAR_AR11   0x800U        // Add Request 11
#define CANFD_TXBAR_AR12   0x1000U       // Add Request 12
#define CANFD_TXBAR_AR13   0x2000U       // Add Request 13
#define CANFD_TXBAR_AR14   0x4000U       // Add Request 14
#define CANFD_TXBAR_AR15   0x8000U       // Add Request 15
#define CANFD_TXBAR_AR16   0x10000U      // Add Request 16
#define CANFD_TXBAR_AR17   0x20000U      // Add Request 17
#define CANFD_TXBAR_AR18   0x40000U      // Add Request 18
#define CANFD_TXBAR_AR19   0x80000U      // Add Request 19
#define CANFD_TXBAR_AR20   0x100000U     // Add Request 20
#define CANFD_TXBAR_AR21   0x200000U     // Add Request 21
#define CANFD_TXBAR_AR22   0x400000U     // Add Request 22
#define CANFD_TXBAR_AR23   0x800000U     // Add Request 23
#define CANFD_TXBAR_AR24   0x1000000U    // Add Request 24
#define CANFD_TXBAR_AR25   0x2000000U    // Add Request 25
#define CANFD_TXBAR_AR26   0x4000000U    // Add Request 26
#define CANFD_TXBAR_AR27   0x8000000U    // Add Request 27
#define CANFD_TXBAR_AR28   0x10000000U   // Add Request 28
#define CANFD_TXBAR_AR29   0x20000000U   // Add Request 29
#define CANFD_TXBAR_AR30   0x40000000U   // Add Request 30
#define CANFD_TXBAR_AR31   0x80000000U   // Add Request 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXBCR register
//
//*************************************************************************************************
#define CANFD_TXBCR_CR0    0x1U          // Cancellation Request 0
#define CANFD_TXBCR_CR1    0x2U          // Cancellation Request 1
#define CANFD_TXBCR_CR2    0x4U          // Cancellation Request 2
#define CANFD_TXBCR_CR3    0x8U          // Cancellation Request 3
#define CANFD_TXBCR_CR4    0x10U         // Cancellation Request 4
#define CANFD_TXBCR_CR5    0x20U         // Cancellation Request 5
#define CANFD_TXBCR_CR6    0x40U         // Cancellation Request 6
#define CANFD_TXBCR_CR7    0x80U         // Cancellation Request 7
#define CANFD_TXBCR_CR8    0x100U        // Cancellation Request 8
#define CANFD_TXBCR_CR9    0x200U        // Cancellation Request 9
#define CANFD_TXBCR_CR10   0x400U        // Cancellation Request 10
#define CANFD_TXBCR_CR11   0x800U        // Cancellation Request 11
#define CANFD_TXBCR_CR12   0x1000U       // Cancellation Request 12
#define CANFD_TXBCR_CR13   0x2000U       // Cancellation Request 13
#define CANFD_TXBCR_CR14   0x4000U       // Cancellation Request 14
#define CANFD_TXBCR_CR15   0x8000U       // Cancellation Request 15
#define CANFD_TXBCR_CR16   0x10000U      // Cancellation Request 16
#define CANFD_TXBCR_CR17   0x20000U      // Cancellation Request 17
#define CANFD_TXBCR_CR18   0x40000U      // Cancellation Request 18
#define CANFD_TXBCR_CR19   0x80000U      // Cancellation Request 19
#define CANFD_TXBCR_CR20   0x100000U     // Cancellation Request 20
#define CANFD_TXBCR_CR21   0x200000U     // Cancellation Request 21
#define CANFD_TXBCR_CR22   0x400000U     // Cancellation Request 22
#define CANFD_TXBCR_CR23   0x800000U     // Cancellation Request 23
#define CANFD_TXBCR_CR24   0x1000000U    // Cancellation Request 24
#define CANFD_TXBCR_CR25   0x2000000U    // Cancellation Request 25
#define CANFD_TXBCR_CR26   0x4000000U    // Cancellation Request 26
#define CANFD_TXBCR_CR27   0x8000000U    // Cancellation Request 27
#define CANFD_TXBCR_CR28   0x10000000U   // Cancellation Request 28
#define CANFD_TXBCR_CR29   0x20000000U   // Cancellation Request 29
#define CANFD_TXBCR_CR30   0x40000000U   // Cancellation Request 30
#define CANFD_TXBCR_CR31   0x80000000U   // Cancellation Request 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXBTO register
//
//*************************************************************************************************
#define CANFD_TXBTO_TO0    0x1U          // Transmission Occurred 0
#define CANFD_TXBTO_TO1    0x2U          // Transmission Occurred 1
#define CANFD_TXBTO_TO2    0x4U          // Transmission Occurred 2
#define CANFD_TXBTO_TO3    0x8U          // Transmission Occurred 3
#define CANFD_TXBTO_TO4    0x10U         // Transmission Occurred 4
#define CANFD_TXBTO_TO5    0x20U         // Transmission Occurred 5
#define CANFD_TXBTO_TO6    0x40U         // Transmission Occurred 6
#define CANFD_TXBTO_TO7    0x80U         // Transmission Occurred 7
#define CANFD_TXBTO_TO8    0x100U        // Transmission Occurred 8
#define CANFD_TXBTO_TO9    0x200U        // Transmission Occurred 9
#define CANFD_TXBTO_TO10   0x400U        // Transmission Occurred 10
#define CANFD_TXBTO_TO11   0x800U        // Transmission Occurred 11
#define CANFD_TXBTO_TO12   0x1000U       // Transmission Occurred 12
#define CANFD_TXBTO_TO13   0x2000U       // Transmission Occurred 13
#define CANFD_TXBTO_TO14   0x4000U       // Transmission Occurred 14
#define CANFD_TXBTO_TO15   0x8000U       // Transmission Occurred 15
#define CANFD_TXBTO_TO16   0x10000U      // Transmission Occurred 16
#define CANFD_TXBTO_TO17   0x20000U      // Transmission Occurred 17
#define CANFD_TXBTO_TO18   0x40000U      // Transmission Occurred 18
#define CANFD_TXBTO_TO19   0x80000U      // Transmission Occurred 19
#define CANFD_TXBTO_TO20   0x100000U     // Transmission Occurred 20
#define CANFD_TXBTO_TO21   0x200000U     // Transmission Occurred 21
#define CANFD_TXBTO_TO22   0x400000U     // Transmission Occurred 22
#define CANFD_TXBTO_TO23   0x800000U     // Transmission Occurred 23
#define CANFD_TXBTO_TO24   0x1000000U    // Transmission Occurred 24
#define CANFD_TXBTO_TO25   0x2000000U    // Transmission Occurred 25
#define CANFD_TXBTO_TO26   0x4000000U    // Transmission Occurred 26
#define CANFD_TXBTO_TO27   0x8000000U    // Transmission Occurred 27
#define CANFD_TXBTO_TO28   0x10000000U   // Transmission Occurred 28
#define CANFD_TXBTO_TO29   0x20000000U   // Transmission Occurred 29
#define CANFD_TXBTO_TO30   0x40000000U   // Transmission Occurred 30
#define CANFD_TXBTO_TO31   0x80000000U   // Transmission Occurred 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXBCF register
//
//*************************************************************************************************
#define CANFD_TXBCF_CF0    0x1U          // Cancellation Finished 0
#define CANFD_TXBCF_CF1    0x2U          // Cancellation Finished 1
#define CANFD_TXBCF_CF2    0x4U          // Cancellation Finished 2
#define CANFD_TXBCF_CF3    0x8U          // Cancellation Finished 3
#define CANFD_TXBCF_CF4    0x10U         // Cancellation Finished 4
#define CANFD_TXBCF_CF5    0x20U         // Cancellation Finished 5
#define CANFD_TXBCF_CF6    0x40U         // Cancellation Finished 6
#define CANFD_TXBCF_CF7    0x80U         // Cancellation Finished 7
#define CANFD_TXBCF_CF8    0x100U        // Cancellation Finished 8
#define CANFD_TXBCF_CF9    0x200U        // Cancellation Finished 9
#define CANFD_TXBCF_CF10   0x400U        // Cancellation Finished 10
#define CANFD_TXBCF_CF11   0x800U        // Cancellation Finished 11
#define CANFD_TXBCF_CF12   0x1000U       // Cancellation Finished 12
#define CANFD_TXBCF_CF13   0x2000U       // Cancellation Finished 13
#define CANFD_TXBCF_CF14   0x4000U       // Cancellation Finished 14
#define CANFD_TXBCF_CF15   0x8000U       // Cancellation Finished 15
#define CANFD_TXBCF_CF16   0x10000U      // Cancellation Finished 16
#define CANFD_TXBCF_CF17   0x20000U      // Cancellation Finished 17
#define CANFD_TXBCF_CF18   0x40000U      // Cancellation Finished 18
#define CANFD_TXBCF_CF19   0x80000U      // Cancellation Finished 19
#define CANFD_TXBCF_CF20   0x100000U     // Cancellation Finished 20
#define CANFD_TXBCF_CF21   0x200000U     // Cancellation Finished 21
#define CANFD_TXBCF_CF22   0x400000U     // Cancellation Finished 22
#define CANFD_TXBCF_CF23   0x800000U     // Cancellation Finished 23
#define CANFD_TXBCF_CF24   0x1000000U    // Cancellation Finished 24
#define CANFD_TXBCF_CF25   0x2000000U    // Cancellation Finished 25
#define CANFD_TXBCF_CF26   0x4000000U    // Cancellation Finished 26
#define CANFD_TXBCF_CF27   0x8000000U    // Cancellation Finished 27
#define CANFD_TXBCF_CF28   0x10000000U   // Cancellation Finished 28
#define CANFD_TXBCF_CF29   0x20000000U   // Cancellation Finished 29
#define CANFD_TXBCF_CF30   0x40000000U   // Cancellation Finished 30
#define CANFD_TXBCF_CF31   0x80000000U   // Cancellation Finished 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXBTIE register
//
//*************************************************************************************************
#define CANFD_TXBTIE_TIE0    0x1U          // Transmission Interrupt Enable 0
#define CANFD_TXBTIE_TIE1    0x2U          // Transmission Interrupt Enable 1
#define CANFD_TXBTIE_TIE2    0x4U          // Transmission Interrupt Enable 2
#define CANFD_TXBTIE_TIE3    0x8U          // Transmission Interrupt Enable 3
#define CANFD_TXBTIE_TIE4    0x10U         // Transmission Interrupt Enable 4
#define CANFD_TXBTIE_TIE5    0x20U         // Transmission Interrupt Enable 5
#define CANFD_TXBTIE_TIE6    0x40U         // Transmission Interrupt Enable 6
#define CANFD_TXBTIE_TIE7    0x80U         // Transmission Interrupt Enable 7
#define CANFD_TXBTIE_TIE8    0x100U        // Transmission Interrupt Enable 8
#define CANFD_TXBTIE_TIE9    0x200U        // Transmission Interrupt Enable 9
#define CANFD_TXBTIE_TIE10   0x400U        // Transmission Interrupt Enable 10
#define CANFD_TXBTIE_TIE11   0x800U        // Transmission Interrupt Enable 11
#define CANFD_TXBTIE_TIE12   0x1000U       // Transmission Interrupt Enable 12
#define CANFD_TXBTIE_TIE13   0x2000U       // Transmission Interrupt Enable 13
#define CANFD_TXBTIE_TIE14   0x4000U       // Transmission Interrupt Enable 14
#define CANFD_TXBTIE_TIE15   0x8000U       // Transmission Interrupt Enable 15
#define CANFD_TXBTIE_TIE16   0x10000U      // Transmission Interrupt Enable 16
#define CANFD_TXBTIE_TIE17   0x20000U      // Transmission Interrupt Enable 17
#define CANFD_TXBTIE_TIE18   0x40000U      // Transmission Interrupt Enable 18
#define CANFD_TXBTIE_TIE19   0x80000U      // Transmission Interrupt Enable 19
#define CANFD_TXBTIE_TIE20   0x100000U     // Transmission Interrupt Enable 20
#define CANFD_TXBTIE_TIE21   0x200000U     // Transmission Interrupt Enable 21
#define CANFD_TXBTIE_TIE22   0x400000U     // Transmission Interrupt Enable 22
#define CANFD_TXBTIE_TIE23   0x800000U     // Transmission Interrupt Enable 23
#define CANFD_TXBTIE_TIE24   0x1000000U    // Transmission Interrupt Enable 24
#define CANFD_TXBTIE_TIE25   0x2000000U    // Transmission Interrupt Enable 25
#define CANFD_TXBTIE_TIE26   0x4000000U    // Transmission Interrupt Enable 26
#define CANFD_TXBTIE_TIE27   0x8000000U    // Transmission Interrupt Enable 27
#define CANFD_TXBTIE_TIE28   0x10000000U   // Transmission Interrupt Enable 28
#define CANFD_TXBTIE_TIE29   0x20000000U   // Transmission Interrupt Enable 29
#define CANFD_TXBTIE_TIE30   0x40000000U   // Transmission Interrupt Enable 30
#define CANFD_TXBTIE_TIE31   0x80000000U   // Transmission Interrupt Enable 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXBCIE register
//
//*************************************************************************************************
#define CANFD_TXBCIE_CFIE0    0x1U          // Cancellation Finished Interrupt Enable 0
#define CANFD_TXBCIE_CFIE1    0x2U          // Cancellation Finished Interrupt Enable 1
#define CANFD_TXBCIE_CFIE2    0x4U          // Cancellation Finished Interrupt Enable 2
#define CANFD_TXBCIE_CFIE3    0x8U          // Cancellation Finished Interrupt Enable 3
#define CANFD_TXBCIE_CFIE4    0x10U         // Cancellation Finished Interrupt Enable 4
#define CANFD_TXBCIE_CFIE5    0x20U         // Cancellation Finished Interrupt Enable 5
#define CANFD_TXBCIE_CFIE6    0x40U         // Cancellation Finished Interrupt Enable 6
#define CANFD_TXBCIE_CFIE7    0x80U         // Cancellation Finished Interrupt Enable 7
#define CANFD_TXBCIE_CFIE8    0x100U        // Cancellation Finished Interrupt Enable 8
#define CANFD_TXBCIE_CFIE9    0x200U        // Cancellation Finished Interrupt Enable 9
#define CANFD_TXBCIE_CFIE10   0x400U        // Cancellation Finished Interrupt Enable 10
#define CANFD_TXBCIE_CFIE11   0x800U        // Cancellation Finished Interrupt Enable 11
#define CANFD_TXBCIE_CFIE12   0x1000U       // Cancellation Finished Interrupt Enable 12
#define CANFD_TXBCIE_CFIE13   0x2000U       // Cancellation Finished Interrupt Enable 13
#define CANFD_TXBCIE_CFIE14   0x4000U       // Cancellation Finished Interrupt Enable 14
#define CANFD_TXBCIE_CFIE15   0x8000U       // Cancellation Finished Interrupt Enable 15
#define CANFD_TXBCIE_CFIE16   0x10000U      // Cancellation Finished Interrupt Enable 16
#define CANFD_TXBCIE_CFIE17   0x20000U      // Cancellation Finished Interrupt Enable 17
#define CANFD_TXBCIE_CFIE18   0x40000U      // Cancellation Finished Interrupt Enable 18
#define CANFD_TXBCIE_CFIE19   0x80000U      // Cancellation Finished Interrupt Enable 19
#define CANFD_TXBCIE_CFIE20   0x100000U     // Cancellation Finished Interrupt Enable 20
#define CANFD_TXBCIE_CFIE21   0x200000U     // Cancellation Finished Interrupt Enable 21
#define CANFD_TXBCIE_CFIE22   0x400000U     // Cancellation Finished Interrupt Enable 22
#define CANFD_TXBCIE_CFIE23   0x800000U     // Cancellation Finished Interrupt Enable 23
#define CANFD_TXBCIE_CFIE24   0x1000000U    // Cancellation Finished Interrupt Enable 24
#define CANFD_TXBCIE_CFIE25   0x2000000U    // Cancellation Finished Interrupt Enable 25
#define CANFD_TXBCIE_CFIE26   0x4000000U    // Cancellation Finished Interrupt Enable 26
#define CANFD_TXBCIE_CFIE27   0x8000000U    // Cancellation Finished Interrupt Enable 27
#define CANFD_TXBCIE_CFIE28   0x10000000U   // Cancellation Finished Interrupt Enable 28
#define CANFD_TXBCIE_CFIE29   0x20000000U   // Cancellation Finished Interrupt Enable 29
#define CANFD_TXBCIE_CFIE30   0x40000000U   // Cancellation Finished Interrupt Enable 30
#define CANFD_TXBCIE_CFIE31   0x80000000U   // Cancellation Finished Interrupt Enable 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXEFC register
//
//*************************************************************************************************
#define CANFD_TXEFC_EFSA_S         2U
#define CANFD_TXEFC_EFSA_M         0xFFFCU        // Event FIFO Start Address
#define CANFD_TXEFC_EFS_S          16U
#define CANFD_TXEFC_EFS_M          0x3F0000U      // Event FIFO Size
#define CANFD_TXEFC_EFWM_S         24U
#define CANFD_TXEFC_EFWM_M         0x3F000000U    // Event FIFO Watermark

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXEFS register
//
//*************************************************************************************************
#define CANFD_TXEFS_EFFL_S         0U
#define CANFD_TXEFS_EFFL_M         0x3FU          // Event FIFO Fill Level
#define CANFD_TXEFS_EFGI_S         8U
#define CANFD_TXEFS_EFGI_M         0x1F00U        // Event FIFO Get Index
#define CANFD_TXEFS_EFPI_S         16U
#define CANFD_TXEFS_EFPI_M         0x1F0000U      // Event FIFO Put Index
#define CANFD_TXEFS_EFF            0x1000000U     // Event FIFO Full
#define CANFD_TXEFS_TEFL           0x2000000U     // Tx Event FIFO Element Lost

//*************************************************************************************************
//
// The following are defines for the bit fields in the TXEFA register
//
//*************************************************************************************************
#define CANFD_TXEFA_EFAI_S         0U
#define CANFD_TXEFA_EFAI_M         0x1FU          // Event FIFO Acknowledge Index


//*************************************************************************************************
//
// The following are defines for the bit fields in the ERM_CTRL register
//
//*************************************************************************************************
#define CANFD_ERM_CTRL_ECC_EN_S               0U
#define CANFD_ERM_CTRL_ECC_EN_M               0x0001U       // ECC check enable

#define CANFD_ERM_CTRL_BEC_INT_EN_S           1U
#define CANFD_ERM_CTRL_BEC_INT_EN_M           0x0002U       // Single-bit error corrected interrupt enable

#define CANFD_ERM_CTRL_BEU_INT_EN_S           2U
#define CANFD_ERM_CTRL_BEU_INT_EN_M           0x0004U       // Multi-bit error uncorrectable interrupt enable

#define CANFD_ERM_CTRL_WAKE_INT_EN_S          3U
#define CANFD_ERM_CTRL_WAKE_INT_EN_M          0x0008U       // CANFD wake-up interrupt enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERM_STS register
//
//*************************************************************************************************
#define CANFD_ERM_STS_BEC_FLAG_S              0U
#define CANFD_ERM_STS_BEC_FLAG_M              0x0001U       // Single-bit error detected and corrected

#define CANFD_ERM_STS_BEU_FLAG_S              1U
#define CANFD_ERM_STS_BEU_FLAG_M              0x0002U       // Multiple-bit error detected and uncorrectable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERM_ECC_ADDR_LOG register
//
//*************************************************************************************************
#define CANFD_ERM_ECC_ADDR_LOG_ERR_ADDR_S     0U
#define CANFD_ERM_ECC_ADDR_LOG_ERR_ADDR_M     0x03FFU       // Error address

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERM_ECC_DATA_LOG register
//
//*************************************************************************************************
#define CANFD_ERM_ECC_DATA_LOG_ERR_DATA_S     0U
#define CANFD_ERM_ECC_DATA_LOG_ERR_DATA_M     0xFFFFFFFFU   // Error data

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERM_RAM_INIT register
//
//*************************************************************************************************
#define CANFD_ERM_RAM_INIT_RAM_INIT_EN_S      0U
#define CANFD_ERM_RAM_INIT_RAM_INIT_EN_M      0x00000001U  // RAM initialization request

#define CANFD_ERM_RAM_INIT_RAM_INIT_DONE_S    1U
#define CANFD_ERM_RAM_INIT_RAM_INIT_DONE_M    0x00000002U  //The flag of RAM initialization flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERM_EXTC_CTRL register
//
//*************************************************************************************************
#define CANFD_ERM_EXTC_CTRL_ETCP_S             0U
#define CANFD_ERM_EXTC_CTRL_ETCP_M             0x000003FFU  //External Timestamp Prescaler Value

#define CANFD_ERM_EXTC_CTRL_ETCE_S             31U
#define CANFD_ERM_EXTC_CTRL_ETCE_M             0x80000000U  //External Timestamp Counter Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERM_EXTC_VAL register
//
//*************************************************************************************************
#define CANFD_ERM_EXTC_VAL_ETSC_S              0U
#define CANFD_ERM_EXTC_VAL_ETSC_M              0x0000FFFFU  //External Timestamp Counter


#endif
