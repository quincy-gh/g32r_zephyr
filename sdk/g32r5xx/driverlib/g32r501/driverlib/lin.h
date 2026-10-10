//###########################################################################
//
// FILE:    lin.h
//
// TITLE:   G32R501 LIN driver.
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
// 1. Partial comments, macro definitions, register names, enum names, function names
//
//###########################################################################
#ifndef LIN_H
#define LIN_H

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

#ifdef __G32R501XX__

//*****************************************************************************
//
//! \addtogroup lin_api LIN
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_lin.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
//
// The IO DFT Enable Key
//
#define LIN_IO_DFT_KEY       (0xAU)      //!< LIN IO DFT Key

//
// LIN Wakeup Signal Key
//
#define LIN_WAKEUP_KEY       (0xF0U)     //!< LIN Wakeup Key

//
// LIN Parity ID Masks
//
#define LIN_ID0              (0x1U)      //!< LIN Parity ID0 Mask
#define LIN_ID1              (0x2U)      //!< LIN Parity ID1 Mask
#define LIN_ID2              (0x4U)      //!< LIN Parity ID2 Mask
#define LIN_ID3              (0x8U)      //!< LIN Parity ID3 Mask
#define LIN_ID4              (0x10U)     //!< LIN Parity ID4 Mask
#define LIN_ID5              (0x20U)     //!< LIN Parity ID5 Mask

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
// Definitions for the intFlags parameter of LIN_enableInterrupt(),
// LIN_disableInterrupt(), LIN_clearInterruptStatus(),
// LIN_setInterruptLevel0() and LIN_setInterruptLevel1().
//
//*****************************************************************************
#define LIN_INT_WAKEUP       (0x00000002U) //!< Wakeup
#define LIN_INT_TO           (0x00000010U) //!< Time out
#define LIN_INT_TOAWUS       (0x00000040U) //!< Time out after wakeup signal
#define LIN_INT_TOA3WUS      (0x00000080U) //!< Time out after 3 wakeup signals
#define LIN_INT_TX           (0x00000100U) //!< Transmit buffer ready
#define LIN_INT_RX           (0x00000200U) //!< Receive buffer ready
#define LIN_INT_ID           (0x00002000U) //!< Received matching identifier
#define LIN_INT_PE           (0x01000000U) //!< Parity error
#define LIN_INT_OE           (0x02000000U) //!< Overrun error
#define LIN_INT_FE           (0x04000000U) //!< Framing error
#define LIN_INT_NRE          (0x08000000U) //!< No response error
#define LIN_INT_ISFE         (0x10000000U) //!< Inconsistent sync field error
#define LIN_INT_CE           (0x20000000U) //!< Checksum error
#define LIN_INT_PBE          (0x40000000U) //!< Physical bus error
#define LIN_INT_BE           (0x80000000U) //!< Bit error
#define LIN_INT_ALL          (0xFF0023D2U) //!< All interrupts

//*****************************************************************************
//
// Definitions for the return value of LIN_getInterruptStatus().
//
//*****************************************************************************
#define LIN_FLAG_BREAK      (LIN_LINFLG_BRKDETFLG)    //!< Break-Detect
#define LIN_FLAG_WAKEUP     (LIN_LINFLG_WUPFLG)       //!< Wakeup
#define LIN_FLAG_IDLE       (LIN_LINFLG_RXIDLEFLG)    //!< Bus Idle
#define LIN_FLAG_BUSY       (LIN_LINFLG_BUSYFLG)      //!< Busy
#define LIN_FLAG_TO         (LIN_LINFLG_LINIDLEFLG)   //!< Time out
#define LIN_FLAG_TOAWUS     (LIN_LINFLG_TOWUPSFLG)    //!< Time out after wakeup
                                                      //!< signal
#define LIN_FLAG_TOA3WUS    (LIN_LINFLG_TO3WUPSFLG)   //!< Time out after 3 wakeup
                                                      //!< signals
#define LIN_FLAG_TXRDY      (LIN_LINFLG_TXBRDYFLG)    //!< Transmit Buffer ready
#define LIN_FLAG_RXRDY      (LIN_LINFLG_RXRDYFLG)     //!< Receive Buffer ready
#define LIN_FLAG_TXWAKE     (LIN_LINFLG_TXWUPSEL)     //!< Transmitter Wakeup
                                                      //!< Method Select
#define LIN_FLAG_TXEMPTY    (LIN_LINFLG_TXEFLG)       //!< Transmitter Empty
#define LIN_FLAG_RXWAKE     (LIN_LINFLG_RXWUPSEL)     //!< Receiver Wakeup detect
#define LIN_FLAG_RXID       (LIN_LINFLG_RXIDFLG)      //!< ID on Receive
#define LIN_FLAG_TXID       (LIN_LINFLG_TXIDFLG)      //!< ID on Transmit
#define LIN_FLAG_PE         (LIN_LINFLG_PEFLG)        //!< Parity Error
#define LIN_FLAG_OE         (LIN_LINFLG_OREFLG)       //!< Overrun Error
#define LIN_FLAG_FE         (LIN_LINFLG_FEFLG)        //!< Framing Error
#define LIN_FLAG_NRE        (LIN_LINFLG_NREFLG)       //!< No-Response Error
#define LIN_FLAG_ISFE       (LIN_LINFLG_ISFEFLG)      //!< Inconsistent Sync Field
                                                      //!< Error
#define LIN_FLAG_CE         (LIN_LINFLG_CSEFLG)       //!< Checksum Error
#define LIN_FLAG_PBE        (LIN_LINFLG_PBEFLG)       //!< Physical Bus Error
#define LIN_FLAG_BE         (LIN_LINFLG_BEFLG)        //!< Bit Error

//*****************************************************************************
//
// Definitions for the return value of LIN_getInterruptLine0Offset() and
// LIN_getInterruptLine1Offset().
//
//*****************************************************************************
#define LIN_VECT_NONE       (0x00)   //!< No Interrupt
#define LIN_VECT_WAKEUP     (0x01)   //!< Wakeup
#define LIN_VECT_ISFE       (0x02)   //!< Inconsistent-sync-field Error
#define LIN_VECT_PE         (0x03)   //!< Parity Error
#define LIN_VECT_ID         (0x04)   //!< ID Interrupt
#define LIN_VECT_PBE        (0x05)   //!< Physical Bus Error
#define LIN_VECT_FE         (0x06)   //!< Frame Error
#define LIN_VECT_BREAK      (0x07)   //!< Break detect
#define LIN_VECT_CE         (0x08)   //!< Checksum Error
#define LIN_VECT_OE         (0x09)   //!< Overrun Error
#define LIN_VECT_BE         (0x0A)   //!< Bit Error
#define LIN_VECT_RX         (0x0B)   //!< Receive Interrupt
#define LIN_VECT_TX         (0x0C)   //!< Transmit Interrupt
#define LIN_VECT_NRE        (0x0D)   //!< No-response Error
#define LIN_VECT_TOAWUS     (0x0E)   //!< Timeout after wakeup signal
#define LIN_VECT_TOA3WUS    (0x0F)   //!< Timeout after 3 wakeup signals
#define LIN_VECT_TO         (0x10)   //!< Timeout (Bus Idle)

//*****************************************************************************
//
// Definitions for the LIN errors parameter of LIN_enableModuleErrors() and
// LIN_disableModuleErrors().
//
//*****************************************************************************
#define LIN_ALL_ERRORS      (0xF0000000U)  //!< All module errors
#define LIN_BIT_ERROR       (0x80000000U)  //!< Bit Error
#define LIN_BUS_ERROR       (0x40000000U)  //!< Physical Bus Error
#define LIN_CHECKSUM_ERROR  (0x20000000U)  //!< Checksum Error
#define LIN_ISF_ERROR       (0x10000000U)  //!< Inconsistent Synch Field Error

//*****************************************************************************
//
// Definitions for the UART errors parameter of LIN_enableUARTModuleErrors() and
// LIN_disableUARTModuleErrors().
//
//*****************************************************************************
#define LIN_UART_ALL_ERRORS      (0x7000000U)   //!< All module errors
#define LIN_UART_FRAME_ERROR     (0x4000000U)   //!< Frame Error
#define LIN_UART_PARITY_ERROR    (0x2000000U)   //!< Parity Error
#define LIN_UART_BREAK_ERROR     (0x1000000U)   //!< Break Detect Error

//*****************************************************************************
//
// Definitions for the intFlags parameter of LIN_enableUARTInterrupt(),
// LIN_disableUARTInterrupt(), LIN_clearUARTInterruptStatus(),
// LIN_setUARTInterruptLevel0() and LIN_setUARTInterruptLevel1().
//
//*****************************************************************************
#define LIN_UART_INT_BREAK       (0x1U)         //!< Break Detect
#define LIN_UART_INT_WAKEUP      (0x2U)         //!< Wakeup
#define LIN_UART_INT_TX          (0x100U)       //!< Transmit Buffer
#define LIN_UART_INT_RX          (0x200U)       //!< Receive Buffer
#define LIN_UART_INT_TX_DMA      (0x10000U)     //!< DMA Transmit
#define LIN_UART_INT_RX_DMA      (0x20000U)     //!< DMA Receive
#define LIN_UART_INT_RX_DMA_ALL  (0x40000U)     //!< DMA Receive All
#define LIN_UART_INT_PARITY      (0x1000000U)   //!< Parity Error
#define LIN_UART_INT_OVERRUN     (0x2000000U)   //!< Overrun Error
#define LIN_UART_INT_FRAME       (0x4000000U)   //!< Framing Error
#define LIN_UART_INT_ALL         (0x7000303U)   //!< All Interrupts

#endif // DOXYGEN_PDF_IGNORE

//*****************************************************************************
//
//! The following are defines for the \e type parameter of the
//! LIN_enableExtLoopback() function.
//
//*****************************************************************************
typedef enum
{
    LIN_LOOPBACK_DIGITAL = 0U,    //!< Digital Loopback Mode
    LIN_LOOPBACK_ANALOG  = 2U     //!< Analog Loopback Mode
} LIN_LoopbackType;

//*****************************************************************************
//
//! The following are defines for the \e path parameter of the
//! LIN_enableExtLoopback() function.
//
//*****************************************************************************
typedef enum
{
    LIN_ANALOG_LOOP_NONE = 0U,    //!< Default path for digital loopback mode
    LIN_ANALOG_LOOP_TX   = 0U,    //!< Analog loopback through transmit pin
    LIN_ANALOG_LOOP_RX   = 1U     //!< Analog loopback through receive pin
} LIN_AnalogLoopback;

