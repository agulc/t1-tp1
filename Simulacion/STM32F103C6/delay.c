#include <delay.h>

void delay_ms(uint16_t time);
void delay_us(uint16_t time);

void delay_ms(uint16_t time)
{
	volatile unsigned long l = 0;
	uint16_t i;
	for (i = 0; i < time; i++)
	{
		for (l; l < 6000; l++);
	}
}

void delay_us(uint16_t time)
{
	volatile unsigned long l = 0;
	uint16_t i;
	for (i = 0; i < time; i++)
	{
		for (l; l < 6; l++);
	}
}
