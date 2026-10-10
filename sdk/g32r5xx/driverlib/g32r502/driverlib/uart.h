//###########################################################################
//
// FILE:    UART.h
//
// TITLE:   G32R502 UART driver.
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
// 1. Module prefix naming, parameter types for some functions.
//
//###########################################################################


#ifndef UART_H
#define UART_H

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
//! \addtogroup uart_api UART
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include "debug.h"

//*****************************************************************************
//
// Values that can be passed to UART_enableInterrupt, UART_disableInterrupt, and
// UART_clearInterruptStatus as the intFlags parameter, and returned from
// UART_getInterruptStatus.
//
//*****************************************************************************
#define UART_INT_RXERR          0x01U  //!< RXERR interrupt
#define UART_INT_RXRDY_BRKDT    0x02U  //!< RXRDY interrupt
#define UART_INT_TXRDY          0x04U  //!< TXRDY interrupt
#define UART_INT_TXFF           0x08U  //!< TX FIFO level interrupt
#define UART_INT_RXFF           0x10U  //!< RX FIFO level interrupt
#define UART_INT_FE             0x20U  //!< Frame Error
#define UART_INT_OE             0x40U  //!< Overrun Error
#define UART_INT_PE             0x80U  //!< Parity Error

//*****************************************************************************
//
// Values that can be passed to UART_setConfig as the config parameter
// and returned by UART_getConfig in the config parameter.
// Additionally, the UART_CONFIG_PAR_* enum subset can be passed to
// UART_setParityMode as the parity parameter, and are returned by
// UART_getParityMode.
//
//*****************************************************************************
#define UART_CONFIG_WLEN_MASK   0x0007U  //!< Mask for extracting word length
#define UART_CONFIG_WLEN_8      0x0007U  //!< 8 bit data
#define UART_CONFIG_WLEN_7      0x0006U  //!< 7 bit data
#define UART_CONFIG_WLEN_6      0x0005U  //!< 6 bit data
#define UART_CONFIG_WLEN_5      0x0004U  //!< 5 bit data
#define UART_CONFIG_WLEN_4      0x0003U  //!< 4 bit data
#define UART_CONFIG_WLEN_3      0x0002U  //!< 3 bit data
#define UART_CONFIG_WLEN_2      0x0001U  //!< 2 bit data
#define UART_CONFIG_WLEN_1      0x0000U  //!< 1 bit data
#define UART_CONFIG_STOP_MASK   0x0080U  //!< Mask for extracting stop bits
#define UART_CONFIG_STOP_ONE    0x0000U  //!< One stop bit
#define UART_CONFIG_STOP_TWO    0x0080U  //!< Two stop bits
#define UART_CONFIG_PAR_MASK    0x0060U  //!< Parity Mask

//*****************************************************************************
//
//! Values that can be used with UART_setParityMode() and UART_getParityMode() to
//! describe the parity of the UART communication.
//
//*****************************************************************************
typedef enum
{
    UART_CONFIG_PAR_NONE = 0x0000U,  //!< No parity
    UART_CONFIG_PAR_EVEN = 0x0060U,  //!< Even parity
    UART_CONFIG_PAR_ODD  = 0x0020U   //!< Odd parity
} UART_ParityType;

//*****************************************************************************
//
//! Values that can be passed to UART_setFIFOInterruptLevel() as the txLevel
//! parameter and returned by UART_getFIFOInteruptLevel() and
//! UART_getTxFIFOStatus().
//
//*****************************************************************************
typedef enum
{
    UART_FIFO_TX0  = 0x0000U, //!< Transmit interrupt empty
    UART_FIFO_TX1  = 0x0001U, //!< Transmit interrupt 1/16 full
    UART_FIFO_TX2  = 0x0002U, //!< Transmit interrupt 2/16 full
    UART_FIFO_TX3  = 0x0003U, //!< Transmit interrupt 3/16 full
    UART_FIFO_TX4  = 0x0004U, //!< Transmit interrupt 4/16 full
    UART_FIFO_TX5  = 0x0005U, //!< Transmit interrupt 5/16 full
    UART_FIFO_TX6  = 0x0006U, //!< Transmit interrupt 6/16 full
    UART_FIFO_TX7  = 0x0007U, //!< Transmit interrupt 7/16 full
    UART_FIFO_TX8  = 0x0008U, //!< Transmit interrupt 8/16 full
    UART_FIFO_TX9  = 0x0009U, //!< Transmit interrupt 9/16 full
    UART_FIFO_TX10 = 0x000AU, //!< Transmit interrupt 10/16 full
    UART_FIFO_TX11 = 0x000BU, //!< Transmit interrupt 11/16 full
    UART_FIFO_TX12 = 0x000CU, //!< Transmit interrupt 12/16 full
    UART_FIFO_TX13 = 0x000DU, //!< Transmit interrupt 13/16 full
    UART_FIFO_TX14 = 0x000EU, //!< Transmit interrupt 14/16 full
    UART_FIFO_TX15 = 0x000FU, //!< Transmit interrupt 15/16 full
    UART_FIFO_TX16 = 0x0010U  //!< Transmit interrupt full
} UART_TxFIFOLevel;

