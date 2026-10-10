//###########################################################################
//
// FILE:    canfd.h
//
// TITLE:   G32R502 CANFD driver API definitions.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
// Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
// 1. Modified macro definitions and module naming and OTP addresses and offsets.
//
//###########################################################################

#ifndef CANFD_H_
#define CANFD_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __G32R502XX__
#include "inc/hw_canfd.h"
#include "inc/hw_canfdss.h"
#include "inc/hw_memmap.h"
#include <stdbool.h>
#include "inc/hw_types_canfd.h"
#include "cpu.h"
#include "sysctl.h"


//! \addtogroup canfd_api CANFD
//! @{

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  CANFD MSG RAM BANK number for ECC AGGR.
 */
#define CANFD_MSGRAM_RAM_NUM                                       (0U)

/**
 * \brief  Maximum Number of Rx Buffers.
 */
#define CANFD_MSGRAM_RX_BUFFER_MAX                                 (64U)

/**
 * \brief  Maximum Number of Tx Buffers.
 */
#define CANFD_MSGRAM_TX_BUFFER_MAX                                  (32U)

/**
 * \brief  Macro for standard Message ID filter.
 */
#define CANFD_MSGRAM_STD_ID_FILTER_SIZE_WORDS                       (1U)

/**
 * \brief  Macro for extended Message ID filter.
 */
#define CANFD_MSGRAM_EXT_ID_FILTER_SIZE_WORDS                        (2U)

/**
 * \brief  Macro for Tx Event FIFO element size.
 */
#define CANFD_MSGRAM_TX_EVENT_FIFO_SIZE_WORDS                         (2U)

/**
 * \brief  Macro for Interrupt Line enable mask.
 */
#define CANFD_MSGRAM_INTR_LINE_EN_MASK   ((CANFD_ILE_EINT0_MASK | CANFD_ILE_EINT1_MASK))


/**
 * \brief  Macro defines mask for all the interrupts status for CANFD.
 */
#define CANFD_INTR_MASK_ALL   (CANFD_IR_RF0N_MASK |                              \
                              CANFD_IR_RF0W_MASK |                              \
                              CANFD_IR_RF0F_MASK |                              \
                              CANFD_IR_RF0L_MASK |                              \
                              CANFD_IR_RF1N_MASK |                              \
                              CANFD_IR_RF1W_MASK |                              \
                              CANFD_IR_RF1F_MASK |                              \
                              CANFD_IR_RF1L_MASK |                              \
                              CANFD_IR_HPM_MASK |                               \
                              CANFD_IR_TC_MASK |                                \
                              CANFD_IR_TCF_MASK |                               \
                              CANFD_IR_TFE_MASK |                               \
                              CANFD_IR_TEFN_MASK |                              \
                              CANFD_IR_TEFW_MASK |                              \
                              CANFD_IR_TEFF_MASK |                              \
                              CANFD_IR_TEFL_MASK |                              \
                              CANFD_IR_TSW_MASK |                               \
                              CANFD_IR_MRAF_MASK |                              \
                              CANFD_IR_TOO_MASK |                               \
                              CANFD_IR_DRX_MASK |                               \
                              CANFD_IR_ELO_MASK |                               \
                              CANFD_IR_EP_MASK |                                \
                              CANFD_IR_EW_MASK |                                \
                              CANFD_IR_BO_MASK |                                \
                              CANFD_IR_WDI_MASK |                               \
                              CANFD_IR_PEA_MASK |                               \
                              CANFD_IR_PED_MASK |                               \
                              CANFD_IR_ARA_MASK)

/**
 * \brief  Maximum payload supported by CAN-FD protocol in bytes.
 */
#define CANFD_MAX_PAYLOAD_BYTES                          (64U)

//*****************************************************************************
//
// These macro definitions are used to specify Standard Filter Types to
// set the sft values of the struct CANFD_StdMsgIDFilterElement
// used as a parameter in the function CANFD_addStdMsgIDFilter()
//
//*****************************************************************************

#define CANFD_STDFILT_RANGE                             (0U)
/**< Range Filter from SFID1 to SFID2 */
#define CANFD_STDFILT_DUAL                              (1U)
/**< Dual ID Filter for SFID1 or SFID2 */
#define CANFD_STDFILT_CLASSIC                           (2U)
/**< Classic Filter: SFID1 = filter, SFID2 = mask */
#define CANFD_STDFILT_DISABLED                          (3U)
/**< Filter Element Disabled */

//*****************************************************************************
//
// These macro definitions are used to specify Standard Filter Element
// Configurations to set the sfec values of the struct CANFD_StdMsgIDFilterElement
// used as a parameter in the function CANFD_addStdMsgIDFilter()
//
//*****************************************************************************

#define CANFD_STDFILTEC_DISABLE                          (0U)
/**< Filter Element Disabled */
#define CANFD_STDFILTEC_FIFO0                            (1U)
/**< Store in RX FIFO 0 if filter matches */
#define CANFD_STDFILTEC_FIFO1                            (2U)
/**< Store in RX FIFO 1 if filter matches */
#define CANFD_STDFILTEC_REJECT                           (3U)
/**< Reject ID if filter matches */
#define CANFD_STDFILTEC_PRI                              (4U)
/**< Set priority if filter matches */
#define CANFD_STDFILTEC_PRI_FIFO0                        (5U)
/**< Set priority and store in RX FIFO 0 if filter matches */
#define CANFD_STDFILTEC_PRI_FIFO1                        (6U)
/**< Set priority and store in RX FIFO 1 if filter matches */
#define CANFD_STDFILTEC_RXBUFF                           (7U)
/**< Store in RX Buffer */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief    Enum to select the CANFD interrupt lines
 */
typedef enum
{
    CANFD_INTR_LINE_NUM_0 = 0U,
    /**< CANFD interrupt line 0 */
    CANFD_INTR_LINE_NUM_1 = 1U
                           /**< CANFD interrupt line 1 */
}CANFD_IntrLineNum;

/**
 *  \brief    Enum to represent the CANFD Identifier Type
 */
typedef enum
{
    CANFD_ID_TYPE_11_BIT = 0U,
    /**< 11bit CANFD Identifier */
    CANFD_ID_TYPE_29_BIT = 1U
                          /**< 29bit CANFD Identifier */
}CANFD_IdType;

/**
 *  \brief    Enum to represent the CANFD mode of operation
 */
typedef enum
{
    CANFD_OPERATION_MODE_NORMAL = 0U,
    /**< CANFD normal mode */
    CANFD_OPERATION_MODE_SW_INIT = 1U
                                  /**< CANFD SW initialization mode */
}CANFD_OperationMode;

/**
 *  \brief    Enum to represent the CANFD Message RAM type.
 */
typedef enum
{
    CANFD_MEM_TYPE_BUF = 0U,
    /**< CANFD Msg RAM buffers */
    CANFD_MEM_TYPE_FIFO = 1U
                         /**< CANFD Msg RAM FIFO/Queue */
}CANFD_MemType;

/**
 *  \brief    Enum to represent the CANFD Rx FIFO number
 */
typedef enum
{
    CANFD_RX_FIFO_NUM_0 = 0U,
    /**< CANFD Rx FIFO 0 */
    CANFD_RX_FIFO_NUM_1 = 1U
                         /**< CANFD Rx FIFO 1 */
}CANFD_RxFIFONum;

/**
 *  \brief    Enum to represent the CANFD pin type
 */
typedef enum
{
    CANFD_PIN_TYPE_RX = 0U,
    /**< CANFD Rx Pin */
    CANFD_PIN_TYPE_TX = 1U
                       /**< CANFD Tx Pin */
}CANFD_PinType;

/**
 *  \brief    Enum to represent FIFO/Buffer element Size
 */
typedef enum
{
    CANFD_ELEM_SIZE_8BYTES = 0U,
    /**< 8 byte data field */
    CANFD_ELEM_SIZE_12BYTES = 1U,
    /**< 12 byte data field */
    CANFD_ELEM_SIZE_16BYTES = 2U,
    /**< 16 byte data field */
    CANFD_ELEM_SIZE_20BYTES = 3U,
    /**< 20 byte data field */
    CANFD_ELEM_SIZE_24BYTES = 4U,
    /**< 24 byte data field */
    CANFD_ELEM_SIZE_32BYTES = 5U,
    /**< 32 byte data field */
    CANFD_ELEM_SIZE_48BYTES = 6U,
    /**< 48 byte data field */
    CANFD_ELEM_SIZE_64BYTES = 7U
                             /**< 64 byte data field */
}CANFD_ElemSize;

/**
 *  \brief    Enum to represent the CANFD time-out counter configuration
 */
typedef enum
{
    CANFD_TIMEOUT_SELECT_CONT = 0U,
    /**< Continuous operation Mode */
    CANFD_TIMEOUT_SELECT_TX_EVENT_FIFO = 1U,
    /**< Timeout controlled by Tx Event FIFO */
    CANFD_TIMEOUT_SELECT_RX_FIFO0 = 2U,
    /**< Timeout controlled by Rx FIFO 0 */
    CANFD_TIMEOUT_SELECT_RX_FIFO1 = 3U
                                   /**< Timeout controlled by Rx FIFO 1 */
}CANFD_TimeOutSelect;

