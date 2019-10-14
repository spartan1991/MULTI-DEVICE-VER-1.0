#include "screens.h"
#include "cpu-init.h"

MenuData_TypeDef mainMenu = {
	
	"^^^^MENU^^^^",
	"GSM",
	"GPS",
	"WI-FI",
	"RESERVE1",
	"RESERVE2",
};

int main(void){
	
	system_init();
	LcdInit();
	LcdClear();
	
	while(1){
		
	  LcdClear();
		
		//testScreen(1);
		//mouseLayerScreen(1);
		MenuScreen(mainMenu);
		cursorsKeyboardHendler();
		LcdUpdate();
	};
}
