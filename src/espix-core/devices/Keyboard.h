#pragma once
#include <Arduino.h>

#include "JogDial.h"
#include "Key.h"

// Represents a keyboard.
// The only instance of KeyboardClass is a global variable `Keyboard`.
class KeyboardClass {
public:
  // Creates a new instance of the keyboard class.
  // Do not call this constructor directly. Always use the global variable `Keyboard`.
  KeyboardClass();

  // Occurs when key pressed.
  void onKeyPress(KeyEventHandler handler);

  // Occurs when Jog Dial scrolled.
  void onScroll(ScrollEventHandler handler);

  // Initializes the keyboard.
  void begin();

  // Updates in loop.
  void update();

  // Registers keyCode and its mapping pin.
  void registerKey(KeyCode keyCode, uint8_t pin);

  // Registers KY04 encoder as Jog Dial.
  void registerJogDial(int clkPin, int dtPin, int swPin = -1);

private:
  void _handleKeyPress(KeyEventArgs e);
  void _handleScroll(ScrollEventArgs e);
  void _fireKeyPressEvent(KeyEventArgs e);
  void _fireScrollEvent(ScrollEventArgs e);

  Key *_keys[10];
  JogDial *_jogDial;
  int _keyCount = 0;
  KeyEventHandler _keyPressHandler = NULL;
  KeyEventHandler _onKeyPress = NULL;
  ScrollEventHandler _jogDialScrollHandler = NULL;
  ScrollEventHandler _onScroll = NULL;
};

extern KeyboardClass Keyboard;