/**
 * \brief  Enum for CANFD interrupts.
 */
typedef enum
{
    CANFD_INTR_SRC_RX_FIFO0_NEW_MSG = CANFD_IR_RF0N_MASK,
    /**< Rx FIFO 0 New Message interrupt */
    CANFD_INTR_SRC_RX_FIFO0_WATERMARK = CANFD_IR_RF0W_MASK,
    /**< Rx FIFO 0 Watermark Reached interrupt */
    CANFD_INTR_SRC_RX_FIFO0_FULL = CANFD_IR_RF0F_MASK,
    /**< Rx FIFO 0 Full interrupt */
    CANFD_INTR_SRC_RX_FIFO0_MSG_LOST = CANFD_IR_RF0L_MASK,
    /**< Rx FIFO 0 Message Lost interrupt */
    CANFD_INTR_SRC_RX_FIFO1_NEW_MSG = CANFD_IR_RF1N_MASK,
    /**< Rx FIFO 1 New Message interrupt */
    CANFD_INTR_SRC_RX_FIFO1_WATERMARK = CANFD_IR_RF1W_MASK,
    /**< Rx FIFO 1 Watermark Reached interrupt */
    CANFD_INTR_SRC_RX_FIFO1_FULL = CANFD_IR_RF1F_MASK,
    /**< Rx FIFO 1 Full interrupt */
    CANFD_INTR_SRC_RX_FIFO1_MSG_LOST = CANFD_IR_RF1L_MASK,
    /**< Rx FIFO 1 Message Lost interrupt */
    CANFD_INTR_SRC_HIGH_PRIO_MSG = CANFD_IR_HPM_MASK,
    /**< High Priority Message interrupt */
    CANFD_INTR_SRC_TRANS_COMPLETE = CANFD_IR_TC_MASK,
    /**< Transmission Completed interrupt */
    CANFD_INTR_SRC_TRANS_CANCEL_FINISH = CANFD_IR_TCF_MASK,
    /**< Transmission Cancellation Finished interrupt */
    CANFD_INTR_SRC_TX_FIFO_EMPTY = CANFD_IR_TFE_MASK,
    /**< Tx FIFO Empty interrupt */
    CANFD_INTR_SRC_TX_EVT_FIFO_NEW_ENTRY = CANFD_IR_TEFN_MASK,
    /**< Tx Event FIFO New Entry interrupt */
    CANFD_INTR_SRC_TX_EVT_FIFO_WATERMARK = CANFD_IR_TEFW_MASK,
    /**< Tx Event FIFO Watermark Reached interrupt */
    CANFD_INTR_SRC_TX_EVT_FIFO_FULL = CANFD_IR_TEFF_MASK,
    /**< Tx Event FIFO Full interrupt */
    CANFD_INTR_SRC_TX_EVT_FIFO_ELEM_LOST = CANFD_IR_TEFL_MASK,
    /**< Tx Event FIFO Element Lost interrupt */
    CANFD_INTR_SRC_TIMESTAMP_WRAPAROUND = CANFD_IR_TSW_MASK,
    /**< Timestamp Wraparound interrupt */
    CANFD_INTR_SRC_MSG_RAM_ACCESS_FAILURE = CANFD_IR_MRAF_MASK,
    /**< Message RAM Access Failure interrupt */
    CANFD_INTR_SRC_TIMEOUT = CANFD_IR_TOO_MASK,
    /**< Timeout Occurred interrupt */
    CANFD_INTR_SRC_DEDICATED_RX_BUFF_MSG = CANFD_IR_DRX_MASK,
    /**< Message stored to Dedicated Rx Buffer interrupt */
    CANFD_INTR_SRC_ERR_LOG_OVRFLW = CANFD_IR_ELO_MASK,
    /**< Error Logging Overflow interrupt */
    CANFD_INTR_SRC_ERR_PASSIVE = CANFD_IR_EP_MASK,
    /**< Error Passive interrupt */
    CANFD_INTR_SRC_WARNING_STATUS = CANFD_IR_EW_MASK,
    /**< Warning Status interrupt */
    CANFD_INTR_SRC_BUS_OFF_STATUS = CANFD_IR_BO_MASK,
    /**< Bus_Off Status interrupt */
    CANFD_INTR_SRC_WATCHDOG = CANFD_IR_WDI_MASK,
    /**< Watchdog Interrupt interrupt */
    CANFD_INTR_SRC_PROTOCOL_ERR_ARB = CANFD_IR_PEA_MASK,
    /**< Protocol Error in Arbitration Phase interrupt */
    CANFD_INTR_SRC_PROTOCOL_ERR_DATA = CANFD_IR_PED_MASK,
    /**< Protocol Error in Data Phase interrupt */
    CANFD_INTR_SRC_RES_ADDR_ACCESS = CANFD_IR_ARA_MASK
                                    /**< Access to Reserved Address interrupt */
}CANFD_IntrSrc;

/**
 *  \brief    Enum to represent the ECC Error Types
 */
typedef enum
{
    CANFD_ECC_ERR_TYPE_SEC = 0U,
    /**< ECC Single Error Correction */
    CANFD_ECC_ERR_TYPE_DED = 1U
    /**< ECC Single Error Detection */
}CANFD_ECCErrType;

/**
 *  \brief    Enum to select the CANFD Loopback mode
 */
typedef enum
{
    CANFD_LPBK_MODE_INTERNAL = 0U,
    /**< Internal Loop Back Mode
     *   This mode can be used for hot self-test and this mode will not
     *   affect bus state.
     */
    CANFD_LPBK_MODE_EXTERNAL = 1U
                              /**< External Loop Back Mode
                               *   In this mode, the CANFD module treats its own
                               *   transmitted messages as received messages and
                               *   stores them (if they pass acceptance filtering)
                               *   into an Rx Buffer or an Rx FIFO.
                               *   This mode will affect bus state
                               */
}CANFD_LpbkMode;

/**
 *  \brief    Enum to represent CANFD's communication state
 */
typedef enum
{
    CANFD_COM_STATE_SYNCHRONIZING = 0U,
    /**< CANFD is synchronizing on CAN communication */
    CANFD_COM_STATE_IDLE = 1U,
    /**< CANFD is neither receiver nor transmitter */
    CANFD_COM_STATE_RECEIVER = 2U,
    /**< CANFD is operating as receiver */
    CANFD_COM_STATE_TRANSMITTER = 3U
                                 /**< CANFD is operating as transmitter */
}CANFD_ComState;

/**
 *  \brief    Enum to represent CANFD's Error Code
 */
typedef enum
{
    CANFD_ERR_CODE_NO_ERROR = 0U,
    /**< No error occurred since LEC has been reset by
     *   successful reception or transmission.
     */
    CANFD_ERR_CODE_STUFF_ERROR = 1U,
    /**< More than 5 equal bits in a sequence have occurred in a part of
     *   a received message where this is not allowed.
     */
    CANFD_ERR_CODE_FORM_ERROR = 2U,
    /**< A fixed format part of a received frame has the wrong format. */
    CANFD_ERR_CODE_ACK_ERROR = 3U,
    /**< The message transmitted by the CANFD module was not acknowledged
     *   by another node.
     */
    CANFD_ERR_CODE_BIT1_ERROR = 4U,
    /**< During the transmission of a message (with the exception of
     *   the arbitration field), the device wanted to send a
     *   recessive level (bit of logical value '1'),
     *  but the monitored bus value was dominant.
     */
    CANFD_ERR_CODE_BIT0_ERROR = 5U,
    /**< During the transmission of a message (or acknowledge bit,
     *   or active error flag, or overload flag), the device wanted to send
     *   a dominant level (data or identifier bit logical value '0'),
     *   but the monitored bus value was recessive. During Bus_Off recovery
     *   this status is set each time a sequence of 11 recessive bits has been
     *   monitored. This enables the CPU to monitor the proceeding of
     *   the Bus_Off recovery sequence (indicating the bus is not stuck at
     *   dominant or continuously disturbed).
     */
    CANFD_ERR_CODE_CRC_ERROR = 6U,
    /**< The CRC check sum of a received message was incorrect.
     *   The CRC of an incoming message does not match with the
     *   CRC calculated from the received data.
     */
    CANFD_ERR_CODE_NO_CHANGE = 7U
                              /**< Any read access to the Protocol Status
                               *   Register re-initializes
                               *   the LEC to '7'. When the LEC shows the value
                               *   '7', no CAN bus event was detected since the last
                               *   CPU read access to
                               *   the Protocol Status Register.
                               */
}CANFD_ErrCode;

/**
 *  \brief    Enum to determine the clock source that will be set 
 *            up via a call to the CANFD_selectClockSource() API
 */
typedef enum
{
    //! Select APBCLK
    CANFD_CLOCK_SOURCE_APB      = 0x0,

    //! Select external crystal (XTAL)
    CANFD_CLOCK_SOURCE_XTAL     = 0x1,

    //! Auxiliary Clock Input Source
    CANFD_CLOCK_SOURCE_AUXCLK   = 0x2

} CANFD_ClockSource;

/**
 * \brief  Structure for bit timing calculation.
 *         Bit timing related to data phase will be valid only in case where
 *         CANFD is put in CAN-FD mode and will be '0' otherwise.
 */
