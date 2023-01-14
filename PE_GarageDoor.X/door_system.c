/* 
 * File:   door_system.c
 * Author: 
 *
 * Created on December 25, 2022, 2:55 PM
 */

#include "door_system.h"

/* LOCAL VARIABLES */

/* Door lock data */
static const uint8_t password[PASSWORD_LENGTH] = {1, 2, 3, 4};
static uint8_t digit_to_check = 0;
static boolean door_locked;

/* Sensor input */
static boolean  movement;
static boolean  key_pressed;
static boolean  touch;

/* Action flags */
static boolean turn_on_light;
static boolean open_door;
static boolean start_alarm;

/* Turn off times */
static uint32_t led_turn_off_time = 0;
static uint32_t door_relock_time = 0;

static void initializePins(void)
{
    // Servo motor izlaz
    TRISDbits.TRISD8 = 0;
    // Senzor PIR ulaz
    TRISDbits.TRISD9 = 1;
    // LED izlaz
    TRISCbits.TRISC15 = 0;
    
    // Input pin for testing TODO change/remove
    TRISAbits.TRISA11 = 1;
    
    // Test for buttons TODO maybe change? works fine like this bcs initADC will overwrite
    ADPCFG = 0xFFFF;
    TRISB = 0xFFFF;
}

/* LOCAL FUNCTIONS */
static void openDoor()
{
    servoPwmSend(200, DOOR_OPEN_DUTY_CYCLE);
}

static void closeDoor()
{
    servoPwmSend(200, DOOR_CLOSED_DUTY_CYCLE);
}

static void startAlarm()
{
    // if (((getTickMs() + 1) % ALARM_LED_PERIOD) == 0) togglePin(PORTA, ALARM_LED_PIN);
    servoPwmSend(200, DOOR_HALF_OPEN_DUTY_CYCLE);
}

static uint8_t getCo2Level()
{
    uint8_t co2_level = 0;
    
    co2_level = (uint8_t) ((co2_raw_data * 100) / CO2_FACTOR);
	
    /* Ogranicavamo co2_level na opseg 0-100 */
    if (co2_level > 100) co2_level = 100;
    
    return co2_level; // TODO scale between 0-100
}

/* Ova funkcija treba da proveri sve ulazne signale (CO2 nivo, pokret, pritisak touchscreena/tastera itd.)
 * i da u skladu sa tim podesi kontrolne signal */
static void checkInputs()
{
    /* Pomocni fleg, dodatak softverskom diferenciranju */
    static boolean key_processed = FALSE;
    
	/* Deo koda koji postavlja flag start_alarm na 0 ili 1 u zavisnosti od CO2 nivoa*/
	uint8_t co2_level = getCo2Level();
    
	if(co2_level >= CO2_MAX_LEVEL)
    {
        start_alarm = TRUE;
    }
	else if(co2_level <= CO2_MIN_LEVEL)
    {
        start_alarm = FALSE;
    }
	
	/* Deo koda koji postavlja flag turn_on_light na 0 ili 1 u zavisnosti od senzora pokreta*/
    if (MOTION_PIN_GET == PIN_HIGH)
    {
        turn_on_light = TRUE;
    }
	
	/* Deo koda koji stavlja key_pressed na true ili false na osnovu pritiska tastera*/
	if(BUTTONS != 0)
	{
        if (key_processed == FALSE)
        {
            key_pressed = TRUE;
            key_processed = TRUE;
        } 
        else
        {
            key_pressed = FALSE;
        }
    }	
	else
    {
        key_pressed = FALSE;
        key_processed = FALSE;
    }
    
    /* Deo koda koji stavlja touch na true ili false na osnovu pritiska touchscreen-a */
    //updateCoords();
    
    if ((getY() != 0) || (getX() != 0))
    {
        touch = TRUE;
    }
    else
    {
        touch = FALSE;
    }
    
    // TODO test, remove later
    if (PORTAbits.RA11)
    {
        if (door_locked == FALSE) open_door = TRUE;
    }
}

static uint8_t getKey(void)
{
    if      (PORTBbits.RB9  == PIN_HIGH) return 1;
    else if (PORTBbits.RB10 == PIN_HIGH) return 2;
    else if (PORTBbits.RB11 == PIN_HIGH) return 3;
    else if (PORTBbits.RB12 == PIN_HIGH) return 4;
    else return 0xFF;
}

