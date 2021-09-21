/*
This module contains functions to initialize different system components.
*/
#include <sysinit.h>

void gpio_init(void);

void gpio_init(void)
{
    // enables clock for GPIO ports
    RCC -> APB2ENR |= 0xFC;
}

