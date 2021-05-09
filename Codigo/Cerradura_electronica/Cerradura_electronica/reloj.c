/*El siguiente modulo espera una determinada cantidad de interrupciones de reloj. Cuando sucede dicha cantidad de interrupciones,
el modulo actualiza una mascara de reloj (masc_reloj) que es recivida como parametro mediante un puntero, para luego ser mostrada
en pantalla por la MEF funciones*/

volatile unsigned char estado_MEF = 1;
unsigned short un_segundo = 10; //Suponer que 1int = 100ms
unsigned char contador_interrupciones_reloj = 0;

void set_temporizador(unsigned short intervalo_interrupcion) //establece la cantidad de interrupciones necesarias para la config. deceada.
{
    un_segundo = (unsigned short) 1000/intervalo_interrupcion;
    
    if (!un_segundo)
    {
        un_segundo  =  1;
    }   
}


void MEF_reloj(unsigned char *masc_hora) //formato: unsigned char masc_hora[] = {0,0,0,0,0,0};
{

    switch (estado_MEF)
    {

    case 1: //Reloj quieto

        estado_MEF = 1;
        contador_interrupciones_reloj++;

        if (un_segundo <= contador_interrupciones_reloj)
        {
            contador_interrupciones_reloj = 0;
            estado_MEF = 2;
        }

        break;

    case 2: //Incrementar HH:MM:SS

        estado_MEF = 1;
        contador_interrupciones_reloj++;

        masc_hora[5]++;

        if (masc_hora[5] > 9)
        {
            masc_hora[5] = 0;
            masc_hora[4]++;

            if (masc_hora[4] > 5)
            {
                masc_hora[4] = 0;
                masc_hora[3]++;

                if (masc_hora[3] > 9)
                {
                    masc_hora[3] = 0;
                    masc_hora[2]++;

                    if (masc_hora[2] > 5)
                    {
                        masc_hora[2] = 0;
                        masc_hora[1]++;

                        if (masc_hora[1] > 9)
                        {
                            masc_hora[1] = 0;
                            masc_hora[0]++;

                            if (masc_hora[0] > 2)
                            {
                                masc_hora[0] = 0;
                            }
                        }
                    }
                }
            }
        }

        break;

    default:
        break;
    }
}