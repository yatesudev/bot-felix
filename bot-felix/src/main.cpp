#include <FelixEngine.cpp>

int repeatsCount = 0;

void loop() {

  //DebugComponents();    /*<< uncomment this line to debug components*/

  Routine::StartUp(5000); /*<< synchronous routine using milis(), once done, it will return true and won't be repeated.*/

  if(isBotSleeping()) {
    Routine::Sleep();
  } else {
    Routine::AwaitInput();
    if (isButtonRightEarPressed() || repeatsCount > 0) {
      setupLearningPhase(repeatsCount);
    }
  }    
}
