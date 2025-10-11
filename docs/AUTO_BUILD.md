# 自动化编译配置说明

## 概述

本项目配置了完整的GitHub Actions自动化编译流程，支持多种触发方式和编译策略。

## 工作流配置

### 1. nRF52 ProMicro DIY 专用编译

**文件**: `.github/workflows/auto-build-nrf52-promicro.yml`

**触发条件**:
- 推送到 `develop` 或 `master` 分支
- 修改相关文件时自动触发
- 手动触发（支持参数配置）

**支持设备**:
- `nrf52_promicro_diy_tcxo` - nRF52 ProMicro DIY with TCXO
- `nrf52_promicro_diy_xtal` - nRF52 ProMicro DIY with XTAL

**编译产物**:
- `firmware.uf2` - USB烧录文件
- `firmware.hex` - 传统烧录工具使用的HEX文件
- `firmware.zip` - 包含所有编译产物的压缩包
- `firmware_info.txt` - 固件信息文件
- `README.md` - 使用说明文档

### 2. 全设备编译

**文件**: `.github/workflows/auto-build-all-devices.yml`

**触发条件**:
- 每日定时编译（UTC 2:00）
- 手动触发（支持设备选择和编译类型）

**支持设备分类**:
- **nRF52**: nrf52_promicro_diy_tcxo, nrf52_promicro_diy_xtal, heltec_mesh_pocket
- **ESP32**: tbeam, heltec_v2, tbeam-s3-core
- **RP2040**: rpipico, rpipicow

**编译类型**:
- `all` - 编译所有设备
- `nrf52` - 仅编译nRF52设备
- `esp32` - 仅编译ESP32设备
- `rp2040` - 仅编译RP2040设备
- `stm32` - 仅编译STM32设备

### 3. 编译状态监控

**文件**: `.github/workflows/build-status.yml`

**功能**:
- 监控编译工作流状态
- 发送编译结果通知
- 记录编译历史

## 使用方法

### 1. 自动触发

#### 推送触发
```bash
# 推送到develop分支会自动编译nRF52 ProMicro DIY固件
git push origin develop

# 推送到master分支会触发全设备编译
git push origin master
```

#### 定时触发
- 每日UTC 2:00自动编译所有设备
- 无需手动操作

### 2. 手动触发

#### 通过GitHub界面
1. 进入Actions页面
2. 选择对应的工作流
3. 点击"Run workflow"
4. 配置参数后执行

#### 通过GitHub CLI
```bash
# 编译nRF52 ProMicro DIY固件
gh workflow run "自动编译 nRF52 ProMicro DIY 固件" \
  --field build_type=nrf52_promicro_diy_tcxo \
  --field release_build=false

# 编译所有设备
gh workflow run "自动编译所有设备固件" \
  --field devices=nrf52_promicro_diy_tcxo,tbeam,heltec_v2 \
  --field build_type=all \
  --field release_build=false
```

### 3. 参数配置

#### nRF52 ProMicro DIY 编译参数
- `build_type`: 编译类型
  - `nrf52_promicro_diy_tcxo` - TCXO版本
  - `nrf52_promicro_diy_xtal` - XTAL版本
- `release_build`: 是否为发布版本
  - `true` - 创建GitHub Release
  - `false` - 仅生成编译产物

#### 全设备编译参数
- `devices`: 要编译的设备列表（逗号分隔）
- `build_type`: 编译类型
  - `all` - 所有设备
  - `nrf52` - nRF52设备
  - `esp32` - ESP32设备
  - `rp2040` - RP2040设备
  - `stm32` - STM32设备
- `release_build`: 是否为发布版本

## 编译产物

### 1. 文件类型

#### UF2文件
- **用途**: USB烧录，支持拖拽操作
- **适用设备**: nRF52, RP2040
- **使用方法**: 直接拖拽到设备存储

#### HEX文件
- **用途**: 传统烧录工具
- **适用设备**: nRF52, STM32
- **使用方法**: 使用专用烧录工具

#### BIN文件
- **用途**: 二进制固件
- **适用设备**: ESP32, STM32
- **使用方法**: 使用专用烧录工具

#### ZIP文件
- **用途**: 包含所有编译产物
- **适用设备**: 所有设备
- **使用方法**: 解压后选择对应文件

### 2. 信息文件

#### firmware_info.txt
包含固件详细信息：
- 设备型号和描述
- 固件版本和编译时间
- Git提交信息
- 文件大小信息
- 使用说明

#### README.md
包含使用说明：
- 固件信息
- 多按钮功能说明
- 烧录方法
- 文件说明

