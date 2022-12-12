#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <RTClib.h>
#include "Adafruit_LEDBackpack.h"
#include "DHT.h"

//Buttons: 
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

// all libraries 


unsigned long dht_previousTime = millis();

bool guteTemperatur(){
  unsigned long currentTime = millis();

  if(currentTime - dht_previousTime > 500) {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Es konnten keine Daten vom DHT gelesen werden");
    
    }

    Serial.print("Luftfeuchtigkeit: ");
    Serial.println(humidity);
    Serial.print("Temperatur: ");
    Serial.println(temperature);

  //testet, ob die Temperatur und Luftfeuchtigkeit in einem Vorgeschlagen Bereich zum Lernen liegen (mit etwas Luft nach oben/unten)
    return  temperature <= 24 && temperature >= 16 && humidity <= 75;
  }
}


int StrLib_Li          = 16;
int StrLib_Lii         = 0; 

int new_li             = 0;

double StrLib_second = 0;
unsigned long StrLib_time_now = 0;

String currentString = "";

bool StrLib_isInitialized = false;
bool StrLib_firstDisplay = false;

String StrLib_Scroll_LCD_Left(String StrDisplay){
  String result;
  String StrProcess = "" + StrDisplay + "                ";
  result = StrProcess.substring(StrLib_Li,StrLib_Lii);
  StrLib_Li++;
  StrLib_Lii++;
  if (StrLib_Li>StrProcess.length()){
    StrLib_Li=16;
    StrLib_Lii=0;
  }
  return result;
}

void StrLib_Clear_Scroll_LCD_Left(){
  StrLib_Li=16;
  StrLib_Lii=0;
  new_li = 0;
}

void StrLib_displayTextInLoop(String Header, String longText){
  int headerLength = Header.length();
  String stringAddition = "";
  for (int i=0; i < ((16-headerLength)/2); i++){
    stringAddition = stringAddition + " ";
  }
  Header = stringAddition + Header;

  if (!StrLib_firstDisplay) {
    StrLib_firstDisplay = true;
    lcd.setCursor(0, 0);
    lcd.print(Header);
    lcd.setCursor(0, 1);
    lcd.print(StrLib_Scroll_LCD_Left(longText));
  }

  if (((unsigned long)(millis() - StrLib_time_now)>2000) || StrLib_isInitialized) {
      //wait 1 sec
      StrLib_isInitialized = true;
    if ((unsigned long)(millis() - StrLib_time_now)>500) {
      StrLib_time_now = millis();
      lcd.setCursor(0, 0);
      lcd.print(Header);
      lcd.setCursor(0, 1);
      lcd.print(StrLib_Scroll_LCD_Left(longText));
    //break;
    } 
  }

  if (StrLib_Lii >= longText.length()) {
    lcd.clear();
    StrLib_isInitialized = false;
    StrLib_firstDisplay = false;
  }
}

void StrLib_displayShortTextInLoop(String Header, String longText) {
  int headerLength = Header.length();
  String stringAddition = "";
  for (int i=0; i < ((16-headerLength)/2); i++){
    stringAddition = stringAddition + " ";
  }
  Header = stringAddition + Header ;

  int longLength = longText.length();  
  String stringAddition2 = "";
  for (int i=0; i < ((16-longLength)/2); i++){
    stringAddition2 = stringAddition2 + " ";
  }
  longText = stringAddition2 + longText + stringAddition2 + stringAddition2;

  lcd.setCursor(0, 0);  
  lcd.print(Header);
  lcd.setCursor(0, 1);
  lcd.print(longText);

}

bool resultOfDisplaying() {
  bool result = StrLib_Li < new_li;
  new_li = StrLib_Li; 
  return (result);
}

bool displayText(String Header, String longText){
  if (currentString != longText) {
    StrLib_Clear_Scroll_LCD_Left();
    currentString = longText;
  }
  
  if ((longText.length() > 16)) {
    StrLib_displayTextInLoop(Header, longText);
  } else {
    StrLib_displayShortTextInLoop(Header, longText);
  }

  return resultOfDisplaying();
}

