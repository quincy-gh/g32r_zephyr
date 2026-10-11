/**
 * @file gpio_g32r5.c
 * @author Quincy.W <wangqyfm@foxmail.com>
 * @brief
 * @version 0.3
 * @date 2026-10-09
 *
 * @copyright Copyright (c) 2025-2026
 *
 */

#define DT_DRV_COMPAT geehy_g32r5_gpio

#include <errno.h>

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/gpio/gpio_utils.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/byteorder.h>
#include <gpio.h>
#include <cpu.h>

#define GPMUX1_OFFSET  0x0CUL
#define GPMUX2_OFFSET  0x10UL
#define GPDIR_OFFSET   0x14UL
#define GPPUD_OFFSET   0x18UL
#define GPINV_OFFSET   0x20UL
#define GPODR_OFFSET   0x24UL
#define GPAMSEL_OFFSET 0x28UL
#define GPGMUX1_OFFSET 0x40UL
#define GPGMUX2_OFFSET 0x44UL

#define GPDAT_OFFSET 0x0UL
#define GPSET_OFFSET 0x4UL
#define GPCLR_OFFSET 0x8UL
#define GPTOGGLE_OFFSET 0xCUL

#define G32R5_GPIOA_CTRL (GPIOCTRL_BASE + 0x000UL)
#define G32R5_GPIOB_CTRL (GPIOCTRL_BASE + 0x080UL)
#define G32R5_GPIOH_CTRL (GPIOCTRL_BASE + 0x380UL)

/*
 * Pin cells are local bits in the port register.
 *   GPIOA bit 0 = GPIO0, GPIOB bit 0 = GPIO32, GPIOH bit 0 = GPIO224.
 *
 * G32R501 GPIOA holes: GPIO19 (internally tied to X1, not a GPIO),
 * GPIO20 and GPIO21 (Table 8: not available on any package).
 * G32R501 GPIOB holes: GPIO36, GPIO38 (no such pins), GPIO48, GPIO50,
 * GPIO51, GPIO52, GPIO55 (Table 8: not bonded), GPIO60-GPIO63.
 *
 * G32R502 GPIOA has GPIO0-GPIO31. GPIOB holes: GPIO36, GPIO38, GPIO39
 * (removed in datasheet V0.2.6), GPIO47, GPIO50-GPIO63.
 *
 * Port H, G32R501 Table 4: AIO224-AIO254 are digital inputs only.
 * GPIO255 is not implemented.
 * Port H, G32R502: AGPIO has full digital I/O, AIO is input only.
 *   AGPIO: GPIO224, 226, 227, 228, 230, 242
 *   AIO:   GPIO225, 231, 232, 233, 237, 238, 239, 241, 244, 245
 */
#if defined(CONFIG_SOC_SERIES_G32R502)
#define G32R5_GPIOA_VALID_MASK      0xFFFFFFFFUL
#define G32R5_GPIOB_VALID_MASK      0x00037F2FUL
#define G32R5_GPIOH_VALID_MASK      0x0036E3DFUL
#define G32R5_GPIOH_INPUT_ONLY_MASK 0x0032E382UL
#elif defined(CONFIG_SOC_SERIES_G32R501)
#define G32R5_GPIOA_VALID_MASK      0xFFC7FFFFUL
#define G32R5_GPIOB_VALID_MASK      0x0F62FFAFUL
#define G32R5_GPIOH_VALID_MASK      0x7FFFFFFFUL
#define G32R5_GPIOH_INPUT_ONLY_MASK 0x7FFFFFFFUL
#else
#error "gpio_g32r5.c requires CONFIG_SOC_SERIES_G32R501 or CONFIG_SOC_SERIES_G32R502"
#endif

#define G32R5_PORT_VALID_MASK(addr)                                                        \
	(((addr) == G32R5_GPIOH_CTRL) ? G32R5_GPIOH_VALID_MASK :                           \
	 ((addr) == G32R5_GPIOB_CTRL) ? G32R5_GPIOB_VALID_MASK :                           \
	 ((addr) == G32R5_GPIOA_CTRL) ? G32R5_GPIOA_VALID_MASK :                           \
					0UL)

struct gpio_g32r5_config
{
	struct gpio_driver_config common;
	uint32_t ctrl_regs_base;
	uint32_t data_regs_base;
	uint32_t input_only_mask;
};

struct gpio_g32r5_data
{
	struct gpio_driver_data common;
	sys_slist_t callbacks;
};

