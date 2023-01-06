/* 
 * File:   utils.h
 * Author: Mieko
 *
 * Created on December 25, 2022, 3:16 PM
 */

/* USER LIBRARIES */
#include "utils.h"

/* GLOBAL FUNCTIONS */
void delayMillis(uint16_t delay_time)
{
    uint16_t start_time, target_time;
    
    start_time = getTicks();
    target_time = start_time + delay_time;
    
    while(getTicks() != target_time);
}

void setPin(uint8_t port, uint8_t pin)
{
    switch (port)
    {
        case PORT_A:
        {
            LATA |= (1 << pin);
        }
        break;
        case PORT_B:
        {
            LATB |= (1 << pin);
        }
        break;
        case PORT_C:
        {
            LATC |= (1 << pin);
        }
        break;
        case PORT_D:
        {
            LATD |= (1 << pin);
        }
        break;
        case PORT_F:
        {
            LATF |= (1 << pin);
        }
        break;
        default:
            break;
    }
}

void resetPin(uint8_t port, uint8_t pin)
{
    switch (port)
    {
        case PORT_A:
        {
            LATA &= ~(1 << pin);
        }
        break;
        case PORT_B:
        {
            LATB &= ~(1 << pin);
        }
        break;
        case PORT_C:
        {
            LATC &= ~(1 << pin);
        }
        break;
        case PORT_D:
        {
            LATD &= ~(1 << pin);
        }
        break;
        case PORT_F:
        {
            LATF &= ~(1 << pin);
        }
        break;
        default:
            break;
    }
}

uint8_t getPinState(uint8_t port, uint8_t pin)
{
    uint8_t pin_state;
    
    switch (port)
    {
        case PORT_A:
        {
            pin_state = PORTA & (1 << pin);
        }
        break;
        case PORT_B:
        {
            pin_state = PORTB & (1 << pin);
        }
        break;
        case PORT_C:
        {
            pin_state = PORTC & (1 << pin);
        }
        break;
        case PORT_D:
        {
            pin_state = PORTD & (1 << pin);
        }
        break;
        case PORT_F:
        {
            pin_state = PORTF & (1 << pin);
        }
        break;
        default:
            break;
    }
    
    return pin_state;
}

void togglePin(uint8_t port, uint8_t pin)
{
    if (getPinState(port, pin) == PIN_HIGH)
    {
        resetPin(port, pin);
    } else
    {
        setPin(port, pin);
    }
}

void sendPWM(uint16_t period_ms, uint8_t duty_cycle)
{
    /* Racunanje periode PWMa po formuli: 
     *   pwm_period = (PRx + 1)*4*Tosc*TMR_prescaler */
    PR2 = (period_ms * 4 * FOSC_IN_KHZ) - 1;
    /* Podesavanje duty cycle-a uzimajuci procenat od PR2 */
    OC1RS = (PR2 + 1) * duty_cycle / 100;
}