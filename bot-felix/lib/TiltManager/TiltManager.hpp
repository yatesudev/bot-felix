#include <Arduino.h>

bool TILTMANAGER_tilt = false;
unsigned long tiltsTime = millis();

bool readTilt(const int tiltVal);