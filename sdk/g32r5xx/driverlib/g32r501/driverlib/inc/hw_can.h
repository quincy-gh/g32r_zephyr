//###########################################################################
//
// FILE:    hw_can.h
//
// TITLE:   Definitions for the CAN registers.
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
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
// 1. Some comments, macro definitions (register and bit-field naming) were changed.
//
//###########################################################################

#ifndef HW_CAN_H
#define HW_CAN_H

//*************************************************************************************************
//
// The following are defines for the CAN register offsets
//
//*************************************************************************************************
#define CAN_O_CTRL              0x0U     // CAN Control Register
#define CAN_O_EFLG              0x4U     // Error and Status Register
#define CAN_O_ECNT              0x8U     // Error Counter Register
#define CAN_O_BTIM              0xCU     // Bit Timing Register
#define CAN_O_INT               0x10U    // Interrupt Register
#define CAN_O_TEST              0x14U    // Test Register
#define CAN_O_PE                0x1CU    // CAN Parity Error Code Register
#define CAN_O_RAMINIT           0x40U    // CAN RAM Initialization Register
#define CAN_O_GLBINTEN          0x50U    // CAN Global Interrupt Enable Register
#define CAN_O_GLBINTFLG         0x54U    // CAN Global Interrupt Flag Register
#define CAN_O_GLBINTCLR         0x58U    // CAN Global Interrupt Clear Register
#define CAN_O_ABOTR             0x80U    // Auto-Bus-On Time Register
#define CAN_O_TXREQFLG          0x84U    // CAN Transmission Request Register
#define CAN_O_TXREQ             0x88U    // CAN Transmission Request 2_1 Register
#define CAN_O_NDATAFLG          0x98U    // CAN New Data Register
#define CAN_O_NDATA             0x9CU    // CAN New Data 2_1 Register
#define CAN_O_IPENDFLG          0xACU    // CAN Interrupt Pending Register
#define CAN_O_IPEND             0xB0U    // CAN Interrupt Pending 2_1 Register
#define CAN_O_MVALFLG           0xC0U    // CAN Message Valid Register
#define CAN_O_MVAL              0xC4U    // CAN Message Valid 2_1 Register
#define CAN_O_INTMAIL           0xD8U    // CAN Interrupt Multiplexer 2_1 Register
#define CAN_O_IF1COM            0x100U   // IF1 Command Register
#define CAN_O_IF1MASK           0x104U   // IF1 Mask Register
#define CAN_O_IF1ARB            0x108U   // IF1 Arbitration Register
#define CAN_O_IF1MCTRL          0x10CU   // IF1 Message Control Register
#define CAN_O_IF1DATAA          0x110U   // IF1 Data A Register
#define CAN_O_IF1DATAB          0x114U   // IF1 Data B Register
#define CAN_O_IF2COM            0x120U   // IF2 Command Register
#define CAN_O_IF2MASK           0x124U   // IF2 Mask Register
#define CAN_O_IF2ARB            0x128U   // IF2 Arbitration Register
#define CAN_O_IF2MCTRL          0x12CU   // IF2 Message Control Register
#define CAN_O_IF2DATAA          0x130U   // IF2 Data A Register
#define CAN_O_IF2DATAB          0x134U   // IF2 Data B Register
#define CAN_O_IF3OBS            0x140U   // IF3 Observation Register
#define CAN_O_IF3MASK           0x144U   // IF3 Mask Register
#define CAN_O_IF3ARB            0x148U   // IF3 Arbitration Register
#define CAN_O_IF3MCTRL          0x14CU   // IF3 Message Control Register
#define CAN_O_IF3DATAA          0x150U   // IF3 Data A Register
#define CAN_O_IF3DATAB          0x154U   // IF3 Data B Register
#define CAN_O_IF3UDEN           0x160U   // IF3 Update Enable Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_CTRL register
//
//*************************************************************************************************
#define CAN_CTRL_INIT           0x1U        // Initialization Mode
#define CAN_CTRL_IEN0           0x2U        // Interrupt line 0 Enable
#define CAN_CTRL_SCHIEN         0x4U        // Status Change Interrupt Enable
#define CAN_CTRL_ERRIEN         0x8U        // Error Interrupt Enable
#define CAN_CTRL_DISARETX       0x20U       // Disable Automatic ReTransmit
#define CAN_CTRL_CFGWACCEN      0x40U       // Configure write access Enable
#define CAN_CTRL_TESTEN         0x80U       // Test Mode Enable
#define CAN_CTRL_IDBGSEN        0x100U      // Interrupt Debug Support Enable
#define CAN_CTRL_ABOEN          0x200U      // Auto-Bus-On Enable
#define CAN_CTRL_PARITYEN_S     10U
#define CAN_CTRL_PARITYEN_M     0x3C00U     // Parity Enable
#define CAN_CTRL_SWRSTEN        0x8000U     // Software Reset Enable
#define CAN_CTRL_DBGFLG         0x10000U    // Debug Mode Flag
#define CAN_CTRL_IEN1           0x20000U    // Interrupt line 1 Enable
#define CAN_CTRL_IFDEN1         0x40000U    // IF1 DMA request line Enable
#define CAN_CTRL_IFDEN2         0x80000U    // IF2 DMA request line Enable
#define CAN_CTRL_IFDEN3         0x100000U   // IF3 DMA request line Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_EFLG register
//
//*************************************************************************************************
#define CAN_EFLG_LEC_S     0U
#define CAN_EFLG_LEC_M     0x7U     // Last Error Code
#define CAN_EFLG_TXCFLG    0x8U     // Transmit completion flag
#define CAN_EFLG_RXCFLG    0x10U    // Reception completion flag
#define CAN_EFLG_EPFLG     0x20U    // Error Passive Flag
#define CAN_EFLG_EWFLG     0x40U    // Error Warning Flag
#define CAN_EFLG_BUSOFLG   0x80U    // Bus-off Flag
#define CAN_EFLG_PEFLG     0x100U   // Parity Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_ECNT register
//
//*************************************************************************************************
#define CAN_ECNT_TXECNT_S   0U
#define CAN_ECNT_TXECNT_M   0xFFU     // Transmit Error Counter
#define CAN_ECNT_RXECNT_S   8U
#define CAN_ECNT_RXECNT_M   0x7F00U   // Receive Error Counter
#define CAN_ECNT_RXEP       0x8000U   // Receive Error Passive

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_BTIM register
//
//*************************************************************************************************
#define CAN_BTIM_BRPSC_S     0U
#define CAN_BTIM_BRPSC_M     0x3FU      // Baud Rate Prescaler
#define CAN_BTIM_SJWP_S      6U
#define CAN_BTIM_SJWP_M      0xC0U      // Synchronization Jump Width
#define CAN_BTIM_TSSPVP1_S   8U
#define CAN_BTIM_TSSPVP1_M   0xF00U     // Time segment 1
#define CAN_BTIM_TSSPVP2_S   12U
#define CAN_BTIM_TSSPVP2_M   0x7000U    // Time segment 2
#define CAN_BTIM_BRPSCEXT_S  16U
#define CAN_BTIM_BRPSCEXT_M  0xF0000U   // Baud Rate Prescaler Extension

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_INT register
//
//*************************************************************************************************
#define CAN_INT_INT0_S   0U
#define CAN_INT_INT0_M   0xFFFFU     // Interrupt 0
#define CAN_INT_INT1_S   16U
#define CAN_INT_INT1_M   0xFF0000U   // Interrupt 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_TEST register
//
//*************************************************************************************************
#define CAN_TEST_MUTEEN       0x8U     // Mute Mode Enable
#define CAN_TEST_LBEN         0x10U    // Loop Back Mode Enable
#define CAN_TEST_TXCTRL_S     5U
#define CAN_TEST_TXCTRL_M     0x60U    // TX pin Control
#define CAN_TEST_RXMON        0x80U    // RX pin Monitors
#define CAN_TEST_EXTLBEN      0x100U   // External Loop Back Mode Enable
#define CAN_TEST_RDAEN        0x200U   // RAM Direct Access Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_PE register
//
//*************************************************************************************************
#define CAN_PE_MAILNUM_S    0U
#define CAN_PE_MAILNUM_M    0xFFU    // parity error Mailbox number
#define CAN_PE_WORDNUM_S    8U
#define CAN_PE_WORDNUM_M    0x700U   // parity error Word number

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_RAMINIT register
//
//*************************************************************************************************
#define CAN_RAMINIT_KEY0            0x1U    // KEY0
#define CAN_RAMINIT_KEY1            0x2U    // KEY1
#define CAN_RAMINIT_KEY2            0x4U    // KEY2
#define CAN_RAMINIT_KEY3            0x8U    // KEY3
#define CAN_RAMINIT_RAMINIT         0x10U   // Initiate CAN Mailbox RAM initialization
#define CAN_RAMINIT_RAMINITCFLG     0x20U   // CAN Mailbox RAM initialization completion flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_GLBINTEN register
//
//*************************************************************************************************
#define CAN_GLBINTEN_GLBINT0EN   0x1U   // CANINT0 Global Interrupt Flag
#define CAN_GLBINTEN_GLBINT1EN   0x2U   // CANINT1 Global Interrupt Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_GLBINTFLG register
//
//*************************************************************************************************
#define CAN_GLBINTFLG_GLBINT0FLG   0x1U   // CANINT0 Global Interrupt Flag
#define CAN_GLBINTFLG_GLBINT1FLG   0x2U   // CANINT1 Global Interrupt Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_GLBINTCLR register
//
//*************************************************************************************************
#define CAN_GLBINTCLR_GLBINT0CLR   0x1U   // CANINT0 Global Interrupt Flag Clear
#define CAN_GLBINTCLR_GLBINT1CLR   0x2U   // CANINT1 Global Interrupt Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_TXREQFLG register
//
//*************************************************************************************************
#define CAN_TXREQFLG_TXREQ1FLG_S   0U
#define CAN_TXREQFLG_TXREQ1FLG_M   0x3U   // Transmit Request Register 1 flag
#define CAN_TXREQFLG_TXREQ2FLG_S   2U
#define CAN_TXREQFLG_TXREQ2FLG_M   0xCU   // Transmit Request Register 2 flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_NDATAFLG register
//
//*************************************************************************************************
#define CAN_NDATAFLG_NDATA1FLG_S   0U
#define CAN_NDATAFLG_NDATA1FLG_M   0x3U   // New Data Register 1 flag
#define CAN_NDATAFLG_NDATA2FLG_S   2U
#define CAN_NDATAFLG_NDATA2FLG_M   0xCU   // New Data Register 2 flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IPENDFLG register
//
//*************************************************************************************************
#define CAN_IPENDFLG_IPEND1FLG_S   0U
#define CAN_IPENDFLG_IPEND1FLG_M   0x3U   // Interrupt Pending Register 1 flag
#define CAN_IPENDFLG_IPEND2FLG_S   2U
#define CAN_IPENDFLG_IPEND2FLG_M   0xCU   // Interrupt Pending Register 2 flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_MVALFLG register
//
//*************************************************************************************************
#define CAN_MVALFLG_MVAL1FLG_S   0U
#define CAN_MVALFLG_MVAL1FLG_M   0x3U   // Message Valid Register 1 flag
#define CAN_MVALFLG_MVAL2FLG_S   2U
#define CAN_MVALFLG_MVAL2FLG_M   0xCU   // Message Valid Register 2 flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1COM register
//
//*************************************************************************************************
#define CAN_IF1COM_VALMNUM_S      0U
#define CAN_IF1COM_VALMNUM_M      0xFFU       // Valid Mailbox Number
#define CAN_IF1COM_REQDMAIF1      0x4000U     // Request DMA after IF1 update
#define CAN_IF1COM_BUSYFLG        0x8000U     // Busy Flag
#define CAN_IF1COM_DATABYTEB      0x10000U    // Access Data Bytes 4-7
#define CAN_IF1COM_DATABYTEA      0x20000U    // Access Data Bytes 0-3
#define CAN_IF1COM_TXREQCFG       0x40000U    // Transmit Request/ New Data Configure
#define CAN_IF1COM_IPENDCLR       0x80000U    // Interrupt Pending Clear
#define CAN_IF1COM_ACCCTRL        0x100000U   // Access control
#define CAN_IF1COM_ACCARB         0x200000U   // Access Arbitration
#define CAN_IF1COM_ACCMASK        0x400000U   // Access Mask
#define CAN_IF1COM_RWCFG          0x800000U   // Read/Write function Configure

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1MASK register
//
//*************************************************************************************************
#define CAN_IF1MASK_IDMASK_S    0U
#define CAN_IF1MASK_IDMASK_M    0x1FFFFFFFU   // Identifier Mask
#define CAN_IF1MASK_DIRMASK     0x40000000U   // Message Direction Mask
#define CAN_IF1MASK_EXTMASK     0x80000000U   // Extended Identifier Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1ARB register
//
//*************************************************************************************************
#define CAN_IF1ARB_MIDCFG_S     0U
#define CAN_IF1ARB_MIDCFG_M     0x1FFFFFFFU   // Message Identifier Configure
#define CAN_IF1ARB_MDIRCFG      0x20000000U   // Message Direction Configure
#define CAN_IF1ARB_EXTIDCFG     0x40000000U   // Extended Identifier Configure
#define CAN_IF1ARB_MAILEN       0x80000000U   // mailbox enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1MCTRL register
//
//*************************************************************************************************
#define CAN_IF1MCTRL_DLCCFG_S    0U
#define CAN_IF1MCTRL_DLCCFG_M    0xFU      // Data Length Code Configure
#define CAN_IF1MCTRL_EOBEN       0x80U     // End of Block Enable
#define CAN_IF1MCTRL_TXREQEN     0x100U    // Transmit Request Enable
#define CAN_IF1MCTRL_REMEN       0x200U    // Remote Enable
#define CAN_IF1MCTRL_RXIEN       0x400U    // Receive Interrupt Enable
#define CAN_IF1MCTRL_TXIEN       0x800U    // Transmit Interrupt Enable
#define CAN_IF1MCTRL_MASKEN      0x1000U   // Mask Enable
#define CAN_IF1MCTRL_IPEND       0x2000U   // Interrupt Pending
#define CAN_IF1MCTRL_MLOST       0x4000U   // Message Lost
#define CAN_IF1MCTRL_NDATA       0x8000U   // New Data

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1DATAA register
//
//*************************************************************************************************
#define CAN_IF1DATAA_DATA0_S   0U
#define CAN_IF1DATAA_DATA0_M   0xFFU         // Data Byte 0
#define CAN_IF1DATAA_DATA1_S   8U
#define CAN_IF1DATAA_DATA1_M   0xFF00U       // Data Byte 1
#define CAN_IF1DATAA_DATA2_S   16U
#define CAN_IF1DATAA_DATA2_M   0xFF0000U     // Data Byte 2
#define CAN_IF1DATAA_DATA3_S   24U
#define CAN_IF1DATAA_DATA3_M   0xFF000000U   // Data Byte 3

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF1DATAB register
//
//*************************************************************************************************
#define CAN_IF1DATAB_DATA4_S   0U
#define CAN_IF1DATAB_DATA4_M   0xFFU         // Data Byte 4
#define CAN_IF1DATAB_DATA5_S   8U
#define CAN_IF1DATAB_DATA5_M   0xFF00U       // Data Byte 5
#define CAN_IF1DATAB_DATA6_S   16U
#define CAN_IF1DATAB_DATA6_M   0xFF0000U     // Data Byte 6
#define CAN_IF1DATAB_DATA7_S   24U
#define CAN_IF1DATAB_DATA7_M   0xFF000000U   // Data Byte 7

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2COM register
//
//*************************************************************************************************
#define CAN_IF2COM_VALMNUM_S      0U
#define CAN_IF2COM_VALMNUM_M      0xFFU       // Valid Mailbox Number
#define CAN_IF2COM_REQDMAIF2      0x4000U     // Request DMA after IF2 update
#define CAN_IF2COM_BUSYFLG        0x8000U     // Busy Flag
#define CAN_IF2COM_DATABYTEB      0x10000U    // Access Data Bytes 4-7
#define CAN_IF2COM_DATABYTEA      0x20000U    // Access Data Bytes 0-3
#define CAN_IF2COM_TXREQCFG       0x40000U    // Transmit Request/ New Data Configure
#define CAN_IF2COM_IPENDCLR       0x80000U    // Interrupt Pending Clear
#define CAN_IF2COM_ACCCTRL        0x100000U   // Access control
#define CAN_IF2COM_ACCARB         0x200000U   // Access Arbitration
#define CAN_IF2COM_ACCMASK        0x400000U   // Access Mask
#define CAN_IF2COM_RWCFG          0x800000U   // Read/Write function Configure

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2MASK register
//
//*************************************************************************************************
#define CAN_IF2MASK_IDMASK_S   0U
#define CAN_IF2MASK_IDMASK_M   0x1FFFFFFFU   // Identifier Mask
#define CAN_IF2MASK_DIRMASK    0x40000000U   // Message Direction Mask
#define CAN_IF2MASK_EXTMASK    0x80000000U   // Extended Identifier Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2ARB register
//
//*************************************************************************************************
#define CAN_IF2ARB_MIDCFG_S     0U
#define CAN_IF2ARB_MIDCFG_M     0x1FFFFFFFU   // Message Identifier Configure
#define CAN_IF2ARB_MDIRCFG      0x20000000U   // Message Direction Configure
#define CAN_IF2ARB_EXTIDCFG     0x40000000U   // Extended Identifier Configure
#define CAN_IF2ARB_MAILEN       0x80000000U   // mailbox enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2MCTRL register
//
//*************************************************************************************************
#define CAN_IF2MCTRL_DLCCFG_S    0U
#define CAN_IF2MCTRL_DLCCFG_M    0xFU      // Data Length Code Configure
#define CAN_IF2MCTRL_EOBEN       0x80U     // End of Block Enable
#define CAN_IF2MCTRL_TXREQEN     0x100U    // Transmit Request Enable
#define CAN_IF2MCTRL_REMEN       0x200U    // Remote Enable
#define CAN_IF2MCTRL_RXIEN       0x400U    // Receive Interrupt Enable
#define CAN_IF2MCTRL_TXIEN       0x800U    // Transmit Interrupt Enable
#define CAN_IF2MCTRL_MASKEN      0x1000U   // Mask Enable
#define CAN_IF2MCTRL_IPEND       0x2000U   // Interrupt Pending
#define CAN_IF2MCTRL_MLOST       0x4000U   // Message Lost
#define CAN_IF2MCTRL_NDATA       0x8000U   // New Data

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2DATAA register
//
//*************************************************************************************************
#define CAN_IF2DATAA_DATA0_S   0U
#define CAN_IF2DATAA_DATA0_M   0xFFU         // Data Byte 0
#define CAN_IF2DATAA_DATA1_S   8U
#define CAN_IF2DATAA_DATA1_M   0xFF00U       // Data Byte 1
#define CAN_IF2DATAA_DATA2_S   16U
#define CAN_IF2DATAA_DATA2_M   0xFF0000U     // Data Byte 2
#define CAN_IF2DATAA_DATA3_S   24U
#define CAN_IF2DATAA_DATA3_M   0xFF000000U   // Data Byte 3

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF2DATAB register
//
//*************************************************************************************************
#define CAN_IF2DATAB_DATA4_S   0U
#define CAN_IF2DATAB_DATA4_M   0xFFU         // Data Byte 4
#define CAN_IF2DATAB_DATA5_S   8U
#define CAN_IF2DATAB_DATA5_M   0xFF00U       // Data Byte 5
#define CAN_IF2DATAB_DATA6_S   16U
#define CAN_IF2DATAB_DATA6_M   0xFF0000U     // Data Byte 6
#define CAN_IF2DATAB_DATA7_S   24U
#define CAN_IF2DATAB_DATA7_M   0xFF000000U   // Data Byte 7

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3OBS register
//
//*************************************************************************************************
#define CAN_IF3OBS_MASKRD       0x1U      // Mask data read
#define CAN_IF3OBS_ARBRD        0x2U      // Arbitration data read
#define CAN_IF3OBS_CTRLRD       0x4U      // Control bits read
#define CAN_IF3OBS_DATAARD      0x8U      // Data A read
#define CAN_IF3OBS_DATABRD      0x10U     // Data B read
#define CAN_IF3OBS_MASKRDACC    0x100U    // Mask data read access status
#define CAN_IF3OBS_ARBRDACC     0x200U    // Arbitration data read access status
#define CAN_IF3OBS_CTRLRDACC    0x400U    // Control bits read access status
#define CAN_IF3OBS_DATAARDACC   0x800U    // Data A read access status
#define CAN_IF3OBS_DATABRDACC   0x1000U   // Data B read access status
#define CAN_IF3OBS_UDDATA       0x8000U   // Update Data

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3MASK register
//
//*************************************************************************************************
#define CAN_IF3MASK_IDMASK_S   0U
#define CAN_IF3MASK_IDMASK_M   0x1FFFFFFFU   // Identifier Mask
#define CAN_IF3MASK_DIRMASK    0x40000000U   // Message Direction Mask
#define CAN_IF3MASK_EXTMASK    0x80000000U   // Extended Identifier Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3ARB register
//
//*************************************************************************************************
#define CAN_IF3ARB_MIDCFG_S     0U
#define CAN_IF3ARB_MIDCFG_M     0x1FFFFFFFU   // Message Identifier Configure
#define CAN_IF3ARB_MDIRCFG      0x20000000U   // Message Direction Configure
#define CAN_IF3ARB_EXTIDCFG     0x40000000U   // Extended Identifier Configure
#define CAN_IF3ARB_MAILEN       0x80000000U   // mailbox enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3MCTRL register
//
//*************************************************************************************************
#define CAN_IF3MCTRL_DLCCFG_S    0U
#define CAN_IF3MCTRL_DLCCFG_M    0xFU      // Data Length Code Configure
#define CAN_IF3MCTRL_EOBEN       0x80U     // End of Block Enable
#define CAN_IF3MCTRL_TXREQEN     0x100U    // Transmit Request Enable
#define CAN_IF3MCTRL_REMEN       0x200U    // Remote Enable
#define CAN_IF3MCTRL_RXIEN       0x400U    // Receive Interrupt Enable
#define CAN_IF3MCTRL_TXIEN       0x800U    // Transmit Interrupt Enable
#define CAN_IF3MCTRL_MASKEN      0x1000U   // Mask Enable
#define CAN_IF3MCTRL_IPEND       0x2000U   // Interrupt Pending
#define CAN_IF3MCTRL_MLOST       0x4000U   // Message Lost
#define CAN_IF3MCTRL_NDATA       0x8000U   // New Data

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3DATAA register
//
//*************************************************************************************************
#define CAN_IF3DATAA_DATA0_S   0U
#define CAN_IF3DATAA_DATA0_M   0xFFU         // Data Byte 0
#define CAN_IF3DATAA_DATA1_S   8U
#define CAN_IF3DATAA_DATA1_M   0xFF00U       // Data Byte 1
#define CAN_IF3DATAA_DATA2_S   16U
#define CAN_IF3DATAA_DATA2_M   0xFF0000U     // Data Byte 2
#define CAN_IF3DATAA_DATA3_S   24U
#define CAN_IF3DATAA_DATA3_M   0xFF000000U   // Data Byte 3

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAN_IF3DATAB register
//
//*************************************************************************************************
#define CAN_IF3DATAB_DATA4_S   0U
#define CAN_IF3DATAB_DATA4_M   0xFFU         // Data Byte 4
#define CAN_IF3DATAB_DATA5_S   8U
#define CAN_IF3DATAB_DATA5_M   0xFF00U       // Data Byte 5
#define CAN_IF3DATAB_DATA6_S   16U
#define CAN_IF3DATAB_DATA6_M   0xFF0000U     // Data Byte 6
#define CAN_IF3DATAB_DATA7_S   24U
#define CAN_IF3DATAB_DATA7_M   0xFF000000U   // Data Byte 7



#endif
