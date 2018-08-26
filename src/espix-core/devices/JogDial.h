#pragma once

#include <Arduino.h>

class JogDial {
public:
  JogDial(uint8_t clkPin, uint8_t dtPin);

  void begin();
  void update();

private:
  uint8_t _clkPin;
  uint8_t _dtPin;
  int _clkValue = HIGH;
  int _lastClkValue = HIGH;
  int _value = 0;
  unsigned long _lastUpdate = 0;
};
