#include "Application.h"

#include <ArduinoOTA.h>

#include "../timing/TimeClient.h"

static Application *__instance = NULL;

Application::Application(OLEDDisplay *display) {
  _screen = new Screen(display);
  _screenContext = _screen->createDrawingContext();
  _keyboard = new Keyboard();
  _mainLoop = new AnimationLoop();
  _network = new WiFiNetwork();
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

WiFiNetwork *Application::getNetwork() {
  return _network;
}

ViewContainer *Application::getRootViewContainer() {
  return _rootViewContainer;
}

View *Application::getRootView() {
  if (_rootViewContainer != NULL) {
    return _rootViewContainer->getView();
  }
  return NULL;
}

void Application::setRootView(View *view, TransitionOptions transitionOptions) {
  if (_rootViewContainer) {
    _rootViewContainer->setView(view, transitionOptions);
  }
}

View *Application::getActiveView() {
  View *activeView = NULL;
  if (_otaUpgrading) {
    activeView = _getOtaUpgradingView();
  } else if (_rootViewContainer != NULL) {
    activeView = _rootViewContainer;
  }
  return activeView;
}

void Application::enableOTA() {
  if (_otaEnabled) {
    return;
  }
  ArduinoOTA.begin();
  _otaEnabled = true;
  ArduinoOTA.onStart([=]() {
    _otaUpgrading = true;
    _getOtaUpgradingView()->setProgress(0);
    _loop();
  });
  ArduinoOTA.onProgress([=](unsigned int progress, unsigned int total) {
    _getOtaUpgradingView()->setProgress(progress * 100 / total);
    _loop();
  });
  ArduinoOTA.onEnd([=]() {
    _getOtaUpgradingView()->setProgress(100);
    _getOtaUpgradingView()->setText("Restarting...");
    _loop();
  });
}

void Application::onKeyPress(KeyEventHandler onKeyPress) {
  _onKeyPress = onKeyPress;
}

void Application::begin() {
  _screen->begin();

  _keyboard->onKeyPress([=](KeyCode keyCode) { _handleKeyPress(keyCode); });
  _keyboard->begin();

  _mainLoop->onTick([=](AnimationLoop *target) { _loop(); });
  _mainLoop->begin();

  _rootViewContainer->willMount();
  _rootViewContainer->redraw(true);
  _rootViewContainer->didMount();
}

int Application::update() {
  if (_otaEnabled) {
    ArduinoOTA.handle();
  }
  auto updateStart = millis();
  _network->update();
  _keyboard->update();
  _mainLoop->update();
  if (_network->isConnected()) {
    // Update time only when network is available.
    TimeClient::getInstance()->update();
  }
  auto elapsedSinceLastUpdate = millis() - _lastUpdate;
  int timeBudget = _mainLoop->getOptions().updateInterval - elapsedSinceLastUpdate;
  _lastUpdate = updateStart;
  return timeBudget;
}

ProgressView *Application::_getOtaUpgradingView() {
  if (_otaUpgradingView == NULL) {
    _otaUpgradingView = new ProgressView("Upgrading firmware...");
  }
  return _otaUpgradingView;
}

void Application::_loop() {
  auto activeView = getActiveView();

  if (activeView != NULL) {
    if (activeView->tryUpdate()) {
      activeView->redraw(true);
      _screen->update();
    }
  }
}

void Application::_handleKeyPress(KeyCode keyCode) {
  _fireKeyPressEvent(keyCode);
  if (_rootViewContainer) {
    _rootViewContainer->handleKeyPress(keyCode);
  }
}

void Application::_fireKeyPressEvent(KeyCode keyCode) {
  if (_onKeyPress != NULL) {
    _onKeyPress(keyCode);
  }
}
