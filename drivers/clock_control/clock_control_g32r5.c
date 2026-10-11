/**
 * @file clock_control_g32r5.c
 * @author Quincy.W <wangqyfm@foxmail.com>
 * @brief 
 * @version 0.1
 * @date 2025-07-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#define DT_DRV_COMPAT geehy_g32r5_sysclk

#include <soc.h>
#include <inc/hw_sysctl.h>
#include <inc/hw_memmap.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/irq.h>
#include <zephyr/sys/util.h>
#include <zephyr/drivers/clock_control/arm_clock_control.h>

#include "sysctl.h"
#include "gpio.h"
#include "pin_map.h"

#define OSC_SRC_INTOSC_1 1
#define OSC_SRC_INTOSC_2 2
#define OSC_SRC_XTAL 3
#define OSC_SRC_PLL 4

#if DT_SAME_NODE(DT_CLOCKS_CTLR(DT_NODELABEL(sysclk)), DT_NODELABEL(pll))

#define SYSCLK_SRC OSC_SRC_PLL

#if DT_SAME_NODE(DT_CLOCKS_CTLR(DT_NODELABEL(pll)), DT_NODELABEL(clk_intosc_1))
#define PLL_SRC OSC_SRC_INTOSC_1
#elif DT_SAME_NODE(DT_CLOCKS_CTLR(DT_NODELABEL(pll)), DT_NODELABEL(clk_intosc_2))
#define PLL_SRC OSC_SRC_INTOSC_2
#else
#define PLL_SRC OSC_SRC_XTAL
#endif

#elif DT_SAME_NODE(DT_CLOCKS_CTLR(DT_NODELABEL(sysclk)), DT_NODELABEL(clk_intosc_1))

#define SYSCLK_SRC OSC_SRC_INTOSC_1

#elif DT_SAME_NODE(DT_CLOCKS_CTLR(DT_NODELABEL(sysclk)), DT_NODELABEL(clk_intosc_2))

#define SYSCLK_SRC OSC_SRC_INTOSC_2

#else

#define SYSCLK_SRC OSC_SRC_XTAL

#endif

uint32_t SystemCoreClock;

struct clock_control_g32r5_config
{
    uint16_t apb_div;
    uint16_t lsp_div;
};

static int clock_control_g32r5_get_rate(const struct device *dev,
                                        clock_control_subsys_t sys,
                                        uint32_t *rate)
{
    const struct clock_control_g32r5_config *config = dev->config;
    int ret = 0;
    int id = (int)sys;

    switch (id)
    {
    case 0:
        // SYSCLK
        *rate = SystemCoreClock;
        break;

    case 1:
        // APBCLK
        *rate = SystemCoreClock / config->apb_div;

        break;

    case 2:
        // LSPCLK
        *rate = SystemCoreClock / config->apb_div / config->lsp_div;
        break;

    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

static DEVICE_API(clock_control, g32r5_clock_control_api) = {
    .get_rate = clock_control_g32r5_get_rate,
};

static int g32r5_control_init(const struct device *dev)
{
#if defined(__CORE_CPU1__)
    /* AMP: CPU0 owns the shared clock tree (PLL, APB/LSP dividers,
     * XCLKOUT). CPU1 reports rates from DT only and writes nothing. */
    ARG_UNUSED(dev);
    SystemCoreClock = DT_PROP(DT_NODELABEL(sysclk), clock_frequency);
    return 0;
#else
    const struct clock_control_g32r5_config *config = dev->config;
    uint32_t sysclk_freq;

#if (SYSCLK_SRC == OSC_SRC_PLL)
    uint32_t cfg;
    uint32_t pll_freq;
    uint16_t imult = DT_PROP(DT_NODELABEL(pll), imult);
    uint16_t fmult = DT_PROP(DT_NODELABEL(pll), fmult);
    uint16_t odiv = DT_PROP(DT_NODELABEL(pll), odiv);
    uint16_t pllsysclkdiv = DT_PROP(DT_NODELABEL(pll), pllsysclkdiv);

#if (PLL_SRC == OSC_SRC_INTOSC_1)
    cfg = SYSCTL_OSCSRC_OSC1;
    sysclk_freq = 10000000UL;
#elif (PLL_SRC == OSC_SRC_INTOSC_2)
    cfg = SYSCTL_OSCSRC_OSC2;
    sysclk_freq = 10000000UL;
#else
    cfg = SYSCTL_OSCSRC_XTAL;
    sysclk_freq = DT_PROP(DT_NODELABEL(clk_xtal), clock_frequency);
