//#############################################################################
//
// FILE:    ipc.h
//
// TITLE:   IPC Driver
//
// VERSION: 1.0.0
//
// DATE:    2025-01-15
//
//###########################################################################
// $Copyright:
// Copyright (C) 2024 Geehy Semiconductor - http://www.geehy.com/
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

#ifndef IPC_H
#define IPC_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************

#ifdef __cplusplus
 extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup ipc_api IPC
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "cpu.h"

//*****************************************************************************
//
// The macro definitions can be used to read or write the IPC registers.
//
//*****************************************************************************
#define IPC_COP_READ32(r)       __arm_mrc(1, 0, 0, r, 0)
#define IPC_COP_READ64(r)       __arm_mrrc(1, 0, r)
#define IPC_COP_WRITE32(r, v)   __arm_mcr(1, 0, v, 0, r, 0)
#define IPC_COP_WRITE64(r, v)   __arm_mcrr(1, 0, v, r)

//*****************************************************************************
//
// Values that can be passed to IPC_COP_READ32(), IPC_COP_READ64(),
// IPC_COP_WRITE32() and IPC_COP_WRITE64() as the r parameter.
//
//*****************************************************************************
#define IPC_COP_TX_REG0     0x0U   //!< Data Transmit Register0
#define IPC_COP_TX_REG1     0x1U   //!< Data Transmit Register1
#define IPC_COP_TX_REG2     0x2U   //!< Data Transmit Register2
#define IPC_COP_TX_REG3     0x3U   //!< Data Transmit Register3
#define IPC_COP_RX_REG0     0x4U   //!< Data Receive Register0
#define IPC_COP_RX_REG1     0x5U   //!< Data Receive Register1
#define IPC_COP_RX_REG2     0x6U   //!< Data Receive Register2
#define IPC_COP_RX_REG3     0x7U   //!< Data Receive Register3
#define IPC_COP_SR_REG      0x8U   //!< Status Register
#define IPC_COP_CTRL_REG    0x9U   //!< Control Register
#define IPC_COP_TASK_REG    0xAU   //!< Task Register
#define IPC_COP_STATE_REG   0xBU   //!< Task State Register

//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
//! Used to access SR_REG
#define IPC_TEn_SHIFT    0U
#define IPC_TEn_MASK     0xFU
#define IPC_RFn_SHIFT    8U
#define IPC_RFn_MASK     0xF00U
#define IPC_GIPn_SHIFT   16U
#define IPC_GIPn_MASK    0xF0000U
#define IPC_LPS_MASK     0x80000000U

//! Used to access CTRL_REG
#define IPC_TIEn_SHIFT   0U
#define IPC_TIEn_MASK    0xFU
#define IPC_RIEn_SHIFT   8U
#define IPC_RIEn_MASK    0xF00U
#define IPC_GIEn_SHIFT   16U
#define IPC_GIEn_MASK    0xF0000U
#define IPC_GIRn_SHIFT   20U
#define IPC_GIRn_MASK    0xF00000U
#define IPC_IPCR_MASK    0x80000000U

//*****************************************************************************
//
// Values that can be passed to IPC_request() and IPC_clearPendingStatus()
// as the GPFlags parameter.  They also make up the enumerated bit field
// returned by IPC_getRequestStatus() and IPC_getPendingStatus().  These
// values can be OR-ed together.
//
//*****************************************************************************
#define IPC_GPFLAG_0     0x1U
#define IPC_GPFLAG_1     0x2U
#define IPC_GPFLAG_2     0x4U
#define IPC_GPFLAG_3     0x8U
#define IPC_GPFLAG_ALL   0xFU

//*****************************************************************************
//
// Values that can be passed to IPC_enableInterrupt() and
// IPC_disableInterrupt() as the intFlags parameter.
//
//*****************************************************************************
#define IPC_INT_TE0   0x1U
#define IPC_INT_TE1   0x2U
#define IPC_INT_TE2   0x4U
#define IPC_INT_TE3   0x8U
#define IPC_INT_RF0   0x100U
#define IPC_INT_RF1   0x200U
#define IPC_INT_RF2   0x400U
#define IPC_INT_RF3   0x800U
#define IPC_INT_GP0   0x10000U
#define IPC_INT_GP1   0x20000U
#define IPC_INT_GP2   0x40000U
#define IPC_INT_GP3   0x80000U
#define IPC_INT_ALL   0xF0F0FU

