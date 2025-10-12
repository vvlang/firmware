#ifndef OLEDDISPLAYFONTSCN_H
#define OLEDDISPLAYFONTSCN_H
#ifdef ARDUINO
#include <Arduino.h>
#elif __MBED__
#define PROGMEM
#endif
extern const uint8_t ArialMT_Plain_12_EN[] PROGMEM;
extern const uint8_t ArialMT_Plain_10_EN[] PROGMEM;
extern const uint8_t ArialMT_Plain_16_EN[] PROGMEM;
extern const uint8_t ArialMT_Plain_24_EN[] PROGMEM;
extern const uint8_t SimSun_Plain_12_CN[] PROGMEM;
#endif
