# nRF52 ProMicro DIY 多按钮功能实现

## 概述

本文档详细说明了为nRF52 ProMicro DIY开发板实现的多按钮功能。该实现支持5个独立按钮，每个按钮都有短按和长按功能，完全集成到Meshtastic固件系统中。

## 硬件配置

### 按钮引脚映射

| 按钮 | 引脚 | 短按功能 | 长按功能 (3秒) | 双击功能 |
|------|------|----------|----------------|----------|
| P1.00 | P1.00 | 确认选择 | 关机 | 无 |
| P1.01 | P1.01 | 向上导航 | 切换GPS模式 | 无 |
| P1.02 | P1.02 | 向下导航 | 发送adhoc ping | 无 |
| P1.06 | P1.06 | 向左导航 | 刷机模式 (DFU) | 无 |
| P1.07 | P1.07 | 向右导航 | 无功能 | 无 |

### 硬件连接

所有按钮都连接到nRF52的P1端口，使用内部上拉电阻，低电平有效触发。

## 软件实现

### 核心文件

1. **`src/input/MultiButtonThread.h`** - 多按钮线程头文件
2. **`src/input/MultiButtonThread.cpp`** - 多按钮线程实现
3. **`variants/nrf52840/diy/nrf52_promicro_diy_tcxo/variant.h`** - 引脚定义
4. **`src/main.cpp`** - 主程序中的按钮初始化
5. **`src/platform/nrf52/main-nrf52.cpp`** - nRF52平台特定配置

### 技术特性

#### 1. 多按钮支持
- 5个独立按钮线程，每个按钮都有自己的配置
- 基于现有的`ButtonThread`类，确保兼容性
- 支持不同的按钮事件映射

#### 2. 事件处理
- **短按事件**：立即响应，用于导航和选择
- **长按事件**：3秒长按，用于系统功能
- **深度睡眠唤醒**：所有按钮都支持从深度睡眠中唤醒设备

#### 3. 系统集成
- 完全集成到Meshtastic的`InputBroker`系统
- 支持现有的输入事件类型
- 与系统命令模块无缝集成

### 功能详解

#### 导航功能
- **向上导航** (P1.01短按)：`INPUT_BROKER_UP`
- **向下导航** (P1.02短按)：`INPUT_BROKER_DOWN`
- **向左导航** (P1.06短按)：`INPUT_BROKER_LEFT`
- **向右导航** (P1.07短按)：`INPUT_BROKER_RIGHT`
- **确认选择** (P1.00短按)：`INPUT_BROKER_SELECT`

#### 系统功能
- **关机** (P1.00长按3秒)：`INPUT_BROKER_SHUTDOWN`
- **GPS模式切换** (P1.01长按3秒)：`INPUT_BROKER_GPS_TOGGLE`
- **发送adhoc ping** (P1.02长按3秒)：`INPUT_BROKER_SEND_PING`
- **DFU模式** (P1.06长按3秒)：`INPUT_BROKER_DFU_MODE`

#### DFU模式实现
DFU模式支持两种方式：
- **UF2 DFU**：设置`NRF_POWER->GPREGRET = 0xB1`后重启
- **Serial DFU**：设置`NRF_POWER->GPREGRET = 0xB2`后重启

### 深度睡眠支持

所有按钮都配置为可以从深度睡眠中唤醒设备：

```cpp
// 配置按钮唤醒
nrf_gpio_cfg_input(BUTTON_PIN, NRF_GPIO_PIN_PULLUP);
nrf_gpio_cfg_sense_set(BUTTON_PIN, NRF_GPIO_PIN_SENSE_LOW);
```

## 编译和烧录

### 编译命令
```bash
pio run -e nrf52_promicro_diy_tcxo
```

### 生成的文件
- **固件文件**：`.pio/build/nrf52_promicro_diy_tcxo/firmware.hex`
- **UF2文件**：`.pio/build/nrf52_promicro_diy_tcxo/firmware.uf2`
- **ZIP文件**：`.pio/build/nrf52_promicro_diy_tcxo/firmware.zip`

### 内存使用情况
- **RAM使用**：31.6% (78,716 / 248,832 字节)
- **Flash使用**：96.1% (782,920 / 815,104 字节)

## 使用方法

### 基本操作
1. **短按**：快速按下并释放按钮，用于导航和选择
2. **长按**：按住按钮3秒后释放，用于系统功能
3. **唤醒**：从深度睡眠状态按下任意按钮即可唤醒设备

### 功能测试
1. **导航测试**：使用P1.01、P1.02、P1.06、P1.07进行菜单导航
2. **确认测试**：使用P1.00确认选择
3. **系统功能测试**：
   - P1.00长按：测试关机功能
   - P1.01长按：测试GPS模式切换
   - P1.02长按：测试adhoc ping发送
   - P1.06长按：测试DFU模式进入

## 故障排除

### 常见问题

1. **按钮无响应**
   - 检查硬件连接
   - 确认引脚配置正确
   - 验证上拉电阻设置

2. **长按功能不工作**
   - 确认长按时间设置为3000ms
   - 检查按钮事件处理逻辑

3. **DFU模式无法进入**
   - 确认`enterDfuMode()`函数正确实现
   - 检查GPREGRET寄存器设置

### 调试方法

1. **串口输出**：通过串口监控按钮事件
2. **LED指示**：使用LED指示按钮状态
3. **日志记录**：启用详细日志记录

## 技术细节

### 中断处理
每个按钮都配置了中断处理程序，确保快速响应：

```cpp
mainConfig.intRoutine = []() {
    MainButtonThread->userButton.tick();
    MainButtonThread->setIntervalFromNow(0);
    runASAP = true;
    BaseType_t higherWake = 0;
    mainDelay.interruptFromISR(&higherWake);
};
```

### 事件分发
按钮事件通过`InputBroker`系统分发到相应的处理模块：

```cpp
InputEvent evt;
evt.source = _originName;
evt.inputEvent = _singlePress;
notifyObservers(&evt);
```

## 扩展功能

### 添加新按钮
1. 在`variant.h`中定义新引脚
2. 在`main.cpp`中创建新的按钮线程
3. 配置相应的输入事件

### 自定义功能
1. 在`InputBroker.h`中添加新的事件类型
2. 在相应的模块中处理新事件
3. 更新按钮配置

## 版本信息

- **固件版本**：2.7.12.fe2e2753
- **实现日期**：2024年
- **兼容性**：nRF52 ProMicro DIY with TCXO
- **依赖**：Meshtastic固件框架

## 贡献

如果您发现任何问题或有改进建议，请：
1. 提交Issue描述问题
2. 提交Pull Request提供修复
3. 更新文档说明

## 许可证

本实现遵循Meshtastic项目的开源许可证。

---

**注意**：本实现专为nRF52 ProMicro DIY开发板设计，其他开发板可能需要不同的配置。
