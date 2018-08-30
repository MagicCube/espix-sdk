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
  if (_bounds.width != width) {
    _bounds.width = width;
    setDirty();
  }
}

int View::getHeight() {
  return _bounds.height;
}
void View::setHeight(int height) {
  if (_bounds.height != height) {
    _bounds.height = height;
    setDirty();
  }
}

void View::resizeTo(int width, int height) {
  setWidth(width);
  setHeight(height);
}

int View::getLeft() {
  return _bounds.left;
}
void View::setLeft(int left) {
  if (_bounds.left != left) {
    _bounds.left = left;
    setDirty();
  }
}

int View::getTop() {
  return _bounds.top;
}
void View::setTop(int top) {
  if (_bounds.top != top) {
    _bounds.top = top;
    setDirty();
  }
}

void View::moveTo(int left, int top) {
  setLeft(left);
  setTop(top);
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
void View::setPaddings(Thickness paddings) {
  _paddings.left = paddings.left;
  _paddings.top = paddings.top;
  _paddings.right = paddings.right;
  _paddings.bottom = paddings.bottom;
  setDirty();
}

void View::setPaddings(int all) {
  _paddings.left = all;
  _paddings.top = all;
  _paddings.right = all;
  _paddings.bottom = all;
  setDirty();
}

void View::setPaddings(int horizontal, int vertical) {
  _paddings.left = horizontal;
  _paddings.right = horizontal;
  _paddings.top = vertical;
  _paddings.bottom = vertical;
  setDirty();
}

void View::setPaddings(int left, int top, int right, int bottom) {
  _paddings.left = left;
  _paddings.top = top;
  _paddings.right = right;
  _paddings.bottom = bottom;
  setDirty();
}

int View::getPaddingLeft() {
  return _paddings.left;
}

int View::getPaddingRight() {
  return _paddings.right;
}

int View::getPaddingTop() {
  return _paddings.top;
}

int View::getPaddingBottom() {
  return _paddings.bottom;
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

void View::redraw() {
  Canvas *canvas = getCanvas();
  if (canvas == NULL) {
    // Not ready to redraw.
    return;
  }
  // Only the client area can be drawn, so we use client bounds here.
  auto context = new CanvasContext(getCanvas(), getClientBounds());
  render(context);
  delete context;
}

void View::select() {
  didSelect();
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

void View::didSelect() {
}

void View::willUnmount() {
}

void View::handleKeyPress(KeyEventArgs e) {
}

void View::handleScroll(ScrollEventArgs e) {
}
