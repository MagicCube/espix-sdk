#include <Arduino.h>

#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_LEFT_ARROW 37
#define KEY_UP_ARROW 38
#define KEY_RIGHT_ARROW 39
#define KEY_DOWN_ARROW 40
#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_D 68

class Keyboard;

enum KeyState { KEY_UP = HIGH, KEY_DOWN = LOW };

typedef uint8_t KeyCode;
typedef std::function<void(KeyCode)> KeyEventHandler;

class Key {
public:
  Key(KeyCode keyCode, uint8_t pin);

  uint8_t getPin();
  KeyState getState();

  void onKeyPress(KeyEventHandler handler);

  void disableRepeat();
  void enableRepeat();
  void update();

private:
  void _setState(KeyState state);
  void _fireKeyPressEvent();

  bool _allowRepeat = true;
  unsigned long _lastEvent;
  unsigned long _lastKeyPressing;

  KeyCode _keyCode;
  bool _keyPressed = false;
  uint8_t _pin;
  KeyState _state = KEY_UP;

  KeyEventHandler _onKeyPress = NULL;
};
