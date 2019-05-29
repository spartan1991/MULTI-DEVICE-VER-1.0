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

byte testScreen(byte choice){
	
	LcdProgressBar(1, 1, 3, 30, 1, 0, PIXEL_ON, 75);
	LcdProgressBar(6, 1, 3, 30, 1, 0, PIXEL_ON, 25);
	LcdProgressBar(65, 1, 15, 4, 0, 0, PIXEL_ON, 35);
	LcdLine(81, 2, 81, 4, PIXEL_ON);
	LcdProgressBar(65, 7, 15, 4, 0, 0, PIXEL_ON, 75);
	LcdLine(81, 8, 81, 10, PIXEL_ON);
	
	LcdGotoXYFont(4, 0);
	LcdFStr(FONT_1X, (byte*)"23:33");
	LcdGotoXYFont(3, 2);
	LcdFStr(FONT_1X, (byte*)"Kyivstar");
	LcdGotoXYFont(0, 5);
	LcdFStr(FONT_1X, (byte*)"Menu");
	LcdGotoXYFont(10, 5);
	LcdFStr(FONT_1X, (byte*)"Call");
	
	return OK;
}
