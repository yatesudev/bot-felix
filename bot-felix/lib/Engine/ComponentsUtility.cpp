#include <Utility.cpp>

bool globalBreak = false;
bool initializedSequence = false;

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
