//###########################################################################
//
// FILE:    UART.c
//
// TITLE:   G32R501 UART driver.
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
// 1. Module prefix naming, parameter types for some functions.
//
//###########################################################################

#include "uart.h"

//*****************************************************************************
//
// UART_setConfig
//
//*****************************************************************************
void
UART_setConfig(uint32_t base, uint32_t lspclkHz, uint32_t baud, uint32_t config)
{
    uint32_t divider;

    //
    // Check the arguments.
    // Is the required baud rate greater than the maximum rate supported?
    //
    ASSERT(UART_isBaseValid(base));
    ASSERT(baud != 0U);
    ASSERT((baud * 16U) <= lspclkHz);

    //
    // Stop the UART.
    //
    UART_disableModule(base);

    //
    // Compute the baud rate divider.
    //
    divider = ((lspclkHz  / (baud * 8U)) - 1U);

    //
    // Set the baud rate.
    //
    HWREGH(base + UART_O_HBAUD) = (divider & 0xFF00U) >> 8U;
    HWREGH(base + UART_O_LBAUD) = divider & 0x00FFU;

    //
    // Set parity, data length, and number of stop bits.
    //
    HWREGH(base + UART_O_CCR) = ((HWREGH(base + UART_O_CCR) &
                                 ~(UART_CONFIG_PAR_MASK |
                                   UART_CONFIG_STOP_MASK |
                                   UART_CONFIG_WLEN_MASK)) | config);

    //
    // Start the UART.
    //
    UART_enableModule(base);
}

//*****************************************************************************
//
// UART_writeCharArray
//
//*****************************************************************************
void
UART_writeCharArray(uint32_t base, const uint8_t * const array, 
                   uint16_t length)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    uint16_t i;
    //
    // Check if FIFO enhancement is enabled.
    //
    if(UART_isFIFOEnabled(base))
    {
        //
        // FIFO is enabled.
        // For loop to write (Blocking) 'length' number of characters
        //
        for(i = 0U; i < length; i++)
        {
            //
            // Wait until space is available in the transmit FIFO.
            //
            while(UART_getTxFIFOStatus(base) == UART_FIFO_TX15)
            {
            }

            //
            // Send a char.
            //
            HWREGH(base + UART_O_TXBUF) = array[i];
        }
    }
    else
    {
        //
        // FIFO is not enabled.
        // For loop to write (Blocking) 'length' number of characters
        //
        for(i = 0U; i < length; i++)
        {
            //
            // Wait until space is available in the transmit buffer.
            //
            while(!UART_isSpaceAvailableNonFIFO(base))
            {
            }

            //
            // Send a char.
            //
            HWREGH(base + UART_O_TXBUF) = array[i];
        }
    }
}

//*****************************************************************************
//
// UART_readCharArray
//
//*****************************************************************************
void
UART_readCharArray(uint32_t base, uint8_t * const array, uint16_t length)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    uint16_t i;
    //
    // Check if FIFO enhancement is enabled.
    //
    if(UART_isFIFOEnabled(base))
    {
        //
        // FIFO is enabled.
        // For loop to read (Blocking) 'length' number of characters
        //
        for(i = 0U; i < length; i++)
        {
            //
            // Wait until a character is available in the receive FIFO.
            //
            while(UART_getRxFIFOStatus(base) == UART_FIFO_RX0)
            {
            }

            //
            // Return the character from the receive buffer.
            //
            array[i] = (uint16_t)
                       (HWREGH(base + UART_O_RXBUF) & UART_RXBUF_SAR_M);
        }
    }
    else
    {
        //
        // FIFO is not enabled.
        // For loop to read (Blocking) 'length' number of characters
        //
        for(i = 0U; i < length; i++)
        {
            //
            // Wait until a character is available in the receive buffer.
            //
            while(!UART_isDataAvailableNonFIFO(base))
            {
            }

            //
            // Return the character from the receive buffer.
            //
            array[i] = (uint16_t)
                       (HWREGH(base + UART_O_RXBUF) & UART_RXBUF_SAR_M);
        }
    }
}

//*****************************************************************************
//
// UART_enableInterrupt
//
//*****************************************************************************
void
UART_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable the specified interrupts.
    //
    if((intFlags & UART_INT_RXERR) == UART_INT_RXERR)
    {
        HWREGH(base + UART_O_CTL1) |= UART_CTL1_RXERRINTENA;
    }
    if((intFlags & UART_INT_RXRDY_BRKDT) == UART_INT_RXRDY_BRKDT)
    {
        HWREGH(base + UART_O_CTL2) |= UART_CTL2_RXBKINTENA;
    }
    if((intFlags & UART_INT_TXRDY) == UART_INT_TXRDY)
    {
        HWREGH(base + UART_O_CTL2) |= UART_CTL2_TXINTENA;
    }
    if((intFlags & UART_INT_TXFF) == UART_INT_TXFF)
    {
        HWREGH(base + UART_O_FFTX) |= UART_FFTX_TXFFIENA;
    }
    if((intFlags & UART_INT_RXFF) == UART_INT_RXFF)
    {
        HWREGH(base + UART_O_FFRX) |= UART_FFRX_RXFFIENA;
    }
}

