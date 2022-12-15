#include "DisplayManager.hpp"

bool displayText(String Header, String longText){
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

bool resultOfDisplaying() {
  bool result = StrLib_Li < new_li;
  new_li = StrLib_Li; 
  return (result);
}

void StrLib_displayShortTextInLoop(String Header, String longText) {
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

void StrLib_displayTextInLoop(String Header, String longText){
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

//----------------------------------
boolean StrLib_isUsed = false;
void StrLib_displayTextOnce(String Header, String longText){
  if (!StrLib_isUsed && (longText.length() > 16)) {
    int headerLength = Header.length();
    String stringAddition = "";
    for (int i=0; i < ((16-headerLength)/2); i++){
      stringAddition = stringAddition + " ";
    }
    Header = stringAddition + Header;

    StrLib_isUsed = true;
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(Header);
    lcd.setCursor(0, 1);
    lcd.print(StrLib_Scroll_LCD_Left(longText));
    
    double StrLib_second = 0;
    unsigned long StrLib_time_now = 0;

    while (true) {
      //wait 1 sec
      if ((unsigned long)(millis() - StrLib_time_now)>3000) {
        break;
      } 
    }
    
    while (true){

      if ((unsigned long)(millis() - StrLib_time_now)>150) {
        StrLib_time_now = millis();
        StrLib_second = StrLib_second + 0.15;
        lcd.setCursor(0, 1);
        lcd.print(StrLib_Scroll_LCD_Left(longText));
      } 

      if (StrLib_Lii >= longText.length()) {
        lcd.clear();
        StrLib_isUsed = false;
        break;
      }
    }
    StrLib_Clear_Scroll_LCD_Left();
  } else if (!StrLib_isUsed) {
    int headerLength = Header.length();
    String stringAddition = "";
    for (int i=0; i < ((16-headerLength)/2); i++){
      stringAddition = stringAddition + " ";
    }
    Header = stringAddition + Header;

    int longLength = longText.length();
    String stringAddition2 = "";
    for (int i=0; i < ((16-longLength)/2); i++){
      stringAddition2 = stringAddition2 + " ";
    }
    longText = stringAddition2 + longText;

    StrLib_isUsed = true;
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(Header);
    lcd.setCursor(0, 1);
    lcd.print(longText);
    
    double StrLib_second = 0;
    unsigned long StrLib_time_now = 0;

    while (true) {
      //wait 1 sec
      if ((unsigned long)(millis() - StrLib_time_now)>5000) {
        lcd.clear();
        break;
      } 
    }
  }
}



String StrLib_Scroll_LCD_Left(String StrDisplay){
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

void StrLib_Clear_Scroll_LCD_Left(){
  StrLib_Li=16;
  StrLib_Lii=0;
  new_li = 0;
}
