//###########################################################################
//
// FILE:    sdf.h
//
// TITLE:   G32R501 SDF Driver
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
// 1. Module names, macro definitions, enum names, function names
//
//###########################################################################
#ifndef SDF_H
#define SDF_H

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
//! \addtogroup sdf_api SDF
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_sdf.h"
#include "inc/hw_memmap.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************
//! Macro to get the low threshold
//!
#define SDF_GET_LOW_THRESHOLD(C)    ((uint16_t)(C))

//! Macro to get the high threshold
//!
#define SDF_GET_HIGH_THRESHOLD(C)   ((uint16_t)((uint32_t)(C) >> 16U))


//! Macro to convert comparator over sampling ratio to acceptable bit location
//!
#define SDF_SET_OSR(X)         (((X) - 1) << 8U)
//! Macro to convert the data shift bit values to acceptable bit location
//!
#define SDF_SHIFT_VALUE(X)     ((X) << 2U)

//! Macro to combine high threshold and low threshold values
//!
#define SDF_THRESHOLD(H, L)     ((((uint32_t)(H)) << 16U) | (L))

//! Macro to set the FIFO level to acceptable bit location
//!
#define SDF_SET_FIFO_LEVEL(X)  ((X) << 7U)

//! Macro to set and enable the zero cross threshold value.
//!
#define SDF_SET_ZERO_CROSS_THRESH_VALUE(X) (0x8000 | (X))

//! Macros to enable or disable filter.
//!
#define SDF_FILTER_DISABLE     0x0U
#define SDF_FILTER_ENABLE      0x2U

//*****************************************************************************
//
//! Values that can be returned from SDF_getThresholdStatus()
//
//*****************************************************************************
typedef enum
{
    SDF_OUTPUT_WITHIN_THRESHOLD = 0,   //!< SDF output is within threshold
    SDF_OUTPUT_ABOVE_THRESHOLD  = 1,   //!< SDF output is above threshold
    SDF_OUTPUT_BELOW_THRESHOLD  = 2    //!< SDF output is below threshold
} SDF_OutputThresholdStatus;

//*****************************************************************************
//
//! Values that can be passed to all functions as the \e filterNumber
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SDF_FILTER_1 = 0, //!< Digital filter 1
    SDF_FILTER_2 = 1, //!< Digital filter 2
    SDF_FILTER_3 = 2, //!< Digital filter 3
    SDF_FILTER_4 = 3  //!< Digital filter 4
} SDF_FilterNumber;

//*****************************************************************************
//
//! Values that can be passed to SDF_setFilterType(),
//! SDF_setComparatorFilterType() as the \e filterType parameter.
//
//*****************************************************************************
typedef enum
{
    //! Digital filter with SincFast structure.
    SDF_FILTER_SINC_FAST = 0x00,
    //! Digital filter with Sinc1 structure
    SDF_FILTER_SINC_1    = 0x10,
    //! Digital filter with Sinc3 structure.
    SDF_FILTER_SINC_2    = 0x20,
    //! Digital filter with Sinc4 structure.
    SDF_FILTER_SINC_3    = 0x30
} SDF_FilterType;

//*****************************************************************************
//
//! Values that can be passed to SDF_setupModulatorClock(),as the
//! \e clockMode parameter.
//
//*****************************************************************************
typedef enum
{
   //! Modulator clock is identical to the data rate
   SDF_MODULATOR_CLK_EQUAL_DATA_RATE  = 0,
   //! Modulator clock is half the data rate
   SDF_MODULATOR_CLK_HALF_DATA_RATE   = 1,
   //! Modulator clock is off. Data is Manchester coded.
   SDF_MODULATOR_CLK_OFF              = 2,
   //! Modulator clock is double the data rate.
   SDF_MODULATOR_CLK_DOUBLE_DATA_RATE = 3
} SDF_ModulatorClockMode;

//*****************************************************************************
//
//! Values that can be passed to SDF_setOutputDataFormat(),as the
//! \e dataFormat parameter.
//
//*****************************************************************************
typedef enum
{
   //! Filter output is in 16 bits 2's complement format.
   SDF_DATA_FORMAT_16_BIT = 0,
   //! Filter output is in 32 bits 2's complement format.
   SDF_DATA_FORMAT_32_BIT = 1
} SDF_OutputDataFormat;

//*****************************************************************************
//
//! Values that can be passed to SDF_setDataReadyInterruptSource(),as the
//! \e dataReadySource parameter.
//
//*****************************************************************************
typedef enum
{
   //! Data ready interrupt source is direct (non -FIFO).
   SDF_DATA_READY_SOURCE_DIRECT = 0,
   //! Data ready interrupt source is FIFO.
   SDF_DATA_READY_SOURCE_FIFO = 1
} SDF_DataReadyInterruptSource;

//*****************************************************************************
//
//! Values that can be passed to SDF_setPWMSyncSource(),as the
//! \e syncSource parameter.
//
//*****************************************************************************
typedef enum
{
   SDF_SYNC_PWM1_SOCA = 0,    //!< SDF sync source is PWM1 SOCA
   SDF_SYNC_PWM1_SOCB = 1,    //!< SDF sync source is PWM1 SOCB
   SDF_SYNC_PWM2_SOCA = 4,    //!< SDF sync source is PWM2 SOCA
   SDF_SYNC_PWM2_SOCB = 5,    //!< SDF sync source is PWM2 SOCB
   SDF_SYNC_PWM3_SOCA = 8,    //!< SDF sync source is PWM3 SOCA
   SDF_SYNC_PWM3_SOCB = 9,    //!< SDF sync source is PWM3 SOCB
   SDF_SYNC_PWM4_SOCA = 12,   //!< SDF sync source is PWM4 SOCA
   SDF_SYNC_PWM4_SOCB = 13,   //!< SDF sync source is PWM4 SOCB
   SDF_SYNC_PWM5_SOCA = 16,   //!< SDF sync source is PWM5 SOCA
   SDF_SYNC_PWM5_SOCB = 17,   //!< SDF sync source is PWM5 SOCB
   SDF_SYNC_PWM6_SOCA = 20,   //!< SDF sync source is PWM6 SOCA
   SDF_SYNC_PWM6_SOCB = 21,   //!< SDF sync source is PWM6 SOCB
   SDF_SYNC_PWM7_SOCA = 24,   //!< SDF sync source is PWM7 SOCA
   SDF_SYNC_PWM7_SOCB = 25,   //!< SDF sync source is PWM7 SOCB
   SDF_SYNC_PWM8_SOCA = 28,   //!< SDF sync source is PWM8 SOCA
   SDF_SYNC_PWM8_SOCB = 29    //!< SDF sync source is PWM8 SOCB
} SDF_PWMSyncSource;

