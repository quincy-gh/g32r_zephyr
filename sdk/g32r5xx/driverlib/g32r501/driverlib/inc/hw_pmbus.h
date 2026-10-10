//###########################################################################
//
// FILE:    hw_pmbus.h
//
// TITLE:   Definitions for the PMBUS registers.
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

#ifndef HW_PMBUS_H
#define HW_PMBUS_H

//*************************************************************************************************
//
// The following are defines for the PMBUS register offsets
//
//*************************************************************************************************
#define PMBUS_O_MCTRL                  0x0U    // PMBUS Master Mode Control Register offset
#define PMBUS_O_TXB                    0x4U    // PMBUS Transmit Buffer offset
#define PMBUS_O_RXB                    0x8U    // PMBUS Receive buffer offset
#define PMBUS_O_ACK                    0xCU    // PMBUS Acknowledge Register offset
#define PMBUS_O_STS                    0x10U   // PMBUS Status Register offset
#define PMBUS_O_IMASK                  0x14U   // PMBUS Interrupt Mask Register offset
#define PMBUS_O_SCTRL                  0x18U   // PMBUS Slave Mode Configuration Register offset
#define PMBUS_O_HSADDR                 0x1CU   // PMBUS Hold Slave Address Register offset
#define PMBUS_O_CTRL                   0x20U   // PMBUS Control Register offset
#define PMBUS_O_TIMCTRL                0x24U   // PMBUS Timing Control Register offset
#define PMBUS_O_CLKTIM                 0x28U   // PMBUS Clock Timing Register offset
#define PMBUS_O_STATIM                 0x2CU   // PMBUS Start Setup Time Register offset
#define PMBUS_O_BUSIDTIM               0x30U   // PMBUS Bus Idle Time Register offset
#define PMBUS_O_CLKLTOTIIM             0x34U   // PMBUS Clock Low Timeout Value Register offset
#define PMBUS_O_CLKHTOTIIM             0x38U   // PMBUS Clock High Timeout Value Register offset

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_MCTRL register
//
//*************************************************************************************************
#define PMBUS_MCTRL_RWCFG              0x1U        // Message read and write Configure
#define PMBUS_MCTRL_SADDR_S            1U
#define PMBUS_MCTRL_SADDR_M            0xFE        // Current message slave address
#define PMBUS_MCTRL_BYTENUM_S          8U
#define PMBUS_MCTRL_BYTENUM_M          0xFF00      // Number of bytes of data transferred
#define PMBUS_MCTRL_COMCEN             0x10000     // Use of command code on Master initiated messages Enable
#define PMBUS_MCTRL_BYTECFG            0x20000     // Use bytes for Command Code Configure
#define PMBUS_MCTRL_PECBYTEEN          0x40000     // PEC byte Enables
#define PMBUS_MCTRL_GCOMEN             0x80000     // Transmit of Group Command message Enable
#define PMBUS_MCTRL_TXPROMEN           0x100000    // Transmit Process Call message Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_ACK register
//
//*************************************************************************************************
#define PMBUS_ACK_ACK                  0x1U        // Acknowledge received data

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_STS register
//
//*************************************************************************************************
#define PMBUS_STS_RXBYTE_S             0U
#define PMBUS_STS_RXBYTE_M             0x7         // Receive byte Select
#define PMBUS_STS_READDATA             0x8         // Read data prior to bus activity
#define PMBUS_STS_ADITDATA             0x10        // Request additional data
#define PMBUS_STS_ENDFLG               0x20        // Current message End Flag
#define PMBUS_STS_RXDFLG               0x40        // Receive data Flag
#define PMBUS_STS_PECVALID             0x80        // Received PEC is valid
#define PMBUS_STS_CLKLTOFLG            0x100       // Clock low timeout Flag
#define PMBUS_STS_CLKHFLG              0x200       // Clock High Flag
#define PMBUS_STS_RDYRSADDR            0x400       // Ready read slave address
#define PMBUS_STS_RXRESFLG             0x800       // Received Repeated Star Flag
#define PMBUS_STS_BUSYFLG              0x1000      // Busy Flag
#define PMBUS_STS_AVAFLG               0x2000      // Available Flag
#define PMBUS_STS_LOSTCTRL             0x4000      // Master lost control of PMBus
#define PMBUS_STS_MASTERFLG            0x8000      // Master Mode Flag
#define PMBUS_STS_ALERTTRAN            0x10000     // Alert pin transitioned
#define PMBUS_STS_CTRLTRAN             0x20000     // Control pin transitioned
#define PMBUS_STS_ALERTOLL             0x40000     // Alert pin at logic level high
#define PMBUS_STS_CTRLOLL              0x80000     // Control pin at logic level high
#define PMBUS_STS_SDAOLL               0x100000    // Data pin at logic level high
#define PMBUS_STS_SCLOLL               0x200000    // Clock pin at logic level high

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_IMASK register
//
//*************************************************************************************************
#define PMBUS_IMASK_DISBUSIDLE         0x1U        // Disables Bus Idle generation interrupt
#define PMBUS_IMASK_DISCLKLTO          0x2U        // Disables Clock Low Timeout generation interrupt
#define PMBUS_IMASK_DISDRDY            0x4U        // Disables Data Ready generation interrupt
#define PMBUS_IMASK_DISDREQ            0x8U        // Disables Data Request generation interrupt
#define PMBUS_IMASK_DISSADDRRDY        0x10       // Disables Slave Address Ready generation interrupt
#define PMBUS_IMASK_DISEND             0x20       // Disables Message End generation interrupt
#define PMBUS_IMASK_DISALERT           0x40       // Disables Alert generation interrupt
#define PMBUS_IMASK_DISCTRL            0x80       // Disables Control generation interrupt
#define PMBUS_IMASK_DISLOSTARB         0x100      // Disables Lost Arbitration generation interrupt
#define PMBUS_IMASK_DISCLKH            0x200      // Disables Clock High generation interrupt

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_SCTRL register
//
//*************************************************************************************************
#define PMBUS_SCTRL_SDEVADDR_S         0U
#define PMBUS_SCTRL_SDEVADDR_M         0x7F        // Slave current device address Set
#define PMBUS_SCTRL_SADDRACKEN         0x80        // Manual Slave Address Acknowledgement Enable
#define PMBUS_SCTRL_SMASKEN_S          8U
#define PMBUS_SCTRL_SMASKEN_M          0x7F00      // Slave mask enable
#define PMBUS_SCTRL_PECPROEN           0x8000      // PEC processing enable
#define PMBUS_SCTRL_VALBYTESEL_S       16U
#define PMBUS_SCTRL_VALBYTESEL_M       0x70000     // Valid bytes Select
#define PMBUS_SCTRL_TXPEC              0x80000     // Transmit a PEC byte at the end of the message
#define PMBUS_SCTRL_COMC               0x100000    // Data Request flag generated after receive of command code
#define PMBUS_SCTRL_AUTOACK_S          21U
#define PMBUS_SCTRL_AUTOACK_M          0x600000    // Slave mode automatic acknowledge data bytes Configure

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_HSADDR register
//
//*************************************************************************************************
#define PMBUS_HSADDR_ADDRRW            0x1U        // Address stored R/W bit
#define PMBUS_HSADDR_DEVADDR_S         1U
#define PMBUS_HSADDR_DEVADDR_M         0xFE        // Stored device address

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_CTRL register
//
//*************************************************************************************************
#define PMBUS_CTRL_STSMRSTEN           0x1U        // State machines reset enable
#define PMBUS_CTRL_ALERTLOW            0x2U        // PMBus Alert driven low by slave
#define PMBUS_CTRL_CLKLTOCFG           0x4U        // Clock low timeout generated interrupt configure
#define PMBUS_CTRL_FASTEN              0x8U        // Fast Mode enable
#define PMBUS_CTRL_CTRLINTCFG          0x20U       // Control generated interrupt configure
#define PMBUS_CTRL_ALERTCFG            0x40U       // Alert pin configure
#define PMBUS_CTRL_ALERTDRVCFG         0x80U       // GPIO Mode Alert pin driven configure
#define PMBUS_CTRL_ALERTDIRCFG         0x100U      // Alert pin direction configure
#define PMBUS_CTRL_CTRLCFG             0x200U      // Control pin configure
#define PMBUS_CTRL_CTRLDRVCFG          0x400U      // GPIO Mode Control pin driven configure
#define PMBUS_CTRL_CTRLDIRCFG          0x800U      // Control pin direction configure
#define PMBUS_CTRL_SDACFG              0x1000U     // Data pin configure
#define PMBUS_CTRL_SDADRVCFG           0x2000U     // GPIO Mode Data pin driven configure
#define PMBUS_CTRL_SDADIRCFG           0x4000U     // Data pin direction configure
#define PMBUS_CTRL_SCLCFG              0x8000U     // Clock pin configure
#define PMBUS_CTRL_SCLDRVCFG           0x10000U    // GPIO Mode Clock pin driven configure
#define PMBUS_CTRL_SCLDIRCFG           0x20000U    // Clock pin direction configure
#define PMBUS_CTRL_THRUENA             0x40000U    // Current source for PMBus address detection thru ADC enable (A)
#define PMBUS_CTRL_THRUENB             0x80000U    // Current source for PMBus address detection thru ADC enable (B)
#define PMBUS_CTRL_DISCLKLTO           0x100000U   // Clock Low Timeout Disabled
#define PMBUS_CTRL_SLAVEEN             0x200000U   // PMBus Slave Enables
#define PMBUS_CTRL_MASTEREN            0x400000U   // PMBus Master Enables
#define PMBUS_CTRL_CLKDIV_S            23U
#define PMBUS_CTRL_CLKDIV_M            0xF800000   // SYSCLK clock divider
#define PMBUS_CTRL_MODECFG             0x80000000  // Mode Configure

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_TIMCTRL register
//
//*************************************************************************************************
#define PMBUS_TIMCTRL_PARCFG           0x1U        // FSM parameters Configure

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_CLKTIM register
//
//*************************************************************************************************
#define PMBUS_CLKTIM_CLKHIGHP_S        0U
#define PMBUS_CLKTIM_CLKHIGHP_M        0xFF        // number of FSM input clock in the PMBUS master clock high pulse Set
#define PMBUS_CLKTIM_CLKTIM_S          16U
#define PMBUS_CLKTIM_CLKTIM_M          0xFF0000    // number of FSM input clock in the PMBUS master clock period

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBTIMCTL register
//
//*************************************************************************************************
#define PMBUS_TIMCTRL_PARCFG   0x1U   // Overide the default settings of the timing
                                     // parameters.

// The bit fields in the PMBUS_STATIM register
//
//*************************************************************************************************
#define PMBUS_STATIM_STATIM_S          0U
#define PMBUS_STATIM_STATIM_M          0xFF        // The time between the last rising edge of the PMBus master clock and the next starting edge

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_BUSIDTIM register
//
//*************************************************************************************************
#define PMBUS_BUSIDTIM_BUSIDTIM_S      0U
#define PMBUS_BUSIDTIM_BUSIDTIM_M      0x3FF       // Bus Idle Time Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_CLKLTOTIIM register
//
//*************************************************************************************************
#define PMBUS_CLKLTOTIIM_CLKLTOTIIM_S  0U
#define PMBUS_CLKLTOTIIM_CLKLTOTIIM_M  0xFFFFF     // Clock Low Timeout Time

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_CLKHTOTIIM register
//
//*************************************************************************************************
#define PMBUS_CLKHTOTIIM_CLKHTOTIIM_S  0U
#define PMBUS_CLKHTOTIIM_CLKHTOTIIM_M  0x3FF       // Clock High Timeout Time

#endif // G32R501_PMBUS_H
