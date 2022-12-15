#include <DisplayManager.cpp>
#include <LEDMatrix.cpp>
#include <TemperatureManager.cpp>
#include <TimeManager.cpp>

#include <TiltManager.cpp>

//#include <Wire.h>
//#include <Adafruit_GFX.h>

//pins
const int PIN_buttonStart = 32;//2
const int PIN_buttonRepeats = 33;//3

const int PIN_tilt = 37;//7

const int PIN_dht = 26;//5

const int PIN_rgbRed = 12;//11
const int PIN_rgbGreen = 13;//10
const int PIN_rgbBlue = 15;//9


void setup() {
  pinMode(PIN_buttonStart, INPUT);
  pinMode(PIN_buttonRepeats, INPUT);
  pinMode(PIN_tilt, INPUT);

  pinMode(PIN_rgbRed, OUTPUT);
  pinMode(PIN_rgbGreen, OUTPUT);
  pinMode(PIN_rgbBlue, OUTPUT);
  
  Serial.begin(9600);

  matrix.begin(0x70);  
  matrix.setRotation(3);
  

  lcd.init();
  lcd.backlight();

  dht.begin();

}


//Setup Getters for returning the PIN values 

int GetTiltPin() {
  return PIN_tilt;
}

int GetDHTPin() {
  return PIN_dht;
}

int GetRGB(int val) {
  switch (val)
  {
  case 0:
    return PIN_rgbRed;
  case 1:
    return PIN_rgbGreen;
  case 2:
    return PIN_rgbBlue;
  default:
    return PIN_rgbRed;
  }
}