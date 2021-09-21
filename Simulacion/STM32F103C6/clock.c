#include <clock.h>

static char time_mask[] = {1,6,1,9,5,9};
char clock_base[] = "    HH:MM:SS    ";

void clock_tick(void)
{

time_mask[5]++;

    if (time_mask[5] > 9)
    {
        time_mask[5] = 0;
        time_mask[4]++;

        if (time_mask[4] > 5)
        {
            time_mask[4] = 0;
            time_mask[3]++;

            if (time_mask[3] > 9)
            {
                time_mask[3] = 0;
                time_mask[2]++;

                if (time_mask[2] > 5)
                {
                    time_mask[2] = 0;
                    time_mask[1]++;

                    if (time_mask[0] >= 2)
                    {
                        if (time_mask[1] >= 4)
                        {
                            time_mask[1] = 0;
                            time_mask[0] = 0;
                        }
                    }
                    else
                    {
                        if (time_mask[1] > 9)
                        {
                            time_mask[1] = 0;
                            time_mask[0]++;     
                        }
                    }
                }
            }
        }
    }
}

void clock_read(char *str)
{
    clock_base[4] = '0' + time_mask[0];
    clock_base[5] = '0' + time_mask[1];
    clock_base[7] = '0' + time_mask[2];
    clock_base[8] = '0' + time_mask[3];
    clock_base[10] = '0' + time_mask[4];
    clock_base[11] = '0' + time_mask[5];

    strcpy(str, clock_base);
}

