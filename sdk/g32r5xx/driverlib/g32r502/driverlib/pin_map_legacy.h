//###########################################################################
//
// FILE:    pin_map_legacy.h
//
// TITLE:   Legacy definitions of pin mux info for gpio.c.
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

#define GPIO_0_PWM1A           GPIO_0_PWM1_A
#define GPIO_0_CANRXA          GPIO_0_CANA_RX
#define GPIO_0_UARTRXDA        GPIO_0_UARTA_RX
#define GPIO_0_SDAA            GPIO_0_I2CA_SDA
#define GPIO_0_SPISTEA         GPIO_0_SPIA_STE
#define GPIO_0_CANFDRXA        GPIO_0_CANFD_RX
#define GPIO_0_QEP1I           GPIO_0_QEP1_INDEX
#define GPIO_0_PWM3A           GPIO_0_PWM3_A

#define GPIO_1_PWM1B           GPIO_1_PWM1_B
#define GPIO_1_UARTTXDA        GPIO_1_UARTA_TX
#define GPIO_1_SCLA            GPIO_1_I2CA_SCL
#define GPIO_1_SPISOMIA        GPIO_1_SPIA_SOMI
#define GPIO_1_QEP1S           GPIO_1_QEP1_STROBE
#define GPIO_1_CANFDTXA        GPIO_1_CANFD_TX
#define GPIO_1_PWM3B           GPIO_1_PWM3_B

#define GPIO_2_PWM2A           GPIO_2_PWM2_A
#define GPIO_2_PMBA_SDA        GPIO_2_PMBUSA_SDA
#define GPIO_2_SPISIMOA        GPIO_2_SPIA_SIMO
#define GPIO_2_UARTTXDA        GPIO_2_UARTA_TX
#define GPIO_2_SDAB            GPIO_2_I2CB_SDA
#define GPIO_2_CANTXA          GPIO_2_CANA_TX
#define GPIO_2_PWM4A           GPIO_2_PWM4_A

#define GPIO_3_PWM2B           GPIO_3_PWM2_B
#define GPIO_3_PMBA_SCL        GPIO_3_PMBUSA_SCL
#define GPIO_3_SPICLKA         GPIO_3_SPIA_CLK
#define GPIO_3_UARTRXDA        GPIO_3_UARTA_RX
#define GPIO_3_SCLB            GPIO_3_I2CB_SCL 
#define GPIO_3_CANRXA          GPIO_3_CANA_RX
#define GPIO_3_PWM4B           GPIO_3_PWM4_B

#define GPIO_4_PWM3A           GPIO_4_PWM3_A
#define GPIO_4_SCLA            GPIO_4_I2CA_SCL
#define GPIO_4_CANFDTXA        GPIO_4_CANFD_TX
#define GPIO_4_CANTXA          GPIO_4_CANA_TX
#define GPIO_4_SPISOMIA        GPIO_4_SPIA_SOMI
#define GPIO_4_PWM1A           GPIO_4_PWM1_A

#define GPIO_5_PWM3B           GPIO_5_PWM3_B
#define GPIO_5_SDAA            GPIO_5_I2CA_SDA
#define GPIO_5_CANFDRXA        GPIO_5_CANFD_RX
#define GPIO_5_CANRXA          GPIO_5_CANA_RX
#define GPIO_5_SPISTEA         GPIO_5_SPIA_STE
#define GPIO_5_UARTRXDA        GPIO_5_UARTA_RX
#define GPIO_5_PWM1B           GPIO_5_PWM1_B

#define GPIO_6_PWM4A           GPIO_6_PWM4_A
#define GPIO_6_PWMSYNCO        GPIO_6_SYNCOUT
#define GPIO_6_QEP1A           GPIO_6_QEP1_A
#define GPIO_6_PWM2A           GPIO_6_PWM2_A

#define GPIO_7_PWM4B           GPIO_7_PWM4_B
#define GPIO_7_PWM2A           GPIO_7_PWM2_A
#define GPIO_7_QEP1B           GPIO_7_QEP1_B
#define GPIO_7_SPISIMOA        GPIO_7_SPIA_SIMO
#define GPIO_7_UARTTXDA        GPIO_7_UARTA_TX
#define GPIO_7_CANTXA          GPIO_7_CANA_TX
#define GPIO_7_PWM2B           GPIO_7_PWM2_B

