#ifndef CHINESEOLEDFONTS_H
#define CHINESEOLEDFONTS_H

#ifdef ARDUINO
#include <Arduino.h>
#elif __MBED__
#define PROGMEM
#else
#include <stdint.h>
#define PROGMEM
#endif

extern const uint8_t ChineseFont_12[] PROGMEM;
extern const uint8_t ChineseFont_16[] PROGMEM;
extern const uint8_t ChineseFont_24[] PROGMEM;

#endif