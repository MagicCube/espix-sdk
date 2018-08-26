#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "../../espix-design/views/ProgressView.h"
#include "../animations/AnimationLoop.h"
#include "../devices/Screen.h"
#include "../views/ViewContainer.h"

// Represent the application of Expix.
class Application {
public:
  // Construct an Espix application.
  Application();

  static Application *getInstance();

  // Get root ViewContainer of application.
  ViewContainer *getRootViewContainer();

  // Get root view of application.
  View *getRootView();

  // Set root view of application.
  // It is the shortcut for getRootViewContainer()->setView().
  void setRootView(View *view, TransitionOptions transitionOptions = TRANSITION_OPTIONS_NONE);

  // Get current active view.
  View *getCurrentView();

  // Enable OTA.
  void enableOTA();

  // Fires when key pressed.
  void onKeyPress(KeyEventHandler onKeyPress);

  // Initialize application. Place this method in your setup().
  void begin();

  // Update application in the Arduino loop. Place this method in your loop().
  int update();

private:
  unsigned long _lastUpdate = 0;
  bool _otaEnabled = false;
  bool _otaUpdating = false;
  Screen *_screen = NULL;
  AnimationLoop _mainLoop;
  ViewContainer *_rootViewContainer;
  ProgressView *_firmwareUpdatingView;

  KeyEventHandler _onKeyPress = NULL;

  ProgressView *_getFirmwareUpdatingView();
  void _loop();
  void _handleKeyPress(KeyCode keyCode);
  void _fireKeyPressEvent(KeyCode keyCode);
};
