//###########################################################################
//
// FILE:    canfd.c
//
// TITLE:   G32R502 CANFD driver.
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
// 1. Modified macro definitions and module naming and offsets.
// - 2026-08-21:
// 1. Add per-function banner comments in can.c style (comment only).
//
//###########################################################################

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include "inc/stw_types.h"
#include "inc/stw_dataTypes.h"
#include "canfd.h"
#include "debug.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  Mask and shift for Tx Buffers elements.
 */
#define CANFD_MSGRAM_TX_BUFFER_ELEM_ID_SHIFT                           (0U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_ID_MASK                            (0x1FFFFFFFU)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_RTR_SHIFT                          (29U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_RTR_MASK                           (0x20000000U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_XTD_SHIFT                          (30U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_XTD_MASK                           (0x40000000U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_ESI_SHIFT                          (31U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_ESI_MASK                           (0x80000000U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_DLC_SHIFT                          (16U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_DLC_MASK                           (0x000F0000U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_BRS_SHIFT                          (20U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_BRS_MASK                           (0x00100000U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_FDF_SHIFT                          (21U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_FDF_MASK                           (0x00200000U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_EFC_SHIFT                          (23U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_EFC_MASK                           (0x00800000U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_MM_SHIFT                           (24U)
#define CANFD_MSGRAM_TX_BUFFER_ELEM_MM_MASK                            (0xFF000000U)

/**
 * \brief  Mask and shift for Rx Buffers elements.
 */
#define CANFD_MSGRAM_RX_BUFFER_ELEM_ID_SHIFT                           (0U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_ID_MASK                            (0x1FFFFFFFU)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_RTR_SHIFT                          (29U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_RTR_MASK                           (0x20000000U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_XTD_SHIFT                          (30U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_XTD_MASK                           (0x40000000U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_ESI_SHIFT                          (31U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_ESI_MASK                           (0x80000000U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_RXTS_SHIFT                         (0U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_RXTS_MASK                          (0x0000FFFFU)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_DLC_SHIFT                          (16U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_DLC_MASK                           (0x000F0000U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_BRS_SHIFT                          (20U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_BRS_MASK                           (0x00100000U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_FDF_SHIFT                          (21U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_FDF_MASK                           (0x00200000U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_FIDX_SHIFT                         (24U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_FIDX_MASK                          (0x7F000000U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_ANMF_SHIFT                         (31U)
#define CANFD_MSGRAM_RX_BUFFER_ELEM_ANMF_MASK                          (0x80000000U)

/**
 * \brief  Mask and shift for Standard Message ID Filter Elements.
 */
#define CANFD_MSGRAM_STD_ID_FILTER_SFID2_SHIFT                         (0U)
#define CANFD_MSGRAM_STD_ID_FILTER_SFID2_MASK                          (0x000003FFU)
#define CANFD_MSGRAM_STD_ID_FILTER_SFID1_SHIFT                         (16U)
#define CANFD_MSGRAM_STD_ID_FILTER_SFID1_MASK                          (0x03FF0000U)
#define CANFD_MSGRAM_STD_ID_FILTER_SFEC_SHIFT                          (27U)
#define CANFD_MSGRAM_STD_ID_FILTER_SFEC_MASK                           (0x38000000U)
#define CANFD_MSGRAM_STD_ID_FILTER_SFT_SHIFT                           (30U)
#define CANFD_MSGRAM_STD_ID_FILTER_SFT_MASK                            (0xC0000000U)

/**
 * \brief  Extended Message ID Filter Element.
 */
#define CANFD_MSGRAM_EXT_ID_FILTER_EFID2_SHIFT                        (0U)
#define CANFD_MSGRAM_EXT_ID_FILTER_EFID2_MASK                         (0x1FFFFFFFU)
#define CANFD_MSGRAM_EXT_ID_FILTER_EFID1_SHIFT                        (0U)
#define CANFD_MSGRAM_EXT_ID_FILTER_EFID1_MASK                         (0x1FFFFFFFU)
#define CANFD_MSGRAM_EXT_ID_FILTER_EFEC_SHIFT                         (29U)
#define CANFD_MSGRAM_EXT_ID_FILTER_EFEC_MASK                          (0xE0000000U)
#define CANFD_MSGRAM_EXT_ID_FILTER_EFT_SHIFT                          (30U)
#define CANFD_MSGRAM_EXT_ID_FILTER_EFT_MASK                           (0xC0000000U)

/**
 * \brief  Loop timeout for CANFD_init sleep/INIT polling.
 */
#define CANFD_INIT_TIMEOUT_COUNT                                      (0x000FFFFFU)