//*****************************************************************************
//
//! The following are defines for the \e mode parameter of the
//! LIN_setCommMode() function.
//
//*****************************************************************************
typedef enum
{
    //! Use the length indicated in the LENGTH field of the UARTFORMAT register
    LIN_COMM_LIN_USELENGTHVAL = 0x0000U,

    //! Use ID4 and ID5 to convey the length
    LIN_COMM_LIN_ID4ID5LENCTL = 0x0001U
} LIN_CommMode;

//*****************************************************************************
//
//! The following are defines for the \e mode parameter of the
//! LIN_setUARTCommMode() function.
//
//*****************************************************************************
typedef enum
{
    //! Idle-line mode is used
    LIN_COMM_UART_IDLELINE     = 0x0000U,

    //! Address bit mode is used
    LIN_COMM_UART_ADDRBIT      = 0x0001U
} LIN_UARTCommMode;

//*****************************************************************************
//
//! The following are defines for the \e mode parameter of the LIN_setLINMode()
//! function.
//
//*****************************************************************************
typedef enum
{
    LIN_MODE_LIN_SLAVE        = 0x0000U,    //!< The node is in slave mode
    LIN_MODE_LIN_MASTER       = 0x0020U     //!< The node is in master mode
} LIN_LINMode;

//*****************************************************************************
//
//! The following are defines for the \e line parameter of the
//! LIN_enableGlobalInterrupt(), LIN_disableGlobalInterrupt(),
//! LIN_clearGlobalInterruptStatus(), and LIN_getGlobalInterruptStatus()
//! functions.
//
//*****************************************************************************
typedef enum
{
    LIN_INTERRUPT_LINE0       = 0x0U,    //!< Interrupt line 0
    LIN_INTERRUPT_LINE1       = 0x1U     //!< Interrupt line 1
} LIN_InterruptLine;

//*****************************************************************************
//
//! The following are defines for the \e type parameter of the
//! LIN_setMessageFiltering() function.
//
//*****************************************************************************
typedef enum
{
    LIN_MSG_FILTER_IDBYTE  = 0x0U,    //!< LIN Message ID Byte Filtering
    LIN_MSG_FILTER_IDSLAVE = 0x1U     //!< Slave Task ID Byte Filtering
} LIN_MessageFilter;

//*****************************************************************************
//
//! The following are defines for the \e type parameter of the
//! LIN_setChecksumType() function.
//
//*****************************************************************************
typedef enum
{
    LIN_CHECKSUM_CLASSIC  = 0x0U,    //!< Checksum Classic
    LIN_CHECKSUM_ENHANCED = 0x1U     //!< Checksum Enhanced
} LIN_ChecksumType;

//*****************************************************************************
//
//! The following are defines for the \e mode parameter of the
//! LIN_setDebugSuspendMode() function.
//
//*****************************************************************************
typedef enum
{
    LIN_DEBUG_FROZEN   = 0x0U,    //!< Freeze module during debug
    LIN_DEBUG_COMPLETE = 0x1U     //!< Complete Tx/Rx before Freezing
} LIN_DebugMode;

//*****************************************************************************
//
//! The following are defines for the \e mask parameter of the
//! LIN_setPinSampleMask() function.
//
//*****************************************************************************
typedef enum
{
    //! No Pin Mask
    LIN_PINMASK_NONE         = 0x0U,

    //! Invert Tx Pin value at T-bit center
    LIN_PINMASK_CENTER       = 0x1U,

    //! Invert Tx Pin value at T-bit center + SCLK
    LIN_PINMASK_CENTER_SCLK  = 0x2U,

    //! Invert Tx Pin value at T-bit center + 2 SCLK
    LIN_PINMASK_CENTER_2SCLK = 0x3U
} LIN_PinSampleMask;

//*****************************************************************************
//
//! The following are defines for the \e parity parameter of the
//! LIN_enableUARTParity() function.
//
//*****************************************************************************
typedef enum
{
    LIN_UART_PAR_ODD   = 0x0U,  //!< Odd parity
    LIN_UART_PAR_EVEN  = 0x1U   //!< Even parity
} LIN_UARTParityType;

//*****************************************************************************
//
//! The following are defines for the \e number parameter of the
//! LIN_setUARTStopBits() function.
//
//*****************************************************************************
typedef enum
{
    LIN_UART_STOP_ONE   = 0x0U,  //!< Use One Stop bit
    LIN_UART_STOP_TWO   = 0x1U   //!< Use Two Stop bits
} LIN_UARTStopBits;

//*****************************************************************************
//
//! The following are defines for the \e pin parameter of the
//! LIN_getPinStatus() function.
//
//*****************************************************************************
typedef enum
{
    LIN_PINTYPE_TX = 0x4U,    //!< Transmit Pin
    LIN_PINTYPE_RX = 0x2U     //!< Receive Pin
} LIN_PinType;

//*****************************************************************************
//
// Prototypes for the LIN mode APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//!
//! Checks a LIN base address.
//!
//! \param base is the base address of the LIN controller.
//!
//! This function determines if a LIN controller base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
LIN_isBaseValid(uint32_t base)
{
    return(
           (base == LINA_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Sets the LIN mode
//!
//! \param base is the LIN module base address
//! \param mode is the desired mode (slave or master)
//!
//! In LIN mode only, this function sets the mode of the LIN mode to either
//! slave or master. The \e mode parameter should be passed a value of
//! \b LIN_MODE_LIN_SLAVE or \b LIN_MODE_LIN_MASTER to configure the mode of
//! the LIN module specified by \e base.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setLINMode(uint32_t base, LIN_LINMode mode)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Write the LIN mode to the appropriate register.
    //
    WRPRT_DISABLE;

    HWREGH(base + LIN_O_LINGCTRL1) = (HWREGH(base + LIN_O_LINGCTRL1) &
                                   ~LIN_LINGCTRL1_CLK_MSCFG) | LIN_LINGCTRL1_LINEN | (uint16_t)mode;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Maximum Baud Rate Prescaler
//!
//! \param base is the LIN module base address
//! \param clock is the device system clock (Hz)
//!
//! In LIN mode only, this function is used to set the maximum baud rate
//! prescaler used during synchronization phase of a slave module if the
//! ADAPT bit is set. The maximum baud rate prescaler is used by the wakeup
//! and idle timer counters for a constant 4 second expiration time relative
//! to a 20kHz rate.
//!
//! \note Use LIN_enableAutomaticBaudrate() to set the ADAPT bit and enable
//! automatic bit rate mod detection.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setMaximumBaudRate(uint32_t base, uint32_t clock)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Calculate maximum baud rate prescaler
    //
    HWREGH(base + LIN_O_LINMBRPSC) = (uint16_t)(clock / 20000U);
}

//*****************************************************************************
//
//! Set Message filtering Type
//!
//! \param base is the LIN module base address
//! \param type is the mask filtering comparison type
//!
//! In LIN mode only, this function sets the message filtering type. The \e
//! type parameter can be one of the following values:
//! - \b LIN_MSG_FILTER_IDBYTE   - Filtering uses LIN message ID Byte
//! - \b LIN_MSG_FILTER_IDSLAVE  - Filtering uses the Slave Task ID Byte
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setMessageFiltering(uint32_t base, LIN_MessageFilter type)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Sets the message filtering type
    //
    if(type == LIN_MSG_FILTER_IDBYTE)
    {
        HWREGH(base + LIN_O_LINGCTRL1) &= ~LIN_LINGCTRL1_HGENCTRL;
    }
    else
    {
        HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_HGENCTRL;
    }
}

//*****************************************************************************
//
//! Enable Parity mode.
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function enables the parity check.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableParity(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Enable the parity mode
    //
    HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_PARITYEN;
}

//*****************************************************************************
//
//! Disable Parity mode.
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function disables the parity check.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableParity(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Disable the parity mode
    //
    HWREGH(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_PARITYEN);
}

//*****************************************************************************
//
//! Generate Parity Identifier
//! \param identifier is the LIN header ID byte
//!
//! In LIN mode only, this function generates the identifier parity bits and
//! appends them to the identifier.
//!
//! \note An ID must be generated with parity before header generation in
//! LIN master mode when parity is enabled using the function
//! LIN_enableParity().
//!
//! \return Returns the identifier appended with parity bits.
//
//*****************************************************************************
static inline uint16_t
LIN_generateParityID(uint16_t identifier)
{

    uint16_t p0, p1, parityIdentifier;

    //
    // Calculate parity bits and generate updated identifier
    //
    p0 = ((identifier & LIN_ID0) ^ ((identifier & LIN_ID1) >> 1U) ^
          ((identifier & LIN_ID2) >> 2U) ^ ((identifier & LIN_ID4) >> 4U));
    p1 = !(((identifier & LIN_ID1) >> 1U) ^ ((identifier & LIN_ID3) >> 3U) ^
           ((identifier & LIN_ID4) >> 4U) ^ ((identifier & LIN_ID5) >> 5U));
    parityIdentifier = identifier | ((p0 << 6U) | (p1 << 7U));

    return(parityIdentifier);
}

//*****************************************************************************
//
//! Set ID Byte
//!
//! \param base is the LIN module base address
//! \param identifier is the LIN header ID byte
//!
//! In LIN mode only, this function sets the message ID byte. In master mode,
//! writing to this ID initiates a header transmission. In slave task, this
//! ID is used for message filtering when HGENCTRL is 0.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setIDByte(uint32_t base, uint16_t identifier)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREGH(base + LIN_O_LINID) = (HWREGH(base + LIN_O_LINID) & ~(LIN_LINID_IDBYTE_M)) |
                               (identifier & LIN_LINID_IDBYTE_M);
}

//*****************************************************************************
//
//! Set ID-SlaveTask
//!
//! \param base is the LIN module base address
//! \param identifier is the Received ID comparison ID
//!
//! In LIN mode only, this function sets the identifier to which the received
//! ID of an incoming Header will be compared in order to decide whether a RX
//! response, a TX response, or no action is required.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setIDSlaveTask(uint32_t base, uint16_t identifier)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREGH(base + LIN_O_LINID) = ((HWREGH(base + LIN_O_LINID) &
                               ~(LIN_LINID_IDSTBYTE_M)) |
                              ((identifier & LIN_LINID_IDBYTE_M) <<
                               LIN_LINID_IDSTBYTE_S));
}

//*****************************************************************************
//
//! Send LIN wakeup signal
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function sends the LIN wakeup signal to terminate
//! the sleep mode of any LIN node connected to the bus.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_sendWakeupSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Set key in Byte 0 (MSB) of transmit buffer 0 register
    //
    HWREGB(base + LIN_O_LINTXB0 + 0x3U) = (uint16_t)LIN_WAKEUP_KEY;

    //
    // Transmit TDO for wakeup
    //
    HWREGH(base + LIN_O_LINGCTRL2) |= LIN_LINGCTRL2_WUPGEN;
}

