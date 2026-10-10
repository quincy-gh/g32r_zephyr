//###########################################################################
//
// FILE:    g32r502.h
//
// TITLE:   CMSIS-Core(M) Peripheral Access Layer Header File for G32R502.
//
// VERSION: 1.0.0
//
// DATE:    2026-06-30
//
//###########################################################################
// $Copyright:
// Copyright (C) 2026 Geehy Semiconductor - http://www.geehy.com/
//
// You may not use this file except in compliance with the
// GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
//
// The program is only for reference, which is distributed in the hope
// that it will be useful and instructional for customers to develop
// their software. Unless required by applicable law or agreed to in
// writing, the program is distributed on an "AS IS" BASIS, WITHOUT
// ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
// See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
// and limitations under the License.
// $
//###########################################################################

#ifndef G32R502_H
#define G32R502_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

#if defined (__G32R502__)

//*****************************************************************************
//
//! \addtogroup CMSIS_Device G32R502
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// G32R5 Library Version
//
//*****************************************************************************
// [31:16] G32R5 Libraries main version V0.1.0
#define __G32R5_VERSION_MAIN   ((uint8_t)0x00) // [31:24] main version
#define __G32R5_VERSION_SUB1   ((uint8_t)0x01) // [23:16] sub1 version
#define __G32R5_VERSION_SUB2   ((uint8_t)0x00) // [15:8]  sub2 version
#define __G32R5_VERSION_RC     ((uint8_t)0x00) // [7:0]   release candidate
#define __G32R5_VERSION        ((__G32R5_VERSION_MAIN << 24)\
                                          |(__G32R5_VERSION_SUB1 << 16)\
                                          |(__G32R5_VERSION_SUB2 << 8)\
                                          |(__G32R5_VERSION_RC))

