/*
This module contains functions to initialize different system components.
*/
#include <sysinit.h>

void gpio_init(void);
void keypad_init(void);

void gpio_init(void)
{
    // enables clock for GPIO ports
    RCC -> APB2ENR |= 0xFC;
}

void keypad_init(void)
{
    //initialices kepad in port A with pull-up resistors.
    GPIOB -> CRH = 0x33338888;
    GPIOB -> ODR |= 0xFF00;
}

