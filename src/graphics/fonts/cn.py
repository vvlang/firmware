import re
import math
import numpy as np
import matplotlib.pyplot as plt

# 清空输出文件
with open('OLEDDisplayFontsCN.h', 'w') as f:
    f.write('#ifdef OLED_CN\n')
with open('OLEDDisplayFontsCN.cpp', 'w') as f:
    f.write('#include "OLEDDisplayFontsCN.h"\n\n')

# Function to extract bits from bytes (MSB first)
def get_bits(data):
    bits = []
    for byte in data:
        for i in range(7, -1, -1):  # MSB first (bit7 = leftmost/top)
            bits.append(1 if (byte & (1 << i)) else 0)
    return bits

# Convert row-major MSB-first to column-major LSB-top for OLEDDisplay
def convert_to_oled_format(binary, w=12, h=12):
    if isinstance(binary, np.ndarray):
        grid = binary
    else:
        bits = get_bits(binary)
        grid = [bits[row * w:(row + 1) * w] for row in range(h)]
    columns = []
    bytes_per_col = (h + 7) // 8
    for col in range(w):
        if isinstance(grid, np.ndarray):
            col_bits = grid[:, col]
        else:
            col_bits = [grid[row][col] for row in range(h)]
        for b in range(bytes_per_col):
            byte = 0
            for bit in range(8):
                y = b * 8 + bit
                if y < h and col_bits[y]:
                    byte |= (1 << bit)  # LSB = top pixel
            columns.append(byte)
    return columns

# Generate bitmap for English characters using Matplotlib
def get_char_bitmap(char):
    fig = plt.figure(figsize=(0.5, 0.5), dpi=100)
    text = fig.text(0, 1, char, va='top', ha='left', fontsize=8, fontfamily='sans-serif')
    fig.canvas.draw()
    renderer = fig.canvas.renderer
    bbox = text.get_window_extent(renderer)
    w = int(bbox.width)
    h = int(bbox.height)
    fig_h = int(fig.bbox.height)
    left = int(bbox.x0)
    right = int(bbox.x1)
    top_px = fig_h - int(bbox.y1)
    bottom_px = fig_h - int(bbox.y0)
    a = np.array(fig.canvas.renderer.buffer_rgba())[top_px:bottom_px, left:right, 0]
    binary = (a < 200).astype(int)
    h = binary.shape[0]
    fp = text.get_fontproperties()
    advance = int(np.ceil(renderer.get_text_width_height_descent(char, fp, False)[0]))
    if np.sum(binary) == 0:
        w = 0
    if h < 12:
        pad = 12 - h
        binary = np.pad(binary, ((pad, 0), (0, 0)), mode='constant')
    elif h > 12:
        binary = binary[h-12:, :]
    h = 12
    plt.close(fig)
    return binary, w, advance

# Generate font files (.h and .cpp)
def generate_font_files(font_name, first_char, charset, glyph_bitmaps, glyph_widths, glyph_advances, nominal_width=12, height=12, output_h='OLEDDisplayFontsCN.h', output_cpp='OLEDDisplayFontsCN.cpp'):
    num_chars = len(glyph_bitmaps)
    offsets = [0]
    current_offset = 0
    for bitmap in glyph_bitmaps[:-1]:
        current_offset += len(bitmap)
        offsets.append(current_offset)
    # 确保所有数值在uint8_t范围内
    header = [nominal_width, height, (first_char >> 8) & 0xFF, first_char & 0xFF, (num_chars >> 8) & 0xFF, num_chars & 0xFF]
    jump_table = []
    for i in range(num_chars):
        offset = offsets[i]
        w = glyph_widths[i]
        adv = glyph_advances[i]
        if w == 0:
            jump_table.extend([0xFF, 0xFF, 0x00, adv])
        else:
            # 确保offset在uint8_t范围内
            offset_high = (offset >> 8) & 0xFF
            offset_low = offset & 0xFF
            jump_table.extend([offset_high, offset_low, w, adv])
    bitmap_data = []
    for bitmap in glyph_bitmaps:
        bitmap_data.extend(bitmap)
    # Append to .h
    with open(output_h, 'a') as f:
        f.write(f'extern const uint8_t {font_name}[] PROGMEM;\n')
    # Append to .cpp
    with open(output_cpp, 'a') as f:
        f.write(f'const uint8_t {font_name}[] PROGMEM = {{\n')
        f.write('    ' + ', '.join(f'0x{b:02X}' for b in header) + ',  // Width, Height, First Char high, low, Num Chars high, low\n')
        f.write('    // Jump Table:\n')
        for i in range(num_chars):
            chunk = jump_table[i*4:i*4+4]
            char_code = first_char + i
            char_str = charset[i] if i < len(charset) else ''
            f.write('    ' + ', '.join(f'0x{b:02X}' for b in chunk) + f',  // 0x{char_code:04X} "{char_str}"\n')
        f.write('    // Bitmap Data:\n')
        for i in range(0, len(bitmap_data), 16):
            chunk = bitmap_data[i:i+16]
            f.write('    ' + ', '.join(f'0x{b:02X}' for b in chunk) + ',\n')
        f.write('};\n')