//*****************************************************************************
//
//! Enter LIN Sleep Mode.
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function puts the LIN module into a low-power, sleep
//! mode. This can also be called to forcefully enter sleep when there is no
//! activity on the bus.
//!
//! \note If this function is called while the receiver is actively receiving
//! data and the wakeup interrupt is disabled, then the module will delay
//! sleep mode from being entered until completion of reception.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enterSleep(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREGH(base + LIN_O_LINGCTRL2) |= LIN_LINGCTRL2_LPREQ;
}

//*****************************************************************************
//
//! Send Checksum Byte
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function enables the transmitter with extended
//! frames to send a checkbyte.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_sendChecksum(uint32_t base)
{
    HWREG_BP(base + LIN_O_LINGCTRL2) |= LIN_LINGCTRL2_TXCHAEN;
}

//*****************************************************************************
//
//! Trigger Checksum Compare
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function enables the receiver for extended frames
//! to trigger a checksum compare.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_triggerChecksumCompare(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREG_BP(base + LIN_O_LINGCTRL2) |= LIN_LINGCTRL2_COMPCHASUM;
}

//*****************************************************************************
//
//! Check Tx buffer ready flag
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function checks to see if the Tx ready flag is set
//! indicating that the Tx buffer(s) is/are ready to get another character.
//!
//! \return Returns \b true if the TX ready flag is set, else returns \b false
//
//*****************************************************************************
static inline bool
LIN_isTxReady(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Read Tx Buffer flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_TXBRDYFLG) ==
           LIN_LINFLG_TXBRDYFLG);
}

//*****************************************************************************
//
//! Set LIN Frame Length
//!
//! \param base is the LIN module base address
//! \param length is the number of bytes.
//!
//! In LIN mode only, this function sets the number of bytes in the response
//! field.
//!
//! The \e length parameter must be in a range between 1 and 8.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setFrameLength(uint32_t base, uint16_t length)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((length > 0U) && (length < 9U));

    //
    // Clear and set frame length value
    //
    HWREG_BP(base + LIN_O_LINLCFG) &= ~(LIN_LINLCFG_FLCFG_M);
    HWREG_BP(base + LIN_O_LINLCFG) |= ((((uint32_t)length - (uint32_t)1U) <<
                                         LIN_LINLCFG_FLCFG_S));
}

//*****************************************************************************
//
//! Set LIN communication mode
//!
//! \param base is the LIN module base address
//! \param mode is the selected communication mode
//!
//! In LIN mode only, this function is used to choose how the length of data is
//! conveyed. This choice relates to the version of LIN being used. The \e mode
//! parameter can have one of two values:
//! - \b LIN_COMM_LIN_USELENGTHVAL will use the length set with the
//!   LIN_setFrameLength() function.
//! - \b LIN_COMM_LIN_ID4ID5LENCTL will use ID4 and ID5 for length control.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setCommMode(uint32_t base, LIN_CommMode mode)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Write communication mode selection to the appropriate bit.
    //
    HWREGH(base + LIN_O_LINGCTRL1) = (HWREGH(base + LIN_O_LINGCTRL1) &
                                    ~LIN_LINGCTRL1_COMCFG) | (uint16_t)mode;
}

//*****************************************************************************
//
//! Sets the transmit ID mask
//!
//! \param base is the LIN module base address
//! \param mask is the mask value to be set
//!
//! In LIN mode only, this function sets the mask used for filtering an
//! incoming ID message to determine if the TX ID flag should be set.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setTxMask(uint32_t base, uint16_t mask)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Clear previous mask value and set new mask
    //
    HWREGH(base + LIN_O_LINIDMASK) &= ~(LIN_LINIDMASK_TXIDMASK_M);
    HWREGH(base + LIN_O_LINIDMASK) |= (mask & LIN_LINIDMASK_TXIDMASK_M);
}

//*****************************************************************************
//
//! Sets the receive ID mask
//!
//! \param base is the LIN module base address
//! \param mask is the mask value to be set
//!
//! In LIN mode only, this function sets the mask used for filtering an
//! incoming ID message to determine if the ID RX flag should be set.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setRxMask(uint32_t base, uint16_t mask)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Clear previous mask value and set new mask
    //
    HWREG_BP(base + LIN_O_LINIDMASK) &= ~(LIN_LINIDMASK_RXIDMASK_M);
    HWREG_BP(base + LIN_O_LINIDMASK) |= ((uint32_t)mask << LIN_LINIDMASK_RXIDMASK_S) &
                                   LIN_LINIDMASK_RXIDMASK_M;
}

//*****************************************************************************
//
//! Gets the transmit ID mask
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function gets the mask used for filtering an
//! incoming ID message to determine if the TX ID flag should be set.
//!
//! \return Returns the Transmit ID Mask.
//
//*****************************************************************************
static inline uint16_t
LIN_getTxMask(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    return(HWREGH(base + LIN_O_LINIDMASK) & LIN_LINIDMASK_TXIDMASK_M);
}

//*****************************************************************************
//
//! Gets the receive ID mask
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function gets the mask used for filtering an
//! incoming ID message to determine if the ID RX flag should be set.
//!
//! \return Returns the Receive ID Mask.
//
//*****************************************************************************
static inline uint16_t
LIN_getRxMask(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    return((uint16_t)((HWREG_BP(base + LIN_O_LINIDMASK) & LIN_LINIDMASK_RXIDMASK_M) >>
                      LIN_LINIDMASK_RXIDMASK_S));
}

//*****************************************************************************
//
//! Check if Rx data is ready
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, checks to see if the Rx ready bit is set indicating that
//! a valid message frame has been received.
//!
//! \return Returns \b true if the Rx ready flag is set, else returns \b false.
//
//*****************************************************************************
static inline bool
LIN_isRxReady(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Ready Rx ready flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_RXRDYFLG) ==
           LIN_LINFLG_RXRDYFLG);
}

//*****************************************************************************
//
//! Get last received identifier
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function gets the last received identifier.
//!
//! \return Returns the Received Identifier.
//
//*****************************************************************************
static inline uint16_t
LIN_getRxIdentifier(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    return((uint16_t)((HWREG_BP(base + LIN_O_LINID) & LIN_LINID_RXID_M) >>
                      LIN_LINID_RXID_S));
}

//*****************************************************************************
//
//!  Checks for Tx ID Match Received
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function checks if an ID is received with a TX match
//! and no ID-parity error.
//!
//! \return Returns \b true if a valid ID is matched, else returns \b false.
//
//*****************************************************************************
static inline bool
LIN_isTxMatch(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Read Tx ID flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_TXIDFLG) ==
           LIN_LINFLG_TXIDFLG);
}

//*****************************************************************************
//
//! Checks for Rx ID Match Received
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function checks if an ID is received with a RX match
//! and no ID-parity error.
//!
//! \return Returns \b true if a valid ID is matched, else returns \b false.
//
//*****************************************************************************
static inline bool
LIN_isRxMatch(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Read Rx ID flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_RXIDFLG) ==
           LIN_LINFLG_RXIDFLG);
}

//*****************************************************************************
//
//! Enable interrupts
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! In LIN mode only, this function enables the interrupts for the specified
//! interrupt sources.
//!
//!  The \e intFlags parameter can be set to the following value to set
//!  all the flag bits:
//!  - \b LIN_INT_ALL     - All Interrupts
//!
//!  To set individual flags, the \e intFlags parameter can be the logical
//!  OR of any of the following:
//!  - \b LIN_INT_WAKEUP  - Wakeup
//!  - \b LIN_INT_TO      - Time out
//!  - \b LIN_INT_TOAWUS  - Time out after wakeup signal
//!  - \b LIN_INT_TOA3WUS - Time out after 3 wakeup signals
//!  - \b LIN_INT_TX      - Transmit buffer ready
//!  - \b LIN_INT_RX      - Receive buffer ready
//!  - \b LIN_INT_ID      - Received matching identifier
//!  - \b LIN_INT_PE      - Parity error
//!  - \b LIN_INT_OE      - Overrun error
//!  - \b LIN_INT_FE      - Framing error
//!  - \b LIN_INT_NRE     - No response error
//!  - \b LIN_INT_ISFE    - Inconsistent sync field error
//!  - \b LIN_INT_CE      - Checksum error
//!  - \b LIN_INT_PBE     - Physical bus error
//!  - \b LIN_INT_BE      - Bit error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    HWREG_BP(base + LIN_O_LINIEN) |= intFlags;
}

//*****************************************************************************
//
//! Disable interrupts
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//!
//! In LIN mode only, this function disables the interrupts for the specified
//! interrupt sources.
//!
//!  The \e intFlags parameter can be set to the following value to disable
//!  all the flag bits:
//!  - \b LIN_INT_ALL     - All Interrupts
//!
//!  To disable individual flags, the \e intFlags parameter can be the logical
//!  OR of any of the following:
//!  - \b LIN_INT_WAKEUP  - Wakeup
//!  - \b LIN_INT_TO      - Time out
//!  - \b LIN_INT_TOAWUS  - Time out after wakeup signal
//!  - \b LIN_INT_TOA3WUS - Time out after 3 wakeup signals
//!  - \b LIN_INT_TX      - Transmit buffer ready
//!  - \b LIN_INT_RX      - Receive buffer ready
//!  - \b LIN_INT_ID      - Received matching identifier
//!  - \b LIN_INT_PE      - Parity error
//!  - \b LIN_INT_OE      - Overrun error
//!  - \b LIN_INT_FE      - Framing error
//!  - \b LIN_INT_NRE     - No response error
//!  - \b LIN_INT_ISFE    - Inconsistent sync field error
//!  - \b LIN_INT_CE      - Checksum error
//!  - \b LIN_INT_PBE     - Physical bus error
//!  - \b LIN_INT_BE      - Bit error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREG_BP(base + LIN_O_LINICLR) = intFlags;
}

//*****************************************************************************
//
//! Clear interrupt status
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of the interrupt sources to be cleared.
//!
//! In LIN mode only, this function clears the specified status flags.
//!
//!  The \e intFlags parameter can be set to the following value to clear
//!  all the flag bits:
//!  - \b LIN_INT_ALL     - All Interrupts
//!
//!  To clear individual flags, the \e intFlags parameter can be the logical
//!  OR of any of the following:
//!  - \b LIN_INT_WAKEUP  - Wakeup
//!  - \b LIN_INT_TO      - Time out
//!  - \b LIN_INT_TOAWUS  - Time out after wakeup signal
//!  - \b LIN_INT_TOA3WUS - Time out after 3 wakeup signals
//!  - \b LIN_INT_TX      - Transmit buffer ready
//!  - \b LIN_INT_RX      - Receive buffer ready
//!  - \b LIN_INT_ID      - Received matching identifier
//!  - \b LIN_INT_PE      - Parity error
//!  - \b LIN_INT_OE      - Overrun error
//!  - \b LIN_INT_FE      - Framing error
//!  - \b LIN_INT_NRE     - No response error
//!  - \b LIN_INT_ISFE    - Inconsistent sync field error
//!  - \b LIN_INT_CE      - Checksum error
//!  - \b LIN_INT_PBE     - Physical bus error
//!  - \b LIN_INT_BE      - Bit error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_clearInterruptStatus(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Clear the status flags
    //
    HWREG_BP(base + LIN_O_LINFLG) = intFlags;
}

