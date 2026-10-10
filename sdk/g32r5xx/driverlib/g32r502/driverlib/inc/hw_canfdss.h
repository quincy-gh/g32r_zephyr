//###########################################################################
//
// FILE:    hw_canfdss.h
//
// TITLE:   Definitions for the CANFDSS registers.
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
// 1. Retain CANFDSS register definitions for G32R502 CANFD.
//
//###########################################################################


#ifndef HW_CANFDSS_H_
#define HW_CANFDSS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "inc/hw_memmap.h"


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
// Sub-module base addresses (relative to CANFDA_DRIVER_BASE / CANFD_BASE).
// CANFD core registers @ +0x0, ERM @ +0x100, Message RAM access window @ +0x800
// (CANFD_BASE + CANFD_CANFD_MSG_MEM == CANFD_SRAM_BASE in hw_memmap.h).
// Message RAM layout offsets in driver APIs are added to CANFD_CANFD_MSG_MEM.

#define CANFD_REGS                                  (0x0U)
#define CANFD_ERM_REGS                              (0x100U)
#define CANFD_CANFD_MSG_MEM                         (0x800U)

#define CANFD_CREL                                    (CANFD_REGS + 0x00U)
#define CANFD_ENDN                                    (CANFD_REGS + 0x04U)
#define CANFD_DBTP                                    (CANFD_REGS + 0x0cU)
#define CANFD_TEST                                    (CANFD_REGS + 0x10U)
#define CANFD_RWD                                     (CANFD_REGS + 0x14U)
#define CANFD_CCCR                                    (CANFD_REGS + 0x18U)
#define CANFD_NBTP                                    (CANFD_REGS + 0x1cU)
#define CANFD_TSCC                                    (CANFD_REGS + 0x20U)
#define CANFD_TSCV                                    (CANFD_REGS + 0x24U)
#define CANFD_TOCC                                    (CANFD_REGS + 0x28U)
#define CANFD_TOCV                                    (CANFD_REGS + 0x2cU)
#define CANFD_ECR                                     (CANFD_REGS + 0x40U)
#define CANFD_PSR                                     (CANFD_REGS + 0x44U)
#define CANFD_TDCR                                    (CANFD_REGS + 0x48U)
#define CANFD_IR                                      (CANFD_REGS + 0x50U)
#define CANFD_IE                                      (CANFD_REGS + 0x54U)
#define CANFD_ILS                                     (CANFD_REGS + 0x58U)
#define CANFD_ILE                                     (CANFD_REGS + 0x5cU)
#define CANFD_GFC                                     (CANFD_REGS + 0x80U)
#define CANFD_SIDFC                                   (CANFD_REGS + 0x84U)
#define CANFD_XIDFC                                   (CANFD_REGS + 0x88U)
#define CANFD_XIDAM                                   (CANFD_REGS + 0x90U)
#define CANFD_HPMS                                    (CANFD_REGS + 0x94U)
#define CANFD_NDAT1                                   (CANFD_REGS + 0x98U)
#define CANFD_NDAT2                                   (CANFD_REGS + 0x9cU)
#define CANFD_RXF0C                                   (CANFD_REGS + 0xa0U)
#define CANFD_RXF0S                                   (CANFD_REGS + 0xa4U)
#define CANFD_RXF0A                                   (CANFD_REGS + 0xa8U)
#define CANFD_RXBC                                    (CANFD_REGS + 0xacU)
#define CANFD_RXF1C                                   (CANFD_REGS + 0xb0U)
#define CANFD_RXF1S                                   (CANFD_REGS + 0xb4U)
#define CANFD_RXF1A                                   (CANFD_REGS + 0xb8U)
#define CANFD_RXESC                                   (CANFD_REGS + 0xbcU)
#define CANFD_TXBC                                    (CANFD_REGS + 0xc0U)
#define CANFD_TXFQS                                   (CANFD_REGS + 0xc4U)
#define CANFD_TXESC                                   (CANFD_REGS + 0xc8U)
#define CANFD_TXBRP                                   (CANFD_REGS + 0xccU)
#define CANFD_TXBAR                                   (CANFD_REGS + 0xd0U)
#define CANFD_TXBCR                                   (CANFD_REGS + 0xd4U)
#define CANFD_TXBTO                                   (CANFD_REGS + 0xd8U)
#define CANFD_TXBCF                                   (CANFD_REGS + 0xdcU)
#define CANFD_TXBTIE                                  (CANFD_REGS + 0xe0U)
#define CANFD_TXBCIE                                  (CANFD_REGS + 0xe4U)
#define CANFD_TXEFC                                   (CANFD_REGS + 0xf0U)
#define CANFD_TXEFS                                   (CANFD_REGS + 0xf4U)
#define CANFD_TXEFA                                   (CANFD_REGS + 0xf8U)


#define CANFD_ERM_CTRL                                (CANFD_ERM_REGS + 0x00U)
#define CANFD_ERM_STS                                 (CANFD_ERM_REGS + 0x04U)
#define CANFD_ERM_ECC_ADDR_LOG                        (CANFD_ERM_REGS + 0x08U)
#define CANFD_ERM_ECC_DATA_LOG                        (CANFD_ERM_REGS + 0x0CU)
#define CANFD_ERM_RAM_INIT                            (CANFD_ERM_REGS + 0x10U)
#define CANFD_ERM_EXTC_CTRL                           (CANFD_ERM_REGS + 0x14U)
#define CANFD_ERM_EXTC_VAL                            (CANFD_ERM_REGS + 0x18U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/
#define CANFD_CREL_DAY_SHIFT                                (0U)
#define CANFD_CREL_DAY_MASK                                 (0x000000ffU)

#define CANFD_CREL_MON_SHIFT                                (8U)
#define CANFD_CREL_MON_MASK                                 (0x0000ff00U)

#define CANFD_CREL_YEAR_SHIFT                               (16U)
#define CANFD_CREL_YEAR_MASK                                (0x000f0000U)

#define CANFD_CREL_SUBSTEP_SHIFT                            (20U)
#define CANFD_CREL_SUBSTEP_MASK                             (0x00f00000U)

#define CANFD_CREL_STEP_SHIFT                               (24U)
#define CANFD_CREL_STEP_MASK                                (0x0f000000U)

#define CANFD_CREL_REL_SHIFT                                (28U)
#define CANFD_CREL_REL_MASK                                 (0xf0000000U)

#define CANFD_ENDN_ETV_SHIFT                                (0U)
#define CANFD_ENDN_ETV_MASK                                 (0xffffffffU)

#define CANFD_DBTP_DSJW_SHIFT                               (0U)
#define CANFD_DBTP_DSJW_MASK                                (0x0000000fU)

#define CANFD_DBTP_DTSEG2_SHIFT                             (4U)
#define CANFD_DBTP_DTSEG2_MASK                              (0x000000f0U)

#define CANFD_DBTP_DTSEG1_SHIFT                             (8U)
#define CANFD_DBTP_DTSEG1_MASK                              (0x00001f00U)

#define CANFD_DBTP_DBRP_SHIFT                               (16U)
#define CANFD_DBTP_DBRP_MASK                                (0x001f0000U)

#define CANFD_DBTP_TDC_SHIFT                                (23U)
#define CANFD_DBTP_TDC_MASK                                 (0x00800000U)

#define CANFD_TEST_LBCK_SHIFT                               (4U)
#define CANFD_TEST_LBCK_MASK                                (0x00000010U)

#define CANFD_TEST_TX_SHIFT                                 (5U)
#define CANFD_TEST_TX_MASK                                  (0x00000060U)

#define CANFD_TEST_RX_SHIFT                                 (7U)
#define CANFD_TEST_RX_MASK                                  (0x00000080U)

#define CANFD_RWD_WDC_SHIFT                                 (0U)
#define CANFD_RWD_WDC_MASK                                  (0x000000ffU)

#define CANFD_RWD_WDV_SHIFT                                 (8U)
#define CANFD_RWD_WDV_MASK                                  (0x0000ff00U)

#define CANFD_CCCR_INIT_SHIFT                               (0U)
#define CANFD_CCCR_INIT_MASK                                (0x00000001U)

#define CANFD_CCCR_CCE_SHIFT                                (1U)
#define CANFD_CCCR_CCE_MASK                                 (0x00000002U)

#define CANFD_CCCR_ASM_SHIFT                                (2U)
#define CANFD_CCCR_ASM_MASK                                 (0x00000004U)

#define CANFD_CCCR_CSA_SHIFT                                (3U)
#define CANFD_CCCR_CSA_MASK                                 (0x00000008U)

#define CANFD_CCCR_CSR_SHIFT                                (4U)
#define CANFD_CCCR_CSR_MASK                                 (0x00000010U)

#define CANFD_CCCR_MON_SHIFT                                (5U)
#define CANFD_CCCR_MON_MASK                                 (0x00000020U)

#define CANFD_CCCR_DAR_SHIFT                                (6U)
#define CANFD_CCCR_DAR_MASK                                 (0x00000040U)

#define CANFD_CCCR_TEST_SHIFT                               (7U)
#define CANFD_CCCR_TEST_MASK                                (0x00000080U)

#define CANFD_CCCR_FDOE_SHIFT                               (8U)
#define CANFD_CCCR_FDOE_MASK                                (0x00000100U)

#define CANFD_CCCR_BRSE_SHIFT                               (9U)
#define CANFD_CCCR_BRSE_MASK                                (0x00000200U)

#define CANFD_CCCR_PXHD_SHIFT                               (12U)
#define CANFD_CCCR_PXHD_MASK                                (0x00001000U)

#define CANFD_CCCR_EFBI_SHIFT                               (13U)
#define CANFD_CCCR_EFBI_MASK                                (0x00002000U)

#define CANFD_CCCR_TXP_SHIFT                                (14U)
#define CANFD_CCCR_TXP_MASK                                 (0x00004000U)

#define CANFD_NBTP_NTSEG2_SHIFT                             (0U)
#define CANFD_NBTP_NTSEG2_MASK                              (0x0000007fU)

#define CANFD_NBTP_NTSEG1_SHIFT                             (8U)
#define CANFD_NBTP_NTSEG1_MASK                              (0x0000ff00U)

#define CANFD_NBTP_NBRP_SHIFT                               (16U)
#define CANFD_NBTP_NBRP_MASK                                (0x01ff0000U)

