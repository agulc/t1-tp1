#include <sysinit.h>
#include <delay.h>
#include <string.h>

void lcd_init(void);
void lcd_clrscr(void);
void lcd_home(void);
void lcd_go_to_xy(uint8_t x, uint8_t y);
void lcd_put_value(char val);
void lcd_put_string(char *str, uint8_t len);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_load_buffer_high(char *str);
void lcd_load_buffer_low(char *str);
void lcd_refresh(void);
