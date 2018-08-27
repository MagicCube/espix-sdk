#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "../drawing/Canvas.h"
#include "../drawing/CanvasContext.h"

// Represent an OLED screen, you use this class to get screen resolution or set brightness.
class ScreenClass {
public:
  // Construct a Screen object by passing an OLEDDisplay object.
  ScreenClass();

  // Get internal OLEDDisplay object.
  OLEDDisplay *getDisplay();

  // Get canvas of screen.
  Canvas *getCanvas();

  // Get brightness percentage of the screen. The range of percentage is 0-100.
  uint8_t getBrightness();

  // Set brightness percentage of the screen. The range of percentage is 0-100.
  void setBrightness(uint8_t percentage);

  // Return true if the screen is flipped vertically.
  bool isFlipped();

  // Set whether the screen is flipped and mirrored.
  void setOrientation(bool flipped = false, bool mirrored = false);

  // Return true if the screen is mirrored horizontally.
  bool isMirrored();

  // Get width of the screen.
  int getWidth();

  // Get height of the screen.
  int getHeight();

  // Initialize screen.
  void begin(OLEDDisplay *display);

  // Update in loop().
  void update();

  // Clear buffer of screen.
  void clearBuffer();

  // Clear screen immediately.
  void clear();

  // Create a new CanvasContext object.
  CanvasContext *createCanvasContext();

private:
  OLEDDisplay *_display;
  Canvas *_canvas;
  int _brightness;
  bool _flipped = false;
  bool _mirrored = false;
};

extern ScreenClass Screen;