//*****************************************************************************
//
//! Values that can be passed to IPC_isTxBufferEmpty(), IPC_transmit32Bits()
//! and IPC_transmit64Bits() as the \e txNumber parameter.
//
//*****************************************************************************
typedef enum
{
    IPC_TX_0 = 0,
    IPC_TX_1 = 1,
    IPC_TX_2 = 2,
    IPC_TX_3 = 3
} IPC_TxNumber;

//*****************************************************************************
//
//! Values that can be passed to IPC_isRxBufferFull(), IPC_receive32Bits()
//! and IPC_receive64Bits() as the \e rxNumber parameter.
//
//*****************************************************************************
typedef enum
{
    IPC_RX_0 = 0,
    IPC_RX_1 = 1,
    IPC_RX_2 = 2,
    IPC_RX_3 = 3
} IPC_RxNumber;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Resets the IPC module.
//!
//! This function resets the IPC module both the self and peer sides.
//!
//! \return None.
//
//*****************************************************************************
static inline void
IPC_resetModule(void)
{
    IPC_COP_WRITE32(IPC_COP_CTRL_REG, IPC_IPCR_MASK);
}

//*****************************************************************************
//
//! Determines whether the peer-side is idle (low power) or not.
//!
//! This function allows the caller to determine whether or not the peer-side
//! is idle (low power).
//!
//! \return Returns \b true if the peer-side is idle (low power) or \b false
//! if it is not.
//
//*****************************************************************************
static inline bool
IPC_isPeerIdle(void)
{
    return((IPC_COP_READ32(IPC_COP_SR_REG) & IPC_LPS_MASK) != 0U);
}

//*****************************************************************************
//
//! Sends the general purpose interrupt request.
//!
//! \param GPFlags is the bitwise OR of \b IPC_GPFLAGS_X.
//!
//! This function requests the peer-side to generate the general purpose
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
IPC_request(uint32_t GPFlags)
{
    uint32_t regVal;

    //
    // Prevent to send the general purpose interrupt request (GIR) repeatedly.
    //
    regVal = (IPC_COP_READ32(IPC_COP_CTRL_REG) &  ~IPC_GIRn_MASK) |
             (GPFlags << IPC_GIRn_SHIFT);

    IPC_COP_WRITE32(IPC_COP_CTRL_REG, regVal);
}

//*****************************************************************************
//
//! Gets the general purpose interrupt request status.
//!
//! This function gets the general purpose interrupt request status.
//!
//! \return Returns the bitwise OR of \b IPC_GPFLAG_X.
//
//*****************************************************************************
static inline uint32_t
IPC_getRequestStatus(void)
{
    return((IPC_COP_READ32(IPC_COP_CTRL_REG) & IPC_GIRn_MASK) >>
           IPC_GIRn_SHIFT);
}

//*****************************************************************************
//
//! Clears the general purpose interrupt pending status.
//!
//! \param GPFlags is the bitwise OR of \b IPC_GPFLAGS_X.
//!
//! This function clears the general purpose interrupt pending status (GIP) on
//! self-side, and also clearing the general purpose interrupt request status
//!(GIR) on peer-side.
//!
//! \return None.
//
//*****************************************************************************
static inline void
IPC_clearPendingStatus(uint32_t GPFlags)
{
    IPC_COP_WRITE32(IPC_COP_SR_REG, GPFlags << IPC_GIPn_SHIFT);
}

//*****************************************************************************
//
//! Gets the general purpose interrupt pending status.
//!
//! This function gets the general purpose interrupt pending status.
//!
//! \return Returns the bitwise OR of \b IPC_GPFLAG_X.
//
//*****************************************************************************
static inline uint32_t
IPC_getPendingStatus(void)
{
    return((IPC_COP_READ32(IPC_COP_SR_REG) & IPC_GIPn_MASK) >>
           IPC_GIPn_SHIFT);
}