#endif

    pll_freq = sysclk_freq * (4 * imult + fmult) / 4; // f(pll_vco) = f(src) * (i + f/4)
    if (pll_freq < 1000000UL || pll_freq > 600000000UL)
    {
        // f(pll_vco): [1MHz, 600MHz]
        return -EINVAL;
    }

    pll_freq /= odiv; // f(pll_out) = f(pll_vco) / odiv
    if (pll_freq < 1000000UL || pll_freq > 300000000UL)
    {
        // f(pll_out): [1MHz, 300MHz]
        return -EINVAL;
    }

    sysclk_freq = pll_freq / pllsysclkdiv; // f(sysclk) = f(pll_out) / pllsysclkdiv
    if (DT_PROP(DT_NODELABEL(sysclk), clock_frequency) != sysclk_freq)
    {
        return -EINVAL;
    }

    cfg |= SYSCTL_IMULT(imult);
    cfg |= SYSCTL_ODIV(odiv);
    cfg |= SYSCTL_SYSDIV(pllsysclkdiv);

    // fmult
    // - 0: 0
    // - 1: 0.25
    // - 2: 0.5
    // - 3: 0.75
    if (fmult == 3)
    {
        cfg |= SYSCTL_FMULT_3_4;
    }
    else if (fmult == 2)
    {
        cfg |= SYSCTL_FMULT_1_2;
    }
    else if (fmult == 1)
    {
        cfg |= SYSCTL_FMULT_1_4;
    }
    else
    {
        cfg |= SYSCTL_FMULT_NONE;
    }

    cfg |= SYSCTL_PLL_ENABLE;

    SysCtl_setClock(cfg);

#else

#if (SYSCLK_SRC == OSC_SRC_INTOSC_1)

    SysCtl_selectOscSource(SYSCTL_OSCSRC_OSC1);
    sysclk_freq = 10000000UL;

#elif (SYSCLK_SRC == OSC_SRC_INTOSC_2)

    SysCtl_selectOscSource(SYSCTL_OSCSRC_OSC2);
    sysclk_freq = 10000000UL;

#else

    SysCtl_selectOscSource(SYSCTL_OSCSRC_XTAL);
    sysclk_freq = DT_PROP(DT_NODELABEL(clk_xtal), clock_frequency);

#endif

    if (DT_PROP(DT_NODELABEL(sysclk), clock_frequency) != sysclk_freq)
    {
        return -EINVAL;
    }

#endif

    if (config->apb_div < 1 || config->apb_div > 2)
    {
        // APB prescaler: [1, 2]
        return -EINVAL;
    }

    SysCtl_setAPBClock((SysCtl_APBCLKPrescaler)(config->apb_div >> 1));

    if (config->lsp_div < 1 || config->lsp_div > 14 ||
        ((config->lsp_div != 1) && ((config->lsp_div & 1U) != 0U)))
    {
        // LSP prescaler: 1 or even, [1, 14]
        return -EINVAL;
    }

    // LOSPCP encoding: value 0 is /1, value N is /(2*N), so div / 2 is the code.
    SysCtl_setLowSpeedClock((SysCtl_LSPCLKPrescaler)(config->lsp_div / 2));

    SystemCoreClock = sysclk_freq;

#if CONFIG_XCLKOUT

#if (CONFIG_XCLKOUT_PIN == 16)
    GPIO_setPinConfig(GPIO_16_XCLKOUT);
#elif (CONFIG_XCLKOUT_PIN == 18)
    GPIO_setPinConfig(GPIO_18_XCLKOUT);
#else
#error Invalid XCLKOUT Pin
#endif

    SysCtl_setXClk((SysCtl_XClkDivider)CONFIG_XCLKOUT_DIV);

#if defined(CONFIG_XCLKOUT_SRC_PLLSYSCLK)
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_PLLSYS);
#elif defined(CONFIG_XCLKOUT_SRC_PLLRAWCLK)
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_PLLRAW);
#elif defined(CONFIG_XCLKOUT_SRC_SYSCLK)
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_SYSCLK);
#elif defined(CONFIG_XCLKOUT_SRC_APBCLK)
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_APBCLK);
#elif defined(CONFIG_XCLKOUT_SRC_INTOSC1)
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_INTOSC1);
#elif defined(CONFIG_XCLKOUT_SRC_INTOSC2)
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_INTOSC2);
#elif defined(CONFIG_XCLKOUT_SRC_XTAL)
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_XTALOSC);
#endif

#endif /* #if CONFIG_XCLKOUT */

    return 0;
#endif /* #if defined(__CORE_CPU1__) */
}

static const struct clock_control_g32r5_config g32r5_cc_cfg = {
    .apb_div = DT_PROP(DT_NODELABEL(sysclk), apb_prescaler),
    .lsp_div = DT_PROP(DT_NODELABEL(sysclk), lsp_prescaler),
};

/**
 * @brief Clock Control device init
 *
 */
DEVICE_DT_INST_DEFINE(0, g32r5_control_init, NULL,
                      NULL, &g32r5_cc_cfg, PRE_KERNEL_1,
                      CONFIG_CLOCK_CONTROL_INIT_PRIORITY,
                      &g32r5_clock_control_api);