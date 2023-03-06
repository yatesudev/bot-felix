#include <Arduino.h>
#include "DHT.h"

//dhtPin

int GetDHTPin(); //

int TemperatureManager_dhtPin = GetDHTPin();

DHT dht(TemperatureManager_dhtPin, DHT11);