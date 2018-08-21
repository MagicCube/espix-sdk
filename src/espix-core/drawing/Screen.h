#pragma once

#include <Arduino.h>

#include "../../ESP8266_SSD1306/OLEDDisplay.h"

class DrawingContext;

// Represent an OLED screen, you use this class to get screen resolution or set brightness.
class Screen {
public:
  // Construct a Screen object by passing an OLEDDisplay object.
  Screen(OLEDDisplay *_display);

  // Get singlton of Screen.
  static Screen *getInstance();

  // Get internal OLEDDisplay object.
  OLEDDisplay *getDisplay();

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

  // Marks screen as dirty.
  void setDirty();

  // Initialize screen.
  void begin();

  // Update in loop().
  void update();

  // Clear buffer of screen.
  void clearBuffer();

  // Clear screen immediately.
  void clear();

  // Create a new DrawingContext object.
  DrawingContext *createDrawingContext();

private:
  OLEDDisplay *_display;
  int _brightness;
  bool _flipped;
  bool _mirrored;
  bool _dirty;
};
