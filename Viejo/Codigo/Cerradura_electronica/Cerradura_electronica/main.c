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
#include <avr/interrupt.h>
volatile uint8_t flag = 0;
volatile uint16_t contador = 0;

int main(void)
{
	
	
    unsigned char masc_hora[] = {0,4,2,0,0,0};
    uint8_t tecla = 0;
	uint8_t hola = 0;
    set_temporizador(100);
	set_temporizador_funciones(100);
	LCDinit();
	/*se configura las interrupciones por temporizador*/
	OCR0A = 250;
	TCCR0A = 0x02; //se activa modo CTC
	TCCR0B = 0x02;
	TIMSK0 = (1<<OCIE0A);
	sei();
	/*se configura las interrupciones por temporizador*/

    while (1) 
    {
		flag = 0;
		MEF_reloj(masc_hora);
		tecla = 0;
		KEYPAD_Update(&tecla);
		mef_funciones(masc_hora,tecla);
		while(!flag);
    }
}
ISR(TIMER0_COMPA_vect){
	contador++;
	if(contador == 50)
	{
		flag = 1;
		contador = 0;
	}
}
