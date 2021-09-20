#include <stm32f103x6.h>
#include <keypad.h>

//4x4 keypad controller
uint8_t keypad_update (uint8_t *pkey);
uint8_t keypad_scan (uint8_t *pkey);
uint16_t keypad_get_imput (void);
uint8_t keypad_refference (uint8_t reading);
uint8_t reading = 0;

void delay_ms(uint16_t time);

void delay_ms(uint16_t time)
{
	volatile unsigned long l = 0;
	uint16_t i;
	for (i = 0; i < time; i++)
	{
		for (l; l < 6000; l++);
	}
}

uint8_t keypad_update (uint8_t *pkey)
{
	static uint8_t Old_key, Key, Last_valid_key = 0xFF; // no key pressed
	
    if (!keypad_scan (&Key))
    {
		Old_key = 0xFF; // no key pressed
		Last_valid_key = 0xFF;
		return 0;
	}

	if (Key == Old_key) 
    { //2nd verification
        if (Key != Last_valid_key)
        { //avoids double key press
			*pkey = Key;
			Last_valid_key = Key;
			return 1;
		}
	}

	Old_key = Key; //first verification

	return 0;
}

uint8_t keypad_scan (uint8_t *pkey)
{
      uint16_t i, input;

     for (i = 0; i < 4; i++)
     {
	GPIOB -> ODR = ~(1 << (12 + i));
	input = keypad_get_imput();
	if (input != 0x0F00)
	{
		*pkey = keypad_refference ((GPIOB -> IDR) >> 8); // ~((1 << 4) | 0x0F) | input;
		return 1;          
	}
	GPIOB -> ODR |= 1 << (12 + i);
      }
     
    return 0;
}

uint16_t keypad_get_imput ()
{
    uint16_t reading = (GPIOB -> IDR & 0x0F00);
    return reading;
}

uint8_t keypad_refference (uint8_t reading)
{
	uint8_t key=1;
	switch (reading)
	{
		case 0x77: key='1';break;
		case 0x7B: key='2';break;
		case 0x7D: key='3';break;
		case 0x7E: key='A';break;
		
		case 0xB7: key='4';break;
		case 0xBB: key='5';break;
		case 0xBD: key='6';break;
		case 0xBE: key='B';break;
		
		case 0xD7: key='7';break;
		case 0xDB: key='8';break;
		case 0xDD: key='9';break;
		case 0xDE: key='C';break;
		
		case 0xE7: key='*';break;
		case 0xEB: key='0';break;
		case 0xED: key='#';break;
		case 0xEE: key='D';break;
		default:
		    key=1;
	}
	return key;
}
