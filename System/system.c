#include "system.h"
#include "models.h"

#define LEFT   5
#define UP     8
#define RIGHT  9
#define DOWN   6
#define CENTER 7
#define NULL 0

// BUTTONS
uint8_t pressedButton = 0;
uint8_t* buttonPtr = &pressedButton;

void setPressedButton(uint8_t button){
	
	*buttonPtr = button;
}

uint8_t getPressedButton(void){
	
	return *buttonPtr;
}

// MOUSE
MOUSE_StateData_TypeDef mouseData = {55, 35, 0};
MOUSE_StateData_TypeDef* mouseDataPtr = &mouseData;

MOUSE_StateData_TypeDef getMouseData(){

	return *mouseDataPtr;
}

void mouseKeyboardHendler(void){
	
	uint8_t* mouseX = &mouseDataPtr->x;
	uint8_t* mouseY = &mouseDataPtr->y;
	
	switch(getPressedButton()){
		
		case LEFT: {
		
			if(*mouseX>=0){*mouseX-=1;}
			setPressedButton(NULL);
			
		};break;
		
		case UP: {
		
			if(*mouseY>=0){*mouseY-=1;}
			setPressedButton(NULL);
			
		};break;
		
		case RIGHT: {
		
			if(*mouseX<=83){*mouseX+=1;}
			setPressedButton(NULL);
			
		};break;
		
		case DOWN: {
		
			if(*mouseY<=47){*mouseY+=1;}
			setPressedButton(NULL);
			
		};break;
		
		case CENTER: {
		
		};break;
	}
}

