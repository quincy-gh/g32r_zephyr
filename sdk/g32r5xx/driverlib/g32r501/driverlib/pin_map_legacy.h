//###########################################################################
//
// FILE:    pin_map.h
//
// TITLE:   Legacy definitions of pin mux info for gpio.c.
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
//
//###########################################################################

#ifndef __PIN_MAP_LEGACY_H__
#define __PIN_MAP_LEGACY_H__


#include "pin_map.h"

//*****************************************************************************
// Legacy pinmuxing MACROS - Retained for portability across devices ONLY
// Not recommended for new users
//*****************************************************************************
#define GPIO_0_PWM1A                     GPIO_0_PWM1_A
#define GPIO_0_SPISTEA                   GPIO_0_SPIA_STE
#define GPIO_0_SDAA                      GPIO_0_I2CA_SDA

#define GPIO_1_PWM1B                     GPIO_1_PWM1_B
#define GPIO_1_SCLA                      GPIO_1_I2CA_SCL
#define GPIO_1_SPISOMIA                  GPIO_1_SPIA_SOMI

#define GPIO_2_PWM2A                     GPIO_2_PWM2_A
#define GPIO_2_CANTXA                    GPIO_2_CANA_TX
#define GPIO_2_SPISIMOA                  GPIO_2_SPIA_SIMO
#define GPIO_2_PMBASDA                   GPIO_2_PMBUSA_SDA
#define GPIO_2_UARTTXDA                  GPIO_2_UARTA_TX


#define GPIO_3_PWM2B                     GPIO_3_PWM2_B
#define GPIO_3_CANRXA                    GPIO_3_CANA_RX
#define GPIO_3_PMBASCL                   GPIO_3_PMBUSA_SCL
#define GPIO_3_SPICLKA                   GPIO_3_SPIA_CLK
#define GPIO_3_UARTRXDA                  GPIO_3_UARTA_RX

#define GPIO_4_PWM3A                     GPIO_4_PWM3_A
#define GPIO_4_QEP2S                     GPIO_4_QEP2_STROBE
#define GPIO_4_SPICLKB                   GPIO_4_SPIB_CLK
#define GPIO_4_CANTXA                    GPIO_4_CANA_TX

#define GPIO_5_PWM3B                     GPIO_5_PWM3_B
#define GPIO_5_CANRXA                    GPIO_5_CANA_RX
#define GPIO_5_SPISTEA                   GPIO_5_SPIA_STE

#define GPIO_6_PWM4A                     GPIO_6_PWM4_A
#define GPIO_6_PWMSYNCO                  GPIO_6_SYNCOUT
#define GPIO_6_QEP1A                     GPIO_6_QEP1_A
#define GPIO_6_CANTXB                    GPIO_6_CANB_TX
#define GPIO_6_SPISOMIB                  GPIO_6_SPIB_SOMI

#define GPIO_7_PWM4B                     GPIO_7_PWM4_B
#define GPIO_7_QEP1B                     GPIO_7_QEP1_B
#define GPIO_7_CANRXB                    GPIO_7_CANB_RX
#define GPIO_7_SPISIMOB                  GPIO_7_SPIB_SIMO

#define GPIO_8_PWM5A                     GPIO_8_PWM5_A
#define GPIO_8_CANTXB                    GPIO_8_CANB_TX
#define GPIO_8_QEP1S                     GPIO_8_QEP1_STROBE
#define GPIO_8_UARTTXDA                  GPIO_8_UARTA_TX
#define GPIO_8_SPISIMOA                  GPIO_8_SPIA_SIMO
#define GPIO_8_SCLA                      GPIO_8_I2CA_SCL

#define GPIO_9_PWM5B                     GPIO_9_PWM5_B
#define GPIO_9_UARTTXDB                  GPIO_9_UARTB_TX
#define GPIO_9_QEP1I                     GPIO_9_QEP1_INDEX
#define GPIO_9_UARTRXDA                  GPIO_9_UARTA_RX
#define GPIO_9_SPICLKA                   GPIO_9_SPIA_CLK

