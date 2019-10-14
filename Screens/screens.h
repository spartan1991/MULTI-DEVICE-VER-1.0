#include "system.h"
#include "models.h"
#include "n3310.h"

byte bootScreen(byte percent);
byte bootTextScreen(byte percent);
byte homeScreen(byte* operatorName, byte batPercent, byte gsmSignal, byte gpsSignal);
byte MenuScreen(MenuData_TypeDef menuData);
byte logInScreen(byte val);
byte mouseLayerScreen(byte val);
byte testScreen(byte choice);
