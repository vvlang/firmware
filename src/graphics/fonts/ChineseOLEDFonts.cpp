#ifdef OLED_CN
#include "ChineseOLEDFonts.h"
#include "ASCIIFontData.h"
#include "font_data.c"  // 导入中文字库数据

// 外部声明中文字符集和位图数据
extern const char charset[];
extern const uint8_t fonts[];

// 中文字符集常量
#define CHINESE_CHAR_COUNT 3755
#define CHINESE_CHAR_WIDTH 12
#define CHINESE_CHAR_HEIGHT 12
#define CHINESE_CHAR_DATA_SIZE 18  // 12x12/8 = 18字节

// 12pt中文字体 - 使用现有的ASCII字体数据
const uint8_t ChineseFont_12[] PROGMEM = {
    // 字体头信息
    0x0C, // Width: 12
    0x0C, // Height: 12
    0x20, // First char: 32
    0x3F, // Number of chars: 63 (ASCII 32-94)
    
    // 跳转表 - 使用ASCII字体数据
    // 每个条目: [offset_high, offset_low, width, height]
    0xFF, 0xFF, 0x00, 0x0C, // 32 (space) - 宽度0
    0x00, 0x00, 0x05, 0x0C, // 33 (!) - 偏移0, 宽度5, 高度12
    0x00, 0x12, 0x06, 0x0C, // 34 (") - 偏移18, 宽度6, 高度12
    0x00, 0x24, 0x08, 0x0C, // 35 (#) - 偏移36, 宽度8, 高度12
    0x00, 0x3C, 0x07, 0x0C, // 36 ($) - 偏移60, 宽度7, 高度12
    0x00, 0x4E, 0x0A, 0x0C, // 37 (%) - 偏移78, 宽度10, 高度12
    0x00, 0x68, 0x08, 0x0C, // 38 (&) - 偏移104, 宽度8, 高度12
    0x00, 0x80, 0x02, 0x0C, // 39 (') - 偏移128, 宽度2, 高度12
    0x00, 0x8C, 0x04, 0x0C, // 40 (() - 偏移140, 宽度4, 高度12
    0x00, 0x98, 0x04, 0x0C, // 41 ()) - 偏移152, 宽度4, 高度12
    0x00, 0xA4, 0x05, 0x0C, // 42 (*) - 偏移164, 宽度5, 高度12
    0x00, 0xB6, 0x07, 0x0C, // 43 (+) - 偏移182, 宽度7, 高度12
    0x00, 0xC8, 0x03, 0x0C, // 44 (,) - 偏移200, 宽度3, 高度12
    0x00, 0xD4, 0x03, 0x0C, // 45 (-) - 偏移212, 宽度3, 高度12
    0x00, 0xE0, 0x03, 0x0C, // 46 (.) - 偏移224, 宽度3, 高度12
    0x00, 0xEC, 0x04, 0x0C, // 47 (/) - 偏移236, 宽度4, 高度12
    0x00, 0xF8, 0x07, 0x0C, // 48 (0) - 偏移248, 宽度7, 高度12
    0x01, 0x0E, 0x06, 0x0C, // 49 (1) - 偏移270, 宽度6, 高度12
    0x01, 0x20, 0x07, 0x0C, // 50 (2) - 偏移288, 宽度7, 高度12
    0x01, 0x32, 0x07, 0x0C, // 51 (3) - 偏移306, 宽度7, 高度12
    0x01, 0x44, 0x08, 0x0C, // 52 (4) - 偏移324, 宽度8, 高度12
    0x01, 0x56, 0x07, 0x0C, // 53 (5) - 偏移342, 宽度7, 高度12
    0x01, 0x68, 0x07, 0x0C, // 54 (6) - 偏移360, 宽度7, 高度12
    0x01, 0x7A, 0x07, 0x0C, // 55 (7) - 偏移378, 宽度7, 高度12
    0x01, 0x8C, 0x07, 0x0C, // 56 (8) - 偏移396, 宽度7, 高度12
    0x01, 0x9E, 0x07, 0x0C, // 57 (9) - 偏移414, 宽度7, 高度12
    0x01, 0xB0, 0x03, 0x0C, // 58 (:) - 偏移432, 宽度3, 高度12
    0x01, 0xBC, 0x03, 0x0C, // 59 (;) - 偏移444, 宽度3, 高度12
    0x01, 0xC8, 0x07, 0x0C, // 60 (<) - 偏移456, 宽度7, 高度12
    0x01, 0xDA, 0x07, 0x0C, // 61 (=) - 偏移474, 宽度7, 高度12
    0x01, 0xEC, 0x07, 0x0C, // 62 (>) - 偏移492, 宽度7, 高度12
    0x01, 0xFE, 0x08, 0x0C, // 63 (?) - 偏移510, 宽度8, 高度12
    0x02, 0x10, 0x0B, 0x0C, // 64 (@) - 偏移528, 宽度11, 高度12
    0x02, 0x2C, 0x09, 0x0C, // 65 (A) - 偏移556, 宽度9, 高度12
    0x02, 0x40, 0x08, 0x0C, // 66 (B) - 偏移576, 宽度8, 高度12
    0x02, 0x52, 0x08, 0x0C, // 67 (C) - 偏移594, 宽度8, 高度12
    0x02, 0x64, 0x08, 0x0C, // 68 (D) - 偏移612, 宽度8, 高度12
    0x02, 0x76, 0x08, 0x0C, // 69 (E) - 偏移630, 宽度8, 高度12
    0x02, 0x88, 0x07, 0x0C, // 70 (F) - 偏移648, 宽度7, 高度12
    0x02, 0x9A, 0x09, 0x0C, // 71 (G) - 偏移666, 宽度9, 高度12
    0x02, 0xAE, 0x09, 0x0C, // 72 (H) - 偏移686, 宽度9, 高度12
    0x02, 0xC2, 0x03, 0x0C, // 73 (I) - 偏移706, 宽度3, 高度12
    0x02, 0xCE, 0x05, 0x0C, // 74 (J) - 偏移718, 宽度5, 高度12
    0x02, 0xDA, 0x09, 0x0C, // 75 (K) - 偏移730, 宽度9, 高度12
    0x02, 0xEE, 0x08, 0x0C, // 76 (L) - 偏移750, 宽度8, 高度12
    0x03, 0x00, 0x0B, 0x0C, // 77 (M) - 偏移768, 宽度11, 高度12
    0x03, 0x16, 0x09, 0x0C, // 78 (N) - 偏移790, 宽度9, 高度12
    0x03, 0x2A, 0x09, 0x0C, // 79 (O) - 偏移810, 宽度9, 高度12
    0x03, 0x3E, 0x08, 0x0C, // 80 (P) - 偏移830, 宽度8, 高度12
    0x03, 0x50, 0x09, 0x0C, // 81 (Q) - 偏移848, 宽度9, 高度12
    0x03, 0x64, 0x08, 0x0C, // 82 (R) - 偏移868, 宽度8, 高度12
    0x03, 0x76, 0x08, 0x0C, // 83 (S) - 偏移888, 宽度8, 高度12
    0x03, 0x88, 0x08, 0x0C, // 84 (T) - 偏移904, 宽度8, 高度12
    0x03, 0x9A, 0x09, 0x0C, // 85 (U) - 偏移920, 宽度9, 高度12
    0x03, 0xAE, 0x09, 0x0C, // 86 (V) - 偏移942, 宽度9, 高度12
    0x03, 0xC2, 0x0C, 0x0C, // 87 (W) - 偏移962, 宽度12, 高度12
    0x03, 0xDA, 0x09, 0x0C, // 88 (X) - 偏移986, 宽度9, 高度12
    0x03, 0xEE, 0x09, 0x0C, // 89 (Y) - 偏移1006, 宽度9, 高度12
    0x04, 0x02, 0x08, 0x0C, // 90 (Z) - 偏移1026, 宽度8, 高度12
    0x04, 0x14, 0x04, 0x0C, // 91 ([) - 偏移1044, 宽度4, 高度12
    0x04, 0x20, 0x04, 0x0C, // 92 (\) - 偏移1056, 宽度4, 高度12
    0x04, 0x2C, 0x04, 0x0C, // 93 (]) - 偏移1068, 宽度4, 高度12
    0x04, 0x38, 0x07, 0x0C, // 94 (^) - 偏移1080, 宽度7, 高度12
    
    // ASCII字符位图数据 (从ASCIIFontData.h获取)
    // 这里直接包含ASCII_FONT_DATA的内容
    // 由于ASCII_FONT_DATA很大，这里使用简化的方式
    // 实际应该从ASCIIFontData.h复制完整的位图数据
};

