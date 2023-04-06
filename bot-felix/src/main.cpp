#include <FelixEngine.cpp>


using namespace LearningPhase;
using namespace Utility;

bool notifyTempState = false;


void loop() {

  Routine::StartUp(5000); /*<< synchronous routine using milis(), once done, it will return true and won't be repeated.  */

  //sleeping case
  if (isBotSleeping()) {
    //Setup your own Sleeping methods using our Docs Function here!
    return;
  } 


  if (!isBotSleeping() && isCurrentlyLearning) {
    if (!notifyTempState && !isTempAndHumOk()) {
      //Setup your method to display that the Temperature and Humidity in the room is not good for learning! (Values editable in Engine.cpp)

      notifyTempState = true;
      delay(3000);
    } else if (notifyTempState && isTempAndHumOk()) {
      //Setup your method to display that the Temperature and Humidity in the room is back to Normal!

      notifyTempState = false;
      delay(3000);
    }
  }

  //background Menu -> Checks if the Input buttons were pressed, if not it turns on the Background Menu which you can configure in Engine.cpp!
  if (lastInputHigherThan(10000) && !isCurrentlyLearning) {
    BackgroundMenu::SetupBackgroundMenu();
    isButtonLeftEarPressed();
    isButtonRightEarPressed();
    setRGB(0,0,25);
    return;
  }

  /*
  *
  **/
  
  //**button pressed Event -> If the left button is pressed we increment the currentType value which defines the Menu you choose.
  
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



