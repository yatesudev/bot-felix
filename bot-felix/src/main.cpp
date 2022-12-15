#include <setup.cpp>

void loop() {


  displayText("Header", "longText");
}


bool isBotSleeping() {
  return readTilt(PIN_tilt);
}

