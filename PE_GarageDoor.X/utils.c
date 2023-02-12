/* 
 * File:   utils.h
 * Author: Mieko
 *
 * Created on December 25, 2022, 3:16 PM
 */

/* USER LIBRARIES */
#include "utils.h"

static volatile boolean servo_pwm_sent  = FALSE;
static volatile boolean buzzer_pwm_sent = FALSE;

/* GLOBAL FUNCTIONS */
void delayMillis(uint16_t delay_time)
{
    uint16_t start_time, target_time;
    
    start_time = getTickMs();
    target_time = start_time + delay_time;
    
    while(getTickMs() != target_time);
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

void buzzerPwmSend(uint16_t period_tenth_of_ms)
{
    if (buzzer_pwm_sent == TRUE) return;
    
    startTimer4(period_tenth_of_ms);
    
    buzzer_pwm_sent = TRUE;
}

boolean stringCompare(uint8_t *string1, uint8_t *string2)
{
    uint8_t str1_len = strlen(string1);
    uint8_t str2_len = strlen(string2);
    
    if (str1_len != str2_len) return FALSE;
    
    uint8_t current_char;
    
    for (current_char = 0; current_char < str1_len; current_char++)
    {
        if (string1[current_char] != string2[current_char]) return FALSE;
    }

    return TRUE;
}

/* INTERRUPT SERVICE ROUTINES */

/* Toggle Servo motor pin for generating PWM signal */
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

/* Toggle Buzzer pin for generating PWM signal */
void __attribute__((__interrupt__)) __attribute__ ((__auto_psv__)) _T4Interrupt(void)
{
    if (BUZZER_PIN_GET == PIN_HIGH)
    {
        BUZZER_PIN_SET = PIN_LOW;
    }
    else if (BUZZER_PIN_GET == PIN_LOW)
    {
        BUZZER_PIN_SET = PIN_HIGH;
    }
    
    buzzer_pwm_sent = FALSE;
   	TMR4 = 0;
    IFS1bits.T4IF = 0;
}