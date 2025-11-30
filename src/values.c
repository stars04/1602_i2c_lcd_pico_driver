#include <stdint.h>
#include "values.h"

const int LCD_ADDR = 0x27;

const uint8_t LCD_ENABLE_PIN = 0x04;
const uint8_t LCD_BACKLIGHT = 0x08;
const uint8_t LCD_CLEAR = 0x01;
const uint8_t LCD_RETURN = 0x02;
const uint8_t LCD_ENTRY = 0x06;
const uint8_t LCD_DISPLAY_CONTROL = 0x0F;
const uint8_t LCD_FUNCTION_SET = 0x28;

// DDRAM ADDRESS
const uint8_t LINE_1_HOME = 0x80;
const uint8_t LINE_1_CHAR_16 = 0x8F;
const uint8_t LINE_1_END = 0xA7;
const uint8_t LINE_2_HOME = 0xC0;
const uint8_t LINE_2_CHAR_16 = 0xCF;
const uint8_t LINE_2_END = 0xE7;

// 'Modes'
const uint8_t WRITE_CHAR = 0x01;
const uint8_t READ_CHAR = 0x03;
const uint8_t NO_REG_RW = 0x00;
