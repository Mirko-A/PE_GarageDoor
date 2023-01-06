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
//#include <outcompare.h>

/* GLOBAL FUNCTIONS */

/** 
 * @brief Inicijalizuje Timer1 za output compare.
 * @param uint16_t period_ms -> timer period u milisekundama
 * @return void
 */
void initTimer1(uint16_t period_ms);

/**
 * @brief Inicijalizuje Timer2 za generisanje PWM signala.
 * @return void
 * @note Za koriscenje Timer2 za PWM upotrebiti funkciju sendPWM() iz ./utils.c
 */
void initTimer2();

uint32_t getTicks(void);

#endif /* TIMER_H_ */

