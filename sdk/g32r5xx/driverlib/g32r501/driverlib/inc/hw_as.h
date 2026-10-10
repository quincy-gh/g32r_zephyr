//###########################################################################
//
// FILE:    hw_as.h
//
// TITLE:   Definitions for the AS registers.
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

#ifndef HW_AS_H
#define HW_AS_H

//*************************************************************************************************
//
// The following are defines for the AS register offsets
//
//*************************************************************************************************
#define AS_O_ANAREFPP      (0x1E*2U)   // ADC Analog Reference Peripheral Properties register. The
                                       // value of this register is populated during boot rom.
#define AS_O_TSNSCTL       (0x60*2U)   // Temperature Sensor Control Register
#define AS_O_ANAREFCTL     (0x68*2U)   // Analog Reference Control Register
#define AS_O_VMONCTL       (0x70*2U)   // Voltage Monitor Control Register
#define AS_O_CMPHPMXSEL    (0x82*2U)   // Bits to select one of the many sources on CopmHP inputs.
                                       // Refer to Pimux diagram for details.
#define AS_O_CMPLPMXSEL    (0x84*2U)   // Bits to select one of the many sources on CopmLP inputs.
                                       // Refer to Pimux diagram for details.
#define AS_O_CMPHNMXSEL    (0x86*2U)   // Bits to select one of the many sources on CopmHN inputs.
                                       // Refer to Pimux diagram for details.
#define AS_O_CMPLNMXSEL    (0x87*2U)   // Bits to select one of the many sources on CopmLN inputs.
                                       // Refer to Pimux diagram for details.
#define AS_O_ADCDACLOOPBACK (0x88*2U)  // Enabble loopback from DAC to ADCs
#define AS_O_LOCK          (0x8E*2U)   // Lock Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the AREF register
//
//*************************************************************************************************
#define AS_ANAREFPP_ANAREFBDIS   0x1U   // ANAREFB Disable
#define AS_ANAREFPP_ANAREFCDIS   0x2U   // ANAREFC Disable

//*************************************************************************************************
//
// The following are defines for the bit fields in the TSCTRL register
//
//*************************************************************************************************
#define AS_TSNSCTL_ENABLE   0x1U   // Temperature Sensor Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the AREFCTRL register
//
//*************************************************************************************************
#define AS_ANAREFCTL_ANAREFASEL      0x1U     // Analog Reference A mode select.
#define AS_ANAREFCTL_ANAREFBSEL      0x2U     // Analog Reference B mode select.
#define AS_ANAREFCTL_ANAREFCSEL      0x4U     // Analog reference C mode select.
#define AS_ANAREFCTL_ANAREFA2P5SEL   0x100U   // Analog referenc A 2.5V source select. In internal reference mode.
#define AS_ANAREFCTL_ANAREFB2P5SEL   0x200U   // Analog referenc B 2.5V source select. In internal reference mode.
#define AS_ANAREFCTL_ANAREFC2P5SEL   0x400U   // Analog referenc C 2.5V source select. In internal reference mode.