//*****************************************************************************
//
//! Values that can be passed to UART_setFIFOInterruptLevel() as the rxLevel
//! parameter and returned by UART_getFIFOInterruptLevel() and
//! UART_getRxFIFOStatus().
//
//*****************************************************************************
typedef enum
{
    UART_FIFO_RX0  = 0x0000U, //!< Receive interrupt empty
    UART_FIFO_RX1  = 0x0001U, //!< Receive interrupt 1/16 full
    UART_FIFO_RX2  = 0x0002U, //!< Receive interrupt 2/16 full
    UART_FIFO_RX3  = 0x0003U, //!< Receive interrupt 3/16 full
    UART_FIFO_RX4  = 0x0004U, //!< Receive interrupt 4/16 full
    UART_FIFO_RX5  = 0x0005U, //!< Receive interrupt 5/16 full
    UART_FIFO_RX6  = 0x0006U, //!< Receive interrupt 6/16 full
    UART_FIFO_RX7  = 0x0007U, //!< Receive interrupt 7/16 full
    UART_FIFO_RX8  = 0x0008U, //!< Receive interrupt 8/16 full
    UART_FIFO_RX9  = 0x0009U, //!< Receive interrupt 9/16 full
    UART_FIFO_RX10 = 0x000AU, //!< Receive interrupt 10/16 full
    UART_FIFO_RX11 = 0x000BU, //!< Receive interrupt 11/16 full
    UART_FIFO_RX12 = 0x000CU, //!< Receive interrupt 12/16 full
    UART_FIFO_RX13 = 0x000DU, //!< Receive interrupt 13/16 full
    UART_FIFO_RX14 = 0x000EU, //!< Receive interrupt 14/16 full
    UART_FIFO_RX15 = 0x000FU, //!< Receive interrupt 15/16 full
    UART_FIFO_RX16 = 0x0010U  //!< Receive interrupt full
} UART_RxFIFOLevel;

//*****************************************************************************
//
// Values returned from UART_getRxStatus().  These correspond to the different
// bits and flags of the UARTRXST register.
//
//*****************************************************************************
#define UART_RXSTATUS_WAKE       0x0002U  //!< Receiver wake up detect
#define UART_RXSTATUS_PARITY     0x0004U  //!< Parity error
#define UART_RXSTATUS_OVERRUN    0x0008U  //!< Overrun error
#define UART_RXSTATUS_FRAMING    0x0010U  //!< Framing error
#define UART_RXSTATUS_BREAK      0x0020U  //!< Break detect
#define UART_RXSTATUS_READY      0x0040U  //!< Receiver ready
#define UART_RXSTATUS_ERROR      0x0080U  //!< Receiver error

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks a UART base address.
//!
//! \param base is the base address of the UART port.
//!
//! This function determines if a UART port base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
UART_isBaseValid(uint32_t base)
{
    return(
           (base == UARTA_BASE) ||
           (base == UARTB_BASE)||
           (base == UARTC_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Sets the type of parity.
//!
//! \param base is the base address of the UART port.
//! \param parity specifies the type of parity to use.
//!
//! Sets the type of parity to use for transmitting and expect when receiving.
//! The \e parity parameter must be one of the following:
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_setParityMode(uint32_t base, UART_ParityType parity)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Set the parity mode.
    //
    HWREGH(base + UART_O_CCR) = ((HWREGH(base + UART_O_CCR) &
                                 ~(UART_CONFIG_PAR_MASK)) | (uint16_t)parity);
}

//*****************************************************************************
//
//! Gets the type of parity currently being used.
//!
//! \param base is the base address of the UART port.
//!
//! This function gets the type of parity used for transmitting data and
//! expected when receiving data.
//!
//! \return Returns the current parity settings, specified as one of the
//! following:
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD.
//
//*****************************************************************************
static inline UART_ParityType
UART_getParityMode(uint32_t base)
{
    uint16_t parity;

    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the current parity setting.
    //
    parity = (HWREGH(base + UART_O_CCR) & (UART_CONFIG_PAR_MASK));

    return((UART_ParityType)parity);
}

//*****************************************************************************
//
//! Sets the multiprocessor protocol to address-bit mode.
//!
//! \param base is the base address of the UART port.
//!
//! This function sets the multi-processor protocol to address-bit mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_setAddrMultiProcessorMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable the address-bit mode protocol
    //
    HWREGH(base + UART_O_CCR) |= UART_CCR_ADDRIDLE_MODE;
}

//*****************************************************************************
//
//! Sets the multiprocessor protocol to idle-line mode.
//!
//! \param base is the base address of the UART port.
//!
//! This function sets the multi-processor protocol to idle-line protocol.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_setIdleMultiProcessorMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable the address-bit mode protocol
    //
    HWREGH(base + UART_O_CCR) &= ~UART_CCR_ADDRIDLE_MODE;
}

