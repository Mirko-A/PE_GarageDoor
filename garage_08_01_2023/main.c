#include <stdlib.h>
#include <stdio.h>
#include <p30fxxxx.h>
#include "glcd_lib.h"
#include "timer2.h"
#include "utils.h"



#define SENZOR_MAX 4000

#define START_POSITION 13
#define CONST_BAR_HEIGHT 6


const char bar_pin_bit_bmp[1024] = {
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 32, 32,240,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 32, 16, 16, 
 240,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 32,144,144, 
 208, 32,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224, 16, 
  16, 16,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  8, 15,  8, 
   8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12, 12, 10, 
   9,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,  8,  8, 
   8,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  8, 
   8,  8,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
   3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
   3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
   3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,124, 68, 68, 68,  0,124, 68, 
  68, 68,124,  0,  0, 68, 32, 16,  8, 68,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63, 33, 33, 
  33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 
  33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 
  33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 
  33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 
  33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 
  33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 
  33, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};


/*

_FOSC(CSW_FSCM_OFF & XT_PLL4); // instrukcioni takt je isti kao i kristal
_FWDT(WDT_OFF);

static unsigned int ms = 0;


//glcd+senzor
static unsigned int senzor_value;
static unsigned int senzor_value_percent;
static unsigned int screen_value_percent;


void __attribute__((__interrupt__)) _ADCInterrupt(void) 
{
	senzor_value = ADCBUF0;
	senzor_value_percent = (senzor_value / SENZOR_MAX)*100;
    IFS0bits.ADIF = 0;

} 
*/



void updateCo2Bar()
{	
	static unsigned previous_update;
	unsigned int co2_percent = getCo2(); //format: 0-100
	                                     //co2_percent + START_POSITION
										 //pixel:procenat = 1:1 ratio
										 
	
	if(previous_update != co2_percent)
	{
		GLCD_DisplayPicture(co2_bar);
	}
	
	for(int x_pos  = START_POSITION; x_pos < (co2_percent + START_POSITION); x_pos++)
	{
		GLCD_ResDot(x_pos, CONST_BAR_HEIGHT);
		GLCD_ResDot(x_pos, CONST_BAR_HEIGHT-1);
		GLCD_ResDot(x_pos, CONST_BAR_HEIGHT-2);
		GLCD_ResDot(x_pos, CONST_BAR_HEIGHT-3);
		
		//delayMilis(30); //nzm mozda napravi kul efekat punjenja
	}
	
	previous_update = co2_percent; //clr screen if
	
	
	//for x_pos = start, x_pos < (end_pos * current_bar_percent) **
	
}

/*
void __attribute__ ((__interrupt__)) _T2Interrupt(void) // svakih 1ms
{

	TMR2 = 0;
    
	ms++;

	IFS0bits.T2IF = 0; 
       
}

void Delay_ms (unsigned int stop)//funkcija za kasnjenje u milisekundama
	{
		ms = 0;
		while(ms < stop);
	}


void main(void)
{
	GLCD_LcdInit();
	
	
	
	GLCD_DisplayPicture(bar_pin_bit_bmp); //displej 4 broja i procenta ugljen dio/mono
	
	while(1)
	{
		updateCarbonLevel();
	}
	
	
}*/