//*************************************************************************************************
//
// The following are defines for the bit fields in the VMCTRL register
//
//*************************************************************************************************
#define AS_VMONCTL_BORLDIS   0x100U   // BORL disable on VDDIO

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPHPMXSEL register
//
//*************************************************************************************************
#define AS_CMPHPMXSEL_CMP1HPMXSEL_S   0U
#define AS_CMPHPMXSEL_CMP1HPMXSEL_M   0x7U        // CMP1HPMXSEL bits.
#define AS_CMPHPMXSEL_CMP2HPMXSEL_S   3U
#define AS_CMPHPMXSEL_CMP2HPMXSEL_M   0x38U       // CMP2HPMXSEL bits.
#define AS_CMPHPMXSEL_CMP3HPMXSEL_S   6U
#define AS_CMPHPMXSEL_CMP3HPMXSEL_M   0x1C0U      // CMP3HPMXSEL bits.
#define AS_CMPHPMXSEL_CMP4HPMXSEL_S   9U
#define AS_CMPHPMXSEL_CMP4HPMXSEL_M   0xE00U      // CMP4HPMXSEL bits.
#define AS_CMPHPMXSEL_CMP5HPMXSEL_S   12U
#define AS_CMPHPMXSEL_CMP5HPMXSEL_M   0x7000U     // CMP5HPMXSEL bits.
#define AS_CMPHPMXSEL_CMP6HPMXSEL_S   16U
#define AS_CMPHPMXSEL_CMP6HPMXSEL_M   0x70000U    // CMP-5HPMXSEL bits.
#define AS_CMPHPMXSEL_CMP7HPMXSEL_S   19U
#define AS_CMPHPMXSEL_CMP7HPMXSEL_M   0x380000U   // CMP-4HPMXSEL bits.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPLPMXSEL register
//
//*************************************************************************************************
#define AS_CMPLPMXSEL_CMP1LPMXSEL_S   0U
#define AS_CMPLPMXSEL_CMP1LPMXSEL_M   0x7U        // CMP1LPMXSEL bits.
#define AS_CMPLPMXSEL_CMP2LPMXSEL_S   3U
#define AS_CMPLPMXSEL_CMP2LPMXSEL_M   0x38U       // CMP2LPMXSEL bits,
#define AS_CMPLPMXSEL_CMP3LPMXSEL_S   6U
#define AS_CMPLPMXSEL_CMP3LPMXSEL_M   0x1C0U      // CMP3LPMXSEL bits.
#define AS_CMPLPMXSEL_CMP4LPMXSEL_S   9U
#define AS_CMPLPMXSEL_CMP4LPMXSEL_M   0xE00U      // CMP4LPMXSEL bits.
#define AS_CMPLPMXSEL_CMP5LPMXSEL_S   12U
#define AS_CMPLPMXSEL_CMP5LPMXSEL_M   0x7000U     // CMP5LPMXSEL bits.
#define AS_CMPLPMXSEL_CMP6LPMXSEL_S   16U
#define AS_CMPLPMXSEL_CMP6LPMXSEL_M   0x70000U    // CMP6LPMXSEL bits.
#define AS_CMPLPMXSEL_CMP7LPMXSEL_S   19U
#define AS_CMPLPMXSEL_CMP7LPMXSEL_M   0x380000U   // CMP7LPMXSEL bits.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPHNMXSEL register
//
//*************************************************************************************************
#define AS_CMPHNMXSEL_CMP1HNMXSEL   0x1U    // CMP1HNMXSEL bits.
#define AS_CMPHNMXSEL_CMP2HNMXSEL   0x2U    // CMP2HNMXSEL bits.
#define AS_CMPHNMXSEL_CMP3HNMXSEL   0x4U    // CMP3HNMXSEL bits.
#define AS_CMPHNMXSEL_CMP4HNMXSEL   0x8U    // CMP4HNMXSEL bits.
#define AS_CMPHNMXSEL_CMP5HNMXSEL   0x10U   // CMP5HNMXSEL bits.
#define AS_CMPHNMXSEL_CMP6HNMXSEL   0x20U   // CMP6HNMXSEL bits.
#define AS_CMPHNMXSEL_CMP7HNMXSEL   0x40U   // CMP7HNMXSEL bits.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPLNMXSEL register
//
//*************************************************************************************************
#define AS_CMPLNMXSEL_CMP1LNMXSEL   0x1U    // CMP1LNMXSEL bits
#define AS_CMPLNMXSEL_CMP2LNMXSEL   0x2U    // CMP2LNMXSEL bits
#define AS_CMPLNMXSEL_CMP3LNMXSEL   0x4U    // CMP3LNMXSEL bits
#define AS_CMPLNMXSEL_CMP4LNMXSEL   0x8U    // CMP4LNMXSEL bits
#define AS_CMPLNMXSEL_CMP5LNMXSEL   0x10U   // CMP5LNMXSEL bits
#define AS_CMPLNMXSEL_CMP6LNMXSEL   0x20U   // CMP6LNMXSEL bits
#define AS_CMPLNMXSEL_CMP7LNMXSEL   0x40U   // CMP7LNMXSEL bits.

//*************************************************************************************************
//
// The following are defines for the bit fields in the LOOPBACK register
//
//*************************************************************************************************
#define AS_ADCDACLOOPBACK_ENLB2ADCA        0x1U    // Loopback CMPDACA output to ADCA
#define AS_ADCDACLOOPBACK_ENLB2ADCB        0x2U    // Loopback CMPDACA output to ADCB
#define AS_ADCDACLOOPBACK_ENLB2ADCC        0x4U    // Loopback CMPDACA output to ADCC
#define AS_ADCDACLOOPBACK_KEY              0x10000U// Write Key

//*************************************************************************************************
//
// The following are defines for the bit fields in the LOCK register
//
//*************************************************************************************************
#define AS_LOCK_TSNSCTL        0x1U      // TSNSCTL Register Lock
#define AS_LOCK_ANAREFCTL      0x2U      // ANAREFCTL Register Lock
#define AS_LOCK_VMONCTL        0x4U      // VMONCTL Register Lock
#define AS_LOCK_CMPHPMXSEL     0x20U     // CMPHPMXSEL Register Lock
#define AS_LOCK_CMPLPMXSEL     0x40U     // CMPLPMXSEL Register Lock
#define AS_LOCK_CMPHNMXSEL     0x80U     // CMPHNMXSEL Register Lock
#define AS_LOCK_CMPLNMXSEL     0x100U    // CMPLNMXSEL Register Lock



#endif
