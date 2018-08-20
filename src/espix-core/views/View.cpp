#include "View.h"

#include "../drawings/Screen.h"

View::View() {
  _drawingContext = Screen::getInstance()->createDrawingContext();
}

DrawingContext *View::getDrawingContext() {
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

bool View::tryUpdate(ViewUpdateOptions options) {
  if (options.forceUpdate || isDirty() || shouldUpdate(options)) {
    update(options);
    _dirty = false;
    return true;
  }
  return false;
}

void View::redraw(bool clearBeforeRendering) {
  DrawingContext *context = getDrawingContext();
  if (clearBeforeRendering) {
    context->clear();
  }
  _lastUpdate = millis();
  render(context);
}

void View::willMount() {
}

void View::render(DrawingContext *context) {
}

void View::didMount() {
}

bool View::shouldUpdate(ViewUpdateOptions options) {
  return options.forceUpdate || isDirty();
}

void View::update(ViewUpdateOptions options) {
}

void View::willUnmount() {
}

void View::handleKeyPress(KeyCode keyCode) {
}
