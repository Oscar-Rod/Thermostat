#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h> //DS18B20

class TemperatureSensor {
  public:
    TemperatureSensor(int pin);
    DallasTemperature dallasTemperature;
    OneWire oneWire;
    float temperature;
    unsigned long lastTempRequestTime;
    int delayInMillis = 750;
    void init();
    float readTemperature();
};

#endif