//*****************************************************************************
//
// Exception / Interrupt Number Definition
//
//*****************************************************************************
typedef enum IRQn
{
    //
    // Exceptions
    //
    NonMaskableInt_IRQn     = -14,   // Non Maskable Interrupt Exception
    HardFault_IRQn          = -13,   // Hard Fault Exception
    MemoryManagement_IRQn   = -12,   // Memory Management Exception
    BusFault_IRQn           = -11,   // Bus Fault Exception
    UsageFault_IRQn         = -10,   // Usage Fault Exception
    SecureFault_IRQn        = -9,    // Secure Fault Exception
    SVCall_IRQn             = -5,    // SV Call Exception
    DebugMonitor_IRQn       = -4,    // Debug Monitor Exception
    PendSV_IRQn             = -2,    // Pend SV Exception
    SysTick_IRQn            = -1,    // System Tick Exception

    //
    // Interrupts
    //
    DCCOMP_IRQn             = 11,    // DCCOMP Interrupt
    TMR1_IRQn               = 13,    // CPU Timer 1 Interrupt
    TMR2_IRQn               = 14,    // CPU Timer 2 Interrupt
    RAM_IRQn                = 16,    // System Memory Interrupt
    ADCA1_IRQn              = 32,    // ADCA Interrupt 1
    ADCC1_IRQn              = 34,    // ADCC Interrupt 1
    TMR0_IRQn               = 38,    // Timer 0 Interrupt
    WWDT_WAKE_IRQn          = 39,    // WWDT interrupt & LPM wakeup Interrupt
    PWM1_TRIP_ZONE_IRQn     = 40,    // PWM1 TRIP ZONE Interrupt
    PWM2_TRIP_ZONE_IRQn     = 41,    // PWM2 TRIP ZONE Interrupt
    PWM3_TRIP_ZONE_IRQn     = 42,    // PWM3 TRIP ZONE Interrupt
    PWM4_TRIP_ZONE_IRQn     = 43,    // PWM4 TRIP ZONE Interrupt
    PWM5_TRIP_ZONE_IRQn     = 44,    // PWM5 TRIP ZONE Interrupt
    PWM6_TRIP_ZONE_IRQn     = 45,    // PWM6 TRIP ZONE Interrupt
    PWM7_TRIP_ZONE_IRQn     = 46,    // PWM7 TRIP ZONE Interrupt
    PWM1_IRQn               = 48,    // PWM1 Interrupt
    PWM2_IRQn               = 49,    // PWM2 Interrupt
    PWM3_IRQn               = 50,    // PWM3 Interrupt
    PWM4_IRQn               = 51,    // PWM4 Interrupt
    PWM5_IRQn               = 52,    // PWM5 Interrupt
    PWM6_IRQn               = 53,    // PWM6 Interrupt
    PWM7_IRQn               = 54,    // PWM7 Interrupt
    CAP1_IRQn               = 56,    // CAP1 Interrupt
    CAP2_IRQn               = 57,    // CAP2 Interrupt
    CAP3_IRQn               = 58,    // CAP3 Interrupt
    QEP1_IRQn               = 64,    // QEP1 Interrupt
    FLB1_IRQn               = 68,    // FLB1 Interrupt
    FLB2_IRQn               = 69,    // FLB2 Interrupt
    FLB3_IRQn               = 70,    // FLB3 Interrupt
    FLB4_IRQn               = 71,    // FLB4 Interrupt
    SPIA_RX_IRQn            = 72,    // SPIA Receive Interrupt
    SPIA_TX_IRQn            = 73,    // SPIA Transmit Interrupt
    DMA_CH1_IRQn            = 80,    // DMA Channel 1 Interrupt
    DMA_CH2_IRQn            = 81,    // DMA Channel 2 Interrupt
    DMA_CH3_IRQn            = 82,    // DMA Channel 3 Interrupt
    DMA_CH4_IRQn            = 83,    // DMA Channel 4 Interrupt
    DMA_CH5_IRQn            = 84,    // DMA Channel 5 Interrupt
    DMA_CH6_IRQn            = 85,    // DMA Channel 6 Interrupt
    I2CA_IRQn               = 88,    // I2CA Interrupt
    I2CA_FIFO_IRQn          = 89,    // I2CA FIFO Interrupt
    I2CB_IRQn               = 91,    // I2CB Interrupt
    I2CB_FIFO_IRQn          = 92,    // I2CB FIFO Interrupt
    UARTA_RX_IRQn           = 96,    // UARTA Receive Interrupt
    UARTA_TX_IRQn           = 97,    // UARTA Transmit Interrupt
    UARTB_RX_IRQn           = 98,    // UARTB Receive Interrupt
    UARTB_TX_IRQn           = 99,    // UARTB Transmit Interrupt
    CANA_INT0_IRQn          = 100,   // CANA INT0
    CANA_INT1_IRQn          = 101,   // CANA INT1
    ADCA_EVENT_IRQn         = 104,   // ADCA EVENT Interrupt
    ADCA2_IRQn              = 105,   // ADCA Interrupt 2
    ADCA3_IRQn              = 106,   // ADCA Interrupt 3
    ADCA4_IRQn              = 107,   // ADCA Interrupt 4
    EXTI_LINE0_IRQn         = 112,   // EXTI LINE0 Interrupt
    EXTI_LINE1_IRQn         = 113,   // EXTI LINE1 Interrupt
    EXTI_LINE2_IRQn         = 114,   // EXTI LINE2 Interrupt
    EXTI_LINE3_IRQn         = 115,   // EXTI LINE3 Interrupt
    EXTI_LINE4_IRQn         = 116,   // EXTI LINE4 Interrupt
    EXTI_LINE5_IRQn         = 117,   // EXTI LINE5 Interrupt
    EXTI_LINE6_IRQn         = 118,   // EXTI LINE6 Interrupt
    EXTI_LINE7_IRQn         = 119,   // EXTI LINE7 Interrupt
    EXTI_LINE8_IRQn         = 120,   // EXTI LINE8 Interrupt
    EXTI_LINE9_IRQn         = 121,   // EXTI LINE9 Interrupt
    EXTI_LINE10_IRQn        = 122,   // EXTI LINE10 Interrupt
    EXTI_LINE11_IRQn        = 123,   // EXTI LINE11 Interrupt
    EXTI_LINE12_IRQn        = 124,   // EXTI LINE12 Interrupt
    FPU_DZC_IRQn            = 129,   // FPU DZC Interrupt
    FPU_IDC_IRQn            = 130,   // FPU IDC Interrupt
    FPU_IOC_IRQn            = 131,   // FPU IOC Interrupt
    FPU_OFC_IRQn            = 132,   // FPU OFC Interrupt
    FPU_UFC_IRQn            = 133,   // FPU UFC Interrupt
    FPU_IXC_IRQn            = 134,   // FPU IXC Interrupt
    CANFDA_INT0_IRQn        = 169,   // CANFDA INT0
    CANFDA_INT1_IRQn        = 170,   // CANFDA INT1
    CANFDA_BEC_INT_IRQn     = 171,   // CANFDA BEC INT
    CANFDA_BEU_INT_IRQn     = 172,   // CANFDA BEU INT
    CANFDA_WAKE_UP_INT_IRQn = 173,   // CANFDA WAKE UP INT
    LINA_INT1_IRQn          = 184,   // LINA INT1
    LINA_INT2_IRQn          = 185,   // LINA INT2
    UARTC_RX_IRQn           = 186,   // UARTC Receive Interrupt
    UARTC_TX_IRQn           = 187,   // UARTC Transmit Interrupt
    PMBUSA_IRQn             = 188,   // PMBUSA Interrupt
    ADCC_EVENT_IRQn         = 200,   // ADCC EVENT Interrupt
    ADCC2_IRQn              = 201,   // ADCC2 Interrupt
    ADCC3_IRQn              = 202,   // ADCC3 Interrupt
    ADCC4_IRQn              = 203,   // ADCC4 Interrupt
    FLASH_ECC_ERR_IRQn      = 218,   // FLASH ECC ERR Interrupt
    SYS_PLL_SLIP_IRQn       = 220,   // System PLL Slip Interrupt
    CTI_INT0_IRQn           = 225,   // CTI INT0
    CTI_INT1_IRQn           = 226    // CTI INT1
} IRQn_Type;