//*****************************************************************************
//
//! Locks Autobaud.
//!
//! \param base is the base address of the UART port.
//!
//! This function performs an autobaud lock for the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_lockAutobaud(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Prime the baud register
    //
    HWREGH(base + UART_O_HBAUD) = 0x0U;
    HWREGH(base + UART_O_LBAUD) = 0x1U;

    //
    // Prepare for autobaud detection.
    // Set the CDC bit to enable autobaud detection and clear the ABD bit.
    //
    HWREGH(base + UART_O_FFCT) |= UART_FFCT_CDC;
    HWREGH(base + UART_O_FFCT) |= UART_FFCT_ABDCLR;

    //
    // Wait until we correctly read an 'A' or 'a' and lock
    //
    while((HWREGH(base + UART_O_FFCT) & UART_FFCT_ABD) != UART_FFCT_ABD)
    {
    }

    //
    // After autobaud lock, clear the ABD and CDC bits
    //
    HWREGH(base + UART_O_FFCT) |= UART_FFCT_ABDCLR;
    HWREGH(base + UART_O_FFCT) &= ~UART_FFCT_CDC;
}

//*****************************************************************************
//
//! Sets the FIFO interrupt level at which interrupts are generated.
//!
//! \param base is the base address of the UART port.
//! \param txLevel is the transmit FIFO interrupt level, specified as one of
//! the following:
//! \b UART_FIFO_TX0, \b UART_FIFO_TX1, \b UART_FIFO_TX2, . . . or
//! \b UART_FIFO_TX15.
//! \param rxLevel is the receive FIFO interrupt level, specified as one of
//! the following
//! \b UART_FIFO_RX0, \b UART_FIFO_RX1, \b UART_FIFO_RX2, ... or \b UART_FIFO_RX15.
//!
//! This function sets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_setFIFOInterruptLevel(uint32_t base, UART_TxFIFOLevel txLevel,
                          UART_RxFIFOLevel rxLevel)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Set the FIFO interrupt levels.
    //
    HWREGH(base + UART_O_FFTX) = (HWREGH(base + UART_O_FFTX) &
                                 (~UART_FFTX_TXFFIL_M)) | (uint16_t)txLevel;
    HWREGH(base + UART_O_FFRX) = (HWREGH(base + UART_O_FFRX) &
                                 (~UART_FFRX_RXFFIL_M)) | (uint16_t)rxLevel;
}

//*****************************************************************************
//
//! Gets the FIFO interrupt level at which interrupts are generated.
//!
//! \param base is the base address of the UART port.
//! \param txLevel is a pointer to storage for the transmit FIFO interrupt
//! level, returned as one of the following:
//! \b UART_FIFO_TX0, \b UART_FIFO_TX1, \b UART_FIFO_TX2, ... or \b UART_FIFO_TX15.
//! \param rxLevel is a pointer to storage for the receive FIFO interrupt
//! level, returned as one of the following:
//! \b UART_FIFO_RX0, \b UART_FIFO_RX1, \b UART_FIFO_RX2, ... or \b UART_FIFO_RX15.
//!
//! This function gets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_getFIFOInterruptLevel(uint32_t base, UART_TxFIFOLevel *txLevel,
                          UART_RxFIFOLevel *rxLevel)
{

    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Extract the transmit and receive FIFO levels.
    //
    *txLevel = (UART_TxFIFOLevel)(HWREGH(base + UART_O_FFTX) &
                                 UART_FFTX_TXFFIL_M);
    *rxLevel = (UART_RxFIFOLevel)(HWREGH(base + UART_O_FFRX) &
                                 UART_FFRX_RXFFIL_M);
}

//*****************************************************************************
//
//! Gets the current configuration of a UART.
//!
//! \param base is the base address of the UART port.
//! \param lspclkHz is the rate of the clock supplied to the UART module.  This
//! is the LSPCLK.
//! \param baud is a pointer to storage for the baud rate.
//! \param config is a pointer to storage for the data format.
//!
//! The baud rate and data format for the UART is determined, given an
//! explicitly provided peripheral clock (hence the ExpClk suffix).  The
//! returned baud rate is the actual baud rate; it may not be the exact baud
//! rate requested or an ``official'' baud rate.  The data format returned in
//! \e config is enumerated the same as the \e config parameter of
//! UART_setConfig().
//!
//! The peripheral clock is the low speed peripheral clock.  This will be
//! the value returned by SysCtl_getLowSeedClock(), or it can be explicitly
//! hard coded if it is constant and known (to save the code/execution overhead
//! of a call to SysCtl_getLowSpeedClock()).
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_getConfig(uint32_t base, uint32_t lspclkHz, uint32_t *baud,
              uint32_t *config)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Compute the baud rate.
    //
    *baud = lspclkHz /
            ((1U + (uint32_t)((uint32_t)(HWREGH(base + UART_O_HBAUD) << 8U) |
               HWREGH(base + UART_O_LBAUD))) * 8U);

    //
    // Get the parity, data length, and number of stop bits.
    //
    *config = HWREGH(base + UART_O_CCR) & (UART_CONFIG_PAR_MASK |
                                          UART_CONFIG_STOP_MASK |
                                          UART_CONFIG_WLEN_MASK);
}

//*****************************************************************************
//
//! Enables transmitting and receiving.
//!
//! \param base is the base address of the UART port.
//!
//! Enables UART by taking UART out of the software reset. Sets the TXENA, and
//! RXENA bits which enables transmit and receive.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable RX, TX, and the UART.
    //
    HWREGH(base + UART_O_CTL1) |= (UART_CTL1_TXENA | UART_CTL1_RXENA |
                                  UART_CTL1_SWRESET);
}

