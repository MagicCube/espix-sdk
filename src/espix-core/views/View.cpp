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
void View::setWidth(int width) {
  _canvasContext->setWidth(width);
}

int View::getHeight() {
  return _canvasContext->getHeight();
}
void View::setHeight(int height) {
  _canvasContext->setHeight(height);
}

int View::getLeft() {
  return _canvasContext->getOffsetX();
}
void View::setLeft(int left) {
  _canvasContext->setOffsetX(left);
}

int View::getTop() {
  return _canvasContext->getOffsetY();
}
void View::setTop(int top) {
  _canvasContext->setOffsetY(top);
}

void View::resizeTo(int width, int height) {
  setWidth(width);
  setHeight(height);
}

void View::moveTo(int left, int top) {
  setLeft(left);
  setTop(top);
}

void View::setBounds(int left, int top, int width, int height) {
  moveTo(left, top);
  resizeTo(width, height);
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