typedef struct
{
    uint32_t nomRatePrescalar;
    /**< Nominal Baud Rate Pre-scaler
     *   Range:[0x0-0x1FF]
     */
    uint32_t nomTimeSeg1;
    /**< Nominal Time segment before sample point
     *   Range:[0x0-0xFF]
     */
    uint32_t nomTimeSeg2;
    /**< Nominal Time segment after sample point
     *   Range:[0x0-0x7F]
     */
    uint32_t nomSynchJumpWidth;
    /**< Nominal (Re)Synchronization Jump Width
     *   Range:[0x0-0x7F]
     */
    uint32_t dataRatePrescalar;
    /**< Data Baud Rate Pre-scaler
     *   Range:[0x0-0x1F]
     */
    uint32_t dataTimeSeg1;
    /**< Data Time segment before sample point
     *   Range:[0x0-0x1F]
     */
    uint32_t dataTimeSeg2;
    /**< Data Time segment after sample point
     *   Range:[0x0-0xF]
     */
    uint32_t dataSynchJumpWidth;
    /**< Data (Re)Synchronization Jump Width
     *   Range:[0x0-0xF]
     */
}CANFD_BitTimingParams;

/**
 * \brief  Structure for CANFD Transmitter Delay Compensation parameters.
 */
typedef struct
{
    uint32_t tdcf;
    /**< Transmitter Delay Compensation Filter Window Length
     *   Range:[0x0-0x7F]
     */
    uint32_t tdco;
    /**< Transmitter Delay Compensation Offset
     *   Range:[0x0-0x7F]
     */
}CANFD_TDCConfig;

/**
 * \brief  Structure for CANFD Global Filter Configuration parameters.
 */
typedef struct
{
    uint32_t rrfe;
    /**< Reject Remote Frames Extended
     *   0 = Filter remote frames with 29-bit extended IDs
     *   1 = Reject all remote frames with 29-bit extended IDs
     */
    uint32_t rrfs;
    /**< Reject Remote Frames Standard
     *   0 = Filter remote frames with 11-bit standard IDs
     *   1 = Reject all remote frames with 11-bit standard IDs
     */
    uint32_t anfe;
    /**< Accept Non-matching Frames Extended
     *   0 = Accept in Rx FIFO 0
     *   1 = Accept in Rx FIFO 1
     *   others = Reject
     */
    uint32_t anfs;
    /**< Accept Non-matching Frames Standard
     *   0 = Accept in Rx FIFO 0
     *   1 = Accept in Rx FIFO 1
     *   others = Reject
     */
}CANFD_GlobalFiltConfig;

/**
 * \brief  Structure for CANFD initialization parameters.
 */
typedef struct
{
    uint32_t       fdMode;
    /**< FD Operation Enable
     *   0 = FD operation disabled
     *   1 = FD operation enabled
     */
    uint32_t       brsEnable;
    /**< Bit Rate Switch Enable
     *   This is valid only when opMode = 1.
     *   0 = Bit rate switching for transmissions disabled
     *   1 = Bit rate switching for transmissions enabled
     */
    uint32_t       txpEnable;
    /**< Transmit Pause
     *   0 = Transmit pause disabled
     *   1 = Transmit pause enabled
     */
    uint32_t       efbi;
    /**< FEdge Filtering during Bus Integration
     *   0 = Edge filtering disabled
     *   1 = Two consecutive dominant tq required to detect an edge for
     *       hard synchronization
     */
    uint32_t       pxhddisable;
    /**< Protocol Exception Handling Disable
     *   0 = Protocol exception handling enabled
     *   1 = Protocol exception handling disabled
     */
    uint32_t       darEnable;
    /**< Disable Automatic Retransmission
     *   0 = Automatic retransmission of messages not transmitted successfully
     *       enabled
     *   1 = Automatic retransmission disabled
     */
    uint32_t       wakeIntEnable;
    /**< CANFD wake-up interrupt enable (ERM_CTRL.WAKE_INT_EN).
     *   0 = Disabled
     *   1 = Enabled
     */
    uint32_t       wdcPreload;
    /**< Start value of the Message RAM Watchdog Counter
     *   Range:[0x0-0xFF]
     */
    CANFD_TDCConfig tdcConfig;
    /**< Transmitter Delay Compensation parameters.
     *   Refer struct #CANFD_TDCConfig.
     */
    uint32_t       tdcEnable;
    /**< Transmitter Delay Compensation Enable
     *   0 = Transmitter Delay Compensation is disabled
     *   1 = Transmitter Delay Compensation is enabled
     */
}CANFD_InitParams;

/**
 * \brief  Structure for CANFD configuration parameters.
 */
typedef struct
{
    uint32_t              monEnable;
    /**< Bus Monitoring Mode
     *   0 = Bus Monitoring Mode is disabled
     *   1 = Bus Monitoring Mode is enabled
     */
    uint32_t              asmEnable;
    /**< Restricted Operation Mode
     *   0 = Normal CAN operation
     *   1 = Restricted Operation Mode active
     *   This mode should not be combined with test modes.
     */
    uint32_t              tsPrescalar;
    /**< Timestamp Counter Prescaler.
     *   Range:[0x0-0xF]
     */
    uint32_t              tsSelect;
    /**< Timestamp source selection (TSCC.TSS).
     *   00 = Timestamp counter value always 0x0000
     *   01 = Timestamp counter incremented per tsPrescalar
     *   10 = Reserved; CANFD_config() uses internal counter mode (01) instead
     *   11 = Same as 00
     *   External timestamp for RX/TX uses ERM via CANFD_extTSCounterConfig()
     *   and CANFD_extTSCounterEnable().
     */
    uint32_t              timeoutSelect;
    /**< Time-out counter source select.
     *   Refer enum #CANFD_TimeOutSelect.
     */
    uint32_t              timeoutPreload;
    /**< Start value of the Timeout Counter (down-counter).
     *   The Timeout Counter is decremented in multiples of CAN bit times [1-16]
     *   depending on the configuration of the tsPrescalar.
     *   Range:[0x0-0xFFFF]
     */
    uint32_t              timeoutCntEnable;
    /**< Time-out Counter Enable
     *   0 = Time-out Counter is disabled
     *   1 = Time-out Counter is enabled
     */
    CANFD_GlobalFiltConfig filterConfig;
    /**< Global Filter Configuration parameters.
     *    Refer struct #CANFD_GlobalFiltConfig.
     */
}CANFD_ConfigParams;

/**
 * \brief  Structure for CANFD error logging counters status.
 */
typedef struct
{
    uint32_t transErrLogCnt;
    /**< Transmit Error Counter */
    uint32_t recErrCnt;
    /**< Receive Error Counter */
    uint32_t rpStatus;
    /**< Receive Error Passive
     *   0 = The Receive Error Counter is below the error passive level(128)
     *   1 = The Receive Error Counter has reached the error passive level(128)
     */
    uint32_t canErrLogCnt;
    /**< CAN Error Logging */
}CANFD_ErrCntStatus;

/**
 * \brief  Structure for CANFD protocol status.
 */
typedef struct
{
    uint32_t lastErrCode;
    /**< Last Error Code
     *   Refer enum #CANFD_ErrCode
     */
    uint32_t act;
    /**< Activity - Monitors the module's CAN communication state.
     *   refer enum #CANFD_ComState
     */
    uint32_t errPassive;
    /**< Error Passive
     *   0 = The CANFD module is in the Error_Active state
     *   1 = The CANFD module is in the Error_Passive state
     */
    uint32_t warningStatus;
    /**< Warning Status
     *   0 = Both error counters are below the Error_Warning limit of 96
     *   1 = At least one of error counter has reached the Error_Warning
     *       limit of 96
     */
    uint32_t busOffStatus;
    /**< Bus_Off Status
     *   0 = The CANFD module is not Bus_Off
     *   1 = The CANFD module is in Bus_Off state
     */
    uint32_t dlec;
    /**< Data Phase Last Error Code
     *   Refer enum #CANFD_ErrCode
     */
    uint32_t resi;
    /**< ESI flag of last received CAN FD Message
     *   0 = Last received CAN FD message did not have its ESI flag set
     *   1 = Last received CAN FD message had its ESI flag set
     */
    uint32_t rbrs;
    /**< BRS flag of last received CAN FD Message
     *   0 = Last received CAN FD message did not have its BRS flag set
     *   1 = TLast received CAN FD message had its BRS flag set
     */
    uint32_t rfdf;
    /**< Received a CAN FD Message
     *   0 = Since this bit was reset by the CPU, no CAN FD message has been
     *       received
     *   1 = Message in CAN FD format with FDF flag set has been received
     */
    uint32_t pxe;
    /**< Protocol Exception Event
     *   0 = No protocol exception event occurred since last read access
     *   1 = Protocol exception event occurred
     */
    uint32_t tdcv;
    /**< Transmitter Delay Compensation Value */
}CANFD_ProtocolStatus;

/**
 * \brief  Structure for CANFD Message RAM Configuration Parameters.
 *         Message RAM can contain following sections:
 *         Standard ID filters, Extended ID filters, TX FIFO(or TX Q),
 *         TX Buffers, TX EventFIFO, RX FIFO0, RX FIFO1, RX Buffer.
 *         Note: If particular section in the RAM is not used then it's size
 *         should be initialized to '0'
 *         (Number of buffers in case of Tx/Rx buffer).
 */
