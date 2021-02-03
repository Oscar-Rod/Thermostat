#ifndef BUTTONS_H
#define BUTTONS_H

#include "Arduino.h"

class Buttons {
  public:
    Buttons(int pin_1, int pin_2, int pin_3, int pin_4, int pin_5, int pin_6);
    void init();
    int check();
  private:
    unsigned long lastCheck;
    int delayInMillis = 750;
    int button1;
    int button2;
    int button3;
    int button4;
    int button5;
    int button6;
};

#endif
