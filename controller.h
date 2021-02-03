#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "screen.h"
#include "temperature_sensor.h"
#include "clock.h"
#include "relay.h"
#include "buttons.h"

class Controller {
  public:
    Controller(int temperatureSensorPin, int relayPin, int pin_1, int pin_2, int pin_3, int pin_4, int pin_5, int pin_6);
    void init();
    void control();
  private:
    Screen screen;
    TemperatureSensor temperatureSensor;
    Clock clock;
    Relay relay;
    Buttons buttons;
    int hour;
    int temporalHour;
    int minute;
    int temporalMinute;
    int second;
    byte dayOfWeek;
    float temperature;
    float setPoint = 15;
    int activeMenu = 1;
    int previousMenu = 1;
    bool automaticMode = false;
    bool boilerOn = false;
    int hourOnWeek = 0;
    int minuteOnWeek = 0;
    int hourOffWeek = 0;
    int minuteOffWeek = 0;
    int hourOnWeekend = 0;
    int minuteOnWeekend = 0;
    int hourOffWeekend = 0;
    int minuteOffWeekend = 0;
    bool modifyingOn = true;
    void fixTimeFormat(int *timeUnit, int limit);
    void modifySetPoint(float *setPoint, int pressedButton);
    void modifyTimes(int *hourOn, int *hourOff, int *minuteOn, int *minuteOff, int pressedButton);
    void modifyClockTimes(int *hour, int *minute, int pressedButton);
    void controlBoiler();
    bool isTimeToControlWeekend();
    bool isTimeToControlWeek();
    void togleBoiler();
    bool isTimeToControl(int onHour, int onMinute, int offHour, int offMinute);
};

#endif
