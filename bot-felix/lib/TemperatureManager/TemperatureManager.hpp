#include <Arduino.h>
#include "DHT.h"

//dhtPin
const int dhtPin = 26;//5

DHT dht(dhtPin, DHT11);
unsigned long dht_previousTime = millis();

float humidity;
float temperature;


bool guteTemperatur();