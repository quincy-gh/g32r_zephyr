/**
 * @file pinctrl_soc.h
 * @author Quincy.W <wangqyfm@foxmail.com>
 * @brief 
 * @version 0.1
 * @date 2025-07-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_PINCTRL_PINCTRL_SOC_G32R5_COMMON_H_
#define ZEPHYR_INCLUDE_DRIVERS_PINCTRL_PINCTRL_SOC_G32R5_COMMON_H_

#include <zephyr/devicetree.h>
#include <zephyr/types.h>
#include <dt-bindings/pinctrl/g32r5-pinctrl.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** @cond INTERNAL_HIDDEN */

/** @brief Type for G32R5 pin.
 *
 */
typedef struct
{
	uint16_t pinmux; /**< Pin configuration value. */
	uint16_t cfg;	 /**< Output speed configuration value. */
} pinctrl_soc_pin_t;

/**
 * @brief Utility macro to initialize each pin.
 *
 * @param node_id Node identifier.
 * @param prop Property name.
 * @param idx Property entry index.
 */
#define Z_PINCTRL_STATE_PIN_INIT(node_id, prop, idx) { \
		.pinmux = DT_PROP(DT_PROP_BY_IDX(node_id, prop, idx), pinmux), \
	 	.cfg = ( \
				(DT_PROP(DT_PROP_BY_IDX(node_id, prop, idx), bias_pull_up) << G32R5_PUPD_POS) | \
				(DT_PROP(DT_PROP_BY_IDX(node_id, prop, idx), drive_open_drain) << G32R5_OTYPE_POS) \
		),\
	},

/**
 * @brief Utility macro to initialize state pins contained in a given property.
 *
 * @param node_id Node identifier.
 * @param prop Property name describing state pins.
 */
#define Z_PINCTRL_STATE_PINS_INIT(node_id, prop) \
	{DT_FOREACH_PROP_ELEM(node_id, prop, Z_PINCTRL_STATE_PIN_INIT)}

/** @endcond */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_PINCTRL_PINCTRL_SOC_G32R5_COMMON_H_ */
