/**
 * @file counter_g32r5_tmr.c
 * @author Quincy.W <wangqyfm@foxmail.com>
 * @brief G32R5 CPU timer as a Zephyr counter
 * @version 0.1
 * @date 2026-10-10
 *
 * @copyright Copyright (c) 2025-2026
 *
 */

#define DT_DRV_COMPAT geehy_g32r5_tmr

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/irq.h>
#include <zephyr/logging/log.h>
#include <zephyr/spinlock.h>
#include <zephyr/sys/util.h>

#include "sysctl.h"
#include "tmr.h"

LOG_MODULE_REGISTER(counter_g32r5_tmr, CONFIG_COUNTER_LOG_LEVEL);

/*
 * Clock-control subsystem id 0 is SYSCLK. See clock_control_g32r5.c.
 * TMR0 and TMR1 run from SYSCLK. TMR2 selects SYSCLK, INTOSC1, INTOSC2
 * or XTAL in TMR2CLKCTL, then divides that input by 1, 2, 4, 8 or 16.
 * The timer prescaler (TDDR + 1) divides the clock after that mux.
 */
#define G32R5_SYSCLK_ID 0

/*
 * TIM loads PRD and counts down. The overflow IRQ is raised when TIM
 * reaches 0, then TIM is loaded from PRD again. One period is
 * (PRD + 1) * (TDDR + 1) input clocks, which is the Zephyr top value:
 * period_ticks = top + 1.
 *
 * TCR.TIF is write-1-to-clear. A read-modify-write that writes the
 * flag back clears it, so every control update masks TIF off unless
 * the write is meant to clear the flag.
 *
 * There is no compare channel. Channel 0 is the overflow used as a
 * one-shot relative alarm. It preempts the top period until it fires,
 * then the top period is restored. Absolute alarms cannot be placed
 * on a free-running count without a compare register.
 */

struct g32r5_tmr_config {
	struct counter_config_info info;
	uint32_t base;
	uint32_t prescaler;
	uint32_t clk_hz;
	uint8_t clk_src;
	uint8_t clk_div;
	void (*irq_config)(const struct device *dev);
};

struct g32r5_tmr_data {
	struct k_spinlock lock;
	uint32_t freq_hz;
	uint32_t top_value;
	counter_top_callback_t top_cb;
	void *top_user_data;
	counter_alarm_callback_t alarm_cb;
	void *alarm_user_data;
	bool alarm_active;
};

static void tmr_reload(uint32_t base)
{
	uint16_t tcr = HWREGH(base + TMR_O_TCR) & (uint16_t)~TMR_TCR_TIF;

	HWREGH(base + TMR_O_TCR) = tcr | TMR_TCR_TRB;
}

static void tmr_run(uint32_t base, bool run)
{
	uint16_t tcr = HWREGH(base + TMR_O_TCR) & (uint16_t)~TMR_TCR_TIF;

	if (run) {
		tcr &= (uint16_t)~TMR_TCR_TSS;
	} else {
		tcr |= TMR_TCR_TSS;
	}

	HWREGH(base + TMR_O_TCR) = tcr;
}

static void tmr_emulation_run_free(uint32_t base)
{
	uint16_t tcr = HWREGH(base + TMR_O_TCR);

	tcr &= (uint16_t)~(TMR_TCR_TIF | TMR_TCR_FREE | TMR_TCR_SOFT);
	tcr |= (uint16_t)TMR_EMULATIONMODE_RUNFREE;
	HWREGH(base + TMR_O_TCR) = tcr;
}

/* PCLKCR needs several cycles before the timer block answers. */
static void tmr_wait_clock(void)
{
	volatile uint32_t ack = HWREG(CPUSYS_BASE + SYSCTL_O_PCLKCR0);

	(void)ack;
}

