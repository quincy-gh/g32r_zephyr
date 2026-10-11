移植 ZephyrRTOS 到 G32Rx 系列 MCU

# 关于 Zephyr RTOS

参阅官网 [👉 https://www.zephyrproject.org](https://www.zephyrproject.org/) 内容。

# 关于 G32R5

> G32R5系列实时控制MCU搭载Arm v8.1-M架构的Arm® Cortex®-M52内核及自研紫电数学指令扩展单元，支持基于矢量扩充方案（MVE）的Arm HeliumTM技术。

产品主页 [👉](https://global.geehy.com/product/fifth/G32R501)。

# 移植情况说明

当前支持 zephyr 的版本是 v4.5.0-rc1，会尽量保持跟进 zephyr 版本升级。

**重要提示**：本项目目前是基于 `EXTRA MODULES` 形式进行移植，使用时需要指定 `ZEPHYR_EXTRA_MODULES`。可以采用环境变量，或是 `-D` 参数传递。

## 支持的器件

目前支持的 MCU 有：
- G32R501
- G32R502

## 支持的编译器

- GCC, v15.3.1
- ARMClang, v6.22

## 外设列表

- [ ] adc
- [ ] can
- [x] clock_control
- [ ] comparator
- [ ] dac
- [ ] dma
- [ ] flash
- [x] gpio
- [ ] i2c
- [ ] interrupt_controller
- [ ] ipc
- [ ] lin
- [x] pinctrl
- [ ] pmbus
- [ ] pwm/hrpwm
- [ ] qep
- [ ] qspi
- [ ] sdf
- [x] serial
- [ ] spi
- [x] timer
- [ ] watchdog
- [ ] xbar

# 使用方法

## S1 创建开发环境

建议按 zephyr [官方文档](https://docs.zephyrproject.org/latest/) 进行操作，也可以参考 21ic 论坛上帖子：[[G32R] 来了来了 G32R501 可以用上 Zephyr 了](https://bbs.21ic.com/forum.php?mod=viewthread&tid=3467596&_dsign=d0fa0552)。


## S2 拉取本项目

```
git clone https://github.com/quincy-gh/g32r_zephyr.git
```

## S3 编译

在 zephyr 开发环境下执行以下命令可以编译 zephyr 自带的 blink 示例，基于 `g32r501_eval` 开发板。

```
cd g32r5_zephyr
set ZEPHYR_EXTRA_MODULES=%cd%
west build -p -b g32r501_eval/g32r501dvxt/cpu0 %ZEPHYR_BASE%\samples\basic\blinky
```

其中 `g32r501_eval/g32r501dvxt/cpu0` 指定了开发板的名称以及核心0，也可以简化为 `g32r501_eval//cpu0`，注意是两个 `//`。

上面的命令是在 `命令行窗口(cmd)` 执行，如果是 `power shell` 或者 `pwsh`，请参考下面的命令：

```pwsh
$env:ZEPHYR_EXTRA_MODULES = $PWD
west build -p -b g32r501_eval/g32r501dvxt/cpu0 $env:ZEPHYR_BASE\samples\basic\blinky
```

## S4 烧录

可以执行命令：

```
west flash
```

该命令调用 `pyocd` 进行烧录。

**需要注意**的是：截止2026年10月 G32R5 系列 MCU 尚未得到 pyocd 的原生支持，需要参考极海官方的应用笔记《AN1126_G32R5xx IDE and Tool Chain User Guide》打补丁~ 或者使用下面的方式安装打过补丁的 pyocd：

```
pip install --upgrade --force-reinstall --no-deps git+https://github.com/quincy-gh/pyOCD.git@g32r5xx
```


# 其他

本项目还处于初级阶段，欢迎工程师朋友试用。遇到问题可以直接提 issues ~ 感谢支持！
