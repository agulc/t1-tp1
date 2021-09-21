#include <mef.h>

static uint8_t state = 1;
static char clock_mask[16];
static uint8_t password_cursor = 0;
uint8_t password_input[] = {'x','x','x','x'};
uint8_t password[] = {'4','3','2','1'};
uint8_t tick_counter = 0;


void mef_functions(uint8_t key);
uint8_t mef_main_menu(uint8_t key);
uint8_t mef_input_password(uint8_t key);
uint8_t mef_open(void);
uint8_t mef_denied(void);
void mef_refresh_password_cursor(void);
void mef_refresh_password_cursorvoid(void);
uint8_t mef_check_password(void);

void mef_functions(uint8_t key)
{
    switch (state)
    {
        case 1:
            state = mef_main_menu(key);
            break;
        case 2:
            state = mef_input_password(key);
            break;
        case 3:
            state = mef_open();
            break;
        case 4:
            state = mef_denied();
            break;
        default:
            state = mef_main_menu(key);
            break;
    }
}

uint8_t mef_main_menu(uint8_t key)
{
    uint8_t next_state = 1;
    clock_read(clock_mask);
    lcd_load_buffer_high(clock_mask, strlen(clock_mask));
    lcd_load_buffer_low("    Cerrado    ", strlen("    Cerrado    "));

    switch (key)
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
            password_input[password_cursor] = key;
            password_cursor++;
            next_state = 2;
            break;
        
        default:
            break;
    }

    return next_state;
}

uint8_t mef_input_password(uint8_t key)
{
    uint8_t next_state = 2;
    lcd_load_buffer_high("Ingrese clave: ", strlen("Ingrese clave: "));
    mef_refresh_password_cursor();

    switch (key)
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
			password_input[password_cursor] = key;
			password_cursor++;
			
			if (password_cursor >= 4)
			{
				password_cursor = 0;
				next_state = 4; //Denegado
				
				if (mef_check_password())
				{
					next_state = 3; //Abierto
				}
			}
			break;
		
		default:
			break;
    }

    return next_state;
}

uint8_t mef_open(void)
{
    uint8_t next_state = 3;

    tick_counter++;
    lcd_load_buffer_high("               ", strlen("               "));
    lcd_load_buffer_low("    Abierto    ", strlen("    Abierto    "));
    
    if (tick_counter > 10)
    {
        next_state = 1;
        tick_counter = 0;
    }

    return next_state;

}

uint8_t mef_denied(void)
{
    uint8_t next_state = 4;

    tick_counter++;
    lcd_load_buffer_high("               ", strlen("               "));
    lcd_load_buffer_low("   DENEGADO    ", strlen("   DENEGADO    "));
    
    if (tick_counter > 4)
    {
        next_state = 1;
        tick_counter = 0;
    }

    return next_state;

}

void mef_refresh_password_cursor(void)
{
    switch (password_cursor)
	{
	case 0:
	    lcd_load_buffer_low("                ", strlen("                "));
		break;
	
	case 1:
	    lcd_load_buffer_low("      *         ", strlen("      *         "));
		break;
	
	case 2:
	    lcd_load_buffer_low("      **        ", strlen("      **        "));
		break;
	
	case 3:
	    lcd_load_buffer_low("      ***       ", strlen("      ***       "));
		break;
	
	case 4:
	    lcd_load_buffer_low("      ****      ", strlen("      ****      "));
		break;
	
	default:
	    lcd_load_buffer_low("      OOB       ", strlen("      OOB       "));
		break;
	}
}

uint8_t mef_check_password(void)
{
    uint8_t i;
    uint8_t result = 1;

    for (i = 0; i < 4; i++)
    {
        if (password_input[i] != password[i])
        {
            result = 0;
        }
    }

    return result;
}