/**
 * \brief  Mask and shift for Tx Event FIFO elements.
 */
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ID_SHIFT                      (0U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ID_MASK                       (0x1FFFFFFFU)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_RTR_SHIFT                     (29U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_RTR_MASK                      (0x20000000U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_XTD_SHIFT                     (30U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_XTD_MASK                      (0x40000000U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ESI_SHIFT                     (31U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ESI_MASK                      (0x80000000U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_TXTS_SHIFT                    (0U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_TXTS_MASK                     (0x0000FFFFU)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_DLC_SHIFT                     (16U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_DLC_MASK                      (0x000F0000U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_BRS_SHIFT                     (20U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_BRS_MASK                      (0x00100000U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_FDF_SHIFT                     (21U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_FDF_MASK                      (0x00200000U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ET_SHIFT                      (22U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ET_MASK                       (0x00C00000U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_MM_SHIFT                      (24U)
#define CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_MM_MASK                       (0xFF000000U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */                               

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API will unblock write access to write protected registers.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  None.
 */
static void CANFD_writeProtectedRegAccessUnlock(uint32_t baseAddr);

/**
 * \brief   This API will block write access to write protected registers.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 *
 * \return  None.
 */
static void CANFD_writeProtectedRegAccessLock(uint32_t baseAddr);

/**
 * \brief   This API will read the message object from Message RAM.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   elemAddr        Address of the message object.
 * \param   elem            Message Object.
 *                          Refer struct #CANFD_RxBufElement.
 *
 * \return  None.
 */
static void CANFD_readMsg(uint32_t           baseAddr,
                         uint32_t           elemAddr,
                         CANFD_RxBufElement *elem);                        

/**
 * \brief   This API will write the message object to Message RAM.
 *
 * \param   baseAddr        Base Address of the CANFD Registers.
 * \param   elemAddr        Address of the message object.
 * \param   elem            Message Object.
 *                          Refer struct #CANFD_TxBufElement.
 *
 * \return  None.
 */
static void CANFD_writeMsg(uint32_t                 baseAddr,
                          uint32_t                 elemAddr,
                          const CANFD_TxBufElement *elem);

/**
 * \brief   This API will return payload depending on 'dlc'  field.
 *
 * \param   dlc             Data Length Code.
 *
 * \return  data size       Size of the payload.
 */
static uint32_t CANFD_getDataSize(uint32_t dlc);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * \brief  Array that stores Data Size in bytes 
 */
static uint32_t dataSize[16] = {0,  1,  2,  3,  4,  5,  6,  7,
                                8, 12, 16, 20, 24, 32, 48, 64};

/**
 * \brief  Array that stores Element Size in words
 */
static uint32_t objSize[8] = {4, 5, 6, 7, 8, 10, 14, 18}; 

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */


//*****************************************************************************
//
// CANFD_isBaseValid
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
CANFD_isBaseValid(uint32_t baseAddr)
{
return(
           (baseAddr == CANFDA_DRIVER_BASE)
          );  
}
#endif

//*****************************************************************************
//
// CANFD_selectClockSource
//
//*****************************************************************************
void CANFD_selectClockSource(uint32_t baseAddr, CANFD_ClockSource source)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    //
    // Determine the CAN controller and set specified clock source
    //
    WRPRT_DISABLE;

    switch(baseAddr)
    {
        case CANFDA_DRIVER_BASE:
            HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL2) =
                (HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL2) &
                 ~(SYSCTL_CLKSRCCTL2_CANFDABCLKSEL_M)) |
                 ((uint16_t)source << SYSCTL_CLKSRCCTL2_CANFDABCLKSEL_S);
            break;


        default:

            //
            // Do nothing. Not a valid mode value.
            //
            break;
    }

    WRPRT_ENABLE;

}

//*****************************************************************************
//
// CANFD_isFDOpEnable
//
//*****************************************************************************
uint32_t CANFD_isFDOpEnable(uint32_t baseAddr)
{
    uint32_t fdoe;
    uint32_t state;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    fdoe = HW_RD_FIELD32(baseAddr + CANFD_CCCR,
                         CANFD_CCCR_FDOE);
    if(1U == fdoe)
    {
        state = (uint32_t) TRUE;
    }
    else
    {
        state = (uint32_t) FALSE;
    }
    return state;
}

//*****************************************************************************
//
// CANFD_setOpMode
//
//*****************************************************************************
void CANFD_setOpMode(uint32_t baseAddr, uint32_t mode)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    HW_WR_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_INIT, mode);
}

//*****************************************************************************
//
// CANFD_getOpMode
//
//*****************************************************************************
uint32_t CANFD_getOpMode(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_INIT));
}

//*****************************************************************************
//
// CANFD_init
//
//*****************************************************************************
int32_t CANFD_init(uint32_t baseAddr, const CANFD_InitParams *initParams)
{
    int32_t  status = STW_SOK;
    uint32_t regVal;
    uint32_t timeout;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    HW_WR_FIELD32(baseAddr + CANFD_ERM_CTRL,
                  CANFD_ERM_CTRL_WAKE_INT_EN,
                  initParams->wakeIntEnable);

    /* Exit from sleep / clock-stop: clear CSR and wait for CSA to de-assert */
    HW_WR_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_CSR, 0x0U);

    timeout = 0U;
    while (HW_RD_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_CSA) == 1U)
    {
        if (timeout > CANFD_INIT_TIMEOUT_COUNT)
        {
            return STW_EFAIL;
        }
        timeout++;
    }

    /* Request initialisation */
    HW_WR_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_INIT, 0x1U);

    timeout = 0U;
    while (HW_RD_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_INIT) != 1U)
    {
        if (timeout > CANFD_INIT_TIMEOUT_COUNT)
        {
            return STW_EFAIL;
        }
        timeout++;
    }

    CANFD_writeProtectedRegAccessUnlock(baseAddr);

    /* Configure CANFD mode(FD vs Classic CAN operation) and controls */
    regVal = HW_RD_REG32(baseAddr + CANFD_CCCR);
    HW_SET_FIELD32(regVal,
                   CANFD_CCCR_FDOE,
                   initParams->fdMode);
    HW_SET_FIELD32(regVal,
                   CANFD_CCCR_BRSE,
                   initParams->brsEnable);
    HW_SET_FIELD32(regVal,
                   CANFD_CCCR_TXP,
                   initParams->txpEnable);
    HW_SET_FIELD32(regVal,
                   CANFD_CCCR_EFBI,
                   initParams->efbi);
    HW_SET_FIELD32(regVal,
                   CANFD_CCCR_PXHD,
                   initParams->pxhddisable);
    HW_SET_FIELD32(regVal,
                   CANFD_CCCR_DAR,
                   initParams->darEnable);
    HW_WR_REG32(baseAddr + CANFD_CCCR, regVal);

    if((CANFD_TDCR_TDCF_MAX >= initParams->tdcConfig.tdcf) &&
        (CANFD_TDCR_TDCO_MAX >= initParams->tdcConfig.tdco) &&
        (CANFD_RWD_WDC_MAX >= initParams->wdcPreload))
    {
        /* Configure Transceiver Delay Compensation */
        HW_WR_FIELD32(baseAddr + CANFD_TDCR,
                      CANFD_TDCR_TDCF,
                      initParams->tdcConfig.tdcf);
        HW_WR_FIELD32(baseAddr + CANFD_TDCR,
                      CANFD_TDCR_TDCO,
                      initParams->tdcConfig.tdco);
        /* Configure MSG RAM watchdog counter preload value */
        HW_WR_FIELD32(baseAddr + CANFD_RWD,
                      CANFD_RWD_WDC,
                      initParams->wdcPreload);
        /* Enable/Disable Transceiver Delay Compensation */
        HW_WR_FIELD32(baseAddr + CANFD_DBTP,
                      CANFD_DBTP_TDC,
                      initParams->tdcEnable);
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }

    CANFD_writeProtectedRegAccessLock(baseAddr);

    return status;
}

//*****************************************************************************
//
// CANFD_config
//
//*****************************************************************************
int32_t CANFD_config(uint32_t baseAddr, const CANFD_ConfigParams *configParams)
{
    int32_t status;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    CANFD_writeProtectedRegAccessUnlock(baseAddr);

    /* Configure CANFD control registers */
    HW_WR_FIELD32(baseAddr + CANFD_CCCR,
                  CANFD_CCCR_MON,
                  configParams->monEnable);
    HW_WR_FIELD32(baseAddr + CANFD_CCCR,
                  CANFD_CCCR_ASM,
                  configParams->asmEnable);
    /* Configure Global Filter */
    HW_WR_FIELD32(baseAddr + CANFD_GFC,
                  CANFD_GFC_RRFE,
                  configParams->filterConfig.rrfe);
    HW_WR_FIELD32(baseAddr + CANFD_GFC,
                  CANFD_GFC_RRFS,
                  configParams->filterConfig.rrfs);
    HW_WR_FIELD32(baseAddr + CANFD_GFC,
                  CANFD_GFC_ANFE,
                  configParams->filterConfig.anfe);
    HW_WR_FIELD32(baseAddr + CANFD_GFC,
                  CANFD_GFC_ANFS,
                  configParams->filterConfig.anfs);

    if((CANFD_TSCC_TCP_MAX >= configParams->tsPrescalar) &&
        (CANFD_TOCC_TOP_MAX >= configParams->timeoutPreload))
    {
        uint32_t tsSelect = configParams->tsSelect;

        /* TSCC.TSS value 10b: use internal counter; external TS is via ERM. */
        if (tsSelect == 2U)
        {
            tsSelect = 1U;
        }

        /* Configure internal time-stamp counter */
        HW_WR_FIELD32(baseAddr + CANFD_TSCC, CANFD_TSCC_TSS, tsSelect);
        HW_WR_FIELD32(baseAddr + CANFD_TSCC,
                      CANFD_TSCC_TCP,
                      (configParams->tsPrescalar - 1U));
        /* Configure Time-out counter */
        HW_WR_FIELD32(baseAddr + CANFD_TOCC,
                      CANFD_TOCC_TOS,
                      configParams->timeoutSelect);
        HW_WR_FIELD32(baseAddr + CANFD_TOCC,
                      CANFD_TOCC_TOP,
                      configParams->timeoutPreload);
        /* Enable Time-out counter */
        HW_WR_FIELD32(baseAddr + CANFD_TOCC,
                      CANFD_TOCC_ETOC,
                      configParams->timeoutCntEnable);
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }

    CANFD_writeProtectedRegAccessLock(baseAddr);

    return status;
}

//*****************************************************************************
//
// CANFD_eccConfig
//
//*****************************************************************************
void CANFD_eccConfig(uint32_t                    baseAddr,
                    const CANFD_ECCConfigParams *configParams)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    HW_WR_FIELD32(baseAddr + CANFD_ERM_CTRL,
                      CANFD_ERM_CTRL_ECC_EN,
                      configParams->eccEnable);
    
    HW_WR_FIELD32(baseAddr + CANFD_ERM_CTRL,
                      CANFD_ERM_CTRL_BEC_INT_EN,
                      configParams->becIntEnable);
    
    HW_WR_FIELD32(baseAddr + CANFD_ERM_CTRL,
                      CANFD_ERM_CTRL_BEU_INT_EN,
                      configParams->beuIntEnable);
}

//*****************************************************************************
//
// CANFD_setBitTime
//
//*****************************************************************************
int32_t CANFD_setBitTime(uint32_t                    baseAddr,
                        const CANFD_BitTimingParams *configParams)
{
    int32_t status;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    CANFD_writeProtectedRegAccessUnlock(baseAddr);

    if((CANFD_NBTP_NSJW_MAX >= configParams->nomSynchJumpWidth) &&
        (CANFD_NBTP_NTSEG2_MAX >= configParams->nomTimeSeg2) &&
        (CANFD_NBTP_NTSEG1_MAX >= configParams->nomTimeSeg1) &&
        (CANFD_NBTP_NBRP_MAX >= configParams->nomRatePrescalar))
    {
        HW_WR_FIELD32(baseAddr + CANFD_NBTP,
                      CANFD_NBTP_NSJW,
                      configParams->nomSynchJumpWidth);
        HW_WR_FIELD32(baseAddr + CANFD_NBTP,
                      CANFD_NBTP_NTSEG2,
                      configParams->nomTimeSeg2);
        HW_WR_FIELD32(baseAddr + CANFD_NBTP,
                      CANFD_NBTP_NTSEG1,
                      configParams->nomTimeSeg1);
        HW_WR_FIELD32(baseAddr + CANFD_NBTP,
                      CANFD_NBTP_NBRP,
                      configParams->nomRatePrescalar);
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }
    if(STW_SOK == status)
    {
        if((CANFD_DBTP_DSJW_MAX >= configParams->dataSynchJumpWidth) &&
            (CANFD_DBTP_DTSEG2_MAX >= configParams->dataTimeSeg2) &&
            (CANFD_DBTP_DTSEG1_MAX >= configParams->dataTimeSeg1) &&
            (CANFD_DBTP_DBRP_MAX >= configParams->dataRatePrescalar))
        {
            HW_WR_FIELD32(baseAddr + CANFD_DBTP,
                          CANFD_DBTP_DSJW,
                          configParams->dataSynchJumpWidth);
            HW_WR_FIELD32(baseAddr + CANFD_DBTP,
                          CANFD_DBTP_DTSEG2,
                          configParams->dataTimeSeg2);
            HW_WR_FIELD32(baseAddr + CANFD_DBTP,
                          CANFD_DBTP_DTSEG1,
                          configParams->dataTimeSeg1);
            HW_WR_FIELD32(baseAddr + CANFD_DBTP,
                          CANFD_DBTP_DBRP,
                          configParams->dataRatePrescalar);
            status = STW_SOK;
        }
        else
        {
            status = STW_EFAIL;
        }
    }

    CANFD_writeProtectedRegAccessLock(baseAddr);
    return status;
}

//*****************************************************************************
//
// CANFD_msgRAMConfig
//
//*****************************************************************************
int32_t CANFD_msgRAMConfig(uint32_t                       baseAddr,
                          const CANFD_MsgRAMConfigParams *msgRAMConfigParams)
{
    int32_t  status;
    uint32_t elemNum = 0U;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    CANFD_writeProtectedRegAccessUnlock(baseAddr);

    /* Configure Message Filters section */
    if(0U != msgRAMConfigParams->lss)
    {
        HW_WR_FIELD32(baseAddr + CANFD_SIDFC,
                      CANFD_SIDFC_FLSSA,
                      (msgRAMConfigParams->flssa >> 2U));
        HW_WR_FIELD32(baseAddr + CANFD_SIDFC,
                      CANFD_SIDFC_LSS,
                      msgRAMConfigParams->lss);
    }
    if(0U != msgRAMConfigParams->lse)
    {
        HW_WR_FIELD32(baseAddr + CANFD_XIDFC,
                      CANFD_XIDFC_FLESA,
                      (msgRAMConfigParams->flesa >> 2U));
        HW_WR_FIELD32(baseAddr + CANFD_XIDFC,
                      CANFD_XIDFC_LSE,
                      msgRAMConfigParams->lse);
    }
    /* Configure Rx FIFO 0 section */
    if(0U != msgRAMConfigParams->rxFIFO0size)
    {
        HW_WR_FIELD32(baseAddr + CANFD_RXF0C,
                      CANFD_RXF0C_F0SA,
                      (msgRAMConfigParams->rxFIFO0startAddr >> 2U));
        HW_WR_FIELD32(baseAddr + CANFD_RXF0C,
                      CANFD_RXF0C_F0S,
                      msgRAMConfigParams->rxFIFO0size);
        HW_WR_FIELD32(baseAddr + CANFD_RXF0C,
                      CANFD_RXF0C_F0WM,
                      msgRAMConfigParams->rxFIFO0waterMark);
        HW_WR_FIELD32(baseAddr + CANFD_RXF0C,
                      CANFD_RXF0C_F0OM,
                      msgRAMConfigParams->rxFIFO0OpMode);
        /* Configure Rx FIFO0 elements size */
        HW_WR_FIELD32(baseAddr + CANFD_RXESC,
                      CANFD_RXESC_F0DS,
                      msgRAMConfigParams->rxFIFO0ElemSize);
    }
    /* Configure Rx FIFO 1 section */
    if(0U != msgRAMConfigParams->rxFIFO1size)
    {
        HW_WR_FIELD32(baseAddr + CANFD_RXF1C,
                      CANFD_RXF1C_F1SA,
                      (msgRAMConfigParams->rxFIFO1startAddr >> 2U));
        HW_WR_FIELD32(baseAddr + CANFD_RXF1C,
                      CANFD_RXF1C_F1S,
                      msgRAMConfigParams->rxFIFO1size);
        HW_WR_FIELD32(baseAddr + CANFD_RXF1C,
                      CANFD_RXF1C_F1WM,
                      msgRAMConfigParams->rxFIFO1waterMark);
        HW_WR_FIELD32(baseAddr + CANFD_RXF1C,
                      CANFD_RXF1C_F1OM,
                      msgRAMConfigParams->rxFIFO1OpMode);
        /* Configure Rx FIFO1 elements size */
        HW_WR_FIELD32(baseAddr + CANFD_RXESC,
                      CANFD_RXESC_F1DS,
                      msgRAMConfigParams->rxFIFO1ElemSize);
    }
    /* Configure Rx Buffer Start Address */
    HW_WR_FIELD32(baseAddr + CANFD_RXBC,
                  CANFD_RXBC_RBSA,
                  (msgRAMConfigParams->rxBufStartAddr >> 2U));
    /* Configure Rx Buffer elements size */
    HW_WR_FIELD32(baseAddr + CANFD_RXESC,
                  CANFD_RXESC_RBDS,
                  msgRAMConfigParams->rxBufElemSize);
    /* Configure Tx Event FIFO section */
    if(0U != msgRAMConfigParams->txEventFIFOSize)
    {
        HW_WR_FIELD32(baseAddr + CANFD_TXEFC,
                      CANFD_TXEFC_EFSA,
                      (msgRAMConfigParams->txEventFIFOStartAddr >> 2U));
        HW_WR_FIELD32(baseAddr + CANFD_TXEFC,
                      CANFD_TXEFC_EFS,
                      msgRAMConfigParams->txEventFIFOSize);
        HW_WR_FIELD32(baseAddr + CANFD_TXEFC,
                      CANFD_TXEFC_EFWM,
                      msgRAMConfigParams->txEventFIFOWaterMark);
    }
    /* Configure Tx Buffer and FIFO/Q section (Tx section may be zero) */
    elemNum = msgRAMConfigParams->txBufNum + msgRAMConfigParams->txFIFOSize;
    if(CANFD_MSGRAM_TX_BUFFER_MAX >= elemNum)
    {
        if((0U != msgRAMConfigParams->txBufNum) ||
           (0U != msgRAMConfigParams->txFIFOSize))
        {
            HW_WR_FIELD32(baseAddr + CANFD_TXBC,
                          CANFD_TXBC_TBSA,
                          (msgRAMConfigParams->txStartAddr >> 2U));
            HW_WR_FIELD32(baseAddr + CANFD_TXBC,
                          CANFD_TXBC_NDTB,
                          msgRAMConfigParams->txBufNum);
            HW_WR_FIELD32(baseAddr + CANFD_TXBC,
                          CANFD_TXBC_TFQS,
                          msgRAMConfigParams->txFIFOSize);
            HW_WR_FIELD32(baseAddr + CANFD_TXBC,
                          CANFD_TXBC_TFQM,
                          msgRAMConfigParams->txBufMode);
            /* Configure Tx Buffer/FIFO0/FIFO1 elements size */
            HW_WR_FIELD32(baseAddr + CANFD_TXESC,
                          CANFD_TXESC_TBDS,
                          msgRAMConfigParams->txBufElemSize);
        }
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }

    CANFD_writeProtectedRegAccessLock(baseAddr);

    return status;
}

//*****************************************************************************
//
// CANFD_setExtIDAndMask
//
//*****************************************************************************
int32_t CANFD_setExtIDAndMask(uint32_t baseAddr, uint32_t idMask)
{
    int32_t status;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if(CANFD_XIDAM_EIDM_MAX >= idMask)
    {
        CANFD_writeProtectedRegAccessUnlock(baseAddr);

        HW_WR_FIELD32(baseAddr + CANFD_XIDAM,
                      CANFD_XIDAM_EIDM,
                      idMask);

        CANFD_writeProtectedRegAccessLock(baseAddr);
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }
    return status;
}

//*****************************************************************************
//
// CANFD_writeMsgRam
//
//*****************************************************************************
void CANFD_writeMsgRam(uint32_t                 baseAddr,
                      uint32_t                 memType,
                      uint32_t                 bufNum,
                      const CANFD_TxBufElement *elem)
{
    uint32_t startAddr = 0U, elemSize = 0U, elemAddr = 0U;
    uint32_t idx       = 0U, enableMod = 0U;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if((uint32_t)CANFD_MEM_TYPE_BUF == memType)
    {
        idx       = bufNum;
        enableMod = 1U;
    }
    if((uint32_t)CANFD_MEM_TYPE_FIFO == memType)
    {
        idx       = HW_RD_FIELD32(baseAddr + CANFD_TXFQS, CANFD_TXFQS_TFQPI);
        enableMod = 1U;
    }
    if(1U == enableMod)
    {
        startAddr = HW_RD_FIELD32(baseAddr + CANFD_TXBC,
                                  CANFD_TXBC_TBSA);
        elemSize = HW_RD_FIELD32(baseAddr + CANFD_TXESC,
                                 CANFD_TXESC_TBDS);
        startAddr = (uint32_t) (startAddr << 2U);
        elemSize  = CANFD_getMsgObjSize(elemSize);
        elemSize *= 4U;
        elemAddr  = startAddr + (elemSize * idx);
        elemAddr += CANFD_CANFD_MSG_MEM;
        CANFD_writeMsg(baseAddr, elemAddr, elem);
    }
}

//*****************************************************************************
//
// CANFD_txBufAddReq
//
//*****************************************************************************
int32_t CANFD_txBufAddReq(uint32_t baseAddr, uint32_t bufNum)
{ 
    int32_t  status;
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if(CANFD_MSGRAM_TX_BUFFER_MAX > bufNum)
    {
        regVal  = HW_RD_REG32(baseAddr + CANFD_TXBAR);
        regVal |= ((uint32_t) 1U << bufNum);

        // For writing to TXBAR CCE bit should be '0'. This need not be
        // reverted because for other qualified writes this is locked state
        // and can't be written.
        CANFD_writeProtectedRegAccessLock(baseAddr);
        HW_WR_REG32(baseAddr + CANFD_TXBAR, regVal);

        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }
    return status;
}

//*****************************************************************************
//
// CANFD_getNewDataStatus
//
//*****************************************************************************
void  CANFD_getNewDataStatus(uint32_t              baseAddr,
                            CANFD_RxNewDataStatus *newDataStatus)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    newDataStatus->statusLow  = HW_RD_REG32(baseAddr + CANFD_NDAT1);
    newDataStatus->statusHigh = HW_RD_REG32(baseAddr + CANFD_NDAT2);
}

//*****************************************************************************
//
// CANFD_clearNewDataStatus
//
//*****************************************************************************
void  CANFD_clearNewDataStatus(uint32_t                    baseAddr,
                              const CANFD_RxNewDataStatus *newDataStatus)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));
     
    HW_WR_REG32(baseAddr + CANFD_NDAT1, newDataStatus->statusLow);
    HW_WR_REG32(baseAddr + CANFD_NDAT2, newDataStatus->statusHigh);
}