//
// NVIC RAM vector table: 16 system exceptions + 227 external IRQ channels.
// Linker scripts must reserve NVIC_RAM_VECTOR_ALIGN bytes (>= table size).
//
#define NVIC_RAM_VECTOR_SIZE        (16U + 227U)
#define NVIC_RAM_VECTOR_ALIGN       0x400U

//*****************************************************************************
//
// Configuration of Core Peripherals
//
//*****************************************************************************
#define __CM52_REV               0x0001U   // Core revision r0p1
#define __NVIC_PRIO_BITS         4U        // Number of Bits used for Priority Levels
#define __Vendor_SysTickConfig   0U        // Set to 1 if different SysTick Config is used
#define __VTOR_PRESENT           1U        // VTOR present
#define __MPU_PRESENT            1U        // MPU present
#define __FPU_PRESENT            1U        // FPU present
#define __FPU_DP                 0U        // R502 does not support double-precision floating-point
#define __DSP_PRESENT            1U        // DSP extension present
#define __SAUREGION_PRESENT      0U        // SAU regions present
#define __PMU_PRESENT            1U        // PMU present
#define __PMU_NUM_EVENTCNT       8U        // PMU Event Counters
#define __ICACHE_PRESENT         1U        // Instruction Cache present
#define __DCACHE_PRESENT         1U        // Data Cache present
#define __ITCM_PRESENT           1U        // ITCM present
#define __DTCM_PRESENT           1U        // DTCM present

//
// Included files
//
#include "core_cm52.h"
#include "system_g32r502.h"

#include "arm_acle.h"

//
// Exported_types
//
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

//
// Intrinsic prototypes
//
// __wrprt_disable(void)
__STATIC_FORCEINLINE void __wrprt_disable(void)
{
    __DSB();
    __arm_mcr(1, 0, 1, 0, 12, 0);
}

// __wrprt_enable(void)
__STATIC_FORCEINLINE void __wrprt_enable(void)
{
    __DSB();
    __arm_mcr(1, 0, 0, 0, 12, 0);
}

