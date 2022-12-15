#include <DisplayManager.cpp>
#include <LEDMatrix.cpp>
#include <TemperatureManager.cpp>
#include <TimeManager.cpp>

#include <TiltManager.cpp>

#include <Wire.h>
#include <Adafruit_GFX.h>

const int buttonStart = 32;//2
const int buttonWiederhohlungen = 33;//3

void setup() {
  pinMode(buttonStart, INPUT);
  pinMode(buttonWiederhohlungen, INPUT);
  pinMode(tilt, INPUT);

  pinMode(rgbRed, OUTPUT);
  pinMode(rgbGreen, OUTPUT);
  pinMode(rgbBlue, OUTPUT);
  
  Serial.begin(9600);

  matrix.begin(0x70);  
  matrix.setRotation(3);
  

  lcd.init();
  lcd.backlight();

  dht.begin();

}