typedef struct
{
    uint32_t flssa;
    /**< Standard ID Filter List Start Address */
    uint32_t lss;
    /**< List Size: Standard ID
     *   0 = No standard Message ID filter
     *   1-127 = Number of standard Message ID filter elements
     *   others = Values greater than 128 are interpreted as 128
     */
    uint32_t flesa;
    /**< Extended ID Filter List Start Address */
    uint32_t lse;
    /**< List Size: Extended ID
     *   0 = No standard Message ID filter
     *   1-64 = Number of standard Message ID filter elements
     *   others = Values greater than 64 are interpreted as 64
     */
    uint32_t txStartAddr;
    /**< Tx Buffers Start Address */
    uint32_t txBufNum;
    /**< Number of Dedicated Transmit Buffers
     *   0 = No Dedicated Tx Buffers
     *   1-32 = Number of Dedicated Tx Buffers
     *   others = Values greater than 32 are interpreted as 32
     */
    uint32_t txFIFOSize;
    /**< Transmit FIFO/Queue Size
     *   0 = No Tx FIFO/Queue
     *   1-32 = Number of Tx Buffers used for Tx FIFO/Queue
     *   others = Values greater than 32 are interpreted as 32
     */
    uint32_t txBufMode;
    /**< Tx FIFO/Queue Mode
     *   0 = Tx FIFO operation
     *   1 = Tx Queue operation
     */
    uint32_t txBufElemSize;
    /**< Tx Buffer Element Size */
    uint32_t txEventFIFOStartAddr;
    /**< Tx Event FIFO Start Address */
    uint32_t txEventFIFOSize;
    /**< Event FIFO Size
     *   0 = Tx Event FIFO disabled
     *   1-32 = Number of Tx Event FIFO elements
     *   others = Values greater than 32 are interpreted as 32
     */
    uint32_t txEventFIFOWaterMark;
    /**< Tx Event FIFO Watermark
     *   0 = Watermark interrupt disabled
     *   1-32 = Level for Tx Event FIFO watermark interrupt
     *   others = Watermark interrupt disabled
     */
    uint32_t rxFIFO0startAddr;
    /**< Rx FIFO0 Start Address */
    uint32_t rxFIFO0size;
    /**< Rx FIFO0 Size
     *   0 = No Rx FIFO
     *   1-64 = Number of Rx FIFO elements
     *   others = Values greater than 64 are interpreted as 64
     */
    uint32_t rxFIFO0waterMark;
    /**< Rx FIFO0 Watermark
     *   0 = Watermark interrupt disabled
     *   1-63 = Level for Rx FIFO 0 watermark interrupt
     *   others = Watermark interrupt disabled
     */
    uint32_t rxFIFO0OpMode;
    /**< Rx FIFO0 Operation Mode
     *   0 = FIFO blocking mode
     *   1 = FIFO overwrite mode
     */
    uint32_t rxFIFO1startAddr;
    /**< Rx FIFO1 Start Address */
    uint32_t rxFIFO1size;
    /**< Rx FIFO1 Size
     *   0 = No Rx FIFO
     *   1-64 = Number of Rx FIFO elements
     *   others = Values greater than 64 are interpreted as 64
     */
    uint32_t rxFIFO1waterMark;
    /**< Rx FIFO1 Watermark
     *   0 = Watermark interrupt disabled
     *   1-63 = Level for Rx FIFO 1 watermark interrupt
     *   others = Watermark interrupt disabled
     */
    uint32_t rxFIFO1OpMode;
    /**< Rx FIFO1 Operation Mode
     *   0 = FIFO blocking mode
     *   1 = FIFO overwrite mode
     */
    uint32_t rxBufStartAddr;
    /**< Rx Buffer Start Address */
    uint32_t rxBufElemSize;
    /**< Rx Buffer Element Size */
    uint32_t rxFIFO0ElemSize;
    /**< Rx FIFO0 Element Size */
    uint32_t rxFIFO1ElemSize;
    /**< Rx FIFO1 Element Size */
}CANFD_MsgRAMConfigParams;

/**
 * \brief  Structure for CANFD High Priority Message.
 */
typedef struct
{
    uint32_t bufIdx;
    /**< Buffer Index
     *   Only valid when MSI[2:0] = '100'.
     */
    uint32_t msi;
    /**< Message Storage Indicator
     *   MSI[1:0]
     *       00  = No FIFO selected
     *       01  = FIFO message lost
     *       10  = Message stored in FIFO 0
     *       11  = Message stored in FIFO 1
     */
    uint32_t filterIdx;
    /**< Filter Index */
    uint32_t filterList;
    /**< Indicates the filter list of the matching filter element
     *   0 = Standard Filter List
     *   1 = Extended Filter List
     */
}CANFD_HighPriorityMsgInfo;

/**
 * \brief  Structure for CANFD new data flag for Rx buffer.
 */
typedef struct
{
    uint32_t statusLow;
    /**< New data flag for Rx buffer no. 0 to 31 */
    uint32_t statusHigh;
    /**< New data flag for Rx buffer no. 32 to 63 */
}CANFD_RxNewDataStatus;

/**
 * \brief  Structure for CANFD Rx FIFO Status.
 */
typedef struct
{
    uint32_t num;
    /**< Rx FIFO number
     *   Refer enum #CANFD_RxFIFONum
     */
    uint32_t fillLvl;
    /**< Rx FIFO Fill Level */
    uint32_t getIdx;
    /**< Rx FIFO Get Index */
    uint32_t putIdx;
    /**< Rx FIFO Put Index */
    uint32_t fifoFull;
    /**< Rx FIFO Full
     *   0 = Rx FIFO not full
     *   1 = Rx FIFO full
     */
    uint32_t msgLost;
    /**< Rx FIFO Message Lost */
}CANFD_RxFIFOStatus;

/**
 * \brief  Structure for CANFD Tx FIFO Status.
 */
typedef struct
{
    uint32_t freeLvl;
    /**< Tx FIFO Free Level */
    uint32_t getIdx;
    /**< Tx FIFO Get Index
     *   Read as zero when Tx Queue operation is configured.
     */
    uint32_t putIdx;
    /**< Tx FIFO/Queue Put Index */
    uint32_t fifoFull;
    /**< Tx FIFO/Queue Full
     *   0 = Tx FIFO/Queue not full
     *   1 = Tx FIFO/Queue full
     */
}CANFD_TxFIFOStatus;

/**
 * \brief  Structure for CANFD Tx Event FIFO Status.
 */
typedef struct
{
    uint32_t fillLvl;
    /**< Event FIFO Fill Level */
    uint32_t getIdx;
    /**< Event FIFO Gut Index */
    uint32_t putIdx;
    /**< Event FIFO Put Index */
    uint32_t fifoFull;
    /**< Event FIFO Full
     *   0 = Tx Event FIFO not full
     *   1 = Tx Event FIFO full
     */
    uint32_t eleLost;
    /**< Tx Event FIFO Element Lost
     *   0 = No Tx Event FIFO element lost
     *   1 = Tx Event FIFO element lost, also set after write attempt to
     *       Tx Event FIFO of size zero.
     */
}CANFD_TxEventFIFOStatus;

/**
 * \brief  Structure for ECC Error forcing.
 */
typedef struct
{
    uint32_t errType;
    /**< Error type to be forced
     *   Refer enum  #CANFD_ECCErrType.
     */
    uint32_t rowNum;
    /**< Row address where error needs to be applied. */
    uint32_t bit1;
    /**< Column/Data bit that needs to be flipped when
     *   force_sec or force_ded is set
     */
    uint32_t bit2;
    /**< Data bit that needs to be flipped when force_ded is set */
    uint32_t errOnce;
    /**< Force Error once
     *   1: The error will inject an error to the specified row only once
     */
    uint32_t errForce;
    /**< Force error on the next RAM read */
}CANFD_ECCErrForceParams;

/**
 * \brief  Structure for ECC Error Status.
 */
typedef struct
{
    uint32_t secErr;
    /**< Single Bit Error Status
     *   0 = No Single Bit Error pending
     *   1 = Single Bit Error pending
     */
    uint32_t dedErr;
    /**< Double Bit Error Status
     *   0 = No Double Bit Error pending
     *   1 = Double Bit Error pending
     */
    uint32_t errorAddress;
    /**< The address of the error found
     *   (bits [9:0]) 
     */
    uint32_t errorData;    
    /**< The data of the error found
     *   (32-bit) 
     */
} CANFD_ECCErrStatus;



/**
 * \brief  Structure for accessing Revision ID and Core Release Info.
 *         of CANFD module.
 */
typedef struct
{
    uint32_t day;
    /**< Time Stamp Day. Two digits, BCD-coded. */
    uint32_t mon;
    /**< Time Stamp Month. Two digits, BCD-coded. */
    uint32_t year;
    /**< Time Stamp Year. Single digit, BCD-coded. */
    uint32_t subStep;
    /**< Sub-step of Core Release Single digit, BCD-coded. */
    uint32_t step;
    /**< Step of Core Release.Two digits, BCD-coded Single digit, BCD-coded. */
    uint32_t rel;
    /**< Core Release. Single digit, BCD-coded. */
}CANFD_RevisionId;

