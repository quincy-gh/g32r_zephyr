/**
 * @file pinctrl_g32r5.c
 * @author Quincy.W <wangqyfm@foxmail.com>
 * @brief 
 * @version 0.2
 * @date 2026-10-09
 * 
 * @copyright Copyright (c) 2025-2026
 * 
 */
#include <errno.h>

#include <zephyr/drivers/pinctrl.h>

#include <soc.h>
#include <inc/hw_memmap.h>
#include "gpio_def_g32r5.h"

#if defined(CONFIG_SOC_SERIES_G32R502)
#include <inc/hw_as.h>
#endif

/* GMUX sits 0x34 bytes after MUX on ports A, B and H. */
#define G32R5_GPIO_MUX_TO_GMUX \
	((G32R5_GPIO_GPAGMUX1 - G32R5_GPIO_GPAMUX1) >> 2)

#if defined(CONFIG_SOC_SERIES_G32R502)
/*
 * GPIO_setPinConfig() does not clear AMSEL when the bit is set.
 * AGPIO pins below still have to leave analog mode for a digital function.
 */
#define G32R5_GPIO_A_AMSEL_SKIP 0x10103000U
#define G32R5_GPIO_H_AMSEL_SKIP 0x003E7F3FU
#endif

/* Peripheral mux. GPIO mode (function 0) is not a mux function. */
static bool pin_has_mux(uint32_t pin_num)
{
#if defined(CONFIG_SOC_SERIES_G32R501)
	/* Port H has pad and AMSEL registers. MUX/GMUX do not latch. */
	return pin_num < 224U;
#elif defined(CONFIG_SOC_SERIES_G32R502)
	switch (pin_num) {
	case 225U:
	case 231U:
	case 232U:
	case 233U:
	case 237U:
	case 238U:
	case 239U:
	case 241U:
	case 244U:
	case 245U:
		return false;
	default:
		return true;
	}
#else
	return false;
#endif
}

static bool pin_is_routable(uint32_t pin_num)
{
	if (pin_num <= 63U) {
		return true;
	}

#if defined(CONFIG_SOC_SERIES_G32R502)
	return (pin_num >= 224U) && (pin_num <= 245U);
#elif defined(CONFIG_SOC_SERIES_G32R501)
	return (pin_num >= 224U) && (pin_num <= 254U);
#else
#error "pinctrl_g32r5.c requires CONFIG_SOC_SERIES_G32R501 or CONFIG_SOC_SERIES_G32R502"
#endif
}

#if defined(CONFIG_SOC_SERIES_G32R502)
static bool agpio_pin(uint32_t pin_num)
{
	switch (pin_num) {
	case 12U:
	case 13U:
	case 20U:
	case 21U:
	case 28U:
	case 224U:
	case 226U:
	case 227U:
	case 228U:
	case 230U:
	case 242U:
		return true;
	default:
		return false;
	}
}
#endif

/* Digital function: clear AMSEL, and on 502 also AGPIOCTRL for AGPIO pins. */
static void pin_leave_analog(uint32_t pin_num)
{
	volatile uint32_t *amsel = NULL;
	uint32_t bit = 0U;

#if defined(CONFIG_SOC_SERIES_G32R502)
	if (pin_num <= 31U) {
		bit = 1U << pin_num;
		if (((bit & G32R5_GPIO_A_AMSEL_SKIP) == 0U) || agpio_pin(pin_num)) {
			amsel = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPAAMSEL);
		}
	} else if (pin_num <= 49U) {
		bit = 1U << (pin_num - 32U);
		amsel = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPBAMSEL);
	} else if ((pin_num >= 224U) && (pin_num <= 245U)) {
		bit = 1U << (pin_num - 224U);
		if (((bit & G32R5_GPIO_H_AMSEL_SKIP) == 0U) || agpio_pin(pin_num)) {
			amsel = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPHAMSEL);
		}
	}
#elif defined(CONFIG_SOC_SERIES_G32R501)
	if ((pin_num == 22U) || (pin_num == 23U)) {
		bit = 1U << pin_num;
		amsel = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPAAMSEL);
	} else if ((pin_num >= 224U) && (pin_num <= 254U)) {
		bit = 1U << (pin_num - 224U);
		amsel = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPHAMSEL);
	}
#endif

	if (amsel != NULL) {
		*amsel &= ~bit;
	}

#if defined(CONFIG_SOC_SERIES_G32R502)
	if (agpio_pin(pin_num)) {
		volatile uint32_t *agpio =
			(uint32_t *)(ANALOGSUBSYS_BASE + AS_O_AGPIOCTRLA +
				     ((pin_num / 32U) * 4U));

		*agpio &= ~(1U << (pin_num % 32U));
	}
#endif
}

static volatile uint32_t *pin_mux_reg(uint32_t pin_num, uint32_t *bit_offset)
{
	if (!pin_is_routable(pin_num)) {
		return NULL;
	}

	if (pin_num <= 63U) {
		*bit_offset = (pin_num & 0x0FU) * 2U;

		switch (pin_num >> 4) {
		case 0: /* GPIO15..0 */
			return (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPAMUX1);
		case 1: /* GPIO31..16 */
			return (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPAMUX2);
		case 2: /* GPIO47..32 */
			return (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPBMUX1);
		case 3: /* GPIO59..48 */
			return (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPBMUX2);
		default:
			return NULL;
		}
	}

	if ((pin_num >= 224U) && (pin_num <= 255U)) {
		uint32_t local = pin_num - 224U;

		*bit_offset = (local & 0x0FU) * 2U;
		if (local < 16U) {
			return (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPHMUX1);
		}

		return (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPHMUX2);
	}

	return NULL;
}

