/* 
 * File:   utils.h
 * Author: 
 *
 * Created on December 25, 2022, 3:16 PM
 */

#ifndef UTILS_H_
#define	UTILS_H_

/* STANDARD LIBRARIES */
#include <stdint.h>

/* CTRL LIBRARIES */
#include <p30fxxxx.h>

/* USER LIBRARIES */
#include "timer.h"
#include "uart.h"

/* MACRO CONSTANTS */
#define PORT_A (0u)
#define PORT_B (1u)
#define PORT_C (2u)
#define PORT_D (3u)
#define PORT_F (4u)

#define PIN_LOW   (0u)
#define PIN_HIGH  (1u)

#define INPUT_PIN  (1u)
#define OUTPUT_PIN (0u)

#define FALSE   (0u)
#define TRUE    (1u)

#define SERVO_PIN       PORT_D, 8
#define SERVO_PIN_GET   PORTDbits.RD8
#define SERVO_PIN_SET   LATDbits.LATD8

#define BUZZER_PIN      PORT_A, 11
#define BUZZER_PIN_GET  PORTAbits.RA11
#define BUZZER_PIN_SET  LATAbits.LATA11

#define BUZZER_SWITCH_PERIOD     (512u)
#define BUZZER_LOW_PITCH_PERIOD  (84u)  //  ~ 120 Hz
#define BUZZER_HIGH_PITCH_PERIOD (21u)  //  ~ 480 KHz

/* TYPE DEFINITIONS */
typedef uint8_t boolean;

/* GLOBAL FUNCTIONS */

/**
 * @brief Function blocks the program for x milliseconds.
 * @param delay_time -> x number of milliseconds to delay the program
 * @return void
 */
void delayMillis(uint16_t delay_time);

/**
 * @Brief Function sends PWM signal to servo motor.
 * @param uint16_t period_tenth_of_ms  -> PWM period in tenths of millisecond
 * @param uint8_t  duty_cycle_time     -> PWM duty cycle in tenths of millisecond
 * @return void
 */
void servoPwmSend(uint16_t period_tenth_of_ms, uint16_t duty_cycle_time);

/**
 * @Brief Function sends PWM signal to buzzer.
 * @param uint16_t period_tenth_of_ms  -> PWM period in tenths of millisecond
 * @return void
 */
void buzzerPwmSend(uint16_t period_tenth_of_ms);

#endif	/* UTILS_H_ */