#define GPIO_10_PWM6A                    GPIO_10_PWM6_A
#define GPIO_10_CANRXB                   GPIO_10_CANB_RX
#define GPIO_10_QEP1A                    GPIO_10_QEP1_A
#define GPIO_10_UARTTXDB                 GPIO_10_UARTB_TX
#define GPIO_10_SPISOMIA                 GPIO_10_SPIA_SOMI
#define GPIO_10_SDAA                     GPIO_10_I2CA_SDA

#define GPIO_11_PWM6B                    GPIO_11_PWM6_B
#define GPIO_11_UARTRXDB                 GPIO_11_UARTB_RX
#define GPIO_11_QEP1B                    GPIO_11_QEP1_B
#define GPIO_11_SPISTEA                  GPIO_11_SPIA_STE
#define GPIO_11_QEP2A                    GPIO_11_QEP2_A
#define GPIO_11_SPISIMOA                 GPIO_11_SPIA_SIMO

#define GPIO_12_PWM7A                    GPIO_12_PWM7_A
#define GPIO_12_CANTXB                   GPIO_12_CANB_TX
#define GPIO_12_SPICLKA                  GPIO_12_SPIA_CLK
#define GPIO_12_QEP1S                    GPIO_12_QEP1_STROBE
#define GPIO_12_UARTTXDB                 GPIO_12_UARTB_TX
#define GPIO_12_PMBACTL                  GPIO_12_PMBUSA_CTL
#define GPIO_12_CANRXA                   GPIO_12_CANA_RX

#define GPIO_13_PWM7B                    GPIO_13_PWM7_B
#define GPIO_13_CANRXB                   GPIO_13_CANB_RX
#define GPIO_13_SPISOMIA                 GPIO_13_SPIA_SOMI
#define GPIO_13_QEP1I                    GPIO_13_QEP1_INDEX
#define GPIO_13_UARTRXDB                 GPIO_13_UARTB_RX
#define GPIO_13_PMBAALRT                 GPIO_13_PMBUSA_ALERT
#define GPIO_13_CANTXA                   GPIO_13_CANA_TX

#define GPIO_14_PWM8A                    GPIO_14_PWM8_A
#define GPIO_14_UARTTXDB                 GPIO_14_UARTB_TX
#define GPIO_14_PWM3A                    GPIO_14_PWM3_A
#define GPIO_14_PMBASDA                  GPIO_14_PMBUSA_SDA
#define GPIO_14_SPICLKB                  GPIO_14_SPIB_CLK
#define GPIO_14_QEP2A                    GPIO_14_QEP2_A

#define GPIO_15_PWM8B                    GPIO_15_PWM8_B
#define GPIO_15_UARTRXDB                 GPIO_15_UARTB_RX
#define GPIO_15_PWM3B                    GPIO_15_PWM3_B
#define GPIO_15_PMBASCL                  GPIO_15_PMBUSA_SCL
#define GPIO_15_SPISTEB                  GPIO_15_SPIB_STE
#define GPIO_15_QEP2B                    GPIO_15_QEP2_B

#define GPIO_16_SPISIMOA                 GPIO_16_SPIA_SIMO
#define GPIO_16_CANTXB                   GPIO_16_CANB_TX
#define GPIO_16_PWM5A                    GPIO_16_PWM5_A
#define GPIO_16_UARTTXDA                 GPIO_16_UARTA_TX
#define GPIO_16_SD_D1                    GPIO_16_SD1_D1
#define GPIO_16_QEP1S                    GPIO_16_QEP1_STROBE
#define GPIO_16_PMBASCL                  GPIO_16_PMBUSA_SCL
#define GPIO_16_SPISOMIB                 GPIO_16_SPIB_SOMI
#define GPIO_16_QEP2B                    GPIO_16_QEP2_B

