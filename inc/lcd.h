void lcd_initialization();

void lcd_print(char* input_text);

void lcd_print_address(char* input_text, uint8_t ddram_address);

void lcd_clear();

void lcd_clear_range(uint8_t start, uint8_t end);
