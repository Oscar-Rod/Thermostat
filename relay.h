#ifndef RELAY_H
#define RELAY_H

#include "Arduino.h"

class Relay {
  public:
    Relay(int relayPin);
    void init();
    void setOn();
    void setOff();
  private:
    int relayPin;
};

#endif