static int tmr2_clk_prescaler(uint8_t div, TMR_Prescaler *code)
{
	switch (div) {
	case 1U:
		*code = TMR_CLOCK_PRESCALER_1;
		return 0;
	case 2U:
		*code = TMR_CLOCK_PRESCALER_2;
		return 0;
	case 4U:
		*code = TMR_CLOCK_PRESCALER_4;
		return 0;
	case 8U:
		*code = TMR_CLOCK_PRESCALER_8;
		return 0;
	case 16U:
		*code = TMR_CLOCK_PRESCALER_16;
		return 0;
	default:
		return -EINVAL;
	}
}

static int g32r5_tmr_tick_hz(const struct g32r5_tmr_config *config, uint32_t *hz)
{
	uint32_t src_hz;
	int ret;

	if (config->clk_src == TMR_CLOCK_SOURCE_SYS) {
		const struct device *clk = DEVICE_DT_GET(DT_NODELABEL(sysclk));

		if (!device_is_ready(clk)) {
			LOG_ERR("sysclk is not ready");
			return -ENODEV;
		}

		ret = clock_control_get_rate(clk, (clock_control_subsys_t)G32R5_SYSCLK_ID, &src_hz);
		if (ret < 0) {
			return ret;
		}
	} else {
		src_hz = config->clk_hz;
	}

	if ((config->clk_div == 0U) || (config->prescaler == 0U) ||
	    (src_hz / config->clk_div / config->prescaler == 0U)) {
		return -EINVAL;
	}

	*hz = src_hz / config->clk_div / config->prescaler;
	return 0;
}

static int tmr_enable_clock(uint32_t base)
{
	if (base == TMR0_BASE) {
		SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);
		return 0;
	}

	if (base == TMR1_BASE) {
		SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER1);
		return 0;
	}

	if (base == TMR2_BASE) {
		SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER2);
		return 0;
	}

	return -ENODEV;
}

static void tmr_program_period(uint32_t base, uint32_t top, bool reload)
{
	TMR_setPeriod(base, top);
	if (reload) {
		tmr_reload(base);
	}
}

static int g32r5_tmr_start(const struct device *dev)
{
	const struct g32r5_tmr_config *config = dev->config;
	struct g32r5_tmr_data *data = dev->data;
	k_spinlock_key_t key;

	key = k_spin_lock(&data->lock);
	TMR_clearOverflowFlag(config->base);
	tmr_run(config->base, true);
	k_spin_unlock(&data->lock, key);

	return 0;
}

static int g32r5_tmr_stop(const struct device *dev)
{
	const struct g32r5_tmr_config *config = dev->config;
	struct g32r5_tmr_data *data = dev->data;
	k_spinlock_key_t key;

	key = k_spin_lock(&data->lock);
	tmr_run(config->base, false);
	k_spin_unlock(&data->lock, key);

	return 0;
}

static int g32r5_tmr_get_value(const struct device *dev, uint32_t *ticks)
{
	const struct g32r5_tmr_config *config = dev->config;

	*ticks = TMR_getTimerCount(config->base);
	return 0;
}

static int g32r5_tmr_reset(const struct device *dev)
{
	const struct g32r5_tmr_config *config = dev->config;
	struct g32r5_tmr_data *data = dev->data;
	k_spinlock_key_t key;

	key = k_spin_lock(&data->lock);
	tmr_reload(config->base);
	TMR_clearOverflowFlag(config->base);
	k_spin_unlock(&data->lock, key);

	return 0;
}

static uint32_t g32r5_tmr_get_top_value(const struct device *dev)
{
	struct g32r5_tmr_data *data = dev->data;

	return data->top_value;
}

static uint32_t g32r5_tmr_get_freq(const struct device *dev)
{
	struct g32r5_tmr_data *data = dev->data;

	return data->freq_hz;
}

static uint32_t g32r5_tmr_get_pending_int(const struct device *dev)
{
	const struct g32r5_tmr_config *config = dev->config;

	return TMR_getTimerOverflowStatus(config->base) ? 1U : 0U;
}