//*****************************************************************************
//
//! Values that can be passed to SDF_setFIFOClearOnSyncMode(),as the
//! \e fifoClearSyncMode parameter.
//
//*****************************************************************************
typedef enum
{
   //! SDF FIFO buffer is not cleared on Sync signal
   SDF_FIFO_NOT_CLEARED_ON_SYNC = 0,
   //! SDF FIFO buffer is cleared on Sync signal
   SDF_FIFO_CLEARED_ON_SYNC     = 1
} SDF_FIFOClearSyncMode;

//*****************************************************************************
//
//! Values that can be passed to SDF_setWaitForSyncClearMode(),as the
//! \e syncClearMode parameter.
//
//*****************************************************************************
typedef enum
{
   //! Wait for sync cleared using software.
   SDF_MANUAL_CLEAR_WAIT_FOR_SYNC = 0,
   //! Wait for sync cleared automatically
   SDF_AUTO_CLEAR_WAIT_FOR_SYNC   = 1
} SDF_WaitForSyncClearMode;

//*****************************************************************************
//
// Values that can be passed to SDF_enableInterrupt and SDF_disableInterrupt
// as intFlags parameter
//
//*****************************************************************************
//! Interrupt is generated if Modulator fails.
//!
#define SDF_MODULATOR_FAILURE_INTERRUPT    0x200U
//! Interrupt on Comparator low-level threshold.
//!
#define SDF_LOW_LEVEL_THRESHOLD_INTERRUPT  0x40U
//! Interrupt on Comparator high-level threshold.
//!
#define SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT 0x20U
//! Interrupt on Acknowledge flag
//!
#define SDF_DATA_FILTER_ACKNOWLEDGE_INTERRUPT 0x1U
//! Interrupt on FIFO level
//!
#define SDF_FIFO_INTERRUPT                 0x1000U
//! Interrupt on FIFO overflow
//!
#define SDF_FIFO_OVERFLOW_INTERRUPT        0x8000U

//*****************************************************************************
//
// Values that can be passed to SDF_clearInterruptFlag flags parameter
//
//*****************************************************************************
//! Master interrupt flag
//!
#define SDF_MASTER_INTERRUPT_FLAG         0x80000000U
//! Filter 1 high -level threshold flag
//!
#define SDF_FILTER_1_HIGH_THRESHOLD_FLAG  0x1U
//! Filter 1 low -level threshold flag
//!
#define SDF_FILTER_1_LOW_THRESHOLD_FLAG   0x2U
//! Filter 2 high -level threshold flag
//!
#define SDF_FILTER_2_HIGH_THRESHOLD_FLAG  0x4U
//! Filter 2 low -level threshold flag
//!
#define SDF_FILTER_2_LOW_THRESHOLD_FLAG   0x8U
//! Filter 3 high -level threshold flag
//!
#define SDF_FILTER_3_HIGH_THRESHOLD_FLAG  0x10U
//! Filter 3 low -level threshold flag
//!
#define SDF_FILTER_3_LOW_THRESHOLD_FLAG   0x20U
//! Filter 4 high -level threshold flag
//!
#define SDF_FILTER_4_HIGH_THRESHOLD_FLAG  0x40U
//! Filter 4 low -level threshold flag
//!
#define SDF_FILTER_4_LOW_THRESHOLD_FLAG   0x80U
//! Filter 1 modulator failed flag
//!
#define SDF_FILTER_1_MOD_FAILED_FLAG      0x100U
//! Filter 2 modulator failed flag
//!
#define SDF_FILTER_2_MOD_FAILED_FLAG      0x200U
//! Filter 3 modulator failed flag
//!
#define SDF_FILTER_3_MOD_FAILED_FLAG      0x400U
//! Filter 4 modulator failed flag
//!
#define SDF_FILTER_4_MOD_FAILED_FLAG      0x800U
//! Filter 1 new data flag
//!
#define SDF_FILTER_1_NEW_DATA_FLAG        0x1000U
//! Filter 2 new data flag
//!
#define SDF_FILTER_2_NEW_DATA_FLAG        0x2000U
//! Filter 3 new data flag
//!
#define SDF_FILTER_3_NEW_DATA_FLAG        0x4000U
//! Filter 4 new data flag
//!
#define SDF_FILTER_4_NEW_DATA_FLAG        0x8000U
//! Filter 1 FIFO overflow flag
//!
#define SDF_FILTER_1_FIFO_OVERFLOW_FLAG   0x10000U
//! Filter 2 FIFO overflow flag
//!
#define SDF_FILTER_2_FIFO_OVERFLOW_FLAG   0x20000U
//! Filter 3 FIFO overflow flag
//!
#define SDF_FILTER_3_FIFO_OVERFLOW_FLAG   0x40000U
//! Filter 4 FIFO overflow flag
//!
#define SDF_FILTER_4_FIFO_OVERFLOW_FLAG   0x80000U
//! Filter 1 FIFO overflow flag
//!
#define SDF_FILTER_1_FIFO_INTERRUPT_FLAG  0x100000U
//! Filter 2 FIFO overflow flag
//!
#define SDF_FILTER_2_FIFO_INTERRUPT_FLAG  0x200000U
//! Filter 3 FIFO overflow flag
//!
#define SDF_FILTER_3_FIFO_INTERRUPT_FLAG  0x400000U
//! Filter 4 FIFO overflow flag
//!
#define SDF_FILTER_4_FIFO_INTERRUPT_FLAG  0x800000U

