/* 
 * File:   door_system.c
 * Author: 
 *
 * Created on December 25, 2022, 2:55 PM
 */

#include "door_system.h"

/* LOCAL VARIABLES */

/* Door lock data */
static const uint8_t password[PASSWORD_LENGTH] = {2, 1, 1, 2};
static const uint8_t secret_key[SECRET_KEY_LEN] = "Sezame!";
static uint8_t digit_to_check = 0;
static boolean door_locked;

/* Sensor input */
static boolean  key_pressed;
static boolean  touch;

/* Action flags */
static boolean    turn_on_light;
static boolean    open_door;
static AlarmState alarm_state;

/* Prompt message flag for system startup */
static boolean display_startup_prompt;
/* Prompt message time for system startup */
static uint32_t prompt_display_time = 0;

/* Turn off times */
static uint32_t light_turn_off_time = 0;
static uint32_t door_relock_time = 0;

/* LOCAL FUNCTIONS */
static void initializePins(void)
{
    /* Servo motor izlaz */
    TRISDbits.TRISD8 = OUTPUT_PIN;
    SERVO_PIN_SET = PIN_LOW;
    /* Buzzer/alarm pwm pin */
    TRISAbits.TRISA11 = OUTPUT_PIN;
    BUZZER_PIN_SET = PIN_LOW;
    /* Light izlaz & Alarm LED pin */
    TRISFbits.TRISF6 = OUTPUT_PIN;
    ALARM_LED_PIN_SET = PIN_LOW;
    /* Senzor PIR ulaz */
    TRISDbits.TRISD9 = INPUT_PIN;
    
    /* Inicijalizuj PORTB pinove kao digital+input (ADC ce kasnije prepisati one koji su mu potrebni) 
     * Koriste se za tastere (B11~B12)
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
    
    buzzerPwmSend(buzzer_period);
}

/* Funckija vraca nivo CO2 ogranicen na opseg 0-100 */
static uint8_t getCo2Level(void)
{
    uint8_t co2_level = 0;
    uint16_t temp_co2_raw = (co2_raw_data < CO2_OFFSET) ? 0 : (co2_raw_data - CO2_OFFSET);
    
    co2_level = (uint8_t) (((uint32_t)temp_co2_raw * (uint32_t)100) / (uint32_t)CO2_FACTOR);
	
    /* Ogranicavamo co2_level na opseg 0-100 (za slucaj da je faktor pogresan) */
    if (co2_level > 100) co2_level = 100;
    
    return co2_level; // TODO scale between 0-100

//    // TODO testing alarm, remove later
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
    uint8_t env_light_level = 0;
    uint16_t temp_photores_raw = (photores_raw_data < PHOTO_RES_OFFSET) ? 0 : (photores_raw_data - PHOTO_RES_OFFSET);
    
    env_light_level = (uint8_t)(((uint32_t)temp_photores_raw * (uint32_t)100) / (uint32_t)PHOTO_RES_FACTOR);
    
    /* Ogranicavamo nivo svetlosti u okolini na opseg 0-100 (za slucaj da je faktor pogresan) */
    if (env_light_level > 100) env_light_level = 100;
    
    return env_light_level;
}

/* Ova funkcija treba da proveri sve ulazne signale (CO2 nivo, pokret, pritisak touchscreena/tastera itd.)
 * i da u skladu sa tim podesi kontrolne signal */
static void checkInputs(void)
{    
    /* Pomocni fleg, dodatak softverskom diferenciranju */
    static boolean key_processed   = FALSE;
    
    uint8_t env_light_level = getEnvLightLevel();
	uint8_t co2_level = getCo2Level();
    
    /* Deo koda koji postavlja flag start_alarm na 0 ili 1 u zavisnosti od CO2 nivoa */
	if(co2_level >= CO2_UNSAFE_LEVEL)
    {
        if (alarm_state != ALARM_SILENT)
        {
            alarm_state = ALARM_ON;
            open_door = TRUE;
            /* Ukljuci tajmer 4 zbog PWM-a za Buzzer */
            BUZZER_TIMER_START;
        }
    }
	else if(co2_level <= CO2_SAFE_LEVEL)
    {
        if (alarm_state != ALARM_OFF)
        {
            alarm_state = ALARM_OFF;
            open_door = FALSE;
            /* Iskljuci alarm LED u slucaju da je ostala na HIGH */
            ALARM_LED_PIN_SET = PIN_LOW;
            /* Iskljuci tajmer 4 da bi Buzzer stao */
            BUZZER_TIMER_STOP;
        }
    }
	
	/* Deo koda koji postavlja flag turn_on_light na 0 ili 1 u zavisnosti od senzora pokreta */
    if ((MOTION_PIN_GET == PIN_HIGH) && (LIGHT_PIN_GET == PIN_LOW))
    //if (PORTBbits.RB12 == PIN_HIGH)
    {
        if (env_light_level < ENV_LIGHT_THRESHOLD) turn_on_light = TRUE;
    }
	
	/* Deo koda koji stavlja key_pressed na true ili false na osnovu pritiska tastera */
	if((PORTBbits.RB11 != 0) || (PORTBbits.RB12 != 0))
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

/* Funckija vraca trenutni pritisnut taster (B11~B12) kao brojeve 1~2 ili 0xFF ako nijedan 
 * od tastera nije pritisnut
 */
static uint8_t getKey(void)
{
    if (PORTBbits.RB11 == PIN_HIGH) return 1;
    else if (PORTBbits.RB12 == PIN_HIGH) return 2;
    else return 0xFF;
}

/* Ova funkcija treba da procesuira pritisnuti taster i poredi sa sifrom.
 * Ako je sifra ispravna, vrata treba otkljucati. U suprotnom, vrata ostaju zakljucana. */
static void processKeyPressed(void)
{
    uint8_t key;
    
    /* Procitaj trenutni pritisnut taster 
     * Tasteri su B11~B12 pa oduzimamo broj 8 kako bi dobili brojeve 1~2
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
            door_relock_time = getTickMs() + DOOR_RELOCK_TIME;
            
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
        // door_locked = TRUE; 
        digit_to_check = 0;
    }
}

static void processTouch(void)
{
    unsigned int x_pos = getX();
    unsigned int y_pos = getY();
    
	/* provera da li smo u delu ekrana gde su dugmici */
	if((y_pos > LCD_ICON_Y_MIN) && (y_pos < LCD_Y_MAX))
	{
		/* provera koje dugme je pritisnuto */
		if(x_pos <= DOOR_OPEN_ICON_END)
		{
			/* Sector 1 - Open door */
			if (door_locked == FALSE) open_door = TRUE;
            //uartWriteString("Otvori");	
	}
        else if((x_pos > DOOR_OPEN_ICON_END) && (x_pos <= DOOR_CLOSE_ICON_END))
		{
			/* Sector 2 - Close door */
			if (alarm_state == ALARM_OFF) open_door = FALSE;
            //uartWriteString("Zatvori");
		}
		else if((x_pos > DOOR_CLOSE_ICON_END) && (x_pos <= LIGHT_SWITCH_ICON_END))
		{
			/* Sector 3 - Light ON/OFF */
            turn_on_light = TRUE;
            //uartWriteString("Svetlo");
		}
		else if((x_pos > LIGHT_SWITCH_ICON_END) && (x_pos <= LCD_X_MAX))
		{
			/* Sector 4 - Alarm OFF */
            if (alarm_state == ALARM_ON)
            {
                if (door_locked == FALSE)
                {
                    alarm_state = ALARM_SILENT;
                    ALARM_LED_PIN_SET = PIN_LOW;
                    BUZZER_TIMER_STOP;    
                }
            }
            //uartWriteString("Alarm");
		}
	}
}

static void displayPrompt(void)
{
    uartWriteString("Enter command number: \r\n");
    uartWriteString(" 1. Display system state\r\n");
    uartWriteString(" 2. Open/close door\r\n");
    uartWriteString(" 3. Light ON/OFF\r\n");
    uartWriteString(" 4. Project information\r\n\r\n");
}

static void displaySystemState(void)
{
    uartWriteString("Door: ");
    if (alarm_state == ALARM_ON)
    {
        uartWriteString("ALARM!!!");
    }
    else if (open_door == TRUE)
    {
        uartWriteString("OPEN");
    }
    else
    {
        uartWriteString("CLOSED");
    }
    uartWriteString("\n\r");

    uartWriteString("Door lock: ");
    if (door_locked == TRUE)
    {
        uartWriteString("LOCKED");
    }
    else
    {
        uartWriteString("UNLOCKED");
    }
    uartWriteString("\n\r");
    
    uartWriteString("Light: ");
    if (LIGHT_PIN_GET == PIN_HIGH)
    {
        uartWriteString("ON");
    }
    else
    {
        uartWriteString("OFF");
    }
    uartWriteString("\n\r");
    
    uartWriteString("Current CO2 level: ");
    uartWriteNumber(getCo2Level());
    uartWriteString("\n\r");
    
    uartWriteString("Environment light level: ");
    uartWriteNumber(getEnvLightLevel());
    uartWriteString("\n\r");
    uartWriteString("\n\r");
}

static void displayProjectInfo(void)
{
    uartWriteString("Projekat: Pametna vrata za garazu\r\n");
    uartWriteString("Grupa: 8\r\n\r\n");
    uartWriteString("Projekat radili:\r\n");
    uartWriteString("Mirko Adzic - EE98/2019\r\n");
    uartWriteString("Nikola Kaludjerski - EE161/2019\r\n");
    uartWriteString("Slobodan Jeremic - EE170/2019\r\n");
    uartWriteString("Vesna Jankovic - EE187/2019\r\n\r\n");
}

static void processUartRx(void)
{
    delayMillis(5);
    uint8_t input_len = uartAvailable();
    
    // Unesen je jedan karakter
    if (input_len == 1) 
    {
        // Ocitamo unos sa UART-a
        uint8_t uart_rx = uartReadChar();
        // Konverzija iz karaktera u broj
        uart_rx = uart_rx - '0';

        switch(uart_rx)
        {
            case 1:
            {
                displaySystemState();
            }
            break;
            case 2:
            {
                if (door_locked == TRUE)
                {
                    uartWriteString("Door is locked. Cannot open.\r\n\r\n");
                }
                else
                {
                    if (alarm_state != ALARM_OFF)
                    {
                        uartWriteString("CO2 level too high!!! Cannot close.\r\n\r\n");
                    }
                    else
                    {
                        if (open_door == TRUE)
                        {
                            open_door = FALSE;
                            uartWriteString("Closing door...\r\n\r\n");
                        }
                        else
                        {
                            open_door = TRUE;
                            uartWriteString("Opening door...\r\n\r\n");
                        }
                    }
                }
            }
            break;
            case 3:
            {
                if (LIGHT_PIN_GET == PIN_LOW)
                {
                    LIGHT_PIN_SET = PIN_HIGH;
                    uartWriteString("Light ON.\r\n\r\n");
                }
                else
                {
                    LIGHT_PIN_SET = PIN_LOW;
                    uartWriteString("Light OFF.\r\n\r\n");
                }
            }
            break;
            case 4:
            {
                displayProjectInfo();
            }
            break;
            default:
            {
                uartWriteString("Wrong command number.\r\n\r\n");
            }
            break;
        }
    }    // Uneseno je vise karaktera (iste duzine kao tajna rec)
    else if (input_len == (SECRET_KEY_LEN - 1))
    {        
        uint8_t entered_key[SECRET_KEY_LEN] = { 0 };
        uartReadString(entered_key);
        
        if (stringCompare(entered_key, secret_key) == TRUE)
        {
            door_locked = FALSE;
            door_relock_time = getTickMs() + DOOR_RELOCK_TIME;
            
            uartWriteString("Vrata su se otkljucala...\r\n\r\n");
        }  // Unesen je pogresan broj karaktera
        else
        {
            uartWriteString("Wrong command number.\r\n\r\n");
        } 
    }
    else
    {
        uartFlush();
        uartWriteString("Wrong command number.\r\n\r\n");
    }
    
    displayPrompt();
}

/* Ova funkcija treba da proverava kontrolne signale i da u skladu sa tim izvrsava odredjene 
 * radnje. */
static void performActions(void)
{   
    uint32_t ms_ticks = getTickMs();
    
    if (open_door == TRUE)
    {
        openDoor();
    }
    else
    {
        closeDoor();
    }
    
    if (alarm_state == ALARM_ON) startAlarm();
    
    if (turn_on_light == TRUE)
    {
        // Movement detected => turn on light
        LIGHT_PIN_SET = PIN_HIGH;
        // Light will turn off after 10s
        light_turn_off_time = ms_ticks + LIGHT_TURNOFF_TIME;
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
        if (alarm_state == ALARM_OFF)
        {
            open_door = FALSE;
            door_locked = TRUE;    
        }
        else
        {
            door_relock_time = ms_ticks + 5000;
        }
    }
}

static void taskLcd(void)
{
    if (touch) processTouch();
    
    uint32_t ms_ticks = getTickMs();
    
    if ((ms_ticks % 5) == 0) LcdUpdateDisplay(getCo2Level(), door_locked);
}

/* GLOBAL FUNCTIONS */
void doorSystemInit(void)
{
    open_door     = FALSE;
    door_locked   = TRUE;
    alarm_state   = ALARM_OFF;
    turn_on_light = FALSE;
    
    display_startup_prompt = TRUE;
    prompt_display_time = getTickMs() + 5000;
    
    initializePins();
    
    initTimers();
    uartInit();
    initADC();
    LcdInit();
    initTouchscreen();
}

void doorSystemRun(void)
{
	// Prikazujemo poruku nekoliko sekundi nakon uključivanja sistema
    if (display_startup_prompt == TRUE)
    {
        if (getTickMs() == prompt_display_time)
        {
            displayPrompt();
            display_startup_prompt = FALSE;
        }
    }
    
    checkInputs();
    
    if (key_pressed == TRUE) processKeyPressed();
    
    if (uartAvailable()) processUartRx();
    
    taskLcd();
    
    performActions();
    
    stopActions();
}