//*****************************************************************************
//
// Peripheral Registers Structures
//
//*****************************************************************************
//
// CLKCFG
//
typedef struct
{
          uint32_t RSVD1[1];        //                    Reserved
    __IOM uint32_t CLKCFGLOCK1;     // Offset: 0x04 (R/W) Lock bit for CLKCFG Register
          uint32_t RSVD2[2];        //                    Reserved
    __IOM uint32_t CLKSRCCTL1;      // Offset: 0x10 (R/W) Clock Source Control Register-1
    __IOM uint32_t CLKSRCCTL2;      // Offset: 0x14 (R/W) Clock Source Control Register-2
    __IOM uint32_t CLKSRCCTL3;      // Offset: 0x18 (R/W) Clock Source Control Register-3
    __IOM uint32_t SYSPLLCTL1;      // Offset: 0x1C (R/W) SYSPLL Control Register-1
          uint32_t RSVD3[2];        //                    Reserved
    __IOM uint32_t SYSPLLMULT;      // Offset: 0x28 (R/W) SYSPLL Multiplier Register
    __IM  uint32_t SYSPLLSTS;       // Offset: 0x2C (R/ ) SYSPLL Status Register
          uint32_t RSVD4[5];        //                    Reserved
    __IOM uint32_t SYSCLKDIVSEL;    // Offset: 0x44 (R/W) System Clock Divider Select Register
          uint32_t RSVD5[2];        //                    Reserved
    __IOM uint32_t XCLKOUTDIVSEL;   // Offset: 0x50 (R/W) XCLKOUT Divider Select Register
          uint32_t RSVD6[1];        //                    Reserved
    __IOM uint32_t LOSPCP;          // Offset: 0x58 (R/W) Low Speed Clock Source Prescalar
    __IOM uint32_t MCDCR;           // Offset: 0x5C (R/W) Missing Clock Detect Control Register
    __IOM uint32_t X1CNT;           // Offset: 0x60 (R/W) 10-bit Counter on X1 Clock
    __IOM uint32_t XTALCR;          // Offset: 0x64 (R/W) XTAL Control Register
} CLKCFG_TypeDef;

//
// Watchdog
//
typedef struct
{
          uint16_t RSVD1[34];   //                    Reserved
    __IOM uint16_t SCSR;        // Offset: 0x44 (R/W) System Control & Status Register
    __IM  uint16_t WDCNTR;      // Offset: 0x46 (R/ ) Watchdog Counter Register
          uint16_t RSVD2[1];    //                    Reserved
    __IOM uint16_t WDKEY;       // Offset: 0x4A (R/W) Watchdog Reset Key Register
          uint16_t RSVD3[3];    //                    Reserved
    __IOM uint16_t WDCR;        // Offset: 0x52 (R/W) Watchdog Control Register
    __IOM uint16_t WDWCR;       // Offset: 0x54 (R/W) Watchdog Windowed Control Register
} WD_TypeDef;

//*****************************************************************************
//
// Peripheral Declaration
//
//*****************************************************************************
#define CLKCFG          ((CLKCFG_TypeDef *)0x40013400U)
#define WD              ((WD_TypeDef     *)0x40010000U)

//*****************************************************************************
//
// Peripheral Registers Bits Definition
//
//*****************************************************************************
//---------------------------------------------------------------------------
// CLKCFG Definitions:
//
// Bit definition for CLKCFG_CLKCFGLOCK1 register
//
#define CLKCFG_CLKCFGLOCK1_CLKSRCCTL1_Pos     (0U)
#define CLKCFG_CLKCFGLOCK1_CLKSRCCTL1_Msk     (0x1U << CLKCFG_CLKCFGLOCK1_CLKSRCCTL1_Pos)
#define CLKCFG_CLKCFGLOCK1_CLKSRCCTL2_Pos     (1U)
#define CLKCFG_CLKCFGLOCK1_CLKSRCCTL2_Msk     (0x1U << CLKCFG_CLKCFGLOCK1_CLKSRCCTL2_Pos)
#define CLKCFG_CLKCFGLOCK1_CLKSRCCTL3_Pos     (2U)
#define CLKCFG_CLKCFGLOCK1_CLKSRCCTL3_Msk     (0x1U << CLKCFG_CLKCFGLOCK1_CLKSRCCTL3_Pos)
#define CLKCFG_CLKCFGLOCK1_SYSPLLCTL1_Pos     (3U)
#define CLKCFG_CLKCFGLOCK1_SYSPLLCTL1_Msk     (0x1U << CLKCFG_CLKCFGLOCK1_SYSPLLCTL1_Pos)
#define CLKCFG_CLKCFGLOCK1_SYSPLLMULT_Pos     (6U)
#define CLKCFG_CLKCFGLOCK1_SYSPLLMULT_Msk     (0x1U << CLKCFG_CLKCFGLOCK1_SYSPLLMULT_Pos)
#define CLKCFG_CLKCFGLOCK1_SYSCLKDIVSEL_Pos   (11U)
#define CLKCFG_CLKCFGLOCK1_SYSCLKDIVSEL_Msk   (0x1U << CLKCFG_CLKCFGLOCK1_SYSCLKDIVSEL_Pos)
#define CLKCFG_CLKCFGLOCK1_LOSPCP_Pos         (15U)
#define CLKCFG_CLKCFGLOCK1_LOSPCP_Msk         (0x1U << CLKCFG_CLKCFGLOCK1_LOSPCP_Pos)
#define CLKCFG_CLKCFGLOCK1_XTALCR_Pos         (16U)
#define CLKCFG_CLKCFGLOCK1_XTALCR_Msk         (0x1U << CLKCFG_CLKCFGLOCK1_XTALCR_Pos)