#define CANFD_NBTP_NSJW_SHIFT                               (25U)
#define CANFD_NBTP_NSJW_MASK                                (0xfe000000U)

#define CANFD_TSCC_TSS_SHIFT                                (0U)
#define CANFD_TSCC_TSS_MASK                                 (0x00000003U)

#define CANFD_TSCC_TCP_SHIFT                                (16U)
#define CANFD_TSCC_TCP_MASK                                 (0x000f0000U)

#define CANFD_TSCV_TSC_SHIFT                                (0U)
#define CANFD_TSCV_TSC_MASK                                 (0x0000ffffU)

#define CANFD_TOCC_ETOC_SHIFT                               (0U)
#define CANFD_TOCC_ETOC_MASK                                (0x00000001U)

#define CANFD_TOCC_TOS_SHIFT                                (1U)
#define CANFD_TOCC_TOS_MASK                                 (0x00000006U)

#define CANFD_TOCC_TOP_SHIFT                                (16U)
#define CANFD_TOCC_TOP_MASK                                 (0xffff0000U)

#define CANFD_TOCV_TOC_SHIFT                                (0U)
#define CANFD_TOCV_TOC_MASK                                 (0x0000ffffU)

#define CANFD_ECR_TEC_SHIFT                                 (0U)
#define CANFD_ECR_TEC_MASK                                  (0x000000ffU)

#define CANFD_ECR_REC_SHIFT                                 (8U)
#define CANFD_ECR_REC_MASK                                  (0x00007f00U)

#define CANFD_ECR_RP_SHIFT                                  (15U)
#define CANFD_ECR_RP_MASK                                   (0x00008000U)

#define CANFD_ECR_CEL_SHIFT                                 (16U)
#define CANFD_ECR_CEL_MASK                                  (0x00ff0000U)

#define CANFD_PSR_LEC_SHIFT                                 (0U)
#define CANFD_PSR_LEC_MASK                                  (0x00000007U)

#define CANFD_PSR_ACT_SHIFT                                 (3U)
#define CANFD_PSR_ACT_MASK                                  (0x00000018U)

#define CANFD_PSR_EP_SHIFT                                  (5U)
#define CANFD_PSR_EP_MASK                                   (0x00000020U)

#define CANFD_PSR_EW_SHIFT                                  (6U)
#define CANFD_PSR_EW_MASK                                   (0x00000040U)

#define CANFD_PSR_BO_SHIFT                                  (7U)
#define CANFD_PSR_BO_MASK                                   (0x00000080U)

#define CANFD_PSR_DLEC_SHIFT                                (8U)
#define CANFD_PSR_DLEC_MASK                                 (0x00000700U)

#define CANFD_PSR_RESI_SHIFT                                (11U)
#define CANFD_PSR_RESI_MASK                                 (0x00000800U)

#define CANFD_PSR_RBRS_SHIFT                                (12U)
#define CANFD_PSR_RBRS_MASK                                 (0x00001000U)

#define CANFD_PSR_RFDF_SHIFT                                (13U)
#define CANFD_PSR_RFDF_MASK                                 (0x00002000U)

#define CANFD_PSR_PXE_SHIFT                                 (14U)
#define CANFD_PSR_PXE_MASK                                  (0x00004000U)

#define CANFD_PSR_TDCV_SHIFT                                (16U)
#define CANFD_PSR_TDCV_MASK                                 (0x007f0000U)

#define CANFD_TDCR_TDCF_SHIFT                               (0U)
#define CANFD_TDCR_TDCF_MASK                                (0x0000007fU)

#define CANFD_TDCR_TDCO_SHIFT                               (8U)
#define CANFD_TDCR_TDCO_MASK                                (0x00007f00U)

#define CANFD_IR_RF0N_SHIFT                                 (0U)
#define CANFD_IR_RF0N_MASK                                  (0x00000001U)

#define CANFD_IR_RF0W_SHIFT                                 (1U)
#define CANFD_IR_RF0W_MASK                                  (0x00000002U)

#define CANFD_IR_RF0F_SHIFT                                 (2U)
#define CANFD_IR_RF0F_MASK                                  (0x00000004U)

#define CANFD_IR_RF0L_SHIFT                                 (3U)
#define CANFD_IR_RF0L_MASK                                  (0x00000008U)

#define CANFD_IR_RF1N_SHIFT                                 (4U)
#define CANFD_IR_RF1N_MASK                                  (0x00000010U)

#define CANFD_IR_RF1W_SHIFT                                 (5U)
#define CANFD_IR_RF1W_MASK                                  (0x00000020U)

#define CANFD_IR_RF1F_SHIFT                                 (6U)
#define CANFD_IR_RF1F_MASK                                  (0x00000040U)

#define CANFD_IR_RF1L_SHIFT                                 (7U)
#define CANFD_IR_RF1L_MASK                                  (0x00000080U)

#define CANFD_IR_HPM_SHIFT                                  (8U)
#define CANFD_IR_HPM_MASK                                   (0x00000100U)

#define CANFD_IR_TC_SHIFT                                   (9U)
#define CANFD_IR_TC_MASK                                    (0x00000200U)

#define CANFD_IR_TCF_SHIFT                                  (10U)
#define CANFD_IR_TCF_MASK                                   (0x00000400U)

#define CANFD_IR_TFE_SHIFT                                  (11U)
#define CANFD_IR_TFE_MASK                                   (0x00000800U)

#define CANFD_IR_TEFN_SHIFT                                 (12U)
#define CANFD_IR_TEFN_MASK                                  (0x00001000U)

#define CANFD_IR_TEFW_SHIFT                                 (13U)
#define CANFD_IR_TEFW_MASK                                  (0x00002000U)

#define CANFD_IR_TEFF_SHIFT                                 (14U)
#define CANFD_IR_TEFF_MASK                                  (0x00004000U)

#define CANFD_IR_TEFL_SHIFT                                 (15U)
#define CANFD_IR_TEFL_MASK                                  (0x00008000U)

#define CANFD_IR_TSW_SHIFT                                  (16U)
#define CANFD_IR_TSW_MASK                                   (0x00010000U)

#define CANFD_IR_MRAF_SHIFT                                 (17U)
#define CANFD_IR_MRAF_MASK                                  (0x00020000U)

#define CANFD_IR_TOO_SHIFT                                  (18U)
#define CANFD_IR_TOO_MASK                                   (0x00040000U)

#define CANFD_IR_DRX_SHIFT                                  (19U)
#define CANFD_IR_DRX_MASK                                   (0x00080000U)

#define CANFD_IR_ELO_SHIFT                                  (22U)
#define CANFD_IR_ELO_MASK                                   (0x00400000U)

#define CANFD_IR_EP_SHIFT                                   (23U)
#define CANFD_IR_EP_MASK                                    (0x00800000U)

#define CANFD_IR_EW_SHIFT                                   (24U)
#define CANFD_IR_EW_MASK                                    (0x01000000U)

#define CANFD_IR_BO_SHIFT                                   (25U)
#define CANFD_IR_BO_MASK                                    (0x02000000U)

#define CANFD_IR_WDI_SHIFT                                  (26U)
#define CANFD_IR_WDI_MASK                                   (0x04000000U)

#define CANFD_IR_PEA_SHIFT                                  (27U)
#define CANFD_IR_PEA_MASK                                   (0x08000000U)

#define CANFD_IR_PED_SHIFT                                  (28U)
#define CANFD_IR_PED_MASK                                   (0x10000000U)

#define CANFD_IR_ARA_SHIFT                                  (29U)
#define CANFD_IR_ARA_MASK                                   (0x20000000U)

#define CANFD_IE_RF0NE_SHIFT                                (0U)
#define CANFD_IE_RF0NE_MASK                                 (0x00000001U)

#define CANFD_IE_RF0WE_SHIFT                                (1U)
#define CANFD_IE_RF0WE_MASK                                 (0x00000002U)

#define CANFD_IE_RF0FE_SHIFT                                (2U)
#define CANFD_IE_RF0FE_MASK                                 (0x00000004U)

#define CANFD_IE_RF0LE_SHIFT                                (3U)
#define CANFD_IE_RF0LE_MASK                                 (0x00000008U)

#define CANFD_IE_RF1NE_SHIFT                                (4U)
#define CANFD_IE_RF1NE_MASK                                 (0x00000010U)

#define CANFD_IE_RF1WE_SHIFT                                (5U)
#define CANFD_IE_RF1WE_MASK                                 (0x00000020U)

#define CANFD_IE_RF1FE_SHIFT                                (6U)
#define CANFD_IE_RF1FE_MASK                                 (0x00000040U)

#define CANFD_IE_RF1LE_SHIFT                                (7U)
#define CANFD_IE_RF1LE_MASK                                 (0x00000080U)

#define CANFD_IE_HPME_SHIFT                                 (8U)
#define CANFD_IE_HPME_MASK                                  (0x00000100U)

#define CANFD_IE_TCE_SHIFT                                  (9U)
#define CANFD_IE_TCE_MASK                                   (0x00000200U)

#define CANFD_IE_TCFE_SHIFT                                 (10U)
#define CANFD_IE_TCFE_MASK                                  (0x00000400U)

#define CANFD_IE_TFEE_SHIFT                                 (11U)
#define CANFD_IE_TFEE_MASK                                  (0x00000800U)

#define CANFD_IE_TEFNE_SHIFT                                (12U)
#define CANFD_IE_TEFNE_MASK                                 (0x00001000U)

#define CANFD_IE_TEFWE_SHIFT                                (13U)
#define CANFD_IE_TEFWE_MASK                                 (0x00002000U)

#define CANFD_IE_TEFFE_SHIFT                                (14U)
#define CANFD_IE_TEFFE_MASK                                 (0x00004000U)

#define CANFD_IE_TEFLE_SHIFT                                (15U)
#define CANFD_IE_TEFLE_MASK                                 (0x00008000U)

#define CANFD_IE_TSWE_SHIFT                                 (16U)
#define CANFD_IE_TSWE_MASK                                  (0x00010000U)

#define CANFD_IE_MRAFE_SHIFT                                (17U)
#define CANFD_IE_MRAFE_MASK                                 (0x00020000U)

#define CANFD_IE_TOOE_SHIFT                                 (18U)
#define CANFD_IE_TOOE_MASK                                  (0x00040000U)

