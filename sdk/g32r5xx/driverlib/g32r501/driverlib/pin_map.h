//###########################################################################
//
// FILE:    pin_map.h
//
// TITLE:   Definitions of pin mux info for gpio.c.
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
// 1. macro definitions
//
//###########################################################################

#ifndef __PIN_MAP_H__
#define __PIN_MAP_H__

//*****************************************************************************
// 0x00000003 = MUX register value
// 0x0000000C = GMUX register value
// 0x0000FF00 = Shift amount within mux registers
// 0xFFFF0000 = Offset of MUX register
//*****************************************************************************


#define GPIO_0_GPIO0                0x00060000U
#define GPIO_0_PWM1_A               0x00060001U
#define GPIO_0_SPIA_STE             0x00060003U
#define GPIO_0_I2CA_SDA             0x00060006U
#define GPIO_0_QSPI_IO1             0x0006000BU

#define GPIO_1_GPIO1                0x00060200U
#define GPIO_1_PWM1_B               0x00060201U
#define GPIO_1_SPIA_SOMI            0x00060203U
#define GPIO_1_I2CA_SCL             0x00060206U

#define GPIO_2_GPIO2                0x00060400U
#define GPIO_2_PWM2_A               0x00060401U
#define GPIO_2_CANA_TX              0x00060402U
#define GPIO_2_SPIA_SIMO            0x00060403U
#define GPIO_2_OUTPUTXBAR1          0x00060405U
#define GPIO_2_PMBUSA_SDA           0x00060406U
#define GPIO_2_UARTA_TX             0x00060409U
#define GPIO_2_QSPI_IO3             0x0006040BU

#define GPIO_3_GPIO3                0x00060600U
#define GPIO_3_PWM2_B               0x00060601U
#define GPIO_3_OUTPUTXBAR2          0x00060602U
#define GPIO_3_CANA_RX              0x00060603U
#define GPIO_3_PMBUSA_SCL           0x00060606U
#define GPIO_3_SPIA_CLK             0x00060607U
#define GPIO_3_UARTA_RX             0x00060609U
#define GPIO_3_QSPI_IO2             0x0006060BU

#define GPIO_4_GPIO4                0x00060800U
#define GPIO_4_PWM3_A               0x00060801U
#define GPIO_4_QEP2_STROBE          0x00060802U
#define GPIO_4_SPIB_CLK             0x00060803U
#define GPIO_4_OUTPUTXBAR3          0x00060805U
#define GPIO_4_CANA_TX              0x00060806U
#define GPIO_4_QSPI_SCLK            0x0006080BU

#define GPIO_5_GPIO5                0x00060A00U
#define GPIO_5_PWM3_B               0x00060A01U
#define GPIO_5_OUTPUTXBAR3          0x00060A03U
#define GPIO_5_CANA_RX              0x00060A06U
#define GPIO_5_SPIA_STE             0x00060A07U
#define GPIO_5_QSPI_IO1             0x00060A0BU

#define GPIO_6_GPIO6                0x00060C00U
#define GPIO_6_PWM4_A               0x00060C01U
#define GPIO_6_OUTPUTXBAR4          0x00060C02U
#define GPIO_6_SYNCOUT              0x00060C03U
#define GPIO_6_QEP1_A               0x00060C05U
#define GPIO_6_CANB_TX              0x00060C06U
#define GPIO_6_SPIB_SOMI            0x00060C07U
#define GPIO_6_QSPI_IO0             0x00060C0BU

#define GPIO_7_GPIO7                0x00060E00U
#define GPIO_7_PWM4_B               0x00060E01U
#define GPIO_7_OUTPUTXBAR5          0x00060E03U
#define GPIO_7_QEP1_B               0x00060E05U
#define GPIO_7_CANB_RX              0x00060E06U
#define GPIO_7_SPIB_SIMO            0x00060E07U
#define GPIO_7_QSPI_SS_N            0x00060E0BU