/**
 * \brief  Structure for accessing Revision ID of ECC AGGR.
 */
typedef struct
{
    uint32_t scheme;
    /**< Scheme */
    uint32_t bu;
    /**< Business Unit: 10 = Processors */
    uint32_t modId;
    /**< Module ID */
    uint32_t rtlRev;
    /**< RTL revision */
    uint32_t major;
    /**< Major revision */
    uint32_t custom;
    /**< Custom revision */
    uint32_t minor;
    /**< Minor revision */
}CANFD_ECCAggrRevisionId;

/**
 * \brief  Structure for CANFD ECC configuration parameters.
 */
typedef struct
{
    uint32_t eccEnable;
    /**< 0 = Disable SRAM ECC check  
     *   1 = Enable SRAM ECC check  */

    uint32_t becIntEnable;
    /**< 0 = Single-bit error corrected interrupt disabled  
     *   1 = Single-bit error corrected interrupt enabled  */

    uint32_t beuIntEnable;
    /**< 0 = Multiple-bit error uncorrectable interrupt disabled  
     *   1 = Multiple-bit error uncorrectable interrupt enabled  */
} CANFD_ECCConfigParams;

/**
 * \brief  Structure for accessing Revision ID of ECC wrapper.
 */
typedef struct
{
    uint32_t scheme;
    /**< Scheme */
    uint32_t bu;
    /**< Business Unit: 10 = Processors */
    uint32_t modId;
    /**< Module ID */
    uint32_t rtlRev;
    /**< RTL revision */
    uint32_t major;
    /**< Major revision */
    uint32_t custom;
    /**< Custom revision */
    uint32_t minor;
    /**< Minor revision */
}CANFD_ECCWrapRevisionId;

/**
 * \brief  Structure for CANFD Tx Buffer element.
 */
typedef struct
{
    uint32_t id;
    /**< Identifier */
    uint32_t rtr;
    /**< Remote Transmission Request
     *   0 = Transmit data frame
     *   1 = Transmit remote frame
     */
    uint32_t xtd;
    /**< Extended Identifier
     *   0 = 11-bit standard identifier
     *   1 = 29-bit extended identifier
     */
    uint32_t esi;
    /**< Error State Indicator
     *   0 = ESI bit in CAN FD format depends only on error passive flag
     *   1 = ESI bit in CAN FD format transmitted recessive
     */
    uint32_t dlc;
    /**< Data Length Code
     *   0-8  = CAN + CAN FD: transmit frame has 0-8 data bytes
     *   9-15 = CAN: transmit frame has 8 data bytes
     *   9-15 = CAN FD: transmit frame has 12/16/20/24/32/48/64 data bytes
     */
    uint32_t brs;
    /**< Bit Rat Switching
     *   0 = CAN FD frames transmitted without bit rate switching
     *   1 = CAN FD frames transmitted with bit rate switching
     */
    uint32_t fdf;
    /**< FD Format
     *   0 = Frame transmitted in Classic CAN format
     *   1 = Frame transmitted in CAN FD format
     */
    uint32_t efc;
    /**< Event FIFO Control
     *   0 = Don't store Tx events
     *   1 = Store Tx events
     */
    uint32_t mm;
    /**< Message Marker */
    uint16_t  data[CANFD_MAX_PAYLOAD_BYTES];
    /**< Data bytes.
     *   Only first dlc number of bytes are valid.
     */
}CANFD_TxBufElement;

/**
 * \brief  Structure for CANFD Rx Buffer element.
 */
typedef struct
{
    uint32_t id;
    /**< Identifier */
    uint32_t rtr;
    /**< Remote Transmission Request
     *   0 = Received frame is a data frame
     *   1 = Received frame is a remote frame
     */
    uint32_t xtd;
    /**< Extended Identifier
     *   0 = 11-bit standard identifier
     *   1 = 29-bit extended identifier
     */
    uint32_t esi;
    /**< Error State Indicator
     *   0 = Transmitting node is error active
     *   1 = Transmitting node is error passive
     */
    uint32_t rxts;
    /**< Rx Timestamp */
    uint32_t dlc;
    /**< Data Length Code
     *   0-8  = CAN + CAN FD: received frame has 0-8 data bytes
     *   9-15 = CAN: received frame has 8 data bytes
     *   9-15 = CAN FD: received frame has 12/16/20/24/32/48/64 data bytes
     */
    uint32_t brs;
    /**< Bit Rat Switching
     *   0 = Frame received without bit rate switching
     *   1 = Frame received with bit rate switching
     */
    uint32_t fdf;
    /**< FD Format
     *   0 = Standard frame format
     *   1 = CAN FD frame format (new DLC-coding and CRC)
     */
    uint32_t fidx;
    /**< Filter Index */
    uint32_t anmf;
    /**< Accepted Non-matching Frame
     *   0 = Received frame matching filter index FIDX
     *   1 = Received frame did not match any Rx filter element
     */
    uint16_t  data[CANFD_MAX_PAYLOAD_BYTES];
    /**< Data bytes.
     *   Only first dlc number of bytes are valid.
     */
}CANFD_RxBufElement;

/**
 * \brief  Structure for CANFD Tx Event FIFO element.
 */
typedef struct
{
    uint32_t id;
    /**< Identifier */
    uint32_t rtr;
    /**< Remote Transmission Request
     *   0 = Data frame transmitted
     *   1 = Remote frame transmitted
     */
    uint32_t xtd;
    /**< Extended Identifier
     *   0 = 11-bit standard identifier
     *   1 = 29-bit extended identifier
     */
    uint32_t esi;
    /**< Error State Indicator
     *   0 = Transmitting node is error active
     *   1 = Transmitting node is error passive
     */
    uint32_t txts;
    /**< Tx Timestamp */
    uint32_t dlc;
    /**< Data Length Code
     *   0-8  = CAN + CAN FD: frame with 0-8 data bytes transmitted
     *   9-15 = CAN: frame with 8 data bytes transmitted
     *   9-15 = CAN FD: frame with 12/16/20/24/32/48/64 data bytes transmitted
     */
    uint32_t brs;
    /**< Bit Rat Switching
     *   0 = Frame transmitted without bit rate switching
     *   1 = Frame transmitted with bit rate switching
     */
    uint32_t fdf;
    /**< FD Format
     *   0 = Standard frame format
     *   1 = CAN FD frame format (new DLC-coding and CRC)
     */
    uint32_t et;
    /**< Event Type
     *   00 = Reserved
     *   01 = Tx event
     *   10 = Transmission in spite of cancellation
     *        (always set for transmissions in DAR mode)
     *   11 = Reserved
     */
    uint32_t mm;
    /**< Message Marker */
}CANFD_TxEventFIFOElement;

/**
 * \brief  Structure for CANFD Standard Message ID Filter Element.
 */
typedef struct
{
    uint32_t sfid2;
    /**< Standard Filter ID 2 */
    uint32_t sfid1;
    /**< Standard Filter ID 1 */
    uint32_t sfec;
    /**< Standard Filter Element Configuration (macros defined for each value)
     *   000 = Disable filter element                               (CANFD_STDFILTEC_DISABLE)
     *   001 = Store in Rx FIFO 0 if filter matches                 (CANFD_STDFILTEC_FIFO0)
     *   010 = Store in Rx FIFO 1 if filter matches                 (CANFD_STDFILTEC_FIFO1)
     *   011 = Reject ID if filter matches                          (CANFD_STDFILTEC_REJECT)
     *   100 = Set priority if filter matches                       (CANFD_STDFILTEC_PRI)
     *   101 = Set priority and store in FIFO 0 if filter matches   (CANFD_STDFILTEC_PRI_FIFO0)
     *   110 = Set priority and store in FIFO 1 if filter matches   (CANFD_STDFILTEC_PRI_FIFO1)
     *   111 = Store into Rx Buffer or as debug message,            (CANFD_STDFILTEC_RXBUFF)
     *         configuration of SFT[1:0] ignored.
     *   If SFEC = '100', '101', or '110' a match sets high priority
     *   message event is generated.
     */
    uint32_t sft;
    /**< Standard Filter Type (macros defined for each value)
     *   00 = Range filter from SFID1 to SFID2 (SFID2 >= SFID1)  (CANFD_STDFILT_RANGE)
     *   01 = Dual ID filter for SFID1 or SFID2                 (CANFD_STDFILT_DUAL)
     *   10 = Classic filter: SFID1 = filter, SFID2 = mask      (CANFD_STDFILT_CLASSIC)
     *   11 = Filter element disabled                           (CANFD_STDFILT_DISABLED)
     */
}CANFD_StdMsgIDFilterElement;

/**
 * \brief  Structure for CANFD Extended Message ID Filter Element.
 */