#define CANFD_IE_DRX_SHIFT                                  (19U)
#define CANFD_IE_DRX_MASK                                   (0x00080000U)

#define CANFD_IE_ELOE_SHIFT                                 (22U)
#define CANFD_IE_ELOE_MASK                                  (0x00400000U)

#define CANFD_IE_EPE_SHIFT                                  (23U)
#define CANFD_IE_EPE_MASK                                   (0x00800000U)

#define CANFD_IE_EWE_SHIFT                                  (24U)
#define CANFD_IE_EWE_MASK                                   (0x01000000U)

#define CANFD_IE_BOE_SHIFT                                  (25U)
#define CANFD_IE_BOE_MASK                                   (0x02000000U)

#define CANFD_IE_WDIE_SHIFT                                 (26U)
#define CANFD_IE_WDIE_MASK                                  (0x04000000U)

#define CANFD_IE_PEAE_SHIFT                                 (27U)
#define CANFD_IE_PEAE_MASK                                  (0x08000000U)

#define CANFD_IE_PEDE_SHIFT                                 (28U)
#define CANFD_IE_PEDE_MASK                                  (0x10000000U)

#define CANFD_IE_ARAE_SHIFT                                 (29U)
#define CANFD_IE_ARAE_MASK                                  (0x20000000U)

#define CANFD_ILS_RF0NL_SHIFT                               (0U)
#define CANFD_ILS_RF0NL_MASK                                (0x00000001U)

#define CANFD_ILS_RF0WL_SHIFT                               (1U)
#define CANFD_ILS_RF0WL_MASK                                (0x00000002U)

#define CANFD_ILS_RF0FL_SHIFT                               (2U)
#define CANFD_ILS_RF0FL_MASK                                (0x00000004U)

#define CANFD_ILS_RF0LL_SHIFT                               (3U)
#define CANFD_ILS_RF0LL_MASK                                (0x00000008U)

#define CANFD_ILS_RF1NL_SHIFT                               (4U)
#define CANFD_ILS_RF1NL_MASK                                (0x00000010U)

#define CANFD_ILS_RF1WL_SHIFT                               (5U)
#define CANFD_ILS_RF1WL_MASK                                (0x00000020U)

#define CANFD_ILS_RF1FL_SHIFT                               (6U)
#define CANFD_ILS_RF1FL_MASK                                (0x00000040U)

#define CANFD_ILS_RF1LL_SHIFT                               (7U)
#define CANFD_ILS_RF1LL_MASK                                (0x00000080U)

#define CANFD_ILS_HPML_SHIFT                                (8U)
#define CANFD_ILS_HPML_MASK                                 (0x00000100U)

#define CANFD_ILS_TCL_SHIFT                                 (9U)
#define CANFD_ILS_TCL_MASK                                  (0x00000200U)

#define CANFD_ILS_TCFL_SHIFT                                (10U)
#define CANFD_ILS_TCFL_MASK                                 (0x00000400U)

#define CANFD_ILS_TFEL_SHIFT                                (11U)
#define CANFD_ILS_TFEL_MASK                                 (0x00000800U)

#define CANFD_ILS_TEFNL_SHIFT                               (12U)
#define CANFD_ILS_TEFNL_MASK                                (0x00001000U)

#define CANFD_ILS_TEFWL_SHIFT                               (13U)
#define CANFD_ILS_TEFWL_MASK                                (0x00002000U)

#define CANFD_ILS_TEFFL_SHIFT                               (14U)
#define CANFD_ILS_TEFFL_MASK                                (0x00004000U)

#define CANFD_ILS_TEFLL_SHIFT                               (15U)
#define CANFD_ILS_TEFLL_MASK                                (0x00008000U)

#define CANFD_ILS_TSWL_SHIFT                                (16U)
#define CANFD_ILS_TSWL_MASK                                 (0x00010000U)

#define CANFD_ILS_MRAFL_SHIFT                               (17U)
#define CANFD_ILS_MRAFL_MASK                                (0x00020000U)

#define CANFD_ILS_TOOL_SHIFT                                (18U)
#define CANFD_ILS_TOOL_MASK                                 (0x00040000U)

#define CANFD_ILS_DRXL_SHIFT                                (19U)
#define CANFD_ILS_DRXL_MASK                                 (0x00080000U)

#define CANFD_ILS_ELOL_SHIFT                                (22U)
#define CANFD_ILS_ELOL_MASK                                 (0x00400000U)

#define CANFD_ILS_EPL_SHIFT                                 (23U)
#define CANFD_ILS_EPL_MASK                                  (0x00800000U)

#define CANFD_ILS_EWL_SHIFT                                 (24U)
#define CANFD_ILS_EWL_MASK                                  (0x01000000U)

#define CANFD_ILS_BOL_SHIFT                                 (25U)
#define CANFD_ILS_BOL_MASK                                  (0x02000000U)

#define CANFD_ILS_WDIL_SHIFT                                (26U)
#define CANFD_ILS_WDIL_MASK                                 (0x04000000U)

#define CANFD_ILS_PEAL_SHIFT                                (27U)
#define CANFD_ILS_PEAL_MASK                                 (0x08000000U)

#define CANFD_ILS_PEDL_SHIFT                                (28U)
#define CANFD_ILS_PEDL_MASK                                 (0x10000000U)

#define CANFD_ILS_ARAL_SHIFT                                (29U)
#define CANFD_ILS_ARAL_MASK                                 (0x20000000U)

#define CANFD_ILE_EINT0_SHIFT                               (0U)
#define CANFD_ILE_EINT0_MASK                                (0x00000001U)

#define CANFD_ILE_EINT1_SHIFT                               (1U)
#define CANFD_ILE_EINT1_MASK                                (0x00000002U)

#define CANFD_GFC_RRFE_SHIFT                                (0U)
#define CANFD_GFC_RRFE_MASK                                 (0x00000001U)

#define CANFD_GFC_RRFS_SHIFT                                (1U)
#define CANFD_GFC_RRFS_MASK                                 (0x00000002U)

#define CANFD_GFC_ANFE_SHIFT                                (2U)
#define CANFD_GFC_ANFE_MASK                                 (0x0000000cU)

#define CANFD_GFC_ANFS_SHIFT                                (4U)
#define CANFD_GFC_ANFS_MASK                                 (0x00000030U)

#define CANFD_SIDFC_FLSSA_SHIFT                             (2U)
#define CANFD_SIDFC_FLSSA_MASK                              (0x0000fffcU)

#define CANFD_SIDFC_LSS_SHIFT                               (16U)
#define CANFD_SIDFC_LSS_MASK                                (0x00ff0000U)

#define CANFD_XIDFC_FLESA_SHIFT                             (2U)
#define CANFD_XIDFC_FLESA_MASK                              (0x0000fffcU)

#define CANFD_XIDFC_LSE_SHIFT                               (16U)
#define CANFD_XIDFC_LSE_MASK                                (0x007f0000U)

#define CANFD_XIDAM_EIDM_SHIFT                              (0U)
#define CANFD_XIDAM_EIDM_MASK                               (0x1fffffffU)

#define CANFD_HPMS_BIDX_SHIFT                               (0U)
#define CANFD_HPMS_BIDX_MASK                                (0x0000003fU)

#define CANFD_HPMS_MSI_SHIFT                                (6U)
#define CANFD_HPMS_MSI_MASK                                 (0x000000c0U)

#define CANFD_HPMS_FIDX_SHIFT                               (8U)
#define CANFD_HPMS_FIDX_MASK                                (0x00007f00U)

#define CANFD_HPMS_FLST_SHIFT                               (15U)
#define CANFD_HPMS_FLST_MASK                                (0x00008000U)

#define CANFD_NDAT1_ND0_SHIFT                               (0U)
#define CANFD_NDAT1_ND0_MASK                                (0x00000001U)

#define CANFD_NDAT1_ND1_SHIFT                               (1U)
#define CANFD_NDAT1_ND1_MASK                                (0x00000002U)

#define CANFD_NDAT1_ND2_SHIFT                               (2U)
#define CANFD_NDAT1_ND2_MASK                                (0x00000004U)

#define CANFD_NDAT1_ND3_SHIFT                               (3U)
#define CANFD_NDAT1_ND3_MASK                                (0x00000008U)

#define CANFD_NDAT1_ND4_SHIFT                               (4U)
#define CANFD_NDAT1_ND4_MASK                                (0x00000010U)

#define CANFD_NDAT1_ND5_SHIFT                               (5U)
#define CANFD_NDAT1_ND5_MASK                                (0x00000020U)

#define CANFD_NDAT1_ND6_SHIFT                               (6U)
#define CANFD_NDAT1_ND6_MASK                                (0x00000040U)

#define CANFD_NDAT1_ND7_SHIFT                               (7U)
#define CANFD_NDAT1_ND7_MASK                                (0x00000080U)

#define CANFD_NDAT1_ND8_SHIFT                               (8U)
#define CANFD_NDAT1_ND8_MASK                                (0x00000100U)

#define CANFD_NDAT1_ND9_SHIFT                               (9U)
#define CANFD_NDAT1_ND9_MASK                                (0x00000200U)

#define CANFD_NDAT1_ND10_SHIFT                              (10U)
#define CANFD_NDAT1_ND10_MASK                               (0x00000400U)

#define CANFD_NDAT1_ND11_SHIFT                              (11U)
#define CANFD_NDAT1_ND11_MASK                               (0x00000800U)

#define CANFD_NDAT1_ND12_SHIFT                              (12U)
#define CANFD_NDAT1_ND12_MASK                               (0x00001000U)

#define CANFD_NDAT1_ND13_SHIFT                              (13U)
#define CANFD_NDAT1_ND13_MASK                               (0x00002000U)

#define CANFD_NDAT1_ND14_SHIFT                              (14U)
#define CANFD_NDAT1_ND14_MASK                               (0x00004000U)

#define CANFD_NDAT1_ND15_SHIFT                              (15U)
#define CANFD_NDAT1_ND15_MASK                               (0x00008000U)

#define CANFD_NDAT1_ND16_SHIFT                              (16U)
#define CANFD_NDAT1_ND16_MASK                               (0x00010000U)

#define CANFD_NDAT1_ND17_SHIFT                              (17U)
#define CANFD_NDAT1_ND17_MASK                               (0x00020000U)

