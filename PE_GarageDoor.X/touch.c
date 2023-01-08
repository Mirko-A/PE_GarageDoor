#include "touch.h"

/* LOCAL VARIABLES */
static unsigned int x_raw;
static unsigned int y_raw;

static unsigned int x_coord;
static unsigned int y_coord;
//Formula:
//Coordinate = ( (raw-AD_MIN) / (AD_MAX-AD_MIN) ) * width;	

/* GLOBAL FUNCTIONS */
void initTouchscreen()
{
	TRISCbits.TRISC13 = 0;
	TRISCbits.TRISC14 = 0;
}

void updateCoords(void)
{
	//Citamo za x
	//Vode horizontalni tranzistori
	DRIVE_A = TRUE;  //RC13
	DRIVE_B = FALSE;  //RC14
   	delayMillis(5); //Potrebno vreme za ADC
	
    x_raw = touch_data_x; //Vrednost sa BOTTOM PIN		

	//Citamo za y
	//Vode vertikalni tranzistori
	DRIVE_A = FALSE;  //RC13
	DRIVE_B = TRUE;  //RC14
    delayMillis(5);   //Potrebno vreme za ADC
		
    y_raw = touch_data_y; //Vrednost sa LEFT PIN	

	//Skaliranje koordinata
	//treba pronaci
    x_coord = ((x_raw - AD_X_MIN) * AD_X_MAX);
	y_coord = ((y_raw - AD_Y_MIN) * AD_Y_MAX);
}

/* get coord functions */
unsigned int getX()
{
	return x_coord;
}

unsigned int getY()
{
	return y_coord;
}
											