#define GPIO_8_GPIO8                0x00061000U
#define GPIO_8_PWM5_A               0x00061001U
#define GPIO_8_CANB_TX              0x00061002U
#define GPIO_8_ADCSOCAO             0x00061003U
#define GPIO_8_QEP1_STROBE          0x00061005U
#define GPIO_8_UARTA_TX             0x00061006U
#define GPIO_8_SPIA_SIMO            0x00061007U
#define GPIO_8_I2CA_SCL             0x00061009U
#define GPIO_8_QSPI_IO3             0x0006100BU

#define GPIO_9_GPIO9                0x00061200U
#define GPIO_9_PWM5_B               0x00061201U
#define GPIO_9_UARTB_TX             0x00061202U
#define GPIO_9_OUTPUTXBAR6          0x00061203U
#define GPIO_9_QEP1_INDEX           0x00061205U
#define GPIO_9_UARTA_RX             0x00061206U
#define GPIO_9_SPIA_CLK             0x00061207U
#define GPIO_9_QSPI_IO2             0x0006120BU

#define GPIO_10_GPIO10              0x00061400U
#define GPIO_10_PWM6_A              0x00061401U
#define GPIO_10_CANB_RX             0x00061402U
#define GPIO_10_ADCSOCBO            0x00061403U
#define GPIO_10_QEP1_A              0x00061405U
#define GPIO_10_UARTB_TX            0x00061406U
#define GPIO_10_SPIA_SOMI           0x00061407U
#define GPIO_10_I2CA_SDA            0x00061409U
#define GPIO_10_QSPI_SCLK           0x0006140BU

#define GPIO_11_GPIO11              0x00061600U
#define GPIO_11_PWM6_B              0x00061601U
#define GPIO_11_UARTB_RX            0x00061602U
#define GPIO_11_OUTPUTXBAR7         0x00061603U
#define GPIO_11_QEP1_B              0x00061605U
#define GPIO_11_SPIA_STE            0x00061607U
#define GPIO_11_QEP2_A              0x0006160AU
#define GPIO_11_QSPI_IO1            0x0006160BU
#define GPIO_11_SPIA_SIMO           0x0006160DU

#define GPIO_12_GPIO12              0x00061800U
#define GPIO_12_PWM7_A              0x00061801U
#define GPIO_12_CANB_TX             0x00061802U
#define GPIO_12_SPIA_CLK            0x00061803U
#define GPIO_12_QEP1_STROBE         0x00061805U
#define GPIO_12_UARTB_TX            0x00061806U
#define GPIO_12_PMBUSA_CTL          0x00061807U
#define GPIO_12_CANA_RX             0x0006180AU
#define GPIO_12_QSPI_IO0            0x0006180BU
#define GPIO_12_TRACED2             0x0006180FU

#define GPIO_13_GPIO13              0x00061A00U
#define GPIO_13_PWM7_B              0x00061A01U
#define GPIO_13_CANB_RX             0x00061A02U
#define GPIO_13_SPIA_SOMI           0x00061A03U
#define GPIO_13_QEP1_INDEX          0x00061A05U
#define GPIO_13_UARTB_RX            0x00061A06U
#define GPIO_13_PMBUSA_ALERT        0x00061A07U
#define GPIO_13_CANA_TX             0x00061A0AU
#define GPIO_13_QSPI_SS_N           0x00061A0BU
#define GPIO_13_TRACED3             0x00061A0FU

#define GPIO_14_GPIO14              0x00061C00U
#define GPIO_14_PWM8_A              0x00061C01U
#define GPIO_14_UARTB_TX            0x00061C02U
#define GPIO_14_PWM3_A              0x00061C05U
#define GPIO_14_OUTPUTXBAR3         0x00061C06U
#define GPIO_14_PMBUSA_SDA          0x00061C07U
#define GPIO_14_SPIB_CLK            0x00061C09U
#define GPIO_14_QEP2_A              0x00061C0AU

