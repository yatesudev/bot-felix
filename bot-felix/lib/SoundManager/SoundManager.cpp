#include "SoundManager.hpp"

void playToneOnTimerStart(){
    tone(SoundManager_speakerPin, 1000, 500);
}

void playToneOnTimerStop(){
    tone(SoundManager_speakerPin, 500, 500);
}