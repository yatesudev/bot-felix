#include "settings.cpp"
#include "lib_RGBLED.cpp" //includes main Arduino lib



bool neigung = false;
unsigned long neigungsZeit = millis();


//Eine Funktion welche bei Aufruf reagiert, je nach dem ob der Lernbot steht oder liegt
bool readNeigung(const int tilt){
  bool currentNeigung = digitalRead(tilt);
  unsigned long neigung_currentTime = millis();


  if(neigung_currentTime - neigungsZeit > 2000){
     
       if(currentNeigung){
        //in diesem Fall "steht" der Bot/Neigungssensor
        //Serial.println("Ich stehe!");
        setRGB(0, 20, 0);
        //delay(500);
        return false;
        } else {
        //in diesem Fall "liegt" der Bot/Neigungssensor
        //Serial.println("Ich liege!");
        setRGB(100, 50, 0);
        //delay(500);
        return true;
       }
       neigung = currentNeigung;
    
    neigungsZeit = neigung_currentTime;
  }

}
