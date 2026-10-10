/*
 * Copyright (c) 2026, Quincy.W <wangqyfm@foxmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * On-target ztest for the G32R5 CPU timer counter driver.
 *
 * TMR0 runs from SYSCLK. Callback counts are compared with k_uptime, so
 * this checks the timer against the kernel clock. It does not prove the
 * PLL frequency; that stays on XCLKOUT and the LED square wave started
 * after the suite (20 ms period on led0 / LD1).
 *
 * TMR2 tests are compiled only when the node is enabled. The INTOSC1
 * overlay points TMR2 at the 10 MHz oscillator and checks that a top
 * value counted in SYSCLK ticks takes longer wall time.
 */

#include <stdint.h>

#include <zephyr/drivers/counter.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/ztest.h>

#define TMR_PERIOD_US 10000U

static const struct device *const tmr0 = DEVICE_DT_GET(DT_NODELABEL(tmr0));
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

#if DT_NODE_HAS_STATUS(DT_NODELABEL(tmr2), okay)
static const struct device *const tmr2 = DEVICE_DT_GET(DT_NODELABEL(tmr2));
#endif

static volatile uint32_t hits;
static volatile uint32_t alarm_hits;
static uint32_t alarm_cookie;

K_SEM_DEFINE(hit_sem, 0, 256);
K_SEM_DEFINE(alarm_sem, 0, 4);

static void count_top(const struct device *dev, void *user_data)
{
	ARG_UNUSED(dev);
	ARG_UNUSED(user_data);

	hits++;
	k_sem_give(&hit_sem);
}

static void alarm_cb(const struct device *dev, uint8_t chan_id, uint32_t ticks,
		     void *user_data)
{
	ARG_UNUSED(dev);
	ARG_UNUSED(chan_id);
	ARG_UNUSED(ticks);

	if (user_data == &alarm_cookie) {
		alarm_hits++;
	}
	k_sem_give(&alarm_sem);
}

static void blink_top(const struct device *dev, void *user_data)
{
	ARG_UNUSED(dev);
	ARG_UNUSED(user_data);

	gpio_pin_toggle_dt(&led);
}

static int arm_top(const struct device *dev, uint32_t top_ticks,
		   counter_top_callback_t cb)
{
	struct counter_top_cfg top = {
		.ticks = top_ticks,
		.callback = cb,
	};

	return counter_set_top_value(dev, &top);
}

static void *tmr_setup(void)
{
	zassert_true(device_is_ready(tmr0), "tmr0");
	zassert_true(gpio_is_ready_dt(&led), "led0");
	zassert_ok(gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE));
	return NULL;
}

static void tmr_before(void *fixture)
{
	ARG_UNUSED(fixture);

	counter_stop(tmr0);
	counter_cancel_channel_alarm(tmr0, 0);
#if DT_NODE_HAS_STATUS(DT_NODELABEL(tmr2), okay)
	counter_stop(tmr2);
	counter_cancel_channel_alarm(tmr2, 0);
#endif
	hits = 0U;
	alarm_hits = 0U;
	k_sem_reset(&hit_sem);
	k_sem_reset(&alarm_sem);
}

/* Leave a 20 ms LED square wave running for the scope. */
static void tmr_teardown(void *fixture)
{
	uint32_t ticks = counter_us_to_ticks(tmr0, TMR_PERIOD_US);
	struct counter_top_cfg top = {
		.ticks = ticks - 1U,
		.callback = blink_top,
	};

	ARG_UNUSED(fixture);

	if ((ticks >= 2U) && (counter_set_top_value(tmr0, &top) == 0)) {
		counter_start(tmr0);
	}
	printk("scope: LD1 20 ms square, freq=%u\n", counter_get_frequency(tmr0));
}

ZTEST(g32r5_tmr, test_freq_is_sysclk)
{
	uint32_t expect = DT_PROP(DT_NODELABEL(sysclk), clock_frequency);

	zassert_equal(counter_get_frequency(tmr0), expect, "freq=%u",
		      counter_get_frequency(tmr0));
}

ZTEST(g32r5_tmr, test_us_to_ticks_10ms)
{
	uint32_t freq = counter_get_frequency(tmr0);

	zassert_not_equal(freq, 0U);
	zassert_equal(freq % 100U, 0U, "freq=%u is not a multiple of 100", freq);
	zassert_equal(counter_us_to_ticks(tmr0, TMR_PERIOD_US), freq / 100U);
}

ZTEST(g32r5_tmr, test_count_runs_only_while_started)
{
	uint32_t first;
	uint32_t second;
	uint32_t top = counter_get_top_value(tmr0);

	zassert_ok(counter_get_value(tmr0, &first));
	k_busy_wait(200);
	zassert_ok(counter_get_value(tmr0, &second));
	zassert_equal(first, second, "counter moved while stopped");

	zassert_true(top > 1U);
	zassert_ok(arm_top(tmr0, top, NULL));
	zassert_ok(counter_start(tmr0));
	zassert_ok(counter_get_value(tmr0, &first));
	k_busy_wait(200);
	zassert_ok(counter_get_value(tmr0, &second));
	zassert_not_equal(first, second, "counter did not move");
}

ZTEST(g32r5_tmr, test_alarm_rejects_bad_args)
{
	struct counter_alarm_cfg alarm = {
		.callback = alarm_cb,
		.ticks = 0U,
		.user_data = &alarm_cookie,
	};

	zassert_ok(arm_top(tmr0, 1000U, NULL));

	zassert_equal(counter_set_channel_alarm(tmr0, 0, &alarm), -EINVAL);

	alarm.ticks = 10U;
	alarm.callback = NULL;
	zassert_equal(counter_set_channel_alarm(tmr0, 0, &alarm), -EINVAL);

	alarm.callback = alarm_cb;
	alarm.ticks = 1001U;
	zassert_equal(counter_set_channel_alarm(tmr0, 0, &alarm), -EINVAL);

	alarm.ticks = 10U;
	alarm.flags = COUNTER_ALARM_CFG_ABSOLUTE;
	zassert_equal(counter_set_channel_alarm(tmr0, 0, &alarm), -ENOTSUP);
}

