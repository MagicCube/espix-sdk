#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "../../espix-design/views/ProgressView.h"
#include "../animations/AnimationLoop.h"
#include "../devices/Screen.h"
#include "../views/ViewContainer.h"

// Represent the application of Expix.
class ApplicationClass {
public:
  // Construct a new Espix application.
  ApplicationClass();

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
  void onKeyPress(KeyEventHandler handler);

  // Fires when key pressed.
  void onScroll(ScrollEventHandler handler);

  // Initialize application. Place this method in your setup().
  void begin();

  // Update application in the Arduino loop. Place this method in your loop().
  int update();

private:
  unsigned long _lastUpdate = 0;
  bool _otaEnabled = false;
  bool _otaUpdating = false;
  AnimationLoop _mainLoop;
  ViewContainer *_rootViewContainer;
  ProgressView *_progressView;

  KeyEventHandler _onKeyPress = NULL;
  ScrollEventHandler _onScroll = NULL;

  void _setRootViewContainer(ViewContainer *container);
  ProgressView *_getProgressView();
  void _loop();
  void _handleKeyPress(KeyCode keyCode);
  void _fireKeyPressEvent(KeyCode keyCode);
  void _handleScroll(int delta);
  void _fireScrollEvent(int delta);
};

extern ApplicationClass Application;
