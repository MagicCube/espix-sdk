#include "View.h"

#include "../devices/Screen.h"

View::View() {
}

View::~View() {
  delete _drawingContext;
}

DrawingContext *View::getDrawingContext() {
  if (_drawingContext == NULL) {
    _drawingContext = ScreenClass::getInstance()->createDrawingContext();
  }
  return _drawingContext;
}

int View::getWidth() {
  return _drawingContext->getWidth();
}

int View::getHeight() {
  return _drawingContext->getHeight();
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
  auto context = getDrawingContext();
  if (clearBeforeRendering) {
    context->clear();
  }
  render(context);
}

void View::willMount() {
}

void View::render(DrawingContext *context) {
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