static void pin_mux(uint32_t pin_num, uint32_t mux)
{
	uint32_t bit_offset = 0U;
	volatile uint32_t *reg = pin_mux_reg(pin_num, &bit_offset);

	volatile uint32_t *gmux;
	uint32_t field;

	if (reg == NULL) {
		return;
	}

	/*
	 * Clear MUX first, then write GMUX, then MUX.
	 * Otherwise the old GMUX plus the new MUX is a third function.
	 */
	field = 0x3U << bit_offset;
	*reg &= ~field;
	gmux = reg + G32R5_GPIO_MUX_TO_GMUX;
	*gmux = (*gmux & ~field) | (((mux >> 2) & 0x3U) << bit_offset);
	*reg |= (mux & 0x3U) << bit_offset;

	pin_leave_analog(pin_num);
}

static void pin_cfg_porth(uint32_t bit, uint16_t cfg)
{
	volatile uint32_t *reg;

	reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPHPUD);
	if ((cfg >> G32R5_PUPD_POS) & G32R5_PUPD_PULLUP) {
		*reg &= ~(1U << bit);
	} else {
		*reg |= (1U << bit);
	}

	reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPHODR);
	if ((cfg >> G32R5_OTYPE_POS) & G32R5_OTYPE_OD) {
		*reg |= (1U << bit);
	} else {
		*reg &= ~(1U << bit);
	}

	uint16_t sl = (cfg >> G32R5_OSPEED_POS) & G32R5_OSPEED_MSK;

	reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPHFEN);
	if (sl == G32R5_OSPEED_25MHZ) {
		*reg |= (1U << bit);
		return;
	}

	*reg &= ~(1U << bit);
	sl &= 0x3U;
	if (bit > 15U) {
		reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPHDSEL2);
		bit -= 16U;
	} else {
		reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPHDSEL1);
	}

	bit *= 2U;
	*reg = (*reg & ~(3UL << bit)) | (sl << bit);
}

static void pin_cfg(uint32_t pin_num, uint16_t cfg)
{
	volatile uint32_t * reg;
	uint32_t reg_offset = 0;

	if (!pin_is_routable(pin_num)) {
		return;
	}

	if (pin_num >= 224U) {
		if (pin_num <= 255U) {
			pin_cfg_porth(pin_num - 224U, cfg);
		}
		return;
	}

	if (pin_num > 31)
	{
		pin_num -= 32;
		reg_offset += 0x80U;
	}

	if ((cfg >> G32R5_PUPD_POS) & G32R5_PUPD_PULLUP)
	{
		// Pull-up
		reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPAPUD + reg_offset);
		*reg &= (~(1U << pin_num));
	}
	else
	{
		// No pull-up
		reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPAPUD + reg_offset);
		*reg |= (1U << pin_num);
	}

	if ((cfg >> G32R5_OTYPE_POS) & G32R5_OTYPE_OD)
	{
		// Open-drain
		reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPAODR + reg_offset);
		*reg |= (1U << pin_num);
	}
	else
	{
		// Push-pull
		reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPAODR + reg_offset);
		*reg &= (~(1U << pin_num));
	}
	
	uint16_t sl = (cfg >> G32R5_OSPEED_POS) & G32R5_OSPEED_MSK;
	if (sl == G32R5_OSPEED_25MHZ)
	{
		// GPIOxFEN
		reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPAFEN + reg_offset);
		*reg |= (1U << pin_num);
	}
	else
	{
		// GPIOxDSEL
		reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPAFEN + reg_offset);
		*reg &= (~(1U << pin_num));

		sl &= 0x3U;
		//
		if (pin_num > 15)
		{
			reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPADSEL2 + reg_offset);
			pin_num -= 16;
		}
		else
		{
			reg = (uint32_t *)(GPIOCTRL_BASE + G32R5_GPIO_GPADSEL1 + reg_offset);
		}

		pin_num *= 2;
		*reg = (*reg & ~(3UL << pin_num)) | (sl << pin_num);
	}
}

static int pinctrl_configure_pin(const pinctrl_soc_pin_t *pin)
{
	uint32_t pin_num = G32R5_PIN_NUMBER_GET(pin->pinmux);
	uint32_t mux = G32R5_PINMUX_GET(pin->pinmux);

	if (!pin_is_routable(pin_num)) {
		return -EINVAL;
	}

	/* These pins have no peripheral function. Function 0 is GPIO / pad only. */
	if (!pin_has_mux(pin_num) && (mux != 0U)) {
		return -EINVAL;
	}

	__wrprt_disable();

	if (pin_has_mux(pin_num)) {
		pin_mux(pin_num, mux);
	} else {
		pin_leave_analog(pin_num);
	}
	pin_cfg(pin_num, pin->cfg);

	__wrprt_enable();

	return 0;
}

int pinctrl_configure_pins(const pinctrl_soc_pin_t *pins, uint8_t pin_cnt, uintptr_t reg)
{
	ARG_UNUSED(reg);

	for (uint8_t i = 0U; i < pin_cnt; i++)
	{
		int ret = pinctrl_configure_pin(pins++);

		if (ret != 0) {
			return ret;
		}
	}

	return 0;
}
