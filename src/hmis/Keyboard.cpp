#include "Keyboard.h"

Keyboard::Keyboard() {
  _keyPressHandler = [=](uint8_t keyCode) { this->_handleKeyPress(keyCode); };
}

void Keyboard::onKeyPress(KeyEventHandler handler) {
  _onKeyPress = handler;
}

void Keyboard::registerKey(KeyCode keyCode, uint8_t pin) {
  Key *key = new Key(keyCode, pin);
  key->onKeyPress(_keyPressHandler);
  _keys[_keyCount] = key;
  if (_keyCount < 10) {
    _keyCount++;
  } else {
    Serial.println("Error: Keyboard can only have 10 keys.");
  }
}

void Keyboard::update() {
  for (int i = 0; i < _keyCount; i++) {
    _keys[i]->update();
  }
}

void Keyboard::_handleKeyPress(uint8_t keyCode) {
  _fireKeyPressEvent(keyCode);
}

void Keyboard::_fireKeyPressEvent(KeyCode keyCode) {
  if (_onKeyPress != NULL) {
    _onKeyPress(keyCode);
  }
}
