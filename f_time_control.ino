void setTimeControl() {
  if (menu == 1) {
    printSetTimeControl(&onHour, &onMinute, &onHourString, &onMinuteString, "On");
    readTimeControlButtons(&onHour, &onMinute);
  } else if (menu == 2) {
    printSetTimeControl(&offHour, &offMinute, &offHourString, &offMinuteString, "Off");
    readTimeControlButtons(&offHour, &offMinute);
  }
}

void printSetTimeControl(int *hour, int *minute, String *hourString, String *minuteString, String state) {
  String message;
  convertTimeToString(hour, hourString);
  convertTimeToString(minute, minuteString);
  lcd.setCursor(0,0);
  message = String("Set Time ");
  message.concat(state);
  message.concat(": ");
  lcd.print(message);
  lcd.setCursor(7,2);
  lcd.print(*hourString);
  lcd.print(":");
  lcd.print(*minuteString);
}

void readTimeControlButtons(int *hour, int *minute) {
  if (digitalRead(BUTTON_1) == LOW) {
    *hour -= 1;
    delay(BUTTONS_DELAY);
  }
  if (digitalRead(BUTTON_2) == LOW) {
    *hour += 1;
    delay(BUTTONS_DELAY);
  }
  if (digitalRead(BUTTON_3) == LOW) {
    *minute -= 1;
    delay(BUTTONS_DELAY);
  }
  if (digitalRead(BUTTON_4) == LOW) {
    *minute += 1;
    delay(BUTTONS_DELAY);
  }
  fixTimeFormat(hour, 24);
  fixTimeFormat(minute, 60);
}
