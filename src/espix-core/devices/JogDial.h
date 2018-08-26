#pragma once

#include <Arduino.h>

#include <Encoder.h>

typedef std::function<void(int)> ScrollEventHandler;

class JogDial {
public:
  JogDial(uint8_t clkPin, uint8_t dtPin);

  void onScroll(ScrollEventHandler handler);

  void begin();
  void update();

private:
  void _fireScrollEvent(int delta);

  Encoder _encoder;
  ScrollEventHandler _onScroll = NULL;
  unsigned long _lastUpdate = 0;
};
