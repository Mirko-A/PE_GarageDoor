#include "touch.h"

/* Local variables */
static unsigned int x_raw;
static unsigned int y_raw;

static int x_coord;
static int y_coord;
//Formula:
//Coordinate = ( (raw-AD_MIN) / (AD_MAX-AD_MIN) ) * width;	


/* Lokalna DELAY funkcija u ms */
static void DelayADC(unsigned int stop)
{
	while (getTicks() < stop);
}

/* Jednom pozivamo */
void initTouchScreen()
{
	TRISCbits.TRISC13 = 0;
	TRISCbits.TRISC14 = 0;
}

/* Potrebno da se nonstop vrti */
void processTouchScreen(void)
{
	//Citamo za x
	//Vode horizontalni tranzistori
	DRIVE_A = 1;  //RC13
	DRIVE_B = 0;  //RC14
    
	DelayADC(5); //Potrebno vreme za ADC
				
	
	x_raw = touch_data_1; //Vrednost sa BOTTOM PIN		

	//Citamo za y
	//Vode vertikalni tranzistori
	DRIVE_A = 0;  //RC13
	DRIVE_B = 1;  //RC14

	Delay(5);   //Potrebno vreme za ADC
		
	y_raw = touch_data_2; //Vrednost sa LEFT PIN	


	//Skaliranje koordinata
	//treba pronaci
    x_coord = ((x_raw-161)*0.03629);
	y_coord = ((y_raw-500)*0.020725);
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




			
		
												