//*****************************************************************************
//
// CANFD_readMsgRam
//
//*****************************************************************************
void CANFD_readMsgRam(uint32_t           baseAddr,
                     uint32_t           memType,
                     uint32_t           bufNum,
                     uint32_t           fifoNum,
                     CANFD_RxBufElement *elem)
{
    uint32_t startAddr = 0U, elemSize = 0U, elemAddr = 0U;
    uint32_t enableMod = 0U, idx = 0U;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if((uint32_t)CANFD_MEM_TYPE_BUF == memType)
    {
        startAddr = HW_RD_FIELD32(baseAddr + CANFD_RXBC,
                                  CANFD_RXBC_RBSA);
        elemSize = HW_RD_FIELD32(baseAddr + CANFD_RXESC,
                                 CANFD_RXESC_RBDS);
        idx       = bufNum;
        enableMod = 1U;
    }
    if((uint32_t)CANFD_MEM_TYPE_FIFO == memType)
    {
        switch (fifoNum)
        {
            case CANFD_RX_FIFO_NUM_0:
                startAddr = HW_RD_FIELD32(baseAddr + CANFD_RXF0C,
                                          CANFD_RXF0C_F0SA);
                elemSize = HW_RD_FIELD32(baseAddr + CANFD_RXESC,
                                         CANFD_RXESC_F0DS);
                idx = HW_RD_FIELD32(baseAddr + CANFD_RXF0S,
                                    CANFD_RXF0S_F0GI);
                enableMod = 1U;
                break;
            case CANFD_RX_FIFO_NUM_1:
                startAddr = HW_RD_FIELD32(baseAddr + CANFD_RXF1C,
                                          CANFD_RXF1C_F1SA);
                elemSize = HW_RD_FIELD32(baseAddr + CANFD_RXESC,
                                         CANFD_RXESC_F1DS);
                idx = HW_RD_FIELD32(baseAddr + CANFD_RXF1S,
                                    CANFD_RXF1S_F1GI);
                enableMod = 1U;
                break;
            default:
                /* Invalid option */
                break;
        }
    }
    if(1U == enableMod)
    {
        startAddr = (uint32_t) (startAddr << 2U);
        elemSize  = CANFD_getMsgObjSize(elemSize);
        elemSize *= 4U;
        elemAddr  = startAddr + (elemSize * idx);
        elemAddr += CANFD_CANFD_MSG_MEM;
        CANFD_readMsg(baseAddr, elemAddr, elem); 
    }
}

