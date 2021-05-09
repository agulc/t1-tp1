/*
 * Cerradura_electronica.c
 *
 * Created: 04/05/2021 12:30:07
 * Author : Agustín
 */ 

#include <avr/io.h>
#include "lcd.h"
#include <time.h>
#define F_CPU 8000000L
#include <util/delay.h>
#include <string.h>
#include "controlador_lcd.c"

int main(void)
{
	uint8_t locked[8] = {1+'0',6+'0',':','2','0',':','0','0'};
	
	LCDinit(); //se inicializa el display
	mostrarArriba(locked);
	LCDGotoXY(0,0);
	//muestreoInicial();
	//mostrarString(locked,0,1, sizeof(locked));
	LCDcursorOnBlink();
    /* Replace with your application code */
    while (1) 
    {
			
    }
}

