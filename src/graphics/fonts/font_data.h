#ifndef FONT_DATA_H
#define FONT_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// 中文字体数据
extern const char charset[];
extern const uint8_t fonts[];

// 中文字符查找函数
int findChineseChar(const char* utf8_char);

// 获取中文字符的点阵数据
const uint8_t* getChineseCharBitmap(int index);

// 字体参数
#define CHINESE_FONT_WIDTH 12
#define CHINESE_FONT_HEIGHT 12
#define CHINESE_FONT_DATA_SIZE 18
#define CHINESE_FONT_CHAR_COUNT 3755

#ifdef __cplusplus
}
#endif

#endif // FONT_DATA_H

