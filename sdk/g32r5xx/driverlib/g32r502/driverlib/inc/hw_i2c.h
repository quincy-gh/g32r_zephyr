//###########################################################################
//
// FILE:    hw_i2c.h
//
// TITLE:   Definitions for the I2C registers.
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

#ifndef HW_I2C_H
#define HW_I2C_H

//*************************************************************************************************
//
// The following are defines for the I2C register offsets
//
//*************************************************************************************************
#define I2C_O_OADDR  (0x0*2U)    // I2C Own address
#define I2C_O_IREN   (0x1*2U)    // I2C Interrupt Enable
#define I2C_O_STS    (0x2*2U)    // I2C Status
#define I2C_O_CLKL   (0x3*2U)    // I2C Clock low-time divider
#define I2C_O_CLKH   (0x4*2U)    // I2C Clock high-time divider
#define I2C_O_CNT    (0x5*2U)    // I2C Data count
#define I2C_O_RXD    (0x6*2U)    // I2C Data receive
#define I2C_O_SADDR  (0x7*2U)    // I2C Slave address
#define I2C_O_TXD    (0x8*2U)    // I2C Data Transmit
#define I2C_O_CTRL   (0x9*2U)    // I2C Mode
#define I2C_O_ISRC   (0xA*2U)    // I2C Interrupt Source
#define I2C_O_EXT    (0xB*2U)    // I2C Extended Mode
#define I2C_O_PSC    (0xC*2U)    // I2C Prescaler
#define I2C_O_TXFIFO (0x20*2U)   // I2C FIFO Transmit
#define I2C_O_RXFIFO (0x21*2U)   // I2C FIFO Receive


