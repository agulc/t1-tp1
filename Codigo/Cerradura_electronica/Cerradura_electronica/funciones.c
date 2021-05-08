/*Este programa es la maquina de estados principal que controla la parte interactiva de la cerradura.
Para mas información, ver la documentación del proyecto*/

unsigned char pantalla_principal(uint8_t tecla);
unsigned char ingresar_clave_entrada(uint8_t tecla);
unsigned char comparar_claves();

uint8_t clave_mascara[] = {'x','x','x','x'} ;
uint8_t clave_ingresada[] = clave_mascara ;
uint8_t clave_nueva[] = clave_mascara ;
uint8_t clave_actual[] = {'0','8','5','2'} ;
char cursor_clave = 0;
char tam_clave = (char) sizeof(clave_mascara)/sizeof(clave_mascara[0]) - 1;


void mef_funciones(unsigned char *masc_reloj, uint8_t tecla)//Analizar que devería recibir una vez establecido el modulo LCD
{

}

unsigned char pantalla_principal(uint8_t tecla)
{
    // Mostrar Hora y "CERRADO", se espera una entrada por teclado. La hora es obtenida de una mascara comandada por la MEF Reloj.
    unsigned char proximo_estado = 1;

    //seteo lo que se tenga que mostrar en el display

    switch (tecla)
    {
		case '0','1','2','3','4','5','6','7','8','9':
			clave_ingresada[cursor_clave] = tecla;
			cursor_clave++;
			proximo_estado = 2; //Ingresar clave entrada
			break;
		
		case 'A':
			proximo_estado = 8; //Modificar hora
			break;
		
		case 'B':
			proximo_estado = 9; //Modificar minutos
			break;
		
		case 'C':
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
	
	switch (tecla)
	{
		case '0','1','2','3','4','5','6','7','8','9':
			clave_ingresada[cursor_clave] = tecla;
			cursor_clave++;
			
			if (cursor_clave > tam_clave)
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
	
	clave_ingresada = clave_mascara;
	
	return comparacion;
}