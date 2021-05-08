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

#define BLOCKED "CERRADO"
#define OPEN "LIBERADO"
#define DENIED "DENEGADO"
#define PASSWORD = 0852
enum week{CERRADO, LIBERADO, DENEGADO};
	
	
void mostrarString(const uint8_t *dato, uint8_t x, uint8_t y, uint8_t size ){ //recibe el string, la posición a ser mostrado y la longitud del string
	uint8_t i;
	LCDGotoXY(x,y);
	for(i=0;i<size;i++){ //no se porque -2 pero así si
		LCDsendChar(dato[i]);
	}
}
void muestreoEstado( enum week estado_actual ) //muestra en el display según el estado en el que esté el display
{ 
	if(estado_actual == CERRADO){
		uint8_t locked[] = BLOCKED; //se crea un string que contiene la palabra CERRADO
		mostrarString(locked,0,1, sizeof(locked)); //se muestra la palabra CERRADO en el display
		/*muestra la hora, falta eso*/
		//time_t t = time(NULL); //crea una variable tiempo
		//struct tm *tm = localtime(&t); //se le da el tiempo actual
		//uint8_t tiempo[16]; //variable para almacenar el tiempo como string
		//strftime(tiempo, sizeof(tiempo), "%c", tm); //guarda en el string tiempo lo que hay en tm
		//mostrarString (tiempo,0,0, sizeof(tiempo));
	}else
		if ( estado_actual == DENEGADO){
			LCDclr();
			uint8_t locked[] = DENIED;
			mostrarString(locked,0,1, sizeof(locked));
			_delay_ms(2000); //espera 2 segundos
			muestreoEstado(CERRADO); //vuelve a la pantalla por defecto
		}else{
			LCDclr();
			uint8_t locked[] = OPEN;
			mostrarString(locked,0,1, sizeof(locked));
			_delay_ms(2000); //espera 2 segundos
			muestreoEstado(CERRADO); //vuelve a la pantalla por defecto
		}
			
}
int main(void)
{
	uint8_t locked[7] = BLOCKED;//{'c','e','r','r','a','d','o'}; //crea un string con la palabra cerrado
	LCDinit(); //se inicializa el display
	LCDGotoXY(0,0);
	//muestreoInicial();
	mostrarString(locked,0,1, sizeof(locked));
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