//*************************************************************************************************
//
// The following are defines for the bit fields in the I2COADDR register
//
//*************************************************************************************************
#define I2C_OADDR_OADDR_S   0U
#define I2C_OADDR_OADDR_M   0x3FFU   // I2C Own address

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CIREN register
//
//*************************************************************************************************
#define I2C_IREN_ARBLIREN   0x1U    // Arbitration-lost interrupt enable
#define I2C_IREN_NACKIREN   0x2U    // No-acknowledgment interrupt enable
#define I2C_IREN_RAIREN     0x4U    // Register-access-ready interrupt enable
#define I2C_IREN_RXDIREN    0x8U    // Receive-data-ready interrupt enable
#define I2C_IREN_TXDIREN    0x10U   // Transmit-data-ready interrupt enable
#define I2C_IREN_STODIREN   0x20U   // Stop condition detected interrupt enable
#define I2C_IREN_SAIREN     0x40U   // Addressed as slave interrupt enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSTS register
//
//*************************************************************************************************
#define I2C_STS_ARBLIFLG       0x1U      // Arbitration-lost interrupt flag bit
#define I2C_STS_NACKIFLG       0x2U      // No-acknowledgment interrupt flag bit.
#define I2C_STS_RAIFLG         0x4U      // Register-access-ready interrupt flag bit
#define I2C_STS_RXDIFLG        0x8U      // Receive-data-ready interrupt flag bit.
#define I2C_STS_TXDIFLG        0x10U     // Transmit-data-ready interrupt flag bit.
#define I2C_STS_STODIFLG       0x20U     // Stop condition detected bit.
#define I2C_STS_BTXCFLG        0x40U     // Byte transmit over indication
#define I2C_STS_ZEROAFLG       0x100U    // Address 0 bits
#define I2C_STS_SAFLG          0x200U    // Addressed-as-slave bit
#define I2C_STS_TXSNEFLG       0x400U    // Transmit shift register empty bit.
#define I2C_STS_RXSFFLG        0x800U    // Receive shift register full bit.
#define I2C_STS_BBSYFLG        0x1000U   // Bus busy bit.
#define I2C_STS_TXNACKFLG      0x2000U   // NACK sent bit.
#define I2C_STS_SFLG           0x4000U   // Slave direction bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CRXD register
//
//*************************************************************************************************
#define I2C_RXD_RXD_S   0U
#define I2C_RXD_RXD_M   0xFFU   // Receive data

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSADDR register
//
//*************************************************************************************************
#define I2C_SADDR_SADDR_S   0U
#define I2C_SADDR_SADDR_M   0x3FFU   // Slave Address

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CTXD register
//
//*************************************************************************************************
#define I2C_TXD_TXD_S   0U
#define I2C_TXD_TXD_M   0xFFU   // Transmit data

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CCTRL register
//
//*************************************************************************************************
#define I2C_CTRL_DBSEL_S      0U
#define I2C_CTRL_DBSEL_M      0x7U      // Bit count bits.
#define I2C_CTRL_FDFEN        0x8U      // Free Data Format
#define I2C_CTRL_STABEN       0x10U     // START Byte Mode
#define I2C_CTRL_I2CEN        0x20U     // I2C Module Reset
#define I2C_CTRL_DLBEN        0x40U     // Digital Loopback Mode
#define I2C_CTRL_REEN         0x80U     // Repeat Mode
#define I2C_CTRL_ADDRLEN      0x100U    // Expanded Address Mode
#define I2C_CTRL_RXTXCFG      0x200U    // Transmitter Mode
#define I2C_CTRL_MSCFG        0x400U    // Master Mode
#define I2C_CTRL_STOGEN       0x800U    // STOP Condition
#define I2C_CTRL_STAGEN       0x2000U   // START condition bit
#define I2C_CTRL_FREEEN       0x4000U   // Debug Action
#define I2C_CTRL_NACKCFG      0x8000U   // NACK mode bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CISRC register
//
//*************************************************************************************************
#define I2C_ISRC_IFLG_S       0U
#define I2C_ISRC_IFLG_M       0x7U     // Interrupt code bits.
#define I2C_ISRC_INTEST_S   8U
#define I2C_ISRC_INTEST_M   0xF00U   // Always write all 0s to this field

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CEXT register
//
//*************************************************************************************************
#define I2C_EXT_BWCCFG    0x1U   // Backwards compatibility mode
#define I2C_EXT_FWCCFG   0x2U   // Forward Compatibility for Tx behav in Type1

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CPSC register
//
//*************************************************************************************************
#define I2C_PSC_PSC_S   0U
#define I2C_PSC_PSC_M   0xFFU   // I2C Prescaler Divide Down

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CTXFIFO register
//
//*************************************************************************************************
#define I2C_TXFIFO_TXFFILEVEL_S     0U
#define I2C_TXFIFO_TXFFILEVEL_M     0x1FU     // Transmit FIFO Interrupt Level
#define I2C_TXFIFO_TXFFIEN          0x20U     // Transmit FIFO Interrupt Enable
#define I2C_TXFIFO_TXFFICLR         0x40U     // Transmit FIFO Interrupt Flag Clear
#define I2C_TXFIFO_TXFFIFLG         0x80U     // Transmit FIFO Interrupt Flag
#define I2C_TXFIFO_TXFFSTS_S        8U
#define I2C_TXFIFO_TXFFSTS_M        0x1F00U   // Transmit FIFO Status
#define I2C_TXFIFO_TXFFEN           0x2000U   // Transmit FIFO Reset
#define I2C_TXFIFO_I2CFFEN          0x4000U   // Transmit FIFO Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CRXFIFO register
//
//*************************************************************************************************
#define I2C_RXFIFO_RXFFILEVEL_S     0U
#define I2C_RXFIFO_RXFFILEVEL_M     0x1FU     // Receive FIFO Interrupt Level
#define I2C_RXFIFO_RXFFIEN          0x20U     // Receive FIFO Interrupt Enable
#define I2C_RXFIFO_RXFFICLR         0x40U     // Receive FIFO Interrupt Flag Clear
#define I2C_RXFIFO_RXFFIFLG         0x80U     // Receive FIFO Interrupt Flag
#define I2C_RXFIFO_RXFFSTS_S        8U
#define I2C_RXFIFO_RXFFSTS_M        0x1F00U   // Receive FIFO Status
#define I2C_RXFIFO_RXFFEN           0x2000U   // Receive FIFO Reset



#endif