//*****************************************************************************
//
// CANFD_readHighPriorityMsgRam
//
//*****************************************************************************
void CANFD_readHighPriorityMsgRam(uint32_t           baseAddr,
                                        CANFD_RxBufElement *elem)
{
    CANFD_HighPriorityMsgInfo hpm;
    uint32_t startAddr = 0U, elemSize = 0U, elemAddr = 0U;
    uint32_t enableMod = 0U, idx = 0U;
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    CANFD_getHighPriorityMsgStatus(baseAddr, &hpm);

    switch((hpm.msi)%2U)
    {
        case CANFD_RX_FIFO_NUM_0:
                startAddr = HW_RD_FIELD32(baseAddr + CANFD_RXF0C,
                                          CANFD_RXF0C_F0SA);
                elemSize = HW_RD_FIELD32(baseAddr + CANFD_RXESC,
                                         CANFD_RXESC_F0DS);
                enableMod = 1U;
                break;
            case CANFD_RX_FIFO_NUM_1:
                startAddr = HW_RD_FIELD32(baseAddr + CANFD_RXF1C,
                                          CANFD_RXF1C_F1SA);
                elemSize = HW_RD_FIELD32(baseAddr + CANFD_RXESC,
                                         CANFD_RXESC_F1DS);
                enableMod = 1U;
                break;
            default:
                /* Invalid option */
                break; 
    }
    if(1U == enableMod)
    {
        idx = hpm.bufIdx;
        startAddr = (uint32_t) (startAddr << 2U);
        elemSize  = CANFD_getMsgObjSize(elemSize);
        elemSize *= 4U;
        elemAddr  = startAddr + (elemSize * idx);
        elemAddr += CANFD_CANFD_MSG_MEM;
        CANFD_readMsg(baseAddr, elemAddr, elem);
    }
}

//*****************************************************************************
//
// CANFD_readTxEventFIFO
//
//*****************************************************************************
void CANFD_readTxEventFIFO(uint32_t           baseAddr,
                          CANFD_TxEventFIFOElement *txEventElem)
{
    uint32_t startAddr = 0U, elemSize = 0U, elemAddr = 0U;
    uint32_t idx = 0U, regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    startAddr = HW_RD_FIELD32(baseAddr + CANFD_TXEFC,
                              CANFD_TXEFC_EFSA);
    elemSize = CANFD_MSGRAM_TX_EVENT_FIFO_SIZE_WORDS;
    idx = HW_RD_FIELD32(baseAddr + CANFD_TXEFS,
                        CANFD_TXEFS_EFGI);

    startAddr = (uint32_t) (startAddr << 2U);
    elemSize *= 4U;
    elemAddr  = startAddr + (elemSize * idx);
    elemAddr += CANFD_CANFD_MSG_MEM;

    regVal   = HW_RD_REG32(baseAddr + elemAddr);
    txEventElem->id = (uint32_t) ((regVal & CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ID_MASK)
                           >> CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ID_SHIFT);
    txEventElem->rtr = (uint32_t) ((regVal & CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_RTR_MASK)
                            >> CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_RTR_SHIFT);
    txEventElem->xtd = (uint32_t) ((regVal & CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_XTD_MASK)
                            >> CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_XTD_SHIFT);
    txEventElem->esi = (uint32_t) ((regVal & CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ESI_MASK)
                            >> CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ESI_SHIFT);
    elemAddr  += 4U;
    regVal     = HW_RD_REG32(baseAddr + elemAddr);
    txEventElem->txts = (uint32_t) ((regVal & CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_TXTS_MASK)
                             >> CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_TXTS_SHIFT);
    txEventElem->dlc = (uint32_t) ((regVal & CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_DLC_MASK)
                            >> CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_DLC_SHIFT);
    txEventElem->brs = (uint32_t) ((regVal & CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_BRS_MASK)
                            >> CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_BRS_SHIFT);
    txEventElem->fdf = (uint32_t) ((regVal & CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_FDF_MASK)
                            >> CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_FDF_SHIFT);
    txEventElem->et = (uint32_t) ((regVal & CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ET_MASK)
                             >> CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_ET_SHIFT);
    txEventElem->mm = (uint32_t) ((regVal & CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_MM_MASK)
                             >> CANFD_MSGRAM_TX_EVENT_FIFO_ELEM_MM_SHIFT);
}

//*****************************************************************************
//
// CANFD_addStdMsgIDFilter
//
//*****************************************************************************
void CANFD_addStdMsgIDFilter(uint32_t                          baseAddr,
                            uint32_t                          filtNum,
                            const CANFD_StdMsgIDFilterElement *elem)
{
    uint32_t startAddr, elemAddr, regVal, totalFilt;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    //
    // Check that the filter number does not exceed the number 
    // of standard filters set during initialization
    //
    totalFilt = HW_RD_FIELD32(baseAddr + CANFD_SIDFC,
                              CANFD_SIDFC_LSS);
    ASSERT(filtNum <= totalFilt); 

    (void)totalFilt;

    startAddr = HW_RD_FIELD32(baseAddr + CANFD_SIDFC,
                              CANFD_SIDFC_FLSSA);
    startAddr = (uint32_t) (startAddr << 2U);
    elemAddr  = startAddr + (filtNum * CANFD_MSGRAM_STD_ID_FILTER_SIZE_WORDS * 4U);
    elemAddr += CANFD_CANFD_MSG_MEM;

    regVal  = 0U;
    regVal |= (uint32_t) (elem->sfid2 << CANFD_MSGRAM_STD_ID_FILTER_SFID2_SHIFT);
    regVal |= (uint32_t) (elem->sfid1 << CANFD_MSGRAM_STD_ID_FILTER_SFID1_SHIFT);
    regVal |= (uint32_t) (elem->sfec << CANFD_MSGRAM_STD_ID_FILTER_SFEC_SHIFT);
    regVal |= (uint32_t) (elem->sft << CANFD_MSGRAM_STD_ID_FILTER_SFT_SHIFT);
    HW_WR_REG32(baseAddr + elemAddr, regVal);
}

//*****************************************************************************
//
// CANFD_addExtMsgIDFilter
//
//*****************************************************************************
void CANFD_addExtMsgIDFilter(uint32_t                          baseAddr,
                            uint32_t                          filtNum,
                            const CANFD_ExtMsgIDFilterElement *elem)
{
    uint32_t startAddr, elemAddr, regVal, totalFilt;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    //
    // Check that the filter number does not exceed the number 
    // of extended filters set during initialization
    //
    totalFilt = HW_RD_FIELD32(baseAddr + CANFD_XIDFC,
                              CANFD_XIDFC_LSE);
    ASSERT(filtNum <= totalFilt); 

    (void)totalFilt;

    startAddr = HW_RD_FIELD32(baseAddr + CANFD_XIDFC,
                              CANFD_XIDFC_FLESA);
    startAddr = (uint32_t) (startAddr << 2U);
    elemAddr  = startAddr + (filtNum * CANFD_MSGRAM_EXT_ID_FILTER_SIZE_WORDS * 4U);
    elemAddr += CANFD_CANFD_MSG_MEM;

    regVal  = 0U;
    regVal |= (uint32_t) (elem->efid1 << CANFD_MSGRAM_EXT_ID_FILTER_EFID1_SHIFT);
    regVal |= (uint32_t) (elem->efec << CANFD_MSGRAM_EXT_ID_FILTER_EFEC_SHIFT);
    HW_WR_REG32(baseAddr + elemAddr, regVal);

    elemAddr += 4U;
    regVal    = 0U;
    regVal   |= (uint32_t) (elem->efid2 << CANFD_MSGRAM_EXT_ID_FILTER_EFID2_SHIFT);
    regVal   |= (uint32_t) (elem->eft << CANFD_MSGRAM_EXT_ID_FILTER_EFT_SHIFT);
    HW_WR_REG32(baseAddr + elemAddr, regVal);
}

//*****************************************************************************
//
// CANFD_lpbkModeEnable
//
//*****************************************************************************
void CANFD_lpbkModeEnable(uint32_t baseAddr,
                         uint32_t lpbkMode,
                         uint32_t enable)
{
    CANFD_writeProtectedRegAccessUnlock(baseAddr);

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if(TRUE == enable)
    {
        HW_WR_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_TEST, 0x1U);
        HW_WR_FIELD32(baseAddr + CANFD_TEST,
                      CANFD_TEST_LBCK,
                      enable);
        if((uint32_t)CANFD_LPBK_MODE_INTERNAL == lpbkMode)
        {
            HW_WR_FIELD32(baseAddr + CANFD_CCCR,
                          CANFD_CCCR_MON,
                          0x1U);
        }
    }
    else
    {
        HW_WR_FIELD32(baseAddr + CANFD_TEST,
                      CANFD_TEST_LBCK,
                      enable);
        HW_WR_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_TEST, 0x0U);
        if((uint32_t)CANFD_LPBK_MODE_INTERNAL == lpbkMode)
        {
            HW_WR_FIELD32(baseAddr + CANFD_CCCR,
                          CANFD_CCCR_MON,
                          0x0U);
        }
    }
    CANFD_writeProtectedRegAccessLock(baseAddr);
}

