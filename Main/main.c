#include "screens.h"
#include "cpu-init.h"

int main(void){
	
	system_init();
	LcdInit();
	LcdClear();
	bootTextScreen(50);
	LcdUpdate();
}
