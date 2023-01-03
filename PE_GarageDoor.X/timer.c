/* 
 * File:   timer.h
 * Author: 
 *
 * Created on November 8, 2017, 10:48 PM
 */

/* USER LIBRARIES */
#include "timer.h"

/* LOCAL VARIABLES */
static uint16_t tick = 0;

/* LOCAL FUNCTIONS */
static void initT1(uint16_t period)
{
	TMR1 = 0;          /* Resetuj vrednost tajmera 1  */
	PR1 = period;      /* Podesi period tajmera 1     */
	
	T1CONbits.TCS = 0; /* 0 = Internal clock (FOSC/4) */
    // IPC1bits.T1IP = 3 /* T2 interrupt pririty (0-7)      */
	// SRbits.IPL = 3;   /* CPU interrupt priority is 3(11) */
	
    IFS0bits.T1IF = 0; /* Resetuj interrupt flag tajmera 1 */
	IEC0bits.T1IE = 1; /* Dozvoli interrupt tajmera 1      */

	T1CONbits.TON = 1; /* T1 on */ 
}

static void initT2(uint16_t period)
{
	TMR2 = 0;          /* Resetuj vrednost tajmera 2  */
	PR2 = period; /* Podesi period tajmera 2     */
	
	T2CONbits.TCS = 0; /* 0 = Internal clock (FOSC/4) */
    // IPC1bits.T2IP = 3 /* T2 interrupt pririty (0-7)      */
	// SRbits.IPL = 3;   /* CPU interrupt priority is 3(11) */
	
    IFS0bits.T2IF = 0; /* Resetuj interrupt flag tajmera 2 */
	IEC0bits.T2IE = 1; /* Dozvoli interrupt tajmera 2      */

	T2CONbits.TON = 1; /* T2 on */ 
}

/* GLOBAL FUNCTIONS */
void timerInit(uint8_t timerId, uint16_t period)
{
    switch (timerId)
    {
        case TIMER1:
            initT1(period);
        break;
        case TIMER2:
            initT2(period);
        break;
        default:
            /* Do nothing */
        break;
    }
}

uint16_t getTicks(void)
{
    return tick;
}

/* INTERRUPT SERVICE ROUTINES */
void __attribute__((__interrupt__)) __attribute__ ((__auto_psv__)) _T1Interrupt(void)
{
    if (tick < UINT16_MAX)
    {
        tick++;
    } else
    {
        tick = 0;
    }
    
   	TMR1 =0;
    IFS0bits.T1IF = 0;
}

void __attribute__((__interrupt__)) __attribute__ ((__auto_psv__)) _T2Interrupt(void)
{
    
   	TMR2 =0;
    IFS0bits.T2IF = 0;
}


