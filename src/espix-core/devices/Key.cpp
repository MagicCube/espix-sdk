#include "Key.h"

Key::Key(KeyCode keyCode, uint8_t pin) {
  _keyCode = keyCode;
  _pin = pin;
  if (_keyCode == KEY_ESC || _keyCode == KEY_ENTER) {
    disableRepeat();
  }
}

uint8_t Key::getPin() {
  return _pin;
}

KeyState Key::getState() {
  return _state;
}

void Key::enableRepeat() {
  _allowRepeat = true;
}

void Key::disableRepeat() {
  _allowRepeat = false;
}

void Key::onKeyPress(KeyEventHandler handler) {
  _onKeyPress = handler;
}

void Key::begin() {
  pinMode(_pin, INPUT_PULLUP);
}

void Key::update() {
  KeyState value = (KeyState)digitalRead(_pin);
  if (value == KeyState::KEY_DOWN) {
    if (_state == KeyState::KEY_UP) {
      _setState(KeyState::KEY_DOWN);
    } else if (_state == KeyState::KEY_DOWN) {
      if (!_keyPressed || (_allowRepeat && millis() - _lastKeyPressing > 500)) {
        if (!_keyPressed) {
          _keyPressed = true;
          _lastKeyPressing = millis();
        }
        _fireKeyPressEvent();
      }
    }
  } else if (value == KeyState::KEY_UP) {
    if (_state == KeyState::KEY_DOWN) {
      _keyPressed = false;
      _setState(KeyState::KEY_UP);
    }
  }
}

void Key::_setState(KeyState state) {
  _state = state;
}

void Key::_fireKeyPressEvent() {
  if (_onKeyPress) {
    if (millis() - _lastEvent > 100) {
      _lastEvent = millis();
      _onKeyPress(_keyCode);
    }
  }
}