//*****************************************************************************
//
//! Set interrupt level to 0
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of interrupt sources to be configured
//!
//! In LIN mode only, this function sets the specified interrupt sources to
//! level 0.
//!
//!  The \e intFlags parameter can be set to the following value to set
//!  all the flag bits:
//!  - \b LIN_INT_ALL     - All Interrupts
//!
//!  To set individual flags, the \e intFlags parameter can be the logical
//!  OR of any of the following:
//!  - \b LIN_INT_WAKEUP  - Wakeup
//!  - \b LIN_INT_TO      - Time out
//!  - \b LIN_INT_TOAWUS  - Time out after wakeup signal
//!  - \b LIN_INT_TOA3WUS - Time out after 3 wakeup signals
//!  - \b LIN_INT_TX      - Transmit buffer ready
//!  - \b LIN_INT_RX      - Receive buffer ready
//!  - \b LIN_INT_ID      - Received matching identifier
//!  - \b LIN_INT_PE      - Parity error
//!  - \b LIN_INT_OE      - Overrun error
//!  - \b LIN_INT_FE      - Framing error
//!  - \b LIN_INT_NRE     - No response error
//!  - \b LIN_INT_ISFE    - Inconsistent sync field error
//!  - \b LIN_INT_CE      - Checksum error
//!  - \b LIN_INT_PBE     - Physical bus error
//!  - \b LIN_INT_BE      - Bit error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setInterruptLevel0(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Clear interrupt levels to 0
    //
    HWREG_BP(base + LIN_O_LINILCLR) = intFlags;
}

//*****************************************************************************
//
//! Set interrupt level to 1
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of interrupt sources to be configured
//!
//! In LIN mode only, this function sets the specified interrupt sources to
//! level 1.
//!
//!  The \e intFlags parameter can be set to the following value to set
//!  all the flag bits:
//!  - \b LIN_INT_ALL     - All Interrupts
//!
//!  To set individual flags, the \e intFlags parameter can be the logical
//!  OR of any of the following:
//!  - \b LIN_INT_WAKEUP  - Wakeup
//!  - \b LIN_INT_TO      - Time out
//!  - \b LIN_INT_TOAWUS  - Time out after wakeup signal
//!  - \b LIN_INT_TOA3WUS - Time out after 3 wakeup signals
//!  - \b LIN_INT_TX      - Transmit buffer ready
//!  - \b LIN_INT_RX      - Receive buffer ready
//!  - \b LIN_INT_ID      - Received matching identifier
//!  - \b LIN_INT_PE      - Parity error
//!  - \b LIN_INT_OE      - Overrun error
//!  - \b LIN_INT_FE      - Framing error
//!  - \b LIN_INT_NRE     - No response error
//!  - \b LIN_INT_ISFE    - Inconsistent sync field error
//!  - \b LIN_INT_CE      - Checksum error
//!  - \b LIN_INT_PBE     - Physical bus error
//!  - \b LIN_INT_BE      - Bit error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setInterruptLevel1(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Set interrupt levels to 1
    //
    HWREG_BP(base + LIN_O_LINILEN) |= intFlags;
}

//*****************************************************************************
//
//! Enable Module Errors for Testing
//!
//! \param base is the LIN module base address
//! \param errors is the specified errors to be enabled
//!
//! In LIN mode only, this function enables the specified errors in the module
//! for testing. The \e errors parameter can be a logical OR-ed result of the
//! following values or \b LIN_ALL_ERRORS can be used to enable all of them:
//! - \b LIN_BIT_ERROR      - Simulates a bit error
//! - \b LIN_BUS_ERROR      - Simulates a physical bus error
//! - \b LIN_CHECKSUM_ERROR - Simulates a checksum error
//! - \b LIN_ISF_ERROR      - Simulates an inconsistent synch field error
//!
//! \note To disable these errors, use the LIN_disableModuleErrors() function.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableModuleErrors(uint32_t base, uint32_t errors)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_LINEET_IODFTEN_M);

    //
    // Enable write access
    //
    HWREGH(base + LIN_O_LINEET) |= (LIN_IO_DFT_KEY <<
                                       LIN_LINEET_IODFTEN_S);

    //
    // Enable specified error bits
    //
    HWREG_BP(base + LIN_O_LINEET) |= errors;

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_IO_DFT_KEY <<
                                        LIN_LINEET_IODFTEN_S);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable Module Errors for Testing
//!
//! \param base is the LIN module base address
//! \param errors is the specified errors to be disabled
//!
//! In LIN mode only, this function disables the specified errors in the module
//! for testing. The \e errors parameter can be a logical OR-ed result of the
//! following values or \b LIN_ALL_ERRORS can be used to disable all of them:
//! - \b LIN_BIT_ERROR      - Simulates a bit error
//! - \b LIN_BUS_ERROR      - Simulates a physical bus error
//! - \b LIN_CHECKSUM_ERROR - Simulates a checksum error
//! - \b LIN_ISF_ERROR      - Simulates an inconsistent synch field error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableModuleErrors(uint32_t base, uint32_t errors)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_LINEET_IODFTEN_M);

    //
    // Enable write access
    //
    HWREGH(base + LIN_O_LINEET) |= (LIN_IO_DFT_KEY <<
                                       LIN_LINEET_IODFTEN_S);

    //
    // Disable specified error bits
    //
    HWREG_BP(base + LIN_O_LINEET) &= ~(errors);

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_IO_DFT_KEY <<
                                        LIN_LINEET_IODFTEN_S);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable Automatic Baudrate Adjustment
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function enables the automatic baudrate adjustment
//! mode during the detection of the Synch Field.
//!
//! \note The baudrate selection register will be updated automatically by a
//! slave node if this mode is enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableAutomaticBaudrate(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    WRPRT_DISABLE;

    HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_ABEN;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable Automatic Baudrate Adjustment
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function disables the automatic baudrate adjustment
//! mode during the detection of the Synch Field. This results in a fixed
//! baud rate.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableAutomaticBaudrate(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    WRPRT_DISABLE;

    HWREGH(base + LIN_O_LINGCTRL1) &= ~LIN_LINGCTRL1_ABEN;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Stops LIN Extended Frame Communication
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function stops the extended frame communication.
//! Once stopped, the bit is automatically cleared.
//!
//! \note This function can only be called during extended frame communication.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_stopExtendedFrame(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Set stop bit
    //
    HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_STOEXTCOM;
}

//*****************************************************************************
//
//! Set Checksum Type
//!
//! \param base is the LIN module base address
//! \param type is the checksum type
//!
//! In LIN mode only, this function sets the checksum type. The \e type
//! parameter can be one of the following two values:
//! - \b LIN_CHECKSUM_CLASSIC  - Checksum Classic
//! - \b LIN_CHECKSUM_ENHANCED - Checksum Enhanced
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setChecksumType(uint32_t base, LIN_ChecksumType type)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    if(type == LIN_CHECKSUM_ENHANCED)
    {
        HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_CHASUMCFG;
    }
    else
    {
        HWREGH(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_CHASUMCFG);
    }
}

//*****************************************************************************
//
//! Set Sync Break Extend and Delimiter
//!
//! \param base is the LIN module base address
//! \param syncBreak is the sync break extend value
//! \param delimiter is the sync delimiter value
//!
//! In LIN mode only, this function sets the 3-bit sync break extend value
//! and the 2-bit sync delimiter compare value.
//!
//! The \e break parameter can be a value between 0 to 7. Details:
//! - \b 0 - Sync Break has no additional T-bit
//! - \b 1 - Sync Break has 1 additional T-bit
//! - \b ...
//! - \b 7 - Sync Break has 7 additional T-bits
//!
//! The \e delimiter parameter can be a value between 1 to 4. Details:
//! - \b 1 - Delimiter has 1 T-bit
//! - \b 2 - Delimiter has 2 T-bits
//! - \b 3 - Delimiter has 3 T-bits
//! - \b 4 - Delimiter has 4 T-bits
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setSyncFields(uint32_t base, uint16_t syncBreak, uint16_t delimiter)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT(syncBreak < 8U);
    ASSERT((delimiter >= 1U) && (delimiter < 5U));

    //
    // Clear sync values and set new values
    //
    HWREGH(base + LIN_O_LINCOMP) &= ~((uint16_t)LIN_LINCOMP_SBEXTSEL_M |
                                   (uint16_t)LIN_LINCOMP_SDCOMPSEL_M);
    HWREGH(base + LIN_O_LINCOMP) |= (syncBreak | ((delimiter - 1U) <<
                                               LIN_LINCOMP_SDCOMPSEL_S));
}

//*****************************************************************************
//
// Prototypes for the UART mode APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Enable UART Mode
//!
//! \param base is the LIN module base address
//!
//! This function enables the LIN peripheral to function as a UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableUARTMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Enable UART communications mode
    //
    WRPRT_DISABLE;

    HWREGH(base + LIN_O_LINGCTRL1) &= ~LIN_LINGCTRL1_LINEN;
    HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_CLK_MSCFG |
                                    LIN_LINGCTRL1_TIM;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable UART Mode
//!
//! \param base is the LIN module base address
//!
//! This function disables the UART mode of the LIN peripheral.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableUARTMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Disable UART communications mode
    //
    WRPRT_DISABLE;

    HWREGH(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_CLK_MSCFG |
                                      LIN_LINGCTRL1_TIM);
    HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_LINEN;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set UART communication mode
//!
//! \param base is the LIN module base address
//! \param mode is the selected communication mode
//!
//! In UART mode only, this function is used to select between idle-line mode
//! and address-bit mode. The \e mode parameter can have one of the following
//! values:
//! - \b LIN_COMM_UART_IDLELINE - Idle-line mode.
//! - \b LIN_COMM_UART_ADDRBIT  - Address-bit mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setUARTCommMode(uint32_t base, LIN_UARTCommMode mode)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Write communication mode selection to the appropriate bit.
    //
    HWREGH(base + LIN_O_LINGCTRL1) = (HWREGH(base + LIN_O_LINGCTRL1) &
                                    ~LIN_LINGCTRL1_COMCFG) | (uint16_t)mode;
}

