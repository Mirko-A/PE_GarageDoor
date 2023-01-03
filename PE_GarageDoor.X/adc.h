/* 
 * File:   adc.h
 * Author: 
 *
 * Created on 27. septembar 2017., 16.09
 */

#ifndef ADC_H_
#define	ADC_H_

/* STANDARD LIBRARIES */
#include <stdint.h>

/* CTRL LIBRARIES */
#include <p30fxxxx.h>

/* GLOBAL VARIABLES */
extern uint16_t fotores_raw_data;
extern uint16_t co2_raw_data;
extern uint16_t raw_data_;

/* GLOBAL FUNCTIONS */
void initADC(void);

#endif	/* ADC_H_*/

