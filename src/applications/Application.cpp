#include "Application.h"

Application::Application(OLEDDisplay *display) {
  _screen = new Screen(display);
  _keyboard = new Keyboard();
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

  _keyboard->begin();
  _keyboard->onKeyPress([=](KeyCode keyCode) { _handleKeyPress(keyCode); });
}

int Application::update() {
  return 100;
}


void Application::_handleKeyPress(KeyCode keyCode) {
  _fireKeyPressEvent(keyCode);
}

void Application::_fireKeyPressEvent(KeyCode keyCode) {
  if (_onKeyPress != NULL) {
    _onKeyPress(keyCode);
  }
}