#define GPIO_17_SPISOMIA                 GPIO_17_SPIA_SOMI
#define GPIO_17_CANRXB                   GPIO_17_CANB_RX
#define GPIO_17_PWM5B                    GPIO_17_PWM5_B
#define GPIO_17_UARTRXDA                 GPIO_17_UARTA_RX
#define GPIO_17_SD_C1                    GPIO_17_SD1_C1
#define GPIO_17_QEP1I                    GPIO_17_QEP1_INDEX
#define GPIO_17_PMBASDA                  GPIO_17_PMBUSA_SDA
#define GPIO_17_CANTXA                   GPIO_17_CANA_TX

#define GPIO_18_GPIO18                   GPIO_18_GPIO18_X2
#define GPIO_18_SPICLKA                  GPIO_18_SPIA_CLK
#define GPIO_18_UARTTXDB                 GPIO_18_UARTB_TX
#define GPIO_18_CANRXA                   GPIO_18_CANA_RX
#define GPIO_18_PWM6A                    GPIO_18_PWM6_A
#define GPIO_18_SCLA                     GPIO_18_I2CA_SCL
#define GPIO_18_SD_D2                    GPIO_18_SD1_D2
#define GPIO_18_QEP2A                    GPIO_18_QEP2_A
#define GPIO_18_PMBACTL                  GPIO_18_PMBUSA_CTL

#define GPIO_19_SPISTEA                  GPIO_19_SPIA_STE
#define GPIO_19_UARTRXDB                 GPIO_19_UARTB_RX
#define GPIO_19_CANTXA                   GPIO_19_CANA_TX
#define GPIO_19_PWM6B                    GPIO_19_PWM6_B
#define GPIO_19_SDAA                     GPIO_19_I2CA_SDA
#define GPIO_19_SD_C2                    GPIO_19_SD1_C2
#define GPIO_19_QEP2B                    GPIO_19_QEP2_B
#define GPIO_19_PMBAALRT                 GPIO_19_PMBUSA_ALERT

#define GPIO_20_QEP1A                    GPIO_20_QEP1_A
#define GPIO_20_CANTXB                   GPIO_20_CANB_TX
#define GPIO_20_SPISIMOB                 GPIO_20_SPIB_SIMO
#define GPIO_20_SD_D3                    GPIO_20_SD1_D3
#define GPIO_20_SPICLKB                  GPIO_20_SPIB_CLK

#define GPIO_21_QEP1B                    GPIO_21_QEP1_B
#define GPIO_21_CANRXB                   GPIO_21_CANB_RX
#define GPIO_21_SPISOMIB                 GPIO_21_SPIB_SOMI
#define GPIO_21_SD_C3                    GPIO_21_SD1_C3
#define GPIO_21_SCLA                     GPIO_21_I2CA_SCL

#define GPIO_22_GPIO22                   GPIO_22_GPIO22_VFBSW
#define GPIO_22_QEP1S                    GPIO_22_QEP1_STROBE
#define GPIO_22_UARTTXDB                 GPIO_22_UARTB_TX
#define GPIO_22_PWM4A                    GPIO_22_PWM4_A
#define GPIO_22_SPICLKB                  GPIO_22_SPIB_CLK
#define GPIO_22_SD_D4                    GPIO_22_SD1_D4
#define GPIO_22_LINTXA                   GPIO_22_LINA_TX

#define GPIO_23_QEP1I                    GPIO_23_QEP1_INDEX
#define GPIO_23_UARTRXDB                 GPIO_23_UARTB_RX
#define GPIO_23_PWM4B                    GPIO_23_PWM4_B
#define GPIO_23_SPISTEB                  GPIO_23_SPIB_STE
#define GPIO_23_SD_C4                    GPIO_23_SD1_C4
#define GPIO_23_LINRXA                   GPIO_23_LINA_RX
#define GPIO_23_SDAA                     GPIO_23_I2CA_SDA
#define GPIO_23_SPISIMOB                 GPIO_23_SPIB_SIMO

