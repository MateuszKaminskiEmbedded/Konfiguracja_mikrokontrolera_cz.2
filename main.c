#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DeviceConfig.h"



void main()
{
	// Set up all ports to be digital and not analog
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELE = 0;
    ANSELG = 0;
	
	// Set max performance mode
	Set_MaxSpeed_Mode();
	
    TRISACLR = 1 << 0; // Clear bit 0 of TRISA. which makes PORT A bit 0 an output

    LATASET = 1 << 0; // Set bit 0 of PORT A to 1
	
	// Main loop
	while (1)
	{
		// Insert code here
	}
}