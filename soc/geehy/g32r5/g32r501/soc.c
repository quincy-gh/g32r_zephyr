/**
 * @file soc.c
 * @author Quincy.W <wangqyfm@foxmail.com>
 * @brief 
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include "soc.h"

#if defined(CONFIG_SOC_PREP_HOOK)

// execute before z_bss_zero and z_data_copy(C runtime initialize)
void soc_prep_hook(void)
{
    // Enable CP0 Full Access and CP0 Non-secure Access
    SCB->CPACR |= (3U << 0U*2U);
    SCB->NSACR |= (3U << 0U*2U);

    // Enable WRPRT Protection COP
    SCB->CPACR |= 0xC;

    __DSB();
    __ISB();
    
    // Disable the Watchdog Timer
    __wrprt_disable();
    WD->WDCR = (0x5U << WD_WDCR_WDCHK_Pos) |
               (0x1U << WD_WDCR_WDDIS_Pos);
    __wrprt_enable();
}

#endif /* CONFIG_SOC_PREP_HOOK */