static int g32r5_tmr_set_alarm(const struct device *dev, uint8_t chan_id,
			       const struct counter_alarm_cfg *alarm_cfg)
{
	const struct g32r5_tmr_config *config = dev->config;
	struct g32r5_tmr_data *data = dev->data;
	k_spinlock_key_t key;

	ARG_UNUSED(chan_id);

	if ((alarm_cfg->callback == NULL) || (alarm_cfg->ticks == 0U) ||
	    (alarm_cfg->ticks > data->top_value)) {
		return -EINVAL;
	}

	/*
	 * A relative alarm of N ticks needs (PRD + 1) == N, so PRD is
	 * N - 1. Changing PRD and reloading abandons the current count,
	 * so an absolute match against a free-running value is not
	 * representable on this timer.
	 */
	if ((alarm_cfg->flags & COUNTER_ALARM_CFG_ABSOLUTE) != 0U) {
		return -ENOTSUP;
	}

	key = k_spin_lock(&data->lock);

	if (data->alarm_active) {
		k_spin_unlock(&data->lock, key);
		return -EBUSY;
	}

	data->alarm_cb = alarm_cfg->callback;
	data->alarm_user_data = alarm_cfg->user_data;
	data->alarm_active = true;

	TMR_disableInterrupt(config->base);
	tmr_program_period(config->base, alarm_cfg->ticks - 1U, true);
	TMR_clearOverflowFlag(config->base);
	TMR_enableInterrupt(config->base);

	k_spin_unlock(&data->lock, key);
	return 0;
}

static int g32r5_tmr_cancel_alarm(const struct device *dev, uint8_t chan_id)
{
	const struct g32r5_tmr_config *config = dev->config;
	struct g32r5_tmr_data *data = dev->data;
	k_spinlock_key_t key;

	ARG_UNUSED(chan_id);

	key = k_spin_lock(&data->lock);

	if (!data->alarm_active) {
		k_spin_unlock(&data->lock, key);
		return 0;
	}

	data->alarm_cb = NULL;
	data->alarm_user_data = NULL;
	data->alarm_active = false;

	TMR_disableInterrupt(config->base);
	tmr_program_period(config->base, data->top_value, true);
	TMR_clearOverflowFlag(config->base);
	if (data->top_cb != NULL) {
		TMR_enableInterrupt(config->base);
	}

	k_spin_unlock(&data->lock, key);
	return 0;
}

static int g32r5_tmr_set_top_value(const struct device *dev, const struct counter_top_cfg *cfg)
{
	const struct g32r5_tmr_config *config = dev->config;
	struct g32r5_tmr_data *data = dev->data;
	k_spinlock_key_t key;
	bool reload = (cfg->flags & COUNTER_TOP_CFG_DONT_RESET) == 0U;

	key = k_spin_lock(&data->lock);

	if (data->alarm_active) {
		k_spin_unlock(&data->lock, key);
		return -EBUSY;
	}

	if (!reload) {
		uint32_t now = TMR_getTimerCount(config->base);

		/* Down counter: a count above the new top is already late. */
		if (now > cfg->ticks) {
			if ((cfg->flags & COUNTER_TOP_CFG_RESET_WHEN_LATE) != 0U) {
				reload = true;
			} else {
				k_spin_unlock(&data->lock, key);
				return -ETIME;
			}
		}
	}

	data->top_cb = cfg->callback;
	data->top_user_data = cfg->user_data;
	data->top_value = cfg->ticks;

	TMR_disableInterrupt(config->base);
	tmr_program_period(config->base, cfg->ticks, reload);
	TMR_clearOverflowFlag(config->base);
	if (cfg->callback != NULL) {
		TMR_enableInterrupt(config->base);
	}

	k_spin_unlock(&data->lock, key);
	return 0;
}

