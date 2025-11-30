extern const int LCD_ADDR;

extern const uint8_t LCD_ENABLE_PIN;
extern const uint8_t LCD_BACKLIGHT; 
extern const uint8_t LCD_CLEAR;
extern const uint8_t LCD_RETURN;
extern const uint8_t LCD_ENTRY;
extern const uint8_t LCD_DISPLAY_CONTROL;
extern const uint8_t LCD_FUNCTION_SET;

/*
 * DDRAM ADDRESSES
 * The 16x2 LCD Display has 40 Memory Addresses 
 * for each row of the display with only 16 physical 'displays'
 * in each row. To view characters written to these Addresses,
 * you must 'scroll' through the addresses to change which 
 * addresses are mapped to the 'displays'
 * 
*/
extern const uint8_t LINE_1_HOME;
extern const uint8_t LINE_1_CHAR16;
extern const uint8_t LINE_1_END;
extern const uint8_t LINE_2_HOME;
extern const uint8_t LINE_2_CHAR16;
extern const uint8_t LINE_2_END;

// 'Modes'
extern const uint8_t WRITE_CHAR;
extern const uint8_t READ_CHAR;
extern const uint8_t NO_REG_RW;
