/* 
 * File:   timer.h
 * Author: 
 *
 * Created on November 8, 2017, 10:48 PM
 */

#ifndef TIMER_H_
#define TIMER_H_

/* STANDARD LIBRARIES */
#include <stdint.h>

/* CTRL LIBRARIES */
#include <p30fxxxx.h>

/* MACRO CONSTANTS */
#define TIMER1 (0u)
#define TIMER2 (1u)

/* PUBLIC FUNCTIONS */
void timerInit(uint8_t timerId, uint16_t period);

uint16_t getTicks(void);

#endif /* TIMER_H_ */

