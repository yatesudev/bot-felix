#include <Setup.cpp>

namespace Utility {
  bool RegisterRoutine(int time, int (*routine)()){
    unsigned long StartUp_time_now = millis();
    while (true) {
      routine();

      if ((unsigned long)(millis() - StartUp_time_now) > time) {
        break;
      }
    }
    return true;
  }

  String getBatteryLevel() {
    return String(Battery.getBatteryChargeLevel());
  }
  
  template<typename T,int N> 
  int ArrayLength(T (&array)[N]) {
    return sizeof(array) / sizeof(array[0]);
  }

  bool isBotSleeping() {
    return readTilt(PIN_tilt);
  }

  unsigned long time_now_LASTINPUT = millis();
  unsigned long time_now_BUTTONRIGHT = millis();
  bool isButtonRightEarPressed() {

    if(digitalRead(PIN_buttonStart) == HIGH){
      if ((unsigned long)(millis() - time_now_BUTTONRIGHT) > 1000) {
        time_now_BUTTONRIGHT = millis();
        time_now_LASTINPUT = millis();
        return true;
      }
    }
    return false;
  }

  unsigned long time_now_BUTTONLEFT = millis();
  bool isButtonLeftEarPressed() {
    if(digitalRead(PIN_buttonRepeats) == HIGH){
      if ((unsigned long)(millis() - time_now_BUTTONLEFT) > 1000) {
        time_now_BUTTONLEFT = millis();
        time_now_LASTINPUT = millis();
        return true;
      }
    }
    return false;
  }

  bool lastInputHigherThan(int time) {
    if ((unsigned long)(millis() - time_now_LASTINPUT) > time) {
      return true;
    }
    return false;
  }

  void setupLearningPhase(int &val) {
    String outputString = "Repeats: " + String(val); //converts int to string, so it can be displayed
    displayText("Setup Learning:", outputString); //
    if (isButtonRightEarPressed()) {
      val++;
      Serial.println(val);
      delay(500);
      if (val > 10) {
        val = 0;
      }
    }
  }
  
  void DebugComponents(){
    Serial.println(readTilt(PIN_tilt));
  }
}

using namespace Utility;

namespace ComponentsUtility{
  
  //SWITCH BETWEEN DIALOG TEXT
  unsigned long SBDT_time_now = millis();
  unsigned long SBDT_oldTime = 0;
  void SwitchBetweenDialogText(String Header, std::vector <String> textArray,const int &time){
    if (((unsigned long)(millis() - SBDT_time_now) > time) || (SBDT_oldTime != SBDT_time_now)) { //switches if time is over or if the time is reset
      SBDT_time_now = millis();
      SBDT_oldTime = SBDT_time_now;
      int randomNumber = (rand() % textArray.size());
      displayText(Header, textArray[randomNumber]);  
    }  
  }

  //SWITCH BETWEEN EMOJIS
  unsigned long SBE_time_now = millis();
  unsigned long SBE_oldTime = 0;
  int SBE_randomNumber = -1;
  void SwitchBetweenEmojis(std::vector <emojiType> emojiArray,const int &time){
    if (SBE_randomNumber == -1) {
      SBE_randomNumber = (rand() % emojiArray.size());
    }
    setEmoji(emojiArray[SBE_randomNumber]);

    if (((unsigned long)(millis() - SBDT_time_now) > time) || (SBDT_oldTime != SBDT_time_now)) { //switches if time is over or if the time is reset
      SBE_time_now = millis();
      SBE_oldTime = SBDT_time_now;
      SBE_randomNumber = (rand() % emojiArray.size());
    }  
  }

 //SWITCH BETWEEN EMOJIS WITH DIALOGS
  unsigned long SBEWD_time_now = millis();
  unsigned long SBEWD_oldTime = 0;
  int SBEWD_randomNumber = -1;
  void SwitchBetweenEmojisWithDialogs(std::vector <emojiType> emojiArray, std::vector <String> textArray,const int &time){
    if (SBEWD_randomNumber == -1) {
      SBEWD_randomNumber = (rand() % emojiArray.size());
    }

    setEmoji(emojiArray[SBEWD_randomNumber]);

    if(((unsigned long)(millis() - SBEWD_time_now) > time) || (SBEWD_oldTime != SBEWD_time_now)) { //switches if time is over or if the time is reset
      SBEWD_time_now = millis();
      SBEWD_oldTime = SBEWD_time_now;
      SBEWD_randomNumber = (rand() % emojiArray.size());
      displayText("Felix:", textArray[SBEWD_randomNumber]);
    }
  }
}

namespace Routine {
  String CurrentRoutine = "";
  //StartUP Routine
  bool startUP_isDone = false;
  bool StartUp(int time){
    if (!startUP_isDone) {
      unsigned long StartUp_time_now = millis();
      while (true) {
        setEmoji(SMILE);
        int timeNow = millis();
        if ((unsigned long)(millis() - timeNow) > 2000) {
          displayText("Felix:", "Welcome!");
        } else {
          //displayText("My Battery", "is at: "+ getBatteryLevel()+"%");
        }
        CurrentRoutine = "StartUp";

        if ((unsigned long)(millis() - StartUp_time_now) > time) {
          startUP_isDone = true;
          break;
        }
        displayText("Felix:", String((unsigned long)(millis() - StartUp_time_now)));
      }
      return false;
    } else {
      return true; 
    }
  }
}