# 中文字体使用指南

## 概述

本指南介绍如何使用OLED_PL模式的中文字符集，该字符集包含完整的ASCII字符（32-126）和GB2312中文字符，实现了英文字体的超集结构。

## 特性

- ✅ **完整ASCII支持** - 包含字符32-126（英文字母、数字、标点符号）
- ✅ **GB2312中文支持** - 包含3755个常用中文字符
- ✅ **OLED_PL模式兼容** - 符合OLED_PL超集设计模式
- ✅ **条件编译支持** - 通过`OLED_CN=1`启用
- ✅ **多尺寸支持** - 12pt、16pt、24pt字体

## 文件结构

```
src/graphics/fonts/
├── ChineseOLEDFonts.h          # 中文字体头文件
├── ChineseOLEDFonts.cpp        # 中文字体实现
├── ASCIIFontData.h             # ASCII字符数据
└── font_data.c                 # GB2312中文字符数据
```

## 使用方法

### 1. 启用中文字体

在编译时添加条件编译宏：

```ini
# platformio.ini
build_flags = 
    -D OLED_CN=1
```

### 2. 基本使用

```cpp
#include "graphics/fonts/ChineseOLEDFonts.h"

#ifdef OLED_CN
    // 获取字体
    const uint8_t* font12 = getChineseFont12();
    const uint8_t* font16 = getChineseFont16();
    const uint8_t* font24 = getChineseFont24();
    
    // 检查字符类型
    if (isASCIIChar('A')) {
        // 处理ASCII字符
    }
    
    if (isChineseChar("你")) {
        // 处理中文字符
    }
    
    // 计算字符串宽度
    uint16_t width = getUTF8StringWidth(font12, "Hello 你好");
#endif
```

### 3. 字符查找

```cpp
// 查找ASCII字符数据
uint8_t* asciiData = findCharData(font, 'A');

// 查找中文字符数据
uint8_t* chineseData = findChineseCharData(font, "你");
```

## 字体配置

### ScreenFonts.h 配置

中文字体已集成到 `ScreenFonts.h` 中：

```cpp
#ifdef OLED_CN
#define FONT_SMALL_LOCAL ChineseFont_12
#define FONT_MEDIUM_LOCAL ChineseFont_16  
#define FONT_LARGE_LOCAL ChineseFont_24
#endif
```

### 编译配置

在 `platformio.ini` 中添加：

```ini
[env:your_environment]
build_flags = 
    -D OLED_CN=1
    # 其他编译标志...
```

## 字符编码

### ASCII字符 (32-126

- 英文字母：A-Z, a-z
- 数字：0-9  
- 标点符号：!@#$%^&*()等

### 中文字符 (GB2312)

- 常用汉字：3755个
- UTF-8编码：3字节
- 字体大小：12x12像素

## 性能优化

### 字符查找优化

```cpp
// 快速ASCII字符检查
if (ch >= 32 && ch <= 126) {
    // 直接ASCII处理
}

// 中文字符检查
if ((unsigned char)utf8Char[0] >= 0xE4 && 
    (unsigned char)utf8Char[0] <= 0xE9) {
    // 中文字符处理
}
```

### 内存使用

- ASCII字符：95个 × 18字节 = 1,710字节
- 中文字符：3,755个 × 18字节 = 67,590字节
- 总计：约69KB字体数据

## 示例代码

### 基本显示

```cpp
void displayText(const char* text) {
    const uint8_t* font = getChineseFont12();
    uint16_t width = getUTF8StringWidth(font, text);
    
    // 在OLED上显示文本
    display.drawUTF8(0, 0, text);
}
```

### 混合文本处理

```cpp
void processMixedText(const char* text) {
    const char* ptr = text;
    
    while (*ptr) {
        if (isASCIIChar(*ptr)) {
            // 处理ASCII字符
            processASCIIChar(*ptr);
            ptr++;
        } else if (isChineseChar(ptr)) {
            // 处理中文字符
            processChineseChar(ptr);
            // 跳过UTF-8多字节
            while ((*ptr & 0xC0) == 0x80) ptr++;
            ptr++;
        } else {
            ptr++; // 跳过未知字符
        }
    }
}
```

## 故障排除

### 编译错误

1. **未定义OLED_CN**：确保在编译标志中添加 `-D OLED_CN=1`
2. **字体数据缺失**：检查 `ASCIIFontData.h` 和 `font_data.c` 是否存在
3. **链接错误**：确保所有字体文件都被编译

### 运行时问题

1. **中文字符不显示**：检查UTF-8编码是否正确
2. **字符宽度计算错误**：验证字符类型检查逻辑
3. **内存不足**：考虑使用较小的字体或减少字符集

## 扩展功能

### 添加新字符

1. 修改 `font_data.c` 添加新字符数据
2. 更新字符映射表
3. 重新编译字体数据

### 自定义字体大小

1. 修改 `CHINESE_FONT_WIDTH` 和 `CHINESE_FONT_HEIGHT`
2. 重新生成ASCII字体数据
3. 更新字体结构定义

## 版本历史

- **v1.0.0** - 初始版本，支持ASCII和中文字符
- **v1.1.0** - 添加多尺寸字体支持
- **v1.2.0** - 优化字符查找性能

## 许可证

本字体系统遵循项目许可证，字体数据来源于开源字体。


