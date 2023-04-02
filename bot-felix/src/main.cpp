#include <FelixEngine.cpp>

void loop() {
  Routine::StartUp(5000); /*<< synchronous routine using milis(), once done, it will return true and won't be repeated.*/

  if (Utility::isBotSleeping()) {
    setEmoji(SLEEP);
    return;
  } 

  if (lastInputHigherThan(10000) && !isCurrentlyLearning) {
    BackgroundMenu::SetupBackgroundMenu();
    isButtonLeftEarPressed();
    isButtonRightEarPressed();
    return;
  }

  if (isButtonLeftEarPressed()) {
    LearningPhase::currentType++;
    if (LearningPhase::currentType > LearningPhase::maxTypes) {
      LearningPhase::currentType = 0;
    } else if (LearningPhase::currentType == 3) {
      isCurrentlyLearning = true;
    }
  }

  displayText(LearningPhase::Header,  LearningPhase::Body);
  LearningPhase::SetupLearningPhase(LearningPhase::currentType);
}
