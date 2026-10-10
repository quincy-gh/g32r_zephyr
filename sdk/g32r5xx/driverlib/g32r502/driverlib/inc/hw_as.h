//###########################################################################
//
// FILE:    hw_as.h
//
// TITLE:   Definitions for the AS registers.
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

#ifndef HW_AS_H
#define HW_AS_H

//*************************************************************************************************
//
// The following are defines for the AS register offsets
//
//*************************************************************************************************
#define AS_O_CONFIGLOCK         0xBC        // Lock Register for all the config registers.
#define AS_O_TSNSCTL            0xC0        // Temperature Sensor Control Register
#define AS_O_ANAREFCTL          0xD0        // Analog Reference Control Register
#define AS_O_VMONCTL            0xE0        // Voltage Monitor Control Register
#define AS_O_CMPHPMXSEL         0x104       // Bits to select sources on CompHP inputs. 
                                            // Refer to Pinmux diagram for details.
#define AS_O_CMPLPMXSEL         0x108       // Bits to select sources on CompLP inputs. 
                                            // Refer to Pinmux diagram for details.
#define AS_O_CMPHNMXSEL         0x10C       // Bits to select sources on CompHN inputs. 
                                            // Refer to Pinmux diagram for details.
#define AS_O_CMPLNMXSEL         0x10E       // Bits to select sources on CompLN inputs. 
                                            // Refer to Pinmux diagram for details.
#define AS_O_ADCDACLOOPBACK     0x110       // Enable loopback from DAC to ADCs
#define AS_O_LOCK               0x11C       // Lock Register

#define AS_O_AGPIOCTRLA         0x214       // AGPIO Control Register
#define AS_O_AGPIOCTRLH         0x230       // AGPIO Control Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CONFIGLOCK register
//
//*************************************************************************************************
#define AS_CONFIGLOCK_AGPIOCTRL   0x8U   // Locks all AGPIOCTRL Register

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
#define AS_ANAREFCTL_ANAREFASEL_S    0U
#define AS_ANAREFCTL_ANAREFASEL_M    0x3U     // Analog Reference A mode select.
#define AS_ANAREFCTL_ANAREFCSEL_S    2U
#define AS_ANAREFCTL_ANAREFCSEL_M    0x4U     // Analog reference C mode select.
#define AS_ANAREFCTL_ANAREFA2P5SEL_S 8U
#define AS_ANAREFCTL_ANAREFA2P5SEL_M 0x300U   // Analog reference A 2.5V select.
#define AS_ANAREFCTL_ANAREFC2P5SEL   0x400U   // Analog reference C 2.5V select.

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

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPHNMXSEL register
//
//*************************************************************************************************
#define AS_CMPHNMXSEL_CMP1HNMXSEL   0x1U    // CMP1HNMXSEL bits.
#define AS_CMPHNMXSEL_CMP2HNMXSEL   0x2U    // CMP2HNMXSEL bits.
#define AS_CMPHNMXSEL_CMP3HNMXSEL   0x4U    // CMP3HNMXSEL bits.
#define AS_CMPHNMXSEL_CMP4HNMXSEL   0x8U    // CMP4HNMXSEL bits.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPLNMXSEL register
//
//*************************************************************************************************
#define AS_CMPLNMXSEL_CMP1LNMXSEL   0x1U    // CMP1LNMXSEL bits
#define AS_CMPLNMXSEL_CMP2LNMXSEL   0x2U    // CMP2LNMXSEL bits
#define AS_CMPLNMXSEL_CMP3LNMXSEL   0x4U    // CMP3LNMXSEL bits
#define AS_CMPLNMXSEL_CMP4LNMXSEL   0x8U    // CMP4LNMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the LOOPBACK register
//
//*************************************************************************************************
#define AS_ADCDACLOOPBACK_ENLB2ADCA        0x1U    // Loopback CMPDACA output to ADCA
#define AS_ADCDACLOOPBACK_ENLB2ADCC        0x4U    // Loopback CMPDACA output to ADCC
#define AS_ADCDACLOOPBACK_KEY              0xA5A50000U// Write Key

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

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOCTRLA register
//
//*************************************************************************************************
#define AS_AGPIOCTRLA_GPIO12   0x1000U       // AGPIOCTRL for GPIO12
#define AS_AGPIOCTRLA_GPIO13   0x2000U       // AGPIOCTRL for GPIO13
#define AS_AGPIOCTRLA_GPIO20   0x100000U     // AGPIOCTRL for GPIO20
#define AS_AGPIOCTRLA_GPIO21   0x200000U     // AGPIOCTRL for GPIO21
#define AS_AGPIOCTRLA_GPIO28   0x10000000U   // AGPIOCTRL for GPIO28

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOCTRLH register
//
//*************************************************************************************************
#define AS_AGPIOCTRLH_GPIO224   0x1U       // AGPIOCTRL for GPIO224
#define AS_AGPIOCTRLH_GPIO226   0x4U       // AGPIOCTRL for GPIO226
#define AS_AGPIOCTRLH_GPIO227   0x8U       // AGPIOCTRL for GPIO227
#define AS_AGPIOCTRLH_GPIO228   0x10U      // AGPIOCTRL for GPIO228
#define AS_AGPIOCTRLH_GPIO230   0x40U      // AGPIOCTRL for GPIO230
#define AS_AGPIOCTRLH_GPIO242   0x40000U   // AGPIOCTRL for GPIO242

#endif