#define GPIO_24_QEP2A                    GPIO_24_QEP2_A
#define GPIO_24_PWM8A                    GPIO_24_PWM8_A
#define GPIO_24_SPISIMOB                 GPIO_24_SPIB_SIMO
#define GPIO_24_SD_D1                    GPIO_24_SD1_D1
#define GPIO_24_PMBASCL                  GPIO_24_PMBUSA_SCL
#define GPIO_24_UARTTXDA                 GPIO_24_UARTA_TX
#define GPIO_24_ERROR_STS                GPIO_24_ERRORSTS

#define GPIO_25_QEP2B                    GPIO_25_QEP2_B
#define GPIO_25_QEP1A                    GPIO_25_QEP1_A
#define GPIO_25_SPISOMIB                 GPIO_25_SPIB_SOMI
#define GPIO_25_SD_C1                    GPIO_25_SD1_C1
#define GPIO_25_PMBASDA                  GPIO_25_PMBUSA_SDA
#define GPIO_25_UARTRXDA                 GPIO_25_UARTA_RX

#define GPIO_26_QEP2I                    GPIO_26_QEP2_INDEX
#define GPIO_26_SPICLKB                  GPIO_26_SPIB_CLK
#define GPIO_26_SD_D2                    GPIO_26_SD1_D2
#define GPIO_26_PMBACTL                  GPIO_26_PMBUSA_CTL
#define GPIO_26_SDAA                     GPIO_26_I2CA_SDA

#define GPIO_27_QEP2S                    GPIO_27_QEP2_STROBE
#define GPIO_27_SPISTEB                  GPIO_27_SPIB_STE
#define GPIO_27_SD_C2                    GPIO_27_SD1_C2
#define GPIO_27_PMBAALRT                 GPIO_27_PMBUSA_ALERT
#define GPIO_27_SCLA                     GPIO_27_I2CA_SCL

#define GPIO_28_UARTRXDA                 GPIO_28_UARTA_RX
#define GPIO_28_PWM7A                    GPIO_28_PWM7_A
#define GPIO_28_QEP1A                    GPIO_28_QEP1_A
#define GPIO_28_SD_D3                    GPIO_28_SD1_D3
#define GPIO_28_QEP2S                    GPIO_28_QEP2_STROBE
#define GPIO_28_LINTXA                   GPIO_28_LINA_TX
#define GPIO_28_SPICLKB                  GPIO_28_SPIB_CLK
#define GPIO_28_ERROR_STS                GPIO_28_ERRORSTS

#define GPIO_29_UARTTXDA                 GPIO_29_UARTA_TX
#define GPIO_29_PWM7B                    GPIO_29_PWM7_B
#define GPIO_29_QEP1B                    GPIO_29_QEP1_B
#define GPIO_29_SD_C3                    GPIO_29_SD1_C3
#define GPIO_29_QEP2I                    GPIO_29_QEP2_INDEX
#define GPIO_29_LINRXA                   GPIO_29_LINA_RX
#define GPIO_29_SPISTEB                  GPIO_29_SPIB_STE
#define GPIO_29_ERROR_STS                GPIO_29_ERRORSTS

#define GPIO_30_CANRXA                   GPIO_30_CANA_RX
#define GPIO_30_PWM1A                    GPIO_30_PWM1_A
#define GPIO_30_SPISIMOB                 GPIO_30_SPIB_SIMO
#define GPIO_30_QEP1S                    GPIO_30_QEP1_STROBE
#define GPIO_30_SD_D4                    GPIO_30_SD1_D4

#define GPIO_31_CANTXA                   GPIO_31_CANA_TX
#define GPIO_31_PWM1B                    GPIO_31_PWM1_B
#define GPIO_31_SPISOMIB                 GPIO_31_SPIB_SOMI
#define GPIO_31_QEP1I                    GPIO_31_QEP1_INDEX
#define GPIO_31_SD_C4                    GPIO_31_SD1_C4

#define GPIO_32_SDAA                     GPIO_32_I2CA_SDA
#define GPIO_32_SPICLKB                  GPIO_32_SPIB_CLK
#define GPIO_32_PWM8B                    GPIO_32_PWM8_B
#define GPIO_32_LINTXA                   GPIO_32_LINA_TX
#define GPIO_32_SD_D3                    GPIO_32_SD1_D3
#define GPIO_32_CANTXA                   GPIO_32_CANA_TX