typedef struct
{
    uint32_t efid1;
    /**< Extended Filter ID 1 */
    uint32_t efec;
    /**< Extended Filter Element Configuration
     *   000 = Disable filter element
     *   001 = Store in Rx FIFO 0 if filter matches
     *   010 = Store in Rx FIFO 1 if filter matches
     *   011 = Reject ID if filter matches
     *   100 = Set priority if filter matches
     *   101 = Set priority and store in FIFO 0 if filter matches
     *   110 = Set priority and store in FIFO 1 if filter matches
     *   111 = Store into Rx Buffer or as debug message,
     *         configuration of SFT[1:0] ignored.
     *   If EFEC = '100', '101', or '110' a match sets high priority
     *   message event is generated.
     */
    uint32_t efid2;
    /**< Extended Filter ID 2 */
    uint32_t eft;
    /**< Extended Filter Type
     *   00 = Range filter from EFID1 to EFID2 (EFID2 >= EFID1)
     *   01 = Dual ID filter for EFID1 or EFID2
     *   10 = Classic filter: EFID1 = filter, EFID2 = mask
     *   11 = Range filter from EFID1 to EFID2 (EFID2 >= EFID1),
     *        XIDAM mask not applied
     */
}CANFD_ExtMsgIDFilterElement;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */


/**
 * \brief   This function selects the specified clock source for the CANFD controller.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   source          Clock source to use for the CANFD controller.
 *
 * The \e source parameter can be any one of the following:
 * - \b CANFD_CLOCK_SOURCE_APB    - APBCLK (reset default)
 * - \b CANFD_CLOCK_SOURCE_XTAL   - External oscillator (XTAL)
 * - \b CANFD_CLOCK_SOURCE_AUXCLK - GPIO29 / AUXCLK
 *
 * \retval  None
 */
void CANFD_selectClockSource(uint32_t baseAddr, CANFD_ClockSource source);

/**
 * \brief   This API will return flexible data rate operation status
 *          CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  state           Returns TRUE if flexible data rate operation
 *                          is enabled. Else returns FALSE.
 */
uint32_t CANFD_isFDOpEnable(uint32_t baseAddr);

/**
 * \brief   This function checks if the memory initialization is done for
 *          CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \retval  state           Returns TRUE if memory initialization is done.
 *                          Else returns FALSE.
 */
uint32_t CANFD_isMemInitDone(uint32_t baseAddr);

/**
 * \brief   Start ERM Message RAM hardware initialization and wait for completion.
 *
 *          Idempotent: returns #STW_SOK immediately if #CANFD_isMemInitDone is
 *          already true. Call before #CANFD_msgRAMConfig, filter programming,
 *          or Message RAM access. Required by the device manual before enabling
 *          ECC via #CANFD_eccConfig; not invoked from #CANFD_init.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   timeoutCount    Poll iterations while waiting for RAM init done;
 *                          use \c 0x000FFFFFU if unsure (same order as
 *                          #CANFD_init internal timeouts).
 *
 * \return  status          #STW_SOK on success, #STW_EFAIL on timeout.
 */
int32_t CANFD_requestAndWaitMemInit(uint32_t baseAddr, uint32_t timeoutCount);

/**
 * \brief   This API will set CANFD module mode of operation.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   mode            Mode of operation.
 *                          Refer enum #CANFD_OperationMode.
 *
 * \return  None.
 */
void CANFD_setOpMode(uint32_t baseAddr, uint32_t mode);

/**
 * \brief   This API will return CANFD module mode of operation.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  mode            Mode of operation.
 *                          Refer enum #CANFD_OperationMode.
 */
uint32_t CANFD_getOpMode(uint32_t baseAddr);

/**
 * \brief   This API will initialize CANFD module.
 *
 *          Does not perform ERM Message RAM initialization; call
 *          #CANFD_requestAndWaitMemInit before entering INIT mode when RAM
 *          has not been initialized since reset.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   initParams      Initialization parameters.
 *                          Refer struct #CANFD_InitParams.
 *
 * \return  status          Initialization status.
 */
int32_t CANFD_init(uint32_t baseAddr, const CANFD_InitParams *initParams);

/**
 * \brief   This API will configure CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   configParams    configuration parameters.
 *                          Refer struct #CANFD_ConfigParams.
 *
 * \return  status          Configuration status.
 */
int32_t CANFD_config(uint32_t baseAddr, const CANFD_ConfigParams *configParams);

/**
 * \brief   This API will enable/disable ECC on the Message RAM.
 *
 *          Call only after Message RAM initialization
 *          (#CANFD_requestAndWaitMemInit). BEC/BEU interrupts use dedicated
 *          NVIC lines, not #CANFD_IR.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   configParams    CANFD ECC Configuration Parameters.
 *                          Refer #struct CANFD_ECCConfigParams.
 *
 * \return  None.
 */
void CANFD_eccConfig(uint32_t                    baseAddr,
                    const CANFD_ECCConfigParams *configParams);

/**
 * \brief   This API will configure a bit timings for CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   configParams    Configuration parameters for CANFD bit timing.
 *                          Refer struct #CANFD_BitTimingParams.
 *
 * \return  status          Bit Timings configuration status.
 */
int32_t CANFD_setBitTime(uint32_t                    baseAddr,
                        const CANFD_BitTimingParams *configParams);

/**
 * \brief   This API will configure Different sections of Message RAM.
 *
 *          Message RAM must be initialized (#CANFD_requestAndWaitMemInit)
 *          before this call. A receive-only layout (\c txBufNum=0 and
 *          \c txFIFOSize=0) is valid and returns #STW_SOK.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   msgRAMConfigParams
 *                          Message RAM Configuration parameters.
 *                          Refer struct #CANFD_MsgRAMConfigParams.
 *
 * \return  status          Configuration Status.
 */
int32_t CANFD_msgRAMConfig(uint32_t                       baseAddr,
                          const CANFD_MsgRAMConfigParams *msgRAMConfigParams);

/**
 * \brief   This API will configure Extended ID AND Mask.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   idMask          Configuration parameters for CANFD Extended Id mask.
 *                          This value is 29 bit wide.
 *
 * \return  status          Extended ID AND Mask configuration status.
 */
int32_t CANFD_setExtIDAndMask(uint32_t baseAddr, uint32_t idMask);

/**
 * \brief   This API is used to write Tx message to message RAM.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   memType         Part of message ram to which given message to write.
 *                          Refer enum #CANFD_MemType.
 * \param   bufNum          Buffer  number where message to write.
 *                          This parameter will ignored if memType is FIFO/Q.
 * \param   elem            Message Object.
 *                          Refer struct #CANFD_TxBufElement.
 *
 * \return  None.
 */
void CANFD_writeMsgRam(uint32_t                 baseAddr,
                      uint32_t                 memType,
                      uint32_t                 bufNum,
                      const CANFD_TxBufElement *elem);

/**
 * \brief   This API will set Tx Buffer Add Request.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   bufNum          Tx Buffer number for which request is to be added.
 *
 * \return  status          Configuration Status.
 */
int32_t CANFD_txBufAddReq(uint32_t baseAddr, uint32_t bufNum);

/**
 * \brief   This API will return New Data Message Status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   newDataStatus   Rx Buffer new data status.
 *                          Refer struct #CANFD_RxNewDataStatus.
 *
 * \return  None.
 */
void  CANFD_getNewDataStatus(uint32_t              baseAddr,
                            CANFD_RxNewDataStatus *newDataStatus);

/**
 * \brief   This API clear New Data Message Status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   newDataStatus
 *                          Rx Buffer new data status.
 *                          Refer struct #CANFD_RxNewDataStatus.
 *
 * \return  None.
 */
void  CANFD_clearNewDataStatus(uint32_t                    baseAddr,
                              const CANFD_RxNewDataStatus *newDataStatus);

/**
 * \brief   This API is used to read received message from Message RAM.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   memType         Part of message ram to which given message to write.
 *                          Refer enum #CANFD_MemType.
 * \param   bufNum          Buffer  number from where message is to read.
 *                          This parameter will ignored if memType is FIFO/Q.
 *  \param  fifoNum         FIFOs number from where message is to read.
 *                          Refer enum #CANFD_RxFIFONum.
 *                          This parameter will ignored if memType is buffer.
 * \param   elem            Message Object.
 *                          Refer struct #CANFD_RxBufElement.
 *
 * \return  None.
 */
void CANFD_readMsgRam(uint32_t           baseAddr,
                     uint32_t           memType,
                     uint32_t           bufNum,
                     uint32_t           fifoNum,
                     CANFD_RxBufElement *elem);                    

/**
 * \brief   This API is used to read from Tx Event FIFO.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   txEventElem     Tx Event FIFO Message Object.
 *                          Refer struct #CANFD_TxEventFIFOElement.
 *
 * \return  None.
 */
void CANFD_readTxEventFIFO(uint32_t           baseAddr,
                          CANFD_TxEventFIFOElement *txEventElem);

/**
 * \brief   This API is used to add Standard Message ID Filter Element.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   filtNum         Filter number.
 * \param   elem            Filter Object.
 *                          Refer struct #CANFD_StdMsgIDFilterElement.
 *
 * \return  None.
 */
void CANFD_addStdMsgIDFilter(uint32_t                          baseAddr,
                            uint32_t                          filtNum,
                            const CANFD_StdMsgIDFilterElement *elem);

/**
 * \brief   This API is used to add Extended Message ID Filter Element.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   filtNum         Filter  number.
 * \param   elem            Filter Object.
 *                          Refer struct #CANFD_ExtMsgIDFilterElement.
 *
 * \return  None.
 */
