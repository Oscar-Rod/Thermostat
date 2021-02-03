#include "controller.h"
#include "temperature_sensor.h"

#define HYSTERESIS 0.1

Controller::Controller(int temperatureSensorPin, int relayPin, int pin_1, int pin_2, int pin_3, int pin_4, int pin_5, int pin_6):
screen(0x27,20,4),
temperatureSensor(temperatureSensorPin),
clock(),
relay(relayPin),
buttons(pin_1, pin_2, pin_3, pin_4, pin_5, pin_6) {}

void Controller::init() {
  temperatureSensor.init();
  screen.init();
  buttons.init();
  relay.init();
}

void Controller::control() {
  int pressedButton;
  pressedButton = buttons.check();
  clock.getTime(&hour, &minute, &second);
  if (pressedButton == 5) {
    activeMenu++;
    pressedButton = 0;
    modifyingOn = true;
  }
  if (activeMenu >= 5) activeMenu = 1;
  if (activeMenu == 1) {
    previousMenu = 1;
    controlBoiler();
    if (pressedButton == 6) {
      pressedButton = 0;
      automaticMode = automaticMode ? false : true;
    }
    modifySetPoint(&setPoint, pressedButton);
    screen.printScreen1(temperature, setPoint, hour, minute, second, automaticMode);
  }
  if (activeMenu == 2) {
    previousMenu = 2;
    if (pressedButton == 6) {
      pressedButton = 0;
      modifyingOn = modifyingOn ? false : true;
    }
    modifyTimes(&hourOnWeek, &hourOffWeek, &minuteOnWeek, &minuteOffWeek, pressedButton);
    screen.printScreen2(hourOnWeek, minuteOnWeek, hourOffWeek, minuteOffWeek, false, modifyingOn);
  }
  if (activeMenu == 3) {
    previousMenu = 3;
    if (pressedButton == 6) {
      pressedButton = 0;
      modifyingOn = modifyingOn ? false : true;
    }
    modifyTimes(&hourOnWeekend, &hourOffWeekend, &minuteOnWeekend, &minuteOffWeekend, pressedButton);
    screen.printScreen2(hourOnWeekend, minuteOnWeekend, hourOffWeekend, minuteOffWeekend, true, modifyingOn);
  }
  if (activeMenu == 4) {
    if (previousMenu != 4) {
      temporalHour = hour;
      temporalMinute = minute;
      previousMenu = 4;
    }
    if (pressedButton == 6) {
      clock.setTime(temporalHour, temporalMinute, 0);
    }
    modifyClockTimes(&temporalHour, &temporalMinute, pressedButton);
    screen.printScreen3(hour, minute, temporalHour, temporalMinute);
  }
}

void Controller::modifySetPoint(float *setPoint, int pressedButton) {
    if (pressedButton == 1) {
      (*setPoint)--;
    } else if (pressedButton == 2) {
      (*setPoint)++;
    } else if (pressedButton == 3) {
      *setPoint = *setPoint - 0.1;
    } else if (pressedButton == 4) {
      *setPoint = *setPoint + 0.1;
    }
}

void Controller::modifyTimes(int *hourOn, int *hourOff, int *minuteOn, int *minuteOff, int pressedButton) {
  if (pressedButton == 1) {
    if (modifyingOn) {
      (*hourOn)--;
      fixTimeFormat(hourOn, 24);
    } else {
      (*hourOff)--;
      fixTimeFormat(hourOff, 24);
    }
  }
  if (pressedButton == 2) {
    if (modifyingOn) {
      (*hourOn)++;
      fixTimeFormat(hourOn, 24);
    }
    else {
      (*hourOff)++;
      fixTimeFormat(hourOff, 24);
    }
  }
  if (pressedButton == 3) {
    if (modifyingOn) {
      (*minuteOn)--;
      fixTimeFormat(minuteOn, 60);
    }
    else {
      (*minuteOff)--;
      fixTimeFormat(minuteOff, 60);
    }
  }
  if (pressedButton == 4) {
    if (modifyingOn) {
      (*minuteOn)++;
      fixTimeFormat(minuteOn, 60);
    }
    else {
      (*minuteOff)++;
      fixTimeFormat(minuteOff, 60);
    }
  }
}

void Controller::modifyClockTimes(int *hour, int *minute, int pressedButton) {
    if (pressedButton == 1) {
      (*hour)--;
      fixTimeFormat(hour, 24);
    } else if (pressedButton == 2) {
      (*hour)++;
      fixTimeFormat(hour, 24);
    } else if (pressedButton == 3) {
      (*minute)--;
      fixTimeFormat(minute, 60);
    } else if (pressedButton == 4) {
      (*minute)++;
      fixTimeFormat(minute, 60);
    }
}

void Controller::fixTimeFormat(int *timeUnit, int limit) {
  if (*timeUnit <= -1) *timeUnit = limit - 1;
  if (*timeUnit >= limit) *timeUnit = 0;
}
    
void Controller::controlBoiler() {
  temperature = temperatureSensor.readTemperature();
  if (clock.isWeekend()) {
    if (isTimeToControlWeekend()) {
      togleBoiler();
    } else {
      relay.setOff();
      boilerOn = false;
    }
  } else {
    if (isTimeToControlWeek()) {
      togleBoiler();
    } else {
      relay.setOff();
      boilerOn = false;
    }
  }
}

bool Controller::isTimeToControlWeekend() {
  return isTimeToControl(hourOnWeekend, minuteOnWeekend, hourOffWeekend, minuteOffWeekend);
}

bool Controller::isTimeToControlWeek() {
  return isTimeToControl(hourOnWeek, minuteOnWeek, hourOffWeek, minuteOffWeek);
}

void Controller::togleBoiler() {
  if (boilerOn) {
    if (temperature > setPoint + HYSTERESIS) {
      relay.setOff();
      boilerOn = false;
    } 
  } else {
    if (temperature < setPoint - HYSTERESIS) {
      relay.setOn();
      boilerOn = true;
    }
  }
}

bool Controller::isTimeToControl(int onHour, int onMinute, int offHour, int offMinute) {
  if ((onHour > offHour) || ((onHour == offHour) && (onMinute > offMinute))) {
    if (((hour > onHour) || ((hour == onHour) && (minute > onMinute))) || (hour < offHour || ((hour == offHour) && (minute < offMinute)))) {
      return true;
    }
  }
  if ((onHour < offHour) || ((onHour == offHour) && (onMinute < offMinute))) {
    if (((hour > onHour) || ((hour == onHour) && (minute > onMinute))) && (hour < offHour || ((hour == offHour) && (minute < offMinute)))) {
      return true;
    }
  }
  return false;
}