//*****************************************************************************
//
//! \internal
//! Checks SDF base address.
//!
//! \param base specifies the SDF module base address.
//!
//! This function determines if SDF module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
SDF_isBaseValid(uint32_t base)
{
    return(
           (base == SDF1_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Enable external reset
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function enables data filter to be reset by an external source (PWM
//! compare output).
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_enableExternalReset(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Set the SDSYNCEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U * 2U)) |=
        SDF_SDDFPARM1_SDSYNCEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable external reset
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function disables data filter from being reset by an external source
//! (PWM compare output).
//!
//! \return None.
//*****************************************************************************
static inline void
SDF_disableExternalReset(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Clear the SDSYNCEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U * 2U)) &=
        ~SDF_SDDFPARM1_SDSYNCEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable filter
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function enables the filter specified by the \e filterNumber variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_enableFilter(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Set the FEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U * 2U)) |=
        SDF_SDDFPARM1_FEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable filter
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function disables the filter specified by the \e filterNumber
//! variable.
//!
//! \return None.
//*****************************************************************************
static inline void
SDF_disableFilter(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Clear the FEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U * 2U)) &=
        ~SDF_SDDFPARM1_FEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable FIFO buffer
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function enables the filter FIFO buffer specified by the
//! \e filterNumber variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_enableFIFOBuffer(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Set the FFEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDFIFOCTL1 + ((uint32_t)filterNumber * 16U * 2U)) |=
        SDF_SDFIFOCTL1_FFEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable FIFO buffer
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function disables the filter FIFO buffer specified by the
//! \e filterNumber variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_disableFIFOBuffer(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Clear the FFEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDFIFOCTL1 + ((uint32_t)filterNumber * 16U * 2U)) &=
        ~SDF_SDFIFOCTL1_FFEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Return the Zero Cross Trip status
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function returns the Zero Cross Trip status for the filter
//! specified by filterNumber variable.
//!
//! \return \b true if Comparator filter output >= High-level threshold (Z)
//!         \b false if Comparator filter output < High-level threshold (Z)
//
//*****************************************************************************
static inline bool
SDF_getZeroCrossTripStatus(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    return(((HWREGH(base + SDF_O_SDSTATUS) >> (uint16_t)filterNumber) &
            0x1U) == 1U);
}

//*****************************************************************************
//
//! Clear the Zero Cross Trip status
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//!  This function clears the Zero Cross Trip status for the filter
//!  specified by filterNumber variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_clearZeroCrossTripStatus(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Set SDCTL MIE bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDCTL) |= ((uint16_t)1U << (uint16_t)filterNumber);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable Comparator.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//!  This function enables the Comparator for the selected filter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_enableComparator(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Set CEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDCPARM1 + ((uint32_t)filterNumber * 16U * 2U)) |=
        SDF_SDCPARM1_CEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable Comparator.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//!  This function disables the Comparator for the selected filter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_disableComparator(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Clear CEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDCPARM1 + ((uint32_t)filterNumber * 16U * 2U)) &=
        ~SDF_SDCPARM1_CEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set filter type.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param filterType is the filter type or structure.
//!
//! This function sets the filter type or structure to be used as specified by
//! filterType for the selected filter number as specified by filterNumber.
//!
//! \return None.
//*****************************************************************************
static inline void
SDF_setFilterType(uint32_t base, SDF_FilterNumber filterNumber,
                   SDF_FilterType filterType)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));

    address = base + SDF_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to SST bits
    //
    WRPRT_DISABLE;
    HWREGH(address) = (HWREGH(address) & (~SDF_SDDFPARM1_SST_M)) |
                      ((uint16_t)filterType << 6U);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set data filter over sampling ratio.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param overSamplingRatio is the data filter over sampling ratio.
//!
//! This function sets the filter oversampling ratio for the filter specified
//! by the filterNumber variable.Valid values for the variable
//! overSamplingRatio are 0 to 255 inclusive. The actual oversampling ratio
//! will be this value plus one.
//!
//! \return None.
//*****************************************************************************
static inline void
SDF_setFilterOverSamplingRatio(uint32_t base, SDF_FilterNumber filterNumber,
                                uint16_t overSamplingRatio)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));
    ASSERT(overSamplingRatio < 256U);

    address = base + SDF_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to DOSR bits
    //
    WRPRT_DISABLE;
    HWREGH(address) = (HWREGH(address) & (~SDF_SDDFPARM1_DOSR_M)) |
                      overSamplingRatio;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set modulator clock mode.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param clockMode is the modulator clock mode.
//!
//! This function sets the modulator clock mode specified by clockMode
//! for the filter specified by filterNumber.
//!
//!
//! \return None.
//*****************************************************************************
static inline void
SDF_setupModulatorClock(uint32_t base, SDF_FilterNumber filterNumber,
                         SDF_ModulatorClockMode clockMode)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));

    address = base + SDF_O_SDCTLPARM1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to MOD bits
    //
    WRPRT_DISABLE;
    HWREGH(address) = (HWREGH(address) & (~SDF_SDCTLPARM1_MOD_M)) |
                      (uint16_t)clockMode;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the output data format
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param dataFormat is the output data format.
//!
//! This function sets the output data format for the filter specified by
//! filterNumber.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_setOutputDataFormat(uint32_t base, SDF_FilterNumber filterNumber,
                         SDF_OutputDataFormat dataFormat)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));

    address = base + SDF_O_SDDPARM1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to DR bit
    //
    WRPRT_DISABLE;
    HWREGH(address) = (HWREGH(address) & (~SDF_SDDPARM1_DR)) |
                      ((uint16_t)dataFormat << 10U);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set data shift value.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param shiftValue is the data shift value.
//!
//! This function sets the shift value for the 16 bit 2's complement data
//! format. The valid maximum value for shiftValue is 31.
//!
//! \b Note: Use this function with 16 bit 2's complement data format only.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_setDataShiftValue(uint32_t base, SDF_FilterNumber filterNumber,
                       uint16_t shiftValue)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));
    ASSERT(shiftValue < 32U);

    address = base + SDF_O_SDDPARM1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to SH bit
    //
    WRPRT_DISABLE;
    HWREGH(address) = (HWREGH(address) & (~SDF_SDDPARM1_SH_M)) |
                      (shiftValue << SDF_SDDPARM1_SH_S);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Filter output high-level threshold.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param highThreshold is the high-level threshold.
