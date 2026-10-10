//###########################################################################
//
// FILE:    hw_qep.h
//
// TITLE:   Definitions for the QEP registers.
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

#ifndef HW_QEP_H
#define HW_QEP_H

//*************************************************************************************************
//
// The following are defines for the QEP register offsets
//
//*************************************************************************************************
#define QEP_O_QPOSCNT        (0x0*2U)    // Position Counter
#define QEP_O_QPOSINIT       (0x2*2U)    // Position Counter Init
#define QEP_O_QPOSMAX        (0x4*2U)    // Maximum Position Count
#define QEP_O_QPOSCMP        (0x6*2U)    // Position Compare
#define QEP_O_QPOSILAT        (0x8*2U)    // Index Position Latch
#define QEP_O_QPOSSLAT       (0xA*2U)    // Strobe Position Latch
#define QEP_O_QPOSLAT        (0xC*2U)    // Position Latch
#define QEP_O_QUTMR          (0xE*2U)    // QEP Unit Timer
#define QEP_O_QUPRD          (0x10*2U)   // QEP Unit Period
#define QEP_O_QWDTMR         (0x12*2U)   // QEP Watchdog Timer
#define QEP_O_QWDPRD         (0x13*2U)   // QEP Watchdog Period
#define QEP_O_QDECCTL        (0x14*2U)   // Quadrature Decoder Control
#define QEP_O_QEPCTL         (0x15*2U)   // QEP Control
#define QEP_O_QCAPCTL        (0x16*2U)   // Qaudrature Capture Control
#define QEP_O_QPOSCTL        (0x17*2U)   // Position Compare Control
#define QEP_O_QEINT          (0x18*2U)   // QEP Interrupt Control
#define QEP_O_QFLG           (0x19*2U)   // QEP Interrupt Flag
#define QEP_O_QCLR           (0x1A*2U)   // QEP Interrupt Clear
#define QEP_O_QFRC           (0x1B*2U)   // QEP Interrupt Force
#define QEP_O_QEPSTS         (0x1C*2U)   // QEP Status
#define QEP_O_QCTMR          (0x1D*2U)   // QEP Capture Timer
#define QEP_O_QCPRD          (0x1E*2U)   // QEP Capture Period
#define QEP_O_QCTMRLAT       (0x1F*2U)   // QEP Capture Latch
#define QEP_O_QCPRDLAT       (0x20*2U)   // QEP Capture Period Latch
#define QEP_O_REV            (0x30*2U)   // QEP Revision Number
#define QEP_O_QEPSTROBESEL   (0x32*2U)   // QEP Strobe select register
#define QEP_O_QMACTRL        (0x34*2U)   // QMA Control register


//*************************************************************************************************
//
// The following are defines for the bit fields in the QDECCTL register
//
//*************************************************************************************************
#define QEP_QDECCTL_QSP         0x20U     // QEPS input polarity
#define QEP_QDECCTL_QIP         0x40U     // QEPI input polarity
#define QEP_QDECCTL_QBP         0x80U     // QEPB input polarity
#define QEP_QDECCTL_QAP         0x100U    // QEPA input polarity
#define QEP_QDECCTL_IGATE       0x200U    // Index pulse gating option
#define QEP_QDECCTL_SWAP        0x400U    // CLK/DIR Signal Source for Position Counter
#define QEP_QDECCTL_XCR         0x800U    // External Clock Rate
#define QEP_QDECCTL_SPSEL       0x1000U   // Sync output pin selection
#define QEP_QDECCTL_SOEN        0x2000U   // Sync output-enable
#define QEP_QDECCTL_QSRC_S      14U
#define QEP_QDECCTL_QSRC_M      0xC000U   // Position-counter source selection