// 16pt和24pt字体暂时使用12pt数据
const uint8_t ChineseFont_16[] PROGMEM = {
    0x0C, // Width: 12
    0x0C, // Height: 12
    0x20, // First char: 32
    0x3F, // Number of chars: 63
    // 使用与12pt相同的数据
};

const uint8_t ChineseFont_24[] PROGMEM = {
    0x0C, // Width: 12
    0x0C, // Height: 12
    0x20, // First char: 32
    0x3F, // Number of chars: 63
    // 使用与12pt相同的数据
};

// 中文字符查找函数
bool isChineseChar(const char* utf8Char) {
    if (!utf8Char) return false;
    
    // 检查UTF-8编码范围 (中文字符通常是3字节)
    unsigned char first = (unsigned char)utf8Char[0];
    if (first >= 0xE4 && first <= 0xE9) {  // 中文字符范围
        return true;
    }
    return false;
}

uint16_t utf8ToGB2312(const char* utf8Char) {
    if (!isChineseChar(utf8Char)) return 0;
    
    // 简化的UTF-8到GB2312转换
    unsigned char b1 = (unsigned char)utf8Char[0];
    unsigned char b2 = (unsigned char)utf8Char[1];
    unsigned char b3 = (unsigned char)utf8Char[2];
    
    // 这里需要实现完整的UTF-8到GB2312转换逻辑
    return ((b1 & 0x0F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
}

int findChineseCharIndex(const char* utf8Char) {
    if (!isChineseChar(utf8Char)) return -1;
    
    // 将UTF-8转换为GB2312
    uint16_t gb2312 = utf8ToGB2312(utf8Char);
    if (gb2312 == 0) return -1;
    
    // 在charset中查找字符
    for (int i = 0; i < CHINESE_CHAR_COUNT; i++) {
        // 从charset中获取字符的UTF-8编码进行比较
        const char* charPtr = &charset[i * 3]; // 每个中文字符占用3个字节
        if (charPtr[0] == utf8Char[0] && charPtr[1] == utf8Char[1] && charPtr[2] == utf8Char[2]) {
            return i;
        }
    }
    return -1;
}

const uint8_t* getChineseCharData(const char* utf8Char) {
    int index = findChineseCharIndex(utf8Char);
    if (index < 0) return nullptr;
    
    // 从fonts数组中获取位图数据
    // 每个中文字符占用18字节的位图数据
    return &fonts[index * 18];
}

uint8_t getChineseCharWidth(const char* utf8Char) {
    if (!isChineseChar(utf8Char)) return 0;
    
    // 中文字符固定宽度12像素
    return CHINESE_CHAR_WIDTH;
}

uint16_t getMixedStringWidth(const char* str) {
    if (!str) return 0;
    
    uint16_t width = 0;
    const char* ptr = str;
    
    while (*ptr) {
        if (*ptr >= 32 && *ptr <= 126) {
            // ASCII字符
            width += 6; // 标准ASCII字符宽度
            ptr++;
        } else if (isChineseChar(ptr)) {
            // 中文字符
            width += CHINESE_CHAR_WIDTH;
            // 跳过UTF-8字符的多个字节
            while ((*ptr & 0xC0) == 0x80) ptr++;
            ptr++;
        } else {
            // 其他字符
            width += 6; // 默认宽度
            ptr++;
        }
    }
    
    return width;
}

bool isCharSupported(const char* utf8Char) {
    if (!utf8Char) return false;
    
    // ASCII字符总是支持
    if (*utf8Char >= 32 && *utf8Char <= 126) {
        return true;
    }
    
    // 检查中文字符是否在charset中
    if (isChineseChar(utf8Char)) {
        return findChineseCharIndex(utf8Char) >= 0;
    }
    
    return false;
}

#endif // OLED_CN