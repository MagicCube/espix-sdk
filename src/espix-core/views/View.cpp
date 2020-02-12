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
  resizeTo(width, getHeight());
}

int View::getHeight() {
  return _bounds.height;
}
void View::setHeight(int height) {
  resizeTo(getWidth(), height);
}

void View::resizeTo(int width, int height) {
  setBounds(Rectangle(getLeft(), getTop(), width, height));
}

int View::getLeft() {
  return _bounds.left;
}
void View::setLeft(int left) {
  moveTo(left, getTop());
}

int View::getTop() {
  return _bounds.top;
}
void View::setTop(int top) {
  moveTo(getLeft(), top);
}

void View::moveTo(int left, int top) {
  setBounds(Rectangle(left, top, getWidth(), getHeight()));
}

Rectangle View::getBounds() {
  return _bounds;
}
void View::setBounds(Rectangle bounds) {
  _bounds.copyFrom(bounds);
  setDirty();
}

int View::getClientLeft() {
  int result = getLeft();
  if (getParentView()) {
    result += getParentView()->getClientLeft();
  }
  return result;
}

int View::getClientTop() {
  int result = getTop();
  if (getParentView()) {
    result += getParentView()->getClientTop() + getParentView()->getPaddingTop();
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
  _paddings.copyFrom(paddings);
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