//*****************************************************************************
//
// UART_disableInterrupt
//
//*****************************************************************************
void
UART_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable the specified interrupts.
    //
    if((intFlags & UART_INT_RXERR) == UART_INT_RXERR)
    {
        HWREGH(base + UART_O_CTL1) &= ~UART_CTL1_RXERRINTENA;
    }
    if((intFlags & UART_INT_RXRDY_BRKDT) == UART_INT_RXRDY_BRKDT)
    {
        HWREGH(base + UART_O_CTL2) &= ~UART_CTL2_RXBKINTENA;
    }
    if((intFlags & UART_INT_TXRDY) == UART_INT_TXRDY)
    {
        HWREGH(base + UART_O_CTL2) &= ~UART_CTL2_TXINTENA;
    }
    if((intFlags & UART_INT_TXFF) == UART_INT_TXFF)
    {
        HWREGH(base + UART_O_FFTX) &= ~UART_FFTX_TXFFIENA;
    }
    if((intFlags & UART_INT_RXFF) == UART_INT_RXFF)
    {
        HWREGH(base + UART_O_FFRX) &= ~UART_FFRX_RXFFIENA;
    }
}

//*****************************************************************************
//
// UART_getInterruptStatus
//
//*****************************************************************************
uint32_t
UART_getInterruptStatus(uint32_t base)
{
    uint32_t interruptStatus = 0;

    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the interrupt status.
    //
    if((HWREGH(base + UART_O_CTL2) & UART_CTL2_TXRDY) == UART_CTL2_TXRDY)
    {
        interruptStatus |= UART_INT_TXRDY;
    }
    if((HWREGH(base + UART_O_RXST) & UART_RXST_RXERROR) == UART_RXST_RXERROR)
    {
        interruptStatus |= UART_INT_RXERR;
    }
    if(((HWREGH(base + UART_O_RXST) & UART_RXST_RXRDY) == UART_RXST_RXRDY)  ||
       ((HWREGH(base + UART_O_RXST) & UART_RXST_BRKDT) ==  UART_RXST_BRKDT))
    {
        interruptStatus |= UART_INT_RXRDY_BRKDT;
    }
    if((HWREGH(base + UART_O_FFTX) & UART_FFTX_TXFFINT) == UART_FFTX_TXFFINT)
    {
        interruptStatus |= UART_INT_TXFF;
    }
    if((HWREGH(base + UART_O_FFRX) & UART_FFRX_RXFFINT) == UART_FFRX_RXFFINT)
    {
        interruptStatus |= UART_INT_RXFF;
    }
    if((HWREGH(base + UART_O_RXST) & UART_RXST_FE) == UART_RXST_FE)
    {
        interruptStatus |= UART_INT_FE;
    }
    if((HWREGH(base + UART_O_RXST) & UART_RXST_OE) == UART_RXST_OE)
    {
        interruptStatus |= UART_INT_OE;
    }
    if((HWREGH(base + UART_O_RXST) & UART_RXST_PE) == UART_RXST_PE)
    {
        interruptStatus |= UART_INT_PE;
    }

    return(interruptStatus);
}

//*****************************************************************************
//
// UART_clearInterruptStatus
//
//*****************************************************************************
void
UART_clearInterruptStatus(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Clear the requested interrupt sources.
    //
    if(((intFlags & UART_INT_RXERR) == UART_INT_RXERR) ||
       ((intFlags & UART_INT_RXRDY_BRKDT) == UART_INT_RXRDY_BRKDT) ||
       ((intFlags & UART_INT_FE) == UART_INT_FE) ||
       ((intFlags & UART_INT_OE) == UART_INT_OE) ||
       ((intFlags & UART_INT_PE) == UART_INT_PE))
    {
        UART_performSoftwareReset(base);
    }
    if((intFlags & UART_INT_TXFF) == UART_INT_TXFF)
    {
        HWREGH(base + UART_O_FFTX) |= UART_FFTX_TXFFINTCLR;
    }
    if((intFlags & UART_INT_RXFF) == UART_INT_RXFF)
    {
         HWREGH(base + UART_O_FFRX) |= UART_FFRX_RXFFINTCLR;
    }
}

//*****************************************************************************
//
// UART_setBaud
//
//*****************************************************************************
void UART_setBaud(uint32_t base, uint32_t lspclkHz, uint32_t baud)
{
    uint32_t divider;

    //
    // Compute the baud rate divider {ROUND TO NEAREST INTEGER}
    //
    divider = (uint32_t)(((float)((float)lspclkHz / ((float)baud * 8.0F)) - 1.0F) + 0.5F);

    //
    // Set the baud rate.
    //
    HWREGH(base + UART_O_HBAUD) = (divider & 0xFF00U) >> 8U;
    HWREGH(base + UART_O_LBAUD) = divider & 0x00FFU;
}

//*****************************************************************************
//
// UART_setWakeFlag
//
//*****************************************************************************
void UART_setWakeFlag(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Set the TX wake flag bit to indicate
    // that the next frame is an address frame.
    //
    HWREGH(base + UART_O_CTL1) |= UART_CTL1_TXWAKE;
}

