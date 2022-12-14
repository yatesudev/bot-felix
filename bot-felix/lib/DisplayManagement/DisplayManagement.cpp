#include "DisplayManagement.hpp"



bool DisplayManagement::displayText(String Header, String longText){
  if (currentString != longText) {
    StrLib_Clear_Scroll_LCD_Left();
    currentString = longText;
  }
  
  if ((longText.length() > 16)) {
    StrLib_displayTextInLoop(Header, longText);
  } else {
    StrLib_displayShortTextInLoop(Header, longText);
  }

  return resultOfDisplaying();
}

bool DisplayManagement::resultOfDisplaying() {
  bool result = StrLib_Li < new_li;
  new_li = StrLib_Li; 
  return (result);
}

void DisplayManagement::StrLib_displayShortTextInLoop(String Header, String longText) {
  int headerLength = Header.length();
  String stringAddition = "";
  for (int i=0; i < ((16-headerLength)/2); i++){
    stringAddition = stringAddition + " ";
  }
  Header = stringAddition + Header ;

  int longLength = longText.length();  
  String stringAddition2 = "";
  for (int i=0; i < ((16-longLength)/2); i++){
    stringAddition2 = stringAddition2 + " ";
  }
  longText = stringAddition2 + longText + stringAddition2 + stringAddition2;

  lcd.setCursor(0, 0);  
  lcd.print(Header);
  lcd.setCursor(0, 1);
  lcd.print(longText);

}

void DisplayManagement::StrLib_displayTextInLoop(String Header, String longText){
  int headerLength = Header.length();
  String stringAddition = "";
  for (int i=0; i < ((16-headerLength)/2); i++){
    stringAddition = stringAddition + " ";
  }
  Header = stringAddition + Header;

  if (!StrLib_firstDisplay) {
    StrLib_firstDisplay = true;
    lcd.setCursor(0, 0);
    lcd.print(Header);
    lcd.setCursor(0, 1);
    lcd.print(StrLib_Scroll_LCD_Left(longText));
  }

  if (((unsigned long)(millis() - StrLib_time_now)>2000) || StrLib_isInitialized) {
      //wait 1 sec
      StrLib_isInitialized = true;
    if ((unsigned long)(millis() - StrLib_time_now)>500) {
      StrLib_time_now = millis();
      lcd.setCursor(0, 0);
      lcd.print(Header);
      lcd.setCursor(0, 1);
      lcd.print(StrLib_Scroll_LCD_Left(longText));
    //break;
    } 
  }

  if (StrLib_Lii >= longText.length()) {
    lcd.clear();
    StrLib_isInitialized = false;
    StrLib_firstDisplay = false;
  }
}


String DisplayManagement::StrLib_Scroll_LCD_Left(String StrDisplay){
  String result;
  String StrProcess = "" + StrDisplay + "                ";
  result = StrProcess.substring(StrLib_Li,StrLib_Lii);
  StrLib_Li++;
  StrLib_Lii++;
  if (StrLib_Li>StrProcess.length()){
    StrLib_Li=16;
    StrLib_Lii=0;
  }
  return result;
}

void DisplayManagement::StrLib_Clear_Scroll_LCD_Left(){
  StrLib_Li=16;
  StrLib_Lii=0;
  new_li = 0;
}

