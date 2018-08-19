#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "../animations/AnimationLoop.h"
#include "../drawings/Screen.h"
#include "../hmis/Keyboard.h"

// Represent the application of Expix.
class Application {
public:
  // Construct an Espix application.
  Application(OLEDDisplay *display);

  // Get a Screen object represent the current screen.
  Screen *getScreen();

  // Get a Keyboard object represent the current keyboard.
  Keyboard *getKeyboard();

  // Fires when key pressed.
  void onKeyPress(KeyEventHandler onKeyPress);

  // Initialize application. Place this method in your setup().
  void begin();

  // Update application in the Arduino loop. Place this method in your loop().
  int update();


private:
  unsigned long _lastUpdate;
  Screen *_screen;
  DrawingContext *_screenContext;
  Keyboard *_keyboard;
  AnimationLoop *_mainLoop;

  KeyEventHandler _onKeyPress;

  void _handleTick();
  void _handleKeyPress(KeyCode keyCode);
  void _fireKeyPressEvent(KeyCode keyCode);
};
