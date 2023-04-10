#include <DisplayManager.cpp>
#include <LEDMatrix.cpp>
#include <TemperatureManager.cpp>
#include <TimeManager.cpp>
#include <TiltManager.cpp>
#include <Pangodream_18650_CL.h>
#include <vector>


//adjust your pin numbers
const int PIN_buttonStart =   00; //left button
const int PIN_buttonRepeats = 00; //right button

const int          PIN_tilt = 00; //tilt sensor

const int           PIN_dht = 00; //temperatur sensor

const int        PIN_rgbRed = 00; //rgb red
const int      PIN_rgbGreen = 00; //rgb green
const int       PIN_rgbBlue = 00; //rgb blue

const int       PIN_speaker = 00; //buzzer

Pangodream_18650_CL Battery;

/**
* Setup ->
* OI
*/
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

  while (! rtc.begin()) {
    Serial.println("RTC is NOT running!");
    delay(1000);
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

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

int GetSpeakerPin(){
  return PIN_speaker;
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
