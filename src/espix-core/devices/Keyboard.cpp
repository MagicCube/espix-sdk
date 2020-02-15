#include "Keyboard.h"

KeyboardClass::KeyboardClass() {
  _keyPressHandler = [=](KeyEventArgs *e) { this->_handleKeyPress(e); };
  _jogDialScrollHandler = [=](ScrollEventArgs *e) { this->_handleScroll(e); };
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

void KeyboardClass::_handleKeyPress(KeyEventArgs *e) {
  _fireKeyPressEvent(e);
}

void KeyboardClass::_handleScroll(ScrollEventArgs *e) {
  _fireScrollEvent(e);
}

void KeyboardClass::_fireKeyPressEvent(KeyEventArgs *e) {
  if (_onKeyPress) {
    _onKeyPress(e);
  }
}

void KeyboardClass::_fireScrollEvent(ScrollEventArgs *e) {
  if (_onScroll) {
    _onScroll(e);
  }
}

KeyboardClass Keyboard;
