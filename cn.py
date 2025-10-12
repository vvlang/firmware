import re

# 读取完整 font_data.c 内容（替换为您的文件内容）
with open('font_data.c', 'r', encoding='utf-8') as f:
    font_content = f.read()

# 提取 charset
charset_match = re.search(r'const char charset\[\] = "(.*?)";', font_content, re.DOTALL)
charset = charset_match.group(1) if charset_match else ''

# 提取 fonts 数组，移除注释
fonts_match = re.search(r'const uint8_t fonts\[\] = \{(.*?)\};', font_content, re.DOTALL)
fonts_str = fonts_match.group(1) if fonts_match else ''
fonts_str = re.sub(r'/\*.*?\*/', '', fonts_str)  # 移除 /* 啊 */ 等注释
fonts = [int(x.strip(), 0) for x in fonts_str.split(',') if x.strip()]  # 支持 0x 或十进制

# 验证：字符数 * 18 == len(fonts)
assert len(fonts) == len(charset) * 18, "数据不完整"

# 生成 chinese_font.h
with open('chinese_font.h', 'w') as f:
    f.write('#ifndef CHINESE_FONT_H\n#define CHINESE_FONT_H\n\n')
    f.write('#include <stdint.h>\n#include <avr/pgmspace.h>  // 如果使用 PROGMEM\n\n')
    f.write('const uint8_t chineseFont[] PROGMEM = {\n')
    for i in range(0, len(fonts), 18):
        char_data = fonts[i:i+18]
        f.write('    ' + ', '.join(f'0x{byte:02X}' for byte in char_data) + ',  // ' + charset[i//18] + '\n')
    f.write('};\n\n')
    f.write('#define FONT_WIDTH 12\n#define FONT_HEIGHT 12\n#define FONT_CHAR_COUNT ' + str(len(charset)) + '\n')
    f.write('#endif\n')