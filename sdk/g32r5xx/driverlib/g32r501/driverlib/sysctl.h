//###########################################################################
//
// FILE:    sysctl.h
//
// TITLE:   G32R501 system control driver.
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
// 1. Some comments, macro definitions, and enum names
// 2. Added the following functions: SysCtl_getAPBClock,
//    SysCtl_getAPBClock, SysCtl_setAPBClk, SysCtl_enableVOS,
//    SysCtl_disableVOS, SysCtl_setLDOVoltage, SysCtl_enableBootRomPrefetch,
//    SysCtl_disableBootRomPrefetch, SysCtl_enableSecureRomPrefetch,
//    SysCtl_disableSecureRomPrefetch, SysCtl_setBootRomLatency,
//    SysCtl_setSecureRomLatency, SysCtl_setCPU1BootAddress,
//    SysCtl_enableBootCPU1
// 3. Removed the following functions: SysCtl_isWatchdogEnabled,
//    SysCtl_getEfuseError, SysCtl_getPIEVErrAddr
//
//###########################################################################

#ifndef SYSCTL_H
#define SYSCTL_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup sysctl_api SysCtl
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_nmi.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"
#include "exti.h"
#include "interrupt.h"


//*****************************************************************************
//
// Defines for system control functions. Not intended for use by application
// code.
//
//*****************************************************************************

//
// Shifted pattern for WDTCTRL register's CHEAK field.
//
#define SYSCTL_WDT_CHKBITS       0x0028U

//
// Keys for WDTCNTRST field. The first enables resets and the second resets.
//
#define SYSCTL_WDT_ENRSTKEY      0x0055U
#define SYSCTL_WDT_RSTKEY        0x00AAU

//
// Values to help decode peripheral parameter
//
#define SYSCTL_PERIPH_REG_M     0x001FU
#define SYSCTL_PERIPH_REG_S     0x0000U
#define SYSCTL_PERIPH_BIT_M     0x1F00U
#define SYSCTL_PERIPH_BIT_S     0x0008U

//
//Keys for the System control registers write protection
//
#define SYSCTL_REG_KEY       0xA5A50000U
#define SYSCTL_PLL_KEY       0XCAFE0000U

//
//Values to help access shifting of bits
//
#define SYSCTL_TYPE_LOCK_S              0xFU


//
// LPM defines for LPMCR.LPM
//
#define SYSCTL_LPM_IDLE         0x0000U
#define SYSCTL_LPM_HALT         0x0002U

//
// Default internal oscillator frequency, 10 MHz
//
#define SYSCTL_DEFAULT_OSC_FREQ     10000000U

//
// Mask for SYNCSELECT.SYNCIN
//
#define SYSCTL_SYNCSELECT_SYNCIN_M  SYSCTL_SYNCSELECT_PWM4SYNCIN_M

//
// Boot ROM Booting and Reset Status
//
#define SYSCTL_BOOT_ROM_STATUS    0x20307F08U
#define SYSCTL_BOOT_ROM_POR       0x2000U
#define SYSCTL_BOOT_ROM_XRS       0x1000U

//
// Device_cal function which is available in OTP memory
// This function is called in SysCtl_resetPeripheral after resetting
// analog peripherals
//
#define Device_cal ((void (*)(void))((uintptr_t)0x10000119))

//*****************************************************************************
//
// The following are values that can be passed to the SysCtl_setClock() API as
// the config parameter.
//
//*****************************************************************************
//
// System clock divider (SYSDIV)
//

//
// Mask and shift for Output Clock Divider value in config
//
#define SYSCTL_ODIV_M        0x00700000UL
#define SYSCTL_ODIV_S        20U

//!
//! Macro to format Clock divider value. x is a number from 1 to 8.
//!
#define SYSCTL_ODIV(x)       ((((uint32_t)(x) - 1U) << SYSCTL_ODIV_S) &        \
                                                        SYSCTL_ODIV_M)

#define SYSCTL_SYSDIV_M     0x00001F80UL // Mask for SYSDIV value in config
#define SYSCTL_SYSDIV_S     7U           // Shift for SYSDIV value in config

//! Macro to format system clock divider value. x must be 1 or even values up
//! to 126.
#define SYSCTL_SYSDIV(x)    ((((x) / 2U) << SYSCTL_SYSDIV_S) & SYSCTL_SYSDIV_M)

//
// Integer multiplier (IMULT)
//
#define SYSCTL_IMULT_M      0x0000007FUL // Mask for IMULT value in config
#define SYSCTL_IMULT_S      0U           // Shift for IMULT value in config
//! Macro to format integer multiplier value. x is a number from 1 to 127.
//!
#define SYSCTL_IMULT(x)     (((x) << SYSCTL_IMULT_S) & SYSCTL_IMULT_M)

#ifndef DOXYGEN_PDF_IGNORE
//
// Fractional multiplier (FMULT)
//
#define SYSCTL_FMULT_M      0x00006000UL //!< Mask for FMULT value in config
#define SYSCTL_FMULT_S      13U          //!< Shift for FMULT value in config
#define SYSCTL_FMULT_NONE   0x00000000UL //!< No fractional multiplier
#define SYSCTL_FMULT_0      0x00000000UL //!< No fractional multiplier
#define SYSCTL_FMULT_1_4    0x00002000UL //!< Fractional multiplier of 0.25
#define SYSCTL_FMULT_1_2    0x00004000UL //!< Fractional multiplier of 0.50
#define SYSCTL_FMULT_3_4    0x00006000UL //!< Fractional multiplier of 0.75

//
// Oscillator source
//
// Also used with the SysCtl_selectOscSource(), SysCtl_turnOnOsc(),
// and SysCtl_turnOffOsc() functions as the oscSource parameter.
//
#define SYSCTL_OSCSRC_M         0x00030000UL // Mask for OSCSRC value in config
#define SYSCTL_OSCSRC_S         16U          // Shift for OSCSRC value in config
//! Internal oscillator INTOSC2
#define SYSCTL_OSCSRC_OSC2      0x00000000UL
//! External oscillator (XTAL) in crystal mode
#define SYSCTL_OSCSRC_XTAL      0x00010000UL
//! External oscillator (XTAL) in single-ended mode
#define SYSCTL_OSCSRC_XTAL_SE   0x00030000UL
//! Internal oscillator INTOSC1
#define SYSCTL_OSCSRC_OSC1      0x00020000UL

//
// Enable/disable PLL
//
#define SYSCTL_PLL_ENABLE       0x80000000UL //!< Enable PLL
#define SYSCTL_PLL_DISABLE      0x00000000UL //!< Disable PLL

//
// Number of PLL retries for SW work around
//
#define SYSCTL_PLL_RETRIES              100U    // Number of PLL retries
#define SYSCTL_PLLLOCK_TIMEOUT          2000U   // PLL Lock timeout
#define SYSCTL_DCC_COUNTER0_WINDOW      100U    // DCCOMP Counter0 Window
//*****************************************************************************
//
// Values that can be passed to SysCtl_clearNMIStatus(),
// SysCtl_forceNMIFlags(), SysCtl_isNMIFlagSet(), and
// SysCtl_isNMIShadowFlagSet() as the nmiFlags parameter and returned by
// SysCtl_getNMIFlagStatus() and SysCtl_getNMIShadowFlagStatus().
//
//*****************************************************************************
#define SYSCTL_NMI_NMIINT       0x1U    //!<  NMI Interrupt Flag
#define SYSCTL_NMI_CLOCKFAIL    0x2U    //!<  Clock Fail Interrupt Flag
#define SYSCTL_NMI_FLUNCERR     0x8U    //!<  Flash Uncorrectable Error NMI Flag
#define SYSCTL_NMI_FLBNMI       0x100U  //!<  Configurable Logic Block NMI Flag
#define SYSCTL_NMI_SWERR        0x2000U //!<  SW Error Force NMI Flag