//!
//! This function sets the unsigned high-level threshold value for the
//! Comparator filter output. If the output value of the filter exceeds
//! highThreshold and interrupt generation is enabled, an interrupt will be
//! issued.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_setCompFilterHighThreshold(uint32_t base, SDF_FilterNumber filterNumber,
                                uint16_t highThreshold)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));
    ASSERT(highThreshold < 0x7FFFU);

    address = base + SDF_O_SDCMPH1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to HLT bit
    //
    WRPRT_DISABLE;
    HWREGH(address) = (HWREGH(address) & ~SDF_SDCMPH1_HLT_M) | highThreshold;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Filter output low-level threshold.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param lowThreshold is the low-level threshold.
//!
//! This function sets the unsigned low-level threshold value for the
//! Comparator filter output. If the output value of the filter gets below
//! lowThreshold and interrupt generation is enabled, an interrupt will be
//! issued.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_setCompFilterLowThreshold(uint32_t base, SDF_FilterNumber filterNumber,
                               uint16_t lowThreshold)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));
    ASSERT(lowThreshold < 0x7FFFU);

    address = base + SDF_O_SDCMPL1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to LLT bit
    //
    WRPRT_DISABLE;
    HWREGH(address) = (HWREGH(address) & ~SDF_SDCMPL1_LLT_M) | lowThreshold;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Filter output zero-cross threshold.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param zeroCrossThreshold is the zero-cross threshold.
//!
//! This function sets the unsigned zero-cross threshold value for the
//! Comparator filter output.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_setCompFilterZeroCrossThreshold(uint32_t base,
                                     SDF_FilterNumber filterNumber,
                                     uint16_t zeroCrossThreshold)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));
    ASSERT(zeroCrossThreshold < 0x7FFFU);

    address = base + SDF_O_SDCMPHZ1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to ZCT bit
    //
    WRPRT_DISABLE;
    HWREGH(address) = (HWREGH(address) & ~SDF_SDCMPHZ1_HLTZ_M) |
                      zeroCrossThreshold;

    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable zero-cross Edge detect mode.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function enables Zero Cross Edge detection.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_enableZeroCrossEdgeDetect(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Set ZCEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDCPARM1 + ((uint32_t)filterNumber * 16U * 2U)) |=
        SDF_SDCPARM1_HZEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable zero-cross Edge detect mode.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function disables Zero Cross Edge detection.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_disableZeroCrossEdgeDetect(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Clear ZCEN bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDCPARM1 + ((uint32_t)filterNumber * 16U * 2U)) &=
        ~SDF_SDCPARM1_HZEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable SDF interrupts.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param intFlags is the interrupt source.
//!
//! This function enables the low threshold , high threshold or modulator
//! failure interrupt as determined by intFlags for the filter specified
//! by filterNumber.
//! Valid values for intFlags are:
//!  SDF_MODULATOR_FAILURE_INTERRUPT , SDF_LOW_LEVEL_THRESHOLD_INTERRUPT,
//!  SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT, SDF_FIFO_INTERRUPT,
//!  SDF_FIFO_OVERFLOW_INTERRUPT,SDF_DATA_FILTER_ACKNOWLEDGE_INTERRUPT
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_enableInterrupt(uint32_t base, SDF_FilterNumber filterNumber,
                     uint16_t intFlags)
{
    uint16_t offset;

    ASSERT(SDF_isBaseValid(base));

    offset = (uint16_t)filterNumber * 16U * 2U;

    WRPRT_DISABLE;

    //
    // Low, high threshold, Modulator failure
    //
    if((intFlags & (SDF_MODULATOR_FAILURE_INTERRUPT |
                    SDF_LOW_LEVEL_THRESHOLD_INTERRUPT |
                    SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT)) != 0U)
    {
        //
        // Set IEL or IEH or MFIE bit of SDF_O_CPARx
        //
        HWREGH(base + SDF_O_SDCPARM1 + offset) |=
                (intFlags & (SDF_MODULATOR_FAILURE_INTERRUPT |
                             SDF_LOW_LEVEL_THRESHOLD_INTERRUPT |
                             SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT));
    }

    //
    // Data filter acknowledge interrupt
    //
    if((intFlags & SDF_DATA_FILTER_ACKNOWLEDGE_INTERRUPT) != 0U)
    {
        HWREGH(base + SDF_O_SDDFPARM1 + offset) |= SDF_SDDFPARM1_AE;
    }

    //
    // FIFO , FIFO overflow interrupt
    //
    if((intFlags & (SDF_FIFO_INTERRUPT | SDF_FIFO_OVERFLOW_INTERRUPT)) != 0U)
    {
        //
        // Set OVFIEN or FFIEN bits of SDF_O_FIFOCTRLx
        //
        HWREGH(base + SDF_O_SDFIFOCTL1 + offset) |=
                (intFlags & (SDF_FIFO_INTERRUPT |
                             SDF_FIFO_OVERFLOW_INTERRUPT));
    }
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable SDF interrupts.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param intFlags is the interrupt source.
//!
//! This function disables the low threshold , high threshold or modulator
//! failure interrupt as determined by intFlags for the filter
//! specified by filterNumber.
//! Valid values for intFlags are:
//!  SDF_MODULATOR_FAILURE_INTERRUPT , SDF_LOW_LEVEL_THRESHOLD_INTERRUPT,
//!  SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT, SDF_FIFO_INTERRUPT,
//!  SDF_FIFO_OVERFLOW_INTERRUPT,SDF_DATA_FILTER_ACKNOWLEDGE_INTERRUPT
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_disableInterrupt(uint32_t base, SDF_FilterNumber filterNumber,
                      uint16_t intFlags)
{
    uint16_t offset;

    ASSERT(SDF_isBaseValid(base));

    offset = (uint16_t)filterNumber * 16U * 2U;

    WRPRT_DISABLE;

    //
    // Low, high threshold, modulator failure interrupts
    //
    if((intFlags & (SDF_MODULATOR_FAILURE_INTERRUPT |
                    SDF_LOW_LEVEL_THRESHOLD_INTERRUPT |
                    SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT)) != 0U)
    {
        //
        // Set IEL or IEH or MFIE bit of SDF_O_CPARx
        //
        HWREGH(base + SDF_O_SDCPARM1 + offset) &=
            ~(intFlags & (SDF_MODULATOR_FAILURE_INTERRUPT |
                          SDF_LOW_LEVEL_THRESHOLD_INTERRUPT |
                          SDF_HIGH_LEVEL_THRESHOLD_INTERRUPT));
    }

    //
    // Data filter acknowledge interrupt
    //
    if((intFlags & SDF_DATA_FILTER_ACKNOWLEDGE_INTERRUPT) != 0U)
    {
        HWREGH(base + SDF_O_SDDFPARM1 + offset) &= ~SDF_SDDFPARM1_AE;
    }

    //
    // FIFO , FIFO overflow interrupt
    //
    if((intFlags & (SDF_FIFO_INTERRUPT | SDF_FIFO_OVERFLOW_INTERRUPT)) != 0U)
    {
         //
         // Set OVFIEN or FFIEN bits of SDF_O_FIFOCTRLx
         //
         HWREGH(base + SDF_O_SDFIFOCTL1 + offset) &=
            ~(intFlags & (SDF_FIFO_INTERRUPT | SDF_FIFO_OVERFLOW_INTERRUPT));
    }
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the comparator filter type.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param filterType is the comparator filter type or structure.
//!
//! This function sets the Comparator filter type or structure to be used as
//! specified by filterType for the selected filter number as specified by
//! filterNumber.
//!
//! \return None.
//*****************************************************************************
static inline void
SDF_setComparatorFilterType(uint32_t base, SDF_FilterNumber filterNumber,
                             SDF_FilterType filterType)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));

    address = base + SDF_O_SDCPARM1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to CS1_CS0 bits
    //
    WRPRT_DISABLE;
    HWREGH(address) = (HWREGH(address) & (~SDF_SDCPARM1_CS1_CS0_M)) |
                      ((uint16_t)filterType << 3U);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Comparator filter over sampling ratio.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param overSamplingRatio is the comparator filter over sampling ration.
