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

static uint16_t getCO2Level()
{
    uint16_t co2_level;
    
    // co2_level = co2_raw_data / CO2_FACTOR;
    
    return co2_level; // TODO scale between 0-100
}

static void checkInputs()
{   
    /* Ova funkcija treba da proveri sve ulazne signale (CO2 nivo, pokret, pritisak touchscreena/tastera itd.)
     * i da u skladu sa tim podesi kontrolne signal */
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

static void processTouchscreen()
{
    /* Ova funkcija treba da proveri sta je pritisnuto na LCD-u  */
}

static void performActions()
{
    /* Ova funkcija treba da proverava kontrolne signale i da u skladu sa tim izvrsava odredjene 
     * radnje. */
}

static void stopActions()
{
    /* Ova funkcija treba da proverava kontrolne signale i da u skladu sa tim stopira odredjene 
     * radnje. */
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
}

void doorSystemRun()
{
    checkInputs();
    
    processKeyPressed();
    
    performActions();
    
    stopActions();
}