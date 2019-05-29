#include "screens.h"
#include "cpu-init.h"

int main(void){
	
	system_init();
	LcdInit();
	LcdClear();
	//logInScreen(1);
	//bootTextScreen(50);
	LcdMouse(55, 35, 3, PIXEL_ON, 1);
	
	while(1){LcdUpdate();};
	LcdUpdate();
}