//!
//! This function sets the comparator filter oversampling ratio for the filter
//! specified by the filterNumber.Valid values for the variable
//! overSamplingRatio are 0 to 31 inclusive.
//! The actual oversampling ratio will be this value plus one.
//!
//! \return None.
//*****************************************************************************
static inline void
SDF_setCompFilterOverSamplingRatio(uint32_t base,
                                    SDF_FilterNumber filterNumber,
                                    uint16_t overSamplingRatio)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));
    ASSERT(overSamplingRatio < 32U);

    address = base + SDF_O_SDCPARM1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to COSR bits
    //
    WRPRT_DISABLE;
    HWREGH(address) = (HWREGH(address) & (~SDF_SDCPARM1_COSR_M)) |
                      overSamplingRatio;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Get the filter data output.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function returns the latest data filter output. Depending on the
//! filter data output format selected, the valid value will be the lower 16
//! bits or the whole 32 bits of the returned value.
//!
//! \return Returns the latest data filter output.
//*****************************************************************************
static inline uint32_t
SDF_getFilterData(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Read DFLT bits
    //
    return(HWREG(base + SDF_O_SDDATA1 + ((uint32_t)filterNumber * 16U * 2U)));
}

//*****************************************************************************
//
//! Get the Comparator threshold status.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function returns the Comparator output threshold status for the given
//! filterNumber.
//!
//! \return Returns the following status flags.
//! - \b SDF_OUTPUT_WITHIN_THRESHOLD if the output is within the
//!                                   specified threshold.
//! - \b SDF_OUTPUT_ABOVE_THRESHOLD  if the output is above the high
//!                                   threshold
//! - \b SDF_OUTPUT_BELOW_THRESHOLD  if the output is below the low
//!                                   threshold.
//!
//*****************************************************************************
static inline SDF_OutputThresholdStatus
SDF_getThresholdStatus(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Read SDIFLG high/low threshold bits
    //
    return((SDF_OutputThresholdStatus)((HWREG(base + SDF_O_SDIFLG) >>
                                        (2U * (uint16_t)filterNumber)) & 0x3U));
}

//*****************************************************************************
//
//! Get the Modulator status.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function returns the Modulator status.
//!
//! \return Returns true if the Modulator is operating normally
//!         Returns false if the Modulator has failed
//!
//*****************************************************************************
static inline bool
SDF_getModulatorStatus(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Read SDIFLG MF1, MF2, MF3 OR MF4 bits
    //
    return(((HWREG(base + SDF_O_SDIFLG) >> ((uint16_t)filterNumber + 8U)) &
            0x1U) != 0x1U);
}

//*****************************************************************************
//
//! Check if new Filter data is available.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function returns new filter data status.
//!
//! \return Returns \b true if new filter data is available
//!         Returns \b false if no new filter data is available
//!
//*****************************************************************************
static inline bool
SDF_getNewFilterDataStatus(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Read SDIFLG AF1, AF2, AF3 OR AF4 bits
    //
    return(((HWREG(base + SDF_O_SDIFLG) >> ((uint16_t)filterNumber + 12U)) &
            0x1U) == 0x1U);
}

//*****************************************************************************
//
//! Check if FIFO buffer is overflowed.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function returns the status of the FIFO buffer overflow for the given
//! filter value.
//!
//! \return Returns \b true if FIFO buffer is overflowed
//!         Returns \b false if FIFO buffer is not overflowed
//!
//*****************************************************************************
static inline bool
SDF_getFIFOOverflowStatus(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Read SDIFLG SDFFOVF1, SDFFOVF2, SDFFOVF3 OR SDFFOVF4 bits
    //
    return(((HWREG(base + SDF_O_SDIFLG) >> ((uint16_t)filterNumber + 16U)) &
            0x1U) == 0x1U);
}

//*****************************************************************************
//
//! Check FIFO buffer interrupt status.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function returns the status of the FIFO buffer interrupt for the given
//! filter.
//!
//! \return Returns \b true if FIFO buffer interrupt has occurred.
//!         Returns \b false if FIFO buffer interrupt has not occurred.
//!
//*****************************************************************************
static inline bool
SDF_getFIFOISRStatus(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Read SDIFLG SDFFINT1, SDFFINT2, SDFFINT3 OR SDFFINT4 bits
    //
    return(((HWREG(base + SDF_O_SDIFLG) >> ((uint16_t)filterNumber + 20U)) &
            0x1U) == 0x1U);
}

//*****************************************************************************
//
//! Get pending interrupt.
//!
//! \param base is the base address of the SDF module
//!
//! This function returns any pending interrupt status.
//!
//! \return Returns \b true if there is a pending interrupt.
//!         Returns \b false if no interrupt is pending.
//!
//*****************************************************************************
static inline bool
SDF_getIsrStatus(uint32_t base)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Read SDIFLG MIF
    //
    return((HWREG(base + SDF_O_SDIFLG) >> 31U) == 0x1U);
}

