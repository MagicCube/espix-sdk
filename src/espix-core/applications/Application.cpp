#include "Application.h"

#include <ArduinoOTA.h>

#include "../devices/Keyboard.h"
#include "../devices/Screen.h"
#include "../networking/WiFiNetwork.h"
#include "../timing/TimeClient.h"

ApplicationClass::ApplicationClass() {
  _rootViewContainer = new NavigationContainer();
}

NavigationContainer *ApplicationClass::getRootViewContainer() {
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
    _rootViewContainer->setCurrentView(view, transitionOptions);
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
    _getProgressView()->setCanvas(Screen.getCanvas());
    _getProgressView()->resizeTo(Screen.getWidth(), Screen.getHeight());
    _getProgressView()->setMode(ProgressMode::DETERMINATE);
    _getProgressView()->setProgress(0);
    _getProgressView()->setText("Updating firmware...");
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
  Keyboard.onKeyPress([=](KeyEventArgs e) { _handleKeyPress(e); });
  Keyboard.onScroll([=](ScrollEventArgs e) { _handleScroll(e); });

  _mainLoop.onTick([=]() { _loop(); });
  _mainLoop.begin();

  _rootViewContainer->setCanvas(Screen.getCanvas());
  _rootViewContainer->resizeTo(Screen.getWidth(), Screen.getHeight());
  _rootViewContainer->willMount();
  _rootViewContainer->redraw(true);
  _rootViewContainer->didMount();
}

int ApplicationClass::update() {
  if (_otaEnabled) {
    ArduinoOTA.handle();
  }
  auto updateStart = millis();
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

ProgressView *ApplicationClass::_getProgressView() {
  if (_progressView == NULL) {
    _progressView = new ProgressView();
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

void ApplicationClass::_handleKeyPress(KeyEventArgs e) {
  _fireKeyPressEvent(e);
  if (_rootViewContainer) {
    _rootViewContainer->handleKeyPress(e);
  }
}

void ApplicationClass::_fireKeyPressEvent(KeyEventArgs e) {
  if (_onKeyPress) {
    _onKeyPress(e);
  }
}

void ApplicationClass::_handleScroll(ScrollEventArgs e) {
  _fireScrollEvent(e);
  if (_rootViewContainer) {
    _rootViewContainer->handleScroll(e);
  }
}

void ApplicationClass::_fireScrollEvent(ScrollEventArgs e) {
  if (_onScroll) {
    _onScroll(e);
  }
}

ApplicationClass Application;
