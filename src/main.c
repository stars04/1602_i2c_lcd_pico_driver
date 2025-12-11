#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "lcd.h"
/*
 * This File is for testing the driver as it is built 
 * (along with testing for the direct use case I have in mind
 */

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
  
  char str1[] = "B Field: \nSensor ONLINE";
  char input_1[] = "60nT";
  char input_2[] = "65nT";
  char input_3[] = "15nT";
  char input_4[] = "-200nT";

  lcd_print(str1);

  while ( true ) {

    lcd_print_address(input_1, 0x89);
    sleep_ms(450);
    lcd_clear_range(0x89, 0x8F);
    sleep_ms(100);
    lcd_print_address(input_2, 0x89);
    sleep_ms(450);
    lcd_clear_range(0x89, 0x8F);
    sleep_ms(100);
    lcd_print_address(input_3, 0x89);
    sleep_ms(450);
    lcd_clear_range(0x89, 0x8F);
    sleep_ms(100);
    lcd_print_address(input_4, 0x89);
    sleep_ms(450);
    lcd_clear_range(0x89, 0x8F);
    sleep_ms(100);

  }
}
