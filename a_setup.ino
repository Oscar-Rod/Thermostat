void setup(void) {
  
  //Serial.begin(9600);
  
  //Temperature sensor SetUp
  temperatureSensor.begin();
  temperatureSensor.setWaitForConversion(false);

  // Boiler SetUp
  pinMode(RELAY_PIN, OUTPUT);

  // LCD SetUp
  lcd.init();// initialize the lcd
  lcd.backlight();

  // Buttons SetUp
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  pinMode(MENU_BUTTON, INPUT_PULLUP);
  pinMode(OK_BUTTON, INPUT_PULLUP);

  //Clock SetUp
  Wire.begin();
  clockModule.setClockMode(false);
}
