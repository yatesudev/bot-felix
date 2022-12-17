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

namespace Routine {

  //StartUP Routine
  unsigned long StartUp_time_now = millis();
  bool StartUp(){
    setEmoji(SMILE);
    displayText("Felix:", "Yoooo!");

    if ((unsigned long)(millis() - StartUp_time_now)> 3000) {
      return true;
    } else {
      return false;
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