#define GPIO_8_PWM5A           GPIO_8_PWM5_A
#define GPIO_8_QEP1S           GPIO_8_QEP1_STROBE
#define GPIO_8_UARTTXDA        GPIO_8_UARTA_TX
#define GPIO_8_SPISIMOA        GPIO_8_SPIA_SIMO
#define GPIO_8_SCLA            GPIO_8_I2CA_SCL

#define GPIO_9_PWM5B           GPIO_9_PWM5_B
#define GPIO_9_UARTTXDB        GPIO_9_UARTB_TX
#define GPIO_9_QEP1I           GPIO_9_QEP1_INDEX
#define GPIO_9_UARTRXDA        GPIO_9_UARTA_RX
#define GPIO_9_SPICLKA         GPIO_9_SPIA_CLK
#define GPIO_9_SCLB            GPIO_9_I2CB_SCL

#define GPIO_10_PWM6A          GPIO_10_PWM6_A
#define GPIO_10_QEP1A          GPIO_10_QEP1_A
#define GPIO_10_UARTTXDB       GPIO_10_UARTB_TX
#define GPIO_10_SPISOMIA       GPIO_10_SPIA_SOMI
#define GPIO_10_SDAA           GPIO_10_I2CA_SDA

#define GPIO_11_PWM6B          GPIO_11_PWM6_B
#define GPIO_11_CANRXA         GPIO_11_CANA_RX
#define GPIO_11_QEP1B          GPIO_11_QEP1_B
#define GPIO_11_UARTRXDB       GPIO_11_UARTB_RX
#define GPIO_11_SPISTEA        GPIO_11_SPIA_STE
#define GPIO_11_SPISIMOA       GPIO_11_SPIA_SIMO

#define GPIO_12_PWM7A          GPIO_12_PWM7_A
#define GPIO_12_CANFDRXA       GPIO_12_CANFD_RX
#define GPIO_12_QEP1S          GPIO_12_QEP1_STROBE
#define GPIO_12_UARTTXDB       GPIO_12_UARTB_TX
#define GPIO_12_PMBACTL        GPIO_12_PMBUSA_CTL
#define GPIO_12_SPICLKA        GPIO_12_SPIA_CLK
#define GPIO_12_CANRXA         GPIO_12_CANA_RX

#define GPIO_13_PWM7B          GPIO_13_PWM7_B
#define GPIO_13_CANFDTXA       GPIO_13_CANFD_TX
#define GPIO_13_QEP1I          GPIO_13_QEP1_INDEX
#define GPIO_13_UARTRXDB       GPIO_13_UARTB_RX
#define GPIO_13_PMBAALRT       GPIO_13_PMBUSA_ALERT
#define GPIO_13_SPISOMIA       GPIO_13_SPIA_SOMI
#define GPIO_13_CANTXA         GPIO_13_CANA_TX

#define GPIO_14_UARTTXDB       GPIO_14_UARTB_TX
#define GPIO_14_SDAB           GPIO_14_I2CB_SDA
#define GPIO_14_PMBA_SDA       GPIO_14_PMBUSA_SDA
#define GPIO_14_PWM3A          GPIO_14_PWM3_A

#define GPIO_15_UARTRXDB       GPIO_15_UARTB_RX
#define GPIO_15_SCLB           GPIO_15_I2CB_SCL
#define GPIO_15_PMBA_SCL       GPIO_15_PMBUSA_SCL
#define GPIO_15_PWM3B          GPIO_15_PWM3_B

#define GPIO_16_SPISIMOA       GPIO_16_SPIA_SIMO
#define GPIO_16_PWM5A          GPIO_16_PWM5_A
#define GPIO_16_UARTTXDA       GPIO_16_UARTA_TX
#define GPIO_16_QEP1S          GPIO_16_QEP1_STROBE
#define GPIO_16_PMBA_SCL       GPIO_16_PMBUSA_SCL

#define GPIO_17_SPISOMIA       GPIO_17_SPIA_SOMI
#define GPIO_17_PWM5B          GPIO_17_PWM5_B
#define GPIO_17_UARTRXDA       GPIO_17_UARTA_RX
#define GPIO_17_QEP1I          GPIO_17_QEP1_INDEX
#define GPIO_17_PMBA_SDA       GPIO_17_PMBUSA_SDA
#define GPIO_17_CANTXA         GPIO_17_CANA_TX
#define GPIO_17_PWM6A          GPIO_17_PWM6_A

