/**
 * @file gpio_def_g32r5.h
 * @author Quincy.W <wangqyfm@foxmail.com>
 * @brief 
 * @version 0.2
 * @date 2026-10-09
 * 
 * @copyright Copyright (c) 2025-2026
 * 
 */
#ifndef GPIO_DEF_G32R5_H
#define GPIO_DEF_G32R5_H

#define G32R5_GPIO_GPACTRL  0x00U  // 端口 A 采样周期寄存器
#define G32R5_GPIO_GPAQSEL1 0x04U  // 端口 A 输入类型寄存器 1
#define G32R5_GPIO_GPAQSEL2 0x08U  // 端口 A 输入类型寄存器 2
#define G32R5_GPIO_GPAMUX1  0x0CU  // 端口 A 复用低位寄存器 1
#define G32R5_GPIO_GPAMUX2  0x10U  // 端口 A 复用低位寄存器 2
#define G32R5_GPIO_GPADIR   0x14U  // 端口 A 数据方向寄存器
#define G32R5_GPIO_GPAPUD   0x18U  // 端口 A 上拉禁用寄存器
#define G32R5_GPIO_GPAINV   0x20U  // 端口 A 输入反相寄存器
#define G32R5_GPIO_GPAODR   0x24U  // 端口 A 开漏输出寄存器
#define G32R5_GPIO_GPAAMSEL 0x28U  // 端口 A 模拟模式选择寄存器
#define G32R5_GPIO_GPADSEL1 0x2CU  // 端口 A 驱动能力选择寄存器 1
#define G32R5_GPIO_GPADSEL2 0x30U  // 端口 A 驱动能力选择寄存器 2
#define G32R5_GPIO_GPAFEN   0x34U  // 端口 A 最大输出频率使能寄存器
#define G32R5_GPIO_GPAGMUX1 0x40U  // 端口 A 复用高位寄存器 1
#define G32R5_GPIO_GPAGMUX2 0x44U  // 端口 A 复用高位寄存器 2
#define G32R5_GPIO_GPACSEL1 0x50U  // 端口 A 主核选择寄存器 1
#define G32R5_GPIO_GPACSEL2 0x54U  // 端口 A 主核选择寄存器 2
#define G32R5_GPIO_GPACSEL3 0x58U  // 端口 A 主核选择寄存器 3
#define G32R5_GPIO_GPACSEL4 0x5CU  // 端口 A 主核选择寄存器 4
#define G32R5_GPIO_GPALOCK  0x78U  // 端口 A 锁定寄存器
#define G32R5_GPIO_GPACR    0x7CU  // 端口 A 提交锁定寄存器
#define G32R5_GPIO_GPBCTRL  0x80U  // 端口 B 采样周期寄存器
#define G32R5_GPIO_GPBQSEL1 0x84U  // 端口 B 输入类型寄存器 1
#define G32R5_GPIO_GPBQSEL2 0x88U  // 端口 B 输入类型寄存器 2
#define G32R5_GPIO_GPBMUX1  0x8CU  // 端口 B 复用低位寄存器 1
#define G32R5_GPIO_GPBMUX2  0x90U  // 端口 B 复用低位寄存器 2
#define G32R5_GPIO_GPBDIR   0x94U  // 端口 B 数据方向寄存器
#define G32R5_GPIO_GPBPUD   0x98U  // 端口 B 上拉禁用寄存器
#define G32R5_GPIO_GPBINV   0xA0U  // 端口 B 输入反相寄存器
#define G32R5_GPIO_GPBODR   0xA4U  // 端口 B 开漏输出寄存器
#define G32R5_GPIO_GPBAMSEL 0xA8U  // 端口 B 模拟模式选择寄存器
#define G32R5_GPIO_GPBDSEL1 0xACU  // 端口 B 驱动能力选择寄存器 1
#define G32R5_GPIO_GPBDSEL2 0xB0U  // 端口 B 驱动能力选择寄存器 2
#define G32R5_GPIO_GPBFEN   0xB4U  // 端口 B 最大输出频率使能寄存器
#define G32R5_GPIO_GPBGMUX1 0xC0U  // 端口 B 复用高位寄存器 1
#define G32R5_GPIO_GPBGMUX2 0xC4U  // 端口 B 复用高位寄存器 2
#define G32R5_GPIO_GPBCSEL1 0xD0U  // 端口 B 主核选择寄存器 1
#define G32R5_GPIO_GPBCSEL2 0xD4U  // 端口 B 主核选择寄存器 2
#define G32R5_GPIO_GPBCSEL3 0xD8U  // 端口 B 主核选择寄存器 3
#define G32R5_GPIO_GPBCSEL4 0xDCU  // 端口 B 主核选择寄存器 4
#define G32R5_GPIO_GPBLOCK  0xF8U  // 端口 B 锁定寄存器
#define G32R5_GPIO_GPBCR    0xFCU  // 端口 B 提交锁定寄存器
#define G32R5_GPIO_GPHMUX1  0x38CU // 端口 H 复用低位寄存器 1（GPIO224..239）
#define G32R5_GPIO_GPHMUX2  0x390U // 端口 H 复用低位寄存器 2（GPIO240..255）
#define G32R5_GPIO_GPHPUD   0x398U // 端口 H 上拉禁用寄存器
#define G32R5_GPIO_GPHODR   0x3A4U // 端口 H 开漏输出寄存器
#define G32R5_GPIO_GPHAMSEL 0x3A8U // 端口 H 模拟模式选择寄存器
#define G32R5_GPIO_GPHDSEL1 0x3ACU // 端口 H 驱动能力选择寄存器 1
#define G32R5_GPIO_GPHDSEL2 0x3B0U // 端口 H 驱动能力选择寄存器 2
#define G32R5_GPIO_GPHFEN   0x3B4U // 端口 H 最大输出频率使能寄存器

#define G32R5_GPIO_GPADAT    0x00U // 端口 A 数据寄存器
#define G32R5_GPIO_GPASET    0x04U // 端口 A 设置寄存器
#define G32R5_GPIO_GPACLR    0x08U // 端口 A 清除寄存器
#define G32R5_GPIO_GPATOGGLE 0x0CU // 端口 A 切换寄存器
#define G32R5_GPIO_GPBDAT    0x10U // 端口 B 数据寄存器
#define G32R5_GPIO_GPBSET    0x14U // 端口 B 设置寄存器
#define G32R5_GPIO_GPBCLR    0x18U // 端口 B 清除寄存器
#define G32R5_GPIO_GPBTOGGLE 0x1CU // 端口 B 切换寄存器
// #define G32R5_GPIO_GPHDAT    0x70U // 端口 H 数据寄存器

#endif // GPIO_DEF_G32R5_H
