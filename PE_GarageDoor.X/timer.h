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
#include <outcompare.h>

/* List of SFRs for Timers */
/* This list contains the SFRs with default (POR) values to be used for configuring Timers */
/* The user can modify this based on the requirement */
#define TMRx_VALUE          0x0000
#define PRx_VALUE           0xFFFF
#define TxCON_VALUE         0x0000

/* Timer1 Control Register (T1CON) Bit Defines */

#define T1_ON               0xffff      /* Timer1 ON */
#define T1_OFF              0x7fff      /* Timer1 OFF */

#define T1_IDLE_CON         0xdfff      /* operate during sleep */
#define T1_IDLE_STOP        0xffff      /* stop operation during sleep */

#define T1_GATE_ON          0xffff      /* Timer Gate time accumulation enabled */
#define T1_GATE_OFF         0xffbf      /* Timer Gate time accumulation disabled */

#define T1_PS_1_1           0xffcf      /* Prescaler 1:1 */
#define T1_PS_1_8           0xffdf      /*           1:8 */
#define T1_PS_1_64          0xffef      /*          1:64 */
#define T1_PS_1_256         0xffff      /*         1:256 */

#define T1_SYNC_EXT_ON      0xffff      /* Synch external clk input */
#define T1_SYNC_EXT_OFF     0xfffb      /* Do not synch external clk input */

#define T1_SOURCE_EXT       0xffff      /* External clock source */
#define T1_SOURCE_INT       0xfffd      /* Internal clock source */

/* defines for Timer Interrupts */

#define T1_INT_PRIOR_7      0xffff      /* 111 = Interrupt is priority 7 */
#define T1_INT_PRIOR_6      0xfffe      /* 110 = Interrupt is priority 6 */
#define T1_INT_PRIOR_5      0xfffd      /* 101 = Interrupt is priority 5 */
#define T1_INT_PRIOR_4      0xfffc      /* 100 = Interrupt is priority 4 */
#define T1_INT_PRIOR_3      0xfffb      /* 011 = Interrupt is priority 3 */
#define T1_INT_PRIOR_2      0xfffa      /* 010 = Interrupt is priority 2 */
#define T1_INT_PRIOR_1      0xfff9      /* 001 = Interrupt is priority 1 */
#define T1_INT_PRIOR_0      0xfff8      /* 000 = Interrupt is priority 0 */

#define T1_INT_ON           0xffff      /* Interrupt Enable */
#define T1_INT_OFF          0xfff7      /* Interrupt Disable */

/* Macros to  Enable/Disable interrupts and set Interrupt priority of Timers 1*/
#define EnableIntT1                    _T1IE = 1
#define DisableIntT1                   _T1IE = 0
#define SetPriorityIntT1(priority)     _T1IP = priority

#define ONE_MS_PERIOD  (5000u)  /* Fosc = 10MHz => 1/Fosc = 0.1us => 0.1us * 10_000 = 1ms  */
                                /* Trenutno Fosc = 5MHz => 1/Fosc = 0.2us => 0.2us * 5000 = 1ms */

#define TENTH_OF_MS_FACTOR (2);

/* nisam siguran? */
#define Nop() {__asm__ volatile ("nop");}

//#define xtal 29480000
#define xtal 25000000

/* Timer1 Function Prototypes */

/* OpenTimer1 */
void OpenTimer1( unsigned int config, unsigned int period); 
//(".libperi")));

/* CloseTimer1 */
void CloseTimer1(void);

/* ReadTimer1 */
unsigned int ReadTimer1(void); 

/* WriteTimer1 */
void WriteTimer1( unsigned int timer);

/* Config Int Timer1 */
void ConfigIntTimer1(unsigned int config);

/* GLOBAL FUNCTIONS */

/** 
 * @brief Inicijalizuje Timer1 za output compare.
 * @param uint16_t period_ms -> timer period u milisekundama
 * @return void
 */
void initTimer1Ticks(uint16_t period_ms);

/** 
 * @brief Inicijalizuje Timer1 za koriscenje GLCD-a.
 * @param void
 * @return void
 */
void initTimer1(void);

/** 
 * @brief Inicijalizuje Timer2 za output compare. Sluzi da generise PWM signal.
 * @param void
 * @return void
 */
void initTimer2(void);

/** 
 * @brief Inicijalizuje Timer2 za output compare. Sluzi da generise PWM signal.
 * @param uint16_t period_ms -> timer period u desetinama milisekundame
 * @return void
 */
void startTimer2(uint16_t period_tenth_of_ms);

/** 
 * @brief Inicijalizuje Timer3 za output compare. Sluzi da uvecava ms_tick svake milisekunde.
 * @param void
 * @return void
 */
void initTimer3(void);

uint32_t getTickMs(void);

#endif /* TIMER_H_ */

