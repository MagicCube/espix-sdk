#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "../drawing/Canvas.h"
#include "../drawing/CanvasContext.h"

// Represents a screen.
// The only instance of ScreenClass is a global variable `Screen`.
class ScreenClass {
public:
  // Creates a new instance of the Screen class.
  // Do not call this constructor directly. Always use the global variable `Screen`.
  ScreenClass();

  // Gets the internal OLEDDisplay object.
  OLEDDisplay *getDisplay();

  // Gets the canvas of screen.
  Canvas *getCanvas();

  // Gets or sets brightness percentage of the screen. The range of percentage is 0-100.
  uint8_t getBrightness();
  void setBrightness(uint8_t percentage);

  // Gets true if the screen is flipped vertically.
  bool isFlipped();

  // Sets whether the screen is flipped and mirrored.
  void setOrientation(bool flipped = false, bool mirrored = false);

  // Gets true if the screen is mirrored horizontally.
  bool isMirrored();

  // Gets width of the screen.
  int getWidth();

  // Gets height of the screen.
  int getHeight();

  // Initializes screen.
  void begin(OLEDDisplay *display);

  // Updates in the loop.
  void update();

  // Clears buffer of screen.
  void clearBuffer();

  // Clears screen immediately.
  void clear();

  // Turns on.
  void turnOn();

  // Turns off.
  void turnOff();

  // Dim screen to minimum brightness.
  void dim();

  // Reset auto dim timer.
  void activate();


private:
  OLEDDisplay *_display;
  Canvas *_canvas;
  int _brightness = 255;
  bool _flipped = false;
  bool _mirrored = false;
  uint32_t _lastActiveTime = millis();
};

extern ScreenClass Screen;