#define GPIO_33_SCLA                     GPIO_33_I2CA_SCL
#define GPIO_33_QEP2B                    GPIO_33_QEP2_B
#define GPIO_33_SPISTEB                  GPIO_33_SPIB_STE
#define GPIO_33_LINRXA                   GPIO_33_LINA_RX
#define GPIO_33_SD_C3                    GPIO_33_SD1_C3
#define GPIO_33_CANRXA                   GPIO_33_CANA_RX

#define GPIO_34_PMBASDA                  GPIO_34_PMBUSA_SDA

#define GPIO_35_UARTRXDA                 GPIO_35_UARTA_RX
#define GPIO_35_SDAA                     GPIO_35_I2CA_SDA
#define GPIO_35_CANRXA                   GPIO_35_CANA_RX
#define GPIO_35_PMBASCL                  GPIO_35_PMBUSA_SCL
#define GPIO_35_LINRXA                   GPIO_35_LINA_RX
#define GPIO_35_QEP1A                    GPIO_35_QEP1_A
#define GPIO_35_PMBACTL                  GPIO_35_PMBUSA_CTL

#define GPIO_37_SCLA                     GPIO_37_I2CA_SCL
#define GPIO_37_UARTTXDA                 GPIO_37_UARTA_TX
#define GPIO_37_CANTXA                   GPIO_37_CANA_TX
#define GPIO_37_LINTXA                   GPIO_37_LINA_TX
#define GPIO_37_QEP1B                    GPIO_37_QEP1_B
#define GPIO_37_PMBAALRT                 GPIO_37_PMBUSA_ALERT

#define GPIO_39_CANRXB                   GPIO_39_CANB_RX

#define GPIO_40_PMBASDA                  GPIO_40_PMBUSA_SDA
#define GPIO_40_UARTTXDB                 GPIO_40_UARTB_TX
#define GPIO_40_QEP1A                    GPIO_40_QEP1_A

#define GPIO_41_PWM2A                    GPIO_41_PWM2_A
#define GPIO_41_SPISTEB                  GPIO_41_SPIB_STE
#define GPIO_41_PMBASCL                  GPIO_41_PMBUSA_SCL
#define GPIO_41_UARTRXDB                 GPIO_41_UARTB_RX
#define GPIO_41_QEP1B                    GPIO_41_QEP1_B
#define GPIO_41_SPISOMIB                 GPIO_41_SPIB_SOMI

#define GPIO_42_LINRXA                   GPIO_42_LINA_RX
#define GPIO_42_PMBACTL                  GPIO_42_PMBUSA_CTL
#define GPIO_42_SDAA                     GPIO_42_I2CA_SDA
#define GPIO_42_UARTRXDB                 GPIO_42_UARTB_RX
#define GPIO_42_QEP1S                    GPIO_42_QEP1_STROBE

#define GPIO_43_PMBAALRT                 GPIO_43_PMBUSA_ALERT
#define GPIO_43_SCLA                     GPIO_43_I2CA_SCL
#define GPIO_43_UARTTXDB                 GPIO_43_UARTB_TX
#define GPIO_43_QEP1I                    GPIO_43_QEP1_INDEX

#define GPIO_44_QEP1A                    GPIO_44_QEP1_A

#define GPIO_46_LINTXA                   GPIO_46_LINA_TX

#define GPIO_47_PWM2B                    GPIO_47_PWM2_B
#define GPIO_47_QEP1A                    GPIO_47_QEP1_A
#define GPIO_47_LINRXA                   GPIO_47_LINA_RX
#define GPIO_47_SPISIMOB                 GPIO_47_SPIB_SIMO
#define GPIO_47_PMBASDA                  GPIO_47_PMBUSA_SDA

#define GPIO_48_CANTXB                   GPIO_48_CANB_TX
#define GPIO_48_UARTTXDA                 GPIO_48_UARTA_TX
#define GPIO_48_SD_D1                    GPIO_48_SD1_D1

