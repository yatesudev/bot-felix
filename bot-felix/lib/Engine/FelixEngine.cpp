#include <Setup.cpp>

namespace Utility {
  bool isBotSleeping() {
    return readTilt(PIN_tilt);
  }

  bool isButtonRightEarPressed() {
    if(digitalRead(PIN_buttonRepeats) == HIGH){
      return true;
    }
    return false;
  }

  bool isButtonLeftEarPressed() {
    if (digitalRead(PIN_buttonStart)== HIGH){
     return true;
    }
    return false;
  }

  void setupLearningPhase(int &val) {
    displayText("Setup Learning:", "Repeats: "+val);
    if (isButtonRightEarPressed()) {
      val++;
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

  //StartUP Routine
  bool startUP_isDone = false;
  bool StartUp(int time){
    if (!startUP_isDone) {
      unsigned long StartUp_time_now = millis();
      while (true) {
        setEmoji(SMILE);
        displayText("Felix:", "Yoooo!");
    
        if ((unsigned long)(millis() - StartUp_time_now) > time) {
          startUP_isDone = true;
          break;
        }
      }
      return false;
    } else {
      return true; 
    }
  }

  //StartUP Routine
  void Sleep(){
    setEmoji(SLEEP);
    displayText("Felix:", "zZzzZzzZzzZzzZzzZzzZzzZzzZzzZzzZzzZzzZz");
  }

  //StartUP Routine
  void AwaitInput(){
    setEmoji(HAPPY);
    displayText("Felix:", "Bro, Please do something.");
  }
}