//*****************************************************************************
//
//! Determines whether the TX_REGn is empty or not.
//!
//! \param txNumber is the bit shift of the IPC module.
//!
//! This function allows the caller to determine whether or not the TX_REGn is
//! empty.
//!
//! \return Returns \b true if the TX_REGn is empty or \b false if it is not.
//
//*****************************************************************************
static inline bool
IPC_isTxBufferEmpty(IPC_TxNumber txNumber)
{
    return(((IPC_COP_READ32(IPC_COP_SR_REG) & IPC_TEn_MASK) &
            (1U << (uint32_t)txNumber)) != 0U);
}

//*****************************************************************************
//
//! Determines whether the RX_REGn is full or not.
//!
//! \param number is the bit shift of the IPC module.
//!
//! This function allows the caller to determine whether or not the RX_REGn is
//! full.
//!
//! \return Returns \b true if the RX_REGn is full or \b false if it is not.
//
//*****************************************************************************
static inline bool
IPC_isRxBufferFull(IPC_RxNumber rxNumber)
{
    return((((IPC_COP_READ32(IPC_COP_SR_REG) & IPC_RFn_MASK) >>
             IPC_RFn_SHIFT) & (1U << (uint32_t)rxNumber)) != 0U);
}

//*****************************************************************************
//
//! Issues the task and sends the wake-up signal to the peer-side
//!
//! \param task is a uint32 value for the peer-side.
//!
//! This function sets the task and sends the wake-up signal to the peer-side.
//!
//! \return None.
//
//*****************************************************************************
static inline void
IPC_issueTask(uint32_t task)
{
    IPC_COP_WRITE32(IPC_COP_TASK_REG, task);
}

//*****************************************************************************
//
//! Fetches the task from the peer-side.
//!
//! This function fetches the task from the peer-side.
//!
//! \return Returns the task set by the peer-side.
//
//*****************************************************************************
static inline uint32_t
IPC_fetchTask(void)
{
    return(IPC_COP_READ32(IPC_COP_TASK_REG));
}

//*****************************************************************************
//
//! Updates the indication of running task to the peer-side.
//!
//! \param state is the indication of running task for the peer-side.
//!
//! This function updates the indication of running task to the peer-side.
//!
//! \return None.
//
//*****************************************************************************
static inline void
IPC_updateTaskState(uint32_t state)
{
    IPC_COP_WRITE32(IPC_COP_STATE_REG, state);
}

//*****************************************************************************
//
//! Gets the indication of running task from the peer-side.
//!
//! This function gets the indication of running task from the peer-side.
//!
//! \return Returns the indication of running task set by the peer-side.
//
//*****************************************************************************
static inline uint32_t
IPC_getTaskState(void)
{
    return(IPC_COP_READ32(IPC_COP_STATE_REG));
}

//*****************************************************************************
//
//! Enables an IPC interrupt source.
//!
//! \param intFlags is the bitwise OR of \b IPC_INT_X.
//!
//! This function enables the IPC interrupt source.
//!
//! \return None.
//
//*****************************************************************************
static inline void
IPC_enableInterrupt(uint32_t intFlags)
{
    uint32_t regVal;

    //
    // Prevent to send the general purpose interrupt request (GIR) repeatedly.
    //
    regVal = (IPC_COP_READ32(IPC_COP_CTRL_REG) & ~IPC_GIRn_MASK) | intFlags;

    IPC_COP_WRITE32(IPC_COP_CTRL_REG, regVal);
}

//*****************************************************************************
//
//! Disables an IPC interrupt source.
//!
//! \param intFlags is the bitwise OR of \b IPC_INT_X.
//!
//! This function disables the IPC interrupt source.
//!
//! \return None.
//
//*****************************************************************************
static inline void
IPC_disableInterrupt(uint32_t intFlags)
{
    uint32_t regVal;

    //
    // Prevent to send the general purpose interrupt request (GIR) repeatedly.
    //
    regVal = (IPC_COP_READ32(IPC_COP_CTRL_REG) & ~IPC_GIRn_MASK) & ~intFlags;

    IPC_COP_WRITE32(IPC_COP_CTRL_REG, regVal);
}

