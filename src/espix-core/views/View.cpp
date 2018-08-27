#include "View.h"

View::View() {
  _canvasContext = new CanvasContext();
}

View::~View() {
  delete _canvasContext;
}

CanvasContext *View::getCanvasContext() {
  return _canvasContext;
}

int View::getWidth() {
  return _canvasContext->getWidth();
}

int View::getHeight() {
  return _canvasContext->getHeight();
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

void View::redraw(Canvas *canvas, bool clearBeforeRendering) {
  auto context = getCanvasContext();
  context->setCanvas(canvas);
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
