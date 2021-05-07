/*
 * Cerradura_electronica.c
 *
 * Created: 04/05/2021 12:30:07
 * Author : Agustín
 */ 

#include <avr/io.h>
#include "lcd.h"
#include <time.h>
void muestreoInicial( ) //muestra en el display el valor por defecto -> en la primera linea la hora y en la segunta "cerrado"
{ 
	uint8_t locked[7] = "CERRADO"; //crea un string con la palabra cerrado
	CopyStringtoLCD(&locked[0], 0, 1); //muestra cerrado en la linea 2 del display
	time_t t = time(NULL); //crea una variable tiempo
	struct tm *tm = localtime(&t); //se le da el tiempo actual
	uint8_t tiempo[64]; //variable para almacenar el tiempo como string
	strftime(tiempo, sizeof(tiempo), "%c", tm); //guarda en el string tiempo lo que hay en tm
	CopyStringtoLCD(tiempo, 0, 1);
}
int main(void)
{
	LCDinit(); //se inicializa el display
	
    /* Replace with your application code */
    while (1) 
    {
		muestreoInicial();
    }
}