//*****************************************************************************
//
//! Enable UART Parity mode.
//!
//! \param base is the LIN module base address
//! \param parity is the UART parity type
//!
//! In UART mode only, this function enables the parity check and sets the
//! parity type. The \e parity parameter can one of the following values:
//! - \b LIN_UART_PAR_ODD  - Sets Odd parity
//! - \b LIN_UART_PAR_EVEN - Sets Even parity
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableUARTParity(uint32_t base, LIN_UARTParityType parity)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Enable the parity mode
    //
    HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_PARITYEN;

    //
    // Set the parity type
    //
    if(parity == LIN_UART_PAR_ODD)
    {
        HWREGH(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_PARITY);
    }
    else
    {
        HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_PARITY;
    }
}

//*****************************************************************************
//
//! Disable UART Parity mode.
//!
//! \param base is the LIN module base address
//!
//! In UART mode only, this function disables the parity check.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableUARTParity(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Disable the parity mode
    //
    HWREGH(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_PARITYEN);
}

//*****************************************************************************
//
//! Set the number of stop bits for UART
//!
//! \param base is the LIN module base address
//! \param number is the number of stop bits
//!
//! In UART mode only, this function sets the number of stop bits transmitted.
//! The \e number parameter can be one of the following values:
//! - \b LIN_UART_STOP_ONE - Set one stop bit
//! - \b LIN_UART_STOP_TWO - Set two stop bits
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setUARTStopBits(uint32_t base, LIN_UARTStopBits number)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Set the number of stop bits
    //
    if(number == LIN_UART_STOP_ONE)
    {
        HWREGH(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_STOPCFG);
    }
    else
    {
        HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_STOPCFG;
    }
}

//*****************************************************************************
//
//! Enable UART Sleep mode.
//!
//! \param base is the LIN module base address
//!
//! In UART mode only, this function enables the receive sleep mode
//! functionality.
//!
//! \note The receiver still operates when the sleep mode is enabled, however,
//! RXRDY is updated and UARTRD is loaded with new data only when an address
//! frame is detected.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableUARTSleepMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Set sleep mode bit
    //
    HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_SLEEPEN;
}

//*****************************************************************************
//
//! Disable UART Sleep mode.
//!
//! \param base is the LIN module base address
//!
//! In UART mode only, this function disables the receive sleep mode
//! functionality.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableUARTSleepMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Clear sleep mode bit
    //
    HWREGH(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_SLEEPEN);
}

//*****************************************************************************
//
//! Enter UART Local Low-Power Mode
//!
//! \param base is the LIN module base address
//!
//! In UART mode only, this function enters the UART local low-power mode.
//!
//! \note If this function is called while the receiver is actively receiving
//! data and the wakeup interrupt is disabled, then the module will delay
//! sleep mode from being entered until completion of reception.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enterUARTLowPower(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Set low power bit
    //
    HWREGH(base + LIN_O_LINGCTRL2) |= LIN_LINGCTRL2_LPREQ;
}

//*****************************************************************************
//
//! Exit UART Local Low-Power Mode
//!
//! \param base is the LIN module base address
//!
//! In UART mode only, this function exits the UART local low-power mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_exitUARTLowPower(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Clear low power bit
    //
    HWREGH(base + LIN_O_LINGCTRL2) &= ~LIN_LINGCTRL2_LPREQ;
}

//*****************************************************************************
//
//! Set UART character length
//!
//! \param base is the LIN module base address
//! \param numBits is the number of bits per character.
//!
//! In UART mode only, this function sets the number of bits per character.
//!
//! The \e numBits parameter must be in a range between 1 and 8.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setUARTCharLength(uint32_t base, uint16_t numBits)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);
    ASSERT((numBits > 0U) && (numBits < 9U));

    //
    // Set the number of bits per character
    //
    HWREGH(base + LIN_O_LINLCFG) = (HWREGH(base + LIN_O_LINLCFG) &
                                      ~LIN_LINLCFG_CLCFG_M) |
                                     (uint16_t)(numBits - 1U);
}

//*****************************************************************************
//
//! Set UART Frame Length
//!
//! \param base is the LIN module base address
//! \param length is the number of characters
//!
//! In UART mode only, this function sets the number of characters in the
//! response field.
//!
//! The \e length parameter must be in a range between 1 and 8.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setUARTFrameLength(uint32_t base, uint16_t length)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);
    ASSERT((length > 0U) && (length < 9U));

    //
    // Set number of characters
    //
    HWREG_BP(base + LIN_O_LINLCFG) = (HWREG_BP(base + LIN_O_LINLCFG) &
                                        ~(LIN_LINLCFG_FLCFG_M)) |
                                        (((uint32_t)length - (uint32_t)1U) <<
                                         LIN_LINLCFG_FLCFG_S);
}

//*****************************************************************************
//
//! Check if new UART data is ready to be read
//!
//! \param base is the LIN module base address
//!
//! In UART mode only, this function checks to see if the Rx ready bit is set
//! indicating that a new data has been received.
//!
//! \return Returns \b true if the Rx ready flag is set, else returns \b false.
//
//*****************************************************************************
static inline bool
LIN_isUARTDataAvailable(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Read Rx Ready flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_RXRDYFLG) ==
           LIN_LINFLG_RXRDYFLG);
}

//*****************************************************************************
//
//! Check if Space is available in UART Transmit Buffer
//!
//! \param base is the LIN module base address
//!
//! In UART mode only, this function checks to see if the Tx ready flag is set
//! indicating that the Tx buffer(s) is/are ready to get another character.
//!
//! \return Returns \b true if the TX ready flag is set, else returns \b false
//
//*****************************************************************************
static inline bool
LIN_isUARTSpaceAvailable(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Read Tx buffer flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_TXBRDYFLG) ==
           LIN_LINFLG_TXBRDYFLG);
}

//*****************************************************************************
//
//! Reads a UART character without Blocking
//!
//! \param base is the LIN module base address
//! \param emulation sets whether the data is being read by an emulator or not
//!
//! In UART mode only, this function gets the byte of data received. The
//! \e emulation parameter can have one of the following values:
//! - \b true - Emulator is being used, the RXRDY flag won't be cleared
//! - \b false - Emulator isn't being used, the RXRDY flag will be cleared
//!              automatically on read
//!
//! \note
//! -# If the UART receives data that is fewer than 8 bits in length, the
//! data is left-justified and padded with trailing zeros.
//! -# To determine if new data is available to read, use the function
//! LIN_isUARTDataAvailable().
//!
//! \return Returns the received data.
//
//*****************************************************************************
static inline uint16_t
LIN_readUARTCharNonBlocking(uint32_t base, bool emulation)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Read specific data register
    //
    return(emulation ? (HWREGH(base + LIN_O_LINRXED) & LIN_LINRXED_RXED_M) :
            (HWREGH(base + LIN_O_LINRXD) & LIN_LINRXED_RXD_M));
}

//*****************************************************************************
//
//! Reads a UART character with Blocking
//!
//! \param base is the LIN module base address
//! \param emulation sets whether the data is being read by an emulator or not
//!
//! In UART mode only, this function gets the byte of data received. If new data
//! isn't available, this function will wait until new data arrives. The
//! \e emulation parameter can have one of the following values:
//! - \b true - Emulator is being used, the RXRDY flag won't be cleared
//! - \b false - Emulator isn't being used, the RXRDY flag will be cleared
//!              automatically on read
//!
//! \note If the UART receives data that is fewer than 8 bits in length, the
//! data is left-justified and padded with trailing zeros.
//!
//! \return Returns the received data.
//
//*****************************************************************************
static inline uint16_t
LIN_readUARTCharBlocking(uint32_t base, bool emulation)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Wait until a character is available in buffer.
    //
    while(!LIN_isUARTDataAvailable(base))
    {
    }

    //
    // Read specific data register
    //
    return(emulation ? (HWREGH(base + LIN_O_LINRXED) & LIN_LINRXED_RXED_M) :
            (HWREGH(base + LIN_O_LINRXD) & LIN_LINRXED_RXD_M));
}

//*****************************************************************************
//
//! Sends a UART character without blocking
//!
//! \param base is the LIN module base address
//! \param data is the byte of data to be transmitted
//!
//! In UART mode only, this function sets the byte of data to be transmitted
//! without blocking.
//!
//! \note The transmit ready flag gets set when this buffer is ready to be
//! loaded with another byte of data. Use LIN_isUARTSpaceAvailable() to
//! determine if space is available to write another character.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_writeUARTCharNonBlocking(uint32_t base, uint16_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);
    ASSERT(data <= LIN_LINRXED_TXD_M);

    //
    // Set the Tx Data
    //
    HWREGH(base + LIN_O_LINTXD) = (data & LIN_LINRXED_TXD_M);
}

//*****************************************************************************
//
//! Sends a UART character with blocking
//!
//! \param base is the LIN module base address
//! \param data is the byte of data to be transmitted
//!
//! In UART mode only, this function sets the byte of data to be transmitted
//! with blocking functionality. If the buffer isn't ready to get new data
//! written to, this function will wait until space is available.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_writeUARTCharBlocking(uint32_t base, uint16_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);
    ASSERT(data <= LIN_LINRXED_TXD_M);

    //
    // Wait until space is available in the transmit buffer.
    //
    while(!LIN_isUARTSpaceAvailable(base))
    {
    }

    //
    // Set the Tx Data
    //
    HWREGH(base + LIN_O_LINTXD) = (data & LIN_LINRXED_TXD_M);
}

//*****************************************************************************
//
//! Enable UART Module Errors for Testing
//!
//! \param base is the LIN module base address
//! \param errors is the specified errors to be enabled
//!
//! In UART mode only, this function enables the specified errors in the module
//! for testing. The \e errors parameter can be a logical OR-ed result of the
//! following values or \b LIN_UART_ALL_ERRORS can be used to enable all of
//! them:
//! - \b LIN_UART_FRAME_ERROR   - Simulates a frame error
//! - \b LIN_UART_PARITY_ERROR  - Simulates a parity error
//! - \b LIN_UART_BREAK_ERROR   - Simulates a break detect error
//!
//! \note To disable these errors, use the LIN_disableUARTModuleErrors()
//! function.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableUARTModuleErrors(uint32_t base, uint32_t errors)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    WRPRT_DISABLE;

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_LINEET_IODFTEN_M);

    //
    // Enable write access
    //
    HWREGH(base + LIN_O_LINEET) |= (LIN_IO_DFT_KEY <<
                                       LIN_LINEET_IODFTEN_S);

    //
    // Enable specified error bits
    //
    HWREG_BP(base + LIN_O_LINEET) |= errors;

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_IO_DFT_KEY <<
                                        LIN_LINEET_IODFTEN_S);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable UART Module Errors for Testing
