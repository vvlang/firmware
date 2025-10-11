<div align="center" markdown="1">

<img src=".github/meshtastic_logo.png" alt="Meshtastic Logo" width="80"/>
<h1>Meshtastic 固件</h1>

![GitHub release downloads](https://img.shields.io/github/downloads/meshtastic/firmware/total)
[![CI](https://img.shields.io/github/actions/workflow/status/meshtastic/firmware/main_matrix.yml?branch=master&label=actions&logo=github&color=yellow)](https://github.com/meshtastic/firmware/actions/workflows/ci.yml)
[![CLA assistant](https://cla-assistant.io/readme/badge/meshtastic/firmware)](https://cla-assistant.io/meshtastic/firmware)
[![Fiscal Contributors](https://opencollective.com/meshtastic/tiers/badge.svg?label=Fiscal%20Contributors&color=deeppink)](https://opencollective.com/meshtastic/)
[![Vercel](https://img.shields.io/static/v1?label=Powered%20by&message=Vercel&style=flat&logo=vercel&color=000000)](https://vercel.com?utm_source=meshtastic&utm_campaign=oss)

<a href="https://trendshift.io/repositories/5524" target="_blank"><img src="https://trendshift.io/api/badge/repositories/5524" alt="meshtastic%2Ffirmware | Trendshift" style="width: 250px; height: 55px;" width="250" height="55"/></a>

</div>

<div align="center">
	<a href="https://meshtastic.org">官方网站</a>
	-
	<a href="https://meshtastic.org/docs/">文档</a>
</div>

## 项目概述

本仓库包含Meshtastic的官方设备固件，这是一个开源LoRa网状网络项目，专为长距离、低功耗通信而设计，无需依赖互联网或蜂窝基础设施。固件支持多种硬件平台，包括ESP32、nRF52、RP2040/RP2350和基于Linux的设备。

Meshtastic支持文本消息、位置共享和遥测数据通过去中心化网状网络传输，非常适合户外探险、应急准备和远程操作。

### 快速开始

- 🔧 **[编译说明](https://meshtastic.org/docs/development/firmware/build)** – 学习如何从源码编译固件
- ⚡ **[烧录说明](https://meshtastic.org/docs/getting-started/flashing-firmware/)** – 在设备上安装或更新固件
- 🎯 **[nRF52 ProMicro DIY多按钮功能](#nrf52-promicro-diy-多按钮功能)** – 查看新增的多按钮支持

加入我们的社区，帮助改进Meshtastic！🚀

## 项目统计

![Alt](https://repobeats.axiom.co/api/embed/8025e56c482ec63541593cc5bd322c19d5c0bdcf.svg "Repobeats analytics image")

## nRF52 ProMicro DIY 多按钮功能

### 功能特性

本项目为nRF52 ProMicro DIY开发板实现了完整的多按钮支持，包括：

- **5个独立按钮**：P1.00、P1.01、P1.02、P1.06、P1.07
- **短按功能**：导航控制（上下左右、确认选择）
- **长按功能**：系统功能（关机、GPS切换、adhoc ping、DFU模式）
- **深度睡眠唤醒**：所有按钮都支持从深度睡眠中唤醒设备
- **3秒长按时间**：防止误操作

### 按钮映射表

| 按钮 | 引脚 | 短按功能 | 长按功能 (3秒) | 双击功能 |
|------|------|----------|----------------|----------|
| P1.00 | P1.00 | 确认选择 | 关机 | 无 |
| P1.01 | P1.01 | 向上导航 | 切换GPS模式 | 无 |
| P1.02 | P1.02 | 向下导航 | 发送adhoc ping | 无 |
| P1.06 | P1.06 | 向左导航 | 刷机模式 (DFU) | 无 |
| P1.07 | P1.07 | 向右导航 | 无功能 | 无 |

### 编译nRF52 ProMicro DIY固件

```bash
# 编译nRF52 ProMicro DIY固件
pio run -e nrf52_promicro_diy_tcxo

# 生成的文件位置
# .pio/build/nrf52_promicro_diy_tcxo/firmware.uf2
# .pio/build/nrf52_promicro_diy_tcxo/firmware.hex
# .pio/build/nrf52_promicro_diy_tcxo/firmware.zip
```

### 内存使用情况

- **RAM使用**：31.6% (78,716 / 248,832 字节)
- **Flash使用**：96.1% (782,920 / 815,104 字节)

## 自动化编译方案

### GitHub Actions 自动编译

本项目配置了完整的GitHub Actions自动化编译流程，支持：

#### 1. 触发条件
- **推送代码**：每次推送到`develop`或`master`分支时自动编译
- **Pull Request**：创建PR时自动编译并测试
- **定时编译**：每日自动编译最新代码
- **手动触发**：可通过GitHub界面手动触发编译

#### 2. 支持的编译环境
- **nRF52 ProMicro DIY**：`nrf52_promicro_diy_tcxo`
- **ESP32系列**：T-Beam、Heltec、RAK等
- **RP2040系列**：Raspberry Pi Pico等
- **STM32系列**：RAK3172等

#### 3. 编译产物
每次编译成功后会自动生成：
- **UF2文件**：用于USB烧录
- **HEX文件**：用于传统烧录工具
- **ZIP文件**：包含所有编译产物
- **固件信息**：版本号、编译时间、Git提交信息

#### 4. 自动发布
- **Release版本**：自动创建GitHub Release
- **固件下载**：提供直接下载链接
- **版本管理**：自动标记版本号

### 本地编译环境设置

#### 1. 安装依赖

```bash
# 安装PlatformIO
pip install platformio

# 安装Arduino CLI（可选）
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

# 安装nRF52工具链
pip install nrfutil
```

#### 2. 编译命令

```bash
# 编译所有支持的设备
pio run

# 编译特定设备
pio run -e nrf52_promicro_diy_tcxo
pio run -e tbeam
pio run -e heltec_v2

# 清理编译缓存
pio run --target clean

# 上传固件到设备
pio run --target upload
```

#### 3. 开发环境配置

```bash
# 克隆仓库
git clone https://github.com/vvlang/firmware.git
cd firmware

# 安装依赖
pio lib install

# 编译测试
pio run -e nrf52_promicro_diy_tcxo
```

### 持续集成配置

#### 1. GitHub Actions工作流

项目包含以下自动化工作流：

- **`main_matrix.yml`**：主要编译矩阵，支持所有设备
- **`build_firmware.yml`**：固件编译工作流
- **`test_native.yml`**：原生平台测试
- **`package_ppa.yml`**：Ubuntu PPA包构建
- **`release_channels.yml`**：发布渠道管理

#### 2. 编译矩阵

```yaml
# 支持的编译环境
strategy:
  matrix:
    include:
      - device: nrf52_promicro_diy_tcxo
        platform: nRF52
        board: promicro-nrf52840
      - device: tbeam
        platform: ESP32
        board: tbeam
      - device: heltec_v2
        platform: ESP32
        board: heltec_wireless_tracker
```

#### 3. 自动测试

- **代码质量检查**：使用Trunk进行代码格式化
- **安全扫描**：使用Semgrep进行安全漏洞检测
- **依赖检查**：自动更新依赖包
- **文档生成**：自动生成API文档

### 部署和发布

#### 1. 自动部署流程

1. **代码推送** → 触发GitHub Actions
2. **编译测试** → 多平台并行编译
3. **质量检查** → 代码格式化和安全检查
4. **产物生成** → 生成UF2、HEX、ZIP文件
5. **自动发布** → 创建GitHub Release
6. **通知发送** → 发送编译结果通知

#### 2. 发布渠道

- **GitHub Releases**：主要发布渠道
- **GitHub Packages**：容器镜像存储
- **Ubuntu PPA**：Linux包管理
- **Docker Hub**：容器镜像分发

#### 3. 版本管理

- **语义化版本**：遵循SemVer规范
- **自动标签**：基于Git标签创建版本
- **变更日志**：自动生成CHANGELOG
- **发布说明**：自动生成Release Notes

### 监控和通知

#### 1. 编译状态监控

- **GitHub Actions**：实时编译状态
- **Badge徽章**：显示最新编译状态
- **邮件通知**：编译失败时发送邮件
- **Slack集成**：团队协作通知

#### 2. 性能监控

- **编译时间**：跟踪编译性能
- **成功率**：监控编译成功率
- **资源使用**：监控CPU和内存使用
- **缓存优化**：优化编译缓存策略

### 故障排除

#### 1. 常见编译问题

```bash
# 清理编译缓存
pio run --target clean

# 重新安装依赖
pio lib install --force

# 检查环境配置
pio check

# 查看详细编译日志
pio run -v
```

#### 2. 环境问题

```bash
# 检查PlatformIO版本
pio --version

# 更新PlatformIO
pip install --upgrade platformio

# 检查工具链
pio platform show
```

#### 3. 依赖问题

```bash
# 清理依赖缓存
pio lib uninstall --all
pio lib install

# 检查依赖冲突
pio lib deps
```

## 贡献指南

### 开发流程

1. **Fork仓库**：创建自己的分支
2. **开发功能**：实现新功能或修复bug
3. **测试验证**：确保代码质量
4. **提交PR**：创建Pull Request
5. **代码审查**：等待代码审查
6. **合并代码**：通过审查后合并

### 代码规范

- **代码格式**：使用Trunk自动格式化
- **提交信息**：遵循Conventional Commits规范
- **测试覆盖**：确保新功能有测试覆盖
- **文档更新**：更新相关文档

### 问题报告

- **Bug报告**：使用GitHub Issues
- **功能请求**：使用Feature Request模板
- **安全漏洞**：使用Security Advisory
- **讨论交流**：使用GitHub Discussions

## 许可证

本项目采用Apache 2.0许可证，详见[LICENSE](LICENSE)文件。

## 社区支持

- **官方网站**：https://meshtastic.org
- **文档中心**：https://meshtastic.org/docs/
- **社区论坛**：https://meshtastic.org/discord
- **GitHub讨论**：https://github.com/meshtastic/firmware/discussions

---

**注意**：本实现专为nRF52 ProMicro DIY开发板设计，其他开发板可能需要不同的配置。更多详细信息请参考[中文说明文档](nRF52_ProMicro_DIY_Button_Implementation_CN.md)。