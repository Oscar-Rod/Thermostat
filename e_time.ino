void setTime() {
  printSetTime();
  readTimeButtons();
}

void printSetTime() {
  convertTimeToString(&currentHour, &currentHourString);
  convertTimeToString(&currentMinute, &currentMinuteString);
  convertTimeToString(&temporalHour, &temporalHourString);
  convertTimeToString(&temporalMinute, &temporalMinuteString);
  lcd.setCursor(0,0);
  lcd.print("Set Time: ");
  lcd.setCursor(15,0);
  lcd.print(temporalHourString);
  lcd.print(":");
  lcd.print(temporalMinuteString);
  lcd.setCursor(0,2);
  lcd.print("Current Time: ");
  lcd.setCursor(15,2);
  lcd.print(currentHourString);
  lcd.print(":");
  lcd.print(currentMinuteString);

}

void printTime() {
  convertTimeToString(&currentHour, &currentHourString);
  convertTimeToString(&currentMinute, &currentMinuteString);
  convertTimeToString(&currentSecond, &currentSecondString);
  lcd.setCursor(6,0);
  lcd.print(currentHourString);
  lcd.print(":");
  lcd.print(currentMinuteString);
  lcd.print(":");
  lcd.print(currentSecondString);
}

void readTimeButtons() {
  if (digitalRead(BUTTON_1) == LOW) {
    temporalHour -= 1;
    delay(BUTTONS_DELAY);
  }
  if (digitalRead(BUTTON_2) == LOW) {
    temporalHour += 1;
    delay(BUTTONS_DELAY);
  }
  if (digitalRead(BUTTON_3) == LOW) {
    temporalMinute -= 1;
    delay(BUTTONS_DELAY);
  }
  if (digitalRead(BUTTON_4) == LOW) {
    temporalMinute += 1;
    delay(BUTTONS_DELAY);
  }
  fixTimeFormat(&temporalHour, 24);
  fixTimeFormat(&temporalMinute, 60);
  if (digitalRead(OK_BUTTON) == LOW) {
    setClockModuleTime();
    delay(BUTTONS_DELAY);
  }
}

void fixTimeFormat(int *timeUnit, int limit) {
  if (*timeUnit <= -1) *timeUnit = limit - 1;
  if (*timeUnit >= limit) *timeUnit = 0;
}

void convertTimeToString(int *timeUnit, String *string) {
  if (*timeUnit < 10) {
    *string = String(0);
    (*string).concat(*timeUnit);
  } else {
    *string = String(*timeUnit);
  }
}

void setClockModuleTime() {
  clockModule.setHour(temporalHour);
  clockModule.setMinute(temporalMinute);
  clockModule.setSecond(0);
}

void getClocModuleTime() {
  currentMilis = millis();
  if (currentMilis - previousMilis >= 1000){
    previousMilis = currentMilis;
    currentHour = clockModule.getHour(h12Flag, pmFlag);
    currentMinute = clockModule.getMinute();
    currentSecond = clockModule.getSecond();
  }
}

void setTemporalTime() {
  temporalHour = currentHour;
  temporalMinute = currentMinute;
}
