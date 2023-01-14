/* 
 * File:   glcd.h
 * Author: student
 *
 * Created on 24. novembar 2022., 17.48
 */

#ifndef GLCD_H
#define	GLCD_H

#ifdef	__cplusplus
extern "C" {
#endif

/* STANDARD LIBRARIES */
#include <stdint.h>  
    
/* USER LIBRARIES */
#include "utils.h"
    
/* CTRL LIBRARIES */
#include<p30fxxxx.h>
    
/* LCD Registers */
#define PAGE_ADRESS	0xB8	/* Adress base for Page 0 */
#define Y_ADRESS	0x40	/* Adress base for Y0	  bilo 40*/
#define START_LINE	0xC0	/* Adress base for line 0 */
#define DISPLAY_ON	0x3F	/* Turn display on	  */
#define DISPLAY_OFF	0x3E	/* Turn display off	  */

/* General use definitions */
#define RIGHT		0
#define LEFT		1
#define BUSY		0x80

#define FONT_LENGHT 5
#define FONT_LENGHT_BIG 16

#define PIXEL_RECT_RATION		1.3

#define OUTPUT 0 //koristi se kod definisanja pravca pina ulazni ili izlazni
#define INPUT  1

/* Co2 bar */
#define BAR_START_POSITION 13
#define BAR_END_POSITION 100
#define BAR_HEIGHT 4
#define BAR_OFFSET 2

#define LCD_Y_MAX 64
#define LCD_X_MAX 128
    
#define RF5_1 LATF|=0b0000000000100000;//RST
#define RF5_0 LATF&=0b1111111111011111;

#define RF4_1 LATF|=0b0000000000010000;//E
#define RF4_0 LATF&=0b1111111111101111;

#define RF1_1 LATF|=0b0000000000000010;//RW
#define RF1_0 LATF&=0b1111111111111101;

#define RF0_1 LATF|=0b0000000000000001;//RS
#define RF0_0 LATF&=0b1111111111111110;

#define RB5_1 LATB|=0b0000000000100000;//CS2
#define RB5_0 LATB&=0b1111111111011111;

#define RB4_1 LATB|=0b0000000000010000;//CS1
#define RB4_0 LATB&=0b1111111111101111;

extern const unsigned char FONT_BIG[];
extern const unsigned char FONT[];
extern const unsigned char CO2_BAR[];
    
/* Konfiguracija registara */
void SetRST(unsigned char vrednost);
void SetE(unsigned char vrednost);
void SetRW(unsigned char vrednost);
void SetRS(unsigned char vrednost);
void SetCS2(unsigned char vrednost);
void SetCS1(unsigned char vrednost);

/*
 *	Konfiguracija SVIH pinova za rad sa LCD - om
 */
void ConfigureLcdPins (void);

/* 
 *	Setovanje LCD pinova na input ili output
 */
void ConfigureLcdData(unsigned char direction);

/* 
 *	Setovanje vrednosti LCD pinova
 */
void SetLcdData(unsigned char vrednost);

/* 
 *	Citanje vrednosti LCD pinova
 */
unsigned char ReadLcdData(void);

/*
 * Strobe
 * Valjda ukljucuje i iskljucuje svetlo kao refresh neki
 */
void LcdStrobeData(void);


/* Funkcije za rad sa GLCD - om */

/* 
 *	Slanje instrukcija modulu
 */
void LcdInstructionWrite (unsigned char u8Instruction);

/* 
 *	Kratak delay za timing
 */
void LcdDelay(unsigned int u32Duration);

/* 
 *	Cekanje sve dok LCD prima informacije
 */
void LcdWaitBusy (void);

/* 
 *	Postavljanje kursora po y tj. veritkalnoj osi.
 *	Prosledjujemo vrednost 0-8
 */
void LcdGotoY(unsigned char y);

/* 
 *	Postavljanje kursora po x tj. horizontalnoj osi.
 *	Prosledjujemo vrednost 0-128
 */
void LcdGotoX(unsigned char x);

/* 
 *	Postavljanje kursora na (x, y) pozicije
 *	Koristi funkcije GotoX, LcdGotoY
 */
void LcdGotoXY(unsigned char x,unsigned char y);

/* 
 *	Koristimo za skroolovanje ekrana tj. tu polovinu koju postavimo startline.
 *	Ona celu polovinu translira gore dole da joj je vrh na liniji koju postavimo.
 *	Prosledjujemo vrednost 0-64
 */
void LcdSelectStartline(unsigned char startna_linija);

/* 
 *	Selektujemo stranu LCD - a.
 *	Prosledjujemo vrednost LEFT ili RIGHT
 */
void LcdSelectSide(unsigned char u8LcdSide);

/* 
 *	Funkcija za citanje informacije sa LCD - a.
 *	Koristi funkciju ReadLcdData
 *  Vraca vrednost unsigned char
 */
unsigned char LcdDataRead (void);

/* 
 *	Inicijalizacija GLCD modula	
 */
void LcdInit(void);

/* 
 *	Salje informaciju LCD - u.
 *	Prosledjujemo vrednosti tipa unsigned char
 */
void LcdDataWrite (unsigned char u8Data);

/* 
 *	Brisanje ekrana
 */
void LcdClearScreen (void);

/* 
 *	Ispuni ceo ekran
 */
void LcdFillScreen (void);

/* 
 *	Prikaz slike na ekranu.
 *	Sliku je potrebno pretvoriti u formu niza tj matrice.
 *	Prosledjujemo adresu niza
 */
void LcdDisplayPicture (const unsigned char *picture);

/* 
 *	Postavljanje tacke na (x, y) poziciju
 */
void LcdSetDot (unsigned char u8Xaxis, unsigned char u8Yaxis);

/* 
 *	Postavljanje praznu tacku na (x, y) poziciju
 */
void LcdClearDot (unsigned char u8Xaxis, unsigned char u8Yaxis);

/*
 *	Crta krug na ekranu
 *	Prosledjujemo vrednosti:
 *		u8CenterX = Center absciss (in pixels)
 *		u8CenterY = Center ordinate (in pixels) 
 *		u8Radius  = Radius (in pixels)
 */
void LcdDrawCircle (unsigned char u8CenterX, unsigned char u8CenterY, unsigned char u8Radius);

/*
 *	Crta pravougaonik na ekranu
 *	Prosledjujemo vrednosti:
 *		u8Xaxis1 = absciss top-left (in pixels)
 *		u8Yaxis1 = ordinate top-left (in pixels)
 *		u8Xaxis2 = absciss bottom-right (in pixels)
 *		u8Yaxis2 = ordinate bottom-right (in pixels)
 */
void LcdDrawRect (unsigned char u8Xaxis1,unsigned char u8Yaxis1,unsigned char u8Xaxis2,unsigned char u8Yaxis2);

/* 
 * Ispisuje se 1 karakter na ekranu.
 * Prebacivanje u novi red pri preteku i vracanje na 0-ti red kada prodje poslednji
 */ 
void LcdPutChar (char AskiKod);

/* 
 * Ispisuje se 1 VELIKI karakter na ekranu.
 * Prebacivanje u novi red pri preteku i vracanje na 0-ti red kada prodje poslednji
 */ 
void LcdPutCharBig (char AskiKod);

/* 
 * Ispisuje strin na ekranu.
 */ 
void LcdPrintf (char *au8Text);

/* 
 * Iscrtava grid na ekranu
 */ 
void LcdShowGrid(unsigned char grid_padding);

/*
 * Azurira procenat Co2 na ekranu
 * Koristi getCo2() funkciju
 */
void LcdUpdateDisplay(uint8_t co2_level, boolean door_locked);

#ifdef	__cplusplus
}
#endif

#endif	/* GLCD_H */

