void controlBoiler() {
  readTemperature();
  toggleBoiler();
  printTemperature();
  readTemperatureButtons();
}

float readTemperature() {
  if (millis() - lastTempRequest >= delayInMillis){
    temperature = temperatureSensor.getTempCByIndex(0);
    temperatureSensor.requestTemperatures();
    lastTempRequest = millis();
  }
}

void toggleBoiler() {
  //int currentHour = 0;
  //int currentMinute = 0;
  //int onHour = 0;
  //int onMinute = 0;
  if (isTimeToControl()){
    if (boilerOn) {
      if (temperature > setPoint + HYSTERESIS) {
        digitalWrite(RELAY_PIN, LOW);
        boilerOn = false;
      } 
    } else {
      if (temperature < setPoint - HYSTERESIS) {
        digitalWrite(RELAY_PIN, HIGH);
        boilerOn = true;
      }
    }
  } else {
    digitalWrite(RELAY_PIN, LOW);
    boilerOn = false;
  }
}

bool isTimeToControl() {
  if ((onHour > offHour) || ((onHour == offHour) && (onMinute > offMinute))) {
    if (((currentHour > onHour) || ((currentHour == onHour) && (currentMinute > onMinute))) || (currentHour < offHour || ((currentHour == offHour) && (currentMinute < offMinute)))) {
      return true;
    }
  }
  if ((onHour < offHour) || ((onHour == offHour) && (onMinute < offMinute))) {
    if (((currentHour > onHour) || ((currentHour == onHour) && (currentMinute > onMinute))) && (currentHour < offHour || ((currentHour == offHour) && (currentMinute < offMinute)))) {
      return true;
    }
  }
  return false;
}

void printTemperature() {
  lcd.setCursor(0,1);
  lcd.print("Temperature: ");
  lcd.setCursor(14,1);
  lcd.print(String(temperature, 1));
  lcd.setCursor(0,3);
  lcd.print("Set Point: ");
  lcd.setCursor(14,3);
  lcd.print(String(setPoint, 1));
}

void readTemperatureButtons() {
  if (digitalRead(BUTTON_4) == LOW) {
    setPoint += 0.1;
    delay(BUTTONS_DELAY);
  }
  if (digitalRead(BUTTON_1) == LOW) {
    setPoint -= 1;
    delay(BUTTONS_DELAY);
  }
  if (digitalRead(BUTTON_3) == LOW) {
    setPoint -= 0.1;
    delay(BUTTONS_DELAY);
  }
  if (digitalRead(BUTTON_2) == LOW) {
    setPoint += 1;
    delay(BUTTONS_DELAY);
  }
}
