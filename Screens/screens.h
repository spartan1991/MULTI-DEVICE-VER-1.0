#include "system.h"
#include "n3310.h"

byte bootScreen(byte percent);
byte bootTextScreen(byte percent);
byte homeScreen(byte* operatorName, byte batPercent, byte gsmSignal, byte gpsSignal);
byte mainMenuScreen(byte choice);
byte logInScreen(byte val);
byte mouseLayerScreen(byte val);
byte testScreen(byte choice);
