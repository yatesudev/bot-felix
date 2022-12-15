#include "TemperatureManager.hpp"

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
  }
  
  return  (temperature <= 24 && temperature >= 16 && humidity <= 75);
}