#define GPIO_18_SPICLKA        GPIO_18_SPIA_CLK
#define GPIO_18_UARTTXDB       GPIO_18_UARTB_TX
#define GPIO_18_CANRXA         GPIO_18_CANA_RX
#define GPIO_18_PWM6A          GPIO_18_PWM6_A
#define GPIO_18_SCLA           GPIO_18_I2CA_SCL
#define GPIO_18_PMBACTL        GPIO_18_PMBUSA_CTL

#define GPIO_19_SPISTEA        GPIO_19_SPIA_STE
#define GPIO_19_UARTRXDB       GPIO_19_UARTB_RX
#define GPIO_19_CANTXA         GPIO_19_CANA_TX
#define GPIO_19_PWM6B          GPIO_19_PWM6_B
#define GPIO_19_SDAA           GPIO_19_I2CA_SDA
#define GPIO_19_PMBAALRT       GPIO_19_PMBUSA_ALERT

#define GPIO_20_QEP1A          GPIO_20_QEP1_A
#define GPIO_20_CANTXA         GPIO_20_CANA_TX
#define GPIO_20_SPISIMOA       GPIO_20_SPIA_SIMO
#define GPIO_20_CANFDTXA        GPIO_20_CANFD_TX
#define GPIO_20_SCLA           GPIO_20_I2CA_SCL
#define GPIO_20_UARTTXDC       GPIO_20_UARTC_TX

#define GPIO_21_QEP1B          GPIO_21_QEP1_B
#define GPIO_21_CANRXA         GPIO_21_CANA_RX
#define GPIO_21_SPISOMIA       GPIO_21_SPIA_SOMI
#define GPIO_21_CANFDRXA       GPIO_21_CANFD_RX
#define GPIO_21_SDAA           GPIO_21_I2CA_SDA
#define GPIO_21_UARTRXDC       GPIO_21_UARTC_RX

#define GPIO_22_QEP1S          GPIO_22_QEP1_STROBE
#define GPIO_22_UARTTXDB       GPIO_22_UARTB_TX
#define GPIO_22_LINTXA         GPIO_22_LINA_TX
#define GPIO_22_PWM4A          GPIO_22_PWM4_A

#define GPIO_23_QEP1I          GPIO_23_QEP1_INDEX
#define GPIO_23_UARTRXDB       GPIO_23_UARTB_RX
#define GPIO_23_LINRXA         GPIO_23_LINA_RX
#define GPIO_23_PWM4B          GPIO_23_PWM4_B

#define GPIO_24_SPISTEA        GPIO_24_SPIA_STE
#define GPIO_24_PWM4A          GPIO_24_PWM4_A
#define GPIO_24_SPISIMOA       GPIO_24_SPIA_SIMO
#define GPIO_24_PMBA_SCL       GPIO_24_PMBUSA_SCL
#define GPIO_24_UARTTXDA       GPIO_24_UARTA_TX
#define GPIO_24_ERROR_STS      GPIO_24_ERRORSTS

#define GPIO_25_QEP1A          GPIO_25_QEP1_A
#define GPIO_25_PMBA_SDA       GPIO_25_PMBUSA_SDA
#define GPIO_25_UARTRXDA       GPIO_25_UARTA_RX

#define GPIO_26_PMBACTL        GPIO_26_PMBUSA_CTL
#define GPIO_26_SDAA           GPIO_26_I2CA_SDA

#define GPIO_27_PMBAALRT       GPIO_27_PMBUSA_ALERT
#define GPIO_27_SCLA           GPIO_27_I2CA_SCL

#define GPIO_28_UARTRXDA       GPIO_28_UARTA_RX
#define GPIO_28_PWM7A          GPIO_28_PWM7_A
#define GPIO_28_QEP1A          GPIO_28_QEP1_A
#define GPIO_28_LINTXA         GPIO_28_LINA_TX
#define GPIO_28_SPICLKA        GPIO_28_SPIA_CLK
#define GPIO_28_ERROR_STS      GPIO_28_ERRORSTS
#define GPIO_28_SDAB           GPIO_28_I2CB_SDA