#define GPIO_15_GPIO15              0x00061E00U
#define GPIO_15_PWM8_B              0x00061E01U
#define GPIO_15_UARTB_RX            0x00061E02U
#define GPIO_15_PWM3_B              0x00061E05U
#define GPIO_15_OUTPUTXBAR4         0x00061E06U
#define GPIO_15_PMBUSA_SCL          0x00061E07U
#define GPIO_15_SPIB_STE            0x00061E09U
#define GPIO_15_QEP2_B              0x00061E0AU

#define GPIO_16_GPIO16              0x00080000U
#define GPIO_16_SPIA_SIMO           0x00080001U
#define GPIO_16_CANB_TX             0x00080002U
#define GPIO_16_OUTPUTXBAR7         0x00080003U
#define GPIO_16_PWM5_A              0x00080005U
#define GPIO_16_UARTA_TX            0x00080006U
#define GPIO_16_SD1_D1              0x00080007U
#define GPIO_16_QEP1_STROBE         0x00080009U
#define GPIO_16_PMBUSA_SCL          0x0008000AU
#define GPIO_16_XCLKOUT             0x0008000BU
#define GPIO_16_SPIB_SOMI           0x0008000DU
#define GPIO_16_QEP2_B              0x0008000EU
#define GPIO_16_TRACED0             0x0008000FU

#define GPIO_17_GPIO17              0x00080200U
#define GPIO_17_SPIA_SOMI           0x00080201U
#define GPIO_17_CANB_RX             0x00080202U
#define GPIO_17_OUTPUTXBAR8         0x00080203U
#define GPIO_17_PWM5_B              0x00080205U
#define GPIO_17_UARTA_RX            0x00080206U
#define GPIO_17_SD1_C1              0x00080207U
#define GPIO_17_QEP1_INDEX          0x00080209U
#define GPIO_17_PMBUSA_SDA          0x0008020AU
#define GPIO_17_CANA_TX             0x0008020DU

#define GPIO_18_GPIO18_X2           0x00080400U
#define GPIO_18_SPIA_CLK            0x00080401U
#define GPIO_18_UARTB_TX            0x00080402U
#define GPIO_18_CANA_RX             0x00080403U
#define GPIO_18_PWM6_A              0x00080405U
#define GPIO_18_I2CA_SCL            0x00080406U
#define GPIO_18_SD1_D2              0x00080407U
#define GPIO_18_QEP2_A              0x00080409U
#define GPIO_18_PMBUSA_CTL          0x0008040AU
#define GPIO_18_XCLKOUT             0x0008040BU

#define GPIO_19_GPIO19              0x00080600U
#define GPIO_19_SPIA_STE            0x00080601U
#define GPIO_19_UARTB_RX            0x00080602U
#define GPIO_19_CANA_TX             0x00080603U
#define GPIO_19_PWM6_B              0x00080605U
#define GPIO_19_I2CA_SDA            0x00080606U
#define GPIO_19_SD1_C2              0x00080607U
#define GPIO_19_QEP2_B              0x00080609U
#define GPIO_19_PMBUSA_ALERT        0x0008060AU


#define GPIO_20_GPIO20              0x00080800U
#define GPIO_20_QEP1_A              0x00080801U
#define GPIO_20_CANB_TX             0x00080803U
#define GPIO_20_SPIB_SIMO           0x00080806U
#define GPIO_20_SD1_D3              0x00080807U
#define GPIO_20_SPIB_CLK            0x00080809U

#define GPIO_21_GPIO21              0x00080A00U
#define GPIO_21_QEP1_B              0x00080A01U
#define GPIO_21_CANB_RX             0x00080A03U
#define GPIO_21_SPIB_SOMI           0x00080A06U
#define GPIO_21_SD1_C3              0x00080A07U
#define GPIO_21_I2CA_SCL            0x00080A0BU

