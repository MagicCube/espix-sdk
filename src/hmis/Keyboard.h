#pragma once
#include <Arduino.h>

#include "Key.h"

class Keyboard {
public:
  Keyboard();

  void onKeyPress(KeyEventHandler handler);

  void registerKey(KeyCode keyCode, uint8_t pin);
  void update();

private:
  void _handleKeyPress(KeyCode keyCode);
  void _fireKeyPressEvent(KeyCode keyCode);

  Key *_keys[10];
  int _keyCount;
  KeyEventHandler _keyPressHandler;
  KeyEventHandler _onKeyPress;
};
