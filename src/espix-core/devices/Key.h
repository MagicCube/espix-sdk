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

enum class KeyState { UP = HIGH, DOWN = LOW };

typedef uint8_t KeyCode;
typedef std::function<void(KeyCode)> KeyEventHandler;

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