static void g32r5_tmr_isr(const struct device *dev)
{
	const struct g32r5_tmr_config *config = dev->config;
	struct g32r5_tmr_data *data = dev->data;
	counter_alarm_callback_t alarm_cb = NULL;
	counter_top_callback_t top_cb = NULL;
	void *user_data = NULL;
	k_spinlock_key_t key;

	if (!TMR_getTimerOverflowStatus(config->base)) {
		return;
	}

	TMR_clearOverflowFlag(config->base);

	key = k_spin_lock(&data->lock);

	if (data->alarm_active) {
		alarm_cb = data->alarm_cb;
		user_data = data->alarm_user_data;
		data->alarm_cb = NULL;
		data->alarm_user_data = NULL;
		data->alarm_active = false;

		/*
		 * Hardware has already reloaded TIM from the alarm
		 * period. Put the top period back before the callback
		 * so a re-armed alarm inside the callback wins.
		 */
		TMR_disableInterrupt(config->base);
		tmr_program_period(config->base, data->top_value, true);
		TMR_clearOverflowFlag(config->base);
		if (data->top_cb != NULL) {
			TMR_enableInterrupt(config->base);
		}
	} else if (data->top_cb != NULL) {
		top_cb = data->top_cb;
		user_data = data->top_user_data;
	}

	k_spin_unlock(&data->lock, key);

	if (alarm_cb != NULL) {
		/* Expiration count is 0; TIM has already been reloaded. */
		alarm_cb(dev, 0, 0U, user_data);
	} else if (top_cb != NULL) {
		top_cb(dev, user_data);
	}
}

static int g32r5_tmr_init(const struct device *dev)
{
	const struct g32r5_tmr_config *config = dev->config;
	struct g32r5_tmr_data *data = dev->data;
	uint32_t tick_hz;
	int ret;

	ret = g32r5_tmr_tick_hz(config, &tick_hz);
	if (ret < 0) {
		LOG_ERR("timer clock is unusable (%d)", ret);
		return ret;
	}

	data->freq_hz = tick_hz;
	data->top_value = config->info.max_top_value;
	data->top_cb = NULL;
	data->alarm_cb = NULL;
	data->alarm_active = false;

	ret = tmr_enable_clock(config->base);
	if (ret < 0) {
		return ret;
	}

	if (config->base == TMR2_BASE) {
		TMR_Prescaler clk_div;

		ret = tmr2_clk_prescaler(config->clk_div, &clk_div);
		if (ret < 0) {
			return ret;
		}

		TMR_selectClockSource(config->base, (TMR_ClockSource)config->clk_src, clk_div);
	}

	tmr_wait_clock();
	tmr_run(config->base, false);
	tmr_emulation_run_free(config->base);
	TMR_setPreScaler(config->base, (uint16_t)(config->prescaler - 1U));
	TMR_setPeriod(config->base, data->top_value);
	tmr_reload(config->base);
	TMR_disableInterrupt(config->base);
	TMR_clearOverflowFlag(config->base);
	config->irq_config(dev);

	return 0;
}

static DEVICE_API(counter, g32r5_tmr_api) = {
	.start = g32r5_tmr_start,
	.stop = g32r5_tmr_stop,
	.get_value = g32r5_tmr_get_value,
	.reset = g32r5_tmr_reset,
	.set_alarm = g32r5_tmr_set_alarm,
	.cancel_alarm = g32r5_tmr_cancel_alarm,
	.set_top_value = g32r5_tmr_set_top_value,
	.get_pending_int = g32r5_tmr_get_pending_int,
	.get_top_value = g32r5_tmr_get_top_value,
	.get_freq = g32r5_tmr_get_freq,
};

#define G32R5_TMR_CLK_SRC_OF(node)                                                                 \
	COND_CODE_1(DT_SAME_NODE(node, DT_NODELABEL(sysclk)), (TMR_CLOCK_SOURCE_SYS),               \
	(COND_CODE_1(DT_SAME_NODE(node, DT_NODELABEL(clk_intosc_1)), (TMR_CLOCK_SOURCE_INTOSC1),    \
	(COND_CODE_1(DT_SAME_NODE(node, DT_NODELABEL(clk_intosc_2)), (TMR_CLOCK_SOURCE_INTOSC2),    \
	(COND_CODE_1(DT_SAME_NODE(node, DT_NODELABEL(clk_xtal)), (TMR_CLOCK_SOURCE_XTAL),           \
	(-1))))))))

