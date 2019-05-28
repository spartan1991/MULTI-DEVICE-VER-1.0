#include "screens.h"

byte bootScreen(byte percent){
	
	LcdProgressBar(4, 26, 75, 2, 0, 0, PIXEL_ON, percent);
	return OK;
}

byte bootTextScreen(byte percent){
	
	LcdGotoXYFont(1, 2);
	LcdFStr(FONT_1X, (byte*)"Loading...");
	LcdProgressBar(4, 26, 75, 2, 0, 0, PIXEL_ON, percent);
	return OK;
}

byte homeScreen(byte* operatorName, byte batPercent, byte gsmSignal, byte gpsSignal){
	
	return OK;
}

byte mainMenuScreen(byte choice){
	
	return OK;
}
