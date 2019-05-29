#include "screens.h"
#include "cpu-init.h"

int main(void){
	
	system_init();
	LcdInit();
	LcdClear();
	
	while(1){
		
	  LcdClear();
		mouseLayerScreen(1);
		LcdUpdate();
	};
}