//----------------------------------
boolean StrLib_isUsed = false;
void StrLib_displayTextOnce(String Header, String longText){
  if (!StrLib_isUsed && (longText.length() > 16)) {
    int headerLength = Header.length();
    String stringAddition = "";
    for (int i=0; i < ((16-headerLength)/2); i++){
      stringAddition = stringAddition + " ";
    }
    Header = stringAddition + Header;

    StrLib_isUsed = true;
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(Header);
    lcd.setCursor(0, 1);
    lcd.print(StrLib_Scroll_LCD_Left(longText));
    
    double StrLib_second = 0;
    unsigned long StrLib_time_now = 0;

    while (true) {
      //wait 1 sec
      if ((unsigned long)(millis() - StrLib_time_now)>3000) {
        break;
      } 
    }
    
    while (true){

      if ((unsigned long)(millis() - StrLib_time_now)>150) {
        StrLib_time_now = millis();
        StrLib_second = StrLib_second + 0.15;
        lcd.setCursor(0, 1);
        lcd.print(StrLib_Scroll_LCD_Left(longText));
      } 

      if (StrLib_Lii >= longText.length()) {
        lcd.clear();
        StrLib_isUsed = false;
        break;
      }
    }
    StrLib_Clear_Scroll_LCD_Left();
  } else if (!StrLib_isUsed) {
    int headerLength = Header.length();
    String stringAddition = "";
    for (int i=0; i < ((16-headerLength)/2); i++){
      stringAddition = stringAddition + " ";
    }
    Header = stringAddition + Header;

    int longLength = longText.length();
    String stringAddition2 = "";
    for (int i=0; i < ((16-longLength)/2); i++){
      stringAddition2 = stringAddition2 + " ";
    }
    longText = stringAddition2 + longText;

    StrLib_isUsed = true;
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(Header);
    lcd.setCursor(0, 1);
    lcd.print(longText);
    
    double StrLib_second = 0;
    unsigned long StrLib_time_now = 0;

    while (true) {
      //wait 1 sec
      if ((unsigned long)(millis() - StrLib_time_now)>5000) {
        lcd.clear();
        break;
      } 
    }
  }
}


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

unsigned long matrix_previousTime = millis();

//--Gesichter Presets--------------------------------------------------------------------------
static const uint8_t PROGMEM
  
    smile1_bmp[] =
  { B00000000,
    B00000000,
    B01000010,
    B10100101,    
    B00000000,
    B00000000,
    B00100100,
    B00011000 },
    smile2_bmp[] =
  { B00000000,
    B01000010,
    B10100101,
    B00000000,
    B00000000,
    B00000000,
    B00100100,
    B00011000 },
     angry1_bmp[] =
  { B00000000,
    B00000000,
    B10100101,
    B01000010,    
    B10100101,
    B00000000,
    B00000000,
    B00111100 },
    angry2_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00111100 },
   happy1_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B01000010,
    B10100101,
    B00000000,
    B00000000,
    B00000000 },
  happy2_bmp[] =
  { B00000000,
    B00000000,
    B01000010,
    B10100101,
    B00000000,
    B00000000,
    B00000000,
    B00000000 },
    cry1_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B11100111,    
    B00000000,
    B00000000,
    B00011000,
    B00100100 },
    cry2_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B01000010,
    B01000000,
    B00000000,
    B00000000 },
    cry3_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B01000010,
    B01000010,
    B00000000,
    B01000000 },
    cry4_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B01000010,
    B00000000,
    B00000010,
    B01000010 },
    sleep1_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11100111,
    B00000000,
    B00000000,
    B00000000 },
  sleep2_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
     B11100111,
    B00000000,
    B00000000 };

//--LED Matrix------------------------------------------------------------------------

//Funktionen welche verschiedene (animierte) Gesichter auf der LED Matrix darstellen können

