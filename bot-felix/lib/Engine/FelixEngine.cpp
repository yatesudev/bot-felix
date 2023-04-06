/**
 * @file ComponentsUtility.cpp
 * @brief Utility functions for managing components in a routine
 */
#include <ComponentsUtility.cpp>

namespace Routine {
  String CurrentRoutine = "";
  //StartUP Routine
  bool startUP_isDone = false;
  
    /**
   * @brief StartUp routine function
   * @param time Time for the routine to run
   * @return Returns true if the routine is done, false otherwise
   */
  bool StartUp(int time){
    if (!startUP_isDone) {
      unsigned long StartUp_time_now = millis();
      while (true) {
        setRGB(0, 0, 25);
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

bool isCurrentlyLearning = false;
namespace LearningPhase {
  
  String Header = "Right ear: +";
  String Body = "Left ear: OK";

  int repeatsCount = 1;

  int currentType = 0;
  int maxTypes = 3;

  int methodNum = 0;
  int methodsLearnTime[][2] = {{1,2},{25, 5}, {45, 10}, {90, 20}, {180, 30}};
  String methods[] = {"test","Pomodoro", "Felidoro", "Ultradian Rhythm", "Beast Mode"};

  namespace manageTimer {
    unsigned long time_length = 0;
    unsigned long time_break = 0;

    unsigned long time_current = 0;
    unsigned long time_start = 0;

    unsigned long displayTime = 0;
    
    
    /**
     * @brief Start time counter
     * @param time Time for the timer
     */
    void startTimeCounter(int time) {
      time_length = (time*60)*1000; //(time[0]  * 10000) - 5*60*1000;

      time_start = millis();
      time_current = millis();
    }
    
      /**
     * @brief Get time left on the timer
     * @return Time left on the timer in seconds
     */
    int getTimeLeft() {
      time_current = millis();
      if (time_current - time_start > time_length) {
        time_start = millis();
        time_current = millis();
      }
      displayTime = time_length - (time_current - time_start);

      if (displayTime < 0) { 
        displayTime = 0;
      }
      return displayTime / 1000;
    }
  }
  
    /**
   * @brief Setup Learning Phase
   * @param type Type of learning phase
   */
  void SetupLearningPhase(int type) {

    if (type == 1) {
      Header = "Learn ";
      Body = String(repeatsCount) + " times";

      if (isButtonRightEarPressed()) {
        repeatsCount++;
        if (repeatsCount > 10) {
          repeatsCount = 1;
        }
      }
    }

    if (type == 2) {
      Header = "Method: ";
      Body = methods[methodNum];

      if (isButtonRightEarPressed()) {
        methodNum++;
        if (methodNum >= Utility::ArrayLength(methods)) {
          methodNum = 0;
        }
      }
    }

    if (type == 3) {
      //Display asynchroneous message here
      isCurrentlyLearning = true;

      // initialization once each Learning Phase (not time sequence)
      if (!initializedSequence) {
        initializedSequence = true;
        repeatsCount = repeatsCount * 2;
        //first time Selected to work
        manageTimer::startTimeCounter(methodsLearnTime[methodNum][0]);
      }


      //Time over manager
      if (manageTimer::getTimeLeft() != 0) {
        //Display Text and Emoji while learning
        Header = formatTimeToString(manageTimer::getTimeLeft());
        Body = ComponentsUtility::GenerateMotivationalBody();
        ComponentsUtility::SwitchBetweenEmojis({HAPPY, SMILE, SLEEP}, 30000);
      } else { 
          if (globalBreak == false) {
            //Display asynchroneous message here
            
            setEmoji(HAPPY);
            tone(GetSpeakerPin(), 50);
            setRGB(50, 0, 0);
            delay(1000);
            tone(GetSpeakerPin(), 100);
            setRGB(0, 50, 0);
            delay(1000);
            tone(GetSpeakerPin(), 200);
            setRGB(0, 0, 50);

            //update Happy Position
            setEmoji(HAPPY);

            displayText("Good job!", "Level UP!");
            delay(1000);

            noTone(GetSpeakerPin());

            if (repeatsCount > 0) {
              repeatsCount--;
            }

            displayText("Remaining:", String(repeatsCount) + " times");

            delay(2000);
            globalBreak = true;
          } else {
            globalBreak = false;
          }

          //Time window selector
      if (globalBreak == true) {
        manageTimer::startTimeCounter(methodsLearnTime[methodNum][1]);    
      } else {
        manageTimer::startTimeCounter(methodsLearnTime[methodNum][0]);
        setRGB(25, 0, 0);
      } 

        if (repeatsCount == 0) {
          manageTimer::time_break = 0;
          manageTimer::time_current = 0;
          manageTimer::time_start = 0;
          manageTimer::displayTime = 0;
          
          methodNum = 0;
          repeatsCount = 0;
          currentType = 0;
          isCurrentlyLearning = false;
          initializedSequence = false;
          return;
        } else {
          //globalBreak = true;
        }

        return;
      }
    }
  }
}

namespace BackgroundMenu {
  String Header = "Background";
  String Body = "Left ear: confirm";

  int currentBackground = 0;
  String backgrounds[] = {"Temperature", "Humidity", "Battery", "Time"};

  String bg_temp = String(getTemperatureValue()) + " C";
  String bg_hum = String(getHumidityValue()) + " %";
  String bg_bat = String(getBatteryLevel()) + " %";

  unsigned long time_UpdateScreen = millis();
  
  /**
 * @brief Set up the BackgroundMenu with updated background information.
 *
 * This function updates the background information displayed in the BackgroundMenu
 * by switching between different backgrounds and displaying the corresponding
 * information on the screen. It uses variables and functions such as `Header`, `Body`,
 * `currentBackground`, `backgrounds[]`, `bg_temp`, `bg_hum`, `bg_bat`, `time_UpdateScreen`,
 * `Utility::ArrayLength()`, `getTemperatureValue()`, `getHumidityValue()`,
 * `getBatteryLevel()`, `getDateTimeString()`, and `displayText()`.
 *
 * @return None
 */
  void SetupBackgroundMenu() {
    ComponentsUtility::SwitchBetweenEmojis({HAPPY, SMILE, SLEEP}, 6000);
    if ((unsigned long)(millis() - time_UpdateScreen) > 3000) {

      time_UpdateScreen = millis();
      currentBackground++;

      if (currentBackground >= Utility::ArrayLength(backgrounds)) {
        bg_temp = String(getTemperatureValue()) + " C";
        bg_hum = String(getHumidityValue()) + " %";
        bg_bat = String(getBatteryLevel()) + " %";
        currentBackground = 0;
      }
    }

    if (currentBackground == 0) {
      Header = backgrounds[currentBackground];
      Body = bg_temp;
    }

    if (currentBackground == 1) {
      Header = backgrounds[currentBackground];
      Body = bg_hum;
    }

    if (currentBackground == 2) {
      Header = backgrounds[currentBackground];
      Body = bg_bat;
    }

    if (currentBackground == 3) {
      Header = backgrounds[currentBackground];
      Body = getDateTimeString();
    }

    displayText(Header, Body);
  }
}