#define GPIO_29_UARTTXDA       GPIO_29_UARTA_TX
#define GPIO_29_PWM7B          GPIO_29_PWM7_B
#define GPIO_29_QEP1B          GPIO_29_QEP1_B
#define GPIO_29_LINRXA         GPIO_29_LINA_RX
#define GPIO_29_SPISTEA        GPIO_29_SPIA_STE
#define GPIO_29_ERROR_STS      GPIO_29_ERRORSTS
#define GPIO_29_SCLB           GPIO_29_I2CB_SCL

#define GPIO_30_CANRXA         GPIO_30_CANA_RX
#define GPIO_30_QEP1S          GPIO_30_QEP1_STROBE
#define GPIO_30_CANFDRXA       GPIO_30_CANFD_RX
#define GPIO_30_PWM1A          GPIO_30_PWM1_A

#define GPIO_31_CANTXA         GPIO_31_CANA_TX
#define GPIO_31_QEP1I          GPIO_31_QEP1_INDEX
#define GPIO_31_CANFDTXA       GPIO_31_CANFD_TX
#define GPIO_31_PWM1B          GPIO_31_PWM1_B

#define GPIO_32_SDAA           GPIO_32_I2CA_SDA
#define GPIO_32_QEP1I          GPIO_32_QEP1_INDEX
#define GPIO_32_SPICLKA        GPIO_32_SPIA_CLK
#define GPIO_32_PWM4B          GPIO_32_PWM4_B
#define GPIO_32_LINTXA         GPIO_32_LINA_TX
#define GPIO_32_CANTXA         GPIO_32_CANA_TX
#define GPIO_32_PMBA_SDA       GPIO_32_PMBUSA_SDA

#define GPIO_33_SCLA           GPIO_33_I2CA_SCL
#define GPIO_33_LINRXA         GPIO_33_LINA_RX
#define GPIO_33_CANRXA         GPIO_33_CANA_RX

#define GPIO_34_PMBA_SDA       GPIO_34_PMBUSA_SDA
#define GPIO_34_SDAB           GPIO_34_I2CB_SDA

#define GPIO_35_UARTRXDA       GPIO_35_UARTA_RX
#define GPIO_35_SPISOMIA       GPIO_35_SPIA_SOMI
#define GPIO_35_SDAA           GPIO_35_I2CA_SDA
#define GPIO_35_CANRXA         GPIO_35_CANA_RX
#define GPIO_35_PMBA_SCL       GPIO_35_PMBUSA_SCL
#define GPIO_35_LINRXA         GPIO_35_LINA_RX
#define GPIO_35_QEP1A          GPIO_35_QEP1_A
#define GPIO_35_PMBACTL        GPIO_35_PMBUSA_CTL
#define GPIO_35_PWM5B          GPIO_35_PWM5_B

#define GPIO_37_SPISTEA        GPIO_37_SPIA_STE
#define GPIO_37_SCLA           GPIO_37_I2CA_SCL
#define GPIO_37_UARTTXDA       GPIO_37_UARTA_TX
#define GPIO_37_CANTXA         GPIO_37_CANA_TX
#define GPIO_37_LINTXA         GPIO_37_LINA_TX
#define GPIO_37_QEP1B          GPIO_37_QEP1_B
#define GPIO_37_PMBAALRT       GPIO_37_PMBUSA_ALERT
#define GPIO_37_PWM5A          GPIO_37_PWM5_A

#define GPIO_39_CANFDRXA       GPIO_39_CANFD_RX
#define GPIO_39_PWMSYNCO       GPIO_39_SYNCOUT
#define GPIO_39_QEP1I          GPIO_39_QEP1_INDEX

#define GPIO_40_PWM2B          GPIO_40_PWM2_B
#define GPIO_40_PMBA_SDA       GPIO_40_PMBUSA_SDA
#define GPIO_40_UARTTXDB       GPIO_40_UARTB_TX
#define GPIO_40_QEP1A          GPIO_40_QEP1_A

#define GPIO_41_PWM7A          GPIO_41_PWM7_A
#define GPIO_41_PWM2A          GPIO_41_PWM2_A
#define GPIO_41_PMBA_SCL       GPIO_41_PMBUSA_SCL
#define GPIO_41_UARTRXDB       GPIO_41_UARTB_RX
#define GPIO_41_QEP1B          GPIO_41_QEP1_B