//*************************************************************************************************
//
// The following are defines for the bit fields in the QEPCTL register
//
//*************************************************************************************************
#define QEP_QEPCTL_WDE          0x1U      // QEP watchdog enable
#define QEP_QEPCTL_UTE          0x2U      // QEP unit timer enable
#define QEP_QEPCTL_QCLM         0x4U      // QEP capture latch mode
#define QEP_QEPCTL_QPEN         0x8U      // Quadrature postotion counter enable
#define QEP_QEPCTL_IEL_S        4U
#define QEP_QEPCTL_IEL_M        0x30U     // Index event latch
#define QEP_QEPCTL_SEL          0x40U     // Strobe event latch
#define QEP_QEPCTL_SWI          0x80U     // Software init position counter
#define QEP_QEPCTL_IEI_S        8U
#define QEP_QEPCTL_IEI_M        0x300U    // Index event init of position counter
#define QEP_QEPCTL_SEI_S        10U
#define QEP_QEPCTL_SEI_M        0xC00U    // Strobe event init
#define QEP_QEPCTL_PCRM_S       12U
#define QEP_QEPCTL_PCRM_M       0x3000U   // Postion counter reset
#define QEP_QEPCTL_FREE_SOFT_S  14U
#define QEP_QEPCTL_FREE_SOFT_M  0xC000U   // Emulation mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the QCAPCTL register
//
//*************************************************************************************************
#define QEP_QCAPCTL_UPPS_S      0U
#define QEP_QCAPCTL_UPPS_M      0xFU      // Unit position event prescaler
#define QEP_QCAPCTL_CCPS_S      4U
#define QEP_QCAPCTL_CCPS_M      0x70U     // QEP capture timer clock prescaler
#define QEP_QCAPCTL_CEN         0x8000U   // Enable QEP capture

//*************************************************************************************************
//
// The following are defines for the bit fields in the QPOSCTL register
//
//*************************************************************************************************
#define QEP_QPOSCTL_PCSPW_S     0U
#define QEP_QPOSCTL_PCSPW_M     0xFFFU    // Position compare sync pulse width
#define QEP_QPOSCTL_PCE         0x1000U   // Position compare enable/disable/disable
#define QEP_QPOSCTL_PCPOL       0x2000U   // Polarity of sync output
#define QEP_QPOSCTL_PCLOAD      0x4000U   // Position compare of shadow load
#define QEP_QPOSCTL_PCSHDW      0x8000U   // Select-position-compare sync output pulse width

