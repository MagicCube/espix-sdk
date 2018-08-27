#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "../drawing/Canvas.h"
#include "../drawing/CanvasContext.h"

// Represents a screen.
class ScreenClass {
public:
  // Initializes a new instance of the Screen class.
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

  // Updates in loop().
  void update();

  // Clears buffer of screen.
  void clearBuffer();

  // Clears screen immediately.
  void clear();

private:
  OLEDDisplay *_display;
  Canvas *_canvas;
  int _brightness;
  bool _flipped = false;
  bool _mirrored = false;
};

extern ScreenClass Screen;