#define GPIO_49_QEP1I                    GPIO_49_QEP1_INDEX
#define GPIO_49_CANRXB                   GPIO_49_CANB_RX
#define GPIO_49_UARTRXDA                 GPIO_49_UARTA_RX
#define GPIO_49_SD_C1                    GPIO_49_SD1_C1
#define GPIO_49_QEP2I                    GPIO_49_QEP2_INDEX
#define GPIO_49_PWMSYNCO                 GPIO_49_SYNCOUT

#define GPIO_50_QEP1A                    GPIO_50_QEP1_A
#define GPIO_50_SPISIMOB                 GPIO_50_SPIB_SIMO
#define GPIO_50_SD_D2                    GPIO_50_SD1_D2

#define GPIO_51_QEP1B                    GPIO_51_QEP1_B
#define GPIO_51_SPISOMIB                 GPIO_51_SPIB_SOMI
#define GPIO_51_SD_C2                    GPIO_51_SD1_C2

#define GPIO_52_QEP1S                    GPIO_52_QEP1_STROBE
#define GPIO_52_SPICLKB                  GPIO_52_SPIB_CLK
#define GPIO_52_SD_D3                    GPIO_52_SD1_D3

#define GPIO_53_QEP1I                    GPIO_53_QEP1_INDEX
#define GPIO_53_SPISTEB                  GPIO_53_SPIB_STE
#define GPIO_53_SD_C3                    GPIO_53_SD1_C3
#define GPIO_53_UARTRXDB                 GPIO_53_UARTB_RX

#define GPIO_54_SPISIMOA                 GPIO_54_SPIA_SIMO
#define GPIO_54_QEP2A                    GPIO_54_QEP2_A
#define GPIO_54_UARTTXDB                 GPIO_54_UARTB_TX
#define GPIO_54_SD_D4                    GPIO_54_SD1_D4

#define GPIO_55_SPISOMIA                 GPIO_55_SPIA_SOMI
#define GPIO_55_QEP2B                    GPIO_55_QEP2_B
#define GPIO_55_UARTRXDB                 GPIO_55_UARTB_RX
#define GPIO_55_SD_C4                    GPIO_55_SD1_C4

#define GPIO_56_SPICLKA                  GPIO_56_SPIA_CLK
#define GPIO_56_QEP2S                    GPIO_56_QEP2_STROBE
#define GPIO_56_UARTTXDB                 GPIO_56_UARTB_TX
#define GPIO_56_SD_D3                    GPIO_56_SD1_D3
#define GPIO_56_SPISIMOB                 GPIO_56_SPIB_SIMO
#define GPIO_56_QEP1A                    GPIO_56_QEP1_A

#define GPIO_57_SPISTEA                  GPIO_57_SPIA_STE
#define GPIO_57_QEP2I                    GPIO_57_QEP2_INDEX
#define GPIO_57_UARTRXDB                 GPIO_57_UARTB_RX
#define GPIO_57_SD_C3                    GPIO_57_SD1_C3
#define GPIO_57_SPISOMIB                 GPIO_57_SPIB_SOMI
#define GPIO_57_QEP1B                    GPIO_57_QEP1_B

#define GPIO_58_SPICLKB                  GPIO_58_SPIB_CLK
#define GPIO_58_SD_D4                    GPIO_58_SD1_D4
#define GPIO_58_LINTXA                   GPIO_58_LINA_TX
#define GPIO_58_CANTXB                   GPIO_58_CANB_TX
#define GPIO_58_QEP1S                    GPIO_58_QEP1_STROBE

#define GPIO_59_SPISTEB                  GPIO_59_SPIB_STE
#define GPIO_59_SD_C4                    GPIO_59_SD1_C4
#define GPIO_59_LINRXA                   GPIO_59_LINA_RX
#define GPIO_59_CANRXB                   GPIO_59_CANB_RX
#define GPIO_59_QEP1I                    GPIO_59_QEP1_INDEX

#endif // __PIN_MAP_LEGACY_H__