//*****************************************************************************
//
//! Disables transmitting and receiving.
//!
//! \param base is the base address of the UART port.
//!
//! Clears the UARTEN, TXE, and RXE bits. The user should ensure that all the
//! data has been sent before disable the module during transmission.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable the FIFO.
    //
    HWREGH(base + UART_O_FFTX) &= ~(UART_FFTX_UARTFFENA);

    //
    // Disable the UART.
    //
    HWREGH(base + UART_O_CTL1) &= ~(UART_CTL1_TXENA | UART_CTL1_RXENA);
}

//*****************************************************************************
//
//! Enables transmitting.
//!
//! \param base is the base address of the UART port.
//!
//! Enables UART by taking UART out of the software reset. Sets the TXENA bit
//! which enables transmit.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableTxModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable TX and the UART.
    //
    HWREGH(base + UART_O_CTL1) |= (UART_CTL1_TXENA | UART_CTL1_SWRESET);
}

//*****************************************************************************
//
//! Disables transmitting.
//!
//! \param base is the base address of the UART port.
//!
//! Disables UART by taking UART out of the software reset. Clears the TXENA bit
//! which disables transmit.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableTxModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable TX.
    //
    HWREGH(base + UART_O_CTL1) &= ~UART_CTL1_TXENA;
}

//*****************************************************************************
//
//! Enables receiving.
//!
//! \param base is the base address of the UART port.
//!
//! Enables UART by taking UART out of the software reset. Sets the RXENA bit
//! which enables receive.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableRxModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable RX and the UART.
    //
    HWREGH(base + UART_O_CTL1) |= (UART_CTL1_RXENA | UART_CTL1_SWRESET);
}

//*****************************************************************************
//
//! Disables receiving.
//!
//! \param base is the base address of the UART port.
//!
//! Disables UART by taking UART out of the software reset. Clears the RXENA bit
//! which disables receive.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableRxModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable RX.
    //
    HWREGH(base + UART_O_CTL1) &= ~UART_CTL1_RXENA;
}

//*****************************************************************************
//
//! Enables UART receive DMA.
//!
//! \param base is the base address of the UART port.
//!
//! Sets the RXDMAENA bit in the UARTCTL1 register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableRxDMA(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable RX DMA.
    //
    HWREGH(base + UART_O_CTL1) |= UART_CTL1_RXDMAENA;
}

//*****************************************************************************
//
//! Disables UART receive DMA.
//!
//! \param base is the base address of the UART port.
//!
//! Clears the RXDMAENA bit in the UARTCTL1 register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableRxDMA(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable RX DMA.
    //
    HWREGH(base + UART_O_CTL1) &= ~UART_CTL1_RXDMAENA;
}

//*****************************************************************************
//
//! Enables UART transmit DMA.
//!
//! \param base is the base address of the UART port.
//!
//! Sets the TXDMAENA bit in the UARTCTL1 register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableTxDMA(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable TX DMA.
    //
    HWREGH(base + UART_O_CTL1) |= UART_CTL1_TXDMAENA;
}

//*****************************************************************************
//
//! Disables UART transmit DMA.
//!
//! \param base is the base address of the UART port.
//!
//! Clears the TXDMAENA bit in the UARTCTL1 register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableTxDMA(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable TX DMA.
    //
    HWREGH(base + UART_O_CTL1) &= ~UART_CTL1_TXDMAENA;
}

//*****************************************************************************
//
//! Enables Sleep Mode
//!
//! \param base is the base address of the UART port.
//!
//! Enables the sleep mode in UART by setting the SLEEP bit in UARTCTL1 register
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableSleepMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Set sleep bit
    //
    HWREGH(base + UART_O_CTL1) |= UART_CTL1_SLEEP;
}

//*****************************************************************************
//
//! Disables Sleep Mode
//!
//! \param base is the base address of the UART port.
//!
//! Disables the sleep mode in UART by clearing the SLEEP bit in UARTCTL1 register
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableSleepMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Clear sleep bit
    //
    HWREGH(base + UART_O_CTL1) &= ~UART_CTL1_SLEEP;
}

//*****************************************************************************
//
//! Enables the transmit and receive FIFOs.
//!
//! \param base is the base address of the UART port.
//!
//! This functions enables the transmit and receive FIFOs in the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable the FIFO.
    //
    HWREGH(base + UART_O_FFTX) |= UART_FFTX_UARTRST;
    HWREGH(base + UART_O_FFTX) |= UART_FFTX_UARTFFENA | UART_FFTX_TXFIFORESET;
    HWREGH(base + UART_O_FFRX) |= UART_FFRX_RXFIFORESET;
}

//*****************************************************************************
//
//! Disables the transmit and receive FIFOs.
//!
//! \param base is the base address of the UART port.
//!
//! This functions disables the transmit and receive FIFOs in the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable the FIFO.
    //
    HWREGH(base + UART_O_FFTX) &= ~UART_FFTX_UARTFFENA;
}

//*****************************************************************************
//
//! Determines if the FIFO enhancement is enabled.
//!
//! \param base is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not the FIFO enhancement
//! is enabled.
//!
//! \return Returns \b true if the FIFO enhancement is enabled or \b false
//! if the FIFO enhancement is disabled.
//
//*****************************************************************************
static inline bool
UART_isFIFOEnabled(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return true if the FIFO is enabled and false if it is disabled.
    //
    return(((HWREGH(base + UART_O_FFTX) & UART_FFTX_UARTFFENA) ==
            UART_FFTX_UARTFFENA) ? true : false);
}

