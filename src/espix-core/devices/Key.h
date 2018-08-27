#include <Arduino.h>

#include "KeyCode.h"
#include "events.h"

class Keyboard;

enum class KeyState { UP = HIGH, DOWN = LOW };

class Key {
public:
  Key(KeyCode keyCode, uint8_t pin);

  uint8_t getPin();
  KeyState getState();
  void disableRepeat();
  void enableRepeat();

  void onKeyPress(KeyEventHandler handler);

  void begin();
  void update();

private:
  void _setState(KeyState state);
  void _fireKeyPressEvent();

  bool _allowRepeat = true;
  unsigned long _lastEvent = 0;
  unsigned long _lastKeyPressing = 0;

  KeyCode _keyCode;
  bool _keyPressed = false;
  uint8_t _pin = 0;
  KeyState _state = KeyState::UP;

  KeyEventHandler _onKeyPress = NULL;
};
