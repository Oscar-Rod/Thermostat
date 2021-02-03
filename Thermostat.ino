
#include "controller.h"
#include "temperature_sensor.h"

#define TEMPERATURE_SENSOR_PIN 11
#define RELAY_PIN 12

#define OK_BUTTON 5
#define MENU_BUTTON 6

#define BUTTON_1 10
#define BUTTON_2 9
#define BUTTON_3 8
#define BUTTON_4 7

Controller controller(TEMPERATURE_SENSOR_PIN, RELAY_PIN, BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, MENU_BUTTON, OK_BUTTON);
