#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "values.h"
#include "write.h"

//const int LCD_ADDR = 0x27;
//
//const uint8_t LCD_ENABLE_PIN = 0x04;
//const uint8_t LCD_BACKLIGHT = 0x08;
//const uint8_t LCD_CLEAR = 0x01;
//const uint8_t LCD_RETURN = 0x02;
//const uint8_t LCD_ENTRY = 0x06;
//const uint8_t LCD_DISPLAY_CONTROL = 0x0F;
//const uint8_t LCD_FUNCTION_SET = 0x28;
//
//// DDRAM ADDRESS
//const uint8_t RETURN_HOME = 0x80;
//const uint8_t LINE_2_HOME = 0xC0;
//
//// 'Modes'
//const uint8_t WRITE_CHAR = 0x01;
//const uint8_t READ_CHAR = 0x03;
//const uint8_t NO_REG_RW = 0x00;

void i2c_write_byte(uint8_t byte) {
#ifdef i2c_default
  i2c_write_blocking(i2c_default, LCD_ADDR, &byte, 1, false);
#endif
}

void write_4bits(uint8_t byte, uint8_t mode) {
  uint8_t high_bits = mode | (byte & 0xF0) | LCD_BACKLIGHT;
  uint8_t low_bits = mode | ((byte << 4) & 0xF0) | LCD_BACKLIGHT;

  // Enable Pin required to write to Registers
  i2c_write_byte(high_bits);

  i2c_write_byte(high_bits | LCD_ENABLE_PIN);
  sleep_ms(1);
  i2c_write_byte(high_bits & ~LCD_ENABLE_PIN);
  sleep_ms(1);

  i2c_write_byte(low_bits);

  i2c_write_byte(low_bits | LCD_ENABLE_PIN);
  sleep_ms(1);
  i2c_write_byte(low_bits & ~LCD_ENABLE_PIN);
  sleep_ms(1);
}

void lcd_print(char* input_text, int size) {
  for (int index = 0; index < size; index++) {
    if (input_text[index] == '\n') {
      write_4bits(LINE_2_HOME, NO_REG_RW);
    } else if (input_text[index] != '\0') {
      write_4bits((uint8_t)input_text[index], WRITE_CHAR);
    }
  }
}

void lcd_clear() {
  write_4bits(LCD_CLEAR, NO_REG_RW);
}
