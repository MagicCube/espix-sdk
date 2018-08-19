#include "Application.h"

int x = 0;
int offsetX = 1;

Application::Application(OLEDDisplay *display) {
  _screen = new Screen(display);
  _screenContext = _screen->createDrawingContext();
  _keyboard = new Keyboard();
  _mainLoop = new AnimationLoop();
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
  x += offsetX;
  if (x < 0 && offsetX < 0) {
    offsetX = 1;
  } else if (x > 70 && offsetX > 0) {
    offsetX = -1;
  }
  _screenContext->clear();
  _screenContext->setFontSize(FONT_SIZE_H1);
  _screenContext->setOffset(x, 0);
  _screenContext->drawString("Hello");
}

void Application::_handleKeyPress(KeyCode keyCode) {
  _fireKeyPressEvent(keyCode);
}

void Application::_fireKeyPressEvent(KeyCode keyCode) {
  if (_onKeyPress != NULL) {
    _onKeyPress(keyCode);
  }
}
