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

void print_field_data(char* str2, int mag_size) {
  char str1[] = "B Field: ";
  //char *str2 = input;
  int size = (sizeof(str1) + mag_size -2);
  int index_tracker = 0;
  char str_new[size];

  for (int strings = 0; strings < 2; strings++) {
    for (int index = 0; index < 100; index++) {
      if (strings == 0) {
        if (str1[index] != '\0') {
          str_new[index_tracker] = str1[index];
          index_tracker += 1;
        } else {
          break;
        }
      } else if (strings == 1) {
        if (str2[index] != '\0') {
          str_new[index_tracker] = str2[index];
          index_tracker += 1;
          //if (index_tracker == size) {break;}
        } else if (str2[index] == '\0') {
          str_new[index_tracker] = str2[index];
          break;
        }
      }
    }
  }
  lcd_clear();
  lcd_print(str_new);
  lcd_print("\nSenor ONLINE");
  sleep_ms(500);
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
  
  char input_1[] = "60nT";
  char input_2[] = "65nT";
  char input_3[] = "15nT";
  char input_4[] = "-200nT";

  while ( true ) {

    print_field_data(input_1, sizeof(input_1));
    print_field_data(input_2, sizeof(input_2));
    print_field_data(input_3, sizeof(input_3));
    print_field_data(input_4, sizeof(input_4));

  }
}
