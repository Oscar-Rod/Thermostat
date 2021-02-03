#include "relay.h"

Relay::Relay(int relayPin) {
  this->relayPin = relayPin;
}

void Relay::init() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void Relay::setOn() {
  digitalWrite(relayPin, HIGH);
}

void Relay::setOff() {
  digitalWrite(relayPin, LOW);
}
