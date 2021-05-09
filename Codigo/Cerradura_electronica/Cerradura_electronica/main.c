/*
 * Cerradura_electronica.c
 *
 * Created: 04/05/2021 12:30:07
 * Author : Agustín
 */ 

#include <avr/io.h>
#include "reloj.h"
#include "lcd.h"
#include "key.h"

int main(void)
{
    uint8_t tecla = 0;
    /* Replace with your application code */
    while (1) 
    {
      tecla = 0;
      KEYPAD_Update(&tecla);
      _delay_ms(10);
    }
}
