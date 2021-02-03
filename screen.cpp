#include "screen.h"

Screen::Screen(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows):liquidCrystal_I2C(lcd_Addr,lcd_cols,lcd_rows){
}

void Screen::init() {
  liquidCrystal_I2C.init();// initialize the lcd
  liquidCrystal_I2C.backlight();
  refresh();
}

void Screen::printScreen1(float temperature, float setPoint, int hour, int minute, int second, bool automaticMode) {
  if (previousScreen != 1) {
    refresh();
    previousScreen = 1;
  }
  liquidCrystal_I2C.setCursor(0,0);
  liquidCrystal_I2C.print(convertTimeToString(hour));
  liquidCrystal_I2C.print(":");
  liquidCrystal_I2C.print(convertTimeToString(minute));
  liquidCrystal_I2C.print(":");
  liquidCrystal_I2C.print(convertTimeToString(second));
  liquidCrystal_I2C.setCursor(19,0);
  if (automaticMode) liquidCrystal_I2C.print("A");
  else liquidCrystal_I2C.print("M");
  liquidCrystal_I2C.setCursor(0,1);
  liquidCrystal_I2C.print("Temperature: ");
  liquidCrystal_I2C.setCursor(14,1);
  liquidCrystal_I2C.print(String(temperature, 1));
  liquidCrystal_I2C.setCursor(0,2);
  liquidCrystal_I2C.print("Set Point: ");
  liquidCrystal_I2C.setCursor(14,2);
  liquidCrystal_I2C.print(String(setPoint, 1));
}

void Screen::printScreen2(int hourOn, int minuteOn, int hourOff, int minuteOff, bool isWeekend, bool modifyingOn) {
  int currentScreen;
  if (!isWeekend) currentScreen = 2;
  else currentScreen = 3;
  if (previousScreen != currentScreen) {
    refresh();
    previousScreen = currentScreen;
  }
  if (isWeekend) {
    liquidCrystal_I2C.setCursor(6,0);
    liquidCrystal_I2C.print("Weekend");
  } else {
    liquidCrystal_I2C.setCursor(8,0);
    liquidCrystal_I2C.print("Week");
  }
  liquidCrystal_I2C.setCursor(3,1);
  liquidCrystal_I2C.print("On");
  liquidCrystal_I2C.setCursor(14,1);
  liquidCrystal_I2C.print("Off");
  liquidCrystal_I2C.setCursor(2,3);
  liquidCrystal_I2C.print(convertTimeToString(hourOn));
  liquidCrystal_I2C.print(":");
  liquidCrystal_I2C.print(convertTimeToString(minuteOn));
  liquidCrystal_I2C.setCursor(13,3);
  liquidCrystal_I2C.print(convertTimeToString(hourOff));
  liquidCrystal_I2C.print(":");
  liquidCrystal_I2C.print(convertTimeToString(minuteOff));
  if (modifyingOn) {
    liquidCrystal_I2C.setCursor(0,3);
    liquidCrystal_I2C.print("->");
    liquidCrystal_I2C.setCursor(11,3);
    liquidCrystal_I2C.print("  ");
  } else {
    liquidCrystal_I2C.setCursor(0,3);
    liquidCrystal_I2C.print("  ");
    liquidCrystal_I2C.setCursor(11,3);
    liquidCrystal_I2C.print("->");
  }
}

void Screen::printScreen3(int currentHour, int currentMinute, int temporalHour, int temporalMinute){
  if (previousScreen != 4) {
    refresh();
    previousScreen = 4;
  }
  liquidCrystal_I2C.setCursor(0,0);
  liquidCrystal_I2C.print("Set Time: ");
  liquidCrystal_I2C.setCursor(15,0);
  liquidCrystal_I2C.print(convertTimeToString(temporalHour));
  liquidCrystal_I2C.print(":");
  liquidCrystal_I2C.print(convertTimeToString(temporalMinute));
  liquidCrystal_I2C.setCursor(0,2);
  liquidCrystal_I2C.print("Current Time: ");
  liquidCrystal_I2C.setCursor(15,2);
  liquidCrystal_I2C.print(convertTimeToString(currentHour));
  liquidCrystal_I2C.print(":");
  liquidCrystal_I2C.print(convertTimeToString(currentMinute));
}

void Screen::refresh() {
  liquidCrystal_I2C.clear();
}

String Screen::convertTimeToString(int timeUnit) {
  String string;
  if (timeUnit < 10) {
    string = String(0);
    string.concat(timeUnit);
  } else {
    string = String(timeUnit);
  }
  return string;
}
