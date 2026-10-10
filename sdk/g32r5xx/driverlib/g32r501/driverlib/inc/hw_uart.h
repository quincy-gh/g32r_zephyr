//###########################################################################
//
// FILE:    hw_UART.h
//
// TITLE:   Definitions for the UART registers.
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

#ifndef HW_UART_H
#define HW_UART_H

//*************************************************************************************************
//
// The following are defines for the UART register offsets
//
//*************************************************************************************************
#define UART_O_CCR     (0x0*2U)   // Communications control register
#define UART_O_CTL1    (0x1*2U)   // Control register 1
#define UART_O_HBAUD   (0x2*2U)   // Baud rate (high) register
#define UART_O_LBAUD   (0x3*2U)   // Baud rate (low) register
#define UART_O_CTL2    (0x4*2U)   // Control register 2
#define UART_O_RXST    (0x5*2U)   // Receive status register
#define UART_O_RXEMU   (0x6*2U)   // Receive emulation buffer register
#define UART_O_RXBUF   (0x7*2U)   // Receive data buffer
#define UART_O_TXBUF   (0x9*2U)   // Transmit data buffer
#define UART_O_FFTX    (0xA*2U)   // FIFO transmit register
#define UART_O_FFRX    (0xB*2U)   // FIFO receive register
#define UART_O_FFCT    (0xC*2U)   // FIFO control register
#define UART_O_PRI     (0xF*2U)   // UART priority control


//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTCCR register
//
//*************************************************************************************************
#define UART_CCR_UARTCHAR_S      0U
#define UART_CCR_UARTCHAR_M      0x7U    // Character length control
#define UART_CCR_ADDRIDLE_MODE   0x8U    // ADDR/IDLE Mode control
#define UART_CCR_LOOPBKENA       0x10U   // Loop Back enable
#define UART_CCR_PARITYENA       0x20U   // Parity enable
#define UART_CCR_PARITY          0x40U   // Even or Odd Parity
#define UART_CCR_STOPBITS        0x80U   // Number of Stop Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTCTL1 register
//
//*************************************************************************************************
#define UART_CTL1_RXENA         0x1U    // UART receiver enable
#define UART_CTL1_TXENA         0x2U    // UART transmitter enable
#define UART_CTL1_SLEEP         0x4U    // UART sleep
#define UART_CTL1_TXWAKE        0x8U    // Transmitter wakeup method
#define UART_CTL1_SWRESET       0x20U   // Software reset
#define UART_CTL1_RXERRINTENA   0x40U   // Receive error interrupt enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTHBAUD register
//
//*************************************************************************************************
#define UART_HBAUD_BAUD_S   0U
#define UART_HBAUD_BAUD_M   0xFFU   // UART 16-bit baud selection Registers UARTHBAUD

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTLBAUD register
//
//*************************************************************************************************
#define UART_LBAUD_BAUD_S   0U
#define UART_LBAUD_BAUD_M   0xFFU   // UART 16-bit baud selection Registers UARTLBAUD

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTCTL2 register
//
//*************************************************************************************************
#define UART_CTL2_TXINTENA     0x1U    // Transmit __interrupt enable
#define UART_CTL2_RXBKINTENA   0x2U    // Receiver-buffer break enable
#define UART_CTL2_TXEMPTY      0x40U   // Transmitter empty flag
#define UART_CTL2_TXRDY        0x80U   // Transmitter ready flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTRXST register
//
//*************************************************************************************************
#define UART_RXST_RXWAKE    0x2U    // Receiver wakeup detect flag
#define UART_RXST_PE        0x4U    // Parity error flag
#define UART_RXST_OE        0x8U    // Overrun error flag
#define UART_RXST_FE        0x10U   // Framing error flag
#define UART_RXST_BRKDT     0x20U   // Break-detect flag
#define UART_RXST_RXRDY     0x40U   // Receiver ready flag
#define UART_RXST_RXERROR   0x80U   // Receiver error flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTRXEMU register
//
//*************************************************************************************************
#define UART_RXEMU_ERXDT_S   0U
#define UART_RXEMU_ERXDT_M   0xFFU   // Receive emulation buffer data

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTRXBUF register
//
//*************************************************************************************************
#define UART_RXBUF_SAR_S     0U
#define UART_RXBUF_SAR_M     0xFFU     // Receive Character bits
#define UART_RXBUF_UARTFFPE   0x4000U   // Receiver error flag
#define UART_RXBUF_UARTFFFE   0x8000U   // Receiver error flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTTXBUF register
//
//*************************************************************************************************
#define UART_TXBUF_TXDT_S   0U
#define UART_TXBUF_TXDT_M   0xFFU   // Transmit data buffer

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTFFTX register
//
//*************************************************************************************************
#define UART_FFTX_TXFFIL_S      0U
#define UART_FFTX_TXFFIL_M      0x1FU     // Interrupt level
#define UART_FFTX_TXFFIENA      0x20U     // Interrupt enable
#define UART_FFTX_TXFFINTCLR    0x40U     // Clear INT flag
#define UART_FFTX_TXFFINT       0x80U     // INT flag
#define UART_FFTX_TXFFST_S      8U
#define UART_FFTX_TXFFST_M      0x1F00U   // FIFO status
#define UART_FFTX_TXFIFORESET   0x2000U   // FIFO reset
#define UART_FFTX_UARTFFENA      0x4000U   // Enhancement enable
#define UART_FFTX_UARTRST        0x8000U   // UART reset rx/tx channels

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTFFRX register
//
//*************************************************************************************************
#define UART_FFRX_RXFFIL_S      0U
#define UART_FFRX_RXFFIL_M      0x1FU     // Interrupt level
#define UART_FFRX_RXFFIENA      0x20U     // Interrupt enable
#define UART_FFRX_RXFFINTCLR    0x40U     // Clear INT flag
#define UART_FFRX_RXFFINT       0x80U     // INT flag
#define UART_FFRX_RXFFST_S      8U
#define UART_FFRX_RXFFST_M      0x1F00U   // FIFO status
#define UART_FFRX_RXFIFORESET   0x2000U   // FIFO reset
#define UART_FFRX_RXFFOVRCLR    0x4000U   // Clear overflow
#define UART_FFRX_RXFFOVF       0x8000U   // FIFO overflow

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTFFCT register
//
//*************************************************************************************************
#define UART_FFCT_FFTXDLY_S   0U
#define UART_FFCT_FFTXDLY_M   0xFFU     // FIFO transmit delay
#define UART_FFCT_CDC         0x2000U   // Auto baud mode enable
#define UART_FFCT_ABDCLR      0x4000U   // Auto baud clear
#define UART_FFCT_ABD         0x8000U   // Auto baud detect

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTPRI register
//
//*************************************************************************************************
#define UART_PRI_FREESOFT_S   3U
#define UART_PRI_FREESOFT_M   0x18U   // Emulation modes



#endif