#define GPIO_22_GPIO22_VFBSW        0x00080C00U
#define GPIO_22_QEP1_STROBE         0x00080C01U
#define GPIO_22_UARTB_TX            0x00080C03U
#define GPIO_22_PWM4_A              0x00080C05U
#define GPIO_22_SPIB_CLK            0x00080C06U
#define GPIO_22_SD1_D4              0x00080C07U
#define GPIO_22_LINA_TX             0x00080C09U

#define GPIO_23_GPIO23_VSW          0x00080E00U
#define GPIO_23_QEP1_INDEX          0x00080E01U
#define GPIO_23_UARTB_RX            0x00080E03U
#define GPIO_23_GPIO23              0x00080E04U
#define GPIO_23_PWM4_B              0x00080E05U
#define GPIO_23_SPIB_STE            0x00080E06U
#define GPIO_23_SD1_C4              0x00080E07U
#define GPIO_23_LINA_RX             0x00080E09U
#define GPIO_23_I2CA_SDA            0x00080E0BU
#define GPIO_23_SPIB_SIMO           0x00080E0DU

#define GPIO_24_GPIO24              0x00081000U
#define GPIO_24_OUTPUTXBAR1         0x00081001U
#define GPIO_24_QEP2_A              0x00081002U
#define GPIO_24_PWM8_A              0x00081005U
#define GPIO_24_SPIB_SIMO           0x00081006U
#define GPIO_24_SD1_D1              0x00081007U
#define GPIO_24_PMBUSA_SCL          0x0008100AU
#define GPIO_24_UARTA_TX            0x0008100BU
#define GPIO_24_ERRORSTS            0x0008100DU
#define GPIO_24_TRACECLK            0x0008100FU

#define GPIO_25_GPIO25              0x00081200U
#define GPIO_25_OUTPUTXBAR2         0x00081201U
#define GPIO_25_QEP2_B              0x00081202U
#define GPIO_25_QEP1_A              0x00081205U
#define GPIO_25_SPIB_SOMI           0x00081206U
#define GPIO_25_SD1_C1              0x00081207U
#define GPIO_25_PMBUSA_SDA          0x0008120AU
#define GPIO_25_UARTA_RX            0x0008120BU
#define GPIO_25_QSPI_IO3            0x0008120DU

#define GPIO_26_GPIO26              0x00081400U
#define GPIO_26_OUTPUTXBAR3         0x00081401U
#define GPIO_26_QEP2_INDEX          0x00081402U
#define GPIO_26_SPIB_CLK            0x00081406U
#define GPIO_26_SD1_D2              0x00081407U
#define GPIO_26_PMBUSA_CTL          0x0008140AU
#define GPIO_26_I2CA_SDA            0x0008140BU
#define GPIO_26_QSPI_IO2            0x0008140DU

#define GPIO_27_GPIO27              0x00081600U
#define GPIO_27_OUTPUTXBAR4         0x00081601U
#define GPIO_27_QEP2_STROBE         0x00081602U
#define GPIO_27_SPIB_STE            0x00081606U
#define GPIO_27_SD1_C2              0x00081607U
#define GPIO_27_PMBUSA_ALERT        0x0008160AU
#define GPIO_27_I2CA_SCL            0x0008160BU
#define GPIO_27_QSPI_SCLK           0x0008160DU

#define GPIO_28_GPIO28              0x00081800U
#define GPIO_28_UARTA_RX            0x00081801U
#define GPIO_28_PWM7_A              0x00081803U
#define GPIO_28_OUTPUTXBAR5         0x00081805U
#define GPIO_28_QEP1_A              0x00081806U
#define GPIO_28_SD1_D3              0x00081807U
#define GPIO_28_QEP2_STROBE         0x00081809U
#define GPIO_28_LINA_TX             0x0008180AU
#define GPIO_28_SPIB_CLK            0x0008180BU
#define GPIO_28_ERRORSTS            0x0008180DU
#define GPIO_28_TRACECLK            0x0008180FU

