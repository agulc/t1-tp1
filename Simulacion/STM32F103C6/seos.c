#include <seos.h>

volatile unsigned char flag_lcd = 0;
volatile unsigned char flag_keypad = 0;
volatile unsigned char flag_clock = 0;

static uint8_t cont_lcd = 49;
static uint8_t cont_keypad = 49;
static uint16_t cont_clock = 99;

volatile unsigned char keyPressed = 0;
static uint8_t key;
static char clock_mask[16];

void seos_schedule_tasks(void);
void seos_dispatch_tasks(void);

void seos_schedule_tasks(void)
{
    if (++cont_lcd >= 200)
    {
        flag_lcd = 1;
        cont_lcd = 0;
    }
    if (++cont_keypad == 50)
    {
        flag_keypad = 1;
        cont_keypad = 0;
    }
    if (++cont_clock >= 1000)
    {
        flag_clock = 1;
        cont_clock = 0;
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
        }
    }
    if (flag_clock)
    {
        clock_tick();
        flag_clock = 0;
    }
    if (flag_lcd)
    {
        clock_read(clock_mask);
        lcd_load_buffer_high(clock_mask, 16);
        lcd_refresh();
        lcd_go_to_xy(0, 1);
        lcd_send_data(key);
        keyPressed = 0;
        flag_lcd = 0;
    }
}