//*****************************************************************************
//
//! Clear pending flags.
//!
//! \param base is the base address of the SDF module
//! \param flag is the SDF status
//!
//! This function clears the specified pending interrupt flag.
//! Valid values are
//! SDF_MASTER_INTERRUPT_FLAG,SDF_FILTER_1_NEW_DATA_FLAG,
//! SDF_FILTER_2_NEW_DATA_FLAG,SDF_FILTER_3_NEW_DATA_FLAG,
//! SDF_FILTER_4_NEW_DATA_FLAG,SDF_FILTER_1_MOD_FAILED_FLAG,
//! SDF_FILTER_2_MOD_FAILED_FLAG,SDF_FILTER_3_MOD_FAILED_FLAG,
//! SDF_FILTER_4_MOD_FAILED_FLAG,SDF_FILTER_1_HIGH_THRESHOLD_FLAG,
//! SDF_FILTER_1_LOW_THRESHOLD_FLAG,SDF_FILTER_2_HIGH_THRESHOLD_FLAG,
//! SDF_FILTER_2_LOW_THRESHOLD_FLAG,SDF_FILTER_3_HIGH_THRESHOLD_FLAG,
//! SDF_FILTER_3_LOW_THRESHOLD_FLAG,SDF_FILTER_4_HIGH_THRESHOLD_FLAG,
//! SDF_FILTER_4_LOW_THRESHOLD_FLAG,SDF_FILTER_1_FIFO_OVERFLOW_FLAG,
//! SDF_FILTER_2_FIFO_OVERFLOW_FLAG,SDF_FILTER_3_FIFO_OVERFLOW_FLAG
//! SDF_FILTER_4_FIFO_OVERFLOW_FLAG,SDF_FILTER_1_FIFO_INTERRUPT_FLAG,
//! SDF_FILTER_2_FIFO_INTERRUPT_FLAG,SDF_FILTER_3_FIFO_INTERRUPT_FLAG
//! SDF_FILTER_4_FIFO_INTERRUPT_FLAG or any combination of the above flags.
//!
//! \return None
//!
//*****************************************************************************
static inline void
SDF_clearInterruptFlag(uint32_t base, uint32_t flag)
{
    ASSERT(SDF_isBaseValid(base));
    ASSERT((flag & 0x80FFFFFFU) == flag);

    //
    // Write to  SDIFLGCLR register
    //
    HWREG(base + SDF_O_SDIFLGCLR) |= flag;
}

//*****************************************************************************
//
//! Enable master interrupt.
//!
//! \param base is the base address of the SDF module
//!
//! This function enables the master SDF interrupt.
//!
//! \return None
//!
//*****************************************************************************
static inline void
SDF_enableMasterInterrupt(uint32_t base)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Set SDCTL MIE bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDCTL) |= SDF_SDCTL_MIE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable master interrupt.
//!
//! \param base is the base address of the SDF module
//!
//! This function disables the master SDF interrupt.
//!
//! \return None
//!
//*****************************************************************************
static inline void
SDF_disableMasterInterrupt(uint32_t base)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Clear SDCTL MIE bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDCTL) &= ~SDF_SDCTL_MIE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable master filter.
//!
//! \param base is the base address of the SDF module
//!
//! This function enables master filter.
//!
//! \return None
//!
//*****************************************************************************
static inline void
SDF_enableMasterFilter(uint32_t base)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Set SDMFILEN MFE bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDMFILEN) |= SDF_SDMFILEN_MFE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable master filter.
//!
//! \param base is the base address of the SDF module
//!
//! This function disables master filter.
//!
//! \return None
//!
//*****************************************************************************
static inline void
SDF_disableMasterFilter(uint32_t base)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Clear SDMFILEN MFE bit
    //
    WRPRT_DISABLE;
    HWREGH(base + SDF_O_SDMFILEN) &= ~SDF_SDMFILEN_MFE;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Return the FIFO data count
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function returns the FIFO data count.
//!
//! \return Returns the number of data words available in FIFO buffer.
//
//*****************************************************************************
static inline uint16_t
SDF_getFIFODataCount(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Read SDFFST
    //
    return((HWREGH(base + SDF_O_SDFIFOCTL1 +
        ((uint32_t)filterNumber * 16U * 2U)) & SDF_SDFIFOCTL1_SDFFST_M) >>
         SDF_SDFIFOCTL1_SDFFST_S);
}

//*****************************************************************************
//
//! Return the Comparator sinc filter data
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function returns the Comparator sinc filter data output.
//!
//! \return Returns the Comparator sinc filter data output.
//!
//
//*****************************************************************************
static inline uint16_t
SDF_getComparatorSincData(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Read SDCDATA
    //
    return(HWREGH(base + SDF_O_SDCDATA1 + ((uint32_t)filterNumber * 16U * 2U)));
}

//*****************************************************************************
//
//! Return the FIFO data
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function returns the latest FIFO data.
//!
//! \return Returns the latest FIFO data.
//!
//! \note Discard the upper 16 bits if the output data format is 16bits.
//
//*****************************************************************************
static inline uint32_t
SDF_getFIFOData(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Read DFIFO
    //
    return(HWREG(base + SDF_O_SDDATFIFO1 + ((uint32_t)filterNumber * 16U * 2U)));
}

//*****************************************************************************
//
//! Set the FIFO interrupt level.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param fifoLevel is the FIFO interrupt level.
//!
//! This function sets the FIFO interrupt level. Interrupt is generated when
//! the FIFO buffer word count gets to or exceeds the value of \e fifoLevel.
//! Maximum value for \e fifoLevel is 16.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_setFIFOInterruptLevel(uint32_t base, SDF_FilterNumber filterNumber,
                           uint16_t fifoLevel)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));
    ASSERT(fifoLevel <= 16U);

    address = base + SDF_O_SDFIFOCTL1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to SDFFIL bit
    //
    WRPRT_DISABLE;
    HWREGH(address) =
        ((HWREGH(address) & (~SDF_SDFIFOCTL1_SDFFIL_M)) | fifoLevel);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set data ready interrupt source.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param dataReadySource is the data ready interrupt source.
