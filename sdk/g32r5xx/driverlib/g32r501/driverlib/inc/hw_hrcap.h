//###########################################################################
//
// FILE:    hw_hrcap.h
//
// TITLE:   Definitions for the HRCAP registers.
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
// 1. Partial comments, macro definitions
// 2. Deleted some register macro definitions and bit field macro definitions
//
//###########################################################################

#ifndef HW_HRCAP_H
#define HW_HRCAP_H

//*************************************************************************************************
//
// The following are defines for the HRCAP register offsets
//
//*************************************************************************************************
#define HRCAP_O_HRCTL         (0x0*2U)    // High-Res Control Register
#define HRCAP_O_HRINTEN       (0x4*2U)    // High-Res Calibration Interrupt Enable Register
#define HRCAP_O_HRFLG         (0x6*2U)    // High-Res Calibration Interrupt Flag Register
#define HRCAP_O_HRCLR         (0x8*2U)    // High-Res Calibration Interrupt Clear Register
#define HRCAP_O_HRFRC         (0xA*2U)    // High-Res Calibration Interrupt Force Register
#define HRCAP_O_HRCALPRD      (0xC*2U)    // High-Res Calibration Period Register
#define HRCAP_O_HRSYSCLKCTR   (0xE*2U)    // High-Res Calibration SYSCLK Counter Register
#define HRCAP_O_HRSYSCLKCAP   (0x10*2U)   // High-Res Calibration SYSCLK Capture Register
#define HRCAP_O_HRCLKCTR      (0x12*2U)   // High-Res Calibration HRCLK Counter Register
#define HRCAP_O_HRCLKCAP      (0x14*2U)   // High-Res Calibration HRCLK Capture Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRCTL register
//
//*************************************************************************************************
#define HRCAP_HRCTL_HRE          0x1U    // High Resolution Enable
#define HRCAP_HRCTL_HRCLKE       0x2U    // High Resolution Clock Enable
#define HRCAP_HRCTL_PRDSEL       0x4U    // Calibration Period Match
#define HRCAP_HRCTL_CALIBSTART   0x8U    // Calibration start
#define HRCAP_HRCTL_CALIBSTS     0x10U   // Calibration status
#define HRCAP_HRCTL_CALIBCONT    0x20U   // Continuous mode Calibration Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRINTEN register
//
//*************************************************************************************************
#define HRCAP_HRINTEN_CALIBDONE      0x2U   // Calibration doe interrupt enable
#define HRCAP_HRINTEN_CALPRDCHKSTS   0x4U   // Calibration period check status enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRFLG register
//
//*************************************************************************************************
#define HRCAP_HRFLG_CALIBINT       0x1U   // Global calibration Interrupt Status Flag
#define HRCAP_HRFLG_CALIBDONE      0x2U   // Calibration Done Interrupt Flag Bit
#define HRCAP_HRFLG_CALPRDCHKSTS   0x4U   // Calibration period check status Flag Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRCLR register
//
//*************************************************************************************************
#define HRCAP_HRCLR_CALIBINT       0x1U   // Clear Global calibration Interrupt Flag
#define HRCAP_HRCLR_CALIBDONE      0x2U   // Clear Calibration Done Interrupt Flag Bit
#define HRCAP_HRCLR_CALPRDCHKSTS   0x4U   // Clear Calibration period check status Flag Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRFRC register
//
//*************************************************************************************************
#define HRCAP_HRFRC_CALIBDONE      0x2U   // Force Calibration Done Interrupt Flag Bit
#define HRCAP_HRFRC_CALPRDCHKSTS   0x4U   // Force Calibration period check status Flag Bit



#endif