//*****************************************************************************
//
// CANFD_getErrCounters
//
//*****************************************************************************
void  CANFD_getErrCounters(uint32_t           baseAddr,
                          CANFD_ErrCntStatus *errCounter)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    errCounter->transErrLogCnt = HW_RD_FIELD32(baseAddr + CANFD_ECR,
                                               CANFD_ECR_TEC);
    errCounter->recErrCnt = HW_RD_FIELD32(baseAddr + CANFD_ECR,
                                          CANFD_ECR_REC);
    errCounter->rpStatus = HW_RD_FIELD32(baseAddr + CANFD_ECR,
                                         CANFD_ECR_RP);
    errCounter->canErrLogCnt = HW_RD_FIELD32(baseAddr + CANFD_ECR,
                                             CANFD_ECR_CEL);
}

//*****************************************************************************
//
// CANFD_getProtocolStatus
//
//*****************************************************************************
void  CANFD_getProtocolStatus(uint32_t             baseAddr,
                             CANFD_ProtocolStatus *protStatus)
{
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    regVal = HW_RD_REG32(baseAddr + CANFD_PSR);
    protStatus->lastErrCode   = HW_GET_FIELD(regVal, CANFD_PSR_LEC);
    protStatus->act           = HW_GET_FIELD(regVal, CANFD_PSR_ACT);
    protStatus->errPassive    = HW_GET_FIELD(regVal, CANFD_PSR_EP);
    protStatus->warningStatus = HW_GET_FIELD(regVal, CANFD_PSR_EW);
    protStatus->busOffStatus  = HW_GET_FIELD(regVal, CANFD_PSR_BO);
    protStatus->dlec          = HW_GET_FIELD(regVal, CANFD_PSR_DLEC);
    protStatus->resi          = HW_GET_FIELD(regVal, CANFD_PSR_RESI);
    protStatus->rbrs          = HW_GET_FIELD(regVal, CANFD_PSR_RBRS);
    protStatus->rfdf          = HW_GET_FIELD(regVal, CANFD_PSR_RFDF);
    protStatus->pxe           = HW_GET_FIELD(regVal, CANFD_PSR_PXE);
    protStatus->tdcv          = HW_GET_FIELD(regVal, CANFD_PSR_TDCV);
}

//*****************************************************************************
//
// CANFD_enableIntr
//
//*****************************************************************************
void CANFD_enableIntr(uint32_t baseAddr, uint32_t intrMask, uint32_t enable)
{
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if(TRUE == enable)
    {
        regVal  = HW_RD_REG32(baseAddr + CANFD_IE);
        regVal |= intrMask;
        HW_WR_REG32(baseAddr + CANFD_IE, regVal);
    }
    else
    {
        regVal  = HW_RD_REG32(baseAddr + CANFD_IE);
        regVal &= ~intrMask;
        HW_WR_REG32(baseAddr + CANFD_IE, regVal);
    }
}

//*****************************************************************************
//
// CANFD_selectIntrLine
//
//*****************************************************************************
void CANFD_selectIntrLine(uint32_t baseAddr,
                         uint32_t intrMask,
                         uint32_t lineNum)
{
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if((uint32_t)CANFD_INTR_LINE_NUM_0 == lineNum)
    {
        regVal  = HW_RD_REG32(baseAddr + CANFD_ILS);
        regVal &= ~intrMask;
        HW_WR_REG32(baseAddr + CANFD_ILS, regVal);
    }
    else
    {
        regVal  = HW_RD_REG32(baseAddr + CANFD_ILS);
        regVal |= intrMask;
        HW_WR_REG32(baseAddr + CANFD_ILS, regVal);
    }
}

//*****************************************************************************
//
// CANFD_getIntrLineSelectStatus
//
//*****************************************************************************
uint32_t CANFD_getIntrLineSelectStatus(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_REG32(baseAddr + CANFD_ILS));
}

//*****************************************************************************
//
// CANFD_enableIntrLine
//
//*****************************************************************************
void CANFD_enableIntrLine(uint32_t baseAddr,
                         uint32_t lineNum,
                         uint32_t enable)
{
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    lineNum &= CANFD_MSGRAM_INTR_LINE_EN_MASK;
    regVal   = HW_RD_REG32(baseAddr + CANFD_ILE);
    regVal  &= ~((uint32_t) 0x1U << lineNum);
    regVal  |= (uint32_t) (enable << lineNum);
    HW_WR_REG32(baseAddr + CANFD_ILE, regVal);
}

//*****************************************************************************
//
// CANFD_getIntrStatus
//
//*****************************************************************************
uint32_t CANFD_getIntrStatus(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_REG32(baseAddr + CANFD_IR));
}

//*****************************************************************************
//
// CANFD_clearIntrStatus
//
//*****************************************************************************
void CANFD_clearIntrStatus(uint32_t baseAddr, uint32_t intrMask)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    HW_WR_REG32(baseAddr + CANFD_IR, intrMask);
}

//*****************************************************************************
//
// CANFD_getHighPriorityMsgStatus
//
//*****************************************************************************
void  CANFD_getHighPriorityMsgStatus(uint32_t                  baseAddr,
                                    CANFD_HighPriorityMsgInfo *hpm)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    hpm->bufIdx = HW_RD_FIELD32(baseAddr + CANFD_HPMS,
                                CANFD_HPMS_BIDX);
    hpm->msi = HW_RD_FIELD32(baseAddr + CANFD_HPMS,
                             CANFD_HPMS_MSI);
    hpm->filterIdx = HW_RD_FIELD32(baseAddr + CANFD_HPMS,
                                   CANFD_HPMS_FIDX);
    hpm->filterList = HW_RD_FIELD32(baseAddr + CANFD_HPMS,
                                    CANFD_HPMS_FLST);
}

//*****************************************************************************
//
// CANFD_getRxFIFOStatus
//
//*****************************************************************************
void CANFD_getRxFIFOStatus(uint32_t           baseAddr,
                          CANFD_RxFIFOStatus *fifoStatus)
{
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    switch (fifoStatus->num)
    {
        case CANFD_RX_FIFO_NUM_0:
            regVal = HW_RD_REG32(baseAddr + CANFD_RXF0S);
            fifoStatus->fillLvl  = HW_GET_FIELD(regVal, CANFD_RXF0S_F0FL);
            fifoStatus->getIdx   = HW_GET_FIELD(regVal, CANFD_RXF0S_F0GI);
            fifoStatus->putIdx   = HW_GET_FIELD(regVal, CANFD_RXF0S_F0PI);
            fifoStatus->fifoFull = HW_GET_FIELD(regVal, CANFD_RXF0S_F0F);
            fifoStatus->msgLost  = HW_GET_FIELD(regVal, CANFD_RXF0S_RF0L);
            break;
        case CANFD_RX_FIFO_NUM_1:
            regVal = HW_RD_REG32(baseAddr + CANFD_RXF1S);
            fifoStatus->fillLvl  = HW_GET_FIELD(regVal, CANFD_RXF1S_F1FL);
            fifoStatus->getIdx   = HW_GET_FIELD(regVal, CANFD_RXF1S_F1GI);
            fifoStatus->putIdx   = HW_GET_FIELD(regVal, CANFD_RXF1S_F1PI);
            fifoStatus->fifoFull = HW_GET_FIELD(regVal, CANFD_RXF1S_F1F);
            fifoStatus->msgLost  = HW_GET_FIELD(regVal, CANFD_RXF1S_RF1L);
            break;
        default:
            /* Invalid option */
            break;
    }
}

//*****************************************************************************
//
// CANFD_writeRxFIFOAck
//
//*****************************************************************************
int32_t CANFD_writeRxFIFOAck(uint32_t baseAddr,
                            uint32_t fifoNum,
                            uint32_t idx)
{
    int32_t  status;
    uint32_t size;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    switch (fifoNum)
    {
        case CANFD_RX_FIFO_NUM_0:
            size = HW_RD_FIELD32(baseAddr + CANFD_RXF0C,
                                 CANFD_RXF0C_F0S);
            if(size >= idx)
            {
                HW_WR_FIELD32(baseAddr + CANFD_RXF0A,
                              CANFD_RXF0A_F0AI,
                              idx);
                status = STW_SOK;
            }
            else
            {
                status = STW_EFAIL;
            }
            break;
        case CANFD_RX_FIFO_NUM_1:
            size = HW_RD_FIELD32(baseAddr + CANFD_RXF1C,
                                 CANFD_RXF1C_F1S);
            if(size >= idx)
            {
                HW_WR_FIELD32(baseAddr + CANFD_RXF1A,
                              CANFD_RXF1A_F1AI,
                              idx);
                status = STW_SOK;
            }
            else
            {
                status = STW_EFAIL;
            }
            break;
        default:
            status = STW_EFAIL;
            break;
    }

    return status;
}

//*****************************************************************************
//
// CANFD_getTxFIFOQueStatus
//
//*****************************************************************************
void CANFD_getTxFIFOQueStatus(uint32_t           baseAddr,
                             CANFD_TxFIFOStatus *fifoStatus)
{
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    regVal = HW_RD_REG32(baseAddr + CANFD_TXFQS);
    fifoStatus->freeLvl  = HW_GET_FIELD(regVal, CANFD_TXFQS_TFFL);
    fifoStatus->getIdx   = HW_GET_FIELD(regVal, CANFD_TXFQS_TFGI);
    fifoStatus->putIdx   = HW_GET_FIELD(regVal, CANFD_TXFQS_TFQPI);
    fifoStatus->fifoFull = HW_GET_FIELD(regVal, CANFD_TXFQS_TFQF);
}

//*****************************************************************************
//
// CANFD_getTxBufReqPend
//
//*****************************************************************************
uint32_t CANFD_getTxBufReqPend(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_REG32(baseAddr + CANFD_TXBRP));
}

//*****************************************************************************
//
// CANFD_txBufCancellationReq
//
//*****************************************************************************
int32_t CANFD_txBufCancellationReq(uint32_t baseAddr, uint32_t buffNum)
{
    int32_t  status;
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if(CANFD_MSGRAM_TX_BUFFER_MAX > buffNum)
    {
        regVal  = HW_RD_REG32(baseAddr + CANFD_TXBCR);
        regVal |= ((uint32_t) 1U << buffNum);

        // For writing to TXBCR CCE bit should be '0'. This need not be
        // reverted because for other qualified writes this is locked state
        // and can't be written.
        CANFD_writeProtectedRegAccessLock(baseAddr);
        HW_WR_REG32(baseAddr + CANFD_TXBCR, regVal);

        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }
    return status;
}

