void lcd_initialization();

void lcd_print(char* input_text);

// lcd_print_address prints text starting at the specific memory ddram_address
// i.e. in an unshifted display, writing to 0x8F (LINE_1_END) will set the 
// cursor to the address that corresponds to the last visible character
// on the top row in the unshifted display.
void lcd_print_address(char* input_text, uint8_t ddram_address);

void lcd_clear();

void lcd_clear_range(uint8_t start, uint8_t end);
