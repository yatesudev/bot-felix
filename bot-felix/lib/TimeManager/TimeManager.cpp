#include "TimeManager.hpp"

String getDateTimeString(){
  if (! rtc.begin()) {
    return "Couldn't find RTC";
  }

  DateTime now = rtc.now();
  String dateTimeString = "";
  
  if (now.hour() < 10) {
    dateTimeString += "0";
  }
  
  dateTimeString += now.hour();
  dateTimeString += ":";
  if (now.minute() < 10) {
    dateTimeString += "0";
  }

  dateTimeString += now.minute();
  dateTimeString += ":";
  if (now.second() < 10) {
    dateTimeString += "0";
  }
  dateTimeString += now.second();
  return dateTimeString;
}
