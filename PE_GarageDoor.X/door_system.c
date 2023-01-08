/* 
 * File:   door_system.c
 * Author: 
 *
 * Created on December 25, 2022, 2:55 PM
 */

#include "door_system.h"

/* LOCAL VARIABLES */

/* Door lock data */
static const uint8_t password[PASSWORD_LENGTH] = {0, 8, 0, 3};
static uint8_t digit_to_check;
static boolean door_locked;

/* Sensor input */
static boolean  movement;
static boolean  key_pressed;
static boolean  touch;
static uint16_t gas_level;

/* Action flags */
static boolean turn_on_light;
static boolean open_door;
static boolean start_alarm;

/* LOCAL FUNCTIONS */
static void openDoor()
{
    sendPWM(20, DOOR_OPEN_DUTY_CYCLE);
}

static void closeDoor()
{
    sendPWM(20, DOOR_CLOSED_DUTY_CYCLE);
}

static void startAlarm()
{
    // if ((getTicks() % ALARM_LED_PERIOD) == 0) togglePin(PORTA, ALARM_LED_PIN);
    sendPWM(20, DOOR_HALF_OPEN_DUTY_CYCLE);
}

static uint8_t getCO2Level()
{
    uint8_t co2_level;
    
    co2_level = (uint8_t) (co2_raw_data / CO2_FACTOR);
    
    return co2_level; // TODO scale between 0-100
}

/* Ova funkcija treba da proveri sve ulazne signale (CO2 nivo, pokret, pritisak touchscreena/tastera itd.)
 * i da u skladu sa tim podesi kontrolne signal */
static void checkInputs()
{   
    updateCoords();
    if (getX() > 0 || getY() > 0) touch = TRUE;
}

/* Ova funkcija treba da procesuira pritisnuti taster i poredi sa sifrom.
 * Ako je sifra ispravna, vrata treba otkljucati. U suprotnom, vrata ostaju zakljucana. */
static void processKeyPressed()
{
    static uint16_t old_key;
    uint16_t key_pressed;
    
    /* Procitaj trenutni pritisnut taster */
    key_pressed = PORTB;
    
    /* Taster je zadrzan ali je vec procesuiran */
    if (key_pressed == old_key) return;
    
    /* Taster odgovara cifri u passwordu */
    if (key_pressed == password[digit_to_check])
    {
        /* Ukucan je ispravan password */
        if (digit_to_check == (PASSWORD_LENGTH - 1))
        {
            /* Otkljucaj vrata */
            door_locked = FALSE;
            
            digit_to_check = 0;
        } else
        {
            /* Proveri sledecu cifru u passwordu */
            digit_to_check++;   
        }
    } else
    {
        /* Pogresna sifra => zakljucaj vrata */
        door_locked = TRUE;
        
        digit_to_check = 0;
    }
    
    /* Sacuvaj trenutni pritisnut taster za sledeci poziv funkcije (de-bouncing) */
    old_key = key_pressed;
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

}

/* Ova funkcija treba da proverava kontrolne signale i da u skladu sa tim stopira odredjene 
 * radnje. */
static void stopActions()
{

}

static void taskLcd()
{
    if (touch) processTouch();
    
    LcdUpdateCo2Bar(getCO2Level());
}

/* GLOBAL FUNCTIONS */
void doorSystemInit()
{
    movement      = FALSE;
    open_door     = FALSE;
    door_locked   = TRUE;
    start_alarm   = FALSE;
    turn_on_light = FALSE;
    
    gas_level      = 0u;
    digit_to_check = 0;
    
    closeDoor();
    
    initTimer1(ONE_MS_PERIOD);
    initTimer2();
    initADC();
    LcdInit();
    initTouchscreen();
}

void doorSystemRun()
{
    checkInputs();
    
    if (key_pressed) processKeyPressed();
    
    taskLcd();
    
    performActions();
    
    stopActions();
}