/* 
 * File:     touch.h
 * Opis:     Korisnicka biblioteka za rad sa touch screen modulom
 * Napomena: Pri AD konverziji potrebno je koristiti 2 pina
 *           koja su definisana u "adc.h", u ovom slucaju *RB7 RB8
 *           
 *           *subject to change
 */


#ifndef TOUCH_H_
#define TOUCH_H_

/* STANDARD LIBRARIES */
#include <stdint.h>

/* CTRL LIBRARIES */
#include <p30fxxxx.h>

/* USER LIBRARIES */
#include "adc.h"
#include "timer.h"
#include "uart.h"
#include "utils.h"

/* Scaling constants */
// TODO treba pronaci
#define AD_X_MIN (500u)
#define AD_X_MAX (0.04491f)  /* 1/(AD_X_MAX-AD_X_MIN)*128 => 1/(3350-500)*128 */
#define AD_Y_MIN (700u)
#define AD_Y_MAX (0.02667f) /* 1/(AD_Y_MAX-AD_Y_MIN)*64 => 1/(3100-700)*64 */

/* Transistor control */
#define DRIVE_A LATCbits.LATC13
#define DRIVE_B LATCbits.LATC14

/* Display positions */
#define Y_MAX (64)
#define X_MAX (128)

/* GLOBAL FUNCTIONS */

/* 
 * Jednom pozivamo
 * Vrsi inicijalizaciju pinova za touch screen
 * Koriste se RC13 RC14
 */
void initTouchscreen();

/* 
 * Radi konverziju raw podataka sa AD konvertora u x,y koordinate 
 * Za x vazi opseg [0,127], a y opseg [0, 63]
 * Potrebno da se nonstop vrti
 */
void updateCoords(void);

/* Getter funkcije */
unsigned int getX();
unsigned int getY();

#endif /* TOUCH_H_ */