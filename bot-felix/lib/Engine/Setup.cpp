#include <DisplayManager.cpp>
#include <LEDMatrix.cpp>
#include <TemperatureManager.cpp>
#include <TimeManager.cpp>
#include <TiltManager.cpp>
#include <Pangodream_18650_CL.h>
#include <vector>


//pins
const int PIN_buttonStart =   32;
const int PIN_buttonRepeats = 33;

const int          PIN_tilt = 37;

const int           PIN_dht = 26;

const int        PIN_rgbRed = 12;
const int      PIN_rgbGreen = 13;
const int       PIN_rgbBlue = 15;

const int       PIN_speaker = 17;

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