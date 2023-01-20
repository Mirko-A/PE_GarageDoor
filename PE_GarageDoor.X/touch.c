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
    static uint32_t last_update_time = 0;
    uint32_t ticks_ms = getTickMs();
    
    // Coords already updated in this millisecond
    if (last_update_time == ticks_ms) return;
    
    if ((ticks_ms % 20) == 0)
    {
        //Citamo za x
        //Vode horizontalni tranzistori
        DRIVE_A = PIN_HIGH;  //RC13
        DRIVE_B = PIN_LOW; //RC14
    }
    else if ((ticks_ms % 15) == 0)
    {
        // Touch je pritisnut
        if (touch_data_x > AD_X_MIN)
        {
            x_raw = touch_data_x; //Vrednost sa BOTTOM PIN	
        }
        else
        {
        
        }
    }
    else if ((ticks_ms % 10) == 0)
    {
        //Citamo za y
        //Vode vertikalni tranzistori
        DRIVE_A = PIN_LOW;  //RC13
        DRIVE_B = PIN_HIGH;  //RC14
    }
    else if ((ticks_ms % 5) == 0)
    {
        y_raw = touch_data_y; //Vrednost sa LEFT PIN	
    
        // Touch je pritisnut
        if (x_raw > AD_X_MIN)
        {
            x_coord = ((x_raw - AD_X_MIN) * AD_X_MAX);
        }
        else
        {
            x_coord = 0;
        }
        
        // Touch je pritisnut
        if (y_raw > AD_Y_MIN)
        {
            y_coord = ((y_raw - AD_Y_MIN) * AD_Y_MAX);
        }
        else
        {
            y_coord = 0;
        }
    }	
    
    // Save update time for next function call
    last_update_time = ticks_ms;
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
											