//*****************************************************************************
//
// The following are values that can be passed to the SysCtl_clearResetCause()
// API as rstCauses or returned by the SysCtl_getResetCause() API.
//
//*****************************************************************************
#define SYSCTL_CAUSE_POR                 0x00000001U //!< Power-on reset (from Boot ROM status)
#define SYSCTL_CAUSE_XRS                 0x00000002U //!< External reset pin (from Boot ROM status)
#define SYSCTL_CAUSE_WDRS                0x00000004U //!< Watchdog reset
#define SYSCTL_CAUSE_NMIWDRS             0x00000008U //!< NMI watchdog reset
#define SYSCTL_CAUSE_SCCRESET            0x00000100U //!< SCCRESETn by DCS
//*****************************************************************************
//
// The following values define the adcsocSrc parameter for
// SysCtl_enableExtADCSOCSource() and SysCtl_disableExtADCSOCSource().
//
//*****************************************************************************
#define SYSCTL_ADCSOC_SRC_PWM1SOCA   0x1U //!<PWM1 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM2SOCA   0x2U //!<PWM2 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM3SOCA   0x4U //!<PWM3 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM4SOCA   0x8U //!<PWM4 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM5SOCA   0x10U //!<PWM5 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM6SOCA   0x20U //!<PWM6 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM7SOCA   0x40U //!<PWM7 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM8SOCA   0x80U //!<PWM8 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM1SOCB   0x10000U //!<PWM1 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM2SOCB   0x20000U //!<PWM2 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM3SOCB   0x40000U //!<PWM3 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM4SOCB   0x80000U //!<PWM4 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM5SOCB   0x100000U //!<PWM5 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM6SOCB   0x200000U //!<PWM6 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM7SOCB   0x400000U //!<PWM7 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM8SOCB   0x800000U //!<PWM8 SOCB for ADCSOCBO
#endif

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_enablePeripheral()
//! and SysCtl_disablePeripheral() as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_PERIPH_CLK_DMA = 0x0200, //!< DMA clock
    SYSCTL_PERIPH_CLK_TIMER0 = 0x0300, //!< TIMER0 clock
    SYSCTL_PERIPH_CLK_TIMER1 = 0x0400, //!< TIMER1 clock
    SYSCTL_PERIPH_CLK_TIMER2 = 0x0500, //!< TIMER2 clock
    SYSCTL_PERIPH_CLK_HRPWM = 0x1000, //!< HRPWM clock
    SYSCTL_PERIPH_CLK_TBCLKSYNC = 0x1200, //!< TBCLKSYNC clock
    SYSCTL_PERIPH_CLK_QSPI = 0x0001, //!< QSPI clock
    SYSCTL_PERIPH_CLK_PWM1 = 0x0002, //!< PWM1 clock
    SYSCTL_PERIPH_CLK_PWM2 = 0x0102, //!< PWM2 clock
    SYSCTL_PERIPH_CLK_PWM3 = 0x0202, //!< PWM3 clock
    SYSCTL_PERIPH_CLK_PWM4 = 0x0302, //!< PWM4 clock
    SYSCTL_PERIPH_CLK_PWM5 = 0x0402, //!< PWM5 clock
    SYSCTL_PERIPH_CLK_PWM6 = 0x0502, //!< PWM6 clock
    SYSCTL_PERIPH_CLK_PWM7 = 0x0602, //!< PWM7 clock
    SYSCTL_PERIPH_CLK_PWM8 = 0x0702, //!< PWM8 clock
    SYSCTL_PERIPH_CLK_CAP1 = 0x0003, //!< CAP1 clock
    SYSCTL_PERIPH_CLK_CAP2 = 0x0103, //!< CAP2 clock
    SYSCTL_PERIPH_CLK_CAP3 = 0x0203, //!< CAP3 clock
    SYSCTL_PERIPH_CLK_CAP4 = 0x0303, //!< CAP4 clock
    SYSCTL_PERIPH_CLK_CAP5 = 0x0403, //!< CAP5 clock
    SYSCTL_PERIPH_CLK_CAP6 = 0x0503, //!< CAP6 clock
    SYSCTL_PERIPH_CLK_CAP7 = 0x0603, //!< CAP7 clock
    SYSCTL_PERIPH_CLK_QEP1 = 0x0004, //!< QEP1 clock
    SYSCTL_PERIPH_CLK_QEP2 = 0x0104, //!< QEP2 clock
    SYSCTL_PERIPH_CLK_SDF = 0x0006, //!< SDF clock
    SYSCTL_PERIPH_CLK_UARTA = 0x0007, //!< UARTA clock
    SYSCTL_PERIPH_CLK_UARTB = 0x0107, //!< UARTB clock
    SYSCTL_PERIPH_CLK_SPIA = 0x0008, //!< SPIA clock
    SYSCTL_PERIPH_CLK_SPIB = 0x0108, //!< SPIB clock
    SYSCTL_PERIPH_CLK_I2CA = 0x0009, //!< I2CA clock
    SYSCTL_PERIPH_CLK_CANA = 0x000A, //!< CANA clock
    SYSCTL_PERIPH_CLK_CANB = 0x010A, //!< CANB clock
    SYSCTL_PERIPH_CLK_ADCA = 0x000D, //!< ADCA clock
    SYSCTL_PERIPH_CLK_ADCB = 0x010D, //!< ADCB clock
    SYSCTL_PERIPH_CLK_ADCC = 0x020D, //!< ADCC clock
    SYSCTL_PERIPH_CLK_COMP1 = 0x000E, //!< COMP1 clock
    SYSCTL_PERIPH_CLK_COMP2 = 0x010E, //!< COMP2 clock
    SYSCTL_PERIPH_CLK_COMP3 = 0x020E, //!< COMP3 clock
    SYSCTL_PERIPH_CLK_COMP4 = 0x030E, //!< COMP4 clock
    SYSCTL_PERIPH_CLK_COMP5 = 0x040E, //!< COMP5 clock
    SYSCTL_PERIPH_CLK_COMP6 = 0x050E, //!< COMP6 clock
    SYSCTL_PERIPH_CLK_COMP7 = 0x060E, //!< COMP7 clock
    SYSCTL_PERIPH_CLK_DACA = 0x1010, //!< DAC_A clock
    SYSCTL_PERIPH_CLK_DACB = 0x1110, //!< DAC_B clock
    SYSCTL_PERIPH_CLK_FLB1 = 0x0011, //!< FLB1 clock
    SYSCTL_PERIPH_CLK_FLB2 = 0x0111, //!< FLB2 clock
    SYSCTL_PERIPH_CLK_FLB3 = 0x0211, //!< FLB3 clock
    SYSCTL_PERIPH_CLK_FLB4 = 0x0311, //!< FLB4 clock
    SYSCTL_PERIPH_CLK_LINA = 0x0013, //!< LIN_A clock
    SYSCTL_PERIPH_CLK_PMBUSA = 0x0014, //!< PMBUS_A clock
    SYSCTL_PERIPH_CLK_DCCOMP0 = 0x0015  //!< DCC_0 clock
} SysCtl_PeripheralPCLOCKCR;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_resetPeripheral() as
//! the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_PERIPH_RES_PWM1 = 0x0002, //!< Reset PWM1 clock
    SYSCTL_PERIPH_RES_PWM2 = 0x0102, //!< Reset PWM2 clock
    SYSCTL_PERIPH_RES_PWM3 = 0x0202, //!< Reset PWM3 clock
    SYSCTL_PERIPH_RES_PWM4 = 0x0302, //!< Reset PWM4 clock
    SYSCTL_PERIPH_RES_PWM5 = 0x0402, //!< Reset PWM5 clock
    SYSCTL_PERIPH_RES_PWM6 = 0x0502, //!< Reset PWM6 clock
    SYSCTL_PERIPH_RES_PWM7 = 0x0602, //!< Reset PWM7 clock
    SYSCTL_PERIPH_RES_PWM8 = 0x0702, //!< Reset PWM8 clock
    SYSCTL_PERIPH_RES_CAP1 = 0x0003, //!< Reset CAP1 clock
    SYSCTL_PERIPH_RES_CAP2 = 0x0103, //!< Reset CAP2 clock
    SYSCTL_PERIPH_RES_CAP3 = 0x0203, //!< Reset CAP3 clock
    SYSCTL_PERIPH_RES_CAP4 = 0x0303, //!< Reset CAP4 clock
    SYSCTL_PERIPH_RES_CAP5 = 0x0403, //!< Reset CAP5 clock
    SYSCTL_PERIPH_RES_CAP6 = 0x0503, //!< Reset CAP6 clock
    SYSCTL_PERIPH_RES_CAP7 = 0x0603, //!< Reset CAP7 clock
    SYSCTL_PERIPH_RES_QEP1 = 0x0004, //!< Reset QEP1 clock
    SYSCTL_PERIPH_RES_QEP2 = 0x0104, //!< Reset QEP2 clock
    SYSCTL_PERIPH_RES_SD1 = 0x0006, //!< Reset SD1 clock
    SYSCTL_PERIPH_RES_UARTA = 0x0007, //!< Reset UARTA clock
    SYSCTL_PERIPH_RES_UARTB = 0x0107, //!< Reset UARTB clock
    SYSCTL_PERIPH_RES_SPIA = 0x0008, //!< Reset SPI_A clock
    SYSCTL_PERIPH_RES_SPIB = 0x0108, //!< Reset SPI_B clock
    SYSCTL_PERIPH_RES_I2CA = 0x0009, //!< Reset I2C_A clock
    SYSCTL_PERIPH_RES_CANA = 0x000A, //!< Reset CAN_A clock
    SYSCTL_PERIPH_RES_CANB = 0x010A, //!< Reset CAN_B clock
    SYSCTL_PERIPH_RES_QSPI = 0x000B, //!< Reset QSPI clock
    SYSCTL_PERIPH_RES_ADCA = 0x000D, //!< Reset ADC_A clock
    SYSCTL_PERIPH_RES_ADCB = 0x010D, //!< Reset ADC_B clock
    SYSCTL_PERIPH_RES_ADCC = 0x020D, //!< Reset ADC_C clock
    SYSCTL_PERIPH_RES_COMP1 = 0x000E, //!< Reset COMP1 clock
    SYSCTL_PERIPH_RES_COMP2 = 0x010E, //!< Reset COMP2 clock
    SYSCTL_PERIPH_RES_COMP3 = 0x020E, //!< Reset COMP3 clock
    SYSCTL_PERIPH_RES_COMP4 = 0x030E, //!< Reset COMP4 clock
    SYSCTL_PERIPH_RES_COMP5 = 0x040E, //!< Reset COMP5 clock
    SYSCTL_PERIPH_RES_COMP6 = 0x050E, //!< Reset COMP6 clock
    SYSCTL_PERIPH_RES_COMP7 = 0x060E, //!< Reset COMP7 clock
    SYSCTL_PERIPH_RES_DACA = 0x1010, //!< Reset DAC_A clock
    SYSCTL_PERIPH_RES_DACB = 0x1110, //!< Reset DAC_B clock
    SYSCTL_PERIPH_RES_FLB1 = 0x0011, //!< Reset FLB1 clock
    SYSCTL_PERIPH_RES_FLB2 = 0x0111, //!< Reset FLB2 clock
    SYSCTL_PERIPH_RES_FLB3 = 0x0211, //!< Reset FLB3 clock
    SYSCTL_PERIPH_RES_FLB4 = 0x0311, //!< Reset FLB4 clock
    SYSCTL_PERIPH_RES_LINA = 0x0013, //!< Reset LIN_A clock
    SYSCTL_PERIPH_RES_PMBUSA = 0x0014  //!< Reset PMBUS_A clock
} SysCtl_PeripheralSWRST;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogPredivider() as the \e predivider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_WDT_PREDIV_2    = 0x800,  //!< PREDIVCLK = INTOSC1 / 2
    SYSCTL_WDT_PREDIV_4    = 0x900,  //!< PREDIVCLK = INTOSC1 / 4
    SYSCTL_WDT_PREDIV_8    = 0xA00,  //!< PREDIVCLK = INTOSC1 / 8
    SYSCTL_WDT_PREDIV_16   = 0xB00,  //!< PREDIVCLK = INTOSC1 / 16
    SYSCTL_WDT_PREDIV_32   = 0xC00,  //!< PREDIVCLK = INTOSC1 / 32
    SYSCTL_WDT_PREDIV_64   = 0xD00,  //!< PREDIVCLK = INTOSC1 / 64
    SYSCTL_WDT_PREDIV_128  = 0xE00,  //!< PREDIVCLK = INTOSC1 / 128
    SYSCTL_WDT_PREDIV_256  = 0xF00,  //!< PREDIVCLK = INTOSC1 / 256
    SYSCTL_WDT_PREDIV_512  = 0x000,  //!< PREDIVCLK = INTOSC1 / 512
    SYSCTL_WDT_PREDIV_1024 = 0x100,  //!< PREDIVCLK = INTOSC1 / 1024
    SYSCTL_WDT_PREDIV_2048 = 0x200,  //!< PREDIVCLK = INTOSC1 / 2048
    SYSCTL_WDT_PREDIV_4096 = 0x300   //!< PREDIVCLK = INTOSC1 / 4096
} SysCtl_WDPredivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogPrescaler() as the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_WDT_PRESCALE_1  = 1,      //!< WDCLK = PREDIVCLK / 1
    SYSCTL_WDT_PRESCALE_2  = 2,      //!< WDCLK = PREDIVCLK / 2
    SYSCTL_WDT_PRESCALE_4  = 3,      //!< WDCLK = PREDIVCLK / 4
    SYSCTL_WDT_PRESCALE_8  = 4,      //!< WDCLK = PREDIVCLK / 8
    SYSCTL_WDT_PRESCALE_16 = 5,      //!< WDCLK = PREDIVCLK / 16
    SYSCTL_WDT_PRESCALE_32 = 6,      //!< WDCLK = PREDIVCLK / 32
    SYSCTL_WDT_PRESCALE_64 = 7       //!< WDCLK = PREDIVCLK / 64
} SysCtl_WDPrescaler;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogMode() as the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    //! Watchdog can generate a reset signal
    SYSCTL_WDT_MODE_RESET,
    //! Watchdog can generate an interrupt signal; reset signal is disabled
    SYSCTL_WDT_MODE_INTERRUPT
} SysCtl_WDMode;