void emoji_happy(){
  matrix.clear();
  unsigned long currentTime = millis();

  if(currentTime - matrix_previousTime > 500) {
    matrix.clear();
    matrix.drawBitmap(0, 0, happy1_bmp, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
  } 
  if(currentTime - matrix_previousTime > 1000){
    matrix.clear();
    matrix.drawBitmap(0, 0, happy2_bmp, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    matrix_previousTime = currentTime;
  } 
}

void emoji_smile(){
   matrix.clear();
  unsigned long currentTime = millis();

  if(currentTime - matrix_previousTime > 500) {
    matrix.clear();
    matrix.drawBitmap(0, 0, smile1_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();
  } 
  if(currentTime - matrix_previousTime > 1000){
    matrix.clear();
    matrix.drawBitmap(0, 0, smile2_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();
    matrix_previousTime = currentTime;
  } 
}

void emoji_angry(){
   matrix.clear();
  unsigned long currentTime = millis();

  if(currentTime - matrix_previousTime > 500) {
    matrix.clear();
    matrix.drawBitmap(0, 0, angry2_bmp, 8, 8, LED_RED);
    matrix.writeDisplay();
  } 

  if(currentTime - matrix_previousTime > 1000){
    matrix.clear();
    matrix.drawBitmap(0, 0, angry1_bmp, 8, 8, LED_RED);
    matrix.writeDisplay();
    matrix_previousTime = currentTime;
  } 
}

void emoji_cry(){
  matrix.clear();
  unsigned long currentTime = millis();

  if(currentTime - matrix_previousTime > 300 && currentTime - matrix_previousTime < 600) {
    matrix.clear();
    matrix.drawBitmap(0, 0, cry1_bmp, 8, 8, LED_YELLOW);
    matrix.drawBitmap(0, 0, cry2_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();
  } 

  if(currentTime - matrix_previousTime > 600 && currentTime - matrix_previousTime < 900){
    matrix.drawBitmap(0, 0, cry1_bmp, 8, 8, LED_YELLOW);
    matrix.drawBitmap(0, 0, cry3_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();   
  } 

  if(currentTime - matrix_previousTime > 900){
    matrix.clear();
     matrix.drawBitmap(0, 0, cry1_bmp, 8, 8, LED_YELLOW);
    matrix.drawBitmap(0, 0, cry4_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay(); 
    matrix_previousTime = currentTime;
  } 
}

void emoji_sleep(){
  matrix.clear();
  unsigned long currentTime = millis();

  if(currentTime - matrix_previousTime > 500) {
    matrix.clear();
    matrix.drawBitmap(0, 0, sleep1_bmp, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
  } 
  if(currentTime - matrix_previousTime > 1000){
    matrix.clear();
    matrix.drawBitmap(0, 0, sleep2_bmp, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
    matrix_previousTime = currentTime;
  } 
}

//--RGB-LED------------------------------------------------------------------------

//Eine Funktion welche bei Aufruf die RGB LED setzt
void setRGB(int redVal, int greenVal, int blueVal){
  
  analogWrite(rgbRed, redVal);
  analogWrite(rgbGreen, greenVal);
  analogWrite(rgbBlue, blueVal);
}

double alte_stunde = -1,alte_minute = -1,alte_sekunde = -1;
double neue_stunde,neue_minute,neue_sekunde;
bool lernen = true;

bool LearnTimer(double learnTime, double breakTime){
  

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  if(alte_stunde == -1 || alte_minute == -1 || alte_sekunde == -1){
    DateTime then = rtc.now();
    alte_stunde = then.hour();
    alte_minute = then.minute();
    alte_sekunde = then.second();
  }

  


  DateTime now = rtc.now();
  neue_stunde = now.hour();
  neue_minute = now.minute();
  neue_sekunde = now.second();

  //double seconds = 0;
  //unsigned long time_now = 0;
  //double startTime = seconds;
  bool ok = true; 
  lernzeit = (neue_stunde * 60 - alte_stunde * 60) + neue_minute - alte_minute + (neue_sekunde / 60 - alte_sekunde / 60); 

  //Serial.println(lernzeit);
  if(lernen){
    if((neue_stunde * 60 - alte_stunde * 60) + neue_minute - alte_minute + (neue_sekunde/ 60 - alte_sekunde/ 60)  > learnTime){     
      alte_stunde = neue_stunde;
      alte_minute = neue_minute;
      alte_sekunde = neue_sekunde;
      lernen = false;
      ok = false;
      if(istLetzterDurchgang){
       countLernWiederhohlungen++;
      }
      
      
      return lernen;
    }
  } else if(!lernen && !istLetzterDurchgang){
    if((neue_stunde * 60 - alte_stunde * 60) + neue_minute - alte_minute + (neue_sekunde / 60 - alte_sekunde / 60) >  breakTime){
      ok = true;
      lernen = true;
      alte_stunde = neue_stunde;
      alte_minute = neue_minute;
      alte_sekunde = neue_sekunde;
      countLernWiederhohlungen++;
      
      return lernen;
     }
  }
  return lernen;
}


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


//shitty code
void sleep() {
    emoji_sleep();
    displayText("Felix:", "zzzz...zz...zzzzzzzzz...zzzzzzzz...zzzzzz...zzzzzz...zzzzzzzzzzzz...");
}

//Funktion zum Auswählen der Wiederhohlungen
void lernzeitAuswahl(){
  if(digitalRead(buttonWiederhohlungen) == HIGH){
        counterButtonWiederhohlungen++;
        Serial.println(counterButtonWiederhohlungen);
        delay(500);
        if(counterButtonWiederhohlungen == 11){
        counterButtonWiederhohlungen = 1;
        }
      } 
      lernAnzahl = "Durchläufe: " + counterButtonWiederhohlungen;
      displayText("Felix:", (String)counterButtonWiederhohlungen);
}


//Funktion für den Lerntimer
void lerne(){
  //Beginn mit dem Lernablauf (mit gesetztem counter) wenn der start Knopf gedrückt wird

  //Teste ob die Temperatur (und Luftfeuchtigkeit) zum lernen geeignet sind
  if(guteTemperatur()){
    lerntGerade = LearnTimer(0.20,0.10);
    if(lerntGerade){
      //Serial.println("Lernphase");
      //matrix.clear();
      emoji_happy();
      displayText("Felix:", "Es ist Zeit zu lernen!");
    } else{
      //Serial.println("Pause");
      //matrix.clear();
      emoji_smile();
      displayText("Felix:", "Jetzt solltest du eine Pause machen!");
    }

    if(lerntGerade != hatGelernt){
      Serial.println(lernzeit);
      if(lerntGerade){
        //code für die Lernphase
        hatGelernt = true;
      } else{
        hatGelernt = false;
      } 
    }
  } else{
    //matrix.clear();
    emoji_cry();
    displayText("Felix:", "Bei der Temperatur kannst du nicht vernünftig lernen!");
  }
}


//--Loop------------------------------------------------------------------------

void loop() {
  //dispNeigung(tilt);
  botLiegt = readNeigung(tilt);
  //Schleife um zu testen, ob der Bot liegt oder nicht
  if(!botLiegt){

    //testen, ob wir nicht die gewünschten wiederhohlungen überschreiten
      if(countLernWiederhohlungen + 1 == counterButtonWiederhohlungen){
          istLetzterDurchgang = true;
        }
      if(countLernWiederhohlungen < counterButtonWiederhohlungen){
        //Funktion zum Stellen auf undefiniert, start und stop für den start Button
        if(digitalRead(buttonStart) == HIGH){
          counterButtonStart++;
          Serial.println(counterButtonStart);
            delay(500);
          if(counterButtonStart ==3){
            counterButtonStart = 0;
          } 
        } 

        //Auswahl der Lernzeit Wiederhohlungen wird nur ausgeführt, wenn der Start knopf noch nicht gedrückt wurde
        if(counterButtonStart == 0){
          //Auswahl der Lernzeit wiederhohlungen:
          lernzeitAuswahl();
        } else if(counterButtonStart == 1){ //Wird eingeleitet, wenn der Knopf gedrückt wurde um den Lernvorgang zu starten
            lerne();
        } else if(counterButtonStart == 2){ //Wird eingeleitet, wenn der Knopf gedrückt wurde um den Lernvorgang zu stoppen
            displayText("Felix: ", "Du hast aufgehoert zu lernen!");
        } else if(counterButtonStart == 3){
          // noch nicht implementiert, mögliches zurücksetzen
        }

      }  else {
        displayText("Felix: ", "Du hast alle Wiederhohlungen absolviert!");
      }
  
  } else {
    sleep();
    
 }  
}