#include <RTClib.h>
#include <Arduino.h>

RTC_DS1307 rtc;

//Variablen für die Uhrzeit / Lernzeit
double alte_stunde = -1, alte_minute = -1, alte_sekunde = -1;
double neue_stunde, neue_minute, neue_sekunde;
double lernzeit = 0;

int countLernWiederhohlungen = 0; 

bool lernen = true;
bool istLetzterDurchgang = false;

//Funktionen
bool LearnTimer(double learnTime, double breakTime);
