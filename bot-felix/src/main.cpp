#include <FelixEngine.cpp>


int repeatsCount = 0;

void loop() {

  if(isBotSleeping()) {
    Routine::Sleep();
  } else {
    Routine::AwaitInput();
    if (isButtonRightEarPressed() || repeatsCount > 0) {
      setupLearningPhase(repeatsCount);
    }
  }
}
