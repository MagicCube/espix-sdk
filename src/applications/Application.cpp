#include "Application.h"

Application::Application(OLEDDisplay *display) {
  _screen = new Screen(display);
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
  _keyboard->update();
  _screen->update();

  return _mainLoop->update();
}

void Application::_handleTick() {
  Serial.println("Tick");
}

void Application::_handleKeyPress(KeyCode keyCode) {
  _fireKeyPressEvent(keyCode);
}

void Application::_fireKeyPressEvent(KeyCode keyCode) {
  if (_onKeyPress != NULL) {
    _onKeyPress(keyCode);
  }
}