/*
 * Flexible GPIO interrupts use two pools that are shared by every port.
 *
 * EXTI lines 0-3 select one GPIO in a fixed group of 15 (GPIO0-14, 15-29,
 * 30-44, 45-59) through GPIOSEL. Port H cannot use these lines.
 *
 * XINT1-5 are EXTI lines 4-8. Input XBAR INPUT4/5/6/13/14 routes any
 * XBAR-valid GPIO, including port H, onto those lines. A sixth request
 * returns -EBUSY. G32R501 AIO248-AIO254 are digital inputs but are outside
 * the XBAR selector, so they cannot interrupt.
 *
 * The vendor EXTI_clearInterruptStatus() writes ~bit into a write-1-to-clear
 * pending register, which clears every other line and leaves the target set.
 * This driver writes only the target bit.
 */
#define G32R5_GROUP_IRQ_COUNT 4
#define G32R5_XINT_COUNT      5
#define G32R5_XINT_NONE       0xFFU

struct g32r5_irq_slot {
	const struct device *dev;
	uint8_t pin;
	uint8_t line;
	uint8_t xint;
};

static struct g32r5_irq_slot group_slot[G32R5_GROUP_IRQ_COUNT] = {
	{ .line = 0, .xint = G32R5_XINT_NONE },
	{ .line = 1, .xint = G32R5_XINT_NONE },
	{ .line = 2, .xint = G32R5_XINT_NONE },
	{ .line = 3, .xint = G32R5_XINT_NONE },
};

static struct g32r5_irq_slot xint_slot[G32R5_XINT_COUNT] = {
	{ .line = 4, .xint = 0 },
	{ .line = 5, .xint = 1 },
	{ .line = 6, .xint = 2 },
	{ .line = 7, .xint = 3 },
	{ .line = 8, .xint = 4 },
};

static const XBAR_InputNum xint_input[G32R5_XINT_COUNT] = {
	XBAR_INPUT4, XBAR_INPUT5, XBAR_INPUT6, XBAR_INPUT13, XBAR_INPUT14,
};

#if defined(CONFIG_SOC_SERIES_G32R501) && defined(__CORE_CPU1__)
#define G32R5_EXTI_IPEND_OFF EXTI_O_IPEND1
#else
#if defined(CONFIG_SOC_SERIES_G32R501)
#define G32R5_EXTI_IPEND_OFF EXTI_O_IPEND0
#else
#define G32R5_EXTI_IPEND_OFF EXTI_O_IPEND
#endif
#endif

static void exti_line_enable(EXTI_LineNumber line)
{
#if defined(CONFIG_SOC_SERIES_G32R501)
#if defined(__CORE_CPU1__)
	EXTI_enableInterrupt(EXTI_CORE_CPU1, line);
#else
	EXTI_enableInterrupt(EXTI_CORE_CPU0, line);
#endif
#else
	EXTI_enableInterrupt(line);
#endif
}

static void exti_line_disable(EXTI_LineNumber line)
{
#if defined(CONFIG_SOC_SERIES_G32R501)
#if defined(__CORE_CPU1__)
	EXTI_disableInterrupt(EXTI_CORE_CPU1, line);
#else
	EXTI_disableInterrupt(EXTI_CORE_CPU0, line);
#endif
#else
	EXTI_disableInterrupt(line);
#endif
}

static void exti_line_clear(uint32_t line)
{
	volatile uint32_t *pend =
		(uint32_t *)(EXTI_BASE + G32R5_EXTI_IPEND_OFF);

	WRPRT_DISABLE;
	*pend = BIT(line);
	WRPRT_ENABLE;
}

static uint32_t exti_pending(void)
{
	volatile uint32_t *pend =
		(uint32_t *)(EXTI_BASE + G32R5_EXTI_IPEND_OFF);

	return *pend;
}

static uint32_t port_gpio_base(const struct gpio_g32r5_config *config)
{
	if (config->ctrl_regs_base == G32R5_GPIOB_CTRL) {
		return 32U;
	}
	if (config->ctrl_regs_base == G32R5_GPIOH_CTRL) {
		return 224U;
	}
	return 0U;
}

static bool xbar_pin_ok(uint32_t gpio)
{
	if (gpio <= XBAR_GPIO_MAX_CNT) {
		return true;
	}

	return (gpio >= XBAR_GPIO_AIO_MIN_CNT) &&
	       (gpio <= XBAR_GPIO_AIO_MAX_CNT);
}

