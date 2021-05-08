/*Este programa es la maquina de estados principal que controla la parte interactiva de la cerradura.
Para mas información, ver la documentación del proyecto*/

uint8_t clave_mascara[] = {'x','x','x','x'} ;
uint8_t clave_ingresada[] = clave_mascara ;
uint8_t clave_nueva[] = clave_mascara ;
uint8_t clave_actual[] = {'0','8','5','2'} ;



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
	
		clave_ingresada[0] = tecla;
		proximo_estado = 2;
        break;
	
	case 'A':
	
		proximo_estado = 8;
		break;
		
	case 'B':
	
		proximo_estado = 9;
		break;
	
	case 'C':
		
		proximo_estado = 10;
		break;
	
	case 'D':
	
		proximo_estado = 5;
		break;
    
    default:
        break;
    }
	
	return proximo_estado;
}