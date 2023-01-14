/* 
 * File:   door_system.h
 * Author: 
 *
 * Created on December 25, 2022, 2:55 PM
 */

#ifndef DOOR_SYSTEM_H_
#define	DOOR_SYSTEM_H_

/* STANDARD LIBRARIES */
#include <stdint.h>

/* CTRL LIBRARIES */
#include <p30fxxxx.h>

/* USER LIBRARIES */
#include "timer.h"
#include "adc.h"
#include "glcd.h"
#include "touch.h"
#include "uart.h"
#include "utils.h"
    
/* MACRO CONSTANTS */ // TODO - SET REAL VALUES FOR MACROS
#define BUZZER_PIN      (11u)

#define PHOTO_RES_PIN   PORT_B, 6
#define PHOTO_RES_GET   PORTBbits.RB6
#define PHOTO_RES_SET   LATBbits.LATB6

#define LED_PIN         PORT_C, 15
#define LED_PIN_GET     PORTCbits.RC15
#define LED_PIN_SET     LATCbits.LATC15

#define MOTION_PIN      PORT_D, 9
#define MOTION_PIN_GET  PORTDbits.RD9
#define MOTION_PIN_SET  LATDbits.LATD9

#define ALARM_LED_PIN   (1)

#define DOOR_CLOSED_DUTY_CYCLE    (15)
#define DOOR_HALF_OPEN_DUTY_CYCLE (10)
#define DOOR_OPEN_DUTY_CYCLE      (5)

/* Used in conjunction with getTicks to make LED blink every 512 milliseconds.
   In order no to miss any milliseconds, value should be 2^n because maximum tick value is also 2^n (uint16_t => 2^16).
 */
#define ALARM_LED_PERIOD (512u)

#define CO2_MAX_LEVEL (40)
#define CO2_MIN_LEVEL (5)
#define CO2_FACTOR    (3150u)

#define PASSWORD_LENGTH (4u)
#define BUTTONS         (PORTB & 0xFE00) /* Looking at pins B9 ~ B15 only */

/* GLOBAL FUNCTIONS */
void doorSystemInit();
void doorSystemRun();

#endif	/* DOOR_SYSTEM_H_ */