#define CANFD_NDAT1_ND18_SHIFT                              (18U)
#define CANFD_NDAT1_ND18_MASK                               (0x00040000U)

#define CANFD_NDAT1_ND19_SHIFT                              (19U)
#define CANFD_NDAT1_ND19_MASK                               (0x00080000U)

#define CANFD_NDAT1_ND20_SHIFT                              (20U)
#define CANFD_NDAT1_ND20_MASK                               (0x00100000U)

#define CANFD_NDAT1_ND21_SHIFT                              (21U)
#define CANFD_NDAT1_ND21_MASK                               (0x00200000U)

#define CANFD_NDAT1_ND22_SHIFT                              (22U)
#define CANFD_NDAT1_ND22_MASK                               (0x00400000U)

#define CANFD_NDAT1_ND23_SHIFT                              (23U)
#define CANFD_NDAT1_ND23_MASK                               (0x00800000U)

#define CANFD_NDAT1_ND24_SHIFT                              (24U)
#define CANFD_NDAT1_ND24_MASK                               (0x01000000U)

#define CANFD_NDAT1_ND25_SHIFT                              (25U)
#define CANFD_NDAT1_ND25_MASK                               (0x02000000U)

#define CANFD_NDAT1_ND26_SHIFT                              (26U)
#define CANFD_NDAT1_ND26_MASK                               (0x04000000U)

#define CANFD_NDAT1_ND27_SHIFT                              (27U)
#define CANFD_NDAT1_ND27_MASK                               (0x08000000U)

#define CANFD_NDAT1_ND28_SHIFT                              (28U)
#define CANFD_NDAT1_ND28_MASK                               (0x10000000U)

#define CANFD_NDAT1_ND29_SHIFT                              (29U)
#define CANFD_NDAT1_ND29_MASK                               (0x20000000U)

#define CANFD_NDAT1_ND30_SHIFT                              (30U)
#define CANFD_NDAT1_ND30_MASK                               (0x40000000U)

#define CANFD_NDAT1_ND31_SHIFT                              (31U)
#define CANFD_NDAT1_ND31_MASK                               (0x80000000U)

#define CANFD_NDAT2_ND32_SHIFT                              (0U)
#define CANFD_NDAT2_ND32_MASK                               (0x00000001U)

#define CANFD_NDAT2_ND33_SHIFT                              (1U)
#define CANFD_NDAT2_ND33_MASK                               (0x00000002U)

#define CANFD_NDAT2_ND34_SHIFT                              (2U)
#define CANFD_NDAT2_ND34_MASK                               (0x00000004U)

#define CANFD_NDAT2_ND35_SHIFT                              (3U)
#define CANFD_NDAT2_ND35_MASK                               (0x00000008U)

#define CANFD_NDAT2_ND36_SHIFT                              (4U)
#define CANFD_NDAT2_ND36_MASK                               (0x00000010U)

#define CANFD_NDAT2_ND37_SHIFT                              (5U)
#define CANFD_NDAT2_ND37_MASK                               (0x00000020U)

#define CANFD_NDAT2_ND38_SHIFT                              (6U)
#define CANFD_NDAT2_ND38_MASK                               (0x00000040U)

#define CANFD_NDAT2_ND39_SHIFT                              (7U)
#define CANFD_NDAT2_ND39_MASK                               (0x00000080U)

#define CANFD_NDAT2_ND40_SHIFT                              (8U)
#define CANFD_NDAT2_ND40_MASK                               (0x00000100U)

#define CANFD_NDAT2_ND41_SHIFT                              (9U)
#define CANFD_NDAT2_ND41_MASK                               (0x00000200U)

#define CANFD_NDAT2_ND42_SHIFT                              (10U)
#define CANFD_NDAT2_ND42_MASK                               (0x00000400U)

#define CANFD_NDAT2_ND43_SHIFT                              (11U)
#define CANFD_NDAT2_ND43_MASK                               (0x00000800U)

#define CANFD_NDAT2_ND44_SHIFT                              (12U)
#define CANFD_NDAT2_ND44_MASK                               (0x00001000U)

#define CANFD_NDAT2_ND45_SHIFT                              (13U)
#define CANFD_NDAT2_ND45_MASK                               (0x00002000U)

#define CANFD_NDAT2_ND46_SHIFT                              (14U)
#define CANFD_NDAT2_ND46_MASK                               (0x00004000U)

#define CANFD_NDAT2_ND47_SHIFT                              (15U)
#define CANFD_NDAT2_ND47_MASK                               (0x00008000U)

#define CANFD_NDAT2_ND48_SHIFT                              (16U)
#define CANFD_NDAT2_ND48_MASK                               (0x00010000U)

#define CANFD_NDAT2_ND49_SHIFT                              (17U)
#define CANFD_NDAT2_ND49_MASK                               (0x00020000U)

#define CANFD_NDAT2_ND50_SHIFT                              (18U)
#define CANFD_NDAT2_ND50_MASK                               (0x00040000U)

#define CANFD_NDAT2_ND51_SHIFT                              (19U)
#define CANFD_NDAT2_ND51_MASK                               (0x00080000U)

#define CANFD_NDAT2_ND52_SHIFT                              (20U)
#define CANFD_NDAT2_ND52_MASK                               (0x00100000U)

#define CANFD_NDAT2_ND53_SHIFT                              (21U)
#define CANFD_NDAT2_ND53_MASK                               (0x00200000U)

#define CANFD_NDAT2_ND54_SHIFT                              (22U)
#define CANFD_NDAT2_ND54_MASK                               (0x00400000U)

#define CANFD_NDAT2_ND55_SHIFT                              (23U)
#define CANFD_NDAT2_ND55_MASK                               (0x00800000U)

#define CANFD_NDAT2_ND56_SHIFT                              (24U)
#define CANFD_NDAT2_ND56_MASK                               (0x01000000U)

#define CANFD_NDAT2_ND57_SHIFT                              (25U)
#define CANFD_NDAT2_ND57_MASK                               (0x02000000U)

#define CANFD_NDAT2_ND58_SHIFT                              (26U)
#define CANFD_NDAT2_ND58_MASK                               (0x04000000U)

#define CANFD_NDAT2_ND59_SHIFT                              (27U)
#define CANFD_NDAT2_ND59_MASK                               (0x08000000U)

#define CANFD_NDAT2_ND60_SHIFT                              (28U)
#define CANFD_NDAT2_ND60_MASK                               (0x10000000U)

#define CANFD_NDAT2_ND61_SHIFT                              (29U)
#define CANFD_NDAT2_ND61_MASK                               (0x20000000U)

#define CANFD_NDAT2_ND62_SHIFT                              (30U)
#define CANFD_NDAT2_ND62_MASK                               (0x40000000U)

#define CANFD_NDAT2_ND63_SHIFT                              (31U)
#define CANFD_NDAT2_ND63_MASK                               (0x80000000U)

#define CANFD_RXF0C_F0SA_SHIFT                              (2U)
#define CANFD_RXF0C_F0SA_MASK                               (0x0000fffcU)

#define CANFD_RXF0C_F0S_SHIFT                               (16U)
#define CANFD_RXF0C_F0S_MASK                                (0x007f0000U)

#define CANFD_RXF0C_F0WM_SHIFT                              (24U)
#define CANFD_RXF0C_F0WM_MASK                               (0x7f000000U)

#define CANFD_RXF0C_F0OM_SHIFT                              (31U)
#define CANFD_RXF0C_F0OM_MASK                               (0x80000000U)

#define CANFD_RXF0S_F0FL_SHIFT                              (0U)
#define CANFD_RXF0S_F0FL_MASK                               (0x0000007fU)

#define CANFD_RXF0S_F0GI_SHIFT                              (8U)
#define CANFD_RXF0S_F0GI_MASK                               (0x00003f00U)

#define CANFD_RXF0S_F0PI_SHIFT                              (16U)
#define CANFD_RXF0S_F0PI_MASK                               (0x003f0000U)

#define CANFD_RXF0S_F0F_SHIFT                               (24U)
#define CANFD_RXF0S_F0F_MASK                                (0x01000000U)

#define CANFD_RXF0S_RF0L_SHIFT                              (25U)
#define CANFD_RXF0S_RF0L_MASK                               (0x02000000U)

#define CANFD_RXF0A_F0AI_SHIFT                              (0U)
#define CANFD_RXF0A_F0AI_MASK                               (0x0000003fU)

#define CANFD_RXBC_RBSA_SHIFT                               (2U)
#define CANFD_RXBC_RBSA_MASK                                (0x0000fffcU)

#define CANFD_RXF1C_F1SA_SHIFT                              (2U)
#define CANFD_RXF1C_F1SA_MASK                               (0x0000fffcU)

#define CANFD_RXF1C_F1S_SHIFT                               (16U)
#define CANFD_RXF1C_F1S_MASK                                (0x007f0000U)

#define CANFD_RXF1C_F1WM_SHIFT                              (24U)
#define CANFD_RXF1C_F1WM_MASK                               (0x7f000000U)

#define CANFD_RXF1C_F1OM_SHIFT                              (31U)
#define CANFD_RXF1C_F1OM_MASK                               (0x80000000U)

#define CANFD_RXF1S_F1FL_SHIFT                              (0U)
#define CANFD_RXF1S_F1FL_MASK                               (0x0000007fU)

#define CANFD_RXF1S_F1GI_SHIFT                              (8U)
#define CANFD_RXF1S_F1GI_MASK                               (0x00003f00U)

#define CANFD_RXF1S_F1PI_SHIFT                              (16U)
#define CANFD_RXF1S_F1PI_MASK                               (0x003f0000U)

#define CANFD_RXF1S_F1F_SHIFT                               (24U)
#define CANFD_RXF1S_F1F_MASK                                (0x01000000U)

#define CANFD_RXF1S_RF1L_SHIFT                              (25U)
#define CANFD_RXF1S_RF1L_MASK                               (0x02000000U)

#define CANFD_RXF1S_DMS_SHIFT                               (30U)
#define CANFD_RXF1S_DMS_MASK                                (0xc0000000U)

#define CANFD_RXF1A_F1AI_SHIFT                              (0U)
#define CANFD_RXF1A_F1AI_MASK                               (0x0000003fU)

#define CANFD_RXESC_F0DS_SHIFT                              (0U)
#define CANFD_RXESC_F0DS_MASK                               (0x00000007U)