//!
//! This function sets the data ready interrupt source.
//! Valid values for \e dataReadySource:
//!   - SDF_DATA_READY_SOURCE_DIRECT - Direct data ready
//!   - SDF_DATA_READY_SOURCE_FIFO  - FIFO data ready.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_setDataReadyInterruptSource(uint32_t base, SDF_FilterNumber filterNumber,
                                 SDF_DataReadyInterruptSource dataReadySource)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));

    address = base + SDF_O_SDFIFOCTL1 + ((uint32_t)filterNumber * 16U * 2U);

    //
    // Write to DRINTSEL
    //
    WRPRT_DISABLE;
    HWREGH(address) = (HWREGH(address) & ~SDF_SDFIFOCTL1_DRINTSEL) |
                      ((uint16_t)dataReadySource << 14U);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Get the wait-for-sync event status.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function returns the Wait-for-Sync event status.
//!
//! \return Returns true if sync event has occurred.
//!         Returns false if sync event has not occurred.
//
//*****************************************************************************
static inline bool
SDF_getWaitForSyncStatus(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    //
    // Read WTSYNFLG bit
    //
    return(((HWREGH(base + SDF_O_SDF_SYNCTRL1 + ((uint32_t)filterNumber * 16U * 2U)) &
            SDF_SDF_SYNCTRL1_WTSYNCLR) >> 7U) == 0x1U);
}

//*****************************************************************************
//
//! Clear the Wait-for-sync event status.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function clears the Wait-for-sync event status.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_clearWaitForSyncFlag(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Clear WTSYNCLR bit
    //
    HWREGH(base + SDF_O_SDF_SYNCTRL1 + ((uint32_t)filterNumber * 16U * 2U)) |=
           SDF_SDF_SYNCTRL1_WTSYNCLR;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Enable wait for sync mode.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function enables the wait for sync mode. Data to FIFO will be written
//! only after PWM sync event.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_enableWaitForSync(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Set WTSYNCEN bit
    //
    HWREGH(base + SDF_O_SDF_SYNCTRL1 + ((uint32_t)filterNumber * 16U * 2U)) |=
        SDF_SDF_SYNCTRL1_WTSYNCEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Disable wait for sync mode.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//!
//! This function disables the wait for sync mode. Data to FIFO will be written
//! every Data ready event.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_disableWaitForSync(uint32_t base, SDF_FilterNumber filterNumber)
{
    ASSERT(SDF_isBaseValid(base));

    WRPRT_DISABLE;

    //
    // Clear WTSYNCEN bit
    //
    HWREGH(base + SDF_O_SDF_SYNCTRL1 + ((uint32_t)filterNumber * 16U * 2U)) &=
        ~SDF_SDF_SYNCTRL1_WTSYNCEN;
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set the PWM sync mode.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param syncSource is the PWM sync source.
//!
//! This function sets the PWM sync source for the specific SDF filter. Valid
//! values for syncSource are SDF_SYNC_PWMx_CMPy. Where x ranges from 1 to 8
//! Representing PWM1 to PWM8 respectively and y ranges from A to D
//! representing PWM comparators A to D.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_setPWMSyncSource(uint32_t base, SDF_FilterNumber filterNumber,
                      SDF_PWMSyncSource syncSource)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));

    address = base + SDF_O_SDF_SYNCTRL1 + ((uint32_t)filterNumber * 16U * 2U);

    WRPRT_DISABLE;

    //
    // Write to SYNCSEL bits
    //
    HWREGH(address) =
        (HWREGH(address) & ~SDF_SDF_SYNCTRL1_SYNCSEL_M) | (uint16_t)syncSource;
    WRPRT_ENABLE;

    //
    //Enable SDSYNC reset to data filter
    //
    SDF_enableExternalReset(base, filterNumber);
}

//*****************************************************************************
//
//! Set FIFO clear on sync mode.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param fifoClearSyncMode is the FIFO clear on sync mode.
//!
//! This function sets the FIFO clear mode for the specified filter when a sync
//! happens depending on the value of fifoClearSyncMode.
//! Valid values for fifoClearSyncMode are:
//!  - SDF_FIFO_NOT_CLEARED_ON_SYNC - FIFO is not cleared on sync.
//!  - SDF_FIFO_CLEARED_ON_SYNC - FIFO is cleared on sync.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_setFIFOClearOnSyncMode(uint32_t base, SDF_FilterNumber filterNumber,
                            SDF_FIFOClearSyncMode fifoClearSyncMode)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));

    address = base + SDF_O_SDF_SYNCTRL1 + ((uint32_t)filterNumber * 16U * 2U);

    WRPRT_DISABLE;

    //
    // Write to FFSYNCCLREN bit
    //
    HWREGH(address) = (HWREGH(address) & ~SDF_SDF_SYNCTRL1_FFSYNCCLREN) |
                      ((uint16_t)fifoClearSyncMode << 9U);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