#define GPIO_29_GPIO29              0x00081A00U
#define GPIO_29_UARTA_TX            0x00081A01U
#define GPIO_29_PWM7_B              0x00081A03U
#define GPIO_29_OUTPUTXBAR6         0x00081A05U
#define GPIO_29_QEP1_B              0x00081A06U
#define GPIO_29_SD1_C3              0x00081A07U
#define GPIO_29_QEP2_INDEX          0x00081A09U
#define GPIO_29_LINA_RX             0x00081A0AU
#define GPIO_29_SPIB_STE            0x00081A0BU
#define GPIO_29_ERRORSTS            0x00081A0DU
#define GPIO_29_TRACED0             0x00081A0FU

#define GPIO_30_GPIO30              0x00081C00U
#define GPIO_30_CANA_RX             0x00081C01U
#define GPIO_30_PWM1_A              0x00081C02U
#define GPIO_30_SPIB_SIMO           0x00081C03U
#define GPIO_30_OUTPUTXBAR7         0x00081C05U
#define GPIO_30_QEP1_STROBE         0x00081C06U
#define GPIO_30_SD1_D4              0x00081C07U
#define GPIO_30_QSPI_IO3            0x00081C0BU
#define GPIO_30_TRACED1             0x00081C0FU

#define GPIO_31_GPIO31              0x00081E00U
#define GPIO_31_CANA_TX             0x00081E01U
#define GPIO_31_PWM1_B              0x00081E02U
#define GPIO_31_SPIB_SOMI           0x00081E03U
#define GPIO_31_OUTPUTXBAR8         0x00081E05U
#define GPIO_31_QEP1_INDEX          0x00081E06U
#define GPIO_31_SD1_C4              0x00081E07U
#define GPIO_31_QSPI_IO1            0x00081E0BU
#define GPIO_31_TRACED2             0x00081E0FU

#define GPIO_32_GPIO32              0x00460000U
#define GPIO_32_I2CA_SDA            0x00460001U
#define GPIO_32_SPIB_CLK            0x00460003U
#define GPIO_32_PWM8_B              0x00460005U
#define GPIO_32_LINA_TX             0x00460006U
#define GPIO_32_SD1_D3              0x00460007U
#define GPIO_32_CANA_TX             0x0046000AU
#define GPIO_32_QSPI_IO0            0x0046000BU
#define GPIO_32_ADCSOCBO            0x0046000DU

#define GPIO_33_GPIO33              0x00460200U
#define GPIO_33_I2CA_SCL            0x00460201U
#define GPIO_33_QEP2_B              0x00460202U
#define GPIO_33_SPIB_STE            0x00460203U
#define GPIO_33_OUTPUTXBAR4         0x00460205U
#define GPIO_33_LINA_RX             0x00460206U
#define GPIO_33_SD1_C3              0x00460207U
#define GPIO_33_CANA_RX             0x0046020AU
#define GPIO_33_QSPI_SS_N           0x0046020BU
#define GPIO_33_ADCSOCAO            0x0046020DU
#define GPIO_33_TRACED1             0x0046020FU

#define GPIO_34_GPIO34              0x00460400U
#define GPIO_34_OUTPUTXBAR1         0x00460401U
#define GPIO_34_PMBUSA_SDA          0x00460406U
#define GPIO_34_TRACED3             0x0046040FU

#define GPIO_35_GPIO35              0x00460600U
#define GPIO_35_UARTA_RX            0x00460601U
#define GPIO_35_I2CA_SDA            0x00460603U
#define GPIO_35_CANA_RX             0x00460605U
#define GPIO_35_PMBUSA_SCL          0x00460606U
#define GPIO_35_LINA_RX             0x00460607U
#define GPIO_35_QEP1_A              0x00460609U
#define GPIO_35_PMBUSA_CTL          0x0046060AU
#define GPIO_35_TDI                 0x0046060FU

