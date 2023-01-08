#include "touch.h"

/* Local variables */
static unsigned int x_raw;
static unsigned int y_raw;

static int x_coord;
static int y_coord;
//Formula:
//Coordinate = ( (raw-AD_MIN) / (AD_MAX-AD_MIN) ) * width;	


/* Jednom pozivamo */
void initTouchScreen()
{
	TRISCbits.TRISC13 = 0;
	TRISCbits.TRISC14 = 0;
}

/* 
 * Potrebno da se nonstop vrti 
 * CheckInputs ce pozivati
 */
void updateCoords(void)
{
	//Citamo za x
	//Vode horizontalni tranzistori
	DRIVE_A = 1;  //RC13
	DRIVE_B = 0;  //RC14
    
	delayMillis(5); //Potrebno vreme za ADC
				
	
	x_raw = touch_data_x; //Vrednost sa BOTTOM PIN		

	//Citamo za y
	//Vode vertikalni tranzistori
	DRIVE_A = 0;  //RC13
	DRIVE_B = 1;  //RC14

	delayMillis(5);   //Potrebno vreme za ADC
		
	y_raw = touch_data_y; //Vrednost sa LEFT PIN	


	//Skaliranje koordinata
	//treba pronaci
    x_coord = ((x_raw-161)*0.03629);
	y_coord = ((y_raw-500)*0.020725);
}


/* process touch -> gleda sta je pritisnuto -> menja flegove open door, light, alarm */
void processTouch(int *open_door, int *turn_on_light, int *start_alarm)
{
	/* provera da li smo u delu ekrana gde su dugmici */
	if(getY() > (Y_MAX/2))
	{
		/* provera koje dugme */
		if(getX() < 32)
		{
			/* sector 1 */
			/* turn on light */
			if(*turn_on_light == 0) *turn_on_light = 1;
			else *turn_on_light = 0;
		}
		if((getX() > 32) && (getX() < 64))
		{
			/* sector 2 */
			*start_alarm = 0;
			
		}
		if((getX() > 64) && (getX() < 96))
		{
			/* sector 3 */
			*open_door = 0;
		}
		if(getX() > 96)
		{
			/* sector 4 */
			*open_door  = 1;
		}
	}
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




			
		
												
