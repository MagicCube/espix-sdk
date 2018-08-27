#include "View.h"

View::View() {
  _canvasContext = new CanvasContext();
}

View::~View() {
  delete _canvasContext;
}

View *View::getParentView() {
  return _parentView;
}

void View::setParentView(View *parentView) {
  _parentView = parentView;
}

CanvasContext *View::getCanvasContext() {
  return _canvasContext;
}

int View::getWidth() {
  return _width;
}
void View::setWidth(int width) {
  _width = width;
  _canvasContext->setWidth(_width);
}

int View::getHeight() {
  return _height;
}
void View::setHeight(int height) {
  _height = height;
  _canvasContext->setHeight(_height);
}

int View::getLeft() {
  return _left;
}
void View::setLeft(int left) {
  _left = left;
  _canvasContext->setOffsetX(_left);
}

int View::getTop() {
  return _top;
}
void View::setTop(int top) {
  _top = top;
  _canvasContext->setOffsetY(_top);
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
