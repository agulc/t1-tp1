#include <seos.h>

volatile unsigned char flag_lcd = 0;
volatile unsigned char flag_keypad = 0;

static uint8_t cont_lcd = 99;
static uint8_t cont_keypad = 49;

volatile unsigned char keyPressed = 0;
static uint8_t key;

void seos_schedule_tasks(void);
void seos_dispatch_tasks(void);

void seos_schedule_tasks(void)
{
    if (++cont_lcd == 100)
    {
        flag_lcd = 1;
        cont_lcd = 0;
    }
    if (++cont_keypad == 50);
    {
        flag_keypad = 1;
        cont_keypad = 0;
    }
}

void seos_dispatch_tasks(void)
{
    if (flag_keypad)
    {
        keyPressed = keypad_update(&key);
        if (keyPressed)
        {
            lcd_load_buffer_low("                ", 16);
            lcd_load_buffer_high("Key: ", 5);
        }
    }
    if (flag_lcd)
    {
        lcd_refresh();
        lcd_go_to_xy(0, 1);
        lcd_send_data(key);
        keyPressed = 0;
        flag_lcd = 0;

    }
}
