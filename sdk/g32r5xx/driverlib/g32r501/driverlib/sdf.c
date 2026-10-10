//###########################################################################
//
// FILE:    sdf.c
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
// 1. Module names, macro definitions, function names
//
//###########################################################################

#include "sdf.h"

//*****************************************************************************
//
// Defines for filter configurations. Not intended for use by application code.
//
//*****************************************************************************
//
// Get filter oversampling ratio
//
#define SDF_GET_OSR(C)             ((C) >> 8U)

//
// Maximum acceptable comparator filter oversampling ratio
//
#define SDF_MAX_COMP_FILTER_OSR    31U

//
// Maximum acceptable data filter oversampling ratio
//
#define SDF_MAX_DATA_FILTER_OSR    255U

//
// Get the filter type
//
#define SDF_GET_FILTER_TYPE(C)     ((C) & 0x30U)

//
// Get the filter number
//
#define SDF_GET_FILTER_NUMBER(C)   ((C) & 0x3U)

//
// Get the zero-crossing high threshold
//
#define SDF_GET_ZHIGH_THRESHOLD(C)  ((C) & 0x7FFFU))
#define SDF_ZHIGH_ENABLE_MASK      0x8000U

//
// Get data shift value
//
#define SDF_GET_SHIFT_VALUE(C)     (((C) >> 2U) & 0x1FU)

