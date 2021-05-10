/*Este programa es la maquina de estados principal que controla la parte interactiva de la cerradura.
Para mas información, ver la documentación del proyecto*/

#include "controlador_lcd.h"
#include "lcd.h"

unsigned char pantalla_principal(uint8_t tecla, unsigned char *reloj);
unsigned char ingresar_clave_entrada(uint8_t tecla);
unsigned char comparar_claves();
unsigned char abierto();
unsigned char denegado();
unsigned char cambiar_clave_clave_actual(uint8_t tecla);
unsigned char cambiar_clave_nueva_clave(uint8_t tecla);
unsigned char cambiar_clave_fin();
unsigned char modificar_hora(unsigned char *reloj, uint8_t tecla);
unsigned char modificar_minutos(unsigned char *reloj, uint8_t tecla);
unsigned char modificar_segundos(unsigned char *reloj, uint8_t tecla);

void refrescar_mascara_reloj(unsigned char *reloj);
void set_temporizador(unsigned short intervalo_interrupcion);
void refrescar_cursor_clave();
void set_temporizador(unsigned short intervalo_interrupcion);
char validar_reloj(unsigned char *reloj);


unsigned short dos_segundos = 20; //Suponer que 1int = 100ms
unsigned short tres_segundos = 30; //Suponer que 1int = 100ms
unsigned short contador_interrupciones = 0;
char cursor_hora = 4;
char valor_hora_alto;
char cursor_minutos = 7;
char cursor_segundos = 10;
uint8_t clave_mascara[] = {'x','x','x','x'} ;
uint8_t clave_ingresada[] = {'x','x','x','x'} ;
uint8_t clave_actual[] = {'0','8','5','2'} ;
uint8_t mascara_reloj[] = {' ',' ',' ',' ','h','h',':','m','m',':','s','s',' ',' ',' ',' '};
uint8_t mascara_reloj_conjelada[] = {' ',' ',' ',' ','h','h',':','m','m',':','s','s',' ',' ',' ',' '};
unsigned char reloj_conjelado[] = {0,0,0,0,0,0};

char cursor_clave = 0;
char tam_clave = (char) sizeof(clave_mascara)/sizeof(clave_mascara[0]);
unsigned char estado = 1;


void mef_funciones(unsigned char *reloj, uint8_t tecla)//Analizar que devería recibir una vez establecido el modulo LCD
{
	switch (estado)
	{
		case 1:
			estado = pantalla_principal(tecla,reloj);
			break;
		case 2:
			estado = ingresar_clave_entrada(tecla);
			break;
		case 3:
			estado = abierto();
			break;
		case 4:
			estado = denegado();
			break;
		case 5:
			estado = cambiar_clave_clave_actual(tecla);
			break;
		case 6:
			estado = cambiar_clave_nueva_clave(tecla);
			break;
		case 7:
			estado = cambiar_clave_fin();
			break;
		case 8:
			estado = modificar_hora(reloj,tecla);
			break;
		case 9:
			estado = modificar_minutos(reloj,tecla);
			break;
		case 10:
			estado = modificar_segundos(reloj,tecla);
			break;
		default:
			estado = pantalla_principal(tecla,reloj);
			break;		
	}
}

