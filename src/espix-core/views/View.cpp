#include "View.h"

#include "../devices/Screen.h"

View::View() {
}

View::~View() {
  delete _CanvasContext;
}

CanvasContext *View::getCanvasContext() {
  if (_CanvasContext == NULL) {
    _CanvasContext = Screen.getCanvas()->createContext();
  }
  return _CanvasContext;
}

int View::getWidth() {
  return _CanvasContext->getWidth();
}

int View::getHeight() {
  return _CanvasContext->getHeight();
}

bool View::isDirty() {
  return _dirty;
}

void View::setDirty() {
  _dirty = true;
}

unsigned long View::getLastUpdate() {
  return _lastUpdate;
}

bool View::tryUpdate() {
  if (isDirty() || shouldUpdate()) {
    update();
    _lastUpdate = millis();
    _dirty = false;
    return true;
  }
  return false;
}

void View::redraw(bool clearBeforeRendering) {
  auto context = getCanvasContext();
  if (clearBeforeRendering) {
    context->clear();
  }
  render(context);
}

void View::willMount() {
}

void View::render(CanvasContext *context) {
}

void View::didMount() {
}

bool View::shouldUpdate() {
  return isDirty();
}

void View::update() {
}

void View::willUnmount() {
}

void View::handleKeyPress(KeyCode keyCode) {
}

void View::handleScroll(int delta) {
}
