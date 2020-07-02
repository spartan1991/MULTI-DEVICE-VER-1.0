#include "system.h"
#include "models.h"
#include "stm32f10x_gpio.h"

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
MOUSE_StateData_TypeDef mouseData = {40, 42, 0, 0};
MOUSE_StateData_TypeDef* mouseDataPtr = &mouseData;

// CURSORS
uint8_t cursorsDataY = 1;
uint8_t *cursorsDataYPtr = &cursorsDataY;

uint8_t getCursorsData(void){
	
	return *cursorsDataYPtr;
}

MOUSE_StateData_TypeDef getMouseData(void){

	return *mouseDataPtr;
}

uint8_t mouseKeyboardHendler(void){
	
	uint8_t* mouseX = &mouseDataPtr->x;
	uint8_t* mouseY = &mouseDataPtr->y;
	uint8_t* mouseCourse = &mouseDataPtr->course;
	uint8_t* mouseAction = &mouseDataPtr->action;
	
	switch(getPressedButton()){
		
		case LEFT: {
		
			if(*mouseX>0){
				*mouseX-=1;
				*mouseCourse=0;
				*mouseAction=0;
			}
			//if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)==0)  // TEST (REFACTOR)
			resetPressedButton();
			
		};break;
		
		case UP: {
		
			if(*mouseY>0){
				*mouseY-=1;
				*mouseAction=0;
			}
			//if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)==0)  // TEST (REFACTOR)
			resetPressedButton();
			
		};break;
		
		case RIGHT: {
		
			if(*mouseX<83-3){
				*mouseX+=1;
				*mouseCourse=1;
				*mouseAction=0;
			}
			//if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)==0)  // TEST (REFACTOR)
			resetPressedButton();
			
		};break;
		
		case DOWN: {
		
			if(*mouseY<47-3){
				*mouseY+=1;
				*mouseAction=0;
			}
			//if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)==0)  // TEST (REFACTOR)
			resetPressedButton();
			
		};break;
		
		case CENTER: {
			
			*mouseAction=1;
			return 1;
			
		};break;
	}
	
	return 0;
}
	
void cursorsKeyboardHendler(void){
	
	switch(getPressedButton()){
		
		case UP: {
		
			if(*cursorsDataYPtr>1){*cursorsDataYPtr-=1;}
			resetPressedButton();
			
		};break;
		
		case DOWN: {
		
			if(*cursorsDataYPtr<5){*cursorsDataYPtr+=1;}
			resetPressedButton();
			
		};break;
		
		case CENTER: {
		
		};break;
	};
 }
