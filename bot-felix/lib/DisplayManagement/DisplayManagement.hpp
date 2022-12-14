#ifndef DisplayManagement_hpp
#define DisplayManagement_hpp

#include <arduino.h>
#include "../src/setup.cpp"

class DisplayManagement
{
private:
    int StrLib_Li          = 16;
    int StrLib_Lii         = 0; 

    int new_li             = 0;

    double StrLib_second = 0;
    unsigned long StrLib_time_now = 0;

    String currentString = "";

    bool StrLib_isInitialized = false;
    bool StrLib_firstDisplay = false;

public:
    DisplayManagement() = default;

    bool displayText(String Header, String longText);
    bool resultOfDisplaying();
    void StrLib_displayShortTextInLoop(String Header, String longText);
    void StrLib_displayTextInLoop(String Header, String longText);
    String StrLib_Scroll_LCD_Left(String StrDisplay);
    void StrLib_Clear_Scroll_LCD_Left();
};

#endif /* DisplayManagement_hpp */
