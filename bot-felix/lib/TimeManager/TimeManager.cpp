#include "TimeManager.hpp"

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