static struct g32r5_irq_slot *find_slot(const struct device *dev, gpio_pin_t pin)
{
	int i;

	for (i = 0; i < G32R5_GROUP_IRQ_COUNT; i++) {
		if (group_slot[i].dev == dev && group_slot[i].pin == pin) {
			return &group_slot[i];
		}
	}

	for (i = 0; i < G32R5_XINT_COUNT; i++) {
		if (xint_slot[i].dev == dev && xint_slot[i].pin == pin) {
			return &xint_slot[i];
		}
	}

	return NULL;
}

static void release_slot(struct g32r5_irq_slot *slot)
{
	exti_line_disable((EXTI_LineNumber)slot->line);
	exti_line_clear(slot->line);
	slot->dev = NULL;
}

static void route_slot(const struct g32r5_irq_slot *slot, uint32_t gpio)
{
	if (slot->xint == G32R5_XINT_NONE) {
		uint32_t group = gpio / 15U;
		uint32_t offset = gpio % 15U;

		/* GPIOSEL nibble shift is group*4; the value is the pin in the group. */
		EXTI_setTriggerSelect(((group * 4U) << 4U) | offset);
	} else {
		XBAR_setInputPin(xint_input[slot->xint], (uint16_t)gpio);
	}
}

static void arm_slot(const struct g32r5_irq_slot *slot, uint32_t gpio,
		     EXTI_TriggerEdge edge)
{
	EXTI_LineNumber line = (EXTI_LineNumber)slot->line;

	exti_line_disable(line);
	route_slot(slot, gpio);
	EXTI_setTriggerEdge(line, edge);
	exti_line_clear(line);
	exti_line_enable(line);
}

static struct g32r5_irq_slot *claim_slot(const struct device *dev, gpio_pin_t pin,
					 uint32_t gpio, int *err)
{
	struct g32r5_irq_slot *slot;
	int group;
	int i;

	slot = find_slot(dev, pin);
	if (slot != NULL) {
		return slot;
	}

	group = (gpio <= 59U) ? (int)(gpio / 15U) : -1;
	if (group >= 0 && group_slot[group].dev == NULL) {
		group_slot[group].dev = dev;
		group_slot[group].pin = (uint8_t)pin;
		return &group_slot[group];
	}

	if (!xbar_pin_ok(gpio)) {
		*err = -ENOTSUP;
		return NULL;
	}

	for (i = 0; i < G32R5_XINT_COUNT; i++) {
		if (xint_slot[i].dev == NULL) {
			xint_slot[i].dev = dev;
			xint_slot[i].pin = (uint8_t)pin;
			return &xint_slot[i];
		}
	}

	*err = -EBUSY;
	return NULL;
}

static int trig_to_edge(enum gpio_int_trig trig, EXTI_TriggerEdge *edge)
{
	uint32_t level = (uint32_t)trig & (GPIO_INT_LOW_0 | GPIO_INT_HIGH_1);

	if (((uint32_t)trig & ~(GPIO_INT_LOW_0 | GPIO_INT_HIGH_1)) != 0U) {
		return -ENOTSUP;
	}

	if (level == GPIO_INT_TRIG_HIGH) {
		*edge = EXTI_TRIGGER_EDGE_RISING;
	} else if (level == GPIO_INT_TRIG_LOW) {
		*edge = EXTI_TRIGGER_EDGE_FALLING;
	} else if (level == GPIO_INT_TRIG_BOTH) {
		*edge = EXTI_TRIGGER_EDGE_BOTH;
	} else {
		return -EINVAL;
	}

	return 0;
}

static void g32r5_exti_isr(const void *arg)
{
	const struct g32r5_irq_slot *slot = arg;
	const struct device *port = slot->dev;
	struct gpio_g32r5_data *data;

	exti_line_clear(slot->line);
	if (port == NULL) {
		return;
	}

	data = port->data;
	gpio_fire_callbacks(&data->callbacks, port, BIT(slot->pin));
}

