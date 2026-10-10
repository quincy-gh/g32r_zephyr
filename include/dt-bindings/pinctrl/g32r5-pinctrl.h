/**
 * @file g32r5-pinctrl.h
 * @author Quincy.W <wangqyfm@foxmail.com>
 * @brief 
 * @version 0.1
 * @date 2025-07-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef DT_BINDINGS_PINCTRL_GEEHY_G32R5_H_
#define DT_BINDINGS_PINCTRL_GEEHY_G32R5_H_

#define G32R5_PIN_POS 0
#define G32R5_PIN_MSK 0xffU

#define G32R5_PINMUX_ALT_FUNC_POS 8
#define G32R5_PINMUX_ALT_FUNC_MSK 0xfU

#define G32R5_PUPD_POS 0
#define G32R5_PUPD_MSK 0x3U

#define G32R5_OTYPE_POS 2
#define G32R5_OTYPE_MSK 0x1U

#define G32R5_OSPEED_POS 3
#define G32R5_OSPEED_MSK 0x7U

/**
 * @name G32R5 PUPD
 * @{
 */

/** No pull-up/down */
#define G32R5_PUPD_NONE 0U
/** Pull-up */
#define G32R5_PUPD_PULLUP 1U

/** No option for pull-down */

/** @} */

/**
 * @name G32R5 OTYPE
 * @{
 */

/** Push-pull */
#define G32R5_OTYPE_PP 0U
/** Open-drain */
#define G32R5_OTYPE_OD 1U

/** @} */

/**
 * @name G32R5 GPIO Strength
 * @{
 */

/** Speed: 30MHz max */
#define G32R5_OSPEED_30MHZ 0U
/** Speed: 50MHz max */
#define G32R5_OSPEED_50MHZ 1U
/** Speed: 40MHz max */
#define G32R5_OSPEED_40MHZ 2U
/** Speed: 60MHz max */
#define G32R5_OSPEED_60MHZ 3U
/** Speed: 25MHz max */
#define G32R5_OSPEED_25MHZ 4U

/** @} */

/**
 * Obtain PUPD field from pinctrl_soc_pin_t configuration.
 *
 * @param pincfg pinctrl_soc_pin_t bit field value.
 */
#define G32R5_PUPD_GET(pincfg) \
	(((pincfg) >> G32R5_PUPD_POS) & G32R5_PUPD_MSK)

/**
 * Obtain OTYPE field from pinctrl_soc_pin_t configuration.
 *
 * @param pincfg pinctrl_soc_pin_t bit field value.
 */
#define G32R5_OTYPE_GET(pincfg) \
	(((pincfg) >> G32R5_OTYPE_POS) & G32R5_OTYPE_MSK)

/**
 * Obtain OSPEED field from pinctrl_soc_pin_t configuration.
 *
 * @param pincfg pinctrl_soc_pin_t bit field value.
 */
#define G32R5_OSPEED_GET(pincfg) \
	(((pincfg) >> G32R5_OSPEED_POS) & G32R5_OSPEED_MSK)

/**
 * Obtain pin number field from pinctrl_soc_pin_t configuration.
 *
 * @param pincfg pinctrl_soc_pin_t bit field value.
 */
#define G32R5_PIN_NUMBER_GET(pincfg) \
	(((pincfg) >> G32R5_PIN_POS) & G32R5_PIN_MSK)

/**
 * Obtain pin mux field from pinctrl_soc_pin_t configuration.
 *
 * @param pincfg pinctrl_soc_pin_t bit field value.
 */
#define G32R5_PINMUX_GET(pincfg) \
	(((pincfg) >> G32R5_PINMUX_ALT_FUNC_POS) & G32R5_PINMUX_ALT_FUNC_MSK)

/**
 * @brief Geehy G32R5 pinmux bit field.
 *
 * Fields:
 *
 * -  0..7: pin number
 * - 8..11: alternate function
 *
 * @param pin Pin (0..255). GPIO224-245 are port H.
 * @param pin_mux Peripheral function (0..15)
 */
#define G32R5_PINMUX(pin, pin_mux) (                           \
    (((pin) & G32R5_PIN_MSK) << G32R5_PIN_POS) | \
    (((pin_mux) & G32R5_PINMUX_ALT_FUNC_MSK) << G32R5_PINMUX_ALT_FUNC_POS))

#endif
