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
static digit_to_check;
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
//    sendPWM(PORT, pin, period, DOOR_OPEN_DUTY_CYCLE);
}

static void closeDoor()
{
//    sendPWM(PORT, pin, period, DOOR_CLOSED_DUTY_CYCLE);
}

static void soundAlarm()
{

}

static uint16_t getCO2Level()
{
    uint16_t co2_level;
    
    // co2_level = (co2_raw_data - CO2_OFFSET) / CO2_FACTOR;
    
    return co2_level; // TODO scale between 0-100
}

static void checkInputs()
{   
    /* Ova funkcija treba da proveri sve ulazne signale (CO2 nivo, pokret, pritisak touchscreena/tastera itd.)
     * i da u skladu sa tim podesi kontrolne signal */
}

static void processKeyPressed()
{
    /* Ova funkcija treba da procesuira pritisnuti taster i poredi sa sifrom.
     * Ako je sifra ispravna, vrata treba otkljucati. U suprotnom, vrata ostaju zakljucana. */
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