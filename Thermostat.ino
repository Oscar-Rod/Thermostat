#include <OneWire.h>
#include <DallasTemperature.h> //DS18B20

#include <LiquidCrystal_I2C.h>

#include <Wire.h>
#include <DS3231.h>

#define TEMPERATURE_SENSOR 11
#define RELAY_PIN 12
#define POTENTIOMETER 1

#define OK_BUTTON 5
#define MENU_BUTTON 6

#define BUTTON_1 10
#define BUTTON_2 9
#define BUTTON_3 8
#define BUTTON_4 7

#define BUTTONS_DELAY 120
#define HYSTERESIS 0.1

OneWire oneWire(TEMPERATURE_SENSOR);

DallasTemperature temperatureSensor(&oneWire);

LiquidCrystal_I2C lcd(0x27,20,4);

DS3231 clockModule;

// Variables

// Main loop
int menu = 0;
float temperature = 0;
float setPoint = 15.0;

// Screen
int previousScreen = 0;

// Control
unsigned long lastTempRequest = millis();
int  delayInMillis = 750;
bool boilerOn = false;

// Time
int currentHour = 0;
int currentMinute = 0;
int currentSecond = 0;
int temporalHour = 0;
int temporalMinute = 0;
String currentHourString;
String currentMinuteString;
String currentSecondString;
String temporalHourString;
String temporalMinuteString;
unsigned long previousMilis = 0;
unsigned long currentMilis = 0;
bool h12Flag;
bool pmFlag;

// Time Control
int onHour = 0;
int onMinute = 0;
String onHourString;
String onMinuteString;
int offHour = 0;
int offMinute = 0;
String offHourString;
String offMinuteString;
