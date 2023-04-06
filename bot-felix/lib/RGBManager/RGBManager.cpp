
#include "RGBManager.hpp"
//--RGB-LED------------------------------------------------------------------------

///
int GetRGB(int val);

//Eine Funktion welche bei Aufruf die RGB LED setzt
int RGBMANAGER_rgbRED = GetRGB(1);
int RGBMANAGER_rgbGREEN = GetRGB(0);
int RGBMANAGER_rgbBLUE = GetRGB(2);

void setRGB(int redVal, int greenVal, int blueVal){
  
  analogWrite(RGBMANAGER_rgbRED, redVal);
  analogWrite(RGBMANAGER_rgbGREEN, greenVal);
  analogWrite(RGBMANAGER_rgbBLUE, blueVal);
}