//
// Bit definition for CLKCFG_CLKSRCCTL1 register
//
#define CLKCFG_CLKSRCCTL1_OSCCLKSRCSEL_Pos   (0U)
#define CLKCFG_CLKSRCCTL1_OSCCLKSRCSEL_Msk   (0x3U << CLKCFG_CLKSRCCTL1_OSCCLKSRCSEL_Pos)
#define CLKCFG_CLKSRCCTL1_INTOSC2OFF_Pos     (3U)
#define CLKCFG_CLKSRCCTL1_INTOSC2OFF_Msk     (0x1U << CLKCFG_CLKSRCCTL1_INTOSC2OFF_Pos)
#define CLKCFG_CLKSRCCTL1_WDHALTI_Pos        (5U)
#define CLKCFG_CLKSRCCTL1_WDHALTI_Msk        (0x1U << CLKCFG_CLKSRCCTL1_WDHALTI_Pos)

//
// Bit definition for CLKCFG_CLKSRCCTL2 register
//
#define CLKCFG_CLKSRCCTL2_CANABCLKSEL_Pos    (2U)
#define CLKCFG_CLKSRCCTL2_CANABCLKSEL_Msk    (0x3U << CLKCFG_CLKSRCCTL2_CANABCLKSEL_Pos)
#define CLKCFG_CLKSRCCTL2_CANFDABCLKSEL_Pos   (4U)
#define CLKCFG_CLKSRCCTL2_CANFDABCLKSEL_Msk   (0x3U << CLKCFG_CLKSRCCTL2_CANFDABCLKSEL_Pos)

//
// Bit definition for CLKCFG_CLKSRCCTL3 register
//
#define CLKCFG_CLKSRCCTL3_XCLKOUTSEL_Pos   (0U)
#define CLKCFG_CLKSRCCTL3_XCLKOUTSEL_Msk   (0x7U << CLKCFG_CLKSRCCTL3_XCLKOUTSEL_Pos)

//
// Bit definition for CLKCFG_SYSPLLCTL1 register
//
#define CLKCFG_SYSPLLCTL1_PLLEN_Pos      (0U)
#define CLKCFG_SYSPLLCTL1_PLLEN_Msk      (0x1U << CLKCFG_SYSPLLCTL1_PLLEN_Pos)
#define CLKCFG_SYSPLLCTL1_PLLCLKEN_Pos   (1U)
#define CLKCFG_SYSPLLCTL1_PLLCLKEN_Msk   (0x1U << CLKCFG_SYSPLLCTL1_PLLCLKEN_Pos)

//
// Bit definition for CLKCFG_SYSPLLMULT register
//
#define CLKCFG_SYSPLLMULT_IMULT_Pos   (0U)
#define CLKCFG_SYSPLLMULT_IMULT_Msk   (0x7FU << CLKCFG_SYSPLLMULT_IMULT_Pos)
#define CLKCFG_SYSPLLMULT_FMULT_Pos   (8U)
#define CLKCFG_SYSPLLMULT_FMULT_Msk   (0x3U << CLKCFG_SYSPLLMULT_FMULT_Pos)
#define CLKCFG_SYSPLLMULT_ODIV_Pos    (16U)
#define CLKCFG_SYSPLLMULT_ODIV_Msk    (0x7U << CLKCFG_SYSPLLMULT_ODIV_Pos)

//
// Bit definition for CLKCFG_SYSPLLSTS register
//
#define CLKCFG_SYSPLLSTS_LOCKS_Pos   (0U)
#define CLKCFG_SYSPLLSTS_LOCKS_Msk   (0x1U << CLKCFG_SYSPLLSTS_LOCKS_Pos)
#define CLKCFG_SYSPLLSTS_SLIPS_Pos   (1U)
#define CLKCFG_SYSPLLSTS_SLIPS_Msk   (0x1U << CLKCFG_SYSPLLSTS_SLIPS_Pos)

