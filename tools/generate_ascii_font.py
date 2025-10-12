#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
生成12x12像素ASCII字符字体数据
用于OLED_PL模式的中文字符集
"""

from PIL import Image, ImageDraw, ImageFont
import os

def generate_ascii_font_data():
    """生成ASCII字符32-126的字体数据"""
    
    # 字体配置
    font_size = 12
    char_width = 12
    char_height = 12
    
    # 尝试使用系统字体
    font_paths = [
        "/System/Library/Fonts/Arial.ttf",  # macOS
        "/System/Library/Fonts/Helvetica.ttc",  # macOS
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",  # Linux
        "C:/Windows/Fonts/arial.ttf",  # Windows
    ]
    
    font = None
    for font_path in font_paths:
        if os.path.exists(font_path):
            try:
                font = ImageFont.truetype(font_path, font_size)
                print(f"使用字体: {font_path}")
                break
            except:
                continue
    
    if font is None:
        # 使用默认字体
        font = ImageFont.load_default()
        print("使用默认字体")
    
    # 生成字符数据
    ascii_data = []
    
    for char_code in range(32, 127):  # ASCII 32-126
        char = chr(char_code)
        
        # 创建图像
        img = Image.new('1', (char_width, char_height), 0)  # 黑色背景
        draw = ImageDraw.Draw(img)
        
        # 绘制字符
        try:
            # 获取字符边界框
            bbox = draw.textbbox((0, 0), char, font=font)
            text_width = bbox[2] - bbox[0]
            text_height = bbox[3] - bbox[1]
            
            # 计算居中位置
            x = (char_width - text_width) // 2
            y = (char_height - text_height) // 2
            
            # 绘制字符
            draw.text((x, y), char, font=font, fill=1)  # 白色字符
            
        except Exception as e:
            print(f"绘制字符 '{char}' 失败: {e}")
            # 绘制一个点作为占位符
            draw.point((char_width//2, char_height//2), fill=1)
        
        # 转换为字节数组
        char_bytes = []
        for y in range(char_height):
            byte = 0
            for x in range(char_width):
                pixel = img.getpixel((x, y))
                if pixel:
                    byte |= (1 << (7 - (x % 8)))
            char_bytes.append(byte)
        
        ascii_data.extend(char_bytes)
    
    return ascii_data

def generate_c_header(ascii_data):
    """生成C头文件"""
    
    header = """// 自动生成的ASCII字体数据
// 字符范围: 32-126 (95个字符)
// 字体大小: 12x12像素
// 数据格式: 每字符18字节 (12x12/8 = 18字节)

const uint8_t ASCII_FONT_DATA[] PROGMEM = {
"""
    
    # 添加数据
    for i, byte in enumerate(ascii_data):
        if i % 18 == 0:
            header += f"    // 字符 {chr(32 + i//18)} (ASCII {32 + i//18})\n"
        header += f"    0x{byte:02X},"
        if (i + 1) % 18 == 0:
            header += "\n"
        elif (i + 1) % 6 == 0:
            header += "\n"
    
    header += "};\n\n"
    header += f"#define ASCII_FONT_SIZE {len(ascii_data)}\n"
    header += f"#define ASCII_CHAR_COUNT {len(ascii_data) // 18}\n"
    
    return header

if __name__ == "__main__":
    print("🔤 生成ASCII字体数据...")
    
    # 生成字体数据
    ascii_data = generate_ascii_font_data()
    
    # 生成C头文件
    header_content = generate_c_header(ascii_data)
    
    # 保存到文件
    output_file = "/Users/vvlang/Library/CloudStorage/SynologyDrive-soft/mesh/firmware/src/graphics/fonts/ASCIIFontData.h"
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(header_content)
    
    print(f"✅ ASCII字体数据已生成")
    print(f"📁 保存到: {output_file}")
    print(f"📊 数据大小: {len(ascii_data)} 字节")
    print(f"🔢 字符数量: {len(ascii_data) // 18} 个")