static void g32r5_gpio_irqs_init(void)
{
	static bool done;

	if (done) {
		return;
	}
	done = true;

	IRQ_CONNECT(EXTI_LINE0_IRQn, 2, g32r5_exti_isr, &group_slot[0], 0);
	IRQ_CONNECT(EXTI_LINE1_IRQn, 2, g32r5_exti_isr, &group_slot[1], 0);
	IRQ_CONNECT(EXTI_LINE2_IRQn, 2, g32r5_exti_isr, &group_slot[2], 0);
	IRQ_CONNECT(EXTI_LINE3_IRQn, 2, g32r5_exti_isr, &group_slot[3], 0);
	IRQ_CONNECT(EXTI_LINE4_IRQn, 2, g32r5_exti_isr, &xint_slot[0], 0);
	IRQ_CONNECT(EXTI_LINE5_IRQn, 2, g32r5_exti_isr, &xint_slot[1], 0);
	IRQ_CONNECT(EXTI_LINE6_IRQn, 2, g32r5_exti_isr, &xint_slot[2], 0);
	IRQ_CONNECT(EXTI_LINE7_IRQn, 2, g32r5_exti_isr, &xint_slot[3], 0);
	IRQ_CONNECT(EXTI_LINE8_IRQn, 2, g32r5_exti_isr, &xint_slot[4], 0);

	irq_enable(EXTI_LINE0_IRQn);
	irq_enable(EXTI_LINE1_IRQn);
	irq_enable(EXTI_LINE2_IRQn);
	irq_enable(EXTI_LINE3_IRQn);
	irq_enable(EXTI_LINE4_IRQn);
	irq_enable(EXTI_LINE5_IRQn);
	irq_enable(EXTI_LINE6_IRQn);
	irq_enable(EXTI_LINE7_IRQn);
	irq_enable(EXTI_LINE8_IRQn);
}

static bool is_port_h(const struct gpio_g32r5_config *config)
{
	return config->ctrl_regs_base == G32R5_GPIOH_CTRL;
}

/*
 * GPIO mode is function 0. The low 2 bits live in MUXn and the high 2 bits
 * in GMUXn, 0x34 bytes later. Ports A, B and H share this layout.
 * Clear MUX before GMUX so the pad does not pass through another function.
 */
static void gpio_select_gpio_mode(uint32_t ctrl_base, gpio_pin_t pin)
{
	uint32_t shift = ((uint32_t)pin & 0x0FU) * 2U;
	uint32_t mask = 3U << shift;
	uint32_t mux_off = (pin < 16U) ? GPMUX1_OFFSET : GPMUX2_OFFSET;
	uint32_t gmux_off = (pin < 16U) ? GPGMUX1_OFFSET : GPGMUX2_OFFSET;
	volatile uint32_t *mux = (uint32_t *)(ctrl_base + mux_off);
	volatile uint32_t *gmux = (uint32_t *)(ctrl_base + gmux_off);

	*mux &= ~mask;
	*gmux &= ~mask;
}

static int output_mask_check(const struct gpio_g32r5_config *config,
			     gpio_port_pins_t pins)
{
	if ((pins & ~config->common.port_pin_mask) != 0U) {
		return -EINVAL;
	}

	if ((pins & config->input_only_mask) != 0U) {
		return -ENOTSUP;
	}

	return 0;
}

static int gpio_g32r5_port_get_raw(const struct device *dev, uint32_t *value)
{
	const struct gpio_g32r5_config *config = dev->config;
	volatile uint32_t *p_dat = (uint32_t *)(config->data_regs_base + GPDAT_OFFSET);

	*value = *p_dat & config->common.port_pin_mask;

	return 0;
}

static int gpio_g32r5_port_set_bits_raw(const struct device *dev,
					gpio_port_pins_t pins)
{
	const struct gpio_g32r5_config *config = dev->config;
	int ret = output_mask_check(config, pins);
	volatile uint32_t *p_set;

	if (ret != 0) {
		return ret;
	}

	p_set = (uint32_t *)(config->data_regs_base + GPSET_OFFSET);
	*p_set = pins;

	return 0;
}

static int gpio_g32r5_port_clear_bits_raw(const struct device *dev,
					  gpio_port_pins_t pins)
{
	const struct gpio_g32r5_config *config = dev->config;
	int ret = output_mask_check(config, pins);
	volatile uint32_t *p_clr;

	if (ret != 0) {
		return ret;
	}

	p_clr = (uint32_t *)(config->data_regs_base + GPCLR_OFFSET);
	*p_clr = pins;

	return 0;
}

static int gpio_g32r5_port_toggle_bits(const struct device *dev,
				       gpio_port_pins_t pins)
{
	const struct gpio_g32r5_config *config = dev->config;
	int ret = output_mask_check(config, pins);
	volatile uint32_t *p_toggle;

	if (ret != 0) {
		return ret;
	}

	p_toggle = (uint32_t *)(config->data_regs_base + GPTOGGLE_OFFSET);
	*p_toggle = pins;

	return 0;
}

