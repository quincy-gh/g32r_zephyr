//###########################################################################
//
// FILE:    hw_COMP.h
//
// TITLE:   Definitions for the COMP registers.
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

#ifndef HW_COMP_H
#define HW_COMP_H

//*************************************************************************************************
//
// The following are defines for the COMP register offsets
//
//*************************************************************************************************
#define COMP_O_COMPCTL           (0x0*2U)    // COMP Comparator Control Register
#define COMP_O_COMPHYSCTL        (0x1*2U)    // COMP Comparator Hysteresis Control Register
#define COMP_O_COMPSTS           (0x2*2U)    // COMP Comparator Status Register
#define COMP_O_COMPSTSCLR        (0x3*2U)    // COMP Comparator Status Clear Register
#define COMP_O_COMPDACCTL        (0x4*2U)    // COMP DAC Control Register
#define COMP_O_DACHVALS          (0x6*2U)    // COMP High DAC Value Shadow Register
#define COMP_O_DACHVALA          (0x7*2U)    // COMP High DAC Value Active Register
#define COMP_O_RAMPMAXREFA       (0x8*2U)    // COMP Ramp Max Reference Active Register
#define COMP_O_RAMPMAXREFS       (0xA*2U)    // COMP Ramp Max Reference Shadow Register
#define COMP_O_RAMPDECVALA       (0xC*2U)    // COMP Ramp Decrement Value Active Register
#define COMP_O_RAMPDECVALS       (0xE*2U)    // COMP Ramp Decrement Value Shadow Register
#define COMP_O_RAMPSTS           (0x10*2U)   // COMP Ramp Status Register
#define COMP_O_DACLVALS          (0x12*2U)   // COMP Low DAC Value Shadow Register
#define COMP_O_DACLVALA          (0x13*2U)   // COMP Low DAC Value Active Register
#define COMP_O_RAMPDLYA          (0x14*2U)   // COMP Ramp Delay Active Register
#define COMP_O_RAMPDLYS          (0x15*2U)   // COMP Ramp Delay Shadow Register
#define COMP_O_CTRIPLFILCTL      (0x16*2U)   // CTRIPL Filter Control Register
#define COMP_O_CTRIPLFILCLKCTL   (0x17*2U)   // CTRIPL Filter Clock Control Register
#define COMP_O_CTRIPHFILCTL      (0x18*2U)   // CTRIPH Filter Control Register
#define COMP_O_CTRIPHFILCLKCTL   (0x19*2U)   // CTRIPH Filter Clock Control Register
#define COMP_O_COMPLOCK          (0x1A*2U)   // COMP Lock Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPCTRL register
//
//*************************************************************************************************
#define COMP_COMPCTL_COMPHSOURCE     0x1U      // High Comparator Source Select
#define COMP_COMPCTL_COMPHINV        0x2U      // High Comparator Invert Select
#define COMP_COMPCTL_CTRIPHSEL_S     2U
#define COMP_COMPCTL_CTRIPHSEL_M     0xCU      // High Comparator Trip Select
#define COMP_COMPCTL_CTRIPOUTHSEL_S  4U
#define COMP_COMPCTL_CTRIPOUTHSEL_M  0x30U     // High Comparator Trip Output Select
#define COMP_COMPCTL_ASYNCHEN        0x40U     // High Comparator Asynchronous Path Enable
#define COMP_COMPCTL_COMPLSOURCE     0x100U    // Low Comparator Source Select
#define COMP_COMPCTL_COMPLINV        0x200U    // Low Comparator Invert Select
#define COMP_COMPCTL_CTRIPLSEL_S     10U
#define COMP_COMPCTL_CTRIPLSEL_M     0xC00U    // Low Comparator Trip Select
#define COMP_COMPCTL_CTRIPOUTLSEL_S  12U
#define COMP_COMPCTL_CTRIPOUTLSEL_M  0x3000U   // Low Comparator Trip Output Select
#define COMP_COMPCTL_ASYNCLEN        0x4000U   // Low Comparator Asynchronous Path Enable
#define COMP_COMPCTL_COMPDACE        0x8000U   // Comparator/DAC Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPHYSCTL register
//
//*************************************************************************************************
#define COMP_COMPHYSCTL_COMPHYS_S   0U
#define COMP_COMPHYSCTL_COMPHYS_M   0xFU   // Comparator Hysteresis Trim

