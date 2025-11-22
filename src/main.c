#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

const int LCD_ADDR = 0x27;
const uint8_t LCD_BACKLIGHT = 0x08;

void i2c_write_byte(uint8_t byte) {
#ifdef i2c_default
  i2c_write_blocking(i2c_default, LCD_ADDR, &byte, 1, false);
#endif
}

void lcd_write(uint8_t byte, uint8_t mode) {
  uint8_t high = mode | (byte & 0xF0) | LCD_BACKLIGHT;
  uint8_t low = mode | ((byte << 4) & 0xF0) | LCD_BACKLIGHT;

  i2c_write_byte(high);
  i2c_write_byte(low);
}

int main(void) {

  stdio_init_all();

  i2c_init(i2c_default, 100000);
  //i2c initialization procedure documented in pico SDK documenation
  gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
  gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
  //Make the I2C pins available to picotool
  bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

  while ( true ) {

    printf("is it working now?\n");

  }
}
