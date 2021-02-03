#include "buttons.h"

#define BUTTONS_DELAY 150

Buttons::Buttons(int pin_1, int pin_2, int pin_3, int pin_4, int pin_5, int pin_6) {
  this->button1 = pin_1;
  this->button2 = pin_2;
  this->button3 = pin_3;
  this->button4 = pin_4;
  this->button5 = pin_5;
  this->button6 = pin_6;
}

void Buttons::init() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);
}

int Buttons::check() {
  int pressedButton = 0;
  if (millis() - lastCheck >= BUTTONS_DELAY){
    if (digitalRead(button1) == LOW) pressedButton = 1;
    else if (digitalRead(button2) == LOW) pressedButton = 2;
    else if (digitalRead(button3) == LOW) pressedButton = 3;
    else if (digitalRead(button4) == LOW) pressedButton = 4;
    else if (digitalRead(button5) == LOW) pressedButton = 5;
    else if (digitalRead(button6) == LOW) pressedButton = 6;

    if (pressedButton != 0) {
      lastCheck = millis();
      return pressedButton;
    }
  }
  return 0;
}
