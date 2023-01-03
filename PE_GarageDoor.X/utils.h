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

/* MACRO CONSTANTS */
#define PORT_A (0u)
#define PORT_B (1u)
#define PORT_C (2u)
#define PORT_D (3u)
#define PORT_F (4u)

#define PIN_LOW (0u)
#define PIN_HIGH (1u)

#define FALSE         (0u)
#define TRUE          (1u)

/* TYPE DEFINITIONS */
typedef uint8_t boolean;

void delayMillis(uint16_t delay_time);

void setPin(uint8_t port, uint8_t pin);
void resetPin(uint8_t port, uint8_t pin);
uint8_t getPinState(uint8_t port, uint8_t pin);

void sendPWM(uint8_t port, uint8_t pin, uint8_t period, uint8_t duty_cycle);

#endif	/* UTILS_H_ */

