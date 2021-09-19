#include <stm32f103x6.h>
#include <keypad.h>

//4x4 keypad controller
uint8_t keypad_update (uint8_t *pkey);
uint8_t keypad_scan (uint8_t *pkey);
uint8_t keypad_get_imput (void);
uint8_t keypad_refference (uint8_t lectura);
uint8_t reading = 0;

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
    uint32_t key_port = keypad_get_imput ();

    if (key_port == 0xFF) return 0;

    *pkey = keypad_refference (key_port);
    return 1;
}

uint8_t keypad_get_imput ()
{
    reading = (GPIOB -> IDR);
    return reading;
}

uint8_t keypad_refference (uint8_t reading)
{
	uint8_t key=1;
	/*switch (reading)
	{
		case 0b01110111: key='1';break;
		case 0b01111011: key='2';break;
		case 0b01111101: key='3';break;
		case 0b01111110: key='A';break;
		
		case 0b10110111: key='4';break;
		case 0b10111011: key='5';;break;
		case 0b10111101: key='6';break;
		case 0b10111110: key='B';break;
		
		case 0b11010111: key='7';break;
		case 0b11011011: key='8';break;
		case 0b11011101: key='9';break;
		case 0b11011110: key='C';break;
		
		case 0b11100111: key='*';break;
		case 0b11101011: key='0';break;
		case 0b11101101: key='#';break;
		case 0b11101110: key='D';break;
	}*/
	return key;
}
