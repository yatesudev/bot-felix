#include <Setup.cpp>

bool globalBreak = false;
bool initializedSequence = false;

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

  unsigned long GMB_time_now = millis();
  String GMB_bodies[] = {"","","","","","","", "U can do it!", "U the best!", "Keep it up!", "not much left!", "great Job!"};
  int GMB_randomNumber = (rand() % ArrayLength(GMB_bodies));
  String GMB_randomString = "";

  String GenerateMotivationalBody() {
    if (globalBreak) {
      return "take a break";
    } else {
      if ((unsigned long)(millis() - GMB_time_now) > 10000) {
        GMB_time_now = millis();
        GMB_randomNumber = (rand() % ArrayLength(GMB_bodies));
        GMB_randomString = GMB_bodies[GMB_randomNumber];
      }
      return GMB_bodies[GMB_randomNumber];
    }
  }

  //SWITCH BETWEEN EMOJIS
  unsigned long SBE_time_now = millis();
  unsigned long SBE_oldTime = 0;
  int SBE_randomNumber = -1;
  void SwitchBetweenEmojis(std::vector <emojiType> emojiArray, const int &time){
    if (SBE_randomNumber == -1) {
      SBE_randomNumber = (rand() % emojiArray.size());
    }

    setEmoji(emojiArray[SBE_randomNumber]);
    if (((unsigned long)(millis() - SBE_time_now) > time)) { //switches if time is over or if the time is reset
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
  String Body = "Left ear: confirm";

  int repeatsCount = 0;

  int currentType = 0;
  int maxTypes = 3;

  int methodNum = 0;
  int methodsLearnTime[][2] = {{4,2},{25, 5}, {45, 10}, {90, 20}, {180, 30}};
  String methods[] = {"test","Pomodoro", "Felidoro", "Ultradian Rhythm", "Beast Mode"};

  int selectedType = 0;

  namespace manageTimer {
    unsigned long time_length = 0;
    unsigned long time_break = 0;

    unsigned long time_current = 0;
    unsigned long time_start = 0;

    unsigned long displayTime = 0;

    void startTimeCounter(int time) {
      time_length = (time*60)*1000; //(time[0]  * 10000) - 5*60*1000;

      time_start = millis();
      time_current = millis();
    }

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

  void SetupLearningPhase(int type) {
    if (globalBreak == true) {
      setRGB(0,25,0);
    }

    if (type == 1) {
      Header = "Learn ";
      Body = String(repeatsCount) + " times";

      if (isButtonRightEarPressed()) {
        repeatsCount++;
        if (repeatsCount > 10) {
          repeatsCount = 0;
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
      if (!initializedSequence) {
        initializedSequence = true;
        repeatsCount = repeatsCount * 2;
      }

      if (globalBreak == true) {
        selectedType++;
        manageTimer::startTimeCounter(methodsLearnTime[methodNum][1]);
        globalBreak = false;
      }

      if (selectedType != currentType) {
        //initialize section
        selectedType = currentType;
        manageTimer::startTimeCounter(methodsLearnTime[methodNum][0]);
        setRGB(25, 0, 0);
      }   

      if (manageTimer::getTimeLeft() == 0) {

        //Display asynchroneous message here
        setEmoji(HAPPY);
        displayText("Good job!", "session finished!");
        delay(2000);
        if (repeatsCount > 0) {
          repeatsCount--;
        }

        displayText("Remaining:", String(repeatsCount) + " times");

        if (repeatsCount == 0) {
          manageTimer::time_break = 0;
          manageTimer::time_current = 0;
          manageTimer::time_start = 0;
          manageTimer::displayTime = 0;
          
          methodNum = 0;
          repeatsCount = 0;
          selectedType = 0;
          currentType = 0;
          isCurrentlyLearning = false;
          initializedSequence = false;
          return;
        } else {
          globalBreak = true;
        }

        return;
      }

      //
      Header = formatTimeToString(manageTimer::getTimeLeft());
      Body = ComponentsUtility::GenerateMotivationalBody();
      ComponentsUtility::SwitchBetweenEmojis({HAPPY, SMILE, SLEEP}, 30000);

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
