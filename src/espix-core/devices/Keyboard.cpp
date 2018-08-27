#include "Keyboard.h"

KeyboardClass::KeyboardClass() {
  _keyPressHandler = [=](KeyCode keyCode) { this->_handleKeyPress(keyCode); };
  _jogDialScrollHandler = [=](int delta) { this->_handleScroll(delta); };
}

void KeyboardClass::onKeyPress(KeyEventHandler handler) {
  _onKeyPress = handler;
}

void KeyboardClass::onScroll(ScrollEventHandler handler) {
  _onScroll = handler;
}

void KeyboardClass::registerKey(KeyCode keyCode, uint8_t pin) {
  auto key = new Key(keyCode, pin);
  key->onKeyPress(_keyPressHandler);
  _keys[_keyCount] = key;
  if (_keyCount < 10) {
    _keyCount++;
  }
}

void KeyboardClass::registerJogDial(int clkPin, int dtPin, int swPin) {
  _jogDial = new JogDial(clkPin, dtPin);
  _jogDial->onScroll(_jogDialScrollHandler);
  if (swPin > 0) {
    registerKey(KEY_ENTER, swPin);
  }
}

void KeyboardClass::begin() {
  if (_jogDial) {
    _jogDial->begin();
  }
  for (int i = 0; i < _keyCount; i++) {
    _keys[i]->begin();
  }
}

void KeyboardClass::update() {
  if (_jogDial) {
    _jogDial->update();
  }
  for (int i = 0; i < _keyCount; i++) {
    _keys[i]->update();
  }
}

void KeyboardClass::_handleKeyPress(uint8_t keyCode) {
  _fireKeyPressEvent(keyCode);
}

void KeyboardClass::_handleScroll(int delta) {
  _fireScrollEvent(delta);
}

void KeyboardClass::_fireKeyPressEvent(KeyCode keyCode) {
  if (_onKeyPress) {
    _onKeyPress(keyCode);
  }
}

void KeyboardClass::_fireScrollEvent(int delta) {
  if (_onScroll) {
    _onScroll(delta);
  }
}

KeyboardClass Keyboard;