void CANFD_addExtMsgIDFilter(uint32_t                          baseAddr,
                            uint32_t                          filtNum,
                            const CANFD_ExtMsgIDFilterElement *elem);

/**
 * \brief   This API will enable/disable Loop Back Test Mode for
 *          CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   lpbkMode        Loopback mode for CANFD.
 *                          Refer #enum CANFD_LpbkMode.
 * \param   enable          Loop Back Mode is enabled if it is TRUE.
 *                          Loop Back Mode is disabled  if it is FALSE.
 *
 * \return  None.
 * \note    This API can be called only when CANFD is in Software
 *          Initialization mode of operation.
 */
void CANFD_lpbkModeEnable(uint32_t baseAddr,
                         uint32_t lpbkMode,
                         uint32_t enable);

/**
 * \brief   This API will return error counter status for CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   errCounter      Error Counter Status.
 *                          Refer struct #CANFD_ErrCntStatus.
 *
 * \return  None.
 */
void  CANFD_getErrCounters(uint32_t           baseAddr,
                          CANFD_ErrCntStatus *errCounter);

/**
 * \brief   This API will return protocol status for CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   protStatus      Protocol Status.
 *                          Refer struct #CANFD_ProtocolStatus.
 *
 * \return  None.
 */
void  CANFD_getProtocolStatus(uint32_t             baseAddr,
                             CANFD_ProtocolStatus *protStatus);

/**
 * \brief   This API is used to enable/disable interrupts.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   intrMask        Interrupts to enable.
 *                          Refer enum #CANFD_IntrSrc.
 * \param   enable          Interrupt is enabled if it is TRUE.
 *                          Interrupt is disabled  if it is FALSE.
 *
 * \return  None.
 */
void CANFD_enableIntr(uint32_t baseAddr, uint32_t intrMask, uint32_t enable);

/**
 * \brief   This API is used to select interrupt line.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   intrMask        Interrupt Number for which interrupt
 *                          line is to be selected. Refer enum #CANFD_IntrSrc.
 * \param   lineNum         Interrupt Line to select.
 *                          Refer enum #CANFD_IntrLineNum,
 *
 * \return  None.
 */
void CANFD_selectIntrLine(uint32_t baseAddr,
                         uint32_t intrMask,
                         uint32_t lineNum);

/**
 * \brief   This API is used to get interrupt line selected for each interrupt.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  status          Interrupt Line Select Status.
 */
uint32_t CANFD_getIntrLineSelectStatus(uint32_t baseAddr);

/**
 * \brief   This API is used to enable/disable selected interrupt line.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   lineNum         Interrupt Line to select.
 *                          Refer enum #CANFD_IntrLineNum,
 * \param   enable          Interrupt Line is enabled if it is 1.
 *                          Interrupt Line is disabled  if it is 0.
 *
 * \return  None.
 */
void CANFD_enableIntrLine(uint32_t baseAddr,
                         uint32_t lineNum,
                         uint32_t enable);

/**
 * \brief   This API will return interrupt status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  status          Interrupt Status.
 */
uint32_t CANFD_getIntrStatus(uint32_t baseAddr);

/**
 * \brief   This API is used to clear the interrupt status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   intrMask        Interrupts to clear status.
 *
 * \return  None.
 */