//*****************************************************************************
//
//! Resets the receive FIFO.
//!
//! \param base is the base address of the UART port.
//!
//! This functions resets the receive FIFO of the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_resetRxFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Reset the specified FIFO.
    //
    HWREGH(base + UART_O_FFRX) &= ~UART_FFRX_RXFIFORESET;
    HWREGH(base + UART_O_FFRX) |= UART_FFRX_RXFIFORESET;
}

//*****************************************************************************
//
//! Resets the transmit FIFO.
//!
//! \param base is the base address of the UART port.
//!
//! This functions resets the transmit FIFO of the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_resetTxFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Reset the specified FIFO.
    //
    HWREGH(base + UART_O_FFTX) &= ~UART_FFTX_TXFIFORESET;
    HWREGH(base + UART_O_FFTX) |= UART_FFTX_TXFIFORESET;
}

//*****************************************************************************
//
//! Resets the UART Transmit and Receive Channels
//!
//! \param base is the base address of the UART port.
//!
//! This functions resets transmit and receive channels in the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_resetChannels(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Reset the Tx and Rx Channels
    //
    HWREGH(base + UART_O_FFTX) &= ~UART_FFTX_UARTRST;
    HWREGH(base + UART_O_FFTX) |= UART_FFTX_UARTRST;
}

//*****************************************************************************
//
//! Determines if there are any characters in the receive buffer when the
//! FIFO enhancement is not enabled.
//!
//! \param base is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is data
//! available in the receive buffer.
//!
//! \return Returns \b true if there is data in the receive buffer or \b false
//! if there is no data in the receive buffer.
//
//*****************************************************************************
static inline bool
UART_isDataAvailableNonFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the availability of characters with FIFO disabled.
    //
    return(((HWREGH(base + UART_O_RXST) & UART_RXST_RXRDY) ==
            UART_RXST_RXRDY) ? true : false);
}

//*****************************************************************************
//
//! Determines if there is any space in the transmit buffer when the FIFO
//! enhancement is not enabled.
//!
//! \param base is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is space
//! available in the transmit buffer when not using the FIFO enhancement.
//!
//! \return Returns \b true if there is space available in the transmit buffer
//! or \b false if there is no space available in the transmit buffer.
//
//*****************************************************************************
static inline bool
UART_isSpaceAvailableNonFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the availability of space.
    //
    return(((HWREGH(base + UART_O_CTL2) & UART_CTL2_TXRDY) ==
            UART_CTL2_TXRDY) ? true : false);
}

//*****************************************************************************
//
//! Get the transmit FIFO status
//!
//! \param base is the base address of the UART port.
//!
//! This functions gets the current number of words in the transmit FIFO.
//!
//! \return Returns the current number of words in the transmit FIFO specified
//! as one of the following:
//! \b UART_FIFO_TX0, \b UART_FIFO_TX1, \b UART_FIFO_TX2, \b UART_FIFO_TX3
//! \b UART_FIFO_TX4, ..., or \b UART_FIFO_TX16
//
//*****************************************************************************
static inline UART_TxFIFOLevel
UART_getTxFIFOStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Get the current FIFO status
    //
    return((UART_TxFIFOLevel)((HWREGH(base + UART_O_FFTX) & UART_FFTX_TXFFST_M) >>
                             UART_FFTX_TXFFST_S));
}

//*****************************************************************************
//
//! Get the receive FIFO status
//!
//! \param base is the base address of the UART port.
//!
//! This functions gets the current number of words in the receive FIFO.
//!
//! \return Returns the current number of words in the receive FIFO specified
//! as one of the following:
//! \b UART_FIFO_RX0, \b UART_FIFO_RX1, \b UART_FIFO_RX2, \b UART_FIFO_RX3
//! \b UART_FIFO_RX4, ..., or \b UART_FIFO_RX16
//
//*****************************************************************************
static inline UART_RxFIFOLevel
UART_getRxFIFOStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Get the current FIFO status
    //
    return((UART_RxFIFOLevel)((HWREGH(base + UART_O_FFRX) & UART_FFRX_RXFFST_M) >>
                             UART_FFRX_RXFFST_S));
}

//*****************************************************************************
//
//! Determines whether the UART transmitter is busy or not.
//!
//! \param base is the base address of the UART port.
//!
//! Allows the caller to determine whether all transmitted bytes have cleared
//! the transmitter hardware when the FIFO is not enabled.  When the FIFO is
//! enabled, this function allows the caller to determine whether there is any
//! data in the FIFO.
//!
//! Without the FIFO enabled, if \b false is returned, the transmit buffer and
//! shift registers are empty and the transmitter is not busy. With the FIFO
//! enabled, if \b false is returned, the FIFO is empty.  This does not
//! necessarily mean that the transmitter is not busy.  The empty FIFO does not
//! reflect the status of the transmitter shift register. The FIFO may be empty
//! while the transmitter is still transmitting data.
//!
//! \return Returns \b true if the UART is transmitting or \b false if
//! transmissions are complete.
//
//*****************************************************************************
static inline bool
UART_isTransmitterBusy(uint32_t base)
{
    //
    // Check the argument.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Check if FIFO enhancement is enabled.
    //
    if(UART_isFIFOEnabled(base))
    {
        //
        // With FIFO enhancement, determine if the UART is busy.
        //
        return(((HWREGH(base + UART_O_FFTX) & UART_FFTX_TXFFST_M) !=
                 0) ? true : false);
    }
    else
    {
        //
        // Without FIFO enhancement, determine if the UART is busy.
        // Check if the transmit buffer and shift register empty.
        //
        return(((HWREGH(base + UART_O_CTL2) & UART_CTL2_TXEMPTY) ==
                UART_CTL2_TXEMPTY) ? false : true);
    }
}

