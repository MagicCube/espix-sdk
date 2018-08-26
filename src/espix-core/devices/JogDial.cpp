#include "JogDial.h"

void log(String text) {
  Serial.print(millis());
  Serial.print("> ");
  Serial.println(text);
}


JogDial::JogDial(uint8_t clkPin, uint8_t dtPin) {
  _clkPin = clkPin;
  _dtPin = dtPin;
}

void JogDial::begin() {
  pinMode(_clkPin, INPUT_PULLUP);
  pinMode(_dtPin, INPUT_PULLUP);
}

void JogDial::update() {
  _clkValue = digitalRead(_clkPin);
  if (_clkValue != _lastClkValue) { // Means the knob is rotating
    if (digitalRead(_dtPin) !=
        _clkValue) { // Means pin clk changed first - We're rotating Clockwise
      _value++;
    } else {
      _value--;
    }
  }
  if (millis() - _lastUpdate > 200) {
    if (std::abs(_value) > 0) {
      if (_value > 0) {
        log("=>");
      } else if (_value < 0) {
        log("<=");
      }
    }
    _value = 0;
    _lastUpdate = millis();
  }
  _lastClkValue = _clkValue;
}
