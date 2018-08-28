#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "../../espix-design/views/ProgressView.h"
#include "../animations/AnimationLoop.h"
#include "../devices/Screen.h"
#include "../views/ViewContainer.h"

// Represents the application of Expix.
// The only instance of ApplicationClass is a global variable `Application`.
class ApplicationClass {
public:
  // Creates a new instance of Espix application.
  // Do not call this constructor directly. Always use the global variable `Application`.
  ApplicationClass();

  // Gets the root ViewContainer of application.
  ViewContainer *getRootViewContainer();

  // Sets root view of application.
  // It is the shortcut for getRootViewContainer()->setCurrentView().
  void setRootView(View *view, TransitionOptions transitionOptions = TRANSITION_OPTIONS_NONE);

  // Gets root view of application.
  View *getRootView();

  // Gets current active view.
  View *getCurrentView();

  // Enables OTA.
  void enableOTA();

  // Occurs when key pressed.
  void onKeyPress(KeyEventHandler handler);

  // Occurs when key pressed.
  void onScroll(ScrollEventHandler handler);

  // Initializes application. Place this method in Arduino's setup().
  void begin();

  // Updates application in the Arduino loop. Place this method in Arduino's loop().sd
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
  void _handleKeyPress(KeyEventArgs e);
  void _fireKeyPressEvent(KeyEventArgs e);
  void _handleScroll(ScrollEventArgs e);
  void _fireScrollEvent(ScrollEventArgs e);
};

extern ApplicationClass Application;
