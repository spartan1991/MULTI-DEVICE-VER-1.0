#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "models.h"

#define LEFT   5
#define UP     8
#define RIGHT  9
#define DOWN   6
#define CENTER 7
#define NULL 0

void setPressedButton(uint8_t button);
uint8_t getPressedButton(void);
void mouseKeyboardHendler(void);
void cursorsKeyboardHendler(void);
MOUSE_StateData_TypeDef getMouseData(void);
uint8_t getCursorsData(void);

#endif  /*  _SYSTEM_H_ */

