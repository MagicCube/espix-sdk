#include "Application.h"

Application::Application(OLEDDisplay *display) {
  _screen = new Screen(display);
}

Screen *Application::getScreen() {
  return _screen;
}

void Application::begin() {
  _screen->begin();
}

int Application::update() {
  return 100;
}
