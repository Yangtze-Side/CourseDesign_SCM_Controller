# CourseDesign_SCM_Controller

2025 年课程设计「智能小车」的单片机（控制器）部分固件。

控制器运行在 STC15W4K32S4（STC15W 系列增强型 8051，主频 24 MHz）上，主要职责是：

- 用 MPU6500 六轴 IMU 做姿态解算，输出 pitch / roll / yaw；
- 采集摇杆（ADC）、左右按键、模式键与编码器旋钮的输入，换算成小车速度与航向指令；
- 通过蓝牙串口与小车端 MCU 通信：下发控制指令，接收小车回传的温湿度、超声波测距、PID 参数与偏航角；
- 板载三相无刷电机 FOC 驱动，配合 AS5600 磁编码器做角度闭环，模拟带「棘轮档位」手感的转向机构；
- 用 128×64 OLED 提供多页菜单式人机交互界面。

> 源码注释为 UTF-8 编码（对应 `config.h` 中的 `__ENCODING` 定义）。

---

## 一、硬件平台与外设分配

| 资源 | 引脚 | 说明 |
| --- | --- | --- |
| MCU | — | STC15W4K32S4，FOSC / MAIN_Fosc = 24 MHz（`config.h`） |
| 摇杆 | P1.0 / P1.1 | ADC 通道 0（Y 轴）/ 通道 1（X 轴），零点 511，量程 0~1023 |
| 左 / 右按键 | P0.0 / P0.3 | 低电平按下；摇杆模式下决定旋转速度 `vw` 的正负，其余页面用于左右切换 |
| 模式键 | P0.6 | 短按 / 长按（长按阈值 400 ms），用于进入页面、返回主页、修改参数 |
| 串口 | P1.6 (RxD) / P1.7 (TxD) | UART1，模式 1，115200 bps，波特率由定时器 2 产生；连接蓝牙模块与小车通信 |
| 蓝牙连接状态 | P3.2 | INT0 双边沿中断，实时刷新链路状态，显示在 OLED 上 |
| SPI | P2.1~P2.4 | 硬件 SPI（SCLK / MISO / MOSI / SS），工作模式 3，时钟 SYSCLK/32，P2.4 兼作 MPU6500 片选 NSS |
| IMU | SPI | MPU6500 六轴加速度计 + 陀螺仪，10 ms 周期读取并做四元数姿态解算 |
| 磁编码器 | P3.3 / P3.4 | 软件 I2C 读取 AS5600（地址 0x36），提供电机转子角度，同时兼作「旋钮」输入 |
| OLED | P5.4 / P5.5 | 软件 I2C 驱动 128×64 OLED（写地址 0x78） |
| 三相 PWM | P2.7 / P4.5 / P4.4 | PWM 通道 A / B / C，PWM 周期 300，用于 FOC 三相电压输出 |
| 仿真指示灯 | P1.3 | `CODE_SIMULATION` 置 1 时翻转，用于 Proteus 仿真中确认程序运行 |

## 二、工程目录结构

```
CourseDesign_SCM_Controller
├── Sources/            AiCube 生成的外设初始化与主函数（main.c 等）
│   ├── main.c          程序入口：SYS_Init() 初始化外设，主循环执行任务表
│   ├── port.c          各端口工作模式与初始电平配置
│   ├── timer.c         定时器 0~3 初始化与中断服务（系统 tick、FOC、IMU）
│   ├── uart.c          串口 1 初始化与收发中断
│   ├── exti.c          INT0 外部中断：更新蓝牙连接状态
│   ├── adc.c           ADC 初始化与单次转换
│   ├── spi.c           SPI 初始化与字节收发
│   └── inc/            外设头文件、寄存器定义（stc15w_def.h）、公共类型（def.h）
├── User/               系统层：system.c（初始化、串口收发、printf、SysTick）、task.c（时基任务表）
├── Communication/      与小车端的通信：communication.c（组帧/解析）、contract.h（协议定义）
├── Control/            控制层：根据摇杆、按键、欧拉角计算 vx / vy / vw / target_yaw
├── Joystick/           摇杆 ADC 采样任务
├── Key/                key_ud.c（左右按键电平采样）、key_SL.c（模式键长短按识别）
├── Encoder/            AS5600 磁编码器（软件 I2C）、EncoderKey.c（旋转分档模拟按键）
├── IMU/                MPU6500 SPI 驱动、四元数姿态解算
├── FOC/                FOC 电机控制
│   ├── FOC.c / FOC_Util.c   速度开环、角度闭环、逆 Park/Clark 变换与三相占空比输出
│   ├── FOC_Simulation.c     「棘轮」手感模拟与三组 PID 参数
│   ├── FOC_App.c            按当前页面调度 FOC 控制逻辑
│   └── Math/                PID（位置式 PID / PI / PD）与数学工具、查表三角函数
├── Display/            OLED 显示层
│   ├── OLED/            显示驱动与中英文字库（16×16、32×32 汉字）
│   └── Pages/           各页面实现（Main / Control / Music / Settings / About）
├── User_Driver/        外设封装：PWM、软件 I2C、SPI、串口 FIFO、IAP（EEPROM 模拟）
├── User_Lib/           通用库：数学工具、环形 FIFO、公共宏定义
├── Controller.uvproj   Keil uVision 工程（Controller_bk1/bk2.uvproj 为历史备份）
├── Controller.aic      STC AiCube 工程配置，用于重新生成外设初始化代码
└── LICENSE             MIT License
```

