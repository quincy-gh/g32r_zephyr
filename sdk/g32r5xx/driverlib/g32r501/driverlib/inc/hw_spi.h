//###########################################################################
//
// FILE:    hw_spi.h
//
// TITLE:   Definitions for the SPI registers.
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

#ifndef HW_SPI_H
#define HW_SPI_H

//*************************************************************************************************
//
// The following are defines for the SPI register offsets
//
//*************************************************************************************************
#define SPI_O_CFG     (0x0*2U)   // SPI Configuration Control Register
#define SPI_O_CTRL    (0x1*2U)   // SPI Operation Control Register
#define SPI_O_STS     (0x2*2U)   // SPI Status Register
#define SPI_O_BR      (0x4*2U)   // SPI Baud Rate Register
#define SPI_O_EMUB    (0x6*2U)   // SPI Emulation Buffer Register
#define SPI_O_RXB     (0x7*2U)   // SPI Serial Input Buffer Register
#define SPI_O_TXB     (0x8*2U)   // SPI Serial Output Buffer Register
#define SPI_O_SDATAS  (0x9*2U)   // SPI Serial Data Register
#define SPI_O_TXFIFO  (0xA*2U)   // SPI FIFO Transmit Register
#define SPI_O_RXFIFO  (0xB*2U)   // SPI FIFO Receive Register
#define SPI_O_FFCTRL  (0xC*2U)   // SPI FIFO Control Register
#define SPI_O_PRICTRL (0xF*2U)   // SPI Priority Control Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the SPICFG register
//
//*************************************************************************************************
#define SPI_CFG_CLENSEL_S     0U
#define SPI_CFG_CLENSEL_M     0xFU    // Character Length
#define SPI_CFG_LBEN          0x10U   // Loopback Mode Enable
#define SPI_CFG_HSEN          0x20U   // High Speed Mode Enable
#define SPI_CFG_POLCFG        0x40U   // Clock Polarity Configure
#define SPI_CFG_SPIRDY        0x80U   // SPI ready

//*************************************************************************************************
//
// The following are defines for the bit fields in the SPICTRL register
//
//*************************************************************************************************
#define SPI_CTRL_IEN              0x1U    // SPI Interrupt Enable
#define SPI_CTRL_TXEN             0x2U    // Master/Slave Transmit Enable
#define SPI_CTRL_MSCFG            0x4U    // Master Slave mode configure
#define SPI_CTRL_PHASEL           0x8U    // Clock Phase Select
#define SPI_CTRL_OVRIEN           0x10U   // Overrun Interrupt Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SPISTS register
//
//*************************************************************************************************
#define SPI_STS_TXBFFLG     0x20U   // SPI Transmit Buffer Full Flag
#define SPI_STS_IFLG        0x40U   // SPI Interrupt Flag
#define SPI_STS_RXOVRFLG    0x80U   // SPI Receiver Overrun Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the SPIBR register
//
//*************************************************************************************************
#define SPI_BR_BRSEL_S   0U
#define SPI_BR_BRSEL_M   0x7FU   // SPI Bit Rate Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the SPITXFIFO register
//
//*************************************************************************************************
#define SPI_TXFIFO_TXFFILSEL_S     0U
#define SPI_TXFIFO_TXFFILSEL_M     0x1FU     // Transmit FIFO interrupt level Selcet
#define SPI_TXFIFO_TXFFIEN         0x20U     // Transmit FIFO Interrupt Enable
#define SPI_TXFIFO_TXFFICLR        0x40U     // Transmit FIFO Interrupt Flag Clear
#define SPI_TXFIFO_TXFFIFLG        0x80U     // Transmit FIFO interrupt flag
#define SPI_TXFIFO_TXFFST_S        8U
#define SPI_TXFIFO_TXFFST_M        0x1F00U   // transmit FIFO status
#define SPI_TXFIFO_TXFFEN          0x2000U   // transmit FIFO enable
#define SPI_TXFIFO_SPIFFEEN        0x4000U   // FIFO Enhancements enable
#define SPI_TXFIFO_SPIEN           0x8000U   // SPI Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SPIRXFIFO register
//
//*************************************************************************************************
#define SPI_RXFIFO_RXFFILSEL_S      0U
#define SPI_RXFIFO_RXFFILSEL_M      0x1FU     // RXFIFO Interrupt Level
#define SPI_RXFIFO_RXFFIEN          0x20U     // RXFIFO Interrupt Enable
#define SPI_RXFIFO_RXFFICLR         0x40U     // RXFIFO Interupt Clear
#define SPI_RXFIFO_RXFFIFLG         0x80U     // RXFIFO Interrupt Flag
#define SPI_RXFIFO_RXFFSTS_S        8U
#define SPI_RXFIFO_RXFFSTS_M        0x1F00U   // Receive FIFO Status
#define SPI_RXFIFO_RXFFEN           0x2000U   // RXFIFO Reset
#define SPI_RXFIFO_RXFFOVRCLR       0x4000U   // Receive FIFO Overflow Clear
#define SPI_RXFIFO_RXFFOVRFLG       0x8000U   // Receive FIFO Overflow Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the SPIFFCTRL register
//
//*************************************************************************************************
#define SPI_FFCTRL_FFTXDLYSEL_S   0U
#define SPI_FFCTRL_FFTXDLYSEL_M   0xFFU   // FIFO Transmit Delay Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the SPIPRICTRL register
//
//*************************************************************************************************
#define SPI_PRICTRL_SPIMSEL   0x1U    // 3-wire mode select bit
#define SPI_PRICTRL_STEINV    0x2U    // SPISTE inversion bit
#define SPI_PRICTRL_EMUFREEEN 0x10U   // Free emulation mode
#define SPI_PRICTRL_EMUSOFT   0x20U   // Soft emulation mode



#endif