//*****************************************************************************
//
//! Transmits a 32-bits message.
//!
//! \param txNumber is the TX register number of the IPC module.
//! \param message is a data that will be sent to the peer-side.
//!
//! This function transmits a 32-bits message to peer-side.
//!
//! \return None.
//
//*****************************************************************************
static inline void
IPC_transmit32Bits(IPC_TxNumber txNumber, uint32_t message)
{
    switch(txNumber)
    {
        case IPC_TX_0:
            IPC_COP_WRITE32(IPC_COP_TX_REG0, message);
            break;

        case IPC_TX_1:
            IPC_COP_WRITE32(IPC_COP_TX_REG1, message);
            break;

        case IPC_TX_2:
            IPC_COP_WRITE32(IPC_COP_TX_REG2, message);
            break;

        case IPC_TX_3:
            IPC_COP_WRITE32(IPC_COP_TX_REG3, message);
            break;
    }
}

//*****************************************************************************
//
//! Receives a 32-bits message.
//!
//! \param rxNumber is the RX register number of the IPC module.
//!
//! This function receives a 32-bits message from the peer-side.
//!
//! \return Returns a 32-bits message sent by the peer-side.
//
//*****************************************************************************
static inline uint32_t
IPC_receive32Bits(IPC_RxNumber rxNumber)
{
    uint32_t result;
    switch(rxNumber)
    {
        case IPC_RX_0:
            result = IPC_COP_READ32(IPC_COP_RX_REG0);
            break;

        case IPC_RX_1:
            result = IPC_COP_READ32(IPC_COP_RX_REG1);
            break;

        case IPC_RX_2:
            result = IPC_COP_READ32(IPC_COP_RX_REG2);
            break;

        case IPC_RX_3:
            result = IPC_COP_READ32(IPC_COP_RX_REG3);
            break;
    }
    return result;
}

//*****************************************************************************
//
//! Transmits a 64-bits message.
//!
//! \param txNumber is the TX register number of the IPC module.
//! \param message is a data that will be sent to the peer-side.
//!
//! This function transmits a 64-bits message to peer-side.
//!
//! \note The function with \b IPC_TX_(n) and \b IPC_TX_(n+1), n={0, 2}, has
//! the same meaning. 
//!
//! \return None.
//
//*****************************************************************************
static inline void
IPC_transmit64Bits(IPC_TxNumber txNumber, uint64_t message)
{
    switch(txNumber)
    {
        case IPC_TX_0:
        case IPC_TX_1:
            IPC_COP_WRITE64(IPC_COP_TX_REG0, message);
            break;

        case IPC_TX_2:
        case IPC_TX_3:
            IPC_COP_WRITE64(IPC_COP_TX_REG2, message);
            break;
    }
}

//*****************************************************************************
//
//! Receives a 64-bits message.
//!
//! \param rxNumber is the RX register number of the IPC module.
//!
//! This function receives a 64-bits message from the peer-side.
//!
//! \note The function with \b IPC_RX_(n) and \b IPC_RX_(n+1), n={0, 2}, has
//! the same meaning. 
//!
//! \return Returns a 64-bits message sent by the peer-side.
//
//*****************************************************************************
static inline uint64_t
IPC_receive64Bits(IPC_RxNumber rxNumber)
{
    uint64_t result;
    switch(rxNumber)
    {
        case IPC_RX_0:
        case IPC_RX_1:
            result = IPC_COP_READ64(IPC_COP_RX_REG0);
            break;

        case IPC_RX_2:
        case IPC_RX_3:
            result = IPC_COP_READ64(IPC_COP_RX_REG2);
            break;
    }
    return result;
}

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
#if __cplusplus
}
#endif

#endif // IPC_H
