#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "../drawings/Screen.h"

// Represent the application of Expix.
class Application {
public:
  // Construct an Espix application.
  Application(OLEDDisplay *display);

  // Initialize application. Place this method in your setup().
  void begin();

  // Update application in the Arduino loop. Place this method in your loop().
  int update();

  // Get a Screen object represent the current screen.
  Screen *getScreen();

private:
  Screen *_screen;
};
