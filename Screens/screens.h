#include "stdint.h"
#include "n3310.h"

byte bootScreen(byte percent);
byte bootTextScreen(byte* text, byte percent);
byte homeScreen(byte* operatorName, byte batPercent, byte gsmSignal, byte gpsSignal);
byte mainMenuScreen(byte choice);
