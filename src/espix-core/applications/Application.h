#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "../../espix-design/views/ProgressView.h"
#include "../animations/AnimationLoop.h"
#include "../drawing/Screen.h"
#include "../hmis/Keyboard.h"
#include "../networking/WiFiNetwork.h"
#include "../views/ViewContainer.h"

// Represent the application of Expix.
class Application {
public:
  // Construct an Espix application.
  Application(OLEDDisplay *display);

  static Application *getInstance();

  // Get a Screen object represent the current screen.
  Screen *getScreen();

  // Get a Keyboard object represent the current keyboard.
  Keyboard *getKeyboard();

  // Get WiFi network.
  WiFiNetwork *getNetwork();

  // Get local IP Address of WiFi if connected.
  String getWiFiLocalIP();

  // Returns whether WiFi is now connected.
  bool isWiFiConnected();

  // Get root ViewContainer of application.
  ViewContainer *getRootViewContainer();

  // Get root view of application.
  View *getRootView();

  // Set root view of application.
  // It is the shortcut for getRootViewContainer()->setView().
  void setRootView(View *view, TransitionOptions transitionOptions = TRANSITION_OPTIONS_NONE);

  // Get current active view.
  View *getActiveView();

  // Enable OTA.
  void enableOTA();

  // Fires when key pressed.
  void onKeyPress(KeyEventHandler onKeyPress);

  // Initialize application. Place this method in your setup().
  void begin();

  // Update application in the Arduino loop. Place this method in your loop().
  int update();

  // Update and wait in Arduino's loop.
  void loop();

  // Connect to WiFi using given setting include ssid and password.
  void connectToWiFi(WiFiConnectionSetting setting);

private:
  unsigned long _lastUpdate;
  bool _otaEnabled;
  bool _otaUpgrading;
  Screen *_screen;
  DrawingContext *_screenContext;
  Keyboard *_keyboard;
  WiFiNetwork *_network;
  AnimationLoop *_mainLoop;
  ViewContainer *_rootViewContainer;
  ProgressView *_otaUpgradingView;

  KeyEventHandler _onKeyPress;

  ProgressView *_getOtaUpgradingView();
  void _handleTick();
  void _handleKeyPress(KeyCode keyCode);
  void _fireKeyPressEvent(KeyCode keyCode);
};