//*****************************************************************************
//
//! Waits to send a character from the specified port when the FIFO enhancement
//! is enabled.
//!
//! \param base is the base address of the UART port.
//! \param data is the character to be transmitted.
//!
//! Sends the character \e data to the transmit buffer for the specified port.
//! If there is no space available in the transmit FIFO, this function waits
//! until there is space available before returning. \e data is a uint16_t but
//! only 8 bits are written to the UART port.  UART only transmits 8 bit
//! characters.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_writeCharBlockingFIFO(uint32_t base, uint8_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Wait until space is available in the transmit FIFO.
    //
    while(UART_getTxFIFOStatus(base) == UART_FIFO_TX16)
    {
    }

    //
    // Send a char.
    //
    HWREGH(base + UART_O_TXBUF) = data;
}

//*****************************************************************************
//
//! Waits to send a character from the specified port.
//!
//! \param base is the base address of the UART port.
//! \param data is the character to be transmitted.
//!
//! Sends the character \e data to the transmit buffer for the specified port.
//! If there is no space available in the transmit buffer, or the transmit
//! FIFO if it is enabled, this function waits until there is space available
//! before returning. \e data is a uint16_t but only 8 bits are written to the
//! UART port.  UART only transmits 8 bit characters.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_writeCharBlockingNonFIFO(uint32_t base, uint8_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Wait until space is available in the transmit buffer.
    //
    while(!UART_isSpaceAvailableNonFIFO(base))
    {
    }

    //
    // Send a char.
    //
    HWREGH(base + UART_O_TXBUF) = data;
}

//*****************************************************************************
//
//! Sends a character to the specified port.
//!
//! \param base is the base address of the UART port.
//! \param data is the character to be transmitted.
//!
//! Writes the character \e data to the transmit buffer for the specified port.
//! This function does not block and only writes to the transmit buffer.
//! The user should use UART_isSpaceAvailableNonFIFO() or UART_getTxFIFOStatus()
//! to determine if the transmit buffer or FIFO have space available.
//! \e data is a uint16_t but only 8 bits are written to the UART port.  UART
//! only transmits 8 bit characters.
//!
//! This function replaces the original UARTCharNonBlockingPut() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_writeCharNonBlocking(uint32_t base, uint8_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Send a char.
    //
    HWREGH(base + UART_O_TXBUF) = data;
}

//*****************************************************************************
//
//! Gets current receiver status flags.
//!
//! \param base is the base address of the UART port.
//!
//! This function returns the current receiver status flags.  The returned
//! error flags are equivalent to the error bits returned via the previous
//! reading or receiving of a character with the exception that the overrun
//! error is set immediately the overrun occurs rather than when a character
//! is next read.
//!
//! \return Returns a bitwise OR combination of the receiver status flags,
//! \b UART_RXSTATUS_WAKE, \b UART_RXSTATUS_PARITY, \b UART_RXSTATUS_OVERRUN,
//! \b UART_RXSTATUS_FRAMING, \b UART_RXSTATUS_BREAK, \b UART_RXSTATUS_READY,
//! and \b UART_RXSTATUS_ERROR.
//
//*****************************************************************************
static inline uint16_t
UART_getRxStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the current value of the receive status register.
    //
    return(HWREGH(base + UART_O_RXST));
}

//*****************************************************************************
//
//! Waits for a character from the specified port when the FIFO enhancement
//! is enabled.
//!
//! \param base is the base address of the UART port.
//!
//! Gets a character from the receive FIFO for the specified port.  If there
//! are no characters available, this function waits until a character is
//! received before returning. Returns immediately in case of Error.
//!
//! \return Returns the character read from the specified port as \e uint16_t
//!         or 0x0 in case of Error. The application must use
//!         UART_getRxStatus() API to check if some error occurred before
//!         consuming the data
//
//*****************************************************************************
static inline uint16_t
UART_readCharBlockingFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Wait until a character is available in the receive FIFO.
    //
    while(UART_getRxFIFOStatus(base) == UART_FIFO_RX0)
    {
        //
        //If there is any error return
        //
        if((UART_getRxStatus(base) & UART_RXSTATUS_ERROR) != 0U)
        {
            return(0U);
        }
    }

    //
    // Return the character from the receive buffer.
    //
    return((uint16_t)(HWREGH(base + UART_O_RXBUF) & UART_RXBUF_SAR_M));
}