#define CANFD_RXESC_F1DS_SHIFT                              (4U)
#define CANFD_RXESC_F1DS_MASK                               (0x00000070U)

#define CANFD_RXESC_RBDS_SHIFT                              (8U)
#define CANFD_RXESC_RBDS_MASK                               (0x00000700U)

#define CANFD_TXBC_TBSA_SHIFT                               (2U)
#define CANFD_TXBC_TBSA_MASK                                (0x0000fffcU)

#define CANFD_TXBC_NDTB_SHIFT                               (16U)
#define CANFD_TXBC_NDTB_MASK                                (0x003f0000U)

#define CANFD_TXBC_TFQS_SHIFT                               (24U)
#define CANFD_TXBC_TFQS_MASK                                (0x3f000000U)

#define CANFD_TXBC_TFQM_SHIFT                               (30U)
#define CANFD_TXBC_TFQM_MASK                                (0x40000000U)

#define CANFD_TXFQS_TFFL_SHIFT                              (0U)
#define CANFD_TXFQS_TFFL_MASK                               (0x0000003fU)

#define CANFD_TXFQS_TFGI_SHIFT                              (8U)
#define CANFD_TXFQS_TFGI_MASK                               (0x00001f00U)

#define CANFD_TXFQS_TFQPI_SHIFT                             (16U)
#define CANFD_TXFQS_TFQPI_MASK                              (0x001f0000U)

#define CANFD_TXFQS_TFQF_SHIFT                              (21U)
#define CANFD_TXFQS_TFQF_MASK                               (0x00200000U)

#define CANFD_TXESC_TBDS_SHIFT                              (0U)
#define CANFD_TXESC_TBDS_MASK                               (0x00000007U)

#define CANFD_TXBRP_TRP0_SHIFT                              (0U)
#define CANFD_TXBRP_TRP0_MASK                               (0x00000001U)

#define CANFD_TXBRP_TRP1_SHIFT                              (1U)
#define CANFD_TXBRP_TRP1_MASK                               (0x00000002U)

#define CANFD_TXBRP_TRP2_SHIFT                              (2U)
#define CANFD_TXBRP_TRP2_MASK                               (0x00000004U)

#define CANFD_TXBRP_TRP3_SHIFT                              (3U)
#define CANFD_TXBRP_TRP3_MASK                               (0x00000008U)

#define CANFD_TXBRP_TRP4_SHIFT                              (4U)
#define CANFD_TXBRP_TRP4_MASK                               (0x00000010U)

#define CANFD_TXBRP_TRP5_SHIFT                              (5U)
#define CANFD_TXBRP_TRP5_MASK                               (0x00000020U)

#define CANFD_TXBRP_TRP6_SHIFT                              (6U)
#define CANFD_TXBRP_TRP6_MASK                               (0x00000040U)

#define CANFD_TXBRP_TRP7_SHIFT                              (7U)
#define CANFD_TXBRP_TRP7_MASK                               (0x00000080U)

#define CANFD_TXBRP_TRP8_SHIFT                              (8U)
#define CANFD_TXBRP_TRP8_MASK                               (0x00000100U)

#define CANFD_TXBRP_TRP9_SHIFT                              (9U)
#define CANFD_TXBRP_TRP9_MASK                               (0x00000200U)

#define CANFD_TXBRP_TRP10_SHIFT                             (10U)
#define CANFD_TXBRP_TRP10_MASK                              (0x00000400U)

#define CANFD_TXBRP_TRP11_SHIFT                             (11U)
#define CANFD_TXBRP_TRP11_MASK                              (0x00000800U)

#define CANFD_TXBRP_TRP12_SHIFT                             (12U)
#define CANFD_TXBRP_TRP12_MASK                              (0x00001000U)

#define CANFD_TXBRP_TRP13_SHIFT                             (13U)
#define CANFD_TXBRP_TRP13_MASK                              (0x00002000U)

#define CANFD_TXBRP_TRP14_SHIFT                             (14U)
#define CANFD_TXBRP_TRP14_MASK                              (0x00004000U)

#define CANFD_TXBRP_TRP15_SHIFT                             (15U)
#define CANFD_TXBRP_TRP15_MASK                              (0x00008000U)

#define CANFD_TXBRP_TRP16_SHIFT                             (16U)
#define CANFD_TXBRP_TRP16_MASK                              (0x00010000U)

#define CANFD_TXBRP_TRP17_SHIFT                             (17U)
#define CANFD_TXBRP_TRP17_MASK                              (0x00020000U)

#define CANFD_TXBRP_TRP18_SHIFT                             (18U)
#define CANFD_TXBRP_TRP18_MASK                              (0x00040000U)

#define CANFD_TXBRP_TRP19_SHIFT                             (19U)
#define CANFD_TXBRP_TRP19_MASK                              (0x00080000U)

#define CANFD_TXBRP_TRP20_SHIFT                             (20U)
#define CANFD_TXBRP_TRP20_MASK                              (0x00100000U)

#define CANFD_TXBRP_TRP21_SHIFT                             (21U)
#define CANFD_TXBRP_TRP21_MASK                              (0x00200000U)

#define CANFD_TXBRP_TRP22_SHIFT                             (22U)
#define CANFD_TXBRP_TRP22_MASK                              (0x00400000U)

#define CANFD_TXBRP_TRP23_SHIFT                             (23U)
#define CANFD_TXBRP_TRP23_MASK                              (0x00800000U)

#define CANFD_TXBRP_TRP24_SHIFT                             (24U)
#define CANFD_TXBRP_TRP24_MASK                              (0x01000000U)

#define CANFD_TXBRP_TRP25_SHIFT                             (25U)
#define CANFD_TXBRP_TRP25_MASK                              (0x02000000U)

#define CANFD_TXBRP_TRP26_SHIFT                             (26U)
#define CANFD_TXBRP_TRP26_MASK                              (0x04000000U)

#define CANFD_TXBRP_TRP27_SHIFT                             (27U)
#define CANFD_TXBRP_TRP27_MASK                              (0x08000000U)

#define CANFD_TXBRP_TRP28_SHIFT                             (28U)
#define CANFD_TXBRP_TRP28_MASK                              (0x10000000U)

#define CANFD_TXBRP_TRP29_SHIFT                             (29U)
#define CANFD_TXBRP_TRP29_MASK                              (0x20000000U)

#define CANFD_TXBRP_TRP30_SHIFT                             (30U)
#define CANFD_TXBRP_TRP30_MASK                              (0x40000000U)

#define CANFD_TXBRP_TRP31_SHIFT                             (31U)
#define CANFD_TXBRP_TRP31_MASK                              (0x80000000U)

#define CANFD_TXBAR_AR0_SHIFT                               (0U)
#define CANFD_TXBAR_AR0_MASK                                (0x00000001U)

#define CANFD_TXBAR_AR1_SHIFT                               (1U)
#define CANFD_TXBAR_AR1_MASK                                (0x00000002U)

#define CANFD_TXBAR_AR2_SHIFT                               (2U)
#define CANFD_TXBAR_AR2_MASK                                (0x00000004U)

#define CANFD_TXBAR_AR3_SHIFT                               (3U)
#define CANFD_TXBAR_AR3_MASK                                (0x00000008U)

#define CANFD_TXBAR_AR4_SHIFT                               (4U)
#define CANFD_TXBAR_AR4_MASK                                (0x00000010U)

#define CANFD_TXBAR_AR5_SHIFT                               (5U)
#define CANFD_TXBAR_AR5_MASK                                (0x00000020U)

#define CANFD_TXBAR_AR6_SHIFT                               (6U)
#define CANFD_TXBAR_AR6_MASK                                (0x00000040U)

#define CANFD_TXBAR_AR7_SHIFT                               (7U)
#define CANFD_TXBAR_AR7_MASK                                (0x00000080U)

#define CANFD_TXBAR_AR8_SHIFT                               (8U)
#define CANFD_TXBAR_AR8_MASK                                (0x00000100U)

#define CANFD_TXBAR_AR9_SHIFT                               (9U)
#define CANFD_TXBAR_AR9_MASK                                (0x00000200U)

#define CANFD_TXBAR_AR10_SHIFT                              (10U)
#define CANFD_TXBAR_AR10_MASK                               (0x00000400U)

#define CANFD_TXBAR_AR11_SHIFT                              (11U)
#define CANFD_TXBAR_AR11_MASK                               (0x00000800U)

#define CANFD_TXBAR_AR12_SHIFT                              (12U)
#define CANFD_TXBAR_AR12_MASK                               (0x00001000U)

#define CANFD_TXBAR_AR13_SHIFT                              (13U)
#define CANFD_TXBAR_AR13_MASK                               (0x00002000U)

#define CANFD_TXBAR_AR14_SHIFT                              (14U)
#define CANFD_TXBAR_AR14_MASK                               (0x00004000U)

#define CANFD_TXBAR_AR15_SHIFT                              (15U)
#define CANFD_TXBAR_AR15_MASK                               (0x00008000U)

#define CANFD_TXBAR_AR16_SHIFT                              (16U)
#define CANFD_TXBAR_AR16_MASK                               (0x00010000U)

#define CANFD_TXBAR_AR17_SHIFT                              (17U)
#define CANFD_TXBAR_AR17_MASK                               (0x00020000U)

#define CANFD_TXBAR_AR18_SHIFT                              (18U)
#define CANFD_TXBAR_AR18_MASK                               (0x00040000U)

#define CANFD_TXBAR_AR19_SHIFT                              (19U)
#define CANFD_TXBAR_AR19_MASK                               (0x00080000U)

#define CANFD_TXBAR_AR20_SHIFT                              (20U)
#define CANFD_TXBAR_AR20_MASK                               (0x00100000U)

#define CANFD_TXBAR_AR21_SHIFT                              (21U)
#define CANFD_TXBAR_AR21_MASK                               (0x00200000U)

#define CANFD_TXBAR_AR22_SHIFT                              (22U)
#define CANFD_TXBAR_AR22_MASK                               (0x00400000U)

#define CANFD_TXBAR_AR23_SHIFT                              (23U)
#define CANFD_TXBAR_AR23_MASK                               (0x00800000U)

#define CANFD_TXBAR_AR24_SHIFT                              (24U)
#define CANFD_TXBAR_AR24_MASK                               (0x01000000U)

