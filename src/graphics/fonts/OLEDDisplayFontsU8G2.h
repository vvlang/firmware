#ifndef OLEDDISPLAYFONTSU8G2_H
#define OLEDDISPLAYFONTSU8G2_H

#ifdef OLED_CN
#include <U8g2lib.h>

// U8G2中文字体定义
extern const uint8_t u8g2_font_unifont_t_chinese2[];

// 中文字体特殊处理
#define FONT_CHINESE_U8G2 u8g2_font_unifont_t_chinese2

#endif

#endif
