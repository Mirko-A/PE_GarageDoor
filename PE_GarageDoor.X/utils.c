/* 
 * File:   utils.h
 * Author: Mieko
 *
 * Created on December 25, 2022, 3:16 PM
 */

#include "utils.h"

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

void sendPWM(uint8_t port, uint8_t pin, uint8_t period, uint8_t duty_cycle)
{
    uint8_t duty_cycle_time;
    
    duty_cycle_time = period * duty_cycle;
    
    setPin(port, pin);
    delayMillis(duty_cycle_time);
    resetPin(port, pin);
    delayMillis(period - duty_cycle_time);
}