#include <FelixEngine.cpp>
#include <list>

namespace LearningPhase {
  String Header = "Right ear: +";
  String Body = "Left ear: confirm";

  int repeatsCount = 0;

  int currentType = 0;
  int types[] = {1, 2};

  int methodNum = 0;
  String methods[] = {"Pomodoro", "Spaced Repetition", "Flashcards"};

  void SetupLearningPhase(int type) {
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
  }
}

namespace BackgroundMenu {
  String Header = "Background";
  String Body = "Left ear: confirm";

  int currentBackground = 0;
  String backgrounds[] = {"Temperature", "Humidity", "Battery", "Time"};

  unsigned long time_UpdateScreen = millis();

  void SetupBackgroundMenu() {
    if ((unsigned long)(millis() - time_UpdateScreen) > 3000) {
      time_UpdateScreen = millis();
      currentBackground++;
      if (currentBackground >= Utility::ArrayLength(backgrounds)-1) {
        currentBackground = 0;
      }
    }

    if (currentBackground == 0) {
      Header = backgrounds[currentBackground];
      Body = String(getTemperatureValue()) + " C";
    }

    if (currentBackground == 1) {
      Header = backgrounds[currentBackground];
      Body = String(getHumidityValue()) + " %";
    }

    if (currentBackground == 2) {
      Header = backgrounds[currentBackground];
      Body = String(getBatteryLevel()) + " %";
    }

    if (currentBackground == 3) {
      Header = backgrounds[currentBackground];
     // Body = getDateTimeString();
    }

    displayText(Header, Body);
  }
}

void loop() {

  //DebugComponents();    /*<< uncomment this line to debug components*/

  Routine::StartUp(5000); /*<< synchronous routine using milis(), once done, it will return true and won't be repeated.*/


  if (lastInputHigherThan(10000)) {
    BackgroundMenu::SetupBackgroundMenu();
    isButtonLeftEarPressed();
    isButtonRightEarPressed();
    return;
  }

  if (isButtonLeftEarPressed()) {
    LearningPhase::currentType++;
    if (LearningPhase::currentType > Utility::ArrayLength(LearningPhase::types)) {
      LearningPhase::currentType = 0;
    }
  }

  displayText(LearningPhase::Header,  LearningPhase::Body);
  LearningPhase::SetupLearningPhase(LearningPhase::currentType);
  
}
