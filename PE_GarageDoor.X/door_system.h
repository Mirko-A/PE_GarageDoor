/* 
 * File:   door_system.h
 * Author: 
 *
 * Created on December 25, 2022, 2:55 PM
 */

#ifndef DOOR_SYSTEM_H_
#define	DOOR_SYSTEM_H_

/* STANDARD LIBRARIES */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* CTRL LIBRARIES */
#include <p30fxxxx.h>

/* USER LIBRARIES */
#include "timer.h"
#include "adc.h"
#include "glcd.h"
#include "utils.h"

/* MISC LIBRARIES */
#include <math.h>
    
/* MACRO CONSTANTS */ // TODO - SET REAL VALUES FOR MACROS
#define BUZZER_PIN      (11u)
#define SERVO_PIN       (1) 
#define PHOTO_RES_PIN   (1) 
#define ALARM_LED_PIN   (1)
#define MOTION_SENS_PIN (1)

#define DOOR_OPEN_DUTY_CYCLE      (1)
#define DOOR_HALF_OPEN_DUTY_CYCLE (1)
#define DOOR_CLOSED_DUTY_CYCLE    (1)

#define ALARM_LED_PERIOD (500u)

#define CO2_MAX_LEVEL (40)
#define CO2_MIN_LEVEL (5)
#define CO2_FACTOR    (1)

#define PASSWORD_LENGTH (4u)

/* GLOBAL FUNCTIONS */
void doorSystemInit();
void doorSystemRun();

#endif	/* DOOR_SYSTEM_H_ */

