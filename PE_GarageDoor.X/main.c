/* 
 * File:   main.c
 * Author: 
 *
 * Created on December 25, 2022, 11:48 AM
 */

/* STANDARD LIBRARIES */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* USER LIBRARIES */
#include "door_system.h"

/* MACRO CONSTANTS */
#define ONE_MS_PERIOD (10000u)  /* Fosc = 10MHz => 1/Fosc = 0.1us => 0.1us * 10_000 = 1ms  */

/* CFG */
_FOSC(CSW_FSCM_OFF & XT_PLL4); /* instruction takt je isti kao i kristal */
_FWDT(WDT_OFF);

/* ENTRY POINT */
int main(int argc, char** argv)
{
    
    // INIT
    initTimer1(ONE_MS_PERIOD);
    initTimer2();
    initADC();
    LcdInit();
    doorSystemInit();
    
    // LOOP
    while (1)
    {
        doorSystemRun();
    }

    return (EXIT_SUCCESS);
}

