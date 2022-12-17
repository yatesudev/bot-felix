#include <FelixEngine.cpp>

int repeatsCount = 0;

void loop() {

  //DebugComponents();    /*<< uncomment this line to debug components*/

  Routine::StartUp(2000); /*<< synchronous routine using milis(), once done, it will return true and won't be repeated.*/

  if(isBotSleeping()) {
    Routine::Sleep();
  } else {
    //Routine::AwaitInput(); // Change a bit

    // ComponentsUtility::SwitchBetweenDialogText("Felix da bot", {"test1", "test2", "test3"}, 3000); //switch every 3 seconds
    // ComponentsUtility::SwitchBetweenEmojis({HAPPY, CRY, SMILE}, 3000); //switch every 3 seconds
    // ComponentsUtility::SwitchBetweenEmojisWithDialogs({HAPPY, CRY, SMILE}, {"test1", "test2", "test3"}, 3000); //switch every 3 seconds

    if (isButtonRightEarPressed() || repeatsCount > 0) {
      setupLearningPhase(repeatsCount);
    }
  }    
}
