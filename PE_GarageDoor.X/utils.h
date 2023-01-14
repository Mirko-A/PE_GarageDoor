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

#define FALSE        (0u)
#define TRUE         (1u)

#define SERVO_PIN       PORT_D, 8
#define SERVO_PIN_GET   PORTDbits.RD8
#define SERVO_PIN_SET   LATDbits.LATD8

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
 * @brief Function set a pin on desired port.
 * @param port
 * @param pin
 */
void setPin(uint8_t port, uint8_t pin);

/**
 * @brief Function reset a pin on desired port.
 * @param port
 * @param pin
 */
void resetPin(uint8_t port, uint8_t pin);

/**
 * @brief Function returns current pin state from a desired pin on specified port.
 * @param port
 * @param pin
 */
uint8_t getPinState(uint8_t port, uint8_t pin);

/**
 * @brief Function toggles a pin on desired port.
 * @param port
 * @param pin
 */
void togglePin(uint8_t port, uint8_t pin);

/**
 * @Brief function sends PWM signal to servo motor.
 * @param uint16_t period_tenth_of_ms  -> PWM period in tenths of millisecond
 * @param uint8_t  duty_cycle_time     -> PWM duty cycle in tenths of millisecond
 * @return void
 */
void servoPwmSend(uint16_t period_tenth_of_ms, uint16_t duty_cycle_time);


#endif	/* UTILS_H_ */