static int gpio_g32r5_configure(const struct device *dev,
				gpio_pin_t pin, gpio_flags_t flags)
{
	const struct gpio_g32r5_config *config = dev->config;
	volatile uint32_t *ptr;
	uint32_t bit;
	bool output = (flags & GPIO_OUTPUT) != 0U;
	bool input = (flags & GPIO_INPUT) != 0U;
	bool input_only;

	if (!gpio_port_pin_is_supported(config->common.port_pin_mask, pin)) {
		return -EINVAL;
	}

	/* Hardware has pull-up only. */
	if ((flags & GPIO_PULL_DOWN) != 0U) {
		return -ENOTSUP;
	}

	bit = BIT(pin);
	input_only = (config->input_only_mask & bit) != 0U;
	if (output && input_only) {
		return -ENOTSUP;
	}

	WRPRT_DISABLE;

	gpio_select_gpio_mode(config->ctrl_regs_base, pin);

	if (is_port_h(config)) {
		/* AMSEL=1 keeps the pin analog or disconnected. Digital use clears it. */
		ptr = (uint32_t *)(config->ctrl_regs_base + GPAMSEL_OFFSET);
		if (output || input) {
			*ptr &= ~bit;
		} else {
			*ptr |= bit;
		}
	}

	if (output) {
		if ((flags & GPIO_OUTPUT_INIT_HIGH) != 0U) {
			ptr = (uint32_t *)(config->data_regs_base + GPSET_OFFSET);
			*ptr = bit;
		} else if ((flags & GPIO_OUTPUT_INIT_LOW) != 0U) {
			ptr = (uint32_t *)(config->data_regs_base + GPCLR_OFFSET);
			*ptr = bit;
		}

		ptr = (uint32_t *)(config->ctrl_regs_base + GPDIR_OFFSET);
		*ptr |= bit;
	} else if (!input_only) {
		/* Input or disabled: clear DIR so the pad stops driving. */
		ptr = (uint32_t *)(config->ctrl_regs_base + GPDIR_OFFSET);
		*ptr &= ~bit;
	}

	ptr = (uint32_t *)(config->ctrl_regs_base + GPPUD_OFFSET);
	if ((flags & GPIO_PULL_UP) != 0U) {
		*ptr &= ~bit;
	} else {
		*ptr |= bit;
	}

	/* Input-only AIO pins have no open-drain bit. */
	if (!input_only) {
		ptr = (uint32_t *)(config->ctrl_regs_base + GPODR_OFFSET);
		if ((flags & GPIO_OPEN_DRAIN) != 0U) {
			*ptr |= bit;
		} else {
			*ptr &= ~bit;
		}
	}

	WRPRT_ENABLE;

	return 0;
}

static int gpio_g32r5_port_set_masked_raw(const struct device *dev,
					  gpio_port_pins_t mask,
					  gpio_port_value_t value)
{
	const struct gpio_g32r5_config *config = dev->config;
	int ret = output_mask_check(config, mask);
	gpio_port_pins_t set_bits = mask & value;
	gpio_port_pins_t clr_bits = mask & ~value;
	volatile uint32_t *reg;

	if (ret != 0) {
		return ret;
	}

	/* GPxSET/GPxCLR ignore zero bits, so pins outside mask stay unchanged. */
	if (set_bits != 0U) {
		reg = (uint32_t *)(config->data_regs_base + GPSET_OFFSET);
		*reg = set_bits;
	}

	if (clr_bits != 0U) {
		reg = (uint32_t *)(config->data_regs_base + GPCLR_OFFSET);
		*reg = clr_bits;
	}

	return 0;
}

static int gpio_g32r5_pin_interrupt_configure(const struct device *dev,
					      gpio_pin_t pin,
					      enum gpio_int_mode mode,
					      enum gpio_int_trig trig)
{
	const struct gpio_g32r5_config *config = dev->config;
	struct g32r5_irq_slot *slot;
	EXTI_TriggerEdge edge;
	uint32_t gpio;
	uint32_t key;
	int err = 0;

	if (!gpio_port_pin_is_supported(config->common.port_pin_mask, pin)) {
		return -EINVAL;
	}