ZTEST(g32r5_tmr, test_set_top_busy_while_alarm_active)
{
	uint32_t window = counter_us_to_ticks(tmr0, 100000U);
	struct counter_alarm_cfg alarm = {
		.callback = alarm_cb,
		.user_data = &alarm_cookie,
	};
	struct counter_top_cfg top = {
		.ticks = window - 1U,
	};

	zassert_true(window > 2U);
	zassert_ok(arm_top(tmr0, window - 1U, NULL));
	zassert_ok(counter_start(tmr0));

	alarm.ticks = window - 1U;
	zassert_ok(counter_set_channel_alarm(tmr0, 0, &alarm));
	zassert_equal(counter_set_top_value(tmr0, &top), -EBUSY);

	zassert_ok(counter_cancel_channel_alarm(tmr0, 0));
	zassert_ok(counter_set_top_value(tmr0, &top));
}

ZTEST(g32r5_tmr, test_relative_alarm_fires_once)
{
	uint32_t window = counter_us_to_ticks(tmr0, 100000U);
	struct counter_alarm_cfg alarm = {
		.callback = alarm_cb,
		.ticks = counter_us_to_ticks(tmr0, TMR_PERIOD_US),
		.user_data = &alarm_cookie,
	};

	zassert_true(window > alarm.ticks);
	zassert_ok(arm_top(tmr0, window - 1U, NULL));
	zassert_ok(counter_start(tmr0));
	zassert_ok(counter_set_channel_alarm(tmr0, 0, &alarm));
	zassert_ok(k_sem_take(&alarm_sem, K_MSEC(50)));
	zassert_equal(alarm_hits, 1U);

	k_msleep(30);
	zassert_equal(alarm_hits, 1U, "alarm repeated");
}

ZTEST(g32r5_tmr, test_stop_freezes_top_callbacks)
{
	uint32_t ticks = counter_us_to_ticks(tmr0, TMR_PERIOD_US);
	uint32_t frozen;
	uint32_t i;

	zassert_true(ticks >= 2U);
	zassert_ok(arm_top(tmr0, ticks - 1U, count_top));
	zassert_ok(counter_start(tmr0));

	for (i = 0U; i < 3U; i++) {
		zassert_ok(k_sem_take(&hit_sem, K_MSEC(50)));
	}

	zassert_ok(counter_stop(tmr0));
	k_msleep(5);
	frozen = hits;
	k_msleep(40);
	zassert_equal(hits, frozen, "callbacks after stop: %u -> %u", frozen, hits);
}

ZTEST(g32r5_tmr, test_top_period_10ms)
{
	uint32_t ticks = counter_us_to_ticks(tmr0, TMR_PERIOD_US);
	int64_t start;
	int64_t elapsed;
	uint32_t i;

	zassert_true(ticks >= 2U);
	zassert_ok(arm_top(tmr0, ticks - 1U, count_top));
	start = k_uptime_get();
	zassert_ok(counter_start(tmr0));

	for (i = 0U; i < 100U; i++) {
		zassert_ok(k_sem_take(&hit_sem, K_MSEC(50)), "missing callback %u", i);
	}

	elapsed = k_uptime_delta(&start);
	zassert_within(elapsed, 1000, 50, "100 x 10 ms took %lld ms", elapsed);
}

#if DT_NODE_HAS_STATUS(DT_NODELABEL(tmr2), okay)
ZTEST(g32r5_tmr, test_tmr2_freq_is_intosc1)
{
	uint32_t expect = DT_PROP(DT_NODELABEL(clk_intosc_1), clock_frequency);

	zassert_true(device_is_ready(tmr2), "tmr2");
	zassert_equal(counter_get_frequency(tmr2), expect, "tmr2 freq=%u",
		      counter_get_frequency(tmr2));
	zassert_not_equal(counter_get_frequency(tmr2), counter_get_frequency(tmr0));
}

ZTEST(g32r5_tmr, test_tmr2_period_tracks_intosc1)
{
	uint32_t sysclk = DT_PROP(DT_NODELABEL(sysclk), clock_frequency);
	uint32_t tmr2_hz = counter_get_frequency(tmr2);
	uint32_t top = sysclk / 1000U - 1U;
	uint32_t expect_ms;
	int64_t start;
	int64_t elapsed;
	uint32_t i;

	zassert_true(tmr2_hz > 0U);
	zassert_true(top > 1U);
	/* Same top tick count as 1 ms of SYSCLK. INTOSC1 must stretch it. */
	expect_ms = (uint32_t)(((uint64_t)top + 1U) * 10U * 1000U / tmr2_hz);
	zassert_true(expect_ms > 50U, "stretch %u ms is too short", expect_ms);

	zassert_ok(arm_top(tmr2, top, count_top));
	start = k_uptime_get();
	zassert_ok(counter_start(tmr2));

	for (i = 0U; i < 10U; i++) {
		zassert_ok(k_sem_take(&hit_sem, K_MSEC(expect_ms)));
	}

	elapsed = k_uptime_delta(&start);
	zassert_within(elapsed, expect_ms, (expect_ms / 10U) + 5U,
		       "tmr2 10 wraps took %lld ms, expect %u", elapsed, expect_ms);
}
#endif

ZTEST_SUITE(g32r5_tmr, NULL, tmr_setup, tmr_before, NULL, tmr_teardown);
