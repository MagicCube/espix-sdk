#include "JogDial.h"

JogDial::JogDial(uint8_t clkPin, uint8_t dtPin) : _encoder(clkPin, dtPin) {
}

void JogDial::onScroll(ScrollEventHandler handler) {
  _onScroll = handler;
}

void JogDial::begin() {
}

void JogDial::update() {
  if (millis() - _lastUpdate > 150) {
    int value = _encoder.read();
    if (value != 0) {
      if (std::abs(value) > 1) {
        value = value / 2;
      }
      _fireScrollEvent(ScrollEventArgs(value));
      _encoder.write(0);
    }
    _lastUpdate = millis();
  }
}

void JogDial::_fireScrollEvent(ScrollEventArgs e) {
  if (_onScroll) {
    _onScroll(e);
  }
}
