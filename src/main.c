#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

const int LCD_ADDR = 0x27;

const uint8_t LCD_ENABLE_PIN = 0x04;
const uint8_t LCD_BACKLIGHT = 0x08;
const uint8_t LCD_CLEAR = 0x01;
const uint8_t LCD_RETURN = 0x02;
const uint8_t LCD_ENTRY = 0x06;
const uint8_t LCD_DISPLAY_CONTROL = 0x0F;
const uint8_t LCD_FUNCTION_SET = 0x28;

// DDRAM ADDRESS
const uint8_t RETURN_HOME = 0x80;
const uint8_t LINE_2_HOME = 0xC0;

// 'Modes'
const uint8_t WRITE_CHAR = 0x01;
const uint8_t READ_CHAR = 0x03;
const uint8_t NO_REG_RW = 0x00;

void i2c_write_byte(uint8_t byte) {
#ifdef i2c_default
  i2c_write_blocking(i2c_default, LCD_ADDR, &byte, 1, false);
#endif
}

void write_4bits(uint8_t byte, uint8_t mode) {
  uint8_t high_bits = mode | (byte & 0xF0) | LCD_BACKLIGHT;
  uint8_t low_bits = mode | ((byte << 4) & 0xF0) | LCD_BACKLIGHT;

  // Enable Pin required to write to Registers
  i2c_write_byte(high_bits | LCD_ENABLE_PIN);

  sleep_ms(1);

  i2c_write_byte(low_bits | LCD_ENABLE_PIN);

  sleep_ms(1);
}

// initialization of LCD instructions from HD44780U Documentation

void lcd_initialization() {
  // Prescribed instruction 
  sleep_ms(15);
  write_4bits(0x03, NO_REG_RW);
  sleep_ms(10);
  write_4bits(0x03, NO_REG_RW);
  sleep_ms(10);
  write_4bits(0x03, NO_REG_RW);
  write_4bits(0x02, NO_REG_RW);
  // Chosen Configuration
  write_4bits(LCD_FUNCTION_SET, NO_REG_RW);
  write_4bits(0x08, NO_REG_RW);
  write_4bits(0x01, NO_REG_RW);
  write_4bits(LCD_ENTRY, NO_REG_RW);
  // Clearing and Reseting Display as part of configuration
  write_4bits(LCD_CLEAR, NO_REG_RW);
  write_4bits(LCD_DISPLAY_CONTROL, NO_REG_RW);

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

  lcd_initialization();
  
  char input_text[] = "The C Driver\nIs Working!";

  for (int index = 0; index < sizeof(input_text); index++) {
    if (input_text[index] == '\n') {
      write_4bits(LINE_2_HOME, NO_REG_RW);
    } else if (input_text[index] != '\0') {
      write_4bits((uint8_t)input_text[index], WRITE_CHAR);
    }
  }
  

  while ( true ) {

    printf("is it working now?\n");

  }
}
