#include "reloj.c"

int test(void)
{
	set_temporizador(500);
	
	unsigned char masc[] = {0,0,0,0,0,0};
	
    while (1) 
    {
		  MEF_reloj(masc);
    }
}