#define CANFD_TXBAR_AR25_SHIFT                              (25U)
#define CANFD_TXBAR_AR25_MASK                               (0x02000000U)

#define CANFD_TXBAR_AR26_SHIFT                              (26U)
#define CANFD_TXBAR_AR26_MASK                               (0x04000000U)

#define CANFD_TXBAR_AR27_SHIFT                              (27U)
#define CANFD_TXBAR_AR27_MASK                               (0x08000000U)

#define CANFD_TXBAR_AR28_SHIFT                              (28U)
#define CANFD_TXBAR_AR28_MASK                               (0x10000000U)

#define CANFD_TXBAR_AR29_SHIFT                              (29U)
#define CANFD_TXBAR_AR29_MASK                               (0x20000000U)

#define CANFD_TXBAR_AR30_SHIFT                              (30U)
#define CANFD_TXBAR_AR30_MASK                               (0x40000000U)

#define CANFD_TXBAR_AR31_SHIFT                              (31U)
#define CANFD_TXBAR_AR31_MASK                               (0x80000000U)

#define CANFD_TXBCR_CR0_SHIFT                               (0U)
#define CANFD_TXBCR_CR0_MASK                                (0x00000001U)

#define CANFD_TXBCR_CR1_SHIFT                               (1U)
#define CANFD_TXBCR_CR1_MASK                                (0x00000002U)

#define CANFD_TXBCR_CR2_SHIFT                               (2U)
#define CANFD_TXBCR_CR2_MASK                                (0x00000004U)

#define CANFD_TXBCR_CR3_SHIFT                               (3U)
#define CANFD_TXBCR_CR3_MASK                                (0x00000008U)

#define CANFD_TXBCR_CR4_SHIFT                               (4U)
#define CANFD_TXBCR_CR4_MASK                                (0x00000010U)

#define CANFD_TXBCR_CR5_SHIFT                               (5U)
#define CANFD_TXBCR_CR5_MASK                                (0x00000020U)

#define CANFD_TXBCR_CR6_SHIFT                               (6U)
#define CANFD_TXBCR_CR6_MASK                                (0x00000040U)

#define CANFD_TXBCR_CR7_SHIFT                               (7U)
#define CANFD_TXBCR_CR7_MASK                                (0x00000080U)

#define CANFD_TXBCR_CR8_SHIFT                               (8U)
#define CANFD_TXBCR_CR8_MASK                                (0x00000100U)

#define CANFD_TXBCR_CR9_SHIFT                               (9U)
#define CANFD_TXBCR_CR9_MASK                                (0x00000200U)

#define CANFD_TXBCR_CR10_SHIFT                              (10U)
#define CANFD_TXBCR_CR10_MASK                               (0x00000400U)

#define CANFD_TXBCR_CR11_SHIFT                              (11U)
#define CANFD_TXBCR_CR11_MASK                               (0x00000800U)

#define CANFD_TXBCR_CR12_SHIFT                              (12U)
#define CANFD_TXBCR_CR12_MASK                               (0x00001000U)

#define CANFD_TXBCR_CR13_SHIFT                              (13U)
#define CANFD_TXBCR_CR13_MASK                               (0x00002000U)

#define CANFD_TXBCR_CR14_SHIFT                              (14U)
#define CANFD_TXBCR_CR14_MASK                               (0x00004000U)

#define CANFD_TXBCR_CR15_SHIFT                              (15U)
#define CANFD_TXBCR_CR15_MASK                               (0x00008000U)

#define CANFD_TXBCR_CR16_SHIFT                              (16U)
#define CANFD_TXBCR_CR16_MASK                               (0x00010000U)

#define CANFD_TXBCR_CR17_SHIFT                              (17U)
#define CANFD_TXBCR_CR17_MASK                               (0x00020000U)

#define CANFD_TXBCR_CR18_SHIFT                              (18U)
#define CANFD_TXBCR_CR18_MASK                               (0x00040000U)

#define CANFD_TXBCR_CR19_SHIFT                              (19U)
#define CANFD_TXBCR_CR19_MASK                               (0x00080000U)

#define CANFD_TXBCR_CR20_SHIFT                              (20U)
#define CANFD_TXBCR_CR20_MASK                               (0x00100000U)

#define CANFD_TXBCR_CR21_SHIFT                              (21U)
#define CANFD_TXBCR_CR21_MASK                               (0x00200000U)

#define CANFD_TXBCR_CR22_SHIFT                              (22U)
#define CANFD_TXBCR_CR22_MASK                               (0x00400000U)

#define CANFD_TXBCR_CR23_SHIFT                              (23U)
#define CANFD_TXBCR_CR23_MASK                               (0x00800000U)

#define CANFD_TXBCR_CR24_SHIFT                              (24U)
#define CANFD_TXBCR_CR24_MASK                               (0x01000000U)

#define CANFD_TXBCR_CR25_SHIFT                              (25U)
#define CANFD_TXBCR_CR25_MASK                               (0x02000000U)

#define CANFD_TXBCR_CR26_SHIFT                              (26U)
#define CANFD_TXBCR_CR26_MASK                               (0x04000000U)

#define CANFD_TXBCR_CR27_SHIFT                              (27U)
#define CANFD_TXBCR_CR27_MASK                               (0x08000000U)

#define CANFD_TXBCR_CR28_SHIFT                              (28U)
#define CANFD_TXBCR_CR28_MASK                               (0x10000000U)

#define CANFD_TXBCR_CR29_SHIFT                              (29U)
#define CANFD_TXBCR_CR29_MASK                               (0x20000000U)

#define CANFD_TXBCR_CR30_SHIFT                              (30U)
#define CANFD_TXBCR_CR30_MASK                               (0x40000000U)

#define CANFD_TXBCR_CR31_SHIFT                              (31U)
#define CANFD_TXBCR_CR31_MASK                               (0x80000000U)

#define CANFD_TXBTO_TO0_SHIFT                               (0U)
#define CANFD_TXBTO_TO0_MASK                                (0x00000001U)

#define CANFD_TXBTO_TO1_SHIFT                               (1U)
#define CANFD_TXBTO_TO1_MASK                                (0x00000002U)

#define CANFD_TXBTO_TO2_SHIFT                               (2U)
#define CANFD_TXBTO_TO2_MASK                                (0x00000004U)

#define CANFD_TXBTO_TO3_SHIFT                               (3U)
#define CANFD_TXBTO_TO3_MASK                                (0x00000008U)

#define CANFD_TXBTO_TO4_SHIFT                               (4U)
#define CANFD_TXBTO_TO4_MASK                                (0x00000010U)

#define CANFD_TXBTO_TO5_SHIFT                               (5U)
#define CANFD_TXBTO_TO5_MASK                                (0x00000020U)

#define CANFD_TXBTO_TO6_SHIFT                               (6U)
#define CANFD_TXBTO_TO6_MASK                                (0x00000040U)

#define CANFD_TXBTO_TO7_SHIFT                               (7U)
#define CANFD_TXBTO_TO7_MASK                                (0x00000080U)

#define CANFD_TXBTO_TO8_SHIFT                               (8U)
#define CANFD_TXBTO_TO8_MASK                                (0x00000100U)

#define CANFD_TXBTO_TO9_SHIFT                               (9U)
#define CANFD_TXBTO_TO9_MASK                                (0x00000200U)

#define CANFD_TXBTO_TO10_SHIFT                              (10U)
#define CANFD_TXBTO_TO10_MASK                               (0x00000400U)

#define CANFD_TXBTO_TO11_SHIFT                              (11U)
#define CANFD_TXBTO_TO11_MASK                               (0x00000800U)

#define CANFD_TXBTO_TO12_SHIFT                              (12U)
#define CANFD_TXBTO_TO12_MASK                               (0x00001000U)

#define CANFD_TXBTO_TO13_SHIFT                              (13U)
#define CANFD_TXBTO_TO13_MASK                               (0x00002000U)

#define CANFD_TXBTO_TO14_SHIFT                              (14U)
#define CANFD_TXBTO_TO14_MASK                               (0x00004000U)

#define CANFD_TXBTO_TO15_SHIFT                              (15U)
#define CANFD_TXBTO_TO15_MASK                               (0x00008000U)

#define CANFD_TXBTO_TO16_SHIFT                              (16U)
#define CANFD_TXBTO_TO16_MASK                               (0x00010000U)

#define CANFD_TXBTO_TO17_SHIFT                              (17U)
#define CANFD_TXBTO_TO17_MASK                               (0x00020000U)

#define CANFD_TXBTO_TO18_SHIFT                              (18U)
#define CANFD_TXBTO_TO18_MASK                               (0x00040000U)

#define CANFD_TXBTO_TO19_SHIFT                              (19U)
#define CANFD_TXBTO_TO19_MASK                               (0x00080000U)

#define CANFD_TXBTO_TO20_SHIFT                              (20U)
#define CANFD_TXBTO_TO20_MASK                               (0x00100000U)

#define CANFD_TXBTO_TO21_SHIFT                              (21U)
#define CANFD_TXBTO_TO21_MASK                               (0x00200000U)

#define CANFD_TXBTO_TO22_SHIFT                              (22U)
#define CANFD_TXBTO_TO22_MASK                               (0x00400000U)

#define CANFD_TXBTO_TO23_SHIFT                              (23U)
#define CANFD_TXBTO_TO23_MASK                               (0x00800000U)

#define CANFD_TXBTO_TO24_SHIFT                              (24U)
#define CANFD_TXBTO_TO24_MASK                               (0x01000000U)

#define CANFD_TXBTO_TO25_SHIFT                              (25U)
#define CANFD_TXBTO_TO25_MASK                               (0x02000000U)

#define CANFD_TXBTO_TO26_SHIFT                              (26U)
#define CANFD_TXBTO_TO26_MASK                               (0x04000000U)

#define CANFD_TXBTO_TO27_SHIFT                              (27U)
#define CANFD_TXBTO_TO27_MASK                               (0x08000000U)

#define CANFD_TXBTO_TO28_SHIFT                              (28U)
#define CANFD_TXBTO_TO28_MASK                               (0x10000000U)

#define CANFD_TXBTO_TO29_SHIFT                              (29U)
#define CANFD_TXBTO_TO29_MASK                               (0x20000000U)

#define CANFD_TXBTO_TO30_SHIFT                              (30U)
#define CANFD_TXBTO_TO30_MASK                               (0x40000000U)