//!
//! \param base is the LIN module base address
//! \param errors is the specified errors to be disabled
//!
//! In UART mode only, this function disables the specified errors in the module
//! for testing. The \e errors parameter can be a logical OR-ed result of the
//! following values or \b LIN_UART_ALL_ERRORS can be used to enable all of
//! them:
//! - \b LIN_UART_FRAME_ERROR   - Simulates a frame error
//! - \b LIN_UART_PARITY_ERROR  - Simulates a parity error
//! - \b LIN_UART_BREAK_ERROR   - Simulates a break detect error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableUARTModuleErrors(uint32_t base, uint32_t errors)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    WRPRT_DISABLE;

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_LINEET_IODFTEN_M);

    //
    // Enable write access
    //
    HWREGH(base + LIN_O_LINEET) |= (LIN_IO_DFT_KEY <<
                                       LIN_LINEET_IODFTEN_S);

    //
    // Disable specified error bits
    //
    HWREG_BP(base + LIN_O_LINEET) &= ~(errors);

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_IO_DFT_KEY <<
                                        LIN_LINEET_IODFTEN_S);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable UART interrupts
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! In UART mode only, this function enables the interrupts for the specified
//! interrupt sources.
//!
//!  The \e intFlags parameter can be set to the following value to set
//!  all the flag bits:
//!  - \b LIN_UART_INT_ALL     - All Interrupts
//!
//!  To set individual flags, the \e intFlags parameter can be the logical
//!  OR of any of the following:
//! - \b LIN_UART_INT_BREAK      - Break Detect
//! - \b LIN_UART_INT_WAKEUP     - Wakeup
//! - \b LIN_UART_INT_TX         - Transmit Buffer
//! - \b LIN_UART_INT_RX         - Receive Buffer
//! - \b LIN_UART_INT_TX_DMA     - DMA Transmit
//! - \b LIN_UART_INT_RX_DMA     - DMA Receive
//! - \b LIN_UART_INT_RX_DMA_ALL - DMA Receive All
//! - \b LIN_UART_INT_PARITY     - Parity Error
//! - \b LIN_UART_INT_OVERRUN    - Overrun Error
//! - \b LIN_UART_INT_FRAME      - Framing Error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableUARTInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Set specified interrupts
    //
    HWREG_BP(base + LIN_O_LINIEN) |= intFlags;
}

//*****************************************************************************
//
//! Disable UART interrupts
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//!
//! In UART mode only, this function disables the interrupts for the specified
//! interrupt sources.
//!
//!  The \e intFlags parameter can be set to the following value to disable
//!  all the flag bits:
//!  - \b LIN_UART_INT_ALL     - All Interrupts
//!
//!  To disable individual flags, the \e intFlags parameter can be the logical
//!  OR of any of the following:
//! - \b LIN_UART_INT_BREAK      - Break Detect
//! - \b LIN_UART_INT_WAKEUP     - Wakeup
//! - \b LIN_UART_INT_TX         - Transmit Buffer
//! - \b LIN_UART_INT_RX         - Receive Buffer
//! - \b LIN_UART_INT_TX_DMA     - DMA Transmit
//! - \b LIN_UART_INT_RX_DMA     - DMA Receive
//! - \b LIN_UART_INT_RX_DMA_ALL - DMA Receive All
//! - \b LIN_UART_INT_PARITY     - Parity Error
//! - \b LIN_UART_INT_OVERRUN    - Overrun Error
//! - \b LIN_UART_INT_FRAME      - Framing Error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableUARTInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Set specified interrupts to be cleared
    //
    HWREG_BP(base + LIN_O_LINICLR) |= intFlags;
}

//*****************************************************************************
//
//! Clear UART interrupt status
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of the interrupt sources to be cleared.
//!
//! In UART mode only, this function clears the specified status flags.
//!
//!  The \e intFlags parameter can be set to the following value to clear
//!  all the flag bits:
//!  - \b LIN_UART_INT_ALL     - All Interrupts
//!
//!  To clear individual flags, the \e intFlags parameter can be the logical
//!  OR of any of the following:
//! - \b LIN_UART_INT_BREAK      - Break Detect
//! - \b LIN_UART_INT_WAKEUP     - Wakeup
//! - \b LIN_UART_INT_TX         - Transmit Buffer
//! - \b LIN_UART_INT_RX         - Receive Buffer
//! - \b LIN_UART_INT_TX_DMA     - DMA Transmit
//! - \b LIN_UART_INT_RX_DMA     - DMA Receive
//! - \b LIN_UART_INT_RX_DMA_ALL - DMA Receive All
//! - \b LIN_UART_INT_PARITY     - Parity Error
//! - \b LIN_UART_INT_OVERRUN    - Overrun Error
//! - \b LIN_UART_INT_FRAME      - Framing Error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_clearUARTInterruptStatus(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Clear the status flags
    //
    HWREG_BP(base + LIN_O_LINFLG) |= intFlags;
}

//*****************************************************************************
//
//! Set UART interrupt level to 0
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of interrupt sources to be configured
//!
//! In UART mode only, this function sets the specified interrupt sources to
//! level 0.
//!
//!  The \e intFlags parameter can be set to the following value to set
//!  all the flag bits:
//!  - \b LIN_UART_INT_ALL     - All Interrupts
//!
//!  To set individual flags, the \e intFlags parameter can be the logical
//!  OR of any of the following:
//! - \b LIN_UART_INT_BREAK      - Break Detect
//! - \b LIN_UART_INT_WAKEUP     - Wakeup
//! - \b LIN_UART_INT_TX         - Transmit Buffer
//! - \b LIN_UART_INT_RX         - Receive Buffer
//! - \b LIN_UART_INT_TX_DMA     - DMA Transmit
//! - \b LIN_UART_INT_RX_DMA     - DMA Receive
//! - \b LIN_UART_INT_RX_DMA_ALL - DMA Receive All
//! - \b LIN_UART_INT_PARITY     - Parity Error
//! - \b LIN_UART_INT_OVERRUN    - Overrun Error
//! - \b LIN_UART_INT_FRAME      - Framing Error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setUARTInterruptLevel0(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Clear interrupt levels to 0
    //
    HWREG_BP(base + LIN_O_LINILCLR) |= intFlags;
}

//*****************************************************************************
//
//! Set UART interrupt level to 1
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of interrupt sources to be configured
//!
//! In UART mode only, this function sets the specified interrupt sources to
//! level 1.
//!
//!  The \e intFlags parameter can be set to the following value to set
//!  all the flag bits:
//!  - \b LIN_UART_INT_ALL     - All Interrupts
//!
//!  To set individual flags, the \e intFlags parameter can be the logical
//!  OR of any of the following:
//! - \b LIN_UART_INT_BREAK      - Break Detect
//! - \b LIN_UART_INT_WAKEUP     - Wakeup
//! - \b LIN_UART_INT_TX         - Transmit Buffer
//! - \b LIN_UART_INT_RX         - Receive Buffer
//! - \b LIN_UART_INT_TX_DMA     - DMA Transmit
//! - \b LIN_UART_INT_RX_DMA     - DMA Receive
//! - \b LIN_UART_INT_RX_DMA_ALL - DMA Receive All
//! - \b LIN_UART_INT_PARITY     - Parity Error
//! - \b LIN_UART_INT_OVERRUN    - Overrun Error
//! - \b LIN_UART_INT_FRAME      - Framing Error
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setUARTInterruptLevel1(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Set interrupt levels to 1
    //
    HWREG_BP(base + LIN_O_LINILEN) |= intFlags;
}

//*****************************************************************************
//
//! Check if UART Receiver is Idle
//!
//! \param base is the LIN module base address
//!
//! In UART mode only, this function checks if the receiver is in an idle state.
//!
//! \return Returns \b true if the state is idle, else returns \b false.
//
//*****************************************************************************
static inline bool
LIN_isUARTReceiverIdle(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Read Rx Idle flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_RXIDLEFLG) == 0U);
}

//*****************************************************************************
//
//! Gets the UART Transmit Frame Type
//!
//! \param base is the LIN module base address
//!
//! In UART mode only, this function gets the transmit frame type which can be
//! either data or an address.
//!
//! \return Returns \b true if the frame will be an address, and returns
//! \b false if the frame will be data.
//
//*****************************************************************************
static inline bool
LIN_getUARTTxFrameType(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Read Tx Wake flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_TXWUPSEL) ==
           LIN_LINFLG_TXWUPSEL);
}

//*****************************************************************************
//
//! Gets the UART Receiver Frame Type
//!
//! \param base is the LIN module base address
//!
//! In UART mode only, this function gets the receiver frame type which can be
//! either an address or not an address.
//!
//! \return Returns \b true if the frame is an address, and returns
//! \b false if the frame isn't an address.
//
//*****************************************************************************
static inline bool
LIN_getUARTRxFrameType(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Read Rx Wake flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_RXWUPSEL) ==
           LIN_LINFLG_RXWUPSEL);
}

//*****************************************************************************
//
//! Check if UART Detected a Break Condition
//!
//! \param base is the LIN module base address
//!
//! In UART mode only, this function checks if the module detected a break
//! condition on the Rx pin.
//!
//! \return Returns \b true if break detected, else returns \b false.
//
//*****************************************************************************
static inline bool
LIN_isUARTBreakDetected(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT((HWREGH(base + LIN_O_LINGCTRL1) & LIN_LINGCTRL1_LINEN) == 0U);

    //
    // Read Break condition flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_BRKDETFLG) ==
           LIN_LINFLG_BRKDETFLG);
}

//*****************************************************************************
//
// Prototypes for the LIN and UART mode APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Enables the LIN module.
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function sets the RESET bit of the UARTGCR0
//! register. Registers in this module are not writable until this has been
//! done. Additionally, the transmit and receive pin control functionality is
//! enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Set reset bit.
    //
    HWREGH(base + LIN_O_LINGCTRL0) |= LIN_LINGCTRL0_RST;

    //
    // Enable TX and RX pin control functionality
    //
    HWREGH(base + LIN_O_LINPCTRL0) |= (LIN_LINPCTRL0_RXPEN | LIN_LINPCTRL0_TXPEN);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable the LIN module.
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function clears the RESET bit of the UARTGCR0
//! register. Registers in this module are not writable when this bit is
//! cleared. Additionally, the transmit and receive pin control functionality
//! is disabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Disable TX and RX pin control functionality
    //
    HWREGH(base + LIN_O_LINPCTRL0) &= ~(LIN_LINPCTRL0_RXPEN | LIN_LINPCTRL0_TXPEN);

    //
    // Clear reset bit.
    //
    HWREGH(base + LIN_O_LINGCTRL0) &= ~LIN_LINGCTRL0_RST;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Baud Rate Prescaler
