#include "system.h"
#include "models.h"
#include "stm32f10x_gpio.h"

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

void resetPressedButton(void){
	
	setPressedButton(NULL);
}

uint8_t getPressedButton(void){
	
	return *buttonPtr;
}

// MOUSE
MOUSE_StateData_TypeDef mouseData = {40, 42, 0};
MOUSE_StateData_TypeDef* mouseDataPtr = &mouseData;

MOUSE_StateData_TypeDef getMouseData(){

	return *mouseDataPtr;
}

void mouseKeyboardHendler(void){
	
	uint8_t* mouseX = &mouseDataPtr->x;
	uint8_t* mouseY = &mouseDataPtr->y;
	
	switch(getPressedButton()){
		
		case LEFT: {
		
			if(*mouseX>0){*mouseX-=1;}
			//if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)==0)  // TEST (REFACTOR)
			resetPressedButton();
			
		};break;
		
		case UP: {
		
			if(*mouseY>0){*mouseY-=1;}
			//if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)==0)  // TEST (REFACTOR)
			resetPressedButton();
			
		};break;
		
		case RIGHT: {
		
			if(*mouseX<83-3){*mouseX+=1;}
			//if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)==0)  // TEST (REFACTOR)
			resetPressedButton();
			
		};break;
		
		case DOWN: {
		
			if(*mouseY<47-3){*mouseY+=1;}
			//if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)==0)  // TEST (REFACTOR)
			resetPressedButton();
			
		};break;
		
		case CENTER: {
		
		};break;
	}
}

