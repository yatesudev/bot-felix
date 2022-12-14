#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <RTClib.h>
#include "Adafruit_LEDBackpack.h"
#include "DHT.h"

//Knopf-Pins: 
const int buttonStart = 32;//2
const int buttonWiederhohlungen = 33;//3

//Neigungssensor-Pin:
const int tilt = 37;//7
bool botLiegt = false;

//RGB-Pins:
const int rgbRed = 12;//11
const int rgbGreen = 13;//10
const int rgbBlue = 15;//9

//dhtPin
const int dhtPin = 26;//5

//counter, welche bei drücken der Buttons hochgezählt werden
int counterButtonStart = 0;
int counterButtonWiederhohlungen = 1;

//bool Werte geben an, ob gerade gelernt wird und ob vorher gelernt wurde;
//double lernzeit speichert die vergangene Zeit seit Anfang der Lernphase (in Minuten) ab
bool lerntGerade = false, hatGelernt = false;
double lernzeit = 0;
int countLernWiederhohlungen = 0; 
bool istLetzterDurchgang = false;

bool inAuswahl = false;
String lernAnzahl;




Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(dhtPin, DHT11);
RTC_DS1307 rtc;

//--Setup------------------------------------------------------------------------

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
