
/***********************************************************************************************

    @file Setup.cpp
    @brief Contains utility functions for setting up and managing system components
    ************************************************************************************************/
#include <Setup.cpp>

const float temp[2] = {16, 25};
const float hum[2] = {40, 80};

namespace Utility {
  /**
    @brief Checks if temperature and humidity values are within acceptable range
    @return true if temperature and humidity values are within range, false otherwise
    */
  bool isTempAndHumOk() {
    if (getTemperatureValue() > temp[0] && getTemperatureValue() < temp[1] && getHumidityValue() < hum[0] && getHumidityValue() > hum[1]) {
      return true;
    } else {
      return false;
    }
  } 
  
  /**
    @brief Executes a routine for a specified time duration
    @param time Time duration in milliseconds for which routine should be executed
    @param routine Function pointer to the routine to be executed
    @return true if routine execution is completed, false otherwise
    */
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
  
  /**
    @brief Gets battery level as a string
    @return String representation of battery charge level
    */
  String getBatteryLevel() {
    return String(Battery.getBatteryChargeLevel());
  }
  
  /**
    @brief Formats time in seconds to string in minutes:seconds format
    @param time Time in seconds
    @return String representation of time in minutes:seconds format
    */
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
  
  /**
    @brief Calculates length of an array
    @tparam T Data type of the array elements
    @tparam N Size of the array
    @param array Reference to the array
    @return Length of the array
    */
  template<typename T,int N> 
  int ArrayLength(T (&array)[N]) {
    return sizeof(array) / sizeof(array[0]);
  }
  
  /***********************************************************************************************

    @file Setup.cpp
    @brief Contains utility functions for setting up and managing system components
    ************************************************************************************************/

#include <Setup.cpp>

const float temp[2] = {16, 25}; ///< Array storing temperature threshold values
const float hum[2] = {40, 80}; ///< Array storing humidity threshold values

namespace Utility {

/**

    @brief Checks if temperature and humidity values are within acceptable range
    @return true if temperature and humidity values are within range, false otherwise
    */
    bool isTempAndHumOk() {
    if (getTemperatureValue() > temp[0] && getTemperatureValue() < temp[1] && getHumidityValue() < hum[0] && getHumidityValue() > hum[1]) {
    return true;
    } else {
    return false;
    }
    }

/**

    @brief Executes a routine for a specified time duration

    @param time Time duration in milliseconds for which routine should be executed

    @param routine Function pointer to the routine to be executed

    @return true if routine execution is completed, false otherwise
    */
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

/**

    @brief Gets battery level as a string
    @return String representation of battery charge level
    */
    String getBatteryLevel() {
    return String(Battery.getBatteryChargeLevel());
    }

/**

    @brief Formats time in seconds to string in minutes:seconds format

    @param time Time in seconds

    @return String representation of time in minutes:seconds format
    */
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

/**

    @brief Calculates length of an array
    @tparam T Data type of the array elements
    @tparam N Size of the array
    @param array Reference to the array
    @return Length of the array
    */
    template<typename T,int N>
    int ArrayLength(T (&array)[N]) {
    return sizeof(array) / sizeof(array[0]);
    }

/**
    @brief Calculates length of a vector
    @param array Vector for which length needs to be calculated
    @return Length of the vector
    */
  String ArrayLength(std::vector <String> array) {
    return String(array.size());
  }
  
  /**
    @brief Checks if bot is in sleep mode
    @return true if bot is sleeping, false otherwise
    */
  bool isBotSleeping() {
    return readTilt(PIN_tilt);
  }

  unsigned long time_now_LASTINPUT = millis();
  unsigned long time_now_BUTTONRIGHT = millis();
  
  /**
    @brief Checks if right ear button is pressed
    @return true if right ear button is pressed, false otherwise
    */
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
 /**
 * @brief Check if the left ear button is pressed.
 *
 * @return true if the left ear button is pressed and enough time has elapsed, false otherwise.
 */
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
  
  /**
 * @brief Check if the time since the last input is higher than a given value.
 *
 * @param time The time threshold in milliseconds.
 * @return true if the time since the last input is higher than the given value, false otherwise.
 */
  bool lastInputHigherThan(int time) {
    if ((unsigned long)(millis() - time_now_LASTINPUT) > time) {
      return true;
    }
    return false;
  }
  
/**
 * @brief Set up the learning phase with a given value.
 *
 * @param val The value to set up the learning phase.
 */
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
  
  /**
 * @brief Print the tilt reading to the Serial monitor for debugging.
 */
  void DebugComponents(){
    Serial.println(readTilt(PIN_tilt));
  }
}
