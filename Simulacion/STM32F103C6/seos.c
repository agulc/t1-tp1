#include <seos.h>

volatile unsigned char flag_mef = 0;
volatile unsigned char flag_keypad = 0;
volatile unsigned char flag_lcd = 0;
volatile unsigned char flag_clock = 0;

static uint8_t cont_mef = 49;
static uint8_t cont_keypad = 59;
static uint8_t cont_lcd = 199;
static uint16_t cont_clock = 999;

static uint8_t key = 0;

void seos_schedule_tasks(void);
void seos_dispatch_tasks(void);

void seos_schedule_tasks(void)
{
    if (++cont_mef >= 50)
    {
        flag_mef = 1;
        cont_mef = 0;
    }
    if (++cont_keypad >= 60)
    {
        flag_keypad = 1;
        cont_keypad = 0;
    }
    if (++cont_lcd >= 200)
    {
        flag_lcd = 1;
        cont_lcd = 0;
    }
    if (++cont_clock >= 1000)
    {
        flag_clock = 1;
        cont_clock = 0;
    }
}

void seos_dispatch_tasks(void)
{

    if (flag_mef)
    {
        mef_functions(key);
        key = 0;
        flag_mef = 0;
    }
    if (flag_keypad)
    {
        keypad_update(&key);
        flag_keypad = 0;
    }
    if (flag_clock)
    {
        clock_tick();
        flag_clock = 0;
    }
    if (flag_lcd)
    {
        lcd_refresh();
        flag_lcd = 0;
    }
}
