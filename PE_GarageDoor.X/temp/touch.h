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

/* CTRL LIBRARIES */
#include<p30fxxxx.h>

/* STANDARD LIBRARIES */
#include <stdlib.h>

/* USER LIBRARIES */
#include "adc.h"
#include "utils.h"

/* Scaling constants */
//treba pronaci
#define AD_X_MIN 220
#define AD_X_MAX 3642
#define AD_Y_MIN 520
#define AD_Y_MAX 3450

/* Transistor control */
#define DRIVE_A PORTCbits.RC13
#define DRIVE_B PORTCbits.RC14

/* Display positions */
#define Y_MAX 64
#define X_MAX 128



/* 
 * Jednom pozivamo
 * Vrsi inicijalizaciju pinova za touch screen
 * Koriste se RC13 RC14
 */
void initTouchScreen();

/* 
 * Radi konverziju raw podataka sa AD konvertora u x,y koordinate 
 * Za x vazi opseg [0,127], a y opseg [0, 63]
 * Potrebno da se nonstop vrti
 */
void updateCoords(void);

/* Getter funkcije za koordinate */
unsigned int getX();
unsigned int getY();

/* 
 * Proverava da li su pritisnuti dugmici 
 * Prosledjujemo adrese flegove
 */
void processTouch(int *open_door, int *turn_on_light, int *start_alarm)



#endif /* TOUCH_H_ */