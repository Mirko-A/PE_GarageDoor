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

/* GPIO pin related macros */
#define PHOTO_RES_PIN   PORT_B, 6
#define PHOTO_RES_GET   PORTBbits.RB6
#define PHOTO_RES_SET   LATBbits.LATB6

#define LIGHT_PIN       PORT_C, 15
#define LIGHT_PIN_GET   PORTCbits.RC15 
#define LIGHT_PIN_SET   LATCbits.LATC15

// TODO used for testing
//#define LIGHT_PIN_GET  PORTAbits.RA11
//#define LIGHT_PIN_SET  LATAbits.LATA11

#define MOTION_PIN      PORT_D, 9
#define MOTION_PIN_GET  PORTDbits.RD9
#define MOTION_PIN_SET  LATDbits.LATD9

#define ALARM_LED_PIN      PORT_F, 6
#define ALARM_LED_PIN_GET  PORTFbits.RF6
#define ALARM_LED_PIN_SET  LATFbits.LATF6

/* Door state related macros - duty cycles in tenths of milliseconds */
#define DOOR_CLOSED_DUTY_CYCLE    (15)
#define DOOR_HALF_OPEN_DUTY_CYCLE (10)
#define DOOR_OPEN_DUTY_CYCLE      (5)

/* Used in conjunction with getTicks to make LED blink every 512 milliseconds.
   In order not to miss any milliseconds, value should be 2^n because maximum tick value is also 2^n (uint16_t => 2^16).
 */
#define ALARM_LED_PERIOD     (256u)

#define CO2_UNSAFE_LEVEL (50)
#define CO2_SAFE_LEVEL   (10)
#define CO2_FACTOR       (3150u)

#define ENV_LIGHT_THRESHOLD (50)
#define PHOTO_RES_FACTOR    (3150u)

#define PASSWORD_LENGTH (4u)
#define BUTTONS         (PORTB & 0xFE00) /* Looking at pins B9 ~ B15 only */

/* TYPE DEFINITIONS */
typedef enum 
{
    DOOR_CLOSED,
    DOOR_OPEN,
    ALARM_STATE
} DoorState;

/* GLOBAL FUNCTIONS */

/**
 * @brief This function initializes all components of the system. These include: 
 * - GPIO pins
 * - Timers
 * - UART module
 * - A/D converter
 * - LCD display
 * - Touchscreen
 * .
 * @param void
 * @return void
 */
void doorSystemInit(void);

/**
 * @brief This function executes core functionalities of the system sequentially. These include: 
 * - Checking input signals and raising corresponding flags
 * - Processing button press events
 * - LCD display updates and touchscreen processing
 * - Starting necessary actions based on flags from input signals
 * - Stopping started actions when necessary (when time limits are reached).
 * .
 * @param void
 * @return void
 */
void doorSystemRun(void);

#endif	/* DOOR_SYSTEM_H_ */

