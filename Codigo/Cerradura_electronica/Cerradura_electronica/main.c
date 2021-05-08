#include "lcd.h"
#include "key.h"			
//este test de funcionamiento del teclado es para probarlo con el proteus, con un keypad-smallcalc modificado y con un LCD LM016L
void testeo_del_teclado()
{
		LCDinit();
		LCDGotoXY(0,0);
		while (1)
		{
			uint8_t tecla=0;
			//programa de testeo del KEYPAD_scan
			if(KEYPAD_Update(&tecla)){
				LCDsendChar(tecla);
			}
			_delay_ms(10);
		}
}
int main(void)
{
	testeo_del_teclado();
	return 0;
}




