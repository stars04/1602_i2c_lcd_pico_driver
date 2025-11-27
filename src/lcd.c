#include "pico/stdlib.h"
#include "values.h"
#include "write.h"

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

void lcd_print(char* input_text) {
  for (int index = 0; index < 100; index++) {
    if (input_text[index] == '\n') {
      write_4bits(LINE_2_HOME, NO_REG_RW);
    } else if (input_text[index] != '\0') {
      write_4bits((uint8_t)input_text[index], WRITE_CHAR);
    } else if (input_text[index] == '\0') {
      break;
    }
  }
}

void lcd_clear() {
  write_4bits(LCD_CLEAR, NO_REG_RW);
}
