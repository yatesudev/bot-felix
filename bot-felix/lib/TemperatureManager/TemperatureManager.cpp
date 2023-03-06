#include "TemperatureManager.hpp"

float getTemperatureValue(){
  float temp = dht.readTemperature();
  
  if (isnan(temp)) {
    Serial.println("Error: Unable to read Temperature data from DHT Sensor");  
  }

  return temp;
}

float getHumidityValue(){
  float humidity = dht.readHumidity();

  if (isnan(humidity)) {
    Serial.println("Error: Unable to read Humidity data from DHT Sensor");  
  }

  return humidity;
}