//! Set Wait-for-sync clear mode.
//!
//! \param base is the base address of the SDF module
//! \param filterNumber is the filter number.
//! \param syncClearMode is the wait-for-sync clear mode.
//!
//! This function sets the Wait-For-sync clear mode depending on the value of
//! syncClearMode.
//! Valid values for syncClearMode are:
//!   - SDF_MANUAL_CLEAR_WAIT_FOR_SYNC - Wait-for-sync flag is cleared by
//!                                       invoking SDF_clearWaitForSyncFlag().
//!   - SDF_AUTO_CLEAR_WAIT_FOR_SYNC   - Wait-for-sync flag is cleared
//!                                       automatically on FIFO interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDF_setWaitForSyncClearMode(uint32_t base, SDF_FilterNumber filterNumber,
                             SDF_WaitForSyncClearMode syncClearMode)
{
    uint32_t address;

    ASSERT(SDF_isBaseValid(base));

    address = base + SDF_O_SDF_SYNCTRL1 + ((uint32_t)filterNumber * 16U * 2U);

    WRPRT_DISABLE;

    //
    // Write to WTSCLREN  bit
    //
    HWREGH(address) = (HWREGH(address) & ~SDF_SDF_SYNCTRL1_WTSCLREN) |
                      ((uint16_t)syncClearMode << 10U);
    WRPRT_ENABLE;
}

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Configures SDF comparator for filter config & threshold values
//!
//! \param base is the base address of the SDF module
//! \param config1 is the filter number, filter type and over sampling ratio.
//! \param config2 is high-level and low-level threshold values.
//! \param config3 is the zero-cross threshold value.
//!
//! This function configures the comparator filter for filter config and
//! threshold values based on provided inputs.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  filter number
//!   - config1.[7:4]  filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDF_FilterNumber and SDF_FilterType enumerations respectively.
//! SDF_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio ,which ranges [1,32] inclusive, in the appropriate bit location.
//! For example the value
//! (SDF_FILTER_1 | SDF_FILTER_SINC_2 | SDF_SET_OSR(16))
//! will select Filter 1, SINC 2 type with an oversampling ratio of 16.
//!
//! The config2 parameter is the logical OR of the filter high and low
//! threshold values.
//! The bit definitions for config2 are as follow:
//!   - config2.[15:0]  low threshold
//!   - config2.[31:16] high threshold
//! The upper 16 bits define the high threshold and the lower
//! 16 bits define the low threshold.
//! SDF_THRESHOLD(H,L) can be used to combine the high and low thresholds.
//!
//! The config3 parameter is the logical OR of the zero cross threshold
//! enable flag and the zero-cross threshold value.
//! The bit definitions for config3 are as follow:
//!   - config3.[15] - Enable or disable zero cross threshold. Valid values
//!                    are 1 or 0 to enable or disable the zero cross threshold
//!                    respectively.
//!   -config3.[14:0] - Zero Cross Threshold value.
//! The SDF_SET_ZERO_CROSS_THRESH_VALUE(X) macro can be used to specify the
//! zero-cross threshold value and OR the 1 to enable it.
//!
//! \return None.
//!
//*****************************************************************************
extern void
SDF_configComparator(uint32_t base, uint16_t config1,
                      uint32_t config2, uint16_t config3);

//*****************************************************************************
//
//! Configure SDF data filter
//!
//! \param base is the base address of the SDF module
//! \param config1 is the filter number, filter type and over sampling ratio
//!                configuration.
//! \param config2 is filter switch, data representation and data shift values
//!                configuration.
//!
//! This function configures the data filter based on configurations
//! config1 and config2.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  Filter number
//!   - config1.[7:4]  Filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDF_FilterNumber and SDF_FilterType enumerations respectively.
//! SDF_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio , which ranges [1,256] inclusive , in the appropriate bit location
//! for config1. For example the value
//! (SDF_FILTER_2 | SDF_FILTER_SINC_3 | SDF_SET_OSR(64))
//! will select Filter 2 , SINC 3 type with an oversampling ratio of 64.
//!
//! The config2 parameter is the logical OR of data representation, filter
//! switch, and data shift values
//! The bit definitions for config2 are as follow:
//!   - config2.[0]  Data representation
//!   - config2.[1]  Filter switch
//!   - config2.[15:2]  Shift values
//! Valid values for data representation are given in SDF_OutputDataFormat
//! enumeration. SDF_FILTER_DISABLE or SDF_FILTER_ENABLE will define the
//! filter switch values.SDF_SHIFT_VALUE(X) macro can be used to set the value
//! of the data shift value,which ranges [0,31] inclusive, in the appropriate
//! bit location for config2.
//! The shift value is valid only in SDF_DATA_FORMAT_16_BIT data
//! representation format.
//!
//! \return None.
//!
//*****************************************************************************
extern void
SDF_configDataFilter(uint32_t base, uint16_t config1, uint16_t config2);

//*****************************************************************************
//
//! Configure SDF comparator Zero Cross threshold
//!
//! \param base is the base address of the SDF module
//! \param config1 is the filter number, filter type and over sampling ratio.
//! \param config2 is the zero cross threshold value.
//!
//! This function configures the comparator filter zero cross threshold values
//! based on configurations config1 and config2.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  filter number
//!   - config1.[7:4]  filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDF_FilterNumber and SDF_FilterType enumerations respectively.
//! SDF_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio ,which ranges [1,32] inclusive, in the appropriate bit location.
//! For example the value
//! (SDF_FILTER_1 | SDF_FILTER_SINC_2 | SDF_SET_OSR(16))
//! will select Filter 1 , SINC 2 type with an oversampling ratio of 16.
//!
//! The config2 parameter is the value of the zero cross threshold. The maximum
//! acceptable value is 32767.
//!
//! \return None.
//!
//*****************************************************************************
extern void
SDF_configZeroCrossComparator(uint32_t base, uint16_t config1,
                               uint16_t config2);

//*****************************************************************************
//
//! Configure SDF data filter FIFO
//!
//! \param base is the base address of the SDF module
//! \param config1 is the filter number, filter type and over sampling ratio
//!                configuration.
//! \param config2 is filter switch, data representation and data shift values
//!                and FIFO level configuration.
//!
//! This function enables and configures the data filter FIFO based on
//! configurations config1 and config2.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  filter number
//!   - config1.[7:4]  filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDF_FilterNumber and SDF_FilterType enumerations respectively.
//! SDF_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio , which ranges [1,256] inclusive , in the appropriate bit location
//! for config1. For example the value
//! (SDF_FILTER_2 | SDF_FILTER_SINC_3 | SDF_SET_OSR(64))
//! will select Filter 2 , SINC 3 type with an oversampling ratio of 64.
//!
//! The config2 parameter is the logical OR of data representation, filter
//! switch, data shift value, and FIFO level
//! The bit definitions for config2 are as follow:
//!   - config2.[0]  Data representation
//!   - config2.[1]  filter switch.
//!   - config2.[6:2]  shift values.
//!   - config2.[15:7] FIFO level
//! Valid values for data representation are given in SDF_OutputDataFormat
//! enumeration. SDF_FILTER_DISABLE or SDF_FILTER_ENABLE will define the
//! filter switch values.SDF_SHIFT_VALUE(X) macro can be used to set the value
//! of the data shift value,which ranges [0,31] inclusive, in the appropriate
//! bit location for config2.
//! The value of FIFO level ranges [1,16] inclusive. The macro
//! SDF_SET_FIFO_LEVEL(X) can be used to set the value of the FIFO level.
//!
//! \return None.
//!
//*****************************************************************************
extern void
SDF_configDataFilterFIFO(uint32_t base, uint16_t config1, uint16_t config2);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif
#endif // SDF_H