void CANFD_clearIntrStatus(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief   This API will return High Priority Message Status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   hpm             High Priority Message Status.
 *                          Refer struct #CANFD_HighPriorityMsgInfo.
 *
 * \return  None.
 */
void  CANFD_getHighPriorityMsgStatus(uint32_t                  baseAddr,
                                    CANFD_HighPriorityMsgInfo *hpm);

/**
 * \brief   This API will read the High Priority message object from Message RAM.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   elem            Message Object.
 *                          Refer struct #CANFD_RxBufElement.
 *
 * \return  None.
 */
void CANFD_readHighPriorityMsgRam(uint32_t           baseAddr,
                                        CANFD_RxBufElement *elem);                                      

/**
 * \brief   This API will Rx FIFO status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   fifoStatus      Rx FIFO Status.
 *                          Refer struct #CANFD_RxFIFOStatus.
 *
 * \return  None.
 */
void CANFD_getRxFIFOStatus(uint32_t           baseAddr,
                          CANFD_RxFIFOStatus *fifoStatus);

/**
 * \brief   This API will write Rx FIFO Acknowledgement.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *                          Refer enum #CANFD_RxFIFONum.
 * \param   fifoNum         FIFO Number.
 * \param   idx             Rx FIFO Acknowledge Index
 *
 * \return  status          Acknowledgement Status.
 */
int32_t CANFD_writeRxFIFOAck(uint32_t baseAddr,
                            uint32_t fifoNum,
                            uint32_t idx);

/**
 * \brief   This API will Tx FIFO status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   fifoStatus      Tx FIFO Status.
 *                          Refer struct #CANFD_TxFIFOStatus.
 *
 * \return  None.
 */
void CANFD_getTxFIFOQueStatus(uint32_t           baseAddr,
                             CANFD_TxFIFOStatus *fifoStatus);

/**
 * \brief   This API will return Tx Buffer Request Pending status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  status          Tx Buffer Request Pending status.
 */
uint32_t CANFD_getTxBufReqPend(uint32_t baseAddr);

/**
 * \brief   This API will set Tx Buffer Cancellation Request.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   buffNum         Tx Buffer number for which request is to be added.
 *
 * \return  status          Configuration Status.
 */
int32_t CANFD_txBufCancellationReq(uint32_t baseAddr, uint32_t buffNum);

/**
 * \brief   This API will return Tx Buffer Transmission Occurred status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  status          Tx Buffer Transmission Occurred status.
 */
uint32_t CANFD_getTxBufTransmissionStatus(uint32_t baseAddr);

/**
 * \brief   This API will return Transmit Buffer Cancellation Finished status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  status          Transmit Buffer Cancellation Finished status.
 */
uint32_t CANFD_txBufCancellationStatus(uint32_t baseAddr);

/**
 * \brief   This API is used to enable/disable Tx Buffer Transmission Interrupt.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   bufNum          Buffer number for which interrupt is to enable.
 * \param   enable          Interrupt is enabled if it is TRUE.
 *                          Interrupt is disabled  if it is FALSE.
 *
 * \return  status          Configuration status.
 */
int32_t CANFD_txBufTransIntrEnable(uint32_t baseAddr,
                                  uint32_t bufNum,
                                  uint32_t enable);

/**
 * \brief   This API is used to enable/disable Tx Buffer Cancellation Finished
 *          Interrupt.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   bufNum         Buffer number for which interrupt is to enable.
 * \param   enable          Interrupt is enabled if it is TRUE.
 *                          Interrupt is disabled  if it is FALSE.
 *
 * \return  status          Configuration status.
 */
int32_t CANFD_getTxBufCancellationIntrEnable(uint32_t baseAddr,
                                            uint32_t bufNum,
                                            uint32_t enable);

/**
 * \brief   Set or clear the CANFD protocol-layer clock-stop request (CCCR.CSR).
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   enable          1 = assert CSR; 0 = de-assert CSR.
 *
 * \return  None.
 *
 * \note    Clock-stop uses two steps that work together:
 *          - **CCCR (protocol)**: #CANFD_addClockStopRequest and #CANFD_getClkStopAck.
 *            The CANFD core completes pending traffic, then sets CSA when ready.
 *          - **System control (clock gate)**: #CANFD_requestClockStop and
 *            #CANFD_isClockStopAcked shut off the CANFD peripheral clock after CSA
 *            is set.
 *          Typical sequence: assert CSR, poll #CANFD_getClkStopAck, then call
 *          #CANFD_requestClockStop and poll #CANFD_isClockStopAcked.
 */
void CANFD_addClockStopRequest(uint32_t baseAddr, uint32_t enable);

/**
 * \brief   This API will Tx Event FIFO status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   fifoStatus      Tx Event FIFO Status.
 *                          Refer struct #CANFD_TxEventFIFOStatus.
 *
 * \return  None.
 */
void CANFD_getTxEventFIFOStatus(uint32_t                baseAddr,
                               CANFD_TxEventFIFOStatus *fifoStatus);

/**
 * \brief   This API will write Event FIFO Acknowledge Index.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   idx             Event FIFO Acknowledge Index
 *
 * \return  status          Acknowledgement Status.
 */
int32_t CANFD_writeTxEventFIFOAck(uint32_t baseAddr, uint32_t idx);

/**
 * \brief   This API will return ECC Error status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   eccErr          ECC error status.
 *                          Refer struct #CANFD_ECCErrStatus.
 *
 * \return  None.
 */
void CANFD_eccGetErrorStatus(uint32_t           baseAddr,
                            CANFD_ECCErrStatus *eccErr);

/**
 * \brief   This API is used to clear the ECC Error status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   errType         Error type to clear status.
 *                          Refer enum #CANFD_ECCErrType.
 *
 * \return  None.
 */
void CANFD_eccClearErrorStatus(uint32_t baseAddr, uint32_t errType);

/**
 * \brief   This API is used to enable ECC interrupt.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   errType         Interrupt to enable.
 *                          Refer enum #CANFD_ECCErrType.
 * \param   enable          ECC Interrupt is enabled if it is TRUE.
 *                          ECC Interrupt is disabled  if it is FALSE.
 *
 * \return  None.
 */
void CANFD_eccEnableIntr(uint32_t baseAddr, uint32_t errType, uint32_t enable);

/**
 * \brief   This API is used to get ECC interrupt status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   errType         Interrupt status to read.
 *                          Refer enum #CANFD_ECCErrType.
 *
 * \return  None.
 */
uint32_t CANFD_eccGetIntrStatus(uint32_t baseAddr, uint32_t errType);

/**
 * \brief   This API is used to clear ECC interrupt status.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   errType         Interrupt status to clear.
 *                          Refer enum #CANFD_ECCErrType.
 *
 * \return  None.
 */
void CANFD_eccClearIntrStatus(uint32_t baseAddr, uint32_t errType);

/**
 * \brief   This API will configure external timestamp counter for CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   prescalar       Timestamp Counter Prescaler. Range:[0x0-0x3FFU]
 *
 * \return  None.
 *
 * \note    Actual value programmed prescalar values is (prescalar + 1).
 */
void CANFD_extTSCounterConfig(uint32_t baseAddr,
                             uint32_t prescalar);

/**
 * \brief   This API will enable/disable fast external time stamp counter for
 *          CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   enable          External TS is enabled if it is 1.
 *                          External TS is disabled  if it is 0.
 *
 * \return  None.
 */
void CANFD_extTSCounterEnable(uint32_t baseAddr, uint32_t enable);

/**
 * \brief  Get the current external time-stamp prescaler value.
 *
 * \param  baseAddr    Base Address of the CANFD Registers.
 *
 * \return             The 10-bit ETCP value read from the register.
 *
 * \note   The actual clock prescaler is (returned value + 1).
 */
uint16_t CANFD_extTSGetPrescaler(uint32_t baseAddr);

/**
 * \brief  Get the external time stamp counter and optionally reset it
 *
 * \param  baseAddr    Base Address of the CANFD Registers.
 *
 * \return The 16-bit value of the external time stamp counter.
 */
uint16_t CANFD_extTSGetCount(uint32_t baseAddr);

/* ========================================================================== */
/*                          Advance Functions                                 */
/* ========================================================================== */

/**
 * \brief   This API is check the CANFD base address.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  Returns \b true if base address is valid, otherwise \b false
 */
#ifdef DEBUG
static inline bool CANFD_isBaseValid(uint32_t baseAddr);
#endif

/**
 * \brief   This API is used get the CANFD revision ID.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   revId           Contains Revision ID of CANFD module.
 *                          Refer struct #CANFD_RevisionId.
 *
 * \return  None.
 */
void CANFD_getRevisionId(uint32_t baseAddr, CANFD_RevisionId *revId);

/**
 * \brief   Read CCCR.CSR (clock-stop request); legacy API name reads the request bit.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  status          1 if CSR is set, 0 otherwise.
 *
 * \note    Despite the name, this reads **CSR (request)**, not CSA (acknowledge).
 *          For the hardware acknowledge bit, use #CANFD_getClkStopAck.
 *          See #CANFD_addClockStopRequest for the two-layer clock-stop model.
 */
uint32_t CANFD_getClockStopAck(uint32_t baseAddr);

/**
 * \brief   This API will return Rx pin state of CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  state           CANFD Rx Pin State.
 *                          0= The CAN bus is dominant
 *                          1= The CAN bus is recessive
 */
uint32_t CANFD_getRxPinState(uint32_t baseAddr);

/**
 * \brief   This API will set Tx pin state of CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   state           CANFD Tx Pin State.
 *                          00= Reset value
 *                          01= Sample Point can be monitored at tx pin
 *                          10= The CAN bus is dominant
 *                          11= The CAN bus is recessive
 *                          other= It will treated as 11.
 *
 * \return  None.
 */
void CANFD_setTxPinState(uint32_t baseAddr, uint32_t state);

/**
 * \brief   This API will return Tx pin state of CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  state           CANFD Tx Pin State.
 *                          00= Reset value
 *                          01= Sample Point can be monitored at tx pin
 *                          10= The CAN bus is dominant
 *                          11= The CAN bus is recessive
 */
uint32_t CANFD_getTxPinState(uint32_t baseAddr);

/**
 * \brief   This API will return current timestamp counter value.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  val             Current Timestamp counter value.
 */
uint32_t CANFD_getTSCounterVal(uint32_t baseAddr);

/**
 * \brief   Read CCCR.CSA (CANFD clock-stop acknowledge).
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  ack             0 = CSA not set; 1 = CANFD ready for clock removal.
 *
 * \note    Protocol-layer acknowledge. Poll this after #CANFD_addClockStopRequest
 *          before calling #CANFD_requestClockStop. See #CANFD_addClockStopRequest.
 */
uint32_t CANFD_getClkStopAck(uint32_t baseAddr);

/**
 * \brief   This API will get the configured bit timings for CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   configParams    Configuration parameters for CANFD bit timing.
 *                          Refer struct #CANFD_BitTimingParams.
 *
 * \return  None.
 */
void CANFD_getBitTime(uint32_t              baseAddr,
                     CANFD_BitTimingParams *configParams);

/**
 * \brief   This API will reset timestamp counter value.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  None.
 */
void CANFD_resetTSCounter(uint32_t baseAddr);

/**
 * \brief   This API will return current time-out counter value.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  val             Current Time-out counter value.
 */
uint32_t CANFD_getTOCounterVal(uint32_t baseAddr);

/**
 * \brief   This function return endianness value of CANFD module.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \retval  val             Endianness value. (0x87654321)
 */
uint32_t CANFD_getEndianVal(uint32_t baseAddr);

/**
 * \brief   This API will get the configured Extended ID AND Mask.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  idMask          Extended ID AND Mask.
 */
uint32_t CANFD_getExtIDANDMask(uint32_t baseAddr);

/**
 * \brief   This API will return message object size.
 *
 * \param   elemSize        Element Size.
 *
 * \return  message object size
 *                          Size of the message object stored in Message RAM.
 */
uint32_t CANFD_getMsgObjSize(uint32_t elemSize);

/**
 * @brief   Enables or disables the CANFD wake-up interrupt (ERM_CTRL.WAKE_INT_EN).
 *
 * @param   baseAddr       Base address of the CANFD module.
 * @param   enable         Non-zero to enable; zero to disable.
 *
 * @return  None
 */
void CANFD_enableWakeupInterrupt(uint32_t baseAddr, uint32_t enable);

/**
 * @brief   Clears the wakeup interrupt status in ERM_STS register (W1C).
 *
 * @param   baseAddr         Base address of the CANFD module.
 *
 * @return  None
 */
void CANFD_wakeupClearIntrStatus(uint32_t baseAddr);

/**
 * \brief  Enable the RAM initialization request in the CANFD module.
 *
 * \param  baseAddr          Base Address of the CANFD module registers.
 *
 * \return None.
 */
void CANFD_enableRamInitRequest(uint32_t baseAddr);

/**
 * \brief  Disable the RAM initialization request in the CANFD module.
 *
 * \param  baseAddr          Base Address of the CANFD module registers.
 *
 * \return None.
 */
void CANFD_disableRamInitRequest(uint32_t baseAddr);

/**
 * \brief  Get the current external timestamp counter value.
 *
 * \param  baseAddr         Base Address of the CANFD module registers.
 *
 * \return timestamp        The current external timestamp counter (ETSC).
 */
uint16_t CANFD_getExtTimeStampCounter(uint32_t baseAddr);

/**
 * \brief  Clear the wake event status for the CANFD module.
 *
 * \param  baseAddr         Base Address of the CANFD module registers.
 *
 * \return None
 */
void CANFD_clearWakeStatus(uint32_t baseAddr);

/**
 * \brief  Get the wake-up status from the CANFDWAKESTATUS register.
 *
 * \param  baseAddr         Base Address of the CANFD module registers.
 *
 * \return flagStatus       Returns '1' if a wake event occurred, '0' otherwise.
 */
uint32_t CANFD_getWakeUpState(uint32_t baseAddr);

/**
 * \brief   Request CANFD peripheral clock stop.
 *
 * \param   baseAddr        Base Address of the CANFD module registers.
 *
 * \return  None.
 *
 * \note    Accesses `CANFDCLKSTOPREQ` in system control. Call only after
 *          #CANFD_getClkStopAck indicates the CCCR clock-stop handshake is
 *          complete. See #CANFD_addClockStopRequest for the recommended sequence.
 */
void CANFD_requestClockStop(uint32_t baseAddr);

/**
 * \brief   Check whether the CANFD peripheral clock-stop request is acknowledged.
 *
 * \param   baseAddr        Base Address of the CANFD module registers.
 *
 * \return  status          1 if `CANFDCLKSTOPACK` is set, 0 otherwise.
 *
 * \note    Poll after #CANFD_requestClockStop. See #CANFD_addClockStopRequest.
 */
uint32_t CANFD_isClockStopAcked(uint32_t baseAddr);

// Close the Doxygen group.
//! @}

#endif  // #ifdef __G32R502__

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