//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPSTS register
//
//*************************************************************************************************
#define COMP_COMPSTS_COMPHSTS     0x1U     // High Comparator Status
#define COMP_COMPSTS_COMPHLATCH   0x2U     // High Comparator Latched Status
#define COMP_COMPSTS_COMPLSTS     0x100U   // Low Comparator Status
#define COMP_COMPSTS_COMPLLATCH   0x200U   // Low Comparator Latched Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPSTSCLR register
//
//*************************************************************************************************
#define COMP_COMPSTSCLR_HLATCHCLR    0x2U     // High Comparator Latched Status Clear
#define COMP_COMPSTSCLR_HSYNCCLREN   0x4U     // High Comparator EPWMSYNCPER Clear Enable
#define COMP_COMPSTSCLR_LLATCHCLR    0x200U   // Low Comparator Latched Status Clear
#define COMP_COMPSTSCLR_LSYNCCLREN   0x400U   // Low Comparator EPWMSYNCPER Clear Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPDACCTL register
//
//*************************************************************************************************
#define COMP_COMPDACCTL_DACSOURCE       0x1U      // DAC Source Control
#define COMP_COMPDACCTL_RAMPSOURCE_S    1U
#define COMP_COMPDACCTL_RAMPSOURCE_M    0x1EU     // Ramp Generator Source Control
#define COMP_COMPDACCTL_RAMPLOADSEL     0x40U     // Ramp Load Select
#define COMP_COMPDACCTL_SWLOADSEL       0x80U     // Software Load Select
#define COMP_COMPDACCTL_BLANKSOURCE_S   8U
#define COMP_COMPDACCTL_BLANKSOURCE_M   0xF00U    // EPWMBLANK Source Select
#define COMP_COMPDACCTL_BLANKEN         0x1000U   // EPWMBLANK Enable
#define COMP_COMPDACCTL_FREESOFT_S      14U
#define COMP_COMPDACCTL_FREESOFT_M      0xC000U   // Free/Soft Emulation Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DACHVALS register
//
//*************************************************************************************************
#define COMP_DACHVALS_DACVAL_S   0U
#define COMP_DACHVALS_DACVAL_M   0xFFFU   // DAC Value Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the DACHVALA register
//
//*************************************************************************************************
#define COMP_DACHVALA_DACVAL_S   0U
#define COMP_DACHVALA_DACVAL_M   0xFFFU   // DAC Value Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the DACLVALS register
//
//*************************************************************************************************
#define COMP_DACLVALS_DACVAL_S   0U
#define COMP_DACLVALS_DACVAL_M   0xFFFU   // DAC Value Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the DACLVALA register
//
//*************************************************************************************************
#define COMP_DACLVALA_DACVAL_S   0U
#define COMP_DACLVALA_DACVAL_M   0xFFFU   // DAC Value Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the RAMPDLYA register
//
//*************************************************************************************************
#define COMP_RAMPDLYA_DELAY_S   0U
#define COMP_RAMPDLYA_DELAY_M   0x1FFFU   // Ramp Delay Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the RAMPDLYS register
//
//*************************************************************************************************
#define COMP_RAMPDLYS_DELAY_S   0U
#define COMP_RAMPDLYS_DELAY_M   0x1FFFU   // Ramp Delay Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the CTRIPLFILCTL register
//
//*************************************************************************************************
#define COMP_CTRIPLFILCTL_SAMPWIN_S   4U
#define COMP_CTRIPLFILCTL_SAMPWIN_M   0x1F0U    // Sample Window
#define COMP_CTRIPLFILCTL_THRESH_S    9U
#define COMP_CTRIPLFILCTL_THRESH_M    0x3E00U   // Majority Voting Threshold
#define COMP_CTRIPLFILCTL_FILINIT     0x8000U   // Filter Initialization Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CTRIPLFILCLKCTL register
//
//*************************************************************************************************
#define COMP_CTRIPLFILCLKCTL_CLKPRESCALE_S   0U
#define COMP_CTRIPLFILCLKCTL_CLKPRESCALE_M   0x3FFU   // Sample Clock Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the CTRIPHFILCTL register
//
//*************************************************************************************************
#define COMP_CTRIPHFILCTL_SAMPWIN_S   4U
#define COMP_CTRIPHFILCTL_SAMPWIN_M   0x1F0U    // Sample Window
#define COMP_CTRIPHFILCTL_THRESH_S    9U
#define COMP_CTRIPHFILCTL_THRESH_M    0x3E00U   // Majority Voting Threshold
#define COMP_CTRIPHFILCTL_FILINIT     0x8000U   // Filter Initialization Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CTRIPHFILCLKCTL register
//
//*************************************************************************************************
#define COMP_CTRIPHFILCLKCTL_CLKPRESCALE_S   0U
#define COMP_CTRIPHFILCLKCTL_CLKPRESCALE_M   0x3FFU   // Sample Clock Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPLOCK register
//
//*************************************************************************************************
#define COMP_COMPLOCK_COMPCTL      0x1U   // COMPCTL Lock
#define COMP_COMPLOCK_COMPHYSCTL   0x2U   // COMPHYSCTL Lock
#define COMP_COMPLOCK_DACCTL       0x4U   // DACCTL Lock
#define COMP_COMPLOCK_CTRIP        0x8U   // CTRIP Lock



#endif
