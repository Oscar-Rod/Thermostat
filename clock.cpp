#include "clock.h"

Clock::Clock() {

}

void Clock::init() {
  Wire.begin();
  clockModule.setClockMode(false);
}

void Clock::setTime(int hour, int minute, int second) {
  clockModule.setHour(hour);
  clockModule.setMinute(minute);
  clockModule.setSecond(second);
}

int Clock::getTime(int *hour, int *minute, int *second) {
  currentMilis = millis();
  if (currentMilis - previousMilis >= 1000){
    previousMilis = currentMilis;
    *hour = clockModule.getHour(h12Flag, pmFlag);
    *minute = clockModule.getMinute();
    *second = clockModule.getSecond();
  }
}

bool Clock::isWeekend() {
  int dayOfWeek = getDayOfWeek();
  if (dayOfWeek > 5) return true;
  else return false;
}

void Clock::setDayOfWeek(byte DayOfWeek) {
  clockModule.setDoW(DayOfWeek);
}

byte Clock::getDayOfWeek() {
  return clockModule.getDoW();
}
