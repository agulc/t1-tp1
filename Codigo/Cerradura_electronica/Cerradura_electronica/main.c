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
uint8_t x = 16;	
void mostrarString(const uint8_t *dato, uint8_t x, uint8_t y, uint8_t size ){ //recibe el string, la posición a ser mostrado y la longitud del string
	uint8_t i;
	LCDGotoXY(x,y);
	for(i=0;i<size;i++){ //no se porque -2 pero así si
		LCDsendChar(dato[i]);
	}
}
void mostrarArriba(const uint8_t *dato){ //recibe el string, la posición a ser mostrado y la longitud del string
	uint8_t i;
	LCDGotoXY(0,0);
	for(i=0;i<x;i++){ //no se porque -2 pero así si
		LCDsendChar(dato[i]);
	}
}
void mostrarAbajo(const uint8_t *dato){ //recibe el string, la posición a ser mostrado y la longitud del string
	uint8_t i;
	LCDGotoXY(0,1);
	for(i=0;i<x;i++){ //no se porque -2 pero así si
		LCDsendChar(dato[i]);
	}
}
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