unsigned char pantalla_principal(uint8_t tecla, unsigned char *reloj)
{
    // Mostrar Hora y "CERRADO", se espera una entrada por teclado. La hora es obtenida de una mascara comandada por la MEF Reloj.
    unsigned char proximo_estado = 1;

    //seteo lo que se tenga que mostrar en el display
	refrescar_mascara_reloj(reloj);
	mostrarAbajo("    CERRADO     ");

    switch (tecla)
    {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			clave_ingresada[cursor_clave] = tecla;
			cursor_clave++;
			proximo_estado = 2; //Ingresar clave entrada
			break;
		
		case 'A':
			copiar_arreglo(mascara_reloj, mascara_reloj_conjelada, 16);
			copiar_arreglo(reloj,reloj_conjelado,6);
			mostrarArriba(mascara_reloj_conjelada);
			mostrarAbajo("    CERRADO    ");
			LCDGotoXY(4,0);
			LCDcursorOnBlink();
			proximo_estado = 8; //Modificar hora

			break;
		
		case 'B':
			copiar_arreglo(mascara_reloj, mascara_reloj_conjelada, 16);
			copiar_arreglo(reloj,reloj_conjelado,6);
			mostrarArriba(mascara_reloj_conjelada);
			mostrarAbajo("    CERRADO    ");
			LCDGotoXY(7,0);
			LCDcursorOnBlink();
			proximo_estado = 9; //Modificar minutos
			break;
		
		case 'C':
			copiar_arreglo(mascara_reloj, mascara_reloj_conjelada, 16);
			copiar_arreglo(reloj,reloj_conjelado,6);
			mostrarArriba(mascara_reloj_conjelada);
			mostrarAbajo("    CERRADO    ");
			LCDGotoXY(10,0);
			LCDcursorOnBlink();
			proximo_estado = 10; //Modificar segundos
			break;
		
		case 'D':
			proximo_estado = 5; //Cambiar clave: Clave actual
			break;
		
		default:
			break;
    }
	
	return proximo_estado;
}

unsigned char ingresar_clave_entrada(uint8_t tecla)
{
	//Mostrar "Ingresar clave" y  "*" por cada caracter ingresado. Se mantiene hasta haber ingresado una clave de 4 caracteres.
	unsigned char proximo_estado = 2;

	//seteo lo que se tenga que mostrar en el display
	mostrarArriba("Ingresar clave ");
	refrescar_cursor_clave();

	switch (tecla)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			clave_ingresada[cursor_clave] = tecla;
			cursor_clave++;
			
			if (cursor_clave >= tam_clave)
			{
				cursor_clave = 0;
				proximo_estado = 4; //Denegado
				
				if (comparar_claves())
				{
					proximo_estado = 3; //Abierto
				}
			}
			
			break;
		
		default:
			break;
	}
	
	return proximo_estado;
	
}

unsigned char abierto()
{
	unsigned char proximo_estado = 3;

	contador_interrupciones++;
	mostrarArriba("               ");
	mostrarAbajo("    ABIERTO    ");

	if (contador_interrupciones > tres_segundos)
	{
		proximo_estado = 1;
		contador_interrupciones = 0;
	}

	return proximo_estado;
	
}

unsigned char denegado()
{
	unsigned char proximo_estado = 4;

	contador_interrupciones++;
	mostrarArriba("               ");
	mostrarAbajo("    DENEGADO   ");

	if (contador_interrupciones > dos_segundos)
	{
		proximo_estado = 1;
		contador_interrupciones = 0;
	}

	return proximo_estado;	
}

unsigned char cambiar_clave_clave_actual(uint8_t tecla)
{
	//Mostrar "Clave actual" y  "*" por cada caracter ingresado. Se mantiene hasta haber ingresado una clave de 4 caracteres.
	unsigned char proximo_estado = 5;

	//seteo lo que se tenga que mostrar en el display
	mostrarArriba("Clave actual   ");
	refrescar_cursor_clave();
	
	switch (tecla)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			clave_ingresada[cursor_clave] = tecla;
			cursor_clave++;

			if (cursor_clave >= tam_clave)
			{
				cursor_clave = 0;
				proximo_estado = 4; //Denegado
				
				if (comparar_claves())
				{
					proximo_estado = 6; //Nueva Clave
				}
			}
			
			break;
		
		case '#':
			copiar_arreglo(clave_mascara, clave_ingresada, tam_clave);
			cursor_clave = 0;
			proximo_estado = 1;
			break;
		
		default:
			break;
	}
	
	return proximo_estado;
}