//
// Bit definition for CLKCFG_SYSCLKDIVSEL register
//
#define CLKCFG_SYSCLKDIVSEL_PLLSYSCLKDIV_Pos   (0U)
#define CLKCFG_SYSCLKDIVSEL_PLLSYSCLKDIV_Msk   (0x3FU << CLKCFG_SYSCLKDIVSEL_PLLSYSCLKDIV_Pos)

//
// Bit definition for CLKCFG_XCLKOUTDIVSEL register
//
#define CLKCFG_XCLKOUTDIVSEL_XCLKOUTDIV_Pos   (0U)
#define CLKCFG_XCLKOUTDIVSEL_XCLKOUTDIV_Msk   (0x3U << CLKCFG_XCLKOUTDIVSEL_XCLKOUTDIV_Pos)

//
// Bit definition for CLKCFG_LOSPCP register
//
#define CLKCFG_LOSPCP_LSPCLKDIV_Pos   (0U)
#define CLKCFG_LOSPCP_LSPCLKDIV_Msk   (0x7U << CLKCFG_LOSPCP_LSPCLKDIV_Pos)

//
// Bit definition for CLKCFG_MCDCR register
//
#define CLKCFG_MCDCR_MCLKSTS_Pos   (0U)
#define CLKCFG_MCDCR_MCLKSTS_Msk   (0x1U << CLKCFG_MCDCR_MCLKSTS_Pos)
#define CLKCFG_MCDCR_MCLKCLR_Pos   (1U)
#define CLKCFG_MCDCR_MCLKCLR_Msk   (0x1U << CLKCFG_MCDCR_MCLKCLR_Pos)
#define CLKCFG_MCDCR_MCLKOFF_Pos   (2U)
#define CLKCFG_MCDCR_MCLKOFF_Msk   (0x1U << CLKCFG_MCDCR_MCLKOFF_Pos)
#define CLKCFG_MCDCR_OSCOFF_Pos    (3U)
#define CLKCFG_MCDCR_OSCOFF_Msk    (0x1U << CLKCFG_MCDCR_OSCOFF_Pos)

//
// Bit definition for CLKCFG_X1CNT register
//
#define CLKCFG_X1CNT_X1CNT_Pos   (0U)
#define CLKCFG_X1CNT_X1CNT_Msk   (0x3FFU << CLKCFG_X1CNT_X1CNT_Pos)
#define CLKCFG_X1CNT_CLR_Pos     (16U)
#define CLKCFG_X1CNT_CLR_Msk     (0x1U << CLKCFG_X1CNT_CLR_Pos)

//
// Bit definition for CLKCFG_XTALCR register
//
#define CLKCFG_XTALCR_OSCOFF_Pos   (0U)
#define CLKCFG_XTALCR_OSCOFF_Msk   (0x1U << CLKCFG_XTALCR_OSCOFF_Pos)
#define CLKCFG_XTALCR_SE_Pos       (1U)
#define CLKCFG_XTALCR_SE_Msk       (0x1U << CLKCFG_XTALCR_SE_Pos)

//---------------------------------------------------------------------------
// WD Definitions:
//
// Bit definition for WD_SCSR register
//
#define WD_SCSR_WDOVERRIDE_Pos   (0U)
#define WD_SCSR_WDOVERRIDE_Msk   (0x1U << WD_SCSR_WDOVERRIDE_Pos)
#define WD_SCSR_WDENINT_Pos      (1U)
#define WD_SCSR_WDENINT_Msk      (0x1U << WD_SCSR_WDENINT_Pos)
#define WD_SCSR_WDINTS_Pos       (2U)
#define WD_SCSR_WDINTS_Msk       (0x1U << WD_SCSR_WDINTS_Pos)

//
// Bit definition for WD_WDCNTR register
//
#define WD_WDCNTR_WDCNTR_Pos   (0U)
#define WD_WDCNTR_WDCNTR_Msk   (0xFFU << WD_WDCNTR_WDCNTR_Pos)

//
// Bit definition for WD_WDKEY register
//
#define WD_WDKEY_WDKEY_Pos   (0U)
#define WD_WDKEY_WDKEY_Msk   (0xFFU << WD_WDKEY_WDKEY_Pos)