//*****************************************************************************
//
//! Waits for a character from the specified port when the FIFO enhancement
//! is not enabled.
//!
//! \param base is the base address of the UART port.
//!
//! Gets a character from the receive buffer for the specified port.  If there
//! is no characters available, this function waits until a character is
//! received before returning.
//!
//! \return Returns the character read from the specified port as \e uint16_t.
//
//*****************************************************************************
static inline uint16_t
UART_readCharBlockingNonFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Wait until a character is available in the receive FIFO.
    //
    while(!UART_isDataAvailableNonFIFO(base))
    {
    }

    //
    // Return the character from the receive buffer.
    //
    return((uint16_t)(HWREGH(base + UART_O_RXBUF) & UART_RXBUF_SAR_M));
}

//*****************************************************************************
//
//! Receives a character from the specified port.
//!
//! \param base is the base address of the UART port.
//!
//! Gets a character from the receive buffer for the specified port. This
//! function does not block and only reads the receive buffer.  The user should
//! use UART_isDataAvailableNonFIFO() or UART_getRxFIFOStatus() to determine if
//! the receive buffer or FIFO have data available.
//!
//! This function replaces the original UARTCharNonBlockingGet() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
//!
//! \return Returns \e uin16_t which is read from the receive buffer.
//
//*****************************************************************************
static inline uint8_t UART_readCharNonBlocking(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the character from the receive buffer.
    //
    return((uint8_t)(HWREGH(base + UART_O_RXBUF) & UART_RXBUF_SAR_M));
}

//*****************************************************************************
//
//! Performs a software reset of the UART and Clears all reported receiver
//! status flags.
//!
//! \param base is the base address of the UART port.
//!
//! This function performs a software reset of the UART port.  It affects the
//! operating flags of the UART, but it neither affects the configuration bits
//! nor restores the reset values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_performSoftwareReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // To clear all errors a sw reset of the module is required
    //
    HWREGH(base + UART_O_CTL1) &= ~UART_CTL1_SWRESET;
    HWREGH(base + UART_O_CTL1) |= UART_CTL1_SWRESET;
}

//*****************************************************************************
//
//! Enables Loop Back Test Mode
//!
//! \param base is the base address of the UART port.
//!
//! Enables the loop back test mode where the Tx pin is internally connected
//! to the Rx pin.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Set the loop back mode.
    //
    HWREGH(base + UART_O_CCR) |= UART_CCR_LOOPBKENA;
}

//*****************************************************************************
//
//! Disables Loop Back Test Mode
//!
//! \param base is the base address of the UART port.
//!
//! Disables the loop back test mode where the Tx pin is no longer internally
//! connected to the Rx pin.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Clear the loop back mode.
    //
    HWREGH(base + UART_O_CCR) &= ~UART_CCR_LOOPBKENA;
}

//*****************************************************************************
//
//! Get the receive FIFO Overflow flag status
//!
//! \param base is the base address of the UART port.
//!
//! This functions gets the receive FIFO overflow flag status.
//!
//! \return Returns \b true if overflow has occurred, else returned \b false if
//! an overflow hasn't occurred.
//
//*****************************************************************************
static inline bool
UART_getOverflowStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the current FIFO overflow status
    //
    return((HWREGH(base + UART_O_FFRX) & UART_FFRX_RXFFOVF) == UART_FFRX_RXFFOVF);
}

//*****************************************************************************
//
//! Clear the receive FIFO Overflow flag status
//!
//! \param base is the base address of the UART port.
//!
//! This functions clears the receive FIFO overflow flag status.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_clearOverflowStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Clear the current FIFO overflow status
    //
    HWREGH(base + UART_O_FFRX) |= UART_FFRX_RXFFOVRCLR;
}

//*****************************************************************************
//
//! Sets the configuration of a UART.
//!
//! \param base is the base address of the UART port.
//! \param lspclkHz is the rate of the clock supplied to the UART module.  This
//! is the LSPCLK.
//! \param baud is the desired baud rate.
//! \param config is the data format for the port (number of data bits,
//! number of stop bits, and parity).
//!
//! This function configures the UART for operation in the specified data
//! format.  The baud rate is provided in the \e baud parameter and the data
//! format in the \e config parameter.
//!
//! The \e config parameter is the bitwise OR of three values: the number of
//! data bits, the number of stop bits, and the parity.  \b UART_CONFIG_WLEN_8,
//! \b UART_CONFIG_WLEN_7, \b UART_CONFIG_WLEN_6, \b UART_CONFIG_WLEN_5,
//! \b UART_CONFIG_WLEN_4, \b UART_CONFIG_WLEN_3, \b UART_CONFIG_WLEN_2, and
//! \b UART_CONFIG_WLEN_1. Select from eight to one data bits per byte
//! (respectively).
//! \b UART_CONFIG_STOP_ONE and \b UART_CONFIG_STOP_TWO select one or two stop
//! bits (respectively).  \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,
//! \b UART_CONFIG_PAR_ODD, select the parity mode (no parity bit, even parity
//! bit, odd parity bit respectively).
//!
//! The peripheral clock is the low speed peripheral clock.  This will be
//! the value returned by SysCtl_getLowSpeedClock(), or it can be explicitly
//! hard coded if it is constant and known (to save the code/execution overhead
//! of a call to SysCtl_getLowSpeedClock()).
//!
//! A baud rate divider (BRR) is used in this function to calculate the
//! baud rate. The value of BRR is calculated in float and type casted as int
//! to be fed in the \b UARTHBAUD and  \b UARTLBAUD registers. This conversion
//! brings an error in the calculated baud rate and the requested. Error will
//! be significant when operating at higher baud rates. The error is due to
//! lower BRR integer value granularity at higher baud rates.
//!
//! \return None.
//
//*****************************************************************************
extern void
UART_setConfig(uint32_t base, uint32_t lspclkHz, uint32_t baud,
              uint32_t config);