/* Ova funkcija treba da procesuira pritisnuti taster i poredi sa sifrom.
 * Ako je sifra ispravna, vrata treba otkljucati. U suprotnom, vrata ostaju zakljucana. */
static void processKeyPressed()
{
    uint8_t key;
    
    /* Procitaj trenutni pritisnut taster 
     * Tasteri su B9~B12 pa oduzimamo broj 8 kako bi dobili brojeve 1~4
     */
    key = getKey();
    
    /* Taster nije validan */
    if (key == 0xFF) return;
    
    // TODO testing only, remove later
    uint8_t key_str[4];
    uint8_t curr_pos[4];
    sprintf(key_str, "%d", key);
    sprintf(curr_pos, "%d", digit_to_check);
    uartWriteString("Key pressed: ");
    uartWriteString(key_str);
    uartWriteString("Current position: ");
    uartWriteString(curr_pos);
    uartWriteString("\r\n");
    
    /* Taster odgovara cifri u passwordu */
    if (key == password[digit_to_check])
    {
        // TODO testing only, remove later
        uartWriteString("****");
        uartWriteString("HIT");
        uartWriteString("****\r\n");
        /* Ukucan je ispravan password */
        if (digit_to_check == (PASSWORD_LENGTH - 1))
        {
            /* Otkljucaj vrata */
            door_locked = FALSE;
            door_relock_time = getTickMs() + 15000;
            
            digit_to_check = 0;
        } 
        else
        {
            /* Proveri sledecu cifru u passwordu */
            digit_to_check++;   
        }
    } 
    else
    {
        /* Pogresna sifra => zakljucaj vrata */
        door_locked = TRUE; 
        digit_to_check = 0;
    }
}

static void processTouch()
{
	/* provera da li smo u delu ekrana gde su dugmici */
	if(getY() > (Y_MAX/2))
	{
        unsigned int x_pos = getX();
        
		/* provera koje dugme */
		if(x_pos < 32)
		{
			/* Sector 1 - Light ON/OFF */
            turn_on_light = (turn_on_light == FALSE) ? TRUE : FALSE;
		}
        else if((x_pos > 32) && (x_pos < 64))
		{
			/* Sector 2 - Alarm OFF */
			start_alarm = FALSE;
			
		}
		else if((x_pos > 64) && (x_pos < 96))
		{
			/* Sector 3 - Close door */
			open_door = FALSE;
		}
		else if(x_pos > 96)
		{
			/* Sector 4 - Open door */
			open_door  = TRUE;
		}
	}
}

/* Ova funkcija treba da proverava kontrolne signale i da u skladu sa tim izvrsava odredjene 
 * radnje. */
static void performActions()
{   
    uint32_t ticks = getTickMs();
    
    if (open_door == TRUE)
    {
        openDoor();
    }
    else
    {
        closeDoor();
    }
    
    if (turn_on_light == TRUE)
    {
        LED_PIN_SET = PIN_HIGH;
        led_turn_off_time = ticks + 10000;
    }
}

/* Ova funkcija treba da proverava kontrolne signale i da u skladu sa tim stopira odredjene 
 * radnje. */
static void stopActions()
{
    uint32_t ticks = getTickMs();
    
    if (ticks == led_turn_off_time)
    {
        if (turn_on_light == TRUE)
        {
            turn_on_light = FALSE;
            LED_PIN_SET = PIN_LOW;
        }
    }
    
    if (ticks == door_relock_time)
    {
        if (start_alarm == FALSE)
        {
            open_door = FALSE;
            door_locked = TRUE;    
        }
    }
}

static void taskLcd()
{
    if (touch) processTouch();
    
    LcdUpdateDisplay(getCo2Level(), door_locked);
}

/* GLOBAL FUNCTIONS */
void doorSystemInit()
{
    movement      = FALSE;
    open_door     = FALSE;
    door_locked   = TRUE;
    start_alarm   = FALSE;
    turn_on_light = FALSE;
    
    initializePins();
    
    initTimer1();
    initTimer2();
    initTimer3();
    uartInit();
    initADC();
    LcdInit();
    initTouchscreen();
}

void doorSystemRun()
{
    checkInputs();
    
    if (key_pressed == TRUE) processKeyPressed();
    
    taskLcd();
    
    performActions();
    
    stopActions();
}