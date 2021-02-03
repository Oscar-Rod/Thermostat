#include "temperature_sensor.h"


TemperatureSensor::TemperatureSensor(int pin):oneWire(pin), dallasTemperature(&oneWire){
}

void TemperatureSensor::init() {
  dallasTemperature.begin();
  dallasTemperature.setWaitForConversion(false);
}

float TemperatureSensor::readTemperature() {
  if (millis() - lastTempRequestTime >= delayInMillis){
    temperature = dallasTemperature.getTempCByIndex(0);
    dallasTemperature.requestTemperatures();
    lastTempRequestTime = millis();
  }
  return temperature;
}