//
// Bit definition for WD_WDCR register
//
#define WD_WDCR_WDPS_Pos          (0U)
#define WD_WDCR_WDPS_Msk          (0x7U << WD_WDCR_WDPS_Pos)
#define WD_WDCR_WDCHK_Pos         (3U)
#define WD_WDCR_WDCHK_Msk         (0x7U << WD_WDCR_WDCHK_Pos)
#define WD_WDCR_WDDIS_Pos         (6U)
#define WD_WDCR_WDDIS_Msk         (0x1U << WD_WDCR_WDDIS_Pos)
#define WD_WDCR_WDPRECLKDIV_Pos   (8U)
#define WD_WDCR_WDPRECLKDIV_Msk   (0xFU << WD_WDCR_WDPRECLKDIV_Pos)

//
// Bit definition for WD_WDWCR register
//
#define WD_WDWCR_MIN_Pos   (0U)
#define WD_WDWCR_MIN_Msk   (0xFFU << WD_WDWCR_MIN_Pos)


// Define a macro to control optimization behavior for different compilers
// This macro ensures that the specified variable is not optimized by the compiler.
// Usage:
// - Use this macro before variable declarations to disable optimizations for that variable.
// - This is useful for debugging or when specific timing is required.

// For IAR Compiler (ICCARM)
#if defined (__ICCARM__)
  #define NO_OPTIMIZE_VAR __root

// For ARM Compiler (CC_ARM) or MDK
#elif defined (__CC_ARM) || defined (__ARMCC_VERSION) || defined (__GNUC__) || defined (__clang__)
  #define NO_OPTIMIZE_VAR __attribute__((used))

// Error if no suitable compiler is detected
#else
  #error "Unsupported compiler: NO_OPTIMIZE_VAR macro cannot be defined."
#endif

// Define a macro to control optimization behavior for different compilers
// This macro ensures that the specified function is not optimized by the compiler.
// Usage:
// - Use this macro before function declarations to disable optimizations for that function.
// - This is useful for debugging or when specific timing is required.

// For ARM Compiler (CC_ARM) or IAR Compiler (ICCARM)
#if defined (__CC_ARM) || defined (__ICCARM__)
  #define NO_OPTIMIZE _Pragma("optimize=none")

// ARM Compiler 6 accepts optnone. GCC 15 ignores it
// ("optnone attribute directive ignored"), so force -O0 there.
// __clang__ is tested first because armclang also defines __GNUC__.
#elif defined (__clang__) || defined (__ARMCC_VERSION)
  #define NO_OPTIMIZE __attribute__((optnone))
#elif defined (__GNUC__)
  #define NO_OPTIMIZE __attribute__((optimize("O0"), noinline))

// Error if no suitable compiler is detected
#else
  #error "Unsupported compiler: NO_OPTIMIZE macro cannot be defined."
#endif


// Define macros to place functions or variables in specific memory sections
// Usage:
// - Use these macros before function declarations or variable definitions to place them in specific sections.
// - Ensure that the linker script (MDK) or ICF file (IAR), or LD script (GCC) includes the corresponding sections.

#if defined (__CC_ARM) || defined (__ICCARM__) || defined (__GNUC__) || defined (__ARMCC_VERSION)
  #define SECTION_ITCM_INSTRUCTION  __attribute__((section("itcm.instruction")))
  #define SECTION_ITCM_RAMFUNC      __attribute__((section("itcm.ramfunc")))
  #define SECTION_DTCM_DATA         __attribute__((section("dtcm.data")))
  #define SECTION_DTCM_BSS          __attribute__((section("dtcm.bss")))
#if defined (__clang__) && !defined (__ARMCC_VERSION)
  #define SECTION_RAM_VEC           __attribute__((section("ram.intvec")))
#else
  #define SECTION_RAM_VEC           __attribute__((section(".bss.ram.intvec")))
#endif
#else
  #error "Unsupported compiler: no section macros can be defined."
#endif

#define DTCM_BOOT_STATUS_BASE       (0x20000000UL)
#define DTCM_BOOT_STATUS_SIZE       (0x14U)

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#else // UNKONW DEVICE
#error "Please define __G32R502__"
#endif // __G32R502__

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // G32R502_H

//
// End of file
//
