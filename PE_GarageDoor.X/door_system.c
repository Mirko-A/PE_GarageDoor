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
static boolean  key_pressed;
static boolean  touch;

/* Action flags */
static boolean turn_on_light;
static DoorState door_state;

/* Turn off times */
static uint32_t light_turn_off_time = 0;
static uint32_t door_relock_time = 0;

/* LOCAL FUNCTIONS */
static void initializePins(void)
{
    /* Servo motor izlaz */
    TRISDbits.TRISD8 = OUTPUT_PIN;
    /* Light izlaz */
    TRISCbits.TRISC15 = OUTPUT_PIN;
    /* Buzzer/alarm pwm pin */
    TRISAbits.TRISA11 = OUTPUT_PIN;
    /* Alarm LED pin */
    TRISFbits.TRISF6 = OUTPUT_PIN;
    /* Senzor PIR ulaz */
    TRISDbits.TRISD9 = INPUT_PIN;
    
    /* Inicijalizuj PORTB pinove kao digital+input (ADC ce kasnije prepisati one koji su mu potrebni) 
     * Koriste se za tastere (B8~B11) i alarm LED (B12)
     */
    ADPCFG = 0xFFFF;
    TRISB = 0xFFFF;
}

static void openDoor(void)
{
    servoPwmSend(200, DOOR_OPEN_DUTY_CYCLE);
}

static void closeDoor(void)
{
    servoPwmSend(200, DOOR_CLOSED_DUTY_CYCLE);
}

static void startAlarm(void)
{
    // Buzzer period used with PWM signal to generate buzzing of certain pitch
    static uint8_t buzzer_period = BUZZER_HIGH_PITCH_PERIOD;
    
    uint32_t ms_ticks = getTickMs();
    
    // Toggle alarm LED
    if (((ms_ticks + 1) % ALARM_LED_PERIOD) == 0)
    {
        if (ALARM_LED_PIN_GET == PIN_LOW)
        {
            ALARM_LED_PIN_SET = PIN_HIGH;
        } else
        {
            ALARM_LED_PIN_SET = PIN_LOW;
        }
    }
    
    if (((ms_ticks + 1) % BUZZER_SWITCH_PERIOD) == 0)
    {
        buzzer_period = (buzzer_period == BUZZER_HIGH_PITCH_PERIOD) ? BUZZER_LOW_PITCH_PERIOD : BUZZER_HIGH_PITCH_PERIOD;
    }
    
    buzzerPwmSend(buzzer_period);
    
    // Half-open door so CO2 can go out
    servoPwmSend(200, DOOR_HALF_OPEN_DUTY_CYCLE);
}

/* Funckija vraca nivo CO2 ogranicen na opseg 0-100 */
static uint8_t getCo2Level(void)
{
    uint8_t co2_level = 0;
    
    co2_level = (uint8_t) ((co2_raw_data * 100) / CO2_FACTOR);
	
    /* Ogranicavamo co2_level na opseg 0-100 (za slucaj da je faktor pogresan) */
    if (co2_level > 100) co2_level = 100;
    
    return co2_level; // TODO scale between 0-100

    // TODO testing alarm, remove later
//    uint32_t ms_ticks = getTickMs();
//    static uint8_t co2_level = 0;
//    
//    if ((ms_ticks % 512) == 0)
//    {
//        co2_level = co2_level + 5;
//        
//        if (co2_level > 100)
//        {
//            co2_level = 0;
//        }
//    }
//    
//    return co2_level;
}

/* Ova funkcija vraca nivo osvetljenosti u okolini skaliran od 0-100
 * Ulaz joj je signal fotootpornika */
static uint8_t getEnvLightLevel(void)
{
    // TODO fotooptornik testiranje
    uint8_t env_light_level = 0;
    
    env_light_level = (photores_raw_data*100)/PHOTO_RES_FACTOR;
    
    /* Ogranicavamo nivo svetlosti u okolini na opseg 0-100 (za slucaj da je faktor pogresan) */
    if (env_light_level > 100) env_light_level = 100;
    
//    return env_light_level; TODO
    return 70;
}

/* Ova funkcija treba da proveri sve ulazne signale (CO2 nivo, pokret, pritisak touchscreena/tastera itd.)
 * i da u skladu sa tim podesi kontrolne signal */
