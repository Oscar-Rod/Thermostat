#ifndef SCREEN_H
#define SCREEN_H

#include "Arduino.h"
#include <LiquidCrystal_I2C.h>

class Screen {
  public:
    Screen(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);
    void init();
    void refresh();
    void print();
    void setRow(int rowNumber, const char rowString[20]);
    void printScreen1(float temperature, float setPoint, int hour, int minute, int second, bool automaticMode);
    void printScreen2(int hourOn, int minuteOn, int hourOff, int minuteOff, bool isWeekend, bool modifyingOn);
    void printScreen3(int currentHour, int currentMinute, int temporalHour, int temporalMinute);
  private:
    LiquidCrystal_I2C liquidCrystal_I2C;
    int previousScreen = 1;
    String convertTimeToString(int timeUnit);
};

#endif