#define GPIO_37_GPIO37              0x00460A00U
#define GPIO_37_OUTPUTXBAR2         0x00460A01U
#define GPIO_37_I2CA_SCL            0x00460A03U
#define GPIO_37_UARTA_TX            0x00460A05U
#define GPIO_37_CANA_TX             0x00460A06U
#define GPIO_37_LINA_TX             0x00460A07U
#define GPIO_37_QEP1_B              0x00460A09U
#define GPIO_37_PMBUSA_ALERT        0x00460A0AU
#define GPIO_37_TDO                 0x00460A0FU

#define GPIO_39_GPIO39              0x00460E00U
#define GPIO_39_CANB_RX             0x00460E06U
#define GPIO_39_QSPI_IO3            0x00460E0BU

#define GPIO_40_GPIO40              0x00461000U
#define GPIO_40_PMBUSA_SDA          0x00461006U
#define GPIO_40_UARTB_TX            0x00461009U
#define GPIO_40_QEP1_A              0x0046100AU
#define GPIO_40_QSPI_IO2            0x0046100BU

#define GPIO_41_GPIO41              0x00461200U
#define GPIO_41_PWM2_A              0x00461201U
#define GPIO_41_SPIB_STE            0x00461203U
#define GPIO_41_PMBUSA_SCL          0x00461206U
#define GPIO_41_UARTB_RX            0x00461209U
#define GPIO_41_QEP1_B              0x0046120AU
#define GPIO_41_QSPI_SCLK           0x0046120BU
#define GPIO_41_SPIB_SOMI           0x0046120DU

#define GPIO_42_GPIO42              0x00461400U
#define GPIO_42_LINA_RX             0x00461402U
#define GPIO_42_OUTPUTXBAR5         0x00461403U
#define GPIO_42_PMBUSA_CTL          0x00461405U
#define GPIO_42_I2CA_SDA            0x00461406U
#define GPIO_42_UARTB_RX            0x00461409U
#define GPIO_42_QEP1_STROBE         0x0046140AU

#define GPIO_43_GPIO43              0x00461600U
#define GPIO_43_OUTPUTXBAR6         0x00461603U
#define GPIO_43_PMBUSA_ALERT        0x00461605U
#define GPIO_43_I2CA_SCL            0x00461606U
#define GPIO_43_UARTB_TX            0x00461609U
#define GPIO_43_QEP1_INDEX          0x0046160AU

#define GPIO_44_GPIO44              0x00461800U
#define GPIO_44_QEP1_A              0x00461802U
#define GPIO_44_OUTPUTXBAR7         0x00461803U
#define GPIO_44_QSPI_IO2            0x0046180BU

#define GPIO_45_GPIO45              0x00461A00U
#define GPIO_45_OUTPUTXBAR8         0x00461A03U
#define GPIO_45_QSPI_IO0            0x00461A0BU

#define GPIO_46_GPIO46              0x00461C00U
#define GPIO_46_LINA_TX             0x00461C03U
#define GPIO_46_QSPI_SS_N           0x00461C0BU

#define GPIO_47_GPIO47              0x00461E00U
#define GPIO_47_PWM2_B              0x00461E01U
#define GPIO_47_QEP1_A              0x00461E02U
#define GPIO_47_LINA_RX             0x00461E03U
#define GPIO_47_SPIB_SIMO           0x00461E06U
#define GPIO_47_PMBUSA_SDA          0x00461E07U

#define GPIO_48_GPIO48              0x00480000U
#define GPIO_48_OUTPUTXBAR3         0x00480001U
#define GPIO_48_CANB_TX             0x00480003U
#define GPIO_48_UARTA_TX            0x00480006U
#define GPIO_48_SD1_D1              0x00480007U