//!
//! \param base is the LIN module base address
//! \param prescaler is the 24-bit integer prescaler
//! \param divider is the 4-bit fractional divider
//!
//! In LIN and UART mode, this function is used to set the baudrate based on
//! the \e prescaler and \e divider values.
//!
//! P = Prescaler  \n
//! M = Fractional Divider \n
//! Bitrate = (SYSCLOCK) / ((P + 1 + M/16) * 16) \n
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setBaudRatePrescaler(uint32_t base, uint32_t prescaler,
                         uint32_t divider)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT(prescaler <= (LIN_LINBR_PSCSELL_M | LIN_LINBR_PSCSELH_M));
    ASSERT(divider <= (LIN_LINBR_FDIVSEL_M >> LIN_LINBR_FDIVSEL_S));

    //
    // Set baud rate prescaler and divider
    //
    HWREG_BP(base + LIN_O_LINBR) = (prescaler | (divider << LIN_LINBR_FDIVSEL_S));
}

//*****************************************************************************
//
//! Enable Transmit Data Transfer.
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function enables the transfer of data from
//! UARTTD or TDy to the transmit shift register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableDataTransmitter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Enable transmit bit
    //
    HWREG_BP(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_TXEN;
}

//*****************************************************************************
//
//! Disable Transmit Data Transfer.
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function disables the transfer of data from
//! UARTTD or TDy to the transmit shift register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableDataTransmitter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Disable transmit bit
    //
    HWREG_BP(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_TXEN);
}

//*****************************************************************************
//
//! Enable Receive Data Transfer.
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function enables the receiver to transfer data
//! from the shift buffer register to the receive buffer or multi-buffer.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableDataReceiver(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Enable receive bit
    //
    HWREG_BP(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_RXEN;
}

//*****************************************************************************
//
//! Disable Receive Data Transfer.
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function disables the receiver to transfer data
//! from the shift buffer register to the receive buffer or multi-buffer.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableDataReceiver(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Disable receive bit
    //
    HWREG_BP(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_RXEN);
}

//*****************************************************************************
//
//! Perform software reset.
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function will reset the LIN state machine and
//! clear all pending flags. It is required to call this function after a
//! wakeup signal has been sent.
//!
//! To enter the reset state separately, use LIN_enterSoftwareReset(). To come
//! out of reset, use LIN_exitSoftwareReset().
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_performSoftwareReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREGH(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_RDY);
    HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_RDY;
}

//*****************************************************************************
//
//! Put LIN into its reset state.
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function will reset the LIN state machine and
//! clear all pending flags. It is required to call this function after a
//! wakeup signal has been sent. When in this state, changes to the
//! configuration of this module may be made.
//!
//! To take LIN out of the reset state and back into the ready state, use
//! LIN_exitSoftwareReset().
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enterSoftwareReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREGH(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_RDY);
}

//*****************************************************************************
//
//! Put LIN into its ready state.
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function will put LIN into its ready state.
//! Transmission and reception can be done in this state. While in the ready
//! state, configuration of the module should not be changed.
//!
//! To put the module into its reset state, use LIN_enterSoftwareReset().
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_exitSoftwareReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_RDY;
}

//*****************************************************************************
//
//! Check if Bus is Busy
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function checks if the receiver bus is busy
//! receiving a frame.
//!
//! \return Returns \b true if the bus is busy, else returns \b false.
//
//*****************************************************************************
static inline bool
LIN_isBusBusy(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Read Bus busy flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_BUSYFLG) ==
           LIN_LINFLG_BUSYFLG);
}

//*****************************************************************************
//
//! Check if the Transmit Buffer is Empty
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function checks if the transmit buffer is empty
//! or not.
//!
//! \return Returns \b true if the Tx buffer is empty, else returns \b false.
//
//*****************************************************************************
static inline bool
LIN_isTxBufferEmpty(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Read Tx Empty Flag and return status
    //
    return((HWREGH(base + LIN_O_LINFLG) & LIN_LINFLG_TXEFLG) ==
           LIN_LINFLG_TXEFLG);
}

//*****************************************************************************
//
//! Enable External Loopback mode for self test
//!
//! \param base is the LIN module base address
//! \param loopbackType is the loopback type (analog or digital)
//! \param path sets the transmit or receive pin to be included in the
//! communication path (Analog loopback mode only)
//!
//! In LIN and UART mode, this function enables the external Loopback mode for
//! self test. The \e loopbackType parameter can be one of the following
//! values:
//! - \b LIN_LOOPBACK_DIGITAL - Digital Loopback
//! - \b LIN_LOOPBACK_ANALOG  - Analog Loopback
//!
//! The \e path parameter is only applicable in analog loopback mode and can
//! be one of the following values:
//! - \b LIN_ANALOG_LOOP_NONE - Default option for digital loopback mode
//! - \b LIN_ANALOG_LOOP_TX   - Enables analog loopback through the Tx pin
//! - \b LIN_ANALOG_LOOP_RX   - Enables analog loopback through the Rx pin
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableExtLoopback(uint32_t base, LIN_LoopbackType loopbackType,
                      LIN_AnalogLoopback path)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_LINEET_IODFTEN_M);

    //
    // Enable Loopback either in Analog or Digital Mode
    //
    HWREGH(base + LIN_O_LINEET) |= ((LIN_IO_DFT_KEY <<
                                        LIN_LINEET_IODFTEN_S) |
                                       (uint16_t)loopbackType |
                                       (uint16_t)path);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable External Loopback mode for self test
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function disables the external Loopback mode.
//!
//! \note This function also resets the analog loopback communication path to
//! the default transmit pin.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableExtLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    //Disable Loopback Mode
    //
    WRPRT_DISABLE;

    HWREGH(base + LIN_O_LINEET) &= ~(LIN_LINEET_IODFTEN_M |
                                        LIN_LINEET_LBCFG |
                                        LIN_LINEET_ALBCFG);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable Internal Loopback mode for self test
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function enables the internal Loopback mode for
//! self test.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableIntLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Enable the internal loopback
    //
    HWREG_BP(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_LBEN;
}

//*****************************************************************************
//
//! Disable Internal Loopback mode for self test
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function disables the internal Loopback mode for
//! self test.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableIntLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Disable the internal loopback
    //
    HWREG_BP(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_LBEN);
}

//*****************************************************************************
//
//! Get Interrupt Flags Status
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function returns the interrupt status register.
//!
//! The following flags can be used to mask the value returned:
//! - \b LIN_FLAG_BREAK   - Break Detect Flag (UART mode only)
//! - \b LIN_FLAG_WAKEUP  - Wake-up Flag
//! - \b LIN_FLAG_IDLE    - Receiver in Idle State (UART mode only)
//! - \b LIN_FLAG_BUSY    - Busy Flag
//! - \b LIN_FLAG_TO      - Bus Idle Timeout Flag (LIN mode only)
//! - \b LIN_FLAG_TOAWUS  - Timeout after Wakeup Signal (LIN mode only)
//! - \b LIN_FLAG_TOA3WUS - Timeout after 3 Wakeup Signals (LIN mode only)
//! - \b LIN_FLAG_TXRDY   - Transmitter Buffer Ready Flag
//! - \b LIN_FLAG_RXRDY   - Receiver Buffer Ready Flag
//! - \b LIN_FLAG_TXWAKE  - Transmitter Wakeup Method Select (UART mode only)
//! - \b LIN_FLAG_TXEMPTY - Transmitter Empty Flag
//! - \b LIN_FLAG_RXWAKE  - Receiver Wakeup Detect Flag
//! - \b LIN_FLAG_TXID    - Identifier on Transmit Flag (LIN mode only)
//! - \b LIN_FLAG_RXID    - Identifier on Receive Flag (LIN mode only)
//! - \b LIN_FLAG_PE      - Parity Error Flag
//! - \b LIN_FLAG_OE      - Overrun Error Flag
//! - \b LIN_FLAG_FE      - Framing Error Flag
//! - \b LIN_FLAG_NRE     - No-Response Error Flag (LIN mode only)
//! - \b LIN_FLAG_ISFE    - Inconsistent Synch Field Error Flag (LIN mode only)
//! - \b LIN_FLAG_CE      - Checksum Error Flag (LIN mode only)
//! - \b LIN_FLAG_PBE     - Physical Bus Error Flag (LIN mode only)
//! - \b LIN_FLAG_BE      - Bit Error Flag (LIN mode only)
//!
//! \return Returns the status flag register.
//
//*****************************************************************************
static inline uint32_t
LIN_getInterruptStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Read and return the flag register
    //
    return(HWREG_BP(base + LIN_O_LINFLG));
}

//*****************************************************************************
//
//! Get the Interrupt Level
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function gets the interrupt level status for
//! all interrupt sources.
//!
//! \return Returns the value of the interrupt level register.
//
//*****************************************************************************
static inline uint32_t
LIN_getInterruptLevel(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Gets the interrupt levels for all sources
    //
    return(HWREG_BP(base + LIN_O_LINILEN));
}

//*****************************************************************************
//
//! Gets the Interrupt Vector Offset for Line 0
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function gets the offset for interrupt line 0.
//! A read to the specified line register updates its value to the next highest
//! priority pending interrupt in the flag register and clears the flag
//! corresponding to the offset that was read.
//!
//! \note The flags for the receive and the transmit interrupts cannot be
//! cleared by reading the corresponding offset vector in this function.
//!
//! The following are values that can be returned:
//! - \b LIN_VECT_NONE    - No Interrupt
//! - \b LIN_VECT_WAKEUP  - Wakeup
//! - \b LIN_VECT_ISFE    - Inconsistent-sync-field Error
//! - \b LIN_VECT_PE      - Parity Error
//! - \b LIN_VECT_ID      - ID Interrupt
//! - \b LIN_VECT_PBE     - Physical Bus Error
//! - \b LIN_VECT_FE      - Frame Error
//! - \b LIN_VECT_BREAK   - Break detect
//! - \b LIN_VECT_CE      - Checksum Error
//! - \b LIN_VECT_OE      - Overrun Error
//! - \b LIN_VECT_BE      - Bit Error
//! - \b LIN_VECT_RX      - Receive Interrupt
//! - \b LIN_VECT_TX      - Transmit Interrupt
//! - \b LIN_VECT_NRE     - No-response Error
//! - \b LIN_VECT_TOAWUS  - Timeout after wakeup signal
//! - \b LIN_VECT_TOA3WUS - Timeout after 3 wakeup signals
//! - \b LIN_VECT_TO      - Timeout (Bus Idle)
//!
//! \return Returns the interrupt vector offset for interrupt line 0.
//
//*****************************************************************************
static inline uint16_t
LIN_getInterruptLine0Offset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Get interrupt vector line offset
    //
    return(HWREGH(base + LIN_O_LINIVO0) & LIN_LINIVO0_IVO0_M);
}