unsigned char cambiar_clave_nueva_clave(uint8_t tecla)
{
	//Mostrar "Nueva" y  "*" por cada caracter ingresado. Se mantiene hasta haber ingresado una clave de 4 caracteres.
	unsigned char proximo_estado = 6;

	//seteo lo que se tenga que mostrar en el display
	mostrarArriba("Clave Nueva    ");
	refrescar_cursor_clave();

	switch (tecla)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':

			if (cursor_clave < tam_clave)
			{
				clave_ingresada[cursor_clave] = tecla;
				cursor_clave++;
			}
			break;
		
		case 'D':

			if (cursor_clave >= tam_clave)
			{
				copiar_arreglo(clave_ingresada, clave_actual, tam_clave);
				copiar_arreglo(clave_mascara, clave_ingresada, tam_clave);
				cursor_clave = 0;
				proximo_estado = 7;
			}
			break;
		
		case '#':
			copiar_arreglo(clave_mascara, clave_ingresada, tam_clave);
			cursor_clave = 0;
			proximo_estado = 1;
			break;
		
		default:
			break;
	}
	
	return proximo_estado;
}

unsigned char cambiar_clave_fin()
{
	unsigned char proximo_estado = 7;

	contador_interrupciones++;
	mostrarArriba("  Fin ingreso  ");
	mostrarAbajo("  nueva clave  ");

	if (contador_interrupciones > tres_segundos)
	{
		proximo_estado = 1;
		contador_interrupciones = 0;
	}

	return proximo_estado;
	
}

unsigned char modificar_hora(unsigned char *reloj, uint8_t tecla)
{
	unsigned char proximo_estado = 8;
	
	switch (tecla)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			mascara_reloj_conjelada[cursor_hora] = tecla;
			if (cursor_hora == 4)
				cursor_hora = 5;
			else
				cursor_hora = 4;
			mostrarArriba(mascara_reloj_conjelada);
			LCDGotoXY(cursor_hora,0);
			break;
		
		case 'A':
			modificar_reloj(reloj);
			cursor_hora = 4;
			LCDcursorOFF();
			proximo_estado = 1;
			break;
		
		case '#':
			copiar_arreglo(reloj_conjelado, reloj, 6);
			cursor_hora = 4;
			LCDcursorOFF();
			proximo_estado = 1;
			break;
		
		default:
			break;
	}
	
	return proximo_estado;
}

unsigned char modificar_minutos(unsigned char *reloj, uint8_t tecla)
{
	unsigned char proximo_estado = 9;
	
	switch (tecla)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':

			if (cursor_minutos == 7)
			{
				if (tecla <= '5')
				{
					mascara_reloj_conjelada[cursor_minutos] = tecla;
					cursor_minutos = 8;
				}
			}
			else
			{
				mascara_reloj_conjelada[cursor_minutos] = tecla;
				cursor_minutos = 7;
			}
			mostrarArriba(mascara_reloj_conjelada);
			LCDGotoXY(cursor_minutos,0);
			break;
		
		case 'B':
			modificar_reloj(reloj);
			cursor_minutos = 7;
			LCDcursorOFF();
			proximo_estado = 1;
			break;
		
		case '#':
			copiar_arreglo(reloj_conjelado, reloj, 6);
			cursor_minutos = 7;
			LCDcursorOFF();
			proximo_estado = 1;
			break;
		
		default:
			break;
	}
	
	return proximo_estado;
}

