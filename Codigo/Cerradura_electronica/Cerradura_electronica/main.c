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
#include "avr/interrupt.h"
volatile uint8_t flag = 0;
int main(void)
{
	/*se configura las interrupciones por temporizador*/
	OCR0A = 100;
	TCCR0A = 0x02; //se activa modo CTC
	TCCR0B = 0x02;
	TIMSK0 = (1<<OCIE0A);
	sei( );	
	/*se configura las interrupciones por temporizador*/	
	
    unsigned char masc_hora[] = {0,4,2,0,0,0};
    uint8_t tecla = 0;
    set_temporizador(100);
	LCDinit();

    while (1) 
    {
		flag = 0;
		MEF_reloj(masc_hora);
		tecla = 0;
		KEYPAD_Update(&tecla);
		mef_funciones(masc_hora,tecla);
		// _delay_ms(10);
		while(!flag){
		
		}
    }
}
ISR(TIMER0_COMPA_vect){
	flag = 1;
}
