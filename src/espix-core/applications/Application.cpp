#include "Application.h"

#include <ESP8266WiFi.h>

static Application *__instance = NULL;

Application::Application(OLEDDisplay *display) {
  _screen = new Screen(display);
  _screenContext = _screen->createDrawingContext();
  _keyboard = new Keyboard();
  _mainLoop = new AnimationLoop();
  _rootViewContainer = new ViewContainer();
  __instance = this;
}

Application *Application::getInstance() {
  return __instance;
}

Screen *Application::getScreen() {
  return _screen;
}

Keyboard *Application::getKeyboard() {
  return _keyboard;
}

wl_status_t Application::getWiFiStatus() {
  return WiFi.status();
}

bool Application::isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

ViewContainer *Application::getRootViewContainer() {
  return _rootViewContainer;
}

void Application::setRootView(View *view, TransitionOptions transitionOptions) {
  if (_rootViewContainer) {
    _rootViewContainer->setView(view, transitionOptions);
  }
}

void Application::onKeyPress(KeyEventHandler onKeyPress) {
  _onKeyPress = onKeyPress;
}

void Application::begin() {
  _screen->begin();

  _keyboard->onKeyPress([=](KeyCode keyCode) { _handleKeyPress(keyCode); });
  _keyboard->begin();

  _mainLoop->onTick([=](AnimationLoop *target) { _handleTick(); });
  _mainLoop->begin();

  _rootViewContainer->willMount();
  _rootViewContainer->redraw(true);
  _rootViewContainer->didMount();
}

int Application::update() {
  unsigned long updateStart = millis();
  _keyboard->update();
  _mainLoop->update();
  _screen->update();
  unsigned long elapsedSinceLastUpdate = millis() - _lastUpdate;
  int timeBudget = _mainLoop->getOptions().updateInterval - elapsedSinceLastUpdate;
  _lastUpdate = updateStart;
  return timeBudget;
}

void Application::connectToWiFi(WiFiConnectionSetting setting) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(setting.ssid, setting.ssid);
}

void Application::_handleTick() {
  if (_rootViewContainer != NULL) {
    ViewUpdateOptions options;
    if (_rootViewContainer->shouldUpdate(options)) {
      _rootViewContainer->update(options);
      _rootViewContainer->redraw(true);
      _screen->update();
    }
  }
}

void Application::_handleKeyPress(KeyCode keyCode) {
  if (_rootViewContainer) {
    _rootViewContainer->handleKeyPress(keyCode);
  } else {
    _fireKeyPressEvent(keyCode);
  }
}

void Application::_fireKeyPressEvent(KeyCode keyCode) {
  if (_onKeyPress != NULL) {
    _onKeyPress(keyCode);
  }
}