#define CANFD_TXBTO_TO31_SHIFT                              (31U)
#define CANFD_TXBTO_TO31_MASK                               (0x80000000U)

#define CANFD_TXBCF_CF0_SHIFT                               (0U)
#define CANFD_TXBCF_CF0_MASK                                (0x00000001U)

#define CANFD_TXBCF_CF1_SHIFT                               (1U)
#define CANFD_TXBCF_CF1_MASK                                (0x00000002U)

#define CANFD_TXBCF_CF2_SHIFT                               (2U)
#define CANFD_TXBCF_CF2_MASK                                (0x00000004U)

#define CANFD_TXBCF_CF3_SHIFT                               (3U)
#define CANFD_TXBCF_CF3_MASK                                (0x00000008U)

#define CANFD_TXBCF_CF4_SHIFT                               (4U)
#define CANFD_TXBCF_CF4_MASK                                (0x00000010U)

#define CANFD_TXBCF_CF5_SHIFT                               (5U)
#define CANFD_TXBCF_CF5_MASK                                (0x00000020U)

#define CANFD_TXBCF_CF6_SHIFT                               (6U)
#define CANFD_TXBCF_CF6_MASK                                (0x00000040U)

#define CANFD_TXBCF_CF7_SHIFT                               (7U)
#define CANFD_TXBCF_CF7_MASK                                (0x00000080U)

#define CANFD_TXBCF_CF8_SHIFT                               (8U)
#define CANFD_TXBCF_CF8_MASK                                (0x00000100U)

#define CANFD_TXBCF_CF9_SHIFT                               (9U)
#define CANFD_TXBCF_CF9_MASK                                (0x00000200U)

#define CANFD_TXBCF_CF10_SHIFT                              (10U)
#define CANFD_TXBCF_CF10_MASK                               (0x00000400U)

#define CANFD_TXBCF_CF11_SHIFT                              (11U)
#define CANFD_TXBCF_CF11_MASK                               (0x00000800U)

#define CANFD_TXBCF_CF12_SHIFT                              (12U)
#define CANFD_TXBCF_CF12_MASK                               (0x00001000U)

#define CANFD_TXBCF_CF13_SHIFT                              (13U)
#define CANFD_TXBCF_CF13_MASK                               (0x00002000U)

#define CANFD_TXBCF_CF14_SHIFT                              (14U)
#define CANFD_TXBCF_CF14_MASK                               (0x00004000U)

#define CANFD_TXBCF_CF15_SHIFT                              (15U)
#define CANFD_TXBCF_CF15_MASK                               (0x00008000U)

#define CANFD_TXBCF_CF16_SHIFT                              (16U)
#define CANFD_TXBCF_CF16_MASK                               (0x00010000U)

#define CANFD_TXBCF_CF17_SHIFT                              (17U)
#define CANFD_TXBCF_CF17_MASK                               (0x00020000U)

#define CANFD_TXBCF_CF18_SHIFT                              (18U)
#define CANFD_TXBCF_CF18_MASK                               (0x00040000U)

#define CANFD_TXBCF_CF19_SHIFT                              (19U)
#define CANFD_TXBCF_CF19_MASK                               (0x00080000U)

#define CANFD_TXBCF_CF20_SHIFT                              (20U)
#define CANFD_TXBCF_CF20_MASK                               (0x00100000U)

#define CANFD_TXBCF_CF21_SHIFT                              (21U)
#define CANFD_TXBCF_CF21_MASK                               (0x00200000U)

#define CANFD_TXBCF_CF22_SHIFT                              (22U)
#define CANFD_TXBCF_CF22_MASK                               (0x00400000U)

#define CANFD_TXBCF_CF23_SHIFT                              (23U)
#define CANFD_TXBCF_CF23_MASK                               (0x00800000U)

#define CANFD_TXBCF_CF24_SHIFT                              (24U)
#define CANFD_TXBCF_CF24_MASK                               (0x01000000U)

#define CANFD_TXBCF_CF25_SHIFT                              (25U)
#define CANFD_TXBCF_CF25_MASK                               (0x02000000U)

#define CANFD_TXBCF_CF26_SHIFT                              (26U)
#define CANFD_TXBCF_CF26_MASK                               (0x04000000U)

#define CANFD_TXBCF_CF27_SHIFT                              (27U)
#define CANFD_TXBCF_CF27_MASK                               (0x08000000U)

#define CANFD_TXBCF_CF28_SHIFT                              (28U)
#define CANFD_TXBCF_CF28_MASK                               (0x10000000U)

#define CANFD_TXBCF_CF29_SHIFT                              (29U)
#define CANFD_TXBCF_CF29_MASK                               (0x20000000U)

#define CANFD_TXBCF_CF30_SHIFT                              (30U)
#define CANFD_TXBCF_CF30_MASK                               (0x40000000U)

#define CANFD_TXBCF_CF31_SHIFT                              (31U)
#define CANFD_TXBCF_CF31_MASK                               (0x80000000U)

#define CANFD_TXBTIE_TIE0_SHIFT                             (0U)
#define CANFD_TXBTIE_TIE0_MASK                              (0x00000001U)

#define CANFD_TXBTIE_TIE1_SHIFT                             (1U)
#define CANFD_TXBTIE_TIE1_MASK                              (0x00000002U)

#define CANFD_TXBTIE_TIE2_SHIFT                             (2U)
#define CANFD_TXBTIE_TIE2_MASK                              (0x00000004U)

#define CANFD_TXBTIE_TIE3_SHIFT                             (3U)
#define CANFD_TXBTIE_TIE3_MASK                              (0x00000008U)

#define CANFD_TXBTIE_TIE4_SHIFT                             (4U)
#define CANFD_TXBTIE_TIE4_MASK                              (0x00000010U)

#define CANFD_TXBTIE_TIE5_SHIFT                             (5U)
#define CANFD_TXBTIE_TIE5_MASK                              (0x00000020U)

#define CANFD_TXBTIE_TIE6_SHIFT                             (6U)
#define CANFD_TXBTIE_TIE6_MASK                              (0x00000040U)

#define CANFD_TXBTIE_TIE7_SHIFT                             (7U)
#define CANFD_TXBTIE_TIE7_MASK                              (0x00000080U)

#define CANFD_TXBTIE_TIE8_SHIFT                             (8U)
#define CANFD_TXBTIE_TIE8_MASK                              (0x00000100U)

#define CANFD_TXBTIE_TIE9_SHIFT                             (9U)
#define CANFD_TXBTIE_TIE9_MASK                              (0x00000200U)

#define CANFD_TXBTIE_TIE10_SHIFT                            (10U)
#define CANFD_TXBTIE_TIE10_MASK                             (0x00000400U)

#define CANFD_TXBTIE_TIE11_SHIFT                            (11U)
#define CANFD_TXBTIE_TIE11_MASK                             (0x00000800U)

#define CANFD_TXBTIE_TIE12_SHIFT                            (12U)
#define CANFD_TXBTIE_TIE12_MASK                             (0x00001000U)

#define CANFD_TXBTIE_TIE13_SHIFT                            (13U)
#define CANFD_TXBTIE_TIE13_MASK                             (0x00002000U)

#define CANFD_TXBTIE_TIE14_SHIFT                            (14U)
#define CANFD_TXBTIE_TIE14_MASK                             (0x00004000U)

#define CANFD_TXBTIE_TIE15_SHIFT                            (15U)
#define CANFD_TXBTIE_TIE15_MASK                             (0x00008000U)

#define CANFD_TXBTIE_TIE16_SHIFT                            (16U)
#define CANFD_TXBTIE_TIE16_MASK                             (0x00010000U)

#define CANFD_TXBTIE_TIE17_SHIFT                            (17U)
#define CANFD_TXBTIE_TIE17_MASK                             (0x00020000U)

#define CANFD_TXBTIE_TIE18_SHIFT                            (18U)
#define CANFD_TXBTIE_TIE18_MASK                             (0x00040000U)

#define CANFD_TXBTIE_TIE19_SHIFT                            (19U)
#define CANFD_TXBTIE_TIE19_MASK                             (0x00080000U)

#define CANFD_TXBTIE_TIE20_SHIFT                            (20U)
#define CANFD_TXBTIE_TIE20_MASK                             (0x00100000U)

#define CANFD_TXBTIE_TIE21_SHIFT                            (21U)
#define CANFD_TXBTIE_TIE21_MASK                             (0x00200000U)

#define CANFD_TXBTIE_TIE22_SHIFT                            (22U)
#define CANFD_TXBTIE_TIE22_MASK                             (0x00400000U)

#define CANFD_TXBTIE_TIE23_SHIFT                            (23U)
#define CANFD_TXBTIE_TIE23_MASK                             (0x00800000U)

#define CANFD_TXBTIE_TIE24_SHIFT                            (24U)
#define CANFD_TXBTIE_TIE24_MASK                             (0x01000000U)

#define CANFD_TXBTIE_TIE25_SHIFT                            (25U)
#define CANFD_TXBTIE_TIE25_MASK                             (0x02000000U)

#define CANFD_TXBTIE_TIE26_SHIFT                            (26U)
#define CANFD_TXBTIE_TIE26_MASK                             (0x04000000U)

#define CANFD_TXBTIE_TIE27_SHIFT                            (27U)
#define CANFD_TXBTIE_TIE27_MASK                             (0x08000000U)

#define CANFD_TXBTIE_TIE28_SHIFT                            (28U)
#define CANFD_TXBTIE_TIE28_MASK                             (0x10000000U)

#define CANFD_TXBTIE_TIE29_SHIFT                            (29U)
#define CANFD_TXBTIE_TIE29_MASK                             (0x20000000U)

#define CANFD_TXBTIE_TIE30_SHIFT                            (30U)
#define CANFD_TXBTIE_TIE30_MASK                             (0x40000000U)

#define CANFD_TXBTIE_TIE31_SHIFT                            (31U)
#define CANFD_TXBTIE_TIE31_MASK                             (0x80000000U)

#define CANFD_TXBCIE_CFIE0_SHIFT                            (0U)
#define CANFD_TXBCIE_CFIE0_MASK                             (0x00000001U)

#define CANFD_TXBCIE_CFIE1_SHIFT                            (1U)
#define CANFD_TXBCIE_CFIE1_MASK                             (0x00000002U)

