#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "values.h"
#include "write.h"


static void i2c_write_byte(uint8_t byte) {
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
  
