#include "screens.h"
#include "models.h"
#include "system.h"

MOUSE_StateData_TypeDef mData;

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

byte logInScreen(byte val){
	
	LcdGotoXYFont(0, 0);
	LcdFStr(FONT_1X, (byte*)"Login:");
	LcdGotoXYFont(0, 1);
	LcdFStr(FONT_1X, (byte*)"vc_system@ukr.net");
	LcdGotoXYFont(0, 3);
	LcdFStr(FONT_1X, (byte*)"Password:");
	LcdGotoXYFont(0, 4);
	LcdFStr(FONT_1X, (byte*)"vovik1991");
	
	return OK;
}

byte mouseLayerScreen(byte val){
	
	mData = getMouseData();
	mouseKeyboardHendler();
	LcdMouse(mData.x, mData.y, 1, 3, PIXEL_ON);
	
	return OK;
}

byte homeScreen(byte* operatorName, byte batPercent, byte gsmSignal, byte gpsSignal){
	
	return OK;
}

byte mainMenuScreen(byte choice){
	
	return OK;
}