//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setAPBClock() as
//! the \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_APBCLK_PRESCALE_1   = 0x0, //!< APBCLK = SYSCLK / 1 (default reset value)
    SYSCTL_APBCLK_PRESCALE_2   = 0x1, //!< APBCLK = SYSCLK / 2
} SysCtl_APBCLKPrescaler;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setLowSpeedClock() as
//! the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_LSPCLK_PRESCALE_1    = 0,    //!< LSPCLK = APBCLK / 1
    SYSCTL_LSPCLK_PRESCALE_2    = 1,    //!< LSPCLK = APBCLK / 2
    SYSCTL_LSPCLK_PRESCALE_4    = 2,    //!< LSPCLK = APBCLK / 4 (default)
    SYSCTL_LSPCLK_PRESCALE_6    = 3,    //!< LSPCLK = APBCLK / 6
    SYSCTL_LSPCLK_PRESCALE_8    = 4,    //!< LSPCLK = APBCLK / 8
    SYSCTL_LSPCLK_PRESCALE_10   = 5,    //!< LSPCLK = APBCLK / 10
    SYSCTL_LSPCLK_PRESCALE_12   = 6,    //!< LSPCLK = APBCLK / 12
    SYSCTL_LSPCLK_PRESCALE_14   = 7     //!< LSPCLK = APBCLK / 14
} SysCtl_LSPCLKPrescaler;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setPeripheralAccessControl() and SysCtl_getPeripheralAccessControl()
//! as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_ACCESS_ADCA         = 0x0, //!< ADCA access
    SYSCTL_ACCESS_ADCB         = 0x2, //!< ADCB access
    SYSCTL_ACCESS_ADCC         = 0x4, //!< ADCC access
    SYSCTL_ACCESS_COMP1        = 0x10, //!< COMP1 access
    SYSCTL_ACCESS_COMP2        = 0x12, //!< COMP2 access
    SYSCTL_ACCESS_COMP3        = 0x14, //!< COMP3 access
    SYSCTL_ACCESS_COMP4        = 0x16, //!< COMP4 access
    SYSCTL_ACCESS_COMP5        = 0x18, //!< COMP5 access
    SYSCTL_ACCESS_COMP6        = 0x1A, //!< COMP6 access
    SYSCTL_ACCESS_COMP7        = 0x1C, //!< COMP7 access
    SYSCTL_ACCESS_DACA         = 0x28, //!< DACA access
    SYSCTL_ACCESS_DACB         = 0x2A, //!< DACB access
    SYSCTL_ACCESS_PWM1         = 0x48, //!< PWM1 access
    SYSCTL_ACCESS_PWM2         = 0x4A, //!< PWM2 access
    SYSCTL_ACCESS_PWM3         = 0x4C, //!< PWM3 access
    SYSCTL_ACCESS_PWM4         = 0x4E, //!< PWM4 access
    SYSCTL_ACCESS_PWM5         = 0x50, //!< PWM5 access
    SYSCTL_ACCESS_PWM6         = 0x52, //!< PWM6 access
    SYSCTL_ACCESS_PWM7         = 0x54, //!< PWM7 access
    SYSCTL_ACCESS_PWM8         = 0x56, //!< PWM8 access
    SYSCTL_ACCESS_QEP1         = 0x70, //!< QEP1 access
    SYSCTL_ACCESS_QEP2         = 0x72, //!< QEP2 access
    SYSCTL_ACCESS_CAP1         = 0x80, //!< CAP1 access
    SYSCTL_ACCESS_CAP2         = 0x82, //!< CAP2 access
    SYSCTL_ACCESS_CAP3         = 0x84, //!< CAP3 access
    SYSCTL_ACCESS_CAP4         = 0x86, //!< CAP4 access
    SYSCTL_ACCESS_CAP5         = 0x88, //!< CAP5 access
    SYSCTL_ACCESS_CAP6         = 0x8A, //!< CAP6 access
    SYSCTL_ACCESS_CAP7         = 0x8C, //!< CAP7 access
    SYSCTL_ACCESS_SDF1         = 0xA8, //!< SDF1 access
    SYSCTL_ACCESS_FLB1         = 0xB0, //!< FLB1 access
    SYSCTL_ACCESS_FLB2         = 0xB2, //!< FLB2 access
    SYSCTL_ACCESS_FLB3         = 0xB4, //!< FLB3 access
    SYSCTL_ACCESS_FLB4         = 0xB6, //!< FLB4 access
    SYSCTL_ACCESS_SPIA         = 0x110, //!< SPIA access
    SYSCTL_ACCESS_SPIB         = 0x112, //!< SPIB access
    SYSCTL_ACCESS_PMBUSA       = 0x130, //!< PMBUS_A access
    SYSCTL_ACCESS_LINA         = 0x138, //!< LIN_A access
    SYSCTL_ACCESS_CANA         = 0x140, //!< DCANA access
    SYSCTL_ACCESS_CANB         = 0x142, //!< DCANB access
    SYSCTL_ACCESS_HRPWMA       = 0x1AA  //!< HRPWM_A access
} SysCtl_AccessPeripheral;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setPeripheralAccessControl() and SysCtl_getPeripheralAccessControl()
//! as the \e master parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_ACCESS_CPU0  = 0U,   //!< CPU0 access to the peripheral
    SYSCTL_ACCESS_CPU1  = 2U,   //!< CPU1 access to the peripheral
    SYSCTL_ACCESS_DMA1  = 4U    //!< DMA access to the peripheral
} SysCtl_AccessMaster;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setPeripheralAccessControl() as the \e permission parameter.
//
//*****************************************************************************
typedef enum
{
    //! Full Access for both read and write.
    SYSCTL_ACCESS_FULL      = 3U,
    //! Protected RD access such that FIFOs. Clear on read, registers are not
    //! changed and no write access.
    SYSCTL_ACCESS_PROTECTED = 2U,
    //! No read or write access.
    SYSCTL_ACCESS_NONE      = 0U
} SysCtl_AccessPermission;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_selectClockOutSource() as the \e source parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_CLOCKOUT_PLLSYS     = 0U,   //!< PLL System Clock post SYSCLKDIV
    SYSCTL_CLOCKOUT_PLLRAW     = 1U,   //!< PLL Raw Clock
    SYSCTL_CLOCKOUT_SYSCLK     = 2U,   //!< CPU System Clock
    SYSCTL_CLOCKOUT_APBCLK     = 3U,   //!< APB Clock
    SYSCTL_CLOCKOUT_INTOSC1    = 5U,   //!< Internal Oscillator 1
    SYSCTL_CLOCKOUT_INTOSC2    = 6U,   //!< Internal Oscillator 2
    SYSCTL_CLOCKOUT_XTALOSC    = 7U,   //!< External Oscillator
} SysCtl_ClockOut;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setExternalOscMode() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_XTALMODE_CRYSTAL = 1U,   //!< XTAL Oscillator Crystal Mode
    SYSCTL_XTALMODE_SINGLE  = 2U    //!< XTAL Oscillator Single-Ended Mode
} SysCtl_ExternalOscMode;

//*****************************************************************************
//
//! The following values define the \e syncInput parameter for
//! SysCtl_setSyncInputConfig().
//
//*****************************************************************************
typedef enum
{
    SYSCTL_SYNC_IN_PWM4 = 0, //!< Sync input to PWM4
    SYSCTL_SYNC_IN_PWM7 = 3, //!< Sync input to PWM7
    SYSCTL_SYNC_IN_CAP1 = 9, //!< Sync input to CAP1
    SYSCTL_SYNC_IN_CAP4 = 12, //!< Sync input to CAP4
    SYSCTL_SYNC_IN_CAP6 = 15, //!< Sync input to CAP6
    SYSCTL_SYNC_IN_PWM1 = 29  //!< Sync input to PWM1
} SysCtl_SyncInput;

//*****************************************************************************
//
//! The following values define the \e syncSrc parameter for
//! SysCtl_setSyncInputConfig(). Note that some of these are only valid for
//! certain values of \e syncInput. See device technical reference manual for
//! info on time-base counter synchronization for details.
//
//*****************************************************************************
typedef enum
{
    //! PWM1SYNCOUT
    SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT      = 0,
    //! PWM4SYNCOUT
    SYSCTL_SYNC_IN_SRC_PWM4SYNCOUT      = 1,
    //! PWM7SYNCOUT
    SYSCTL_SYNC_IN_SRC_PWM7SYNCOUT      = 2,
    //! CAP1SYNCOUT
    SYSCTL_SYNC_IN_SRC_CAP1SYNCOUT      = 4,
    //! EXTSYNCIN1--Valid for all values of syncInput
    SYSCTL_SYNC_IN_SRC_EXTSYNCIN1       = 5,
    //! EXTSYNCIN2--Valid for all values of syncInput
    SYSCTL_SYNC_IN_SRC_EXTSYNCIN2       = 6,
} SysCtl_SyncInputSource;

//*****************************************************************************
//
//! The following values define the \e syncSrc parameter for
//! SysCtl_setSyncOutputConfig().
//
//*****************************************************************************
typedef enum
{
    SYSCTL_SYNC_OUT_SRC_PWM1SYNCOUT,   //!< PWM1SYNCOUT --> EXTSYNCOUT
    SYSCTL_SYNC_OUT_SRC_PWM4SYNCOUT,   //!< PWM4SYNCOUT --> EXTSYNCOUT
    SYSCTL_SYNC_OUT_SRC_PWM7SYNCOUT    //!< PWM7SYNCOUT --> EXTSYNCOUT

} SysCtl_SyncOutputSource;

//*****************************************************************************
//
//! The following values define the \e parametric parameter for
//! SysCtl_getDeviceParametric().
//
//*****************************************************************************
typedef enum
{
    SYSCTL_DEVICE_QUAL,       //!< Device Qualification Status
    SYSCTL_DEVICE_PINCOUNT,   //!< Device Pin Count
    SYSCTL_DEVICE_INSTASPIN,  //!< Device InstaSPIN Feature Set
    SYSCTL_DEVICE_FLASH,      //!< Device Flash size (KB)
    SYSCTL_DEVICE_FAMILY,     //!< Device Family
    SYSCTL_DEVICE_PARTNO,     //!< Device Part Number
    SYSCTL_DEVICE_CLASSID     //!< Device Class ID
} SysCtl_DeviceParametric;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setXClk() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_XCLKOUT_DIV_1  = 0,      //!<  XCLKOUT =  XCLKOUT / 1
    SYSCTL_XCLKOUT_DIV_2  = 1,      //!<  XCLKOUT =  XCLKOUT / 2
    SYSCTL_XCLKOUT_DIV_4  = 2,      //!<  XCLKOUT =  XCLKOUT / 4
    SYSCTL_XCLKOUT_DIV_8  = 3       //!<  XCLKOUT =  XCLKOUT / 8

}SysCtl_XClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setCputimer2Clk() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_TMR2CLKPRESCALE_1,   //!<  timer2 clock =  timer2 clock / 1
    SYSCTL_TMR2CLKPRESCALE_2,   //!<  timer2 clock =  timer2 clock / 2
    SYSCTL_TMR2CLKPRESCALE_4,   //!<  timer2 clock =  timer2 clock / 4
    SYSCTL_TMR2CLKPRESCALE_8,   //!<  timer2 clock =  timer2 clock / 8
    SYSCTL_TMR2CLKPRESCALE_16   //!<  timer2 clock =  timer2 clock / 16

}SysCtl_Timer2ClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setCputimer2Clk()
//! as \e source parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_TMR2CLKSRCSEL_SYSCLK     = 0U,   //!< System Clock
    SYSCTL_TMR2CLKSRCSEL_INTOSC1    = 1U,   //!< Internal Oscillator 1
    SYSCTL_TMR2CLKSRCSEL_INTOSC2    = 2U,   //!< Internal Oscillator 2
    SYSCTL_TMR2CLKSRCSEL_XTAL       = 3U,   //!< Crystal oscillator
    SYSCTL_TMR2CLKSRCSEL_FLPUMPOSC  = 4U    //!< FLPUMPOSC CLock
}SysCtl_Timer2ClkSource;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setLDOVoltage() as \e scaler parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_LDOVOLT_0 = 0U,                      //!<  LDO voltage 1.1v
    SYSCTL_LDOVOLT_3 = 3U,                      //!<  LDO voltage 1.0v
    SYSCTL_LDOVOLT_4 = 4U,                      //!<  LDO voltage 1.05v
    SYSCTL_LDOVOLT_5 = 5U,                      //!<  LDO voltage 1.1v
    SYSCTL_LDOVOLT_6 = 6U,                      //!<  LDO voltage 1.15v
    SYSCTL_LDOVOLT_7 = 7U                       //!<  LDO voltage 1.15v
}SysCtl_LDOVolScaler;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Wrapper function for Device_cal function
//!
//! \param None
//!
//! This is a wrapper function for the Device_cal function available in the OTP
//! memory.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_deviceCal(void)
{
    //
    // Call the Device_cal function
    //
    Device_cal();
}

