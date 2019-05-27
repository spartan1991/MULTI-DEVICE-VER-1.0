#include "screens.h"

byte bootScreen(byte percent){
	
	LcdProgressBar(20, 20, 30, 10, 0, 1, PIXEL_ON, percent);
	return OK;
}

byte bootTextScreen(byte* text, byte percent){
	
	return OK;
}

byte homeScreen(byte* operatorName, byte batPercent, byte gsmSignal, byte gpsSignal){
	
	return OK;
}

byte mainMenuScreen(byte choice){
	
	return OK;
}
