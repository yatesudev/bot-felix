
#include <Setup.cpp>

const float temp[2] = {16, 25};
const float hum[2] = {40, 80};

namespace Utility {
  bool isTempAndHumOk() {
    if (getTemperatureValue() > temp[0] && getTemperatureValue() < temp[1] && getHumidityValue() < hum[0] && getHumidityValue() > hum[1]) {
      return true;
    } else {
      return false;
    }
  }

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

  String formatTimeToString(int time) {
    int minutes = time / 60;
    int seconds = time % 60;

    String local_seconds = "";
    String local_minutes = "";
    
    if (seconds < 10) {
      local_seconds = "0" + String(seconds);
    } else {
      local_seconds = String(seconds);
    }

    if (minutes < 10) {
      local_minutes = "0" + String(minutes);
    } else {
      local_minutes = String(minutes);
    }

    String outputString = local_minutes + ":" + local_seconds;
    return outputString;
  }
  
  template<typename T,int N> 
  int ArrayLength(T (&array)[N]) {
    return sizeof(array) / sizeof(array[0]);
  }

  String ArrayLength(std::vector <String> array) {
    return String(array.size());
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