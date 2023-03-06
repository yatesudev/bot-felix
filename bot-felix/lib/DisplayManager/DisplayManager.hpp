
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);

bool displayText(String Header, String longText);
bool resultOfDisplaying();
void StrLib_displayShortTextInLoop(String Header, String longText);
void StrLib_displayTextOnce(String Header, String longText);
void StrLib_displayTextInLoop(String Header, String longText);
void StrLib_Clear_Scroll_LCD_Left();
String StrLib_Scroll_LCD_Left(String longText);


int StrLib_Li          = 16;
int StrLib_Lii         = 0; 

int new_li             = 0;

double StrLib_second = 0;
unsigned long StrLib_time_now = 0;

String currentString = "";

bool StrLib_isInitialized = false;
bool StrLib_firstDisplay = false;
