#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <OLEDDisplay.h>

#include "../animations/AnimationLoop.h"
#include "../drawings/Screen.h"
#include "../hmis/Keyboard.h"
#include "../views/ViewContainer.h"

struct WiFiConnectionSetting {
  WiFiConnectionSetting(String p_ssid, String p_password = "") {
    ssid = p_ssid;
    password = p_password;
  }

  String ssid;
  String password;
};

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

  // Get WiFi status.
  wl_status_t getWiFiStatus();

  // Get local IP Address of WiFi if connected.
  String getWiFiLocalIP();

  // Returns whether WiFi is now connected.
  bool isWiFiConnected();

  // Get root ViewContainer of application.
  ViewContainer *getRootViewContainer();

  // Set root view of application.
  // It is the shortcut for getRootViewContainer()->setView().
  void setRootView(View *view, TransitionOptions transitionOptions = TRANSITION_OPTIONS_NONE);

  // Fires when key pressed.
  void onKeyPress(KeyEventHandler onKeyPress);

  // Initialize application. Place this method in your setup().
  void begin();

  // Update application in the Arduino loop. Place this method in your loop().
  int update();

  // Connect to WiFi using given setting include ssid and password.
  void connectToWiFi(WiFiConnectionSetting setting);

private:
  unsigned long _lastUpdate;
  Screen *_screen;
  DrawingContext *_screenContext;
  Keyboard *_keyboard;
  AnimationLoop *_mainLoop;
  ViewContainer *_rootViewContainer;

  KeyEventHandler _onKeyPress;

  void _handleTick();
  void _handleKeyPress(KeyCode keyCode);
  void _fireKeyPressEvent(KeyCode keyCode);
};