#define GPIO_42_LINRXA         GPIO_42_LINA_RX
#define GPIO_42_PMBACTL        GPIO_42_PMBUSA_CTL
#define GPIO_42_SDAA           GPIO_42_I2CA_SDA
#define GPIO_42_UARTRXDC       GPIO_42_UARTC_RX
#define GPIO_42_QEP1S          GPIO_42_QEP1_STROBE

#define GPIO_43_PMBAALRT       GPIO_43_PMBUSA_ALERT
#define GPIO_43_SCLA           GPIO_43_I2CA_SCL
#define GPIO_43_UARTTXDC       GPIO_43_UARTC_TX
#define GPIO_43_QEP1I          GPIO_43_QEP1_INDEX

#define GPIO_44_QEP1A          GPIO_44_QEP1_A
#define GPIO_44_PMBA_SDA       GPIO_44_PMBUSA_SDA
#define GPIO_44_PMBACTL        GPIO_44_PMBUSA_CTL

#define GPIO_45_PMBAALRT       GPIO_45_PMBUSA_ALERT

#define GPIO_46_LINTXA         GPIO_46_LINA_TX
#define GPIO_46_CANFDTXA       GPIO_46_CANFD_TX
#define GPIO_46_PMBA_SDA       GPIO_46_PMBUSA_SDA

#define GPIO_48_CANTXA         GPIO_48_CANA_TX
#define GPIO_48_CANFDTXA        GPIO_48_CANFD_TX
#define GPIO_48_UARTTXDA       GPIO_48_UARTA_TX
#define GPIO_48_PMBA_SDA       GPIO_48_PMBUSA_SDA

#define GPIO_49_CANRXA         GPIO_49_CANA_RX
#define GPIO_49_CANFDRXA       GPIO_49_CANFD_RX
#define GPIO_49_UARTRXDA       GPIO_49_UARTA_RX
#define GPIO_49_LINRXA         GPIO_49_LINA_RX

#define GPIO_224_SPISIMOA      GPIO_224_SPIA_SIMO
#define GPIO_224_PWM1A         GPIO_224_PWM1_A
#define GPIO_224_CANTXA        GPIO_224_CANA_TX
#define GPIO_224_QEP1A         GPIO_224_QEP1_A
#define GPIO_224_UARTTXDC      GPIO_224_UARTC_TX

#define GPIO_226_LINRXA        GPIO_226_LINA_RX
#define GPIO_226_PWM6A         GPIO_226_PWM6_A
#define GPIO_226_SPICLKA       GPIO_226_SPIA_CLK
#define GPIO_226_PWM1B         GPIO_226_PWM1_B
#define GPIO_226_QEP1S         GPIO_226_QEP1_STROBE
#define GPIO_226_UARTRXDC      GPIO_226_UARTC_RX

#define GPIO_227_SCLB          GPIO_227_I2CB_SCL
#define GPIO_227_PWM3A         GPIO_227_PWM3_A
#define GPIO_227_PWM2B         GPIO_227_PWM2_B

#define GPIO_228_CANTXA        GPIO_228_CANA_TX
#define GPIO_228_SPISOMIA      GPIO_228_SPIA_SOMI
#define GPIO_228_PWM2B         GPIO_228_PWM2_B
#define GPIO_228_QEP1B         GPIO_228_QEP1_B

#define GPIO_230_SDAB          GPIO_230_I2CB_SDA
#define GPIO_230_PWM3B         GPIO_230_PWM3_B
#define GPIO_230_CANRXA        GPIO_230_CANA_RX
#define GPIO_230_PWM2A         GPIO_230_PWM2_A
#define GPIO_230_SDAA          GPIO_230_I2CA_SDA
#define GPIO_230_PMBA_SCL      GPIO_230_PMBUSA_SCL

#define GPIO_242_SPISTEA       GPIO_242_SPIA_STE
#define GPIO_242_PWM4A         GPIO_242_PWM4_A
#define GPIO_242_CANRXA        GPIO_242_CANA_RX
#define GPIO_242_QEP1I         GPIO_242_QEP1_INDEX

#endif // __PIN_MAP_LEGACY_H__
