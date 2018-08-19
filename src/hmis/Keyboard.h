#pragma once
#include <Arduino.h>

#include "Key.h"

// Represent a keyboard.
class Keyboard {
public:
  // Construct a new Keyboard.
  Keyboard();

  // Fires when key pressed.
  void onKeyPress(KeyEventHandler handler);

  // Initialize keyboard.
  void begin();

  // Update in loop().
  void update();

  // Register keyCode and its mapping pin.
  void registerKey(KeyCode keyCode, uint8_t pin);

private:
  void _handleKeyPress(KeyCode keyCode);
  void _fireKeyPressEvent(KeyCode keyCode);

  Key *_keys[10];
  int _keyCount;
  KeyEventHandler _keyPressHandler;
  KeyEventHandler _onKeyPress;
};
