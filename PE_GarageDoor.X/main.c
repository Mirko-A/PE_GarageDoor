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
#include "touch.h"

/* CFG */
_FOSC(CSW_FSCM_OFF & XT_PLL4); /* instruction takt je isti kao i kristal */
_FWDT(WDT_OFF);

/* ENTRY POINT */
int main(int argc, char** argv)
{
    
    // INIT
    doorSystemInit();
    
    // LOOP
    while (1)
    {
        doorSystemRun();
    }

    return (EXIT_SUCCESS);
}

