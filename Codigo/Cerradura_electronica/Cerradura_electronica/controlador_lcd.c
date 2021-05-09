#include <avr/io.h>
uint8_t x = 16;

void mostrarString(const uint8_t *dato, uint8_t x, uint8_t y, uint8_t size )
{ //recibe el string, la posición a ser mostrado y la longitud del string
	uint8_t i;
	LCDGotoXY(x,y);
	for(i=0;i<size;i++){ //no se porque -2 pero así si
		LCDsendChar(dato[i]);
	}
}
void mostrarArriba(const uint8_t *dato)
{ //recibe el string, la posición a ser mostrado y la longitud del string
	uint8_t i;
	LCDGotoXY(0,0);
	for(i=0;i<x;i++){ //no se porque -2 pero así si
		LCDsendChar(dato[i]);
	}
}
void mostrarAbajo(const uint8_t *dato)
{ //recibe el string, la posición a ser mostrado y la longitud del string
	uint8_t i;
	LCDGotoXY(0,1);
	for(i=0;i<x;i++){ //no se porque -2 pero así si
		LCDsendChar(dato[i]);
	}
}