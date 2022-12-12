
#include "settings.cpp"

//--RGB-LED------------------------------------------------------------------------

//Eine Funktion welche bei Aufruf die RGB LED setzt
void setRGB(int redVal, int greenVal, int blueVal){
  
  analogWrite(rgbRed, redVal);
  analogWrite(rgbGreen, greenVal);
  analogWrite(rgbBlue, blueVal);
}
