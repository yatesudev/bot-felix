#include <FelixEngine.cpp>


using namespace LearningPhase;
using namespace Utility;

bool notifyTempState = false;


void loop() {
  
  /**
  * StartMethode, rechnet bis 5000.
  */
  Routine::StartUp(5000); /*<< Asynchrone funktion, welche nach dem Ablauf nicht mehr wiederholt wird. */

  /**
  * Methode welche aufgerufen wird, wenn der Bot seitlich hingelegt wurde.
  */
  if (isBotSleeping()) {
    //Trage hier die Funktionalität vom  ein!
    return;
  } 


  /**
  * Methode welche aufgerufen wird, wenn der Bot lernt und nicht hingelegt wurde.
  */
  if (!isBotSleeping() && isCurrentlyLearning) {
      /**
      * Methode welche aufgerufen wird, wenn der Bot gerade anfängt zu lernen und die Temepratur / Lufrfeuchtigkeit nicht in ordnung ist.
      */
    if (!notifyTempState && !isTempAndHumOk()) {
      //Trage hier funktionen ein, die aufgerufen werden wenn die Temepratur / Lufrfeuchtigkeit nicht in Ordnung ist

      notifyTempState = true;
      delay(3000);
    } else if (notifyTempState && isTempAndHumOk()) {
      //Trage hier funktionen ein, die aufgerufen werden wenn die Temepratur / Lufrfeuchtigkeit wieder in Ordnung ist.

      notifyTempState = false;
      delay(3000);
    }
  }

  /**
  * Methode welche prüft ob bei dem Bot buttons benutzt wurden, falls diese mehr als 10 sekunden (10000ms) betragen,
  * und der Bot gerade nicht am lernen ist, wird das Background Menu aufgerufen.
  */
  if (lastInputHigherThan(10000) && !isCurrentlyLearning) {
    BackgroundMenu::SetupBackgroundMenu();
    isButtonLeftEarPressed();
    isButtonRightEarPressed();
    setRGB(0,0,25);
    return;
  }


  /**
  * Bei der betätigung des Linken ohr-buttons wird der Typ des menüs um 1 erhöht
  * Diese Methode muss und sollte von dir nicht bearbeitet werden!
  */ 
  if (isButtonLeftEarPressed()) {
    currentType++;
    if (currentType > maxTypes) {
      currentType = 0;
    } else if (currentType == 3) {
      isCurrentlyLearning = true;
    }
  }

  /**
  * Methoden welche für die Lernphase benutzt werden. Diese wurden in der FelixEngine beschrieben und
  * sollten von dir nicht verändert werden. Die logik befindet sich in /lib/Engine/FelixEngine.cpp
  */
  displayText(Header,  Body); //von LearningPhase -> FelixEngine.cpp
  SetupLearningPhase(currentType); //von LearningPhase -> FelixEngine.cpp
}
