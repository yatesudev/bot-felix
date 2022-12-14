#include <DisplayManager.cpp>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <RTClib.h>
#include "Adafruit_LEDBackpack.h"
#include "DHT.h"

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}