#include "TiltManager.hpp"
#include "RGBManager.cpp"

bool TILTMANAGER_returnVal;

//Eine Funktion welche bei Aufruf reagiert, je nach dem ob der Lernbot steht oder liegt
bool readTilt(const int tiltVal){
  bool currentTilt = digitalRead(tiltVal);
  unsigned long tilt_currentTime = millis();


  if(tilt_currentTime - tiltsTime > 2000){
     
       if(currentTilt){
        //in diesem Fall "steht" der Bot/Tiltssensor
        //Serial.println("Ich stehe!");
        setRGB(0, 20, 0);
        //delay(500);
        TILTMANAGER_returnVal = false;
        } else {
        //in diesem Fall "liegt" der Bot/Tiltssensor
        //Serial.println("Ich liege!");
        setRGB(100, 50, 0);
        //delay(500);
        TILTMANAGER_returnVal = true;
       }
       TILTMANAGER_tilt = currentTilt;
    
    tiltsTime = tilt_currentTime;
  }
    return TILTMANAGER_returnVal;
}