unsigned char modificar_segundos(unsigned char *reloj, uint8_t tecla)
{
	unsigned char proximo_estado = 10;
	
	switch (tecla)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		
			if (cursor_segundos == 10)
			{
				if (tecla <= '5')
				{
					mascara_reloj_conjelada[cursor_segundos] = tecla;
					cursor_segundos = 11;
				}
			}
			else
			{
				mascara_reloj_conjelada[cursor_segundos] = tecla;
				cursor_segundos = 10;
			}
			mostrarArriba(mascara_reloj_conjelada);
			LCDGotoXY(cursor_segundos,0);
			break;
		
		case 'C':
			modificar_reloj(reloj);
			cursor_hora = 4;
			LCDcursorOFF();
			proximo_estado = 1;
			break;
		
		case '#':
			copiar_arreglo(reloj_conjelado, reloj, 6);
			cursor_segundos = 10;
			LCDcursorOFF();
			proximo_estado = 1;
			break;
		
		default:
			break;
	}
	
	return proximo_estado;
}

unsigned char comparar_claves()
{
	char comparacion = 1;
	
	for (char cursor = 0; cursor < tam_clave; cursor++)
	{
		if (clave_ingresada[cursor] != clave_actual[cursor])
		{
			comparacion = 0;
			break;
		}
	}
	
	copiar_arreglo(clave_mascara,clave_ingresada,tam_clave);
	
	return comparacion;
}

void refrescar_mascara_reloj(unsigned char *reloj)
{
	mascara_reloj[4] = reloj[0] + '0';
	mascara_reloj[5] = reloj[1] + '0';
	mascara_reloj[7] = reloj[2] + '0';
	mascara_reloj[8] = reloj[3] + '0';
	mascara_reloj[10] =  reloj[4] + '0';
	mascara_reloj[11] =  reloj[5] + '0';

	mostrarArriba(mascara_reloj);
}

void modificar_reloj(unsigned char *reloj)
{
	unsigned char pre_reloj[] = {0,0,0,0,0,0};
		
	pre_reloj[0] = mascara_reloj_conjelada[4] - '0';
	pre_reloj[1] = mascara_reloj_conjelada[5] - '0';
	pre_reloj[2] = mascara_reloj_conjelada[7] - '0';
	pre_reloj[3] = mascara_reloj_conjelada[8] - '0';
	pre_reloj[4] = mascara_reloj_conjelada[10] - '0';
	pre_reloj[5] = mascara_reloj_conjelada[11] - '0';
	
	if (validar_reloj(pre_reloj))
		copiar_arreglo(pre_reloj,reloj,6);
}

void refrescar_cursor_clave()
{
	switch (cursor_clave)
	{
	case 0:
		mostrarAbajo("                ");
		break;
	
	case 1:
		mostrarAbajo("      *         ");
		break;
	
	case 2:
		mostrarAbajo("      **        ");
		break;
	
	case 3:
		mostrarAbajo("      ***       ");
		break;
	
	case 4:
		mostrarAbajo("      ****      ");
		break;
	
	default:
		mostrarAbajo("      OOB       ");
		break;
	}
}

void copiar_arreglo(uint8_t *origen, uint8_t *destino, int tam)
{
	int i = 0;
	for (i = 0; i < tam; i++)
	{
		destino[i] = origen[i];
	}
}

void set_temporizador_funciones(unsigned short intervalo_interrupcion) //establece la cantidad de interrupciones necesarias para la config. deseada.
{
    dos_segundos = (unsigned short) 2000/intervalo_interrupcion;
	tres_segundos = (unsigned short) 3000/intervalo_interrupcion;
}

char validar_reloj(unsigned char *reloj)
{
	char valido = 1;
	if (reloj[0] == 2 )
	{
		if (reloj[1] > 3)
		{
			valido = 0;
			return valido;
		}
	}
	if (reloj[0] > 2)
	{			
		valido = 0;
		return valido;
	}
	
	if (reloj[2] == 5)
	{
		if (reloj[3] > 5)
		{
			valido = 0;
			return valido;
		}
	}
	if (reloj[2] > 5)
	{
		valido = 0;
		return valido;
	}
	
	if (reloj[4] == 5)
	{
		if (reloj[5] > 5)
		{
			valido = 0;
			return valido;
		}
	}
	if (reloj[4] > 5)
	{
		valido = 0;
		return valido;
	}
	return valido;
}