#define G32R5_TMR_CLK_SRC(n)                                                                       \
	COND_CODE_1(DT_INST_NODE_HAS_PROP(n, clocks),                                              \
		    (G32R5_TMR_CLK_SRC_OF(DT_INST_CLOCKS_CTLR(n))), (TMR_CLOCK_SOURCE_SYS))

#define G32R5_TMR_CLK_HZ(n)                                                                        \
	COND_CODE_1(DT_INST_NODE_HAS_PROP(n, clocks),                                              \
		    (COND_CODE_1(DT_SAME_NODE(DT_INST_CLOCKS_CTLR(n), DT_NODELABEL(sysclk)), (0),  \
				 (DT_PROP(DT_INST_CLOCKS_CTLR(n), clock_frequency)))),             \
		    (0))

#define G32R5_TMR_IRQ_CONFIG(n)                                                                    \
	static void g32r5_tmr_irq_config_##n(const struct device *dev)                             \
	{                                                                                          \
		IRQ_CONNECT(DT_INST_IRQN(n), DT_INST_IRQ(n, priority), g32r5_tmr_isr,              \
			    DEVICE_DT_INST_GET(n), 0);                                             \
		irq_enable(DT_INST_IRQN(n));                                                       \
	}

#define G32R5_TMR_INIT(n)                                                                          \
	BUILD_ASSERT(DT_INST_PROP(n, prescaler) >= 1, "prescaler must be >= 1");                   \
	BUILD_ASSERT(DT_INST_PROP(n, prescaler) <= 65536, "prescaler must be <= 65536");           \
	BUILD_ASSERT((DT_INST_REG_ADDR(n) == TMR2_BASE) || !DT_INST_NODE_HAS_PROP(n, clocks),      \
		     "clocks is valid on TMR2 only");                                              \
	BUILD_ASSERT((DT_INST_REG_ADDR(n) == TMR2_BASE) ||                                         \
			     !DT_INST_NODE_HAS_PROP(n, clock_prescaler),                           \
		     "clock-prescaler is valid on TMR2 only");                                     \
	BUILD_ASSERT(G32R5_TMR_CLK_SRC(n) >= 0, "unsupported TMR2 clock");                         \
	G32R5_TMR_IRQ_CONFIG(n)                                                                    \
	static struct g32r5_tmr_data g32r5_tmr_data_##n;                                           \
	static const struct g32r5_tmr_config g32r5_tmr_config_##n = {                              \
		.info = {                                                                          \
			.max_top_value = UINT32_MAX,                                               \
			.freq = 0U,                                                                \
			.flags = 0U,                                                               \
			.channels = 1U,                                                            \
		},                                                                                 \
		.base = DT_INST_REG_ADDR(n),                                                       \
		.prescaler = DT_INST_PROP(n, prescaler),                                           \
		.clk_hz = G32R5_TMR_CLK_HZ(n),                                                     \
		.clk_src = G32R5_TMR_CLK_SRC(n),                                                   \
		.clk_div = DT_INST_PROP_OR(n, clock_prescaler, 1),                                  \
		.irq_config = g32r5_tmr_irq_config_##n,                                            \
	};                                                                                         \
	DEVICE_DT_INST_DEFINE(n, g32r5_tmr_init, NULL, &g32r5_tmr_data_##n,                        \
			      &g32r5_tmr_config_##n, PRE_KERNEL_1, CONFIG_COUNTER_INIT_PRIORITY,   \
			      &g32r5_tmr_api);

DT_INST_FOREACH_STATUS_OKAY(G32R5_TMR_INIT)
