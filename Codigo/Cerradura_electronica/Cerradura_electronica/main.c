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
#include "controlador_lcd.h"
#include "funciones.h"
#define F_CPU 8000000L

int main(void)
{
    unsigned char masc_hora[] = {0,0,0,0,0,0};
    uint8_t tecla = 0;
    set_temporizador(100);

    while (1) 
    {
      MEF_reloj(masc_hora);
      tecla = 0;
      KEYPAD_Update(&tecla);
	  mef_funciones(masc_hora,tecla);
      _delay_ms(10);  
    }
}