## 三、中断与时基任务调度

### 定时器分工

| 定时器 | 周期 | 工作内容 |
| --- | --- | --- |
| TIMER0 | 1 ms | 系统 tick 自增；每 5 ms 置任务执行标志并更新秒计数 |
| TIMER1 | 5 ms | `AS5600_Update()` 读取编码器角度 + `FOC_Task()` 执行电机控制（仿真模式下屏蔽） |
| TIMER2 | — | UART1 波特率发生器（115200 bps，1T 模式） |
| TIMER3 | 10 ms | `IMU_Update()` 读取 IMU 并解算姿态（与 `halfT_s` 采样周期一致） |

### 5 ms 时基任务表（`User/task.c`）

| 任务 | 周期 | 功能 |
| --- | --- | --- |
| `uart_recv_task` | 5 ms | 串口接收处理：帧头/帧尾对齐、组帧与解析 |
| `ADC_Task` | 50 ms | 摇杆双通道 ADC 采样 |
| `Key_UD_Task` | 20 ms | 左右按键电平采样 |
| `KeySL_Task` | 20 ms | 模式键短按 / 长按（400 ms）识别 |
| `EncoderKey_Update` | 20 ms | 编码器旋钮分档，越档时模拟左右按键 |
| `Comm_SendTask` | 60 ms | 向小车下发控制帧或命令帧 |
| `Display_Task` | 100 ms | OLED 页面刷新 |
| `simulation_led_task` | 200 ms | 仿真指示灯翻转 |

主循环在 `Sources/main.c` 中轮询任务标志，标志由定时器 0 中断每 5 ms 置位，任务表按各自的周期倍数计数执行。

## 四、通信协议

控制器与小车端通过 UART1（蓝牙）通信，帧格式为定长帧：

```
帧头 0xCC 0x33 | 命令字 | 数据区 | 帧尾 0x99 0x66
```

### 控制器 → 小车

| 命令字 | 值 | 帧长 | 数据区 |
| --- | --- | --- | --- |
| 摇杆模式 | 1 | 15 B | `vx`(float) + `vy`(float) + `vw`(float) |
| 重力遥控 | 2 | 15 B | `vx`(float) + `vy`(float) + `target_yaw`(float) |
| 自动巡航 | 3 | 3 B | 无 |
| 自动跟随 | 4 | 3 B | 无 |
| 音乐播放 | 5 | 4 B | 曲目序号（1~5） |
| 音乐暂停 / 停止 / 继续 | 6 / 7 / 8 | 3 B | 无 |
| 重力 PID Kp / Ki / Kd 增减 | 9 ~ 14 | 3 B | 无 |
| 跟随 PID Kp / Ki / Kd 增减 | 15 ~ 20 | 3 B | 无 |
| 编码器模式 | 21 | 15 B | `vx`(float) + `vy`(float) + `target_yaw`(float) |

### 小车 → 控制器

| 命令字 | 值 | 帧长 | 数据区 |
| --- | --- | --- | --- |
| 小车数据 | 51 | 53 B | 温度、湿度（各为 1 字节整数 + 1 字节小数）+ 前置/后置/左/右超声波测距（4×float）+ 重力 PID 与跟随 PID（6×float）+ 小车 Yaw（float） |

控制器持续统计解析失败的帧数，每 100 帧给出一次丢包率（百分比），并显示在控制页上。

## 五、控制模式

在控制页可切换以下 5 种模式，由 `Control/control.c` 统一换算为速度指令：

| 模式 | 名称 | 输入来源 |
| --- | --- | --- |
| 0 | 摇杆模式 JoyStick | 摇杆 ADC 决定 `vx` / `vy`；左右按键决定 `vw`（默认 30，可按 10~100 步进调整） |
| 1 | 编码器模式 Encoder | 摇杆决定 `vx` / `vy`；AS5600 角度决定 `target_yaw` |
| 2 | 重力遥控 Gravity | 横滚角决定 `vx`，俯仰角决定 `vy`，偏航角决定 `target_yaw` |
| 3 | 自动巡航 AutoCruise | 仅下发模式命令，由小车自主巡航 |
| 4 | 自动跟随 AutoFollow | 仅下发模式命令，由小车自主跟随 |

