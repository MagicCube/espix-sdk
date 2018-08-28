#include "View.h"

#include "../devices/Screen.h"

#include "ViewContainer.h"

View::View() {
}

ViewContainer *View::getParentView() {
  return _parentView;
}

void View::setParentView(ViewContainer *parentView) {
  _parentView = parentView;
}

Canvas *View::getCanvas() {
  if (_canvas) {
    return _canvas;
  }
  if (getParentView()) {
    return getParentView()->getCanvas();
  }
  return NULL;
}

void View::setCanvas(Canvas *canvas) {
  _canvas = canvas;
}

int View::getWidth() {
  return _bounds.width;
}
void View::setWidth(int width) {
  _bounds.width = width;
}

int View::getHeight() {
  return _bounds.height;
}
void View::setHeight(int height) {
  _bounds.height = height;
}

int View::getLeft() {
  return _bounds.left;
}
void View::setLeft(int left) {
  _bounds.left = left;
}

int View::getTop() {
  return _bounds.top;
}
void View::setTop(int top) {
  _bounds.top = top;
}

Rectangle View::getBounds() {
  return _bounds;
}
void View::setBounds(Rectangle bounds) {
  moveTo(bounds.left, bounds.top);
  resizeTo(bounds.width, bounds.height);
}

int View::getClientLeft() {
  int result = getLeft() + getPaddings().left;
  if (getParentView()) {
    result += getParentView()->getClientLeft();
  }
  return result;
}

int View::getClientTop() {
  int result = getTop() + getPaddings().top;
  if (getParentView()) {
    result += getParentView()->getClientTop();
  }
  return result;
}

int View::getClientWidth() {
  int result = getWidth() - getPaddings().left - getPaddings().right;
  return result;
}

int View::getClientHeight() {
  int result = getHeight() - getPaddings().top - getPaddings().bottom;
  return result;
}

Rectangle View::getClientBounds() {
  return Rectangle(getClientLeft(), getClientTop(), getClientWidth(), getClientHeight());
}

Thickness View::getPaddings() {
  return _paddings;
}


void View::resizeTo(int width, int height) {
  setWidth(width);
  setHeight(height);
}

void View::moveTo(int left, int top) {
  setLeft(left);
  setTop(top);
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
  // Only the client area can be drawn, so we use client bounds here.
  auto context = new CanvasContext(getCanvas(), getClientBounds());

  if (clearBeforeRendering) {
    context->clear();
  }
  render(context);

  delete context;
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

void View::handleKeyPress(KeyEventArgs e) {
}

void View::handleScroll(ScrollEventArgs e) {
}
