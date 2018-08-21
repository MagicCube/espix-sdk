#include "Application.h"

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

void Application::loop() {
  int timeBudget = app->update();
  if (timeBudget > 0) {
    delay(timeBudget);
  }
}

void Application::_handleTick() {
  if (_rootViewContainer != NULL) {
    if (_rootViewContainer->tryUpdate()) {
      _rootViewContainer->redraw(true);
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
