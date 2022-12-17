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
  void StartUp(){
    setEmoji(SMILE);
    displayText("Felix:", "Yoooo!");
  }

  void Sleep(){
    setEmoji(SLEEP);
    displayText("Felix:", "zZzzZzzZzzZzzZzzZzzZzzZzzZzzZzzZzzZzzZz");
  }

  void AwaitInput(){
    setEmoji(HAPPY);
    displayText("Felix:", "Bro, Please do something.");
  }
}
