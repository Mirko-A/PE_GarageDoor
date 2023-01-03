/* 
 * File:   glcd.h
 * Author: student
 *
 * Created on 24. novembar 2022., 17.48
 */

#ifndef GLCD_H_
#define	GLCD_H_

/* STANDARD LIBRARIES */
#include <stdlib.h>    

/* CTRL LIBRARIES */
#include <p30fxxxx.h>

/* MACRO CONSTANTS */

/* LCD Registers */
#define PAGE_ADRESS	(0xB8)	/* Adress base for Page 0 */
#define Y_ADRESS	(0x40)	/* Adress base for Y0	  */
#define START_LINE	(0xC0)	/* Adress base for line 0 */
#define DISPLAY_ON	(0x3F)	/* Turn display on	      */
#define DISPLAY_OFF	(0x3E)	/* Turn display off	      */

/* General use definitions */
#define RIGHT		(0)
#define LEFT		(1)
#define BUSY		(0x80)

#define FONT_LENGHT     (5)
#define FONT_LENGHT_BIG (16)

#define PIXEL_RECT_RATIO (1.3)

#define INPUT   (0u)
#define OUTPUT  (1u)

#define RF5_1 LATF|=0b0000000000100000 //RST
#define RF5_0 LATF&=0b1111111111011111

#define RF4_1 LATF|=0b0000000000010000 //E
#define RF4_0 LATF&=0b1111111111101111

#define RF1_1 LATF|=0b0000000000000010 //RW
#define RF1_0 LATF&=0b1111111111111101

#define RF0_1 LATF|=0b0000000000000001 //RS
#define RF0_0 LATF&=0b1111111111111110

#define RB5_1 LATB|=0b0000000000100000 //CS2
#define RB5_0 LATB&=0b1111111111011111

#define RB4_1 LATB|=0b0000000000010000 //CS1
#define RB4_0 LATB&=0b1111111111101111

/* GLOBAL CONSTANTS */
extern const char DISPLAY1_bmp[1024];
extern const char zvezde[1024];
extern const char fontBIG[];
extern const char truck[1024];
extern const char bank[1024];

/* GLOBAL FUNCTIONS */
void SetRST(unsigned char vrednost);
void SetE(unsigned char vrednost);
void SetRW(unsigned char vrednost);
void SetRS(unsigned char vrednost);
void SetCS2(unsigned char vrednost);
void SetCS1(unsigned char vrednost);
void ConfigureLcdPins(void);
void ConfigureLcdData(unsigned char direction);
void SetLcdData(unsigned char vrednost);
unsigned char ReadLcdData(void);
void LcdStrobeData(void);
void LcdInstructionWrite(unsigned char u8Instruction);
void LcdDelay(unsigned int u32Duration);
void LcdWaitBusy(void);
void LcdGotoX(unsigned char x);
void LcdGotoY(unsigned char y);
void LcdGotoXY(unsigned char x, unsigned char y);
void LcdSelectStartline(unsigned char startna_linija);
void LcdSelectSide(unsigned char u8LcdSide);
unsigned char LcdDataRead(void);
void LcdInit(void);
void LcdDataWrite(unsigned char u8Data);
void LcdClearScreen(void);
void LcdFillScreen(void);
void LcdDisplayPicture(unsigned char *slika);
void LcdSetDot(unsigned char u8Xaxis, unsigned char u8Yaxis);
void LcdClearDot(unsigned char u8Xaxis, unsigned char u8Yaxis);
void LcdDrawCircle(unsigned char u8CenterX, unsigned char u8CenterY, unsigned char u8Radius);
void LcdDrawRect(unsigned char u8Xaxis1,unsigned char u8Yaxis1, unsigned char u8Xaxis2, unsigned char u8Yaxis2);
void LcdPutChar(char AskiKod);
void LcdPutCharBig(char AskiKod);
void LcdPrintf(char *au8Text);
void LcdShowGrid(unsigned char grid_padding);

#endif	/* GLCD_H_ */

