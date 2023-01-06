/* 
 * File:   timer.h
 * Author: 
 *
 * Created on November 8, 2017, 10:48 PM
 */

/* USER LIBRARIES */
#include "timer.h"

/* LOCAL VARIABLES */
static uint32_t tick = 0;

/* GLOBAL FUNCTIONS */
void initTimer1(uint16_t period_ms)
{
	TMR1 = 0;          /* Resetuj vrednost tajmera 1  */
	PR1  = period_ms;  /* Podesi period tajmera 1     */
	
	T1CONbits.TCS = 0;   /* 0 = Internal clock (FOSC/4) */
    // IPC1bits.T1IP = 3 /* T2 interrupt pririty (0-7)      */
	// SRbits.IPL = 3;   /* CPU interrupt priority is 3(11) */
	
    IFS0bits.T1IF = 0; /* Resetuj interrupt flag tajmera 1 */
	IEC0bits.T1IE = 1; /* Dozvoli interrupt tajmera 1      */

	T1CONbits.TON = 1; /* T1 on */ 
}

void initTimer2()
{
    TRISDbits.TRISD0 = 0; /* Output pin za OC1 */
    
    PR2    = 0; /* Odredjuje PWM frekvenciju */
    OC1RS  = 0; /* Odredjuje duty cycle */
    OC1R   = 0; /* Pocetni duty cycle */
    OC1CON = 0b111;//OC_IDLE_CON & OC_TIMER2_SRC & OC_PWM_FAULT_PIN_DISABLE & T2_PS_1_256; /* PWM configuration */
    
    T2CONbits.TON = 1; /* T2 on */ 
}


uint32_t getTicks(void)
{
    return tick;
}

/* INTERRUPT SERVICE ROUTINES */
void __attribute__((__interrupt__)) __attribute__ ((__auto_psv__)) _T1Interrupt(void)
{
    tick++;
    
   	TMR1 = 0;
    IFS0bits.T1IF = 0;
}

void __attribute__((__interrupt__)) __attribute__ ((__auto_psv__)) _T2Interrupt(void)
{
   	TMR2 = 0;
    IFS0bits.T2IF = 0;
}