## 监控和通知

### 1. 编译状态监控

#### GitHub Actions状态
- 实时显示编译状态
- 支持状态徽章
- 历史记录查看

#### 通知方式
- GitHub通知
- 邮件通知（配置后）
- Slack集成（配置后）

### 2. 编译结果

#### 成功情况
- 生成所有编译产物
- 创建发布包
- 上传到GitHub Actions Artifacts
- 发送成功通知

#### 失败情况
- 记录错误信息
- 发送失败通知
- 提供调试信息

## 故障排除

### 1. 常见问题

#### 编译失败
```bash
# 检查编译日志
gh run view --log

# 重新触发编译
gh workflow run "自动编译 nRF52 ProMicro DIY 固件"
```

#### 依赖问题
```bash
# 检查依赖状态
pio lib deps

# 更新依赖
pio lib install --force
```

#### 环境问题
```bash
# 检查PlatformIO版本
pio --version

# 更新PlatformIO
pip install --upgrade platformio
```

### 2. 调试方法

#### 查看详细日志
```bash
# 查看工作流运行日志
gh run view --log

# 查看特定步骤日志
gh run view --log --step="编译固件"
```

#### 本地测试
```bash
# 本地编译测试
pio run -e nrf52_promicro_diy_tcxo -v

# 检查编译产物
ls -la .pio/build/nrf52_promicro_diy_tcxo/
```

## 最佳实践

### 1. 开发流程

1. **功能开发**: 在feature分支开发
2. **本地测试**: 确保本地编译成功
3. **代码提交**: 推送到develop分支
4. **自动编译**: 触发自动编译流程
5. **结果检查**: 检查编译产物
6. **合并代码**: 合并到master分支

### 2. 版本管理

#### 语义化版本
- 主版本号：重大功能更新
- 次版本号：新功能添加
- 修订号：bug修复

#### 标签管理
```bash
# 创建版本标签
git tag -a v1.0.0 -m "nRF52 ProMicro DIY多按钮功能v1.0.0"
git push origin v1.0.0

# 查看标签
git tag -l
```

### 3. 发布管理

#### 自动发布
- 配置`release_build=true`时自动创建Release
- 包含所有编译产物
- 自动生成Release Notes

#### 手动发布
```bash
# 创建Release
gh release create v1.0.0 \
  --title "nRF52 ProMicro DIY多按钮功能v1.0.0" \
  --notes "包含完整的多按钮支持功能" \
  release/nrf52_promicro_diy_tcxo/*
```

## 扩展配置

### 1. 添加新设备

#### 修改编译矩阵
```yaml
# 在.github/workflows/auto-build-all-devices.yml中添加
- device: new_device
  platform: ESP32
  description: "New Device Description"
  category: esp32
```

#### 更新设备列表
```yaml
# 在README.md中更新支持的设备列表
# 在docs/AUTO_BUILD.md中更新设备说明
```

### 2. 自定义编译参数

#### 环境变量
```yaml
env:
  CUSTOM_BUILD_FLAGS: "-DCUSTOM_FEATURE=1"
  BUILD_OPTIMIZATION: "-Os"
```

#### 编译选项
```yaml
# 在platformio.ini中配置
[env:custom_device]
build_flags = ${common.build_flags}
  -DCUSTOM_FEATURE=1
  -DBUILD_OPTIMIZATION=-Os
```

### 3. 集成外部服务

#### Slack通知
```yaml
- name: 发送Slack通知
  uses: 8398a7/action-slack@v3
  with:
    status: ${{ job.status }}
    channel: '#firmware-builds'
    webhook_url: ${{ secrets.SLACK_WEBHOOK }}
```

#### 邮件通知
```yaml
- name: 发送邮件通知
  uses: dawidd6/action-send-mail@v3
  with:
    server_address: smtp.gmail.com
    server_port: 587
    username: ${{ secrets.EMAIL_USERNAME }}
    password: ${{ secrets.EMAIL_PASSWORD }}
    subject: "固件编译结果: ${{ matrix.device }}"
    body: "编译状态: ${{ job.status }}"
```

## 总结

本自动化编译系统提供了完整的固件编译、测试、发布流程，支持多种触发方式和编译策略。通过合理配置和使用，可以大大提高开发效率和代码质量。

更多详细信息请参考：
- [GitHub Actions文档](https://docs.github.com/en/actions)
- [PlatformIO文档](https://docs.platformio.org/)
- [Meshtastic文档](https://meshtastic.org/docs/)
