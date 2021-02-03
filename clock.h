#ifndef CLOCK_H
#define CLOCK_H

#include "Arduino.h"
#include <Wire.h>
#include <DS3231.h>

class Clock {
  public:
    Clock();
    void init();
    void setTime(int hour, int minute, int second);
    void setDayOfWeek(byte DayOfWeek);
    int getTime(int *hour, int *minute, int *second);
    bool isWeekend();
  private:
    DS3231 clockModule;
    unsigned long currentMilis;
    unsigned long previousMilis;
    bool h12Flag = false;
    bool pmFlag = false;
    byte getDayOfWeek();
};

#endif
