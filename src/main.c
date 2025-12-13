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

const uint8_t GPIO_PIN_04 = 0x04;
const uint8_t GPIO_PIN_05 = 0x05;


int main(void) {

  stdio_init_all();

  i2c_init(i2c0, 100000);
  //i2c_init(i2c1, 100000);
  //i2c_set_slave_mode(i2c1, true, 0x55);
  //i2c initialization procedure documented in pico SDK documenation
  gpio_set_function(GPIO_PIN_04, GPIO_FUNC_I2C);
  gpio_set_function(GPIO_PIN_05, GPIO_FUNC_I2C);
  gpio_pull_up(GPIO_PIN_04);
  gpio_pull_up(GPIO_PIN_05);
  //Make the I2C pins available to picotool
  bi_decl(bi_2pins_with_func(GPIO_PIN_04, GPIO_PIN_05, GPIO_FUNC_I2C));

  lcd_initialization();
  char value[] = {PICO_DEFAULT_I2C_SDA_PIN,PICO_DEFAULT_I2C_SDA_PIN - 0x01,PICO_DEFAULT_I2C_SDA_PIN +0x01,'\0'}; 
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
    lcd_print_address(value, 0x89);
    sleep_ms(450);
    //lcd_clear_range(0x89, 0x8F);
    sleep_ms(100);


  }
}