#define CANFD_TXBCIE_CFIE2_SHIFT                            (2U)
#define CANFD_TXBCIE_CFIE2_MASK                             (0x00000004U)

#define CANFD_TXBCIE_CFIE3_SHIFT                            (3U)
#define CANFD_TXBCIE_CFIE3_MASK                             (0x00000008U)

#define CANFD_TXBCIE_CFIE4_SHIFT                            (4U)
#define CANFD_TXBCIE_CFIE4_MASK                             (0x00000010U)

#define CANFD_TXBCIE_CFIE5_SHIFT                            (5U)
#define CANFD_TXBCIE_CFIE5_MASK                             (0x00000020U)

#define CANFD_TXBCIE_CFIE6_SHIFT                            (6U)
#define CANFD_TXBCIE_CFIE6_MASK                             (0x00000040U)

#define CANFD_TXBCIE_CFIE7_SHIFT                            (7U)
#define CANFD_TXBCIE_CFIE7_MASK                             (0x00000080U)

#define CANFD_TXBCIE_CFIE8_SHIFT                            (8U)
#define CANFD_TXBCIE_CFIE8_MASK                             (0x00000100U)

#define CANFD_TXBCIE_CFIE9_SHIFT                            (9U)
#define CANFD_TXBCIE_CFIE9_MASK                             (0x00000200U)

#define CANFD_TXBCIE_CFIE10_SHIFT                           (10U)
#define CANFD_TXBCIE_CFIE10_MASK                            (0x00000400U)

#define CANFD_TXBCIE_CFIE11_SHIFT                           (11U)
#define CANFD_TXBCIE_CFIE11_MASK                            (0x00000800U)

#define CANFD_TXBCIE_CFIE12_SHIFT                           (12U)
#define CANFD_TXBCIE_CFIE12_MASK                            (0x00001000U)

#define CANFD_TXBCIE_CFIE13_SHIFT                           (13U)
#define CANFD_TXBCIE_CFIE13_MASK                            (0x00002000U)

#define CANFD_TXBCIE_CFIE14_SHIFT                           (14U)
#define CANFD_TXBCIE_CFIE14_MASK                            (0x00004000U)

#define CANFD_TXBCIE_CFIE15_SHIFT                           (15U)
#define CANFD_TXBCIE_CFIE15_MASK                            (0x00008000U)

#define CANFD_TXBCIE_CFIE16_SHIFT                           (16U)
#define CANFD_TXBCIE_CFIE16_MASK                            (0x00010000U)

#define CANFD_TXBCIE_CFIE17_SHIFT                           (17U)
#define CANFD_TXBCIE_CFIE17_MASK                            (0x00020000U)

#define CANFD_TXBCIE_CFIE18_SHIFT                           (18U)
#define CANFD_TXBCIE_CFIE18_MASK                            (0x00040000U)

#define CANFD_TXBCIE_CFIE19_SHIFT                           (19U)
#define CANFD_TXBCIE_CFIE19_MASK                            (0x00080000U)

#define CANFD_TXBCIE_CFIE20_SHIFT                           (20U)
#define CANFD_TXBCIE_CFIE20_MASK                            (0x00100000U)

#define CANFD_TXBCIE_CFIE21_SHIFT                           (21U)
#define CANFD_TXBCIE_CFIE21_MASK                            (0x00200000U)

#define CANFD_TXBCIE_CFIE22_SHIFT                           (22U)
#define CANFD_TXBCIE_CFIE22_MASK                            (0x00400000U)

#define CANFD_TXBCIE_CFIE23_SHIFT                           (23U)
#define CANFD_TXBCIE_CFIE23_MASK                            (0x00800000U)

#define CANFD_TXBCIE_CFIE24_SHIFT                           (24U)
#define CANFD_TXBCIE_CFIE24_MASK                            (0x01000000U)

#define CANFD_TXBCIE_CFIE25_SHIFT                           (25U)
#define CANFD_TXBCIE_CFIE25_MASK                            (0x02000000U)

#define CANFD_TXBCIE_CFIE26_SHIFT                           (26U)
#define CANFD_TXBCIE_CFIE26_MASK                            (0x04000000U)

#define CANFD_TXBCIE_CFIE27_SHIFT                           (27U)
#define CANFD_TXBCIE_CFIE27_MASK                            (0x08000000U)

#define CANFD_TXBCIE_CFIE28_SHIFT                           (28U)
#define CANFD_TXBCIE_CFIE28_MASK                            (0x10000000U)

#define CANFD_TXBCIE_CFIE29_SHIFT                           (29U)
#define CANFD_TXBCIE_CFIE29_MASK                            (0x20000000U)

#define CANFD_TXBCIE_CFIE30_SHIFT                           (30U)
#define CANFD_TXBCIE_CFIE30_MASK                            (0x40000000U)

#define CANFD_TXBCIE_CFIE31_SHIFT                           (31U)
#define CANFD_TXBCIE_CFIE31_MASK                            (0x80000000U)

#define CANFD_TXEFC_EFSA_SHIFT                              (2U)
#define CANFD_TXEFC_EFSA_MASK                               (0x0000fffcU)

#define CANFD_TXEFC_EFS_SHIFT                               (16U)
#define CANFD_TXEFC_EFS_MASK                                (0x003f0000U)

#define CANFD_TXEFC_EFWM_SHIFT                              (24U)
#define CANFD_TXEFC_EFWM_MASK                               (0x3f000000U)

#define CANFD_TXEFS_EFFL_SHIFT                              (0U)
#define CANFD_TXEFS_EFFL_MASK                               (0x0000003fU)

#define CANFD_TXEFS_EFGI_SHIFT                              (8U)
#define CANFD_TXEFS_EFGI_MASK                               (0x00001f00U)

#define CANFD_TXEFS_EFPI_SHIFT                              (16U)
#define CANFD_TXEFS_EFPI_MASK                               (0x001f0000U)

#define CANFD_TXEFS_EFF_SHIFT                               (24U)
#define CANFD_TXEFS_EFF_MASK                                (0x01000000U)

#define CANFD_TXEFS_TEFL_SHIFT                              (25U)
#define CANFD_TXEFS_TEFL_MASK                               (0x02000000U)

#define CANFD_TXEFA_EFAI_SHIFT                              (0U)
#define CANFD_TXEFA_EFAI_MASK                               (0x0000001fU)

/* User defined ranges */
#define CANFD_DBTP_DSJW_MAX                                 (0xFU)
#define CANFD_DBTP_DTSEG2_MAX                               (0xFU)
#define CANFD_DBTP_DTSEG1_MAX                               (0x1FU)
#define CANFD_DBTP_DBRP_MAX                                 (0x1FU)

#define CANFD_NBTP_NSJW_MAX                                 (0x7FU)
#define CANFD_NBTP_NTSEG2_MAX                               (0x7FU)
#define CANFD_NBTP_NTSEG1_MAX                               (0xFFU)
#define CANFD_NBTP_NBRP_MAX                                 (0x1FFU)

#define CANFD_RWD_WDC_MAX                                   (0xFFU)

#define CANFD_TDCR_TDCF_MAX                                 (0x7FU)
#define CANFD_TDCR_TDCO_MAX                                 (0x7FU)

#define CANFD_XIDAM_EIDM_MAX                                (0x1FFFFFFFU)

#define CANFD_TSCC_TCP_MAX                                  (0xFU)

#define CANFD_TOCC_TOP_MAX                                  (0xFFFFU)

#define CANFD_ERM_CTRL_ECC_EN_SHIFT                         (0U)
#define CANFD_ERM_CTRL_ECC_EN_MASK                          (0x00000001U)

#define CANFD_ERM_CTRL_BEC_INT_EN_SHIFT                     (1U)
#define CANFD_ERM_CTRL_BEC_INT_EN_MASK                      (0x00000002U)

#define CANFD_ERM_CTRL_BEU_INT_EN_SHIFT                     (2U)
#define CANFD_ERM_CTRL_BEU_INT_EN_MASK                      (0x00000004U)

#define CANFD_ERM_CTRL_WAKE_INT_EN_SHIFT                    (3U)
#define CANFD_ERM_CTRL_WAKE_INT_EN_MASK                     (0x00000008U)

#define CANFD_ERM_STS_BEC_FLAG_SHIFT                        (0U)
#define CANFD_ERM_STS_BEC_FLAG_MASK                         (0x00000001U)

#define CANFD_ERM_STS_BEU_FLAG_SHIFT                        (1U)
#define CANFD_ERM_STS_BEU_FLAG_MASK                         (0x00000002U)

#define CANFD_ERM_STS_CANFD_WAKEUP_CLEAR_SHIFT              (2U)
#define CANFD_ERM_STS_CANFD_WAKEUP_CLEAR_MASK               (0x00000004U)

#define CANFD_ERM_ECC_ADDR_LOG_ERR_ADDR_SHIFT               (0U)
#define CANFD_ERM_ECC_ADDR_LOG_ERR_ADDR_MASK                (0x000003FFU)

#define CANFD_ERM_ECC_DATA_LOG_ERR_DATA_SHIFT               (0U)
#define CANFD_ERM_ECC_DATA_LOG_ERR_DATA_MASK                (0xFFFFFFFFU)

#define CANFD_ERM_RAM_INIT_RAM_INIT_EN_SHIFT                (0U)
#define CANFD_ERM_RAM_INIT_RAM_INIT_EN_MASK                 (0x00000001U)

#define CANFD_ERM_RAM_INIT_RAM_INIT_DONE_SHIFT              (1U)
#define CANFD_ERM_RAM_INIT_RAM_INIT_DONE_MASK               (0x00000002U)

#define CANFD_ERM_EXTC_CTRL_ETCE_SHIFT                      (31U)
#define CANFD_ERM_EXTC_CTRL_ETCE_MASK                       (0x80000000U)

#define CANFD_ERM_EXTC_CTRL_ETCP_SHIFT                      (0U)
#define CANFD_ERM_EXTC_CTRL_ETCP_MASK                       (0x000003FFU)

#define CANFD_ERM_EXTC_VAL_ETSC_SHIFT                       (0U)
#define CANFD_ERM_EXTC_VAL_ETSC_MASK                        (0x0000FFFFU)

#ifdef __cplusplus
}
#endif

#endif /* HW_CANFDSS_H_ */

