#include "Application.h"

static Application *__instance = NULL;

Application::Application(OLEDDisplay *display) {
  _screen = new Screen(display);
  _screenContext = _screen->createDrawingContext();
  _keyboard = new Keyboard();
  _mainLoop = new AnimationLoop();
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

void Application::onKeyPress(KeyEventHandler onKeyPress) {
  _onKeyPress = onKeyPress;
}

void Application::begin() {
  _screen->begin();

  _keyboard->onKeyPress([=](KeyCode keyCode) { _handleKeyPress(keyCode); });
  _keyboard->begin();

  _mainLoop->onTick([=](AnimationLoop *target) { _handleTick(); });
  _mainLoop->begin();
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

void Application::_handleTick() {
}

void Application::_handleKeyPress(KeyCode keyCode) {
  _fireKeyPressEvent(keyCode);
}

void Application::_fireKeyPressEvent(KeyCode keyCode) {
  if (_onKeyPress != NULL) {
    _onKeyPress(keyCode);
  }
}