#define GPIO_49_GPIO49              0x00480200U
#define GPIO_49_OUTPUTXBAR4         0x00480201U
#define GPIO_49_QEP1_INDEX          0x00480202U
#define GPIO_49_CANB_RX             0x00480203U
#define GPIO_49_UARTA_RX            0x00480206U
#define GPIO_49_SD1_C1              0x00480207U
#define GPIO_49_QEP2_INDEX          0x00480209U
#define GPIO_49_SYNCOUT             0x0048020BU

#define GPIO_50_GPIO50              0x00480400U
#define GPIO_50_QEP1_A              0x00480401U
#define GPIO_50_SPIB_SIMO           0x00480406U
#define GPIO_50_SD1_D2              0x00480407U

#define GPIO_51_GPIO51              0x00480600U
#define GPIO_51_QEP1_B              0x00480601U
#define GPIO_51_SPIB_SOMI           0x00480606U
#define GPIO_51_SD1_C2              0x00480607U

#define GPIO_52_GPIO52              0x00480800U
#define GPIO_52_QEP1_STROBE         0x00480801U
#define GPIO_52_SPIB_CLK            0x00480806U
#define GPIO_52_SD1_D3              0x00480807U

#define GPIO_53_GPIO53              0x00480A00U
#define GPIO_53_QEP1_INDEX          0x00480A01U
#define GPIO_53_SPIB_STE            0x00480A06U
#define GPIO_53_SD1_C3              0x00480A07U
#define GPIO_53_UARTB_RX            0x00480A09U

#define GPIO_54_GPIO54              0x00480C00U
#define GPIO_54_SPIA_SIMO           0x00480C01U
#define GPIO_54_QEP2_A              0x00480C05U
#define GPIO_54_UARTB_TX            0x00480C06U
#define GPIO_54_SD1_D4              0x00480C07U

#define GPIO_55_GPIO55              0x00480E00U
#define GPIO_55_SPIA_SOMI           0x00480E01U
#define GPIO_55_QEP2_B              0x00480E05U
#define GPIO_55_UARTB_RX            0x00480E06U
#define GPIO_55_SD1_C4              0x00480E07U

#define GPIO_56_GPIO56              0x00481000U
#define GPIO_56_SPIA_CLK            0x00481001U
#define GPIO_56_QEP2_STROBE         0x00481005U
#define GPIO_56_UARTB_TX            0x00481006U
#define GPIO_56_SD1_D3              0x00481007U
#define GPIO_56_SPIB_SIMO           0x00481009U
#define GPIO_56_QEP1_A              0x0048100BU

#define GPIO_57_GPIO57              0x00481200U
#define GPIO_57_SPIA_STE            0x00481201U
#define GPIO_57_QEP2_INDEX          0x00481205U
#define GPIO_57_UARTB_RX            0x00481206U
#define GPIO_57_SD1_C3              0x00481207U
#define GPIO_57_SPIB_SOMI           0x00481209U
#define GPIO_57_QEP1_B              0x0048120BU

#define GPIO_58_GPIO58              0x00481400U
#define GPIO_58_OUTPUTXBAR1         0x00481405U
#define GPIO_58_SPIB_CLK            0x00481406U
#define GPIO_58_SD1_D4              0x00481407U
#define GPIO_58_LINA_TX             0x00481409U
#define GPIO_58_CANB_TX             0x0048140AU
#define GPIO_58_QEP1_STROBE         0x0048140BU

#define GPIO_59_GPIO59              0x00481600U
#define GPIO_59_OUTPUTXBAR2         0x00481605U
#define GPIO_59_SPIB_STE            0x00481606U
#define GPIO_59_SD1_C4              0x00481607U
#define GPIO_59_LINA_RX             0x00481609U
#define GPIO_59_CANB_RX             0x0048160AU
#define GPIO_59_QEP1_INDEX          0x0048160BU

#endif // PIN_MAP_H