//*************************************************************************************************
//
// The following are defines for the bit fields in the QEINT register
//
//*************************************************************************************************
#define QEP_QEINT_PCE           0x2U      // Position counter error interrupt enable
#define QEP_QEINT_QPE           0x4U      // Quadrature phase error interrupt enable
#define QEP_QEINT_QDC           0x8U      // Quadrature direction change interrupt enable
#define QEP_QEINT_WTO           0x10U     // Watchdog time out interrupt enable
#define QEP_QEINT_PCU           0x20U     // Position counter underflow interrupt enable
#define QEP_QEINT_PCO           0x40U     // Position counter overflow interrupt enable
#define QEP_QEINT_PCR           0x80U     // Position-compare ready interrupt enable
#define QEP_QEINT_PCM           0x100U    // Position-compare match interrupt enable
#define QEP_QEINT_SEL           0x200U    // Strobe event latch interrupt enable
#define QEP_QEINT_IEL           0x400U    // Index event latch interrupt enable
#define QEP_QEINT_UTO           0x800U    // Unit time out interrupt enable
#define QEP_QEINT_QMAE          0x1000U   // QMA error interrupt enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the QFLG register
//
//*************************************************************************************************
#define QEP_QFLG_INT         0x1U      // Global interrupt status flag
#define QEP_QFLG_PCE         0x2U      // Position counter error interrupt flag
#define QEP_QFLG_QPE         0x4U      // Quadrature phase error interrupt flag
#define QEP_QFLG_QDC         0x8U      // Quadrature direction change interrupt flag
#define QEP_QFLG_WTO         0x10U     // Watchdog time out interrupt flag
#define QEP_QFLG_PCU         0x20U     // Position counter underflow interrupt flag
#define QEP_QFLG_PCO         0x40U     // Position counter overflow interrupt flag
#define QEP_QFLG_PCR         0x80U     // Position-compare ready interrupt flag
#define QEP_QFLG_PCM         0x100U    // Position-compare match interrupt flag
#define QEP_QFLG_SEL         0x200U    // Strobe event latch interrupt flag
#define QEP_QFLG_IEL         0x400U    // Index event latch interrupt flag
#define QEP_QFLG_UTO         0x800U    // Unit time out interrupt flag
#define QEP_QFLG_QMAE        0x1000U   // QMA error interrupt flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the QCLR register
//
//*************************************************************************************************
#define QEP_QCLR_INT         0x1U      // Global interrupt status Clear flag
#define QEP_QCLR_PCE         0x2U      // Clear position counter error interrupt flag
#define QEP_QCLR_QPE         0x4U      // Clear quadrature phase error interrupt flag
#define QEP_QCLR_QDC         0x8U      // Clear quadrature direction change interrupt flag
#define QEP_QCLR_WTO         0x10U     // Clear watchdog timeout interrupt flag
#define QEP_QCLR_PCU         0x20U     // Clear position counter underflow interrupt flag
#define QEP_QCLR_PCO         0x40U     // Clear position counter overflow interrupt flag
#define QEP_QCLR_PCR         0x80U     // Clear position-compare ready interrupt flag
#define QEP_QCLR_PCM         0x100U    // Clear Position-compare match interrupt flag
#define QEP_QCLR_SEL         0x200U    // Clear strobe event latch interrupt flag
#define QEP_QCLR_IEL         0x400U    // Clear index event latch interrupt flag
#define QEP_QCLR_UTO         0x800U    // Clear unit time out interrupt flag
#define QEP_QCLR_QMAE        0x1000U   // Clear QMA error interrupt flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the QFRC register
//
//*************************************************************************************************
#define QEP_QFRC_PCE         0x2U      // Force position counter error interrupt
#define QEP_QFRC_QPE         0x4U      // Force quadrature phase error interrupt
#define QEP_QFRC_QDC         0x8U      // Force quadrature direction change interrupt
#define QEP_QFRC_WTO         0x10U     // Force watchdog time out interrupt
#define QEP_QFRC_PCU         0x20U     // Force position counter underflow interrupt
#define QEP_QFRC_PCO         0x40U     // Force position counter overflow interrupt
#define QEP_QFRC_PCR         0x80U     // Force position-compare ready interrupt
#define QEP_QFRC_PCM         0x100U    // Force position-compare match interrupt
#define QEP_QFRC_SEL         0x200U    // Force strobe event latch interrupt
#define QEP_QFRC_IEL         0x400U    // Force index event latch interrupt
#define QEP_QFRC_UTO         0x800U    // Force unit time out interrupt
#define QEP_QFRC_QMAE        0x1000U   // Force QMA error interrupt

//*************************************************************************************************
//
// The following are defines for the bit fields in the QEPSTS register
//
//*************************************************************************************************
#define QEP_QEPSTS_PCEF      0x1U      // Position counter error flag.
#define QEP_QEPSTS_FIMF      0x2U      // First index marker flag
#define QEP_QEPSTS_CDEF      0x4U      // Capture direction error flag
#define QEP_QEPSTS_COEF      0x8U      // Capture overflow error flag
#define QEP_QEPSTS_QDLF      0x10U     // QEP direction latch flag
#define QEP_QEPSTS_QDF       0x20U     // Quadrature direction flag
#define QEP_QEPSTS_FIDF      0x40U     // The first index marker
#define QEP_QEPSTS_UPEFLG    0x80U     // Unit position event flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the REV register
//
//*************************************************************************************************
#define QEP_REV_MAJOR_S      0U
#define QEP_REV_MAJOR_M      0x7U      // Major Revision Number
#define QEP_REV_MINOR_S      3U
#define QEP_REV_MINOR_M      0x38U     // Minor Revision Number

//*************************************************************************************************
//
// The following are defines for the bit fields in the QEPSTROBESEL register
//
//*************************************************************************************************
#define QEP_QEPSTROBESEL_SERSRCSEL_S   0U
#define QEP_QEPSTROBESEL_SERSRCSEL_M   0x3U   // QMA Mode Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the QMACTRL register
//
//*************************************************************************************************
#define QEP_QMACTRL_MODE_S   0U
#define QEP_QMACTRL_MODE_M   0x7U      // QMA Mode Select



#endif