速度统一限幅（±100）并设 5 的死区；仅当处于控制页且处于「运行」状态时才输出速度，其它情况输出 0 以避免误动作。设置页的「角度置零」可把当前俯仰角 / 偏航角记为零点，消除安装偏差。

## 六、显示与按键交互

| 页面 | 内容与操作 |
| --- | --- |
| 主页 Main | 欢迎界面 + 蓝牙连接状态 + 秒计数；左右键切换 4 个功能入口，短按进入对应页面；主页短按还会触发电机电角度标定 |
| 控制页 Control | 显示链路状态、当前模式、旋转速度、编码器角度、小车 Yaw、丢包率、温湿度与四路超声波距离；短按在「运行 / 改模式 / 改 vw」间切换，左右键调整 |
| 音乐页 Music | 播放、暂停、继续、停止与曲目选择（1~5） |
| 设置页 Settings | 子菜单：角度置零（Reset Pitch / Reset Yaw）、重力 PID、跟随 PID；PID 参数通过命令字交给小车端修改 |
| 关于页 About | 显示作者；左键触发开环转动测试，右键触发角度闭环摆动测试 |

交互输入共三个来源：P0.0 / P0.3 左右按键、P0.6 模式键，以及 AS5600 旋钮——旋钮把 360° 均分为 6 档，跨档即模拟一次左 / 右按键（控制页与关于页除外，避免与调试操作冲突）。长按模式键可返回主页。

## 七、FOC 电机控制

- 供电 12 V，电机极对数 7，三相 PWM 周期 300，占空比按「电压 / 供电电压」换算后写入 PWM A/B/C。
- `setPhaseVoltage()` 完成逆 Park / 逆 Clark 变换并输出三相电压；`velocityOpenloop()` 为速度开环，`angleControl_loop()` 为角度闭环（位置式 PID + 低通滤波，抑制输出突变）。
- `Zero_Electric_Init()` 先在固定电角度下施加电压 1 s，再读取编码器角度作为电角度零点，用于对齐转子与电角度。
- 「棘轮」模拟：把转子角度分成 6 个档位区域，接近档位边界时叠加额外的 PID 参数，形成带档位感的手感；主页、控制页、关于页分别使用三组不同的 PID 参数（见 `FOC_Simulation.c`）。
- FOC 控制位于定时器 1 的 5 ms 中断中执行，页面上不执行耗时操作以保证时序。

## 八、代码仿真（Proteus）

`Sources/inc/config.h` 中的 `CODE_SIMULATION` 用于切换运行环境：

```c
#define CODE_SIMULATION   0   /* 下载到仿真的时候置 1，以适应 Proteus */
```

- 置 1 时，AS5600 / FOC / PWM / IMU 等依赖真实硬件外设的代码被屏蔽，任务表照常运行，并用 P1.3 翻转作为运行指示；
- 置 0 时为真实硬件运行。

## 九、编译与烧录

1. 用 Keil uVision（C51）打开 `Controller.uvproj`，目标器件为 STC15W4K32S4，内存模型 Large，xdata 0~0xEFF；
2. 编译后使用 STC-ISP 通过串口将固件下载到芯片；
3. 外设初始化代码（`main.c`、`port.c`、`timer.c`、`uart.c`、`exti.c`、`adc.c`、`spi.c`）由 STC AiCube 生成，配置保存在 `Controller.aic`。若需在 AiCube 中重新生成，请保留所有 `AICUBE_USER_*` 用户代码块，否则会覆盖已有逻辑；
4. 工程同样可用 VS Code + EIDE 构建（`.eide` 相关产物已在 `.gitignore` 中忽略）。

## 十、其它说明

- 通信协议常量集中在 `Communication/contract.h`，新增指令时需同步修改 `communication.c` 的组帧逻辑与小车端固件。
- 串口接收同时实现了「超时组帧」与「FIFO 组帧」两套方案，由 `User_Driver/user_uart_fifo.h` 中的 `UART_RECV_USE_FIFO` 选择，当前默认使用前者。
- `Display/Pages/Page_Example.c` 为新增页面的模板；新增页面需同步注册页面枚举并在 `Display/Display.c` 的分发函数中添加分支。
- `User_Driver/user_iap.c` 提供基于片内 Flash 的 EEPROM 模拟读写，注意使用地址不能与用户程序区重叠。

## License

本项目采用 MIT License，详见 [LICENSE](LICENSE)。