//*****************************************************************************
//
//! Waits to send an array of characters from the specified port.
//!
//! \param base is the base address of the UART port.
//! \param array is the address of the array of characters to be transmitted.
//!   It is pointer to the array of characters to be transmitted.
//! \param length is the length of the array, or number of characters in the
//!   array to be transmitted.
//!
//! Sends the number of characters specified by \e length, starting at the
//! address \e array, out of the transmit buffer for the specified port.
//! If there is no space available in the transmit buffer, or the transmit
//! FIFO if it is enabled, this function waits until there is space available
//! and \e length number of characters are transmitted before returning.
//! \e array is a pointer to uint16_ts but only the least significant 8 bits
//! are written to the UART port.  UART only transmits 8 bit characters.
//!
//! \return None.
//
//*****************************************************************************
extern void
UART_writeCharArray(uint32_t base, const uint8_t * const array,
                   uint16_t length);

//*****************************************************************************
//
//! Waits to receive an array of characters from the specified port.
//!
//! \param base is the base address of the UART port.
//! \param array is the address of the array of characters to be received.
//!   It is a pointer to the array of characters to be received.
//! \param length is the length of the array, or number of characters in the
//!   array to be received.
//!
//! Receives an array of characters from the receive buffer for the specified
//! port, and stores them as an array of characters starting at address
//! \e array.  This function waits until the \e length number of characters are
//! received before returning.
//!
//! \return None.
//
//*****************************************************************************
extern void
UART_readCharArray(uint32_t base, uint8_t * const array, uint16_t length); 

//*****************************************************************************
//
//! Enables individual UART interrupt sources.
//!
//! \param base is the base address of the UART port.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e intFlags parameter is the bitwise OR of any of the following:
//!
//! - \b UART_INT_RXERR      - RXERR Interrupt
//! - \b UART_INT_RXRDY_BRKDT - RXRDY/BRKDT Interrupt
//! - \b UART_INT_TXRDY      - TXRDY Interrupt
//! - \b UART_INT_TXFF       - TX FIFO Level Interrupt
//! - \b UART_INT_RXFF       - RX FIFO Level Interrupt
//! - \b UART_INT_FE         - Frame Error
//! - \b UART_INT_OE         - Overrun Error
//! - \b UART_INT_PE         - Parity Error
//!
//! \return None.
//
//*****************************************************************************
extern void
UART_enableInterrupt(uint32_t base, uint32_t intFlags);

//*****************************************************************************
//
//! Disables individual UART interrupt sources.
//!
//! \param base is the base address of the UART port.
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//!
//! Disables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e intFlags parameter has the same definition as the \e intFlags
//! parameter to UART_enableInterrupt().
//!
//! \return None.
//
//*****************************************************************************
extern void
UART_disableInterrupt(uint32_t base, uint32_t intFlags);

//*****************************************************************************
//
//! Gets the current interrupt status.
//!
//! \param base is the base address of the UART port.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! values described in UART_enableInterrupt().
//
//*****************************************************************************
extern uint32_t
UART_getInterruptStatus(uint32_t base);

//*****************************************************************************
//
//! Clears UART interrupt sources.
//!
//! \param base is the base address of the UART port.
//! \param intFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified UART interrupt sources are cleared, so that they no longer
//! assert.  This function must be called in the interrupt handler to keep the
//! interrupt from being recognized again immediately upon exit.
//!
//! The \e intFlags parameter has the same definition as the \e intFlags
//! parameter to UART_enableInterrupt().
//!
//! \return None.
//
//*****************************************************************************
extern void
UART_clearInterruptStatus(uint32_t base, uint32_t intFlags);

//*****************************************************************************
//
//! Sets UART Baud rate.
//!
//! \param base is the base address of the UART port.
//! \param lspclkHz is the rate of the clock supplied to the UART module.  This
//! is the LSPCLK.
//! \param baud is the desired baud rate.
//!
//! This function configures the UART for operation in the specified baud rate
//! The baud rate is provided in the \e baud parameter.
//!
//! The peripheral clock is the low speed peripheral clock.  This will be
//! the value returned by SysCtl_getLowSpeedClock()
//!
//! \return None.
//
//*****************************************************************************
extern void
UART_setBaud(uint32_t base, uint32_t lspclkHz, uint32_t baud);

//*****************************************************************************
//
//! Sets the UART TXWAKE flag
//!
//! \param base is the base address of the UART port.
//!
//! This function sets the TXWAKE flag bit to indicate that the next frame
//! is an address frame.
//! TXWAKE bit controls selection of data-transmit feature based on
//! which mode is selected from idle-line and address-bit.
//!
//! \return None.
//
//*****************************************************************************
extern void
UART_setWakeFlag(uint32_t base);

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

#endif //  UART_H