//*****************************************************************************
//
// CANFD_getTxBufTransmissionStatus
//
//*****************************************************************************
uint32_t CANFD_getTxBufTransmissionStatus(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_REG32(baseAddr + CANFD_TXBTO));
}

//*****************************************************************************
//
// CANFD_txBufCancellationStatus
//
//*****************************************************************************
uint32_t CANFD_txBufCancellationStatus(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_REG32(baseAddr + CANFD_TXBCF));
}

//*****************************************************************************
//
// CANFD_txBufTransIntrEnable
//
//*****************************************************************************
int32_t CANFD_txBufTransIntrEnable(uint32_t baseAddr,
                                  uint32_t bufNum,
                                  uint32_t enable)
{
    int32_t  status;
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if(CANFD_MSGRAM_TX_BUFFER_MAX > bufNum)
    {
        if(TRUE == enable)
        {
            regVal  = HW_RD_REG32(baseAddr + CANFD_TXBTIE);
            regVal |= ((uint32_t) 1U << bufNum);
            HW_WR_REG32(baseAddr + CANFD_TXBTIE, regVal);
        }
        else
        {
            regVal  = HW_RD_REG32(baseAddr + CANFD_TXBTIE);
            regVal &= ~((uint32_t) 0x1U << bufNum);
            HW_WR_REG32(baseAddr + CANFD_TXBTIE, regVal);
        }
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }
    return status;
}

//*****************************************************************************
//
// CANFD_getTxBufCancellationIntrEnable
//
//*****************************************************************************
int32_t CANFD_getTxBufCancellationIntrEnable(uint32_t baseAddr,
                                            uint32_t bufNum,
                                            uint32_t enable)
{
    int32_t  status;
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if(CANFD_MSGRAM_TX_BUFFER_MAX > bufNum)
    {
        if(TRUE == enable)
        {
            regVal  = HW_RD_REG32(baseAddr + CANFD_TXBCIE);
            regVal |= ((uint32_t) 0x1U << bufNum);
            HW_WR_REG32(baseAddr + CANFD_TXBCIE, regVal);
        }
        else
        {
            regVal  = HW_RD_REG32(baseAddr + CANFD_TXBCIE);
            regVal &= ~((uint32_t) 0x1U << bufNum);
            HW_WR_REG32(baseAddr + CANFD_TXBCIE, regVal);
        }
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }
    return status;
}

//*****************************************************************************
//
// CANFD_getTxEventFIFOStatus
//
//*****************************************************************************
void CANFD_getTxEventFIFOStatus(uint32_t                baseAddr,
                               CANFD_TxEventFIFOStatus *fifoStatus)
{
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    regVal = HW_RD_REG32(baseAddr + CANFD_TXEFS);
    fifoStatus->fillLvl  = HW_GET_FIELD(regVal, CANFD_TXEFS_EFFL);
    fifoStatus->getIdx   = HW_GET_FIELD(regVal, CANFD_TXEFS_EFGI);
    fifoStatus->putIdx   = HW_GET_FIELD(regVal, CANFD_TXEFS_EFPI);
    fifoStatus->fifoFull = HW_GET_FIELD(regVal, CANFD_TXEFS_EFF);
    fifoStatus->eleLost  = HW_GET_FIELD(regVal, CANFD_TXEFS_TEFL);
}

//*****************************************************************************
//
// CANFD_addClockStopRequest
//
//*****************************************************************************
void CANFD_addClockStopRequest(uint32_t baseAddr, uint32_t enable)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if(TRUE == enable)
    {
        HW_WR_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_CSR, 0x1U);
    }
    else
    {
        HW_WR_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_CSR, 0x0U);
    }
}

//*****************************************************************************
//
// CANFD_writeTxEventFIFOAck
//
//*****************************************************************************
int32_t CANFD_writeTxEventFIFOAck(uint32_t baseAddr, uint32_t idx)
{
    int32_t  status;
    uint32_t size;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    size = HW_RD_FIELD32(baseAddr + CANFD_TXEFC,
                         CANFD_TXEFC_EFS);
    if(size >= idx)
    {
        HW_WR_FIELD32(baseAddr + CANFD_TXEFA,
                      CANFD_TXEFA_EFAI,
                      idx);
        status = STW_SOK;
    }
    else
    {
        status = STW_EFAIL;
    }

    return status;
}

//*****************************************************************************
//
// CANFD_eccGetErrorStatus
//
//*****************************************************************************
void CANFD_eccGetErrorStatus(uint32_t           baseAddr,
                            CANFD_ECCErrStatus *eccErr)
{
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    /* Read ECC status register */
    regVal = HW_RD_REG32(baseAddr + CANFD_ERM_STS);
    eccErr->secErr = HW_GET_FIELD(regVal,
                                  CANFD_ERM_STS_BEC_FLAG);
    eccErr->dedErr = HW_GET_FIELD(regVal,
                                  CANFD_ERM_STS_BEU_FLAG);

    /* Read error address register */
    regVal = HW_RD_REG32(baseAddr + CANFD_ERM_ECC_ADDR_LOG);
    eccErr->errorAddress = HW_GET_FIELD(regVal,
                                  CANFD_ERM_ECC_ADDR_LOG_ERR_ADDR); 

    /* Read error data register  */
    regVal = HW_RD_REG32(baseAddr + CANFD_ERM_ECC_DATA_LOG);
    eccErr->errorData = regVal;
}

//*****************************************************************************
//
// CANFD_eccClearErrorStatus
//
//*****************************************************************************
void CANFD_eccClearErrorStatus(uint32_t baseAddr, uint32_t errType)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    switch (errType)
    {
        case CANFD_ECC_ERR_TYPE_SEC:
            HW_WR_FIELD32(baseAddr + CANFD_ERM_STS,
                          CANFD_ERM_STS_BEC_FLAG,
                          0x1U);
            break;
        case CANFD_ECC_ERR_TYPE_DED:
            HW_WR_FIELD32(baseAddr + CANFD_ERM_STS,
                          CANFD_ERM_STS_BEU_FLAG,
                          0x1U);
            break;
        default:
            /* Invalid option */
            break;
    }
}

//*****************************************************************************
//
// CANFD_eccEnableIntr
//
//*****************************************************************************
void CANFD_eccEnableIntr(uint32_t baseAddr, uint32_t errType, uint32_t enable)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    if(TRUE == enable)
    {
        switch (errType)
        {
            case CANFD_ECC_ERR_TYPE_SEC:
                HW_WR_FIELD32(baseAddr + CANFD_ERM_CTRL,
                              CANFD_ERM_CTRL_BEC_INT_EN,
                              0x1U);
                break;
            case CANFD_ECC_ERR_TYPE_DED:
                HW_WR_FIELD32(baseAddr + CANFD_ERM_CTRL,
                              CANFD_ERM_CTRL_BEU_INT_EN,
                              0x1U);
                break;
            default:
                /* Invalid option */
                break;
        }
    }
    else
    {
        switch (errType)
        {
            case CANFD_ECC_ERR_TYPE_SEC:
                HW_WR_FIELD32(baseAddr + CANFD_ERM_CTRL,
                              CANFD_ERM_CTRL_BEC_INT_EN,
                              0x0U);
                break;
            case CANFD_ECC_ERR_TYPE_DED:
                HW_WR_FIELD32(baseAddr + CANFD_ERM_CTRL,
                              CANFD_ERM_CTRL_BEU_INT_EN,
                              0x0U);
                break;
            default:
                /* Invalid option */
                break;
        }
    }
}

//*****************************************************************************
//
// CANFD_eccGetIntrStatus
//
//*****************************************************************************
uint32_t CANFD_eccGetIntrStatus(uint32_t baseAddr, uint32_t errType)
{
    uint32_t retVal = 0U;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    switch (errType)
    {
        case CANFD_ECC_ERR_TYPE_SEC:
            retVal = HW_RD_FIELD32(baseAddr + CANFD_ERM_STS,
                                   CANFD_ERM_STS_BEC_FLAG);
            
        break;
        case CANFD_ECC_ERR_TYPE_DED:
            retVal = HW_RD_FIELD32(baseAddr + CANFD_ERM_STS,
                                    CANFD_ERM_STS_BEU_FLAG);
        break;
        default:
            retVal = 0U;
            break;
    }

    return retVal;
}

//*****************************************************************************
//
// CANFD_eccClearIntrStatus
//
//*****************************************************************************
void CANFD_eccClearIntrStatus(uint32_t baseAddr, uint32_t errType)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    switch (errType)
    {
        case CANFD_ECC_ERR_TYPE_SEC:
            HW_WR_FIELD32(baseAddr + CANFD_ERM_STS,
                          CANFD_ERM_STS_BEC_FLAG,
                          0x1U);
            
        break;
        case CANFD_ECC_ERR_TYPE_DED:
            HW_WR_FIELD32(baseAddr + CANFD_ERM_STS,
                          CANFD_ERM_STS_BEU_FLAG,
                          0x1U);
        break;
        default:
            break;
    }
}

/* ========================================================================== */
/*                          Advance Functions                                 */
/* ========================================================================== */

//*****************************************************************************
//
// CANFD_getRevisionId
//
//*****************************************************************************
void CANFD_getRevisionId(uint32_t baseAddr, CANFD_RevisionId *revId)
{
    uint32_t regVal;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    regVal         = HW_RD_REG32(baseAddr + CANFD_CREL);
    revId->day     = HW_GET_FIELD(regVal, CANFD_CREL_DAY);
    revId->mon     = HW_GET_FIELD(regVal, CANFD_CREL_MON);
    revId->year    = HW_GET_FIELD(regVal, CANFD_CREL_YEAR);
    revId->subStep = HW_GET_FIELD(regVal, CANFD_CREL_SUBSTEP);
    revId->step    = HW_GET_FIELD(regVal, CANFD_CREL_STEP);
    revId->rel     = HW_GET_FIELD(regVal, CANFD_CREL_REL);
}

