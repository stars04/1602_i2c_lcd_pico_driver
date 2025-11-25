#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "values.h"
#include "write.h"
#include "initialize.h"

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
  
  char input_text[] = "B Field: 60nT\nAngle: 65deg";
  char input_text_1[] = "Testing the Driver\nText Input";

  //lcd_print(input_text);

  for (int index = 0; index < sizeof(input_text); index++) {
    if (input_text[index] == '\n') {
      write_4bits(LINE_2_HOME, NO_REG_RW);
    } else if (input_text[index] != '\0') {
      write_4bits((uint8_t)input_text[index], WRITE_CHAR);
    }
  }

  sleep_ms(1000);
  lcd_clear();
  sleep_ms(1000);

  lcd_print(input_text_1, sizeof(input_text_1));

  while ( true ) {

    printf("is it working now?\n");

  }
}
