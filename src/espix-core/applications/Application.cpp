#include "Application.h"

#include <ArduinoOTA.h>

#include "../devices/Keyboard.h"
#include "../devices/Screen.h"
#include "../networking/WiFiNetwork.h"
#include "../timing/TimeClient.h"

ApplicationClass::ApplicationClass() {
  _rootViewContainer = new ViewContainer();
}

ViewContainer *ApplicationClass::getRootViewContainer() {
  return _rootViewContainer;
}

View *ApplicationClass::getRootView() {
  if (_rootViewContainer) {
    return _rootViewContainer->getCurrentView();
  }
  return NULL;
}

void ApplicationClass::setRootView(View *view, TransitionOptions transitionOptions) {
  if (_rootViewContainer) {
    _rootViewContainer->setView(view, transitionOptions);
  }
}

View *ApplicationClass::getCurrentView() {
  View *activeView = NULL;
  if (_otaUpdating) {
    activeView = _getProgressView();
  } else if (_rootViewContainer) {
    activeView = _rootViewContainer;
  }
  return activeView;
}

void ApplicationClass::enableOTA() {
  if (_otaEnabled) {
    return;
  }
  ArduinoOTA.begin();
  _otaEnabled = true;
  ArduinoOTA.onStart([=]() {
    _otaUpdating = true;
    _getProgressView()->setProgress(0);
    _loop();
  });
  ArduinoOTA.onProgress([=](unsigned int progress, unsigned int total) {
    _getProgressView()->setProgress(progress * 100 / total);
    _loop();
  });
  ArduinoOTA.onEnd([=]() {
    _getProgressView()->setProgress(100);
    _getProgressView()->setText("Restarting...");
    _loop();
  });
}

void ApplicationClass::onKeyPress(KeyEventHandler handler) {
  _onKeyPress = handler;
}

void ApplicationClass::onScroll(ScrollEventHandler handler) {
  _onScroll = handler;
}

void ApplicationClass::begin() {
  Keyboard.onKeyPress([=](KeyCode keyCode) { _handleKeyPress(keyCode); });
  Keyboard.onScroll([=](int delta) { _handleScroll(delta); });

  _mainLoop.onTick([=](AnimationLoop *target) { _loop(); });
  _mainLoop.begin();

  _setRootViewContainer(_rootViewContainer);
}

int ApplicationClass::update() {
  if (_otaEnabled) {
    ArduinoOTA.handle();
  }
  auto updateStart = millis();
  WiFiNetwork.update();
  Keyboard.update();
  _mainLoop.update();
  if (WiFiNetwork.isConnected()) {
    // Update time only when network is available.
    TimeClient.update();
  }
  auto elapsedSinceLastUpdate = millis() - _lastUpdate;
  int timeBudget = _mainLoop.getOptions().updateInterval - elapsedSinceLastUpdate;
  _lastUpdate = updateStart;
  return timeBudget;
}

void ApplicationClass::_setRootViewContainer(ViewContainer *container) {
  _rootViewContainer = container;
  _rootViewContainer->setCanvas(Screen.getCanvas());
  _rootViewContainer->resizeTo(Screen.getWidth(), Screen.getHeight());
  _rootViewContainer->willMount();
  _rootViewContainer->redraw(true);
  _rootViewContainer->didMount();
}

ProgressView *ApplicationClass::_getProgressView() {
  if (_progressView == NULL) {
    _progressView = new ProgressView("Updating firmware...");
    _progressView->resizeTo(Screen.getWidth(), Screen.getHeight());
  }
  return _progressView;
}

void ApplicationClass::_loop() {
  auto currentView = getCurrentView();

  if (currentView) {
    if (currentView->tryUpdate()) {
      currentView->redraw(true);
      Screen.update();
    }
  }
}

void ApplicationClass::_handleKeyPress(KeyCode keyCode) {
  _fireKeyPressEvent(keyCode);
  if (_rootViewContainer) {
    _rootViewContainer->handleKeyPress(keyCode);
  }
}

void ApplicationClass::_fireKeyPressEvent(KeyCode keyCode) {
  if (_onKeyPress) {
    _onKeyPress(keyCode);
  }
}

void ApplicationClass::_handleScroll(int delta) {
  _fireScrollEvent(delta);
  if (_rootViewContainer) {
    _rootViewContainer->handleScroll(delta);
  }
}

void ApplicationClass::_fireScrollEvent(int delta) {
  if (_onScroll) {
    _onScroll(delta);
  }
}

ApplicationClass Application;