//*****************************************************************************
//
// CANFD_getClockStopAck
//
//*****************************************************************************
uint32_t CANFD_getClockStopAck(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_CSR));
}

//*****************************************************************************
//
// CANFD_getRxPinState
//
//*****************************************************************************
uint32_t CANFD_getRxPinState(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_FIELD32(baseAddr + CANFD_TEST, CANFD_TEST_RX));
}

//*****************************************************************************
//
// CANFD_setTxPinState
//
//*****************************************************************************
void CANFD_setTxPinState(uint32_t baseAddr, uint32_t state)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    CANFD_writeProtectedRegAccessUnlock(baseAddr);

    HW_WR_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_TEST, 0x1U);
    HW_WR_FIELD32(baseAddr + CANFD_TEST,
                  CANFD_TEST_TX,
                  state);

    CANFD_writeProtectedRegAccessLock(baseAddr);
}

//*****************************************************************************
//
// CANFD_getTxPinState
//
//*****************************************************************************
uint32_t CANFD_getTxPinState(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_FIELD32(baseAddr + CANFD_TEST, CANFD_TEST_TX));
}

//*****************************************************************************
//
// CANFD_getTSCounterVal
//
//*****************************************************************************
uint32_t CANFD_getTSCounterVal(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_FIELD32(baseAddr + CANFD_TSCV, CANFD_TSCV_TSC));
}

//*****************************************************************************
//
// CANFD_getClkStopAck
//
//*****************************************************************************
uint32_t CANFD_getClkStopAck(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_CSA));
}

//*****************************************************************************
//
// CANFD_getBitTime
//
//*****************************************************************************
void CANFD_getBitTime(uint32_t              baseAddr,
                     CANFD_BitTimingParams *configParams)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    configParams->nomSynchJumpWidth = HW_RD_FIELD32(baseAddr + CANFD_NBTP,
                                                    CANFD_NBTP_NSJW);
    configParams->nomTimeSeg2 = HW_RD_FIELD32(baseAddr + CANFD_NBTP,
                                              CANFD_NBTP_NTSEG2);
    configParams->nomTimeSeg1 = HW_RD_FIELD32(baseAddr + CANFD_NBTP,
                                              CANFD_NBTP_NTSEG1);
    configParams->nomRatePrescalar = HW_RD_FIELD32(baseAddr + CANFD_NBTP,
                                                   CANFD_NBTP_NBRP);

    configParams->dataSynchJumpWidth = HW_RD_FIELD32(baseAddr + CANFD_DBTP,
                                                     CANFD_DBTP_DSJW);
    configParams->dataTimeSeg2 = HW_RD_FIELD32(baseAddr + CANFD_DBTP,
                                               CANFD_DBTP_DTSEG2);
    configParams->dataTimeSeg1 = HW_RD_FIELD32(baseAddr + CANFD_DBTP,
                                               CANFD_DBTP_DTSEG1);
    configParams->dataRatePrescalar = HW_RD_FIELD32(baseAddr + CANFD_DBTP,
                                                    CANFD_DBTP_DBRP);
}

//*****************************************************************************
//
// CANFD_resetTSCounter
//
//*****************************************************************************
void CANFD_resetTSCounter(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    HW_WR_FIELD32(baseAddr + CANFD_TSCV, CANFD_TSCV_TSC, 0x0U);
}

//*****************************************************************************
//
// CANFD_getTOCounterVal
//
//*****************************************************************************
uint32_t CANFD_getTOCounterVal(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));
    
    return(HW_RD_FIELD32(baseAddr + CANFD_TOCV, CANFD_TOCV_TOC));
}

//*****************************************************************************
//
// CANFD_getEndianVal
//
//*****************************************************************************
uint32_t CANFD_getEndianVal(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_FIELD32(baseAddr + CANFD_ENDN, CANFD_ENDN_ETV));
}

//*****************************************************************************
//
// CANFD_getExtIDANDMask
//
//*****************************************************************************
uint32_t CANFD_getExtIDANDMask(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    return(HW_RD_FIELD32(baseAddr + CANFD_XIDAM, CANFD_XIDAM_EIDM));
}

/* ========================================================================== */
/*                          Internal Functions                                */
/* ========================================================================== */

//*****************************************************************************
//
// CANFD_writeProtectedRegAccessUnlock
//
//*****************************************************************************
static void CANFD_writeProtectedRegAccessUnlock(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    HW_WR_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_CCE, 0x1U);
}

//*****************************************************************************
//
// CANFD_writeProtectedRegAccessLock
//
//*****************************************************************************
static void CANFD_writeProtectedRegAccessLock(uint32_t baseAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    HW_WR_FIELD32(baseAddr + CANFD_CCCR, CANFD_CCCR_CCE, 0x0U);
}

//*****************************************************************************
//
// CANFD_readMsg
//
//*****************************************************************************
static void CANFD_readMsg(uint32_t           baseAddr,
                         uint32_t           elemAddr,
                         CANFD_RxBufElement *elem)
{
    uint32_t regVal = 0U, loopCnt = 0U;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    regVal   = HW_RD_REG32(baseAddr + elemAddr);
    elem->id = (uint32_t) ((regVal & CANFD_MSGRAM_RX_BUFFER_ELEM_ID_MASK)
                           >> CANFD_MSGRAM_RX_BUFFER_ELEM_ID_SHIFT);
    elem->rtr = (uint32_t) ((regVal & CANFD_MSGRAM_RX_BUFFER_ELEM_RTR_MASK)
                            >> CANFD_MSGRAM_RX_BUFFER_ELEM_RTR_SHIFT);
    elem->xtd = (uint32_t) ((regVal & CANFD_MSGRAM_RX_BUFFER_ELEM_XTD_MASK)
                            >> CANFD_MSGRAM_RX_BUFFER_ELEM_XTD_SHIFT);
    elem->esi = (uint32_t) ((regVal & CANFD_MSGRAM_RX_BUFFER_ELEM_ESI_MASK)
                            >> CANFD_MSGRAM_RX_BUFFER_ELEM_ESI_SHIFT);

    elemAddr  += 4U;
    regVal     = HW_RD_REG32(baseAddr + elemAddr);
    elem->rxts = (uint32_t) ((regVal & CANFD_MSGRAM_RX_BUFFER_ELEM_RXTS_MASK)
                             >> CANFD_MSGRAM_RX_BUFFER_ELEM_RXTS_SHIFT);
    elem->dlc = (uint32_t) ((regVal & CANFD_MSGRAM_RX_BUFFER_ELEM_DLC_MASK)
                            >> CANFD_MSGRAM_RX_BUFFER_ELEM_DLC_SHIFT);
    elem->brs = (uint32_t) ((regVal & CANFD_MSGRAM_RX_BUFFER_ELEM_BRS_MASK)
                            >> CANFD_MSGRAM_RX_BUFFER_ELEM_BRS_SHIFT);
    elem->fdf = (uint32_t) ((regVal & CANFD_MSGRAM_RX_BUFFER_ELEM_FDF_MASK)
                            >> CANFD_MSGRAM_RX_BUFFER_ELEM_FDF_SHIFT);
    elem->fidx = (uint32_t) ((regVal & CANFD_MSGRAM_RX_BUFFER_ELEM_FIDX_MASK)
                             >> CANFD_MSGRAM_RX_BUFFER_ELEM_FIDX_SHIFT);
    elem->anmf = (uint32_t) ((regVal & CANFD_MSGRAM_RX_BUFFER_ELEM_ANMF_MASK)
                             >> CANFD_MSGRAM_RX_BUFFER_ELEM_ANMF_SHIFT);
    elemAddr += 4U;

    loopCnt = 0U;
    /* Reading words from message RAM and forming payload bytes out of it */
    while((4U <= (CANFD_getDataSize(elem->dlc) - loopCnt)) &&
           (0U != (CANFD_getDataSize(elem->dlc) - loopCnt)))
    {
        ASSERT((loopCnt + 3U) < CANFD_MAX_PAYLOAD_BYTES);
        regVal = HW_RD_REG32(baseAddr + elemAddr);
        elem->data[loopCnt]       = (uint16_t)(regVal & 0x000000FFU);
        elem->data[(loopCnt + 1U)] = (uint16_t)((regVal & 0x0000FF00U) >> 8U);
        elem->data[(loopCnt + 2U)] = (uint16_t)((regVal & 0x00FF0000U) >> 16U);
        elem->data[(loopCnt + 3U)] = (uint16_t)((regVal & 0xFF000000U) >> 24U);
        elemAddr += 4U;
        loopCnt  += 4U;
    }
    /* Reading remaining bytes from message RAM */
    if(0U < (CANFD_getDataSize(elem->dlc) - loopCnt))
    {
        ASSERT((loopCnt + 2U) < CANFD_MAX_PAYLOAD_BYTES);
        regVal = HW_RD_REG32(baseAddr + elemAddr);
        elem->data[loopCnt]       = (uint16_t)(regVal & 0x000000FFU);
        elem->data[(loopCnt + 1U)] = (uint16_t)((regVal & 0x0000FF00U) >> 8U);
        elem->data[(loopCnt + 2U)] = (uint16_t)((regVal & 0x00FF0000U) >> 16U);
    }
} 