static void checkInputs(void)
{
    /* Pomocni fleg, dodatak softverskom diferenciranju */
    static boolean key_processed = FALSE;
    
    uint8_t env_light_level = getEnvLightLevel();
	uint8_t co2_level = getCo2Level();
    
    /* Deo koda koji postavlja flag start_alarm na 0 ili 1 u zavisnosti od CO2 nivoa*/
	if(co2_level >= CO2_UNSAFE_LEVEL)
    {
        door_state = ALARM_STATE;
        /* Ukljuci tajmer 4 zbog PWM-a za Buzzer */
        BUZZER_TIMER_START;
    }
	else if(co2_level <= CO2_SAFE_LEVEL)
    {
        door_state = DOOR_CLOSED;
        ALARM_LED_PIN_SET = PIN_LOW;
        /* Iskljuci tajmer 4 da bi Buzzer stao */
        BUZZER_TIMER_STOP;
    }
	
	/* Deo koda koji postavlja flag turn_on_light na 0 ili 1 u zavisnosti od senzora pokreta */
    if (MOTION_PIN_GET == PIN_HIGH)
    {
        if (env_light_level < ENV_LIGHT_THRESHOLD) turn_on_light = TRUE;
    }
	
	/* Deo koda koji stavlja key_pressed na true ili false na osnovu pritiska tastera */
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
    updateCoords();
    
    if ((getY() != 0) || (getX() != 0))
    {
        touch = TRUE;
    }
    else
    {
        touch = FALSE;
    }
}

/* Funckija vraca trenutni pritisnut taster (B9~B12) kao brojeve 1~4 ili 0xFF ako nijedan 
 * od tastera nije pritisnut
 */
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
static void processKeyPressed(void)
{
    uint8_t key;
    
    /* Procitaj trenutni pritisnut taster 
     * Tasteri su B9~B12 pa oduzimamo broj 8 kako bi dobili brojeve 1~4
     */
    key = getKey();
    
    /* Taster nije validan */
    if (key == 0xFF) return;
    
    /* Taster odgovara cifri u passwordu */
    if (key == password[digit_to_check])
    {
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

static void processTouch(void)
{
	/* provera da li smo u delu ekrana gde su dugmici */
	if(getY() < LCD_ICON_Y_MAX)
	{
        unsigned int x_pos = getX();
        
		/* provera koje dugme */
		if(x_pos <= DOOR_OPEN_ICON_END)
		{
			/* Sector 1 - Open door */
			if (door_locked == FALSE) door_state = DOOR_OPEN;
		}
        else if((x_pos > DOOR_OPEN_ICON_END) && (x_pos <= DOOR_CLOSE_ICON_END))
		{
			/* Sector 2 - Close door */
			door_state = DOOR_CLOSED;
		}
		else if((x_pos > DOOR_CLOSE_ICON_END) && (x_pos <= LIGHT_SWITCH_ICON_END))
		{
			/* Sector 3 - Light ON/OFF */
            turn_on_light = (turn_on_light == FALSE) ? TRUE : FALSE;
		}
		else if(x_pos > LIGHT_SWITCH_ICON_END)
		{
			/* Sector 4 - Alarm OFF */
			door_state = DOOR_CLOSED;
		}
	}
}

/* Ova funkcija treba da proverava kontrolne signale i da u skladu sa tim izvrsava odredjene 
 * radnje. */
static void performActions(void)
{   
    uint32_t ms_ticks = getTickMs();
    
    if (door_state == DOOR_OPEN)
    {
        openDoor();
    }
    else if (door_state == DOOR_CLOSED)
    {
        closeDoor();
    }
    else if (door_state == ALARM_STATE)
    {
        startAlarm();
    }
    
    if (turn_on_light == TRUE)
    {
        // Movement detected => turn on light
        LIGHT_PIN_SET = PIN_HIGH;
        // Light will turn off after 10s
        light_turn_off_time = ms_ticks + 10000;
        // Movement processed => clear flag
        turn_on_light = FALSE;
    }
}

/* Ova funkcija treba da proverava kontrolne signale i da u skladu sa tim stopira odredjene 
 * radnje. */
static void stopActions(void)
{
    uint32_t ms_ticks = getTickMs();
    
    if (ms_ticks == light_turn_off_time)
    {
        if (LIGHT_PIN_GET == PIN_HIGH)
        {
            LIGHT_PIN_SET = PIN_LOW;
        }
    }
    
    if (ms_ticks == door_relock_time)
    {
        if (door_state != ALARM_STATE)
        {
            door_state = DOOR_CLOSED;
            door_locked = TRUE;    
        }
    }
}

static void taskLcd(void)
{
    if (touch) processTouch();
    
    LcdUpdateDisplay(getCo2Level(), door_locked);
}

/* GLOBAL FUNCTIONS */
void doorSystemInit(void)
{
    door_state    = DOOR_CLOSED;
    door_locked   = TRUE;
    turn_on_light = FALSE;
    
    initializePins();
    
    initTimers();
    uartInit();
    initADC();
    LcdInit();
    initTouchscreen();
}

void doorSystemRun(void)
{
    checkInputs();
    
    if (key_pressed == TRUE) processKeyPressed();
    
    taskLcd();
    
    performActions();
    
    stopActions();
}