//*****************************************************************************
//
// SDF_configComparator
//
//*****************************************************************************
void SDF_configComparator(uint32_t base, uint16_t config1, uint32_t config2,
                           uint16_t config3)
{
    SDF_FilterNumber filter;
    uint16_t ratio;
    SDF_FilterType filterType;

    filter = (SDF_FilterNumber)(SDF_GET_FILTER_NUMBER(config1));
    ratio = SDF_GET_OSR(config1);
    filterType = (SDF_FilterType)SDF_GET_FILTER_TYPE(config1);

    //
    // Limit the oversampling ratio
    //
    if(ratio > SDF_MAX_COMP_FILTER_OSR)
    {
        ratio = SDF_MAX_COMP_FILTER_OSR;
    }

    //
    // Set the comparator filter type
    //
    SDF_setComparatorFilterType(base, filter, filterType);

    //
    // Set the comparator filter over sampling ratio
    //
    SDF_setCompFilterOverSamplingRatio(base, filter, ratio);

    //
    // Set the comparator high threshold value
    //
    SDF_setCompFilterHighThreshold(base, filter,
                                    SDF_GET_HIGH_THRESHOLD(config2));

    //
    // Set the comparator low threshold value
    //
    SDF_setCompFilterLowThreshold(base, filter,
                                   SDF_GET_LOW_THRESHOLD(config2));


    //
    // If requested, enable and set the zero-cross high threshold value
    //
    if((config3 & SDF_ZHIGH_ENABLE_MASK) != 0U)
    {
        SDF_setCompFilterZeroCrossThreshold(base, filter,
                                             SDF_GET_ZHIGH_THRESHOLD(config3);
        SDF_enableZeroCrossEdgeDetect(base, filter);
    }
}

//*****************************************************************************
//
// SDF_configDataFilter
//
//*****************************************************************************
void SDF_configDataFilter(uint32_t base, uint16_t config1, uint16_t config2)
{
    SDF_FilterNumber filter;
    uint16_t ratio;
    SDF_FilterType filterType;

    filter = (SDF_FilterNumber)(SDF_GET_FILTER_NUMBER(config1));
    ratio = SDF_GET_OSR(config1);
    filterType = (SDF_FilterType)SDF_GET_FILTER_TYPE(config1);

    //
    // Limit the oversampling ratio
    //
    if(ratio > SDF_MAX_DATA_FILTER_OSR)
    {
        ratio = SDF_MAX_DATA_FILTER_OSR;
    }

    //
    // Set the comparator filter type
    //
    SDF_setFilterType(base, filter, filterType);

    //
    // Set the comparator filter over sampling ratio
    //
    SDF_setFilterOverSamplingRatio(base, filter, ratio);

    //
    // If filter switch on
    //
    if((config2 & SDF_FILTER_ENABLE) == SDF_FILTER_ENABLE)
    {
        SDF_enableFilter(base, filter);
    }
    else
    {
        SDF_disableFilter(base, filter);
    }

    //
    // Set output data format
    //
    SDF_setOutputDataFormat(base, filter,
                             (SDF_OutputDataFormat)(config2 & 0x1U));

    //
    // Set the shift value if data is in 16-bit 2's complement format
    //
    if((config2 & 0x1U) == (uint16_t)(SDF_DATA_FORMAT_16_BIT))
    {
        SDF_setDataShiftValue(base, filter, SDF_GET_SHIFT_VALUE(config2));
    }
}

//*****************************************************************************
//
// SDF_configZeroCrossComparator
//
//*****************************************************************************
void SDF_configZeroCrossComparator(uint32_t base, uint16_t config1,
                                    uint16_t config2)
{
    SDF_FilterNumber filter;
    uint16_t ratio;
    SDF_FilterType filterType;

    filter = (SDF_FilterNumber)(SDF_GET_FILTER_NUMBER(config1));
    ratio = SDF_GET_OSR(config1);
    filterType = (SDF_FilterType)SDF_GET_FILTER_TYPE(config1);

    //
    // Limit the oversampling ratio
    //
    if(ratio > SDF_MAX_COMP_FILTER_OSR)
    {
        ratio = SDF_MAX_COMP_FILTER_OSR;
    }

    //
    // Set the comparator filter type
    //
    SDF_setComparatorFilterType(base, filter, filterType);

    //
    // Set the comparator filter over sampling ratio
    //
    SDF_setCompFilterOverSamplingRatio(base, filter, ratio);

    //
    // Set the zero cross threshold value
    //
    SDF_setCompFilterZeroCrossThreshold(base, filter, config2);
}

//*****************************************************************************
//
// SDF_configDataFilterFIFO
//
//*****************************************************************************
void SDF_configDataFilterFIFO(uint32_t base, uint16_t config1,
                               uint16_t config2)
{
    SDF_FilterNumber filter;
    uint16_t ratio;
    uint16_t fifoLevel;
    SDF_FilterType filterType;

    filter = (SDF_FilterNumber)(SDF_GET_FILTER_NUMBER(config1));
    fifoLevel = ((config2 >> 7U) & 0x1FU);
    ratio = SDF_GET_OSR(config1);
    filterType = (SDF_FilterType)SDF_GET_FILTER_TYPE(config1);

    //
    // Limit the oversampling ratio
    //
    if(ratio > SDF_MAX_DATA_FILTER_OSR)
    {
        ratio = SDF_MAX_DATA_FILTER_OSR;
    }

    //
    // Set the comparator filter type
    //
    SDF_setFilterType(base, filter, filterType);

    //
    // Set the comparator filter over sampling ratio
    //
    SDF_setFilterOverSamplingRatio(base, filter, ratio);

    //
    // If filter switch on
    //
    if((config2 & SDF_FILTER_ENABLE) == SDF_FILTER_ENABLE)
    {
        SDF_enableFilter(base, filter);
    }
    else
    {
        SDF_disableFilter(base, filter);
    }

    //
    // Set output data format
    //
    SDF_setOutputDataFormat(base, filter,
                             (SDF_OutputDataFormat)(config2 & 0x1U));

    //
    // Set the shift value if data is in 16bit 2's complement format
    //
    if((config2 & 0x1U) == (uint16_t)(SDF_DATA_FORMAT_16_BIT))
    {
        SDF_setDataShiftValue(base, filter, SDF_GET_SHIFT_VALUE(config2));
    }

    //
    // Set the FIFO level
    //
    SDF_setFIFOInterruptLevel(base, filter, fifoLevel);
    SDF_enableFIFOBuffer(base, filter);
}


