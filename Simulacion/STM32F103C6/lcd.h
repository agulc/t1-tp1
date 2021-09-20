#include <sysinit.h>
#include <delay.h>

void lcd_init(void);
void lcd_clrscr(void);
void lcd_home(void);
void lcd_go_to_xy(uint8_t x, uint8_t y);
void lcd_put_value(char val);
void lcd_put_string(char *str, uint8_t len);
void lcd_send_cmd(uint8_t cmd);
