/**
 * @file soc.c
 * @author Quincy.W <wangqyfm@foxmail.com>
 * @brief
 * @version 0.1
 * @date 2026-10-01
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include "soc.h"

#if defined(CONFIG_SOC_PREP_HOOK)

/* Runs before z_bss_zero and z_data_copy. WD is 0x40010000 on G32R502. */
void soc_prep_hook(void)
{
	/* Enable CP0 full access and CP0 non-secure access.
	 * WRPRT uses the custom coprocessor.
	 */
	SCB->CPACR |= (3U << 0U * 2U);
	SCB->NSACR |= (3U << 0U * 2U);

	SCB->CPACR |= 0xC;

	__DSB();
	__ISB();

	/* Disable the watchdog. The key and WDDIS bit match g32r502.h. */
	__wrprt_disable();
	WD->WDCR = (0x5U << WD_WDCR_WDCHK_Pos) |
		   (0x1U << WD_WDCR_WDDIS_Pos);
	__wrprt_enable();
}

#endif /* CONFIG_SOC_PREP_HOOK */