//*****************************************************************************
//
//! Sets up APBCLK divider.
//!
//! \param divider is the value that configures the divider.
//!
//! This function sets up the APBCLK divider. There is only one
//! divider that scales the system clock to generate the APBCLK.
//! The \e divider parameter is the value by which the SYSCLK rate is divided
//! to get the APBCLK rate. For example, a \e divider of
//! \b SYSCTL_APBCLK_PRESCALE_4 will result in an APBCLK rate that is a quarter
//! of the SYSCLK rate.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setAPBClock(SysCtl_APBCLKPrescaler prescaler)
{
    //
    // Write the divider selection to the appropriate register.
    //
    WRPRT_DISABLE;

    HWREG(SYSCTL_BASE + SYSCTL_O_APBCLKDIVCFG) =
        (HWREG(SYSCTL_BASE + SYSCTL_O_APBCLKDIVCFG) &
        ~(SYSCTL_APBCLKDIVCFG_APBCLKDIVCFG_M)) | prescaler;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables VOS mode.
//!
//! \param None.
//!
//! \return None.
//*****************************************************************************
static inline void
SysCtl_enableVOS(void)
{
    WRPRT_DISABLE;

    HWREG(SYSCTL_BASE + SYSCTL_O_VOS) |= 0x01;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//!Disables VOS mode.
//!
//! \param None.
//!
//! \return None.
//*****************************************************************************
static inline void
SysCtl_disableVOS(void)
{

    WRPRT_DISABLE;

    HWREG(SYSCTL_BASE + SYSCTL_O_VOS) &= ~(0x01);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets LDO voltage value.
//!
//! \param scaler is the value that configures the LDO voltage scaling.
//!
//! This function setsthe LDO voltage.
//!
//! The \e scaler parameter can have one enumerated value from
//! SysCtl_LDOVolScaler.
//!
//! \return None.
//*****************************************************************************
static inline void
SysCtl_setLDOVoltage(SysCtl_LDOVolScaler scaler)
{

    WRPRT_DISABLE;

    HWREG(SYSCTL_BASE + SYSCTL_O_VOS) =
        (HWREG(SYSCTL_BASE + SYSCTL_O_VOS) &
        ~(SYSCTL_VOS_LDOVSCACFG_M << SYSCTL_VOS_LDOVSCACFG_S)) | (scaler << SYSCTL_VOS_LDOVSCACFG_S);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables BOOT ROM prefetch.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableBootRomPrefetch(void)
{
    WRPRT_DISABLE;
    HWREG(ROM_PREFETCH_BASE + SYSCTL_O_BOOT_ROM_PREFETCH) |= 0x01;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables BOOT ROM prefetch.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableBootRomPrefetch(void)
{
    WRPRT_DISABLE;
    HWREG(ROM_PREFETCH_BASE + SYSCTL_O_BOOT_ROM_PREFETCH) &= ~(0x01);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables SECURE ROM prefetch.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableSecureRomPrefetch(void)
{
    WRPRT_DISABLE;
    HWREG(ROM_PREFETCH_BASE + SYSCTL_O_SECURE_ROM_PREFETCH) |= 0x01;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables SECURE ROM prefetch.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableSecureRomPrefetch(void)
{
    WRPRT_DISABLE;
    HWREG(ROM_PREFETCH_BASE + SYSCTL_O_SECURE_ROM_PREFETCH) &= ~(0x01);
    WRPRT_ENABLE;
}

//
//! Sets BOOT ROM latency
//!
//! \param latency is the rom latency to set.
//!
//! This function sets boot rom latency, The latency parameter is a number between 0 and 7.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setBootRomLatency(uint8_t latency)
{
    ASSERT(latency <= 0x07);

    WRPRT_DISABLE;
    HWREG(ROM_WAIT_BASE + SYSCTL_O_BOOT_ROM_LATENCY) =
        (HWREG(ROM_WAIT_BASE + SYSCTL_O_BOOT_ROM_LATENCY) &
        ~(0x07)) | latency;
    WRPRT_ENABLE;
}

//
//! Sets SECURE ROM latency
//!
//! \param latency is the rom latency to set.
//!
//! This function sets secure rom latency, The latency parameter is a number between 0 and 7.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setSecureRomLatency(uint8_t latency)
{
    ASSERT(latency <= 0x07);

    WRPRT_DISABLE;
    HWREG(ROM_WAIT_BASE + SYSCTL_O_SECURE_ROM_LATENCY) =
        (HWREG(ROM_WAIT_BASE + SYSCTL_O_SECURE_ROM_LATENCY) &
        ~(0x07)) | latency;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Resets a peripheral
//!
//! \param peripheral is the peripheral to reset.
//!
//! This function uses the SWRSTx registers to reset a specified peripheral.
//! Module registers will be returned to their reset states.
//!
//! \note This includes registers containing trim values.The peripheral
//! software reset needed by CPU2 can be communicated to CPU1 via
//! IPC for all shared peripherals.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_resetPeripheral(SysCtl_PeripheralSWRST peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)4U * ((uint16_t)peripheral &
                               (uint16_t)SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
               SYSCTL_PERIPH_BIT_S;

    WRPRT_DISABLE;

    //
    // Sets the appropriate reset bit and then clears it.
    //
    HWREG(DEVCFG_BASE + SYSCTL_O_SOFTPRES2 + regIndex - 8U) |=  (1UL << bitIndex);
    HWREG(DEVCFG_BASE + SYSCTL_O_SOFTPRES2 + regIndex - 8U) &= ~(1UL << bitIndex);

    //
    // Call Device_cal function
    //
    if((((uint16_t)peripheral & SYSCTL_PERIPH_REG_M) == 0xDU) ||      // ADCx
       (((uint16_t)peripheral & SYSCTL_PERIPH_REG_M) == 0x10U)        // DACx
       )
    {
        SysCtl_deviceCal();
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables a peripheral.
//!
//! \param peripheral is the peripheral to enable.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! \note Note that there should be atleast 5 cycles delay between enabling the
//! peripheral clock and accessing the peripheral registers. The delay should be
//! added by the user if the peripheral is accessed immediately after this
//! function call.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)4U * ((uint16_t)peripheral &
                               (uint16_t)SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
               SYSCTL_PERIPH_BIT_S;

    WRPRT_DISABLE;

    //
    // Turn on the module clock.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_PCLKCR0 + regIndex) |= (1UL << bitIndex);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables a peripheral.
//!
//! \param peripheral is the peripheral to disable.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)4U * ((uint16_t)peripheral &
                               (uint16_t)SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
               SYSCTL_PERIPH_BIT_S;

    WRPRT_DISABLE;

    //
    // Turn off the module clock.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_PCLKCR0 + regIndex) &= ~(1UL << bitIndex);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Resets the device.
//!
//! This function performs a watchdog reset of the device.
//!
//! \return This function does not return.
//
//*****************************************************************************
static inline void
SysCtl_resetDevice(void)
{
    //
    // Write an incorrect check value to the watchdog control register
    // This will cause a device reset
    //
    WRPRT_DISABLE;

    //
    // Enable the watchdog
    //
    HWREGH(WDT_BASE + SYSCTL_O_WDCR) = SYSCTL_WDT_CHKBITS;

    //
    // Write a bad check value
    //
    HWREGH(WDT_BASE + SYSCTL_O_WDCR) = 0U;

    WRPRT_ENABLE;

    //
    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    //
    while((bool)1)
    {
    }
}

//*****************************************************************************
//
//! Gets the reason for a reset.
//!
//! This function will return the reason(s) for a reset.  Since the reset
//! reasons are sticky until either cleared by software or an external reset,
//! multiple reset reasons may be returned if multiple resets have occurred.
//! The reset reason will be a logical OR of
//! - \b SYSCTL_CAUSE_POR - Power-on reset (from Boot ROM status only)
//! - \b SYSCTL_CAUSE_XRS - External reset pin (from Boot ROM status only)
//! - \b SYSCTL_CAUSE_WDRS - Watchdog reset
//! - \b SYSCTL_CAUSE_NMIWDRS - NMI watchdog reset
//! - \b SYSCTL_CAUSE_SCCRESET - SCCRESETn reset from DCS
//!
//! \note POR and XRS are reported from Boot ROM status only. RESC bit0/bit1
//! are reserved and are not used for reset-cause detection.
//!
//! \note If you re-purpose the reserved boot ROM RAM, the POR and XRS reset
//! statuses won't be accurate.
//!
//! \return Returns the reason(s) for a reset.
//
//*****************************************************************************
static inline uint32_t
SysCtl_getResetCause(void)
{
    uint32_t resetCauses;

    //
    // Read CPU reset register (RESC bit0/bit1 are reserved)
    //
    resetCauses = HWREG(CPUSYS_BASE + SYSCTL_O_RESC) &
                  ((uint32_t)SYSCTL_RESC_WDRSN |
                   (uint32_t)SYSCTL_RESC_NMIWDRSN |
                   (uint32_t)SYSCTL_RESC_SCCRESETN
                   );

    //
    // Set POR and XRS Causes from boot ROM Status
    //
    if((HWREG(SYSCTL_BOOT_ROM_STATUS) & (uint32_t)SYSCTL_BOOT_ROM_POR) ==
       (uint32_t)SYSCTL_BOOT_ROM_POR)
    {
        resetCauses |= SYSCTL_CAUSE_POR;
    }
    if((HWREG(SYSCTL_BOOT_ROM_STATUS) & (uint32_t)SYSCTL_BOOT_ROM_XRS) ==
       (uint32_t)SYSCTL_BOOT_ROM_XRS)
    {
        resetCauses |= SYSCTL_CAUSE_XRS;
    }

    //
    // Return the reset reasons.
    //
    return(resetCauses);
}

//*****************************************************************************
//
//! Clears reset reasons.
//!
//! \param rstCauses are the reset causes to be cleared; must be a logical
//! OR of
//! - \b SYSCTL_CAUSE_WDRS - Watchdog reset
//! - \b SYSCTL_CAUSE_NMIWDRS - NMI watchdog reset
//! - \b SYSCTL_CAUSE_SCCRESET - SCCRESETn reset from DCS
//!
//! This function clears the specified sticky reset reasons.  Once cleared,
//! another reset for the same reason can be detected, and a reset for a
//! different reason can be distinguished (instead of having two reset causes
//! set).  If the reset reason is used by an application, all reset causes
//! should be cleared after they are retrieved with SysCtl_getResetCause().
//!
//! \note Some reset causes are cleared by the boot ROM.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearResetCause(uint32_t rstCauses)
{
    //
    // Clear the given reset reasons.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_RESCCLR) = rstCauses;
}

//*****************************************************************************
//
//! Sets the low speed peripheral clock rate prescaler.
//!
//! \param prescaler is the LSPCLK rate relative to APBCLK
//!
//! This function configures the clock rate of the low speed peripherals. The
//! \e prescaler parameter is the value by which the APBCLK rate is divided to
//! get the LSPCLK rate. For example, a \e prescaler of
//! \b SYSCTL_LSPCLK_PRESCALE_4 will result in a LSPCLK rate that is a quarter
//! of the APBCLK rate.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setLowSpeedClock(SysCtl_LSPCLKPrescaler prescaler)
{
    //
    // Write the divider selection to the appropriate register.
    //
    WRPRT_DISABLE;
    HWREG(CLKCFG_BASE + SYSCTL_O_LOSPCP) =
        (HWREG(CLKCFG_BASE + SYSCTL_O_LOSPCP) &
         ~(uint32_t)SYSCTL_LOSPCP_LSPCLKDIV_M) | (uint32_t)prescaler;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Selects a clock source to mux to an external GPIO pin (XCLKOUT).
//!
//! \param source is the internal clock source to be configured.
//!
//! This function configures the specified clock source to be muxed to an
//! external clock out (XCLKOUT) GPIO pin. The \e source parameter may take a
//! value of one of the following values:
//! - \b SYSCTL_CLOCKOUT_PLLSYS
//! - \b SYSCTL_CLOCKOUT_PLLRAW
//! - \b SYSCTL_CLOCKOUT_SYSCLK
//! - \b SYSCTL_CLOCKOUT_APBCLK
//! - \b SYSCTL_CLOCKOUT_INTOSC1
//! - \b SYSCTL_CLOCKOUT_INTOSC2
//! - \b SYSCTL_CLOCKOUT_XTALOSC
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_selectClockOutSource(SysCtl_ClockOut source)
{
    WRPRT_DISABLE;

    //
    // Clear clock out source
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL3) &=
        ~SYSCTL_CLKSRCCTL3_XCLKOUTSEL_M;

    //
    // Set clock out source
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL3) |= (uint16_t)source;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the external oscillator mode.
//!
//! \param mode is the external oscillator mode to be configured.
//!
//! This function sets the external oscillator mode specified by the \e mode
//! parameter which may take one of two values:
//! - \b SYSCTL_XTALMODE_CRYSTAL - Crystal Mode
//! - \b SYSCTL_XTALMODE_SINGLE  - Single-Ended Mode
//!
//! \note The external oscillator must be powered off before this configuration
//! can be performed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setExternalOscMode(SysCtl_ExternalOscMode mode)
{
    WRPRT_DISABLE;

    switch(mode)
    {
        case SYSCTL_XTALMODE_CRYSTAL:
            //
            // Set mode to Crystal
            //
            HWREG(CLKCFG_BASE + SYSCTL_O_XTALCR) &= ~(uint32_t)SYSCTL_XTALCR_SE;
            break;

        case SYSCTL_XTALMODE_SINGLE:
            //
            // Set mode to Single-Ended
            //
            HWREG(CLKCFG_BASE + SYSCTL_O_XTALCR) |= SYSCTL_XTALCR_SE;
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
//! Gets the external oscillator counter value.
//!
//! This function returns the X1 clock counter value. When the return value
//! reaches 0x3FF, it freezes. Before switching from INTOSC2 to an external
//! oscillator (XTAL), an application should call this function to make sure
//! the counter is saturated.
//!
//! \return Returns the value of the 10-bit X1 clock counter.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getExternalOscCounterValue(void)
{
    return(HWREGH(CLKCFG_BASE + SYSCTL_O_X1CNT) & SYSCTL_X1CNT_X1CNT_M);
}

//*****************************************************************************
//
//! Clears the external oscillator counter value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearExternalOscCounterValue(void)
{
    HWREG(CLKCFG_BASE + SYSCTL_O_X1CNT) |= SYSCTL_X1CNT_CLR;
}

//*****************************************************************************
//
//! Turns on the specified oscillator sources.
//!
//! Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
//! SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function turns on the oscillator specified by the \e oscSource
//! parameter which may take a value of  \b SYSCTL_OSCSRC_XTAL
//! or \b SYSCTL_OSCSRC_OSC2.
//!
//! \note \b SYSCTL_OSCSRC_OSC1 is not a valid value for \e oscSource.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_turnOnOsc(uint32_t oscSource)
{
    ASSERT(
           (oscSource == SYSCTL_OSCSRC_OSC2) ||
           (oscSource == SYSCTL_OSCSRC_XTAL)
          );

    WRPRT_DISABLE;

    switch(oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            //
            // Turn on INTOSC2
            //
            HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &=
                ~SYSCTL_CLKSRCCTL1_INTOSC2OFF;
            break;

        case SYSCTL_OSCSRC_XTAL:
            //
            // Turn on XTALOSC
            //
            HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_OSCOFF;

            break;

        default:
            //
            // Do nothing. Not a valid oscSource value.
            //
            break;
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Turns off the specified oscillator sources.
//!
//! Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
//! SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function turns off the oscillator specified by the \e oscSource
//! parameter which may take a value of  \b SYSCTL_OSCSRC_XTAL
//! or \b SYSCTL_OSCSRC_OSC2.
//!
//! \note \b SYSCTL_OSCSRC_OSC1 is not a valid value for \e oscSource.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_turnOffOsc(uint32_t oscSource)
{
    ASSERT(
           (oscSource == SYSCTL_OSCSRC_OSC2) |
           (oscSource == SYSCTL_OSCSRC_XTAL)
          );

    WRPRT_DISABLE;

    switch(oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            //
            // Turn off INTOSC2
            //
            HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) |=
                SYSCTL_CLKSRCCTL1_INTOSC2OFF;
            break;

        case SYSCTL_OSCSRC_XTAL:
            //
            // Turn off XTALOSC
            //
            HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) |= SYSCTL_XTALCR_OSCOFF;
            break;

        default:
            //
            // Do nothing. Not a valid oscSource value.
            //
            break;
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enters IDLE mode.
//!
//! This function puts the device into IDLE mode. The CPU clock is gated while
//! all peripheral clocks are left running. Any enabled interrupt will wake the
//! CPU up from IDLE mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enterIdleMode(void)
{
    WRPRT_DISABLE;

    //
    // Configure the device to go into IDLE mode when IDLE is executed.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) =
                (HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) &
                 ~(uint32_t)SYSCTL_LPMCR_LPM_M) | SYSCTL_LPM_IDLE;

    WRPRT_ENABLE;

#ifndef _DUAL_HEADERS
    IDLE_ASM;
#else
    IDLE_ASM;
#endif
}

//*****************************************************************************
//
//! Enters HALT mode.
//!
//! This function puts the device into HALT mode. This will gate almost all
//! systems and clocks and allows for the power-down of oscillators and analog
//! blocks. The watchdog may be left clocked to produce a reset. See
//! SysCtl_enableWatchdogInHalt() to enable this. GPIOs should be
//! configured to wake the CPU subsystem. See SysCtl_enableLPMWakeupPin().
//!
//!
//! The CPU will receive an interrupt (WAKEINT) on wakeup.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enterHaltMode(void)
{
    WRPRT_DISABLE;

    //
    // Configure the device to go into HALT mode when IDLE is executed.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) =
                (HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) &
                 ~(uint32_t)SYSCTL_LPMCR_LPM_M) | SYSCTL_LPM_HALT;

    WRPRT_ENABLE;

#ifndef _DUAL_HEADERS
    IDLE_ASM;
#else
    IDLE_ASM;
#endif
}

//*****************************************************************************
//! Enables a pin to wake up the device from the following mode(s):
//!  - HALT
//!
//! \param pin is the identifying number of the pin.
//!
//! This function connects a pin to the LPM circuit, allowing an event on the
//! pin to wake up the device when when it is in following mode(s):
//!  - HALT
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin. Only GPIOs 0 through 63 are capable of
//! being connected to the LPM circuit.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableLPMWakeupPin(uint32_t pin)
{
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(pin <= 63U);

    pinMask = 1UL << (pin % 32U);

    WRPRT_DISABLE;

    if(pin < 32U)
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL0) |= pinMask;
    }
    else
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL1) |= pinMask;
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//! Disables a pin to wake up the device from the following mode(s):
//!  - HALT
//!
//! \param pin is the identifying number of the pin.
//!
//! This function disconnects a pin to the LPM circuit, disallowing an event on
//! the pin to wake up the device when when it is in following mode(s):
//!  - HALT
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin. Only GPIOs 0 through 63 are valid.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableLPMWakeupPin(uint32_t pin)
{
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(pin <= 63U);

    pinMask = 1UL << (pin % 32U);

    WRPRT_DISABLE;

    if(pin < 32U)
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL0) &= ~pinMask;
    }
    else
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL1) &= ~pinMask;
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable the watchdog to run while in HALT mode.
//!
//! Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
//! SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//!
//! This function configures the watchdog to continue to run while in HALT
//! mode. Additionally, INTOSC1 and INTOSC2 are not powered down when the
//! system enters HALT mode. By default the watchdog is gated when the system
//! enters HALT.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableWatchdogInHalt(void)
{
    WRPRT_DISABLE;

    //
    // Set the watchdog HALT mode ignore bit.
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) |= SYSCTL_CLKSRCCTL1_WDHALTI;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable the watchdog from running while in HALT mode.
//!
//! Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
//! SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//!
//! This function gates the watchdog when the system enters HALT mode. INTOSC1
//! and INTOSC2 will be powered down. This is the default behavior of the
//! device.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableWatchdogInHalt(void)
{
    WRPRT_DISABLE;

    //
    // Clear the watchdog HALT mode ignore bit.
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &= ~SYSCTL_CLKSRCCTL1_WDHALTI;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Configures whether the watchdog generates a reset or an interrupt signal.
//!
//! \param mode is a flag to select the watchdog mode.
//!
//! This function configures the action taken when the watchdog counter reaches
//! its maximum value. When the \e mode parameter is
//! \b SYSCTL_WDT_MODE_INTERRUPT, the watchdog is enabled to generate a watchdog
//! interrupt signal and disables the generation of a reset signal. This will
//! allow the watchdog module to wake up the device from IDLE
//!
//! When the \e mode parameter is \b SYSCTL_WDT_MODE_RESET, the watchdog will
//! be put into reset mode and generation of a watchdog interrupt signal will
//! be disabled. This is how the watchdog is configured by default.
//!
//! \note Check the status of the watchdog interrupt using
//! SysCtl_isWatchdogInterruptActive() before calling this function. If the
//! interrupt is still active, switching from interrupt mode to reset mode will
//! immediately reset the device.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogMode(SysCtl_WDMode mode)
{
    WRPRT_DISABLE;

    //
    // Either set or clear the INTRSTCFG bit to that will determine whether the
    // watchdog will generate a reset signal or an interrupt signal. Take care
    // not to write a 1 to DISLOCK.
    //
    if(mode == SYSCTL_WDT_MODE_INTERRUPT)
    {
        HWREGH(WDT_BASE + SYSCTL_O_SCSR) =
                (HWREGH(WDT_BASE + SYSCTL_O_SCSR) & ~SYSCTL_SCSR_WDOVERRIDE) |
                SYSCTL_SCSR_WDENINT;
    }
    else
    {
        HWREGH(WDT_BASE + SYSCTL_O_SCSR) &= ~(SYSCTL_SCSR_WDENINT |
                                             SYSCTL_SCSR_WDOVERRIDE);
    }

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the status of the watchdog interrupt signal.
//!
//! This function returns the status of the watchdog interrupt signal. If the
//! interrupt is active, this function will return \b true. If \b false, the
//! interrupt is NOT active.
//!
//! \note Make sure to call this function to ensure that the interrupt is not
//! active before making any changes to the configuration of the watchdog to
//! prevent any unexpected behavior. For instance, switching from interrupt
//! mode to reset mode while the interrupt is active will immediately reset the
//! device.
//!
//! \return \b true if the interrupt is active and \b false if it is not.
//
//*****************************************************************************
static inline bool
SysCtl_isWatchdogInterruptActive(void)
{
    //
    // If the status bit is cleared, the WDINTn signal is active.
    //
    return((HWREGH(WDT_BASE + SYSCTL_O_SCSR) & SYSCTL_SCSR_WDINTS) == 0U);
}

//*****************************************************************************
//
//! Disables the watchdog.
//!
//! This function disables the watchdog timer. Note that the watchdog timer is
//! enabled on reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableWatchdog(void)
{
    WRPRT_DISABLE;

    //
    // Set the disable bit.
    //
    HWREGH(WDT_BASE + SYSCTL_O_WDCR) |= SYSCTL_WDT_CHKBITS | SYSCTL_WDCR_WDDIS;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables the watchdog.
//!
//! This function enables the watchdog timer. Note that the watchdog timer is
//! enabled on reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableWatchdog(void)
{
    WRPRT_DISABLE;

    //
    // Clear the disable bit.
    //
    HWREGH(WDT_BASE + SYSCTL_O_WDCR) = (HWREGH(WDT_BASE + SYSCTL_O_WDCR) &
                                       ~SYSCTL_WDCR_WDDIS) | SYSCTL_WDT_CHKBITS;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Services the watchdog.
//!
//! This function resets the watchdog.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_serviceWatchdog(void)
{
    WRPRT_DISABLE;

    //
    // Enable the counter to be reset and then reset it.
    //
    HWREGH(WDT_BASE + SYSCTL_O_WDKEY) = SYSCTL_WDT_ENRSTKEY;
    HWREGH(WDT_BASE + SYSCTL_O_WDKEY) = SYSCTL_WDT_RSTKEY;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Writes the first key to enter the watchdog reset.
//!
//! This function writes the first key to enter the watchdog reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableWatchdogReset(void)
{
    WRPRT_DISABLE;

    //
    // Enable the counter to be reset
    //
    HWREGH(WDT_BASE + SYSCTL_O_WDKEY) = SYSCTL_WDT_ENRSTKEY;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Writes the second key to reset the watchdog.
//!
//! This function writes the second key to reset the watchdog.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_resetWatchdog(void)
{
    WRPRT_DISABLE;

    //
    // Reset the watchdog counter
    //
    HWREGH(WDT_BASE + SYSCTL_O_WDKEY) = SYSCTL_WDT_RSTKEY;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets up watchdog clock (WDCLK) pre-divider.
//!
//! \param predivider is the value that configures the pre-divider.
//!
//! This function sets up the watchdog clock (WDCLK) pre-divider. There are two
//! dividers that scale INTOSC1 to WDCLK. The \e predivider parameter divides
//! INTOSC1 down to PREDIVCLK and the prescaler (set by the
//! SysCtl_setWatchdogPrescaler() function) divides PREDIVCLK down to WDCLK.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogPredivider(SysCtl_WDPredivider predivider)
{
    uint16_t regVal;

    regVal = (uint16_t)predivider | SYSCTL_WDT_CHKBITS;

    WRPRT_DISABLE;

    //
    // Write the predivider to the appropriate register.
    //
    HWREGH(WDT_BASE + SYSCTL_O_WDCR) = (HWREGH(WDT_BASE + SYSCTL_O_WDCR) &
                                       ~(SYSCTL_WDCR_WDPRECLKDIV_M)) | regVal;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets up watchdog clock (WDCLK) prescaler.
//!
//! \param prescaler is the value that configures the watchdog clock relative
//! to the value from the pre-divider.
//!
//! This function sets up the watchdog clock (WDCLK) prescaler. There are two
//! dividers that scale INTOSC1 to WDCLK. The predivider (set with the
//! SysCtl_setWatchdogPredivider() function) divides INTOSC1 down to PREDIVCLK
//! and the \e prescaler parameter divides PREDIVCLK down to WDCLK.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogPrescaler(SysCtl_WDPrescaler prescaler)
{
    uint16_t regVal;

    regVal = (uint16_t)prescaler | (uint16_t)SYSCTL_WDT_CHKBITS;

    WRPRT_DISABLE;

    //
    // Write the prescaler to the appropriate register.
    //
    HWREGH(WDT_BASE + SYSCTL_O_WDCR) = (HWREGH(WDT_BASE + SYSCTL_O_WDCR) &
                                       ~(SYSCTL_WDCR_WDPS_M)) | regVal;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the watchdog counter value.
//!
//! \return Returns the current value of the 8-bit watchdog counter. If this
//! count value overflows, a watchdog output pulse is generated.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getWatchdogCounterValue(void)
{
    //
    // Read and return the value of the watchdog counter.
    //
    return(HWREGH(WDT_BASE + SYSCTL_O_WDCNTR));
}

//*****************************************************************************
//
//! Gets the watchdog reset status.
//!
//! This function returns the watchdog reset status. If this function returns
//! \b true, that indicates that a watchdog reset generated the last reset
//! condition. Otherwise, it was an external device or power-up reset
//! condition.
//!
//! \return Returns \b true if the watchdog generated the last reset condition.
//
//*****************************************************************************
static inline bool
SysCtl_getWatchdogResetStatus(void)
{
    //
    // Read and return the status of the watchdog reset status flag.
    //
    return((HWREGH(CPUSYS_BASE + SYSCTL_O_RESC) & SYSCTL_RESC_WDRSN) != 0U);
}


//*****************************************************************************
//
//! Clears the watchdog reset status.
//!
//! This function clears the watchdog reset status. To check if it was set
//! first, see SysCtl_getWatchdogResetStatus().
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearWatchdogResetStatus(void)
{
    WRPRT_DISABLE;

    //
    // Read and return the status of the watchdog reset status flag.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_RESCCLR) = SYSCTL_RESCCLR_WDRSN;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the minimum threshold value for windowed watchdog
//!
//! \param value is the value to set the window threshold
//!
//! This function sets the minimum threshold value used to define the lower
//! limit of the windowed watchdog functionality.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogWindowValue(uint16_t value)
{
    WRPRT_DISABLE;

    //
    // Clear the windowed value
    //
    HWREGH(WDT_BASE + SYSCTL_O_WDWCR) &= ~SYSCTL_WDWCR_MIN_M;

    //
    // Set the windowed value
    //
    HWREGH(WDT_BASE + SYSCTL_O_WDWCR) |= (value & SYSCTL_WDWCR_MIN_M);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Clears the watchdog override.
//!
//! This function clears the watchdog override and locks the watchdog timer
//! module to remain in its prior state which could be either enable /disable.
//! The watchdog timer will remain in this state until the next system reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearWatchdogOverride(void)
{
    WRPRT_DISABLE;

    HWREGH(WDT_BASE + SYSCTL_O_SCSR) |= SYSCTL_SCSR_WDOVERRIDE;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable the NMI Global interrupt bit
//!
//! \b Note: This bit should be set after the device security related
//! initialization is complete.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableNMIGlobalInterrupt(void)
{
    WRPRT_DISABLE;

    HWREGH(NMI_BASE + NMI_O_CFG) |= NMI_CFG_NMIE;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Read NMI interrupts.
//!
//! Read the current state of NMI interrupt.
//!
//! \return \b true if NMI interrupt is triggered, \b false if not.
//
//*****************************************************************************
static inline bool
SysCtl_getNMIStatus(void)
{
    //
    // Read and return the current value of the NMI flag register, masking out
    // all but the NMI bit.
    //
    return((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_NMIINT) != 0U);
}

//*****************************************************************************
//
//! Read NMI Flags.
//!
//! Read the current state of individual NMI interrupts
//!
//! \return Value of NMIFLG register. These defines are provided to decode
//! the value:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//
//*****************************************************************************
static inline uint16_t
SysCtl_getNMIFlagStatus(void)
{
    //
    // Read and return the current value of the NMI flag register.
    //
    return(HWREGH(NMI_BASE + NMI_O_FLG));
}

//*****************************************************************************
//
//! Check if the individual NMI interrupts are set.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//!
//! Check if interrupt flags corresponding to the passed in bit mask are
//! asserted.
//!
//! \return \b true if any of the NMI asked for in the parameter bit mask
//! is set. \b false if none of the NMI requested in the parameter bit mask are
//! set.
//
//*****************************************************************************
static inline bool
SysCtl_isNMIFlagSet(uint16_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(
                     SYSCTL_NMI_NMIINT        |
                     SYSCTL_NMI_CLOCKFAIL     |
                     SYSCTL_NMI_FLUNCERR      |
                     SYSCTL_NMI_FLBNMI        |
                     SYSCTL_NMI_SWERR
                     )) == 0U);

    //
    // Read the flag register and return true if any of them are set.
    //
    return((HWREGH(NMI_BASE + NMI_O_FLG) & nmiFlags) != 0U);
}

//*****************************************************************************
//
//! Function to clear individual NMI interrupts.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//!
//! Clear NMI interrupt flags that correspond with the passed in bit mask.
//!
//! \b Note: The NMI Interrupt flag is always cleared by default and
//! therefore doesn't have to be included in the bit mask.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearNMIStatus(uint16_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(
                        SYSCTL_NMI_NMIINT        |
                        SYSCTL_NMI_CLOCKFAIL     |
                        SYSCTL_NMI_FLUNCERR      |
                        SYSCTL_NMI_FLBNMI        |
                        SYSCTL_NMI_SWERR
                        )) == 0U);

    WRPRT_DISABLE;

    //
    // Clear the individual flags as well as NMI Interrupt flag
    //
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = nmiFlags;
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_NMIINT;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Clear all the NMI Flags that are currently set.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearAllNMIFlags(void)
{
    uint16_t nmiFlags;

    //
    // Read the flag status register and then write to the clear register,
    // clearing all the flags that were returned plus the NMI flag.
    //
    WRPRT_DISABLE;

    nmiFlags = SysCtl_getNMIFlagStatus();
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = nmiFlags;
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_NMIINT;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Function to force individual NMI interrupt fail flags
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_forceNMIFlags(uint16_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(
                        SYSCTL_NMI_NMIINT        |
                        SYSCTL_NMI_CLOCKFAIL     |
                        SYSCTL_NMI_FLUNCERR      |
                        SYSCTL_NMI_FLBNMI        |
                        SYSCTL_NMI_SWERR
                       )) == 0U);

    WRPRT_DISABLE;

    //
    // Set the Flags for the individual interrupts in the NMI flag
    // force register
    //
    HWREGH(NMI_BASE + NMI_O_FLGFRC) |= nmiFlags;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the NMI watchdog counter value.
//!
//! \b Note: The counter is clocked at the SYSCLKOUT rate.
//!
//! \return Returns the NMI watchdog counter register's current value.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getNMIWatchdogCounter(void)
{
    //
    // Read and return the NMI watchdog counter register's value.
    //
    return(HWREGH(NMI_BASE + NMI_O_WDCNT));
}

//*****************************************************************************
//
//! Sets the NMI watchdog period value.
//!
//! \param wdPeriod is the 16-bit value at which a reset is generated.
//!
//! This function writes to the NMI watchdog period register that holds the
//! value to which the NMI watchdog counter is compared. When the two registers
//! match, a reset is generated. By default, the period is 0xFFFF.
//!
//! \note If a value smaller than the current counter value is passed into the
//! \e wdPeriod parameter, a NMIRSn will be forced.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setNMIWatchdogPeriod(uint16_t wdPeriod)
{
    WRPRT_DISABLE;

    //
    // Write to the period register.
    //
    HWREGH(NMI_BASE + NMI_O_WDPRD) = wdPeriod;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Gets the NMI watchdog period value.
//!
//! \return Returns the NMI watchdog period register's current value.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getNMIWatchdogPeriod(void)
{
    //
    // Read and return the NMI watchdog period register's value.
    //
    return(HWREGH(NMI_BASE + NMI_O_WDPRD));
}

//*****************************************************************************
//
//! Read NMI Shadow Flags.
//!
//! Read the current state of individual NMI interrupts
//!
//! \return Value of NMISHFLG register. These defines are provided to decode
//! the value:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//
//*****************************************************************************
static inline uint32_t
SysCtl_getNMIShadowFlagStatus(void)
{
    //
    // Read and return the current value of the NMI shadow flag register.
    //
    return(HWREGH(NMI_BASE + NMI_O_SHDFLG));
}

//*****************************************************************************
//
//! Check if the individual NMI shadow flags are set.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants  to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT        -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL     -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_FLUNCERR      -  Flash Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_FLBNMI        -  Configurable Logic Block NMI Flag
//! - \b SYSCTL_NMI_SWERR         -  SW Error Force NMI Flag
//!
//! Check if interrupt flags corresponding to the passed in bit mask are
//! asserted.
//!
//! \return \b true if any of the NMI asked for in the parameter bit mask
//! is set. \b false if none of the NMI requested in the parameter bit mask are
//! set.
//
//*****************************************************************************
static inline bool
SysCtl_isNMIShadowFlagSet(uint16_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(
                         SYSCTL_NMI_NMIINT        |
                         SYSCTL_NMI_CLOCKFAIL       |
                         SYSCTL_NMI_FLUNCERR      |
                         SYSCTL_NMI_FLBNMI        |
                         SYSCTL_NMI_SWERR
                        )) == 0U);

    //
    // Read the flag register and return true if any of them are set.
    //
    return((HWREGH(NMI_BASE + NMI_O_SHDFLG) & nmiFlags) != 0U);
}

//*****************************************************************************
//
//! Enable the missing clock detection (MCD) Logic
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableMCD(void)
{
    WRPRT_DISABLE;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) &= ~(SYSCTL_MCDCR_MCLKOFF);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable the missing clock detection (MCD) Logic
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableMCD(void)
{
    WRPRT_DISABLE;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_MCLKOFF;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Get the missing clock detection Failure Status
//!
//! \note A failure means the oscillator clock is missing
//!
//! \return Returns \b true if a failure is detected or \b false if a
//! failure isn't detected
//
//*****************************************************************************
static inline bool
SysCtl_isMCDClockFailureDetected(void)
{
    //
    //  Check the status bit to determine failure
    //
    return((HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) & SYSCTL_MCDCR_MCLKSTS) != 0U);
}

//*****************************************************************************
//
//! Reset the missing clock detection logic after clock failure
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_resetMCD(void)
{
    WRPRT_DISABLE;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_MCLKCLR;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Re-connect missing clock detection clock source to stop simulating clock
//! failure
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_connectMCDClockSource(void)
{
    WRPRT_DISABLE;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) &= ~(SYSCTL_MCDCR_OSCOFF);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disconnect missing clock detection clock source to simulate clock failure.
//! This is for testing the MCD functionality.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disconnectMCDClockSource(void)
{
    WRPRT_DISABLE;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_OSCOFF;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Lock the Access Control Registers
//!
//! This function locks the access control registers and puts them in a
//! read-only state.
//!
//! \note Only a reset can unlock the access control registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_lockAccessControlRegs(void)
{
    WRPRT_DISABLE;

    HWREGH(PERIPHAC_BASE + SYSCTL_O_PERIPH_AC_LOCK) |=
        SYSCTL_PERIPH_AC_LOCK_LOCK_AC_WR;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the peripheral access control permissions
//!
//! \param peripheral is the selected peripheral
//! \param master is the selected master (CPU0, CPU1, or DMA1)
//! \param permission is the selected access permissions
//!
//! This function sets the specified peripheral access control permissions for
//! the the specified master (CPU0, CPU1, or DMA1)
//!
//! The \e peripheral parameter can have one enumerated value in the format of
//! \b SYSCTL_ACCESS_X where X is the name of the peripheral instance to be
//! configured such as \b SYSCTL_ACCESS_ADCA.
//!
//! The \e master parameter can have one the following enumerated values:
//! - \b SYSCTL_ACCESS_CPU0 - CPU0 Master
//! - \b SYSCTL_ACCESS_CPU1 - CPU1 Master
//! - \b SYSCTL_ACCESS_DMA1 - DMA1 Master
//!
//! The \e permission parameter can have one the following enumerated values:
//! - \b SYSCTL_ACCESS_FULL      - Full Access for both read and write
//! - \b SYSCTL_ACCESS_PROTECTED - Protected read access such that FIFOs, clear
//!                                on read registers are not changed, and no
//!                                write access
//! - \b SYSCTL_ACCESS_NONE      - No read or write access
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setPeripheralAccessControl(SysCtl_AccessPeripheral peripheral,
                                  SysCtl_AccessMaster master,
                                  SysCtl_AccessPermission permission)
{
    //
    // Set master permissions for specified peripheral. Each master has
    // two bits dedicated to its permission setting.
    //
    WRPRT_DISABLE;

    HWREG(PERIPHAC_BASE + (uint16_t)peripheral * 2) =
        (HWREG(PERIPHAC_BASE + (uint16_t)peripheral * 2) &
         ~(0x3U << (uint16_t)master)) |
        ((uint16_t)permission << (uint16_t)master);

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Get the peripheral access control permissions
//!
//! \param peripheral is the selected peripheral
//! \param master is the selected master (CPU0, CPU1, or DMA1)
//!
//! This function gets the specified peripheral access control permissions for
//! the the specified master (CPU0, CPU1, or DMA1)
//!
//! The \e peripheral parameter can have one enumerated value in the format of
//! \b SYSCTL_ACCESS_X where X is the name of the peripheral instance to be
//! configured such as \b SYSCTL_ACCESS_ADCA.
//!
//! The \e master parameter can have one the following enumerated values:
//! - \b SYSCTL_ACCESS_CPU0 - CPU0 Master
//! - \b SYSCTL_ACCESS_CPU1 - CPU1 Master
//! - \b SYSCTL_ACCESS_DMA1 - DMA1 Master
//!
//! \return Returns one of the following enumerated permission values:
//! - \b SYSCTL_ACCESS_FULL      - Full Access for both read and write
//! - \b SYSCTL_ACCESS_PROTECTED - Protected read access such that FIFOs, clear
//!                                on read registers are not changed, and no
//!                                write access
//! - \b SYSCTL_ACCESS_NONE      - No read or write access
//
//*****************************************************************************
static inline uint16_t
SysCtl_getPeripheralAccessControl(SysCtl_AccessPeripheral peripheral,
                                  SysCtl_AccessMaster master)
{
    //
    // Read master permissions for specified peripheral. Each master has
    // two bits dedicated to its permission setting.
    //
    return((HWREG(PERIPHAC_BASE + (uint16_t)peripheral * 2) >> (uint16_t)master) & 0x3U);
}

//*****************************************************************************
//
//! Configures the sync input source for the PWM and CAP signals.
//!
//! \param syncInput is the sync input being configured
//! \param syncSrc is sync input source selection.
//!
//! This function configures the sync input source for the PWM and CAP
//! modules. The \e syncInput parameter is the sync input being configured. It
//! should be passed a value of \b SYSCTL_SYNC_IN_XXXX, where XXXX is the PWM
//! or CAP instance the sync signal is entering.
//!
//! The \e syncSrc parameter is the sync signal selected as the source of the
//! sync input. It should be passed a value of \b SYSCTL_SYNC_IN_SRC_XXXX,
//! XXXX is a sync signal coming from an PWM, CAP or external sync output.
//! where For example, a \e syncInput value of \b SYSCTL_SYNC_IN_CAP1 and a
//! \e syncSrc value of \b SYSCTL_SYNC_IN_SRC_PWM1SYNCOUT will make the
//! PWM1SYNCOUT signal drive CAP1's SYNCIN signal.
//!
//! Note that some \e syncSrc values are only valid for certain values of
//! \e syncInput. See device technical reference manual for details on
//! time-base counter synchronization.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setSyncInputConfig(SysCtl_SyncInput syncInput,
                          SysCtl_SyncInputSource syncSrc)
{
    uint32_t clearMask;

    //
    // Write the input sync source selection to the appropriate register.
    //
    WRPRT_DISABLE;
    if(syncInput == SYSCTL_SYNC_IN_PWM1)
    {
        //
        // Note that EXTSYNCIN1 is the only valid option for PWM1
        //
        HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT) &=
            ~SYSCTL_SYNCSELECT_PWM1SYNCIN_M;
    }
    else
    {
        clearMask = (uint32_t)SYSCTL_SYNCSELECT_SYNCIN_M <<
                    (uint32_t)syncInput;

        HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT) =
            (HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT) & ~clearMask) |
            ((uint32_t)syncSrc << (uint32_t)syncInput);
    }

    WRPRT_ENABLE;
}
//*****************************************************************************
//
//! Configures the sync output source.
//!
//! \param syncSrc is sync output source selection.
//!
//! This function configures the sync output source from the PWM modules. The
//! \e syncSrc parameter is a value \b SYSCTL_SYNC_OUT_SRC_XXXX, where XXXX is
//! a sync signal coming from an PWM such as SYSCTL_SYNC_OUT_SRC_PWM1SYNCOUT
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setSyncOutputConfig(SysCtl_SyncOutputSource syncSrc)
{
    //
    // Write the sync output source selection to the appropriate register.
    //
    WRPRT_DISABLE;
    HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT) =
        (HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT) &
         ~((uint32_t)SYSCTL_SYNCSELECT_SYNCOUT_M)) |
        ((uint32_t)syncSrc << SYSCTL_SYNCSELECT_SYNCOUT_S);
    WRPRT_ENABLE;

}
//*****************************************************************************
//
//! Enables PWM SOC signals to drive an external (off-chip) ADCSOC signal.
//!
//! \param adcsocSrc is a bit field of the selected signals to be enabled
//!
//! This function configures which PWM SOC signals are enabled as a source for
//! either ADCSOCAO or ADCSOCBO. The \e adcsocSrc parameter takes a logical OR
//! of \b SYSCTL_ADCSOC_SRC_PWMxSOCA/B values that correspond to different
//! signals.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableExtADCSOCSource(uint32_t adcsocSrc)
{
    //
    // Set the bits that correspond to signal to be enabled.
    //
    WRPRT_DISABLE;
    HWREG(SYNCSOC_BASE + SYSCTL_O_ADCSOCOUTSELECT) |= adcsocSrc;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disables PWM SOC signals from driving an external ADCSOC signal.
//!
//! \param adcsocSrc is a bit field of the selected signals to be disabled
//!
//! This function configures which PWM SOC signals are disabled as a source
//! for either ADCSOCAO or ADCSOCBO. The \e adcsocSrc parameter takes a logical
//! OR of \b SYSCTL_ADCSOC_SRC_PWMxSOCA/B values that correspond to different
//! signals.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableExtADCSOCSource(uint32_t adcsocSrc)
{
    //
    // Clear the bits that correspond to signal to be disabled.
    //
    WRPRT_DISABLE;
    HWREG(SYNCSOC_BASE + SYSCTL_O_ADCSOCOUTSELECT) &= ~adcsocSrc;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks the SOC Select of the Trig X-BAR.
//!
//! This function locks the external ADC SOC select of the Trig X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_lockExtADCSOCSelect(void)
{
    //
    // Lock the EADCSOCSEL bit of the SESOCLSEL register.
    //
    WRPRT_DISABLE;
    HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSOCLOCK) =
        SYSCTL_SYNCSOCLOCK_ADCSOCOUTSELECT;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Locks the Sync Select of the Trig X-BAR.
//!
//! This function locks Sync Input and Output Select of the Trig X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_lockSyncSelect(void)
{
    //
    // Lock the SYNCIOSEL register.
    //
    WRPRT_DISABLE;
    HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSOCLOCK) = SYSCTL_SYNCSOCLOCK_SYNCSELECT;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Get the Device Silicon Revision ID
//!
//! This function returns the silicon revision ID for the device.
//!
//! \note This API is applicable only for the CPU1 subsystem.
//!
//! \return Returns the silicon revision ID value.
//
//*****************************************************************************
static inline uint32_t
SysCtl_getDeviceRevision(void)
{
    //
    // Returns the device silicon revision ID
    //
    return(HWREG(DEVCFG_BASE + SYSCTL_O_REVID));
}

//*****************************************************************************
//
//! Sets up XCLK divider.
//!
//! \param divider is the value that configures the divider.
//!
//! This function sets up the XCLK divider. There is only one
//! divider that scales INTOSC1 to XCLK.
//!
//! The \e divider parameter can have one enumerated value from
//! SysCtl_XClkDivider
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setXClk(SysCtl_XClkDivider divider)
{
    //
    // Clears the divider then configures it.
    //
    WRPRT_DISABLE;
    HWREGH(CLKCFG_BASE + SYSCTL_O_XCLKOUTDIVSEL) =
                        (HWREGH(CLKCFG_BASE + SYSCTL_O_XCLKOUTDIVSEL) &
                         ~(SYSCTL_XCLKOUTDIVSEL_XCLKOUTDIV_M)) |
                        (uint16_t)divider;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets up PLLSYSCLK divider.
//!
//! \param divider is the value that configures the divider.
//!
//! This function sets up the PLLSYSCLK divider. There is only one
//! divider that scales PLLSYSCLK to generate the system clock.
//!
//! The \e divider parameter can have one value from the set below:
//!     0x0 = /1
//!     0x1 = /2
//!     0x2 = /4 (default on reset)
//!     0x3 = /6
//!     0x4 = /8
//!    ......
//!     0x3F =/126
//!
//! \return None.
//!
//! \note Please make sure to check if the PLL is locked and valid using the
//! SysCtl_isPLLValid() before setting the divider.
//
//*****************************************************************************
static inline void
SysCtl_setPLLSysClk(uint16_t divider)
{
    //
    // Clears the divider then configures it.
    //
    WRPRT_DISABLE;
    HWREGH(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) =
                    (HWREGH(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) &
                     ~(SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M)) | divider;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets up CPU Timer 2  CLK source & divider.
//!
//! \param divider is the value that configures the divider.
//! \param source is the source for the clock divider
//!
//! This function sets up the CPU Timer 2 CLK divider based on the source that
//! is selected. There is only one divider that scales the "source" to
//! CPU Timer 2 CLK.
//!
//! The \e divider parameter can have one enumerated value from
//! SysCtl_Timer2ClkDivider
//! The \e source parameter can have one enumerated value from
//! SysCtl_Timer2ClkSource
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setCputimer2Clk(SysCtl_Timer2ClkDivider divider,
                               SysCtl_Timer2ClkSource source)
{
    //
    // Clears the divider & the source, then configures it.
    //
    WRPRT_DISABLE;
    HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) =
                    (HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) &
                     ~(SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_M |
                       SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_M));

    HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) |=
                    ((uint16_t)divider << SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_S) |
                    ((uint16_t)source << SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_S);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Sets the CPU1 boot address.
//!
//! \param cpu1Address is CPU1 boot address.
//!
//! This function sets the CPU1 boot address configuration.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setCPU1BootAddress(uint32_t cpu1Address)
{
    WRPRT_DISABLE;
    
    HWREG(SYSCTL_BASE + SYSCTL_O_BOOTADDR1) = cpu1Address;
    
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enables CPU1 to boot.
//!
//! This function will set to allow CPU1 to boot.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableBootCPU1(void)
{
    WRPRT_DISABLE;
    
    HWREG(SYSCTL_BASE + SYSCTL_O_BOOTCTRL) |= SYSCTL_BOOTCTRL_BOOTCTRL1;
    
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Delays for a fixed number of cycles.
//!
//! \param count is the number of delay loop iterations to perform.
//!
//! This function generates a constant length delay using assembly code. The
//! loop takes 5 cycles per iteration plus 9 cycles of overhead.
//!
//! \note If count is equal to zero, the loop will underflow and run for a
//! very long time.
//!
//! \note Refer to the macro DEVICE_DELAY_US(x) in device.h which can be used to
//! insert a delay in microseconds.
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_delay(uint32_t count);

//*****************************************************************************
//
//! Calculates the system clock frequency (SYSCLK).
//!
//! Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
//! SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//!
//! \param clockInHz is the frequency of the oscillator clock source (OSCCLK).
//!
//! This function determines the frequency of the system clock based on the
//! frequency of the oscillator clock source (from \e clockInHz) and the PLL
//! and clock divider configuration registers.
//!
//! \return Returns the system clock frequency. If a missing clock is detected,
//! the function will return the INTOSC1 frequency. This needs to be
//! corrected and cleared (see SysCtl_resetMCD()) before trying to call this
//! function again.
//
//*****************************************************************************
extern uint32_t
SysCtl_getClock(uint32_t clockInHz);

//*****************************************************************************
//
//! Configures the clocking of the device.
//!
//! Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
//! SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//!
//! \param config is the required configuration of the device clocking.
//!
//! This function configures the clocking of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! The \e config parameter is the OR of several different values, many of
//! which are grouped into sets where only one can be chosen.
//!
//! - The system clock divider is chosen with the macro \b SYSCTL_SYSDIV(x)
//!   where x is either 1 or an even value up to 126.
//!
//! - The use of the PLL is chosen with either \b SYSCTL_PLL_ENABLE or
//!   \b SYSCTL_PLL_DISABLE.
//!
//! - The integer multiplier is chosen \b SYSCTL_IMULT(x) where x is a value
//!   from 1 to 127.
//!
//! - The fractional multiplier is chosen with either \b SYSCTL_FMULT_0,
//!   \b SYSCTL_FMULT_1_4, \b SYSCTL_FMULT_1_2, or \b SYSCTL_FMULT_3_4.
//!
//! - The oscillator source chosen with \b SYSCTL_OSCSRC_OSC2,
//!   \b SYSCTL_OSCSRC_XTAL, \b SYSCTL_OSCSRC_XTAL_SE or \b SYSCTL_OSCSRC_OSC1.
//!
//! This function uses the DCCOMP to check that the PLLRAWCLK is running at the
//! expected rate. If you are using the DCCOMP, you must back up its configuration
//! before calling this function and restore it afterward.
//! Locking PLL sequence is only done if the multipliers are updated.
//!
//! \note See your device errata for more details about locking the PLL.
//!
//! \return Returns \b false if a missing clock error is detected. This needs
//! to be cleared (see SysCtl_resetMCD()) before trying to call this function
//! again. Also, returns \b false if the PLLRAWCLK is not running and its
//! expected rate after \b SYSCTL_PLL_RETRIES retries. Otherwise, returns
//! \b true.
//
//*****************************************************************************
extern bool
SysCtl_setClock(uint32_t config);

//*****************************************************************************
//
//! Validates PLL Raw Clock Frequency (PLLRAWCLK)
//!
//! \param oscSource is the Clock Source for the PLL that is also used for DCCOMP
//! \param pllMult has the PLL Multiplier Register configuration which include
//!  integer and fractional multiplier used to configure the DCCOMP Counter1 clock
//!
//!  This function uses DCCOMP module to validate the PLL clock frequency.
//!  It uses oscSource as a reference clock for DCCOMP, and PLL is used as clock
//!  under test. As long as the Counter0 (running of oscSource) & Counter1
//!  (running of PLL) expire at the same time, DCCOMP will not generate an Error.
//!  This function gives 100 attempts for PLL to lock and make sure frequency
//!  is as expected.
//!
//!  \note This function does not validate if PLL output frequency (PLLRAWCLK)
//!  is within the operating range as per the datasheet.
//!
//! - The \e oscSource parameter is the oscillator source chosen with
//!   \b SYSCTL_OSCSRC_OSC2, \b SYSCTL_OSCSRC_XTAL, \b SYSCTL_OSCSRC_XTAL_SE
//!    or \b SYSCTL_OSCSRC_OSC1.
//!
//! - The \e pllMult parameter is a bitwise OR of \b SYSCTL_IMULT(x) where x is
//!   a value from 1 to 127 and one of the following fractional values:
//!   \b SYSCTL_FMULT_0, \b SYSCTL_FMULT_1_4, \b SYSCTL_FMULT_1_2, or
//!   \b SYSCTL_FMULT_3_4.
//!
//!  \return Returns \b true if the DCCSTATUS error flag is not set.
//!    Otherwise, returns \b false.
//
//*****************************************************************************
extern bool
SysCtl_isPLLValid(uint32_t oscSource, uint32_t pllMult);

//*****************************************************************************
//
//! Configures the external oscillator for the clocking of the device.
//!
//! This function configures the external oscillator (XTAL) to be used for the
//! clocking of the device in crystal mode. It follows the procedure to turn on
//! the oscillator, wait for it to power up, and select it as the source of the
//! system clock.
//!
//! Please note that this function blocks while it waits for the XTAL to power
//! up. If the XTAL does not manage to power up properly, the function will
//! loop for a long time. It is recommended that you modify this function to
//! add an appropriate timeout and error-handling procedure.
//!
//! Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
//! SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_selectXTAL(void);

//*****************************************************************************
//
//! Configures the external oscillator for the clocking of the device in
//! single-ended mode.
//!
//! This function configures the external oscillator (XTAL) to be used for the
//! clocking of the device in single-ended mode. It follows the procedure to
//! turn on the oscillator, wait for it to power up, and select it as the
//! source of the system clock.
//!
//! Please note that this function blocks while it waits for the XTAL to power
//! up. If the XTAL does not manage to power up properly, the function will
//! loop for a long time. It is recommended that you modify this function to
//! add an appropriate timeout and error-handling procedure.
//!
//! Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
//! SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_selectXTALSingleEnded(void);

//*****************************************************************************
//
//! Selects the oscillator to be used for the clocking of the device.
//!
//! Attention : After modifying the CLKSRCCTL1 register, please reconfigure the 
//! SYSPLLMULT register to prevent abnormal display of the SYSPLLMULT register.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function configures the oscillator to be used in the clocking of the
//! device. The \e oscSource parameter may take a value of
//! \b SYSCTL_OSCSRC_OSC2, \b SYSCTL_OSCSRC_XTAL, \b SYSCTL_OSCSRC_XTAL_SE, or
//! \b SYSCTL_OSCSRC_OSC1.
//!
//! \sa SysCtl_turnOnOsc()
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_selectOscSource(uint32_t oscSource);

//*****************************************************************************
//
//! Calculates the APB peripheral clock frequency (APBCLK).
//!
//! \param clockInHz is the frequency of the oscillator clock source (OSCCLK).
//!
//! This function determines the frequency of the APB peripheral clock
//! based on the frequency of the oscillator clock source (from \e clockInHz)
//! and the PLL and clock divider configuration registers.
//!
//! \return Returns the APB peripheral clock frequency.
//
//*****************************************************************************
uint32_t
SysCtl_getAPBClock(uint32_t clockInHz);

//*****************************************************************************
//
//! Calculates the low-speed peripheral clock frequency (LSPCLK).
//!
//! \param clockInHz is the frequency of the oscillator clock source (OSCCLK).
//!
//! This function determines the frequency of the low-speed peripheral clock
//! based on the frequency of the oscillator clock source (from \e clockInHz)
//! and the PLL and clock divider configuration registers.
//!
//! \return Returns the low-speed peripheral clock frequency.
//
//*****************************************************************************
extern uint32_t
SysCtl_getLowSpeedClock(uint32_t clockInHz);

//*****************************************************************************
//
//! Get the device part parametric value
//!
//! \param parametric is the requested device parametric value
//!
//! This function gets the device part parametric value.
//!
//! The \e parametric parameter can have one the following enumerated values:
//! - \b SYSCTL_DEVICE_QUAL      - Device Qualification Status
//! - \b SYSCTL_DEVICE_PINCOUNT  - Device Pin Count
//! - \b SYSCTL_DEVICE_INSTASPIN - Device InstaSPIN Feature Set
//! - \b SYSCTL_DEVICE_FLASH     - Device Flash size (KB)
//! - \b SYSCTL_DEVICE_FAMILY    - Device Family
//! - \b SYSCTL_DEVICE_PARTNO    - Device Part Number
//! - \b SYSCTL_DEVICE_CLASSID   - Device Class ID
//!
//! \note This API is applicable only for the CPU1 subsystem.
//!
//! \return Returns the specified parametric value.
//
//*****************************************************************************
extern uint16_t
SysCtl_getDeviceParametric(SysCtl_DeviceParametric parametric);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // SYSCTL_H
