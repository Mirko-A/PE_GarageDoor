/* 
 * File:   utils.h
 * Author: Mieko
 *
 * Created on December 25, 2022, 3:16 PM
 */

/* USER LIBRARIES */
#include "utils.h"

static boolean servo_pwm_sent = FALSE;

/* GLOBAL FUNCTIONS */
void delayMillis(uint16_t delay_time)
{
    uint16_t start_time, target_time;
    
    start_time = getTickMs();
    target_time = start_time + delay_time;
    
    while(getTickMs() != target_time);
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

void servoPwmSend(uint16_t period_tenth_of_ms, uint16_t duty_cycle_time)
{
    if (servo_pwm_sent == TRUE) return;
    
    if (duty_cycle_time == period_tenth_of_ms)
    {
        SERVO_PIN_SET = PIN_HIGH;
        return;
    }
    else if (duty_cycle_time == 0)
    {
        SERVO_PIN_SET = PIN_LOW;
        return;
    }
    
    if (SERVO_PIN_GET == PIN_LOW)
    {
        // Pin was high and interrupt set it to low
        startTimer2(period_tenth_of_ms - duty_cycle_time);
    }
    else if (SERVO_PIN_GET == PIN_HIGH)
    {
        // Pin was low and interrupt set it to high
        startTimer2(duty_cycle_time);
    }
    
    servo_pwm_sent = TRUE;
}

void __attribute__((__interrupt__)) __attribute__ ((__auto_psv__)) _T2Interrupt(void)
{
    if (SERVO_PIN_GET == PIN_HIGH)
    {
        SERVO_PIN_SET = PIN_LOW;
    }
    else if (SERVO_PIN_GET == PIN_LOW)
    {
        SERVO_PIN_SET = PIN_HIGH;
    }
    
    servo_pwm_sent = FALSE;
   	TMR2 = 0;
    IFS0bits.T2IF = 0;
}