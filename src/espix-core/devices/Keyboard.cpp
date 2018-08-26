#include "Keyboard.h"

KeyboardClass::KeyboardClass() {
  _keyPressHandler = [=](uint8_t keyCode) { this->_handleKeyPress(keyCode); };
}

void KeyboardClass::onKeyPress(KeyEventHandler handler) {
  _onKeyPress = handler;
}

void KeyboardClass::registerKey(KeyCode keyCode, uint8_t pin) {
  auto key = new Key(keyCode, pin);
  key->onKeyPress(_keyPressHandler);
  _keys[_keyCount] = key;
  if (_keyCount < 10) {
    _keyCount++;
  } else {
    Serial.println("Error: Keyboard can only have 10 keys.");
  }
}

void KeyboardClass::begin() {
  for (int i = 0; i < _keyCount; i++) {
    _keys[i]->begin();
  }
}

void KeyboardClass::update() {
  for (int i = 0; i < _keyCount; i++) {
    _keys[i]->update();
  }
}

void KeyboardClass::_handleKeyPress(uint8_t keyCode) {
  _fireKeyPressEvent(keyCode);
}

void KeyboardClass::_fireKeyPressEvent(KeyCode keyCode) {
  if (_onKeyPress) {
    _onKeyPress(keyCode);
  }
}

KeyboardClass Keyboard;
