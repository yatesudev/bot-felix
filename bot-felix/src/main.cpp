#include <FelixEngine.cpp>


using namespace LearningPhase;
using namespace Utility;

bool notifyTempState = false;

void loop() {


  Routine::StartUp(5000); /*<< synchronous routine using milis(), once done, it will return true and won't be repeated.*/

  //sleeping case
  if (isBotSleeping()) {
    setEmoji(SLEEP);
    return;
  } 


  if (!isBotSleeping() && isCurrentlyLearning) {
    if (!notifyTempState && !isTempAndHumOk()) {
      setRGB(80, 0, 0);
      displayText("Warning!", "" + String((int) getTemperatureValue()) + " C " + " | " + String((int) getHumidityValue())+"%");
      notifyTempState = true;
      delay(3000);
    } else if (notifyTempState && isTempAndHumOk()) {
      notifyTempState = false;
      setRGB(0, 80, 0);
      displayText("Info!", "" + String((int) getTemperatureValue()) + " C " + " | " + String((int) getHumidityValue())+"%");
      delay(3000);
    }
  }

  //background Menu
  if (lastInputHigherThan(10000) && !isCurrentlyLearning) {
    BackgroundMenu::SetupBackgroundMenu();
    isButtonLeftEarPressed();
    isButtonRightEarPressed();
    setRGB(0,0,25);
    return;
  }

  //button pressed 
  if (isButtonLeftEarPressed()) {
    currentType++;
    if (currentType > maxTypes) {
      currentType = 0;
    } else if (currentType == 3) {
      isCurrentlyLearning = true;
    }
  }

  //default if nothing else is true (= Learning)
  displayText(Header,  Body); //from LearningPhase -> FelixEngine.cpp
  SetupLearningPhase(currentType); //from LearningPhase -> FelixEngine.cpp
}
