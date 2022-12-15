#include <Arduino.h>
#include "DHT.h"

//dhtPin

int GetDHTPin(); //

int TemperatureManager_dhtPin = GetDHTPin();

DHT dht(TemperatureManager_dhtPin, DHT11);
unsigned long dht_previousTime = millis();

float humidity;
float temperature;


bool guteTemperatur();