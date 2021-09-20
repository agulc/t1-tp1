#include <lcd.h>

#define LCD_RS 7
#define LCD_RW 6
#define LCD_EN 5

char lcd_buffer_high[16];
char lcd_buffer_low[16];

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

void lcd_init(void)
{
    GPIOA->CRL = 0x33333333;
    GPIOB->CRL = 0x33344444;
    GPIOB->BRR = (1<<LCD_EN); //same as GPIOA->ODR &= ~(1<<LCD_EN);/* LCD_EN = 0 */
    GPIOB->BRR = (1<<LCD_RW); //same as GPIOA->ODR &= ~(1<<LCD_RW);/* LCD_RW = 0 */
   // delay_us(3000); /* wait 3ms */
    lcd_send_cmd(0x38);/* init.LCD 2 line,5´7 matrix */
    lcd_send_cmd(0x0C);/* display on, cursor on */
    lcd_send_cmd(0x01);/* clear LCD */
    //delay_us(2000);/* wait 2ms */
    lcd_send_cmd(0x06);/* shift cursor right */
}

void lcd_send_cmd(uint8_t cmd)
{
    GPIOB->BRR = (1 << LCD_RS); /* RS = 0 forcommand*/
    lcd_put_value(cmd);
    delay_us(10000);/* wait*/
}

void lcd_send_data(uint8_t data)
{
    GPIOB->BSRR = (1 << LCD_RS); /* RS = 1 fordata */
    lcd_put_value(data);
    delay_us(250);/* wait*/
}

void lcd_put_value(char value)
{
    GPIOA->BRR = 0xFF; /* clearPA0-PA7 */
    GPIOA->BSRR = value & 0xFF; /* putvalueonPA0-PA7 */
    GPIOB->BSRR = (1<<LCD_EN);/* EN = 1 forH-to-L pulse */
    delay_us(2);/* makeEN pulse wider*/
    GPIOB->BRR = (1<<LCD_EN); /* EN = 0 forH-to-L pulse */
}

void lcd_go_to_xy(uint8_t x, uint8_t y)
{
    uint8_t address;

    if (y == 0)
    {
        address = 0x80 + x;
    }
    else
    {
        address = 0xC0 + x;
    }

    lcd_send_cmd(address);
}

void lcd_clrscr(void)
{
    lcd_send_cmd(0x01);
}

void lcd_home(void)
{
    lcd_send_cmd(0x02);
}

void lcd_put_string(char *str, uint8_t len)
{
    uint8_t i;
    for (i = 0; i < len; i++)
    {
        lcd_send_data(str[i]);
    }
}

void lcd_load_buffer_high(char *str)
{
    strncpy(lcd_buffer_high, str, 16);
}

void lcd_load_buffer_low(char *str)
{
    strncpy(lcd_buffer_low, str, 16);
}

void lcd_refresh(void)
{
    lcd_home();
    lcd_put_string(lcd_buffer_high, 16);
    lcd_go_to_xy(0, 1);
    lcd_put_string(lcd_buffer_low, 16);
}
