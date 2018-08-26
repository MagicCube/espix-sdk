#include "Application.h"

#include <ArduinoOTA.h>

#include "../devices/Keyboard.h"
#include "../timing/TimeClient.h"

static Application *__instance = NULL;

Application::Application(OLEDDisplay *display) {
  _screen = new Screen(display);
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

WiFiNetwork *Application::getNetwork() {
  return _network;
}

ViewContainer *Application::getRootViewContainer() {
  return _rootViewContainer;
}

View *Application::getRootView() {
  if (_rootViewContainer) {
    return _rootViewContainer->getCurrentView();
  }
  return NULL;
}

void Application::setRootView(View *view, TransitionOptions transitionOptions) {
  if (_rootViewContainer) {
    _rootViewContainer->setView(view, transitionOptions);
  }
}

View *Application::getCurrentView() {
  View *activeView = NULL;
  if (_otaUpdating) {
    activeView = _getFirmwareUpdatingView();
  } else if (_rootViewContainer) {
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
    _otaUpdating = true;
    _getFirmwareUpdatingView()->setProgress(0);
    _loop();
  });
  ArduinoOTA.onProgress([=](unsigned int progress, unsigned int total) {
    _getFirmwareUpdatingView()->setProgress(progress * 100 / total);
    _loop();
  });
  ArduinoOTA.onEnd([=]() {
    _getFirmwareUpdatingView()->setProgress(100);
    _getFirmwareUpdatingView()->setText("Restarting...");
    _loop();
  });
}

void Application::onKeyPress(KeyEventHandler onKeyPress) {
  _onKeyPress = onKeyPress;
}

void Application::begin() {
  _screen->begin();

  Keyboard.onKeyPress([=](KeyCode keyCode) { _handleKeyPress(keyCode); });

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
  Keyboard.update();
  _mainLoop->update();
  if (_network->isConnected()) {
    // Update time only when network is available.
    TimeClient.update();
  }
  auto elapsedSinceLastUpdate = millis() - _lastUpdate;
  int timeBudget = _mainLoop->getOptions().updateInterval - elapsedSinceLastUpdate;
  _lastUpdate = updateStart;
  return timeBudget;
}

ProgressView *Application::_getFirmwareUpdatingView() {
  if (_firmwareUpdatingView == NULL) {
    _firmwareUpdatingView = new ProgressView("Updating firmware...");
  }
  return _firmwareUpdatingView;
}

void Application::_loop() {
  auto currentView = getCurrentView();

  if (currentView) {
    if (currentView->tryUpdate()) {
      currentView->redraw(true);
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
  if (_onKeyPress) {
    _onKeyPress(keyCode);
  }
}