//*****************************************************************************
//
//! Gets the Interrupt Vector Offset for Line 1
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function gets the offset for interrupt line 1.
//! A read to the specified line register updates its value to the next highest
//! priority pending interrupt in the flag register and clears the flag
//! corresponding to the offset that was read.
//!
//! \note The flags for the receive and the transmit interrupts cannot be
//! cleared by reading the corresponding offset vector in this function.
//!
//! The following are values that can be returned:
//! - \b LIN_VECT_NONE    - No Interrupt
//! - \b LIN_VECT_WAKEUP  - Wakeup
//! - \b LIN_VECT_ISFE    - Inconsistent-sync-field Error
//! - \b LIN_VECT_PE      - Parity Error
//! - \b LIN_VECT_ID      - ID Interrupt
//! - \b LIN_VECT_PBE     - Physical Bus Error
//! - \b LIN_VECT_FE      - Frame Error
//! - \b LIN_VECT_BREAK   - Break detect
//! - \b LIN_VECT_CE      - Checksum Error
//! - \b LIN_VECT_OE      - Overrun Error
//! - \b LIN_VECT_BE      - Bit Error
//! - \b LIN_VECT_RX      - Receive Interrupt
//! - \b LIN_VECT_TX      - Transmit Interrupt
//! - \b LIN_VECT_NRE     - No-response Error
//! - \b LIN_VECT_TOAWUS  - Timeout after wakeup signal
//! - \b LIN_VECT_TOA3WUS - Timeout after 3 wakeup signals
//! - \b LIN_VECT_TO      - Timeout (Bus Idle)
//!
//! \return Returns the interrupt vector offset for interrupt line 1.
//
//*****************************************************************************
static inline uint16_t
LIN_getInterruptLine1Offset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Get interrupt vector line offset
    //
    return(HWREGH(base + LIN_O_LINIVO1) & LIN_LINIVO1_IVO1_M);
}

//*****************************************************************************
//
//! Enable Multi-buffer Mode
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function enables the multi-buffer mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableMultibufferMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREGH(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_MBUFEN;
}

//*****************************************************************************
//
//! Disable Multi-buffer Mode
//!
//! \param base is the LIN module base address
//!
//! In LIN and UART mode, this function disables the multi-buffer mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableMultibufferMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREGH(base + LIN_O_LINGCTRL1) &= ~LIN_LINGCTRL1_MBUFEN;
}

//*****************************************************************************
//
//! Set Transmit Pin Delay
//!
//! \param base is the LIN module base address
//! \param delay is number of clock delays for the Tx pin (0 to 7)
//!
//! In LIN and UART mode, this function sets the delay by which the value on
//! the transmit pin is delayed so that the value on the receive pin is
//! asynchronous.
//!
//! \note This is not applicable to the Start bit.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setTransmitDelay(uint32_t base, uint16_t delay)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));
    ASSERT(delay < 8U);

    WRPRT_DISABLE;

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_LINEET_IODFTEN_M);

    //
    // Enable write access
    //
    HWREGH(base + LIN_O_LINEET) |= (LIN_IO_DFT_KEY <<
                                       LIN_LINEET_IODFTEN_S);

    //
    // Clear delay value
    //
    HWREG_BP(base + LIN_O_LINEET) &= ~(LIN_LINEET_TXDLYCFG_M);

    //
    // Set the delay value
    //
    HWREG_BP(base + LIN_O_LINEET) |= ((uint32_t)delay <<
                                        LIN_LINEET_TXDLYCFG_S);

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_LINEET_IODFTEN_M);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Pin Sample Mask
//!
//! \param base is the LIN module base address
//! \param mask is the pin sample mask to be set
//!
//! In LIN and UART mode, this function sets sample number at which the transmit
//! pin value that is being transmitted will be inverted to verify the
//! receive pin samples correctly with the majority detection circuitry.
//! The \e mask parameter can be one of the following values:
//! - \b LIN_PINMASK_NONE         - No mask
//! - \b LIN_PINMASK_CENTER       - Invert Tx Pin value at T-bit center
//! - \b LIN_PINMASK_CENTER_SCLK  - Invert Tx Pin value at T-bit center + SCLK
//! - \b LIN_PINMASK_CENTER_2SCLK - Invert Tx Pin value at T-bit center +
//!                                 2 SCLK
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setPinSampleMask(uint32_t base, LIN_PinSampleMask mask)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_LINEET_IODFTEN_M);

    //
    // Enable write access
    //
    HWREGH(base + LIN_O_LINEET) |= (LIN_IO_DFT_KEY <<
                                       LIN_LINEET_IODFTEN_S);

    //
    // Clear pin mask
    //
    HWREG_BP(base + LIN_O_LINEET) &= ~(LIN_LINEET_PSMASK_M);

    //
    // Set new pin mask value
    //
    HWREG_BP(base + LIN_O_LINEET) |= ((uint32_t)mask <<
                                         LIN_LINEET_PSMASK_S);

    //
    // Clear the IO DFT Enable Key
    //
    HWREGH(base + LIN_O_LINEET) &= ~(LIN_LINEET_IODFTEN_M);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the Debug Suspended Mode
//!
//! \param base is the LIN module base address
//! \param mode is the debug mode
//!
//! In LIN and UART mode, this function sets how the module operates when the
//! program is suspended and being debugged with an emulator. The \e mode
//! parameter can be one of the following values:
//! - \b LIN_DEBUG_FROZEN - The module state machine is frozen; transmissions
//! and LIN counters are halted until debug mode is exited.
//! - \b LIN_DEBUG_COMPLETE - The module continues to operate until the
//! current transmit and receive functions are complete.
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_setDebugSuspendMode(uint32_t base, LIN_DebugMode mode)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Set the debug suspend mode type
    //
    if(mode == LIN_DEBUG_FROZEN)
    {
        HWREG_BP(base + LIN_O_LINGCTRL1) &= ~(LIN_LINGCTRL1_CONTSUS);
    }
    else
    {
        HWREG_BP(base + LIN_O_LINGCTRL1) |= LIN_LINGCTRL1_CONTSUS;
    }
}

//*****************************************************************************
//
//! Enables a LIN global interrupt.
//!
//! \param base is the LIN module base address
//! \param line is specified interrupt vector line
//!
//! In LIN and UART mode, this function globally enables an interrupt
//! corresponding to a specified interrupt line. The \e line parameter can be
//! one of the following enumerated values:
//!
//! - \b LIN_INTERRUPT_LINE0      - Interrupt Vector Line 0
//! - \b LIN_INTERRUPT_LINE1      - Interrupt Vector Line 1
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_enableGlobalInterrupt(uint32_t base, LIN_InterruptLine line)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREGH(base + LIN_O_LINGIEN) |= LIN_LINGIEN_GIEN0 <<
                                      (uint16_t)line;
}

//*****************************************************************************
//
//! Disables a LIN global interrupt.
//!
//! \param base is the LIN module base address
//! \param line is specified interrupt vector line
//!
//! In LIN and UART mode, this function globally disables an interrupt
//! corresponding to a specified interrupt line. The \e line parameter can be
//! one of the following enumerated values:
//!
//! - \b LIN_INTERRUPT_LINE0      - Interrupt Vector Line 0
//! - \b LIN_INTERRUPT_LINE1      - Interrupt Vector Line 1
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_disableGlobalInterrupt(uint32_t base, LIN_InterruptLine line)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREGH(base + LIN_O_LINGIEN) &= ~(LIN_LINGIEN_GIEN0 <<
                                         (uint16_t)line);
}

//*****************************************************************************
//
//! Clears a LIN global interrupt flag.
//!
//! \param base is the LIN module base address
//! \param line is specified interrupt vector line
//!
//! In LIN and UART mode, this function clears the global interrupt flag that
//! corresponds to a specified interrupt line. The \e line parameter can be
//! one of the following enumerated values:
//!
//! - \b LIN_INTERRUPT_LINE0      - Interrupt Vector Line 0
//! - \b LIN_INTERRUPT_LINE1      - Interrupt Vector Line 1
//!
//! \return None.
//
//*****************************************************************************
static inline void
LIN_clearGlobalInterruptStatus(uint32_t base, LIN_InterruptLine line)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    HWREGH(base + LIN_O_LINGICLR) = LIN_LINGICLR_GICLR0 <<
                                        (uint16_t)line;
}

//*****************************************************************************
//
//! Returns a LIN global interrupt flag status.
//!
//! \param base is the LIN module base address
//! \param line is specified interrupt vector line
//!
//! In LIN and UART mode, this function returns the status of a global interrupt
//! flag that corresponds to a specified interrupt line. The \e line parameter
//! can be one of the following enumerated values:
//!
//! - \b LIN_INTERRUPT_LINE0      - Interrupt Vector Line 0
//! - \b LIN_INTERRUPT_LINE1      - Interrupt Vector Line 1
//!
//! \return Returns \b true if the interrupt flag is set. Return \b false if
//!  not.
//
//*****************************************************************************
static inline bool
LIN_getGlobalInterruptStatus(uint32_t base, LIN_InterruptLine line)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Read the flag register and return true if the specified flag is set.
    //
    return((HWREGH(base + LIN_O_LINGIFLG) &
            (LIN_LINGIFLG_GIFLG0 << (uint16_t)line)) ==
           (LIN_LINGIFLG_GIFLG0 << (uint16_t)line));
}

//*****************************************************************************
//
//! Get the Status of LIN TX/RX Pin status.
//!
//! \param base is the LIN module base address
//! \param pin is the type of pin that is being read.
//!
//! In LIN and UART mode, this function indicates the current status of LINTX
//! and LINRX pins. the \e pin parameter can be either LIN_PINTYPE_TX or
//! LIN_PINTYPE_RX.
//!
//! \return Returns \b true if the pin is high else \b false if low.
//
//*****************************************************************************
static inline bool
LIN_getPinStatus(uint32_t base, LIN_PinType pin)
{
    //
    // Check the arguments.
    //
    ASSERT(LIN_isBaseValid(base));

    //
    // Read RX/Tx pin value and return status
    //
    return((HWREGH(base + LIN_O_LINPCTRL2) & pin) == pin);
}

//*****************************************************************************
//
//! Initializes the LIN Driver
//!
//! \param base is the LIN module base address
//!
//! This function initializes the LIN module.
//!
//! \return None.
//
//*****************************************************************************
extern void
LIN_initModule(uint32_t base);

//*****************************************************************************
//
//! Send Data
//!
//! \param base is the LIN module base address
//! \param data is the pointer to data to send
//!
//! In LIN mode only, this function sends a block of data pointed to by 'data'.
//! The number of data to transmit must be set with LIN_setFrameLength()
//! before.
//!
//! \return None.
//
//*****************************************************************************

extern void LIN_sendData(uint32_t base, uint16_t *data);

//*****************************************************************************
//
//! Read received data
//!
//! \param base is the LIN module base address
//! \param data is the pointer to the data buffer
//!
//! In LIN mode only, this function reads a block of bytes and place it into
//! the data buffer pointed to by 'data'.
//!
//! \return None.
//
//*****************************************************************************

extern void LIN_getData(uint32_t base, uint16_t * const data);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#endif // #ifdef __G32R501XX__

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // LIN_H
