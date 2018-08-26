#pragma once
#include <Arduino.h>

#include "JogDial.h"
#include "Key.h"

// Represent a keyboard.
class KeyboardClass {
public:
  // Construct a new Keyboard.
  KeyboardClass();

  // Fires when key pressed.
  void onKeyPress(KeyEventHandler handler);

  // Fires when Jog Dial scrolled.
  void onScroll(ScrollEventHandler handler);

  // Initialize keyboard.
  void begin();

  // Update in loop().
  void update();

  // Register keyCode and its mapping pin.
  void registerKey(KeyCode keyCode, uint8_t pin);

  // Register KY04 encoder.
  void registerJogDial(int clkPin, int dtPin, int swPin = -1);

private:
  void _handleKeyPress(KeyCode keyCode);
  void _handleScroll(int delta);
  void _fireKeyPressEvent(KeyCode keyCode);
  void _fireScrollEvent(int delta);

  Key *_keys[10];
  JogDial *_jogDial;
  int _keyCount = 0;
  KeyEventHandler _keyPressHandler = NULL;
  KeyEventHandler _onKeyPress = NULL;
  ScrollEventHandler _jogDialScrollHandler = NULL;
  KeyEventHandler _onScroll = NULL;
};

extern KeyboardClass Keyboard;