//*****************************************************************************
//
// CANFD_writeMsg
//
//*****************************************************************************
static void CANFD_writeMsg(uint32_t                 baseAddr,
                          uint32_t                 elemAddr,
                          const CANFD_TxBufElement *elem)
{
    uint32_t regVal = 0, loopCnt = 0U;

    //
    // Check the arguments.
    //
    ASSERT(CANFD_isBaseValid(baseAddr));

    regVal  = 0U;
    regVal |= (((uint32_t) (elem->id << CANFD_MSGRAM_TX_BUFFER_ELEM_ID_SHIFT)) |
               ((uint32_t) (elem->rtr << CANFD_MSGRAM_TX_BUFFER_ELEM_RTR_SHIFT)) |
               ((uint32_t) (elem->xtd << CANFD_MSGRAM_TX_BUFFER_ELEM_XTD_SHIFT)) |
               ((uint32_t) (elem->esi << CANFD_MSGRAM_TX_BUFFER_ELEM_ESI_SHIFT)));
    HW_WR_REG32(baseAddr + elemAddr, regVal);
    elemAddr += 4U;

    regVal  = 0U;
    regVal |= ((uint32_t) (elem->dlc << CANFD_MSGRAM_TX_BUFFER_ELEM_DLC_SHIFT)) |
              ((uint32_t) (elem->brs << CANFD_MSGRAM_TX_BUFFER_ELEM_BRS_SHIFT)) |
              ((uint32_t) (elem->fdf << CANFD_MSGRAM_TX_BUFFER_ELEM_FDF_SHIFT)) |
              ((uint32_t) (elem->efc << CANFD_MSGRAM_TX_BUFFER_ELEM_EFC_SHIFT)) |
              ((uint32_t) (elem->mm << CANFD_MSGRAM_TX_BUFFER_ELEM_MM_SHIFT));
    HW_WR_REG32(baseAddr + elemAddr, regVal);
    elemAddr += 4U;

    loopCnt = 0U;
    /* Framing words out of the payload bytes and writing it to message RAM */
    while((4U <= (CANFD_getDataSize(elem->dlc) - loopCnt)) &&
           (0U != (CANFD_getDataSize(elem->dlc) - loopCnt)))
    {
        ASSERT((loopCnt + 3U) < CANFD_MAX_PAYLOAD_BYTES);
        regVal  = 0U;
        regVal |= ((uint32_t)elem->data[loopCnt] |
                   ((uint32_t)elem->data[(loopCnt + 1U)] << 8U) |
                   ((uint32_t)elem->data[(loopCnt + 2U)] << 16U) |
                   ((uint32_t)elem->data[(loopCnt + 3U)] << 24U));
        HW_WR_REG32(baseAddr + elemAddr, regVal);
        elemAddr += 4U;
        loopCnt  += 4U;
    }
    /* Framing a word out of remaining payload bytes and writing it to
     * message RAM */
    if(0U < (CANFD_getDataSize(elem->dlc) - loopCnt))
    {
        ASSERT((loopCnt + 3U) < CANFD_MAX_PAYLOAD_BYTES);
        regVal  = 0U;
        regVal |= ((uint32_t)elem->data[loopCnt] |
                   ((uint32_t)elem->data[(loopCnt + 1U)] << 8U) |
                   ((uint32_t)elem->data[(loopCnt + 2U)] << 16U) |
                   ((uint32_t)elem->data[(loopCnt + 3U)] << 24U));
        HW_WR_REG32(baseAddr + elemAddr, regVal);
    }
}

//*****************************************************************************
//
// CANFD_getDataSize
//
//*****************************************************************************
static uint32_t CANFD_getDataSize(uint32_t dlc)
{
    ASSERT(dlc < 16U);
    return(dataSize[dlc]);
}

//*****************************************************************************
//
// CANFD_getMsgObjSize
//
//*****************************************************************************
uint32_t CANFD_getMsgObjSize(uint32_t elemSize)
{
    ASSERT(elemSize < 8U);
    return(objSize[elemSize]);
}

//*****************************************************************************
//
// CANFD_enableWakeupInterrupt
//
//*****************************************************************************
void CANFD_enableWakeupInterrupt(uint32_t baseAddr, uint32_t enable)
{
    ASSERT(CANFD_isBaseValid(baseAddr));

    HW_WR_FIELD32(baseAddr + CANFD_ERM_CTRL,
                  CANFD_ERM_CTRL_WAKE_INT_EN,
                  (enable != 0U) ? 1U : 0U);
}

//*****************************************************************************
//
// CANFD_wakeupClearIntrStatus
//
//*****************************************************************************
void CANFD_wakeupClearIntrStatus(uint32_t baseAddr)
{
    ASSERT(CANFD_isBaseValid(baseAddr));
    
    HW_WR_FIELD32(baseAddr + CANFD_ERM_STS, CANFD_ERM_STS_CANFD_WAKEUP_CLEAR,0x01U);
}

//*****************************************************************************
//
// CANFD_requestAndWaitMemInit
//
//*****************************************************************************
int32_t CANFD_requestAndWaitMemInit(uint32_t baseAddr, uint32_t timeoutCount)
{
    uint32_t timeout;

    ASSERT(CANFD_isBaseValid(baseAddr));

    if((uint32_t)TRUE == CANFD_isMemInitDone(baseAddr))
    {
        return STW_SOK;
    }

    CANFD_enableRamInitRequest(baseAddr);

    timeout = timeoutCount;
    while((uint32_t)FALSE == CANFD_isMemInitDone(baseAddr))
    {
        if(0U == timeout)
        {
            return STW_EFAIL;
        }
        timeout--;
    }

    return STW_SOK;
}

//*****************************************************************************
//
// CANFD_enableRamInitRequest
//
//*****************************************************************************
void CANFD_enableRamInitRequest(uint32_t baseAddr)
{
    ASSERT(CANFD_isBaseValid(baseAddr));
    
    HW_WR_FIELD32(baseAddr + CANFD_ERM_RAM_INIT, CANFD_ERM_RAM_INIT_RAM_INIT_EN,0x01U);
}

//*****************************************************************************
//
// CANFD_disableRamInitRequest
//
//*****************************************************************************
void CANFD_disableRamInitRequest(uint32_t baseAddr)
{
    ASSERT(CANFD_isBaseValid(baseAddr));
    
    HW_WR_FIELD32(baseAddr + CANFD_ERM_RAM_INIT, CANFD_ERM_RAM_INIT_RAM_INIT_EN,0x00U);
}

//*****************************************************************************
//
// CANFD_isMemInitDone
//
//*****************************************************************************
uint32_t CANFD_isMemInitDone(uint32_t baseAddr)
{
    uint32_t done;
    uint32_t state;

    ASSERT(CANFD_isBaseValid(baseAddr));

    done = HW_RD_FIELD32(baseAddr + CANFD_ERM_RAM_INIT,
                         CANFD_ERM_RAM_INIT_RAM_INIT_DONE);

    if(1U == done)
    {
        state = (uint32_t)TRUE;
    }
    else
    {
        state = (uint32_t)FALSE;
    }
    return state;
}

//*****************************************************************************
//
// CANFD_getExtTimeStampCounter
//
//*****************************************************************************
uint16_t CANFD_getExtTimeStampCounter(uint32_t baseAddr)
{
    return CANFD_extTSGetCount(baseAddr);
}

//*****************************************************************************
//
// CANFD_extTSCounterEnable
//
//*****************************************************************************
void CANFD_extTSCounterEnable(uint32_t baseAddr, uint32_t enable)
{
    ASSERT(CANFD_isBaseValid(baseAddr));

    HW_WR_FIELD32((baseAddr + CANFD_ERM_EXTC_CTRL),
                  CANFD_ERM_EXTC_CTRL_ETCE,
                  enable);
}

//*****************************************************************************
//
// CANFD_extTSCounterConfig
//
//*****************************************************************************
void CANFD_extTSCounterConfig(uint32_t baseAddr,
                             uint32_t prescalar)
{
    ASSERT(CANFD_isBaseValid(baseAddr));

    prescalar &= 0x3FFU;

    HW_WR_FIELD32((baseAddr + CANFD_ERM_EXTC_CTRL),
                  CANFD_ERM_EXTC_CTRL_ETCP,
                  (uint32_t)prescalar);
}

//*****************************************************************************
//
// CANFD_extTSGetPrescaler
//
//*****************************************************************************
uint16_t CANFD_extTSGetPrescaler(uint32_t baseAddr)
{
    ASSERT(CANFD_isBaseValid(baseAddr));

    return (uint16_t)HW_RD_FIELD32((baseAddr + CANFD_ERM_EXTC_CTRL),
                                   CANFD_ERM_EXTC_CTRL_ETCP);
}

//*****************************************************************************
//
// CANFD_extTSGetCount
//
//*****************************************************************************
uint16_t CANFD_extTSGetCount(uint32_t baseAddr)
{
    ASSERT(CANFD_isBaseValid(baseAddr));

    return (uint16_t)HW_RD_FIELD32((baseAddr + CANFD_ERM_EXTC_VAL),
                                   CANFD_ERM_EXTC_VAL_ETSC);
}

//*****************************************************************************
//
// CANFD_clearWakeStatus
//
//*****************************************************************************
void CANFD_clearWakeStatus(uint32_t baseAddr)
{
    (void)baseAddr;

    /* Write-1-to-clear: only need to write 1 to bit0, hardware auto-clears */
    HWREG(SYSCTL_BASE + SYSCTL_O_CANFDWAKESTATUSCLR) = SYSCTL_CANFDWAKESTATUSCLR_CLEAR;
}

//*****************************************************************************
//
// CANFD_getWakeUpState
//
//*****************************************************************************
uint32_t CANFD_getWakeUpState(uint32_t baseAddr)
{
    //
    // Read Wake Up Flag bit in CANFDWAKESTATUS register
    //
    return (HWREG(SYSCTL_BASE + SYSCTL_O_CANFDWAKESTATUS) & SYSCTL_CANFDWAKESTATUS_FLAG);
}

//*****************************************************************************
//
// CANFD_requestClockStop
//
//*****************************************************************************
void CANFD_requestClockStop(uint32_t baseAddr)
{
    (void)baseAddr;

    /*
     * Clock-stop request lives in SYSCTL, not the CANFD peripheral window.
     * Write KEY field to bits [31:16] and set REQ.
     */
    HWREG(SYSCTL_BASE + SYSCTL_O_CANFDCLKSTOPREQ) =
        SYSCTL_CANFDCLKSTOPREQ_KEY | SYSCTL_CANFDCLKSTOPREQ_REQ;
}

//*****************************************************************************
//
// CANFD_isClockStopAcked
//
//*****************************************************************************
uint32_t CANFD_isClockStopAcked(uint32_t baseAddr)
{
    (void)baseAddr;

    return ((HWREG(SYSCTL_BASE + SYSCTL_O_CANFDCLKSTOPACK) &
             SYSCTL_CANFDCLKSTOPACK_ACK) == SYSCTL_CANFDCLKSTOPACK_ACK);
}