	if (mode == GPIO_INT_MODE_LEVEL) {
		return -ENOTSUP;
	}

#if defined(CONFIG_GPIO_ENABLE_DISABLE_INTERRUPT)
	if ((mode == GPIO_INT_MODE_DISABLE_ONLY) ||
	    (mode == GPIO_INT_MODE_ENABLE_ONLY)) {
		key = irq_lock();
		slot = find_slot(dev, pin);
		if (slot == NULL) {
			irq_unlock(key);
			return -EINVAL;
		}
		if (mode == GPIO_INT_MODE_DISABLE_ONLY) {
			exti_line_disable((EXTI_LineNumber)slot->line);
		} else {
			exti_line_enable((EXTI_LineNumber)slot->line);
		}
		irq_unlock(key);
		return 0;
	}
#endif

	if (mode == GPIO_INT_MODE_DISABLED) {
		key = irq_lock();
		slot = find_slot(dev, pin);
		if (slot != NULL) {
			release_slot(slot);
		}
		irq_unlock(key);
		return 0;
	}

	if (mode != GPIO_INT_MODE_EDGE) {
		return -ENOTSUP;
	}

	err = trig_to_edge(trig, &edge);
	if (err != 0) {
		return err;
	}

	gpio = port_gpio_base(config) + pin;
	key = irq_lock();
	slot = claim_slot(dev, pin, gpio, &err);
	if (slot == NULL) {
		irq_unlock(key);
		return err;
	}
	arm_slot(slot, gpio, edge);
	irq_unlock(key);

	return 0;
}

static int gpio_g32r5_manage_callback(const struct device *dev,
				      struct gpio_callback *callback, bool set)
{
	struct gpio_g32r5_data *data = dev->data;

	return gpio_manage_callback(&data->callbacks, callback, set);
}

static uint32_t gpio_g32r5_get_pending_int(const struct device *dev)
{
	uint32_t pend = exti_pending();
	uint32_t pins = 0U;
	int i;

	for (i = 0; i < G32R5_GROUP_IRQ_COUNT; i++) {
		if ((group_slot[i].dev == dev) &&
		    ((pend & BIT(group_slot[i].line)) != 0U)) {
			pins |= BIT(group_slot[i].pin);
		}
	}

	for (i = 0; i < G32R5_XINT_COUNT; i++) {
		if ((xint_slot[i].dev == dev) &&
		    ((pend & BIT(xint_slot[i].line)) != 0U)) {
			pins |= BIT(xint_slot[i].pin);
		}
	}

	return pins;
}

static DEVICE_API(gpio, gpio_g32r5_api) = {
	.pin_configure = gpio_g32r5_configure,
	.port_get_raw = gpio_g32r5_port_get_raw,
	.port_set_masked_raw = gpio_g32r5_port_set_masked_raw,
	.port_set_bits_raw = gpio_g32r5_port_set_bits_raw,
	.port_clear_bits_raw = gpio_g32r5_port_clear_bits_raw,
	.port_toggle_bits = gpio_g32r5_port_toggle_bits,
	.pin_interrupt_configure = gpio_g32r5_pin_interrupt_configure,
	.manage_callback = gpio_g32r5_manage_callback,
	.get_pending_int = gpio_g32r5_get_pending_int,
};

static int gpio_g32r5_init(const struct device *dev)
{
	ARG_UNUSED(dev);

	g32r5_gpio_irqs_init();

	return 0;
}

#define GPIO_G32R5_DEFINE(inst)                                             \
	static const struct gpio_g32r5_config gpio_g32r5_config##inst = {   \
		.common = {                                                 \
			.port_pin_mask = G32R5_PORT_VALID_MASK(         \
				DT_INST_REG_ADDR(inst)),                    \
		},                                                          \
		.ctrl_regs_base = DT_INST_REG_ADDR(inst),                   \
		.data_regs_base =                                           \
			GPIODATA_BASE +                                     \
			(((DT_INST_REG_ADDR(inst) - GPIOCTRL_BASE) >> 7) << 4), \
		.input_only_mask = (DT_INST_REG_ADDR(inst) ==               \
				    G32R5_GPIOH_CTRL)                       \
					   ? G32R5_GPIOH_INPUT_ONLY_MASK    \
					   : 0U,                            \
	};                                                                  \
                                                                            \
	static struct gpio_g32r5_data gpio_g32r5_data##inst;                \
                                                                            \
	DEVICE_DT_INST_DEFINE(inst, gpio_g32r5_init, NULL,                  \
			      &gpio_g32r5_data##inst, &gpio_g32r5_config##inst, \
			      POST_KERNEL, CONFIG_GPIO_INIT_PRIORITY,       \
			      &gpio_g32r5_api);

DT_INST_FOREACH_STATUS_OKAY(GPIO_G32R5_DEFINE)
