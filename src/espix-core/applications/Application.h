#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "../../espix-design/views/ProgressView.h"
#include "../animations/AnimationLoop.h"
#include "../devices/Screen.h"
#include "../views/NavigationContainer.h"

// Represents the application of Expix.
// The only instance of ApplicationClass is a global variable `Application`.
class ApplicationClass {
public:
  // Creates a new instance of Espix application.
  // Do not call this constructor directly. Always use the global variable `Application`.
  ApplicationClass();

  // Get current active view.
  View *getCurrentView();

  // Sets root view of application.
  // It is the shortcut for getRootViewContainer()->setCurrentView().
  void setRootView(View *view, TransitionOptions transitionOptions = TRANSITION_OPTIONS_NONE);

  // Gets root view of application.
  View *getRootView();

  // Gets or sets the status bar view of navigation container.
  // Set to NULL if you don't want to use status bar.
  // Try StatusBar in espix-design if you don't want to implement one by yourself.
  View *getStatusBar();
  void setStatusBar(StatusBar *view);

  // Show or hide status bar.
  void showStatusBar();
  void hideStatusBar();

  // Pushes a specific view to the application navigation stack and display it.
  void pushView(View *view, TransitionOptions transitionOptions = TRANSITION_OPTIONS_LEFT);

  // Pops the view on the top of the application navigation stack and return it back.
  // Returns `NULL` if the navigation stack is empty.
  View *popView(TransitionOptions transitionOptions = TRANSITION_OPTIONS_RIGHT);

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
  ProgressView *_getProgressView();
  void _loop();
  void _handleKeyPress(KeyEventArgs e);
  void _fireKeyPressEvent(KeyEventArgs e);
  void _handleScroll(ScrollEventArgs e);
  void _fireScrollEvent(ScrollEventArgs e);

  unsigned long _lastUpdate = 0;
  bool _otaEnabled = false;
  bool _otaUpdating = false;
  AnimationLoop _mainLoop;
  NavigationContainer *_rootViewContainer;
  ProgressView *_progressView;

  KeyEventHandler _onKeyPress = NULL;
  ScrollEventHandler _onScroll = NULL;
};

extern ApplicationClass Application;
