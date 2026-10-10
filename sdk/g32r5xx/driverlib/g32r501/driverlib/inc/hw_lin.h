//###########################################################################
//
// FILE:    hw_lin.h
//
// TITLE:   Definitions for the LIN registers.
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

#ifndef HW_LIN_H
#define HW_LIN_H

//*************************************************************************************************
//
// The following are defines for the LIN register offsets
//
//*************************************************************************************************
#define LIN_O_LINGCTRL0          (0x0)    // Global Control Register 0
#define LIN_O_LINGCTRL1          (0x4)    // Global Control Register 1
#define LIN_O_LINGCTRL2          (0x8)    // Global Control Register 2
#define LIN_O_LINIEN             (0xC)    // Interrupt Enable Register
#define LIN_O_LINICLR            (0x10)   // Interrupt Disable Register
#define LIN_O_LINILEN            (0x14)   // Set Interrupt Level Register
#define LIN_O_LINILCLR           (0x18)   // Clear Interrupt Level Register
#define LIN_O_LINFLG             (0x1C)   // Flag Register
#define LIN_O_LINIVO0            (0x20)   // Interrupt Vector Offset Register 0
#define LIN_O_LINIVO1            (0x24)   // Interrupt Vector Offset Register 1
#define LIN_O_LINLCFG            (0x28)   // Length Control Register
#define LIN_O_LINBR              (0x2C)   // Baud Rate Selection Register
#define LIN_O_LINRXED            (0x30)   // Emulation buffer Register
#define LIN_O_LINRXD             (0x34)   // Receiver data buffer Register
#define LIN_O_LINTXD             (0x38)   // Transmit data buffer Register
#define LIN_O_LINPCTRL0          (0x3C)   // Pin control Register 0
#define LIN_O_LINPCTRL2          (0x44)   // Pin control Register 2
#define LIN_O_LINCOMP            (0x60)   // Compare register
#define LIN_O_LINRXB0            (0x64)   // Receive data register 0
#define LIN_O_LINRXB1            (0x68)   // Receive data register 1
#define LIN_O_LINIDMASK          (0x6C)   // Acceptance mask register
#define LIN_O_LINID              (0x70)   // LIN ID Register
#define LIN_O_LINTXB0            (0x74)   // Transmit Data Register 0
#define LIN_O_LINTXB1            (0x78)   // Transmit Data Register 1
#define LIN_O_LINMBRPSC          (0x7C)   // Maximum Baud Rate Selection Register
#define LIN_O_LINEET             (0x90)   // IODFT for LIN
#define LIN_O_LINGIEN            (0xE0)   // LIN Global Interrupt Enable Register
#define LIN_O_LINGIFLG           (0xE4)   // LIN Global Interrupt Flag Register
#define LIN_O_LINGICLR           (0xE8)   // LIN Global Interrupt Clear Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the LINGCTRL0 register
//
//*************************************************************************************************
#define LIN_LINGCTRL0_RST   0x1U   // UART/LIN reset

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINGCTRL1 register
//
//*************************************************************************************************
#define LIN_LINGCTRL1_COMCFG       0x1U         // UART/LIN communication mode Configure
#define LIN_LINGCTRL1_TIM          0x2U         // UART timing mode
#define LIN_LINGCTRL1_PARITYEN     0x4U         // UART/LIN Parity Enable
#define LIN_LINGCTRL1_PARITY       0x8U         // UART Odd/Even Parity Select
#define LIN_LINGCTRL1_STOPCFG      0x10U        // UART STOP Bit Configure
#define LIN_LINGCTRL1_CLK_MSCFG    0x20U        // UART internal clock enable/LIN Master Slave configure
#define LIN_LINGCTRL1_LINEN        0x40U        // LIN mode Enable
#define LIN_LINGCTRL1_RDY          0x80U        // UART/LIN Ready
#define LIN_LINGCTRL1_SLEEPEN      0x100U       // UART Sleep mode enable
#define LIN_LINGCTRL1_ABEN         0x200U       // LIN Automatic baudrate adjustment enable
#define LIN_LINGCTRL1_MBUFEN       0x400U       // UART/LIN multi-buffer mode enable
#define LIN_LINGCTRL1_CHASUMCFG    0x800U       // LIN Checksum Configure
#define LIN_LINGCTRL1_HGENCTRL     0x1000U      // LIN HGEN control
#define LIN_LINGCTRL1_STOEXTCOM    0x2000U      // Stop LIN extended frame communication
#define LIN_LINGCTRL1_LBEN         0x10000U     // UART/LIN Loopback Mode Enable
#define LIN_LINGCTRL1_CONTSUS      0x20000U     // UART/LIN Continue work on suspend
#define LIN_LINGCTRL1_RXEN         0x1000000U   // UART/LIN Receive enable
#define LIN_LINGCTRL1_TXEN         0x2000000U   // UART/LIN Transmit enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINGCTRL2 register
//
//*************************************************************************************************
#define LIN_LINGCTRL2_LPREQ        0x1U       // low-power mode Request
#define LIN_LINGCTRL2_WUPGEN       0x100U     // Generate wakeup signal
#define LIN_LINGCTRL2_TXCHAEN      0x10000U   // Transmit Checksum Byte Enable
#define LIN_LINGCTRL2_COMPCHASUM   0x20000U   // Compare Checksum

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINIEN register
//
//*************************************************************************************************
#define LIN_LINIEN_BRKDETIEN     0x1U          // break detect interrupt Enable
#define LIN_LINIEN_WUPIEN        0x2U          // wake up interrupt Enable
#define LIN_LINIEN_TOIEN         0x10U         // timeout interrupt Enable
#define LIN_LINIEN_TOWUPSIEN     0x40U         // Timeout After Wakeup Signal interrupt Enable
#define LIN_LINIEN_TO3WUPSIEN    0x80U         // Timeout After 3 Wakeup Signal interrupt Enable
#define LIN_LINIEN_TXIEN         0x100U        // Transmitter interrupt Enable
#define LIN_LINIEN_RXIEN         0x200U        // Receiver interrupt Enable
#define LIN_LINIEN_IDIEN         0x2000U       // Identification interrupt Enable
#define LIN_LINIEN_TXDREQEN      0x10000U      // transmit DMA request enable
#define LIN_LINIEN_RXDREQEN      0x20000U      // Receive DMA request enable
#define LIN_LINIEN_ADRXDREQEN    0x40000U      // Address & Data frames Receive DMA request enable
#define LIN_LINIEN_PIEN          0x1000000U    // parity interrupt Enable
#define LIN_LINIEN_OREIEN        0x2000000U    // overrun error interrupt Enable
#define LIN_LINIEN_FEIEN         0x4000000U    // framing error interrupt Enable
#define LIN_LINIEN_NREIEN        0x8000000U    // no response error interrupt Enable
#define LIN_LINIEN_ISFEIEN       0x10000000U   // inconsistent sync field error interrupt Enable
#define LIN_LINIEN_CSEIEN        0x20000000U   // checksum-error Interrupt Enable
#define LIN_LINIEN_PBEIEN        0x40000000U   // physical bus error interrupt Enable
#define LIN_LINIEN_BEIEN         0x80000000U   // bit error interrupt Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINICLR register
//
//*************************************************************************************************
#define LIN_LINICLR_BRKDETICLR    0x1U          // Break detect interrupt Clear
#define LIN_LINICLR_WUPICLR       0x2U          // Wake up interrupt Clear
#define LIN_LINICLR_TOICLR        0x10U         // Timeout interrupt Clear
#define LIN_LINICLR_TOWUPSICLR    0x40U         // Timeout After Wakeup Signal interrupt Clear
#define LIN_LINICLR_TO3WUPSICLR   0x80U         // Timeout After 3 Wakeup Signal interrupt Clear
#define LIN_LINICLR_TXICLR        0x100U        // Transmitter interrupt Clear
#define LIN_LINICLR_RXICLR        0x200U        // Receiver interrupt Clear
#define LIN_LINICLR_IDICLR        0x2000U       // Identification interrupt Clear
#define LIN_LINICLR_TXDREQCLR     0x10000U      // transmit DMA request Clear
#define LIN_LINICLR_RXDREQCLR     0x20000U      // Receive DMA request Clear
#define LIN_LINICLR_PICLR         0x1000000U    // parity interrupt Clear
#define LIN_LINICLR_OREICLR       0x2000000U    // Overrun error interrupt Clear
#define LIN_LINICLR_FEICLR        0x4000000U    // Framing error interrupt Clear
#define LIN_LINICLR_NREICLR       0x8000000U    // No response error interrupt Clear
#define LIN_LINICLR_ISFEICLR      0x10000000U   // Inconsistent sync field error interrupt Clear
#define LIN_LINICLR_CSEICLR       0x20000000U   // Checksum-error Interrupt Clear
#define LIN_LINICLR_PBEICLR       0x40000000U   // Physical bus error interrupt Clear
#define LIN_LINICLR_BEICLR        0x80000000U   // Bit error interrupt Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINILEN register
//
//*************************************************************************************************
#define LIN_LINILEN_BRKDETILEN    0x1U           // Break detect interrupt level 1 Enable
#define LIN_LINILEN_WUPILEN       0x2U           // Wake up interrupt level 1 Enable
#define LIN_LINILEN_TOILEN        0x10U          // Timeout interrupt level 1 Enable
#define LIN_LINILEN_TOWUPSILEN    0x40U          // Timeout After Wakeup Signal interrupt level 1 Enable
#define LIN_LINILEN_TO3WUPSILEN   0x80U          // Timeout After 3 Wakeup Signal interrupt level 1 Enable
#define LIN_LINILEN_TXILEN        0x100U         // Transmitter interrupt level 1 Enable
#define LIN_LINILEN_RXILEN        0x200U         // Receiver interrupt level 1 Enable
#define LIN_LINILEN_IDILEN        0x2000U        // Identification interrupt level 1 Enable
#define LIN_LINILEN_PILEN         0x1000000U     // parity interrupt level 1 Enable
#define LIN_LINILEN_OREILEN       0x2000000U     // Overrun error interrupt level 1 Enable
#define LIN_LINILEN_FEILEN        0x4000000U     // Framing error interrupt level 1 Enable
#define LIN_LINILEN_NREILEN       0x8000000U     // No response error interrupt level 1 Enable
#define LIN_LINILEN_ISFEILEN      0x10000000U    // Inconsistent sync field error interrupt level 1 Enable
#define LIN_LINILEN_CSEILEN       0x20000000U    // Checksum-error Interrupt level 1 Enable
#define LIN_LINILEN_PBEILEN       0x40000000U    // Physical bus error interrupt level 1 Enable
#define LIN_LINILEN_BEILEN        0x80000000U    // Bit error interrupt level 1 Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINILCLR register
//
//*************************************************************************************************
#define LIN_LINILCLR_BRKDETILCLR    0x1U          // Break detect interrupt level 1 Clear
#define LIN_LINILCLR_WUPILCLR       0x2U          // Wake up interrupt level 1 Clear
#define LIN_LINILCLR_TOILCLR        0x10U         // Timeout interrupt level 1 Clear
#define LIN_LINILCLR_TOWUPSILCLR    0x40U         // Timeout After Wakeup Signal interrupt level 1 Clear
#define LIN_LINILCLR_TO3WUPSILCLR   0x80U         // Timeout After 3 Wakeup Signal interrupt level 1 Clear
#define LIN_LINILCLR_TXILCLR        0x100U        // Transmitter interrupt level 1 Clear
#define LIN_LINILCLR_RXILCLR        0x200U        // Receiver interrupt level 1 Clear
#define LIN_LINILCLR_IDILCLR        0x2000U       // Identification interrupt level 1 Clear
#define LIN_LINILCLR_PILCLR         0x1000000U    // Parity interrupt level 1 Clear
#define LIN_LINILCLR_OREILCLR       0x2000000U    // Overrun error interrupt level 1 Clear
#define LIN_LINILCLR_FEILCLR        0x4000000U    // Framing error interrupt level 1 Clear
#define LIN_LINILCLR_NREILCLR       0x8000000U    // No response error interrupt level 1 Clear
#define LIN_LINILCLR_ISFEILCLR      0x10000000U   // Inconsistent sync field error interrupt level 1 Clear
#define LIN_LINILCLR_CSEILCLR       0x20000000U   // Checksum-error Interrupt level 1 Clear
#define LIN_LINILCLR_PBEILCLR       0x40000000U   // Physical bus error interrupt level 1 Clear
#define LIN_LINILCLR_BEILCLR        0x80000000U   // Bit error interrupt level 1 Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINFLG register
//
//*************************************************************************************************
#define LIN_LINFLG_BRKDETFLG     0x1U          // Break detect flag
#define LIN_LINFLG_WUPFLG        0x2U          // Wake up flag
#define LIN_LINFLG_RXIDLEFLG     0x4U          // Receiver idle flag
#define LIN_LINFLG_BUSYFLG       0x8U          // Bus BUSY flag
#define LIN_LINFLG_LINIDLEFLG    0x10U         // LIN bus idle flag
#define LIN_LINFLG_TOWUPSFLG     0x40U         // Timeout After Wakeup Signal flag
#define LIN_LINFLG_TO3WUPSFLG    0x80U         // Timeout After 3 Wakeup Signal flag
#define LIN_LINFLG_TXBRDYFLG     0x100U        // Transmitter buffer ready flag
#define LIN_LINFLG_RXRDYFLG      0x200U        // Receiver ready flag
#define LIN_LINFLG_TXWUPSEL      0x400U        // Transmitter wakeup mode select
#define LIN_LINFLG_TXEFLG        0x800U        // Transmitter Empty flag
#define LIN_LINFLG_RXWUPSEL      0x1000U       // Receiver wakeup mode select
#define LIN_LINFLG_TXIDFLG       0x2000U       // Transmit Identifier Flag
#define LIN_LINFLG_RXIDFLG       0x4000U       // Receive Identifier Flag
#define LIN_LINFLG_PEFLG         0x1000000U    // Parity Error Flag
#define LIN_LINFLG_OREFLG        0x2000000U    // Overrun error flag
#define LIN_LINFLG_FEFLG         0x4000000U    // Framing error flag
#define LIN_LINFLG_NREFLG        0x8000000U    // No Response Error Flag
#define LIN_LINFLG_ISFEFLG       0x10000000U   // Inconsistent Sync Field Error Flag
#define LIN_LINFLG_CSEFLG        0x20000000U   // Checksum Error Flag
#define LIN_LINFLG_PBEFLG        0x40000000U   // Physical Bus Error Flag
#define LIN_LINFLG_BEFLG         0x80000000U   // Bit Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINIVO0 register
//
//*************************************************************************************************
#define LIN_LINIVO0_IVO0_S   0U
#define LIN_LINIVO0_IVO0_M   0x1FU   // INT0 Interrupt vector offset

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINIVO1 register
//
//*************************************************************************************************
#define LIN_LINIVO1_IVO1_S   0U
#define LIN_LINIVO1_IVO1_M   0x1FU   // INT1 Interrupt vector offset

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINLCFG register
//
//*************************************************************************************************
#define LIN_LINLCFG_CLCFG_S     0U
#define LIN_LINLCFG_CLCFG_M     0x7U       // Character length Configure
#define LIN_LINLCFG_FLCFG_S     16U
#define LIN_LINLCFG_FLCFG_M     0x70000U   // Frame length Configure

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINBR register
//
//*************************************************************************************************
#define LIN_LINBR_PSCSELL_S              0U
#define LIN_LINBR_PSCSELL_M              0xFFFFU       // 24-Bit Integer Prescaler Select (Low Bits)
#define LIN_LINBR_PSCSELH_S              16U
#define LIN_LINBR_PSCSELH_M              0xFF0000U     // Prescaler Selcet
#define LIN_LINBR_FDIVSEL_S             24U
#define LIN_LINBR_FDIVSEL_M             0xF000000U    // 4 bit Fractional Divider Selcet
#define LIN_LINBR_SFDIVSEL_S            28U
#define LIN_LINBR_SFDIVSEL_M            0x70000000U   // Superfractional Divider Selcet

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINRXED register
//
//*************************************************************************************************
#define LIN_LINRXED_RXED_S   0U
#define LIN_LINRXED_RXED_M   0xFFU   // Receiver Emulation Data.

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINRXD register
//
//*************************************************************************************************
#define LIN_LINRXED_RXD_S   0U
#define LIN_LINRXED_RXD_M   0xFFU   // Received Data.

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINTXD register
//
//*************************************************************************************************
#define LIN_LINRXED_TXD_S   0U
#define LIN_LINRXED_TXD_M   0xFFU   // Transmit data

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINPCTRL0 register
//
//*************************************************************************************************
#define LIN_LINPCTRL0_RXPEN   0x2U   // Receive pin Enable
#define LIN_LINPCTRL0_TXPEN   0x4U   // Transmit  pin Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINPCTRL2 register
//
//*************************************************************************************************
#define LIN_LINPCTRL2_RXPVAL   0x2U   // Receive pin current value
#define LIN_LINPCTRL2_TXPVAL   0x4U   // Transmit  pin current value

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINCOMP register
//
//*************************************************************************************************
#define LIN_LINCOMP_SBEXTSEL_S      0U
#define LIN_LINCOMP_SBEXTSEL_M      0x7U     // Sync Break extend Selcet
#define LIN_LINCOMP_SDCOMPSEL_S     8U
#define LIN_LINCOMP_SDCOMPSEL_M     0x300U   // Sync Delimiter compare Selcet

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINRXB0 register
//
//*************************************************************************************************
#define LIN_LINRXB0_RXB3_S   0U
#define LIN_LINRXB0_RXB3_M   0xFFU         // Receive Buffer 3
#define LIN_LINRXB0_RXB2_S   8U
#define LIN_LINRXB0_RXB2_M   0xFF00U       // Receive Buffer 2
#define LIN_LINRXB0_RXB1_S   16U
#define LIN_LINRXB0_RXB1_M   0xFF0000U     // Receive Buffer 1
#define LIN_LINRXB0_RXB0_S   24U
#define LIN_LINRXB0_RXB0_M   0xFF000000U   // Receive Buffer 0

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINRXB1 register
//
//*************************************************************************************************
#define LIN_LINRXB1_RXB7_S   0U
#define LIN_LINRXB1_RXB7_M   0xFFU         // Receive Buffer 7
#define LIN_LINRXB1_RXB6_S   8U
#define LIN_LINRXB1_RXB6_M   0xFF00U       // Receive Buffer 6
#define LIN_LINRXB1_RXB5_S   16U
#define LIN_LINRXB1_RXB5_M   0xFF0000U     // Receive Buffer 5
#define LIN_LINRXB1_RXB4_S   24U
#define LIN_LINRXB1_RXB4_M   0xFF000000U   // Receive Buffer 4

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINIDMASK register
//
//*************************************************************************************************
#define LIN_LINIDMASK_TXIDMASK_S   0U
#define LIN_LINIDMASK_TXIDMASK_M   0xFFU       // Transmit ID mask
#define LIN_LINIDMASK_RXIDMASK_S   16U
#define LIN_LINIDMASK_RXIDMASK_M   0xFF0000U   // Receive ID mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINID register
//
//*************************************************************************************************
#define LIN_LINID_IDBYTE_S            0U
#define LIN_LINID_IDBYTE_M            0xFFU       // ID byte Set
#define LIN_LINID_IDSTBYTE_S          8U
#define LIN_LINID_IDSTBYTE_M          0xFF00U     // ID Slave Task byte
#define LIN_LINID_RXID_S              16U
#define LIN_LINID_RXID_M              0xFF0000U   // Received ID

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINTXB0 register
//
//*************************************************************************************************
#define LIN_LINTXB0_TXB3_S   0U
#define LIN_LINTXB0_TXB3_M   0xFFU         // TRANSMIT Buffer 3
#define LIN_LINTXB0_TXB2_S   8U
#define LIN_LINTXB0_TXB2_M   0xFF00U       // TRANSMIT Buffer 2
#define LIN_LINTXB0_TXB1_S   16U
#define LIN_LINTXB0_TXB1_M   0xFF0000U     // TRANSMIT Buffer 1
#define LIN_LINTXB0_TXB0_S   24U
#define LIN_LINTXB0_TXB0_M   0xFF000000U   // TRANSMIT Buffer 0

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINTXB1 register
//
//*************************************************************************************************
#define LIN_LINTXB1_TXB7_S   0U
#define LIN_LINTXB1_TXB7_M   0xFFU         // TRANSMIT Buffer 7
#define LIN_LINTXB1_TXB6_S   8U
#define LIN_LINTXB1_TXB6_M   0xFF00U       // TRANSMIT Buffer 6
#define LIN_LINTXB1_TXB5_S   16U
#define LIN_LINTXB1_TXB5_M   0xFF0000U     // TRANSMIT Buffer 5
#define LIN_LINTXB1_TXB4_S   24U
#define LIN_LINTXB1_TXB4_M   0xFF000000U   // TRANSMIT Buffer 4

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINMBRPSC register
//
//*************************************************************************************************
#define LIN_LINMBRPSC_MBRPSC_S   0U
#define LIN_LINMBRPSC_MBRPSC_M   0x1FFFU   // Maximum Baud Rate Prescaler

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINEET register
//
//*************************************************************************************************
#define LIN_LINEET_ALBCFG          0x1U          // Analog loopback Configure
#define LIN_LINEET_LBCFG           0x2U          // Loopback Mode Configure
#define LIN_LINEET_IODFTEN_S       8U
#define LIN_LINEET_IODFTEN_M       0xF00U        // IO DFT Enable
#define LIN_LINEET_TXDLYCFG_S      16U
#define LIN_LINEET_TXDLYCFG_M      0x70000U      // Transmit Delay Configure
#define LIN_LINEET_PSMASK_S        19U
#define LIN_LINEET_PSMASK_M        0x180000U     // Pin sample mask
#define LIN_LINEET_BRKEEN          0x1000000U    // BRKDT error Enable
#define LIN_LINEET_PEEN            0x2000000U    // Parity error Enable
#define LIN_LINEET_FEEN            0x4000000U    // Frame error Enable
#define LIN_LINEET_ISFEEN          0x10000000U   // Inconsistent Sync Field Error Enable
#define LIN_LINEET_CSEEN           0x20000000U   // Checksum Error Enable
#define LIN_LINEET_PBEEN           0x40000000U   // Physical Bus Error Enable
#define LIN_LINEET_BEEN            0x80000000U   // Bit Error Enable 

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINGIEN register
//
//*************************************************************************************************
#define LIN_LINGIEN_GIEN0   0x1U   // Global Interrupt Enable for LIN INT0
#define LIN_LINGIEN_GIEN1   0x2U   // Global Interrupt Enable for LIN INT1

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINGIFLG register
//
//*************************************************************************************************
#define LIN_LINGIFLG_GIFLG0   0x1U   // Global Interrupt Flag for LIN INT0
#define LIN_LINGIFLG_GIFLG1   0x2U   // Global Interrupt Flag for LIN INT1

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINGICLR register
//
//*************************************************************************************************
#define LIN_LINGICLR_GICLR0   0x1U   // Global Interrupt Flag clear for LIN INT0
#define LIN_LINGICLR_GICLR1   0x2U   // Global Interrupt Flag clear for LIN INT1



#endif
