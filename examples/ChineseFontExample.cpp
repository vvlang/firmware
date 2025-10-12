/*
 * 中文字体使用示例
 * 演示如何使用OLED_PL模式的中文字符集
 */

#include "graphics/fonts/ChineseOLEDFonts.h"

#ifdef OLED_CN

void setup() {
    Serial.begin(115200);
    Serial.println("中文字体测试开始");
    
    // 测试ASCII字符
    Serial.println("=== ASCII字符测试 ===");
    const uint8_t* font12 = getChineseFont12();
    
    // 测试英文字符
    char asciiChar = 'A';
    if (isASCIIChar(asciiChar)) {
        Serial.print("字符 '");
        Serial.print(asciiChar);
        Serial.print("' 是ASCII字符，宽度: ");
        Serial.println(getCharWidth(font12, asciiChar));
    }
    
    // 测试中文字符
    Serial.println("=== 中文字符测试 ===");
    const char* chineseText = "你好世界";
    if (isChineseChar(chineseText)) {
        Serial.print("文本 '");
        Serial.print(chineseText);
        Serial.print("' 包含中文字符，宽度: ");
        Serial.println(getUTF8StringWidth(font12, chineseText));
    }
    
    // 测试混合文本
    Serial.println("=== 混合文本测试 ===");
    const char* mixedText = "Hello 你好 World 世界";
    Serial.print("混合文本: ");
    Serial.println(mixedText);
    Serial.print("总宽度: ");
    Serial.println(getUTF8StringWidth(font12, mixedText));
}

void loop() {
    // 主循环
    delay(1000);
}

#else
void setup() {
    Serial.begin(115200);
    Serial.println("中文字体未启用，请定义 OLED_CN=1");
}

void loop() {
    delay(1000);
}
#endif