# Parse Chinese font_data.c
def parse_font_data():
    try:
        with open('font_data.c', 'r', encoding='utf-8') as f:
            content = f.read()
    except FileNotFoundError:
        print("Error: font_data.c not found in current directory")
        exit(1)
    charset_match = re.search(r'const char charset\[\] = \"(.*?)\";', content, re.DOTALL)
    charset = charset_match.group(1) if charset_match else ''
    fonts_match = re.search(r'const uint8_t fonts\[\] = \{(.*?)\};', content, re.DOTALL)
    fonts_str = fonts_match.group(1) if fonts_match else ''
    fonts = [int(hex_val, 16) for hex_val in re.findall(r'0x[0-9A-Fa-f]{2}', fonts_str)]
    return charset, fonts

# Extract English from PL font
def extract_en_from_pl(font_name_pl, font_name_en):
    try:
        with open('OLEDDisplayFontsPL.cpp', 'r') as f:
            content = f.read()
    except FileNotFoundError:
        print(f"Error: OLEDDisplayFontsPL.cpp not found for {font_name_pl}")
        return
    match = re.search(r'const uint8_t ' + font_name_pl + r'\[\] PROGMEM = \{(.*?)\};', content, re.DOTALL)
    if not match:
        print(f'No match for {font_name_pl}')
        return
    str_data = match.group(1)
    data = [int(x, 16) for x in re.findall(r'0x[0-9A-Fa-f]{2}', str_data)]
    header = data[0:4]
    num_old = data[3]
    jump = data[4:4 + num_old*4]
    bitmap = data[4 + num_old*4:]
    num = 95  # ASCII 32-126
    jump_en = jump[0:num*4]
    new_offsets = []
    used = []
    current = 0
    for i in range(num):
        off_h = jump_en[i*4]
        off_l = jump_en[i*4+1]
        if off_h == 0xFF and off_l == 0xFF:
            new_offsets.append(0xFFFF)
        else:
            offset = off_h << 8 | off_l
            w = jump_en[i*4+2]
            bytes_per = (header[1] + 7) // 8
            size = w * bytes_per
            used.append(bitmap[offset:offset + size])
            new_offsets.append(current)
            current += size
    bitmap_en = []
    for u in used:
        bitmap_en.extend(u)
    for i in range(num):
        offset = new_offsets[i]
        if offset == 0xFFFF:
            jump_en[i*4] = 0xFF
            jump_en[i*4+1] = 0xFF
        else:
            jump_en[i*4] = offset >> 8
            jump_en[i*4+1] = offset & 0xFF
    header[3] = num
    # 直接写入字体定义，不调用generate_font_files
    with open('OLEDDisplayFontsCN.cpp', 'a') as f:
        f.write(f'const uint8_t {font_name_en}[] PROGMEM = {{\n')
        f.write('    ' + ', '.join(f'0x{b:02X}' for b in header) + ', // Width, Height, First Char, Num Chars\n')
        f.write('    // Jump Table:\n')
        for i in range(num):
            chunk = jump_en[i*4:i*4+4]
            f.write('    ' + ', '.join(f'0x{b:02X}' for b in chunk) + f',  // 0x{32 + i:04X} "{chr(32 + i)}"\n')
        f.write('    // Bitmap Data:\n')
        for i in range(0, len(bitmap_en), 16):
            chunk = bitmap_en[i:i+16]
            f.write('    ' + ', '.join(f'0x{b:02X}' for b in chunk) + ',\n')
        f.write('};\n')

# Initialize files
with open('OLEDDisplayFontsCN.h', 'w') as f:
    f.write('#ifndef OLEDDISPLAYFONTSCN_H\n#define OLEDDISPLAYFONTSCN_H\n#ifdef ARDUINO\n#include <Arduino.h>\n#elif __MBED__\n#define PROGMEM\n#endif\n')

with open('OLEDDisplayFontsCN.cpp', 'w') as f:
    f.write('#include "OLEDDisplayFontsCN.h"\n\n')

# Generate English 12px
charset_en = [chr(i) for i in range(32, 127)]
glyph_bitmaps_en = []
glyph_widths_en = []
glyph_advances_en = []
for char in charset_en:
    binary, w, adv = get_char_bitmap(char)
    bitmap = convert_to_oled_format(binary, w)
    glyph_bitmaps_en.append(bitmap)
    glyph_widths_en.append(w)
    glyph_advances_en.append(adv)
generate_font_files('ArialMT_Plain_12_EN', 32, ''.join(charset_en), glyph_bitmaps_en, glyph_widths_en, glyph_advances_en)

# Generate Chinese 12px
charset_cn, fonts = parse_font_data()
num_chars_cn = len(charset_cn)
data_per_char = 18
glyph_bitmaps_cn = []
glyph_widths_cn = [12] * num_chars_cn
glyph_advances_cn = [12] * num_chars_cn
for i in range(num_chars_cn):
    start = i * data_per_char
    char_data = fonts[start:start + data_per_char]
    bitmap = convert_to_oled_format(char_data, 12, 12)
    glyph_bitmaps_cn.append(bitmap)
generate_font_files('SimSun_Plain_12_CN', ord(charset_cn[0]), charset_cn, glyph_bitmaps_cn, glyph_widths_cn, glyph_advances_cn)

# Extract English from PL fonts
extract_en_from_pl('ArialMT_Plain_10_PL', 'ArialMT_Plain_10_EN')
extract_en_from_pl('ArialMT_Plain_16_PL', 'ArialMT_Plain_16_EN')
extract_en_from_pl('ArialMT_Plain_24_PL', 'ArialMT_Plain_24_EN')

# Close .h file
with open('OLEDDisplayFontsCN.h', 'a') as f:
    f.write('#endif\n')

print("Font files generated: OLEDDisplayFontsCN.h, OLEDDisplayFontsCN.cpp")