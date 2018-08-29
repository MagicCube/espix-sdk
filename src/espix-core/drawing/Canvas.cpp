#include "Canvas.h"

Canvas::Canvas(OLEDDisplay *display) {
  _display = display;
}

int Canvas::getWidth() {
  return _display->getWidth();
}

int Canvas::getHeight() {
  return _display->getHeight();
}

bool Canvas::isDirty() {
  return _dirty;
}

void Canvas::setDirty() {
  _dirty = true;
}

void Canvas::setColor(Color color) {
  OLEDDISPLAY_COLOR oColor;
  switch (color) {
  case Color::BLACK:
    oColor = BLACK;
    break;
  case Color::WHITE:
    oColor = WHITE;
    break;
  case Color::INVERSE:
    oColor = WHITE;
    break;
  default:
    oColor = WHITE;
    break;
  }
  _display->setColor(oColor);
}

void Canvas::setTextAlign(TextAlign textAlign) {
  _display->setTextAlignment((OLEDDISPLAY_TEXT_ALIGNMENT)textAlign);
}

void Canvas::setFont(const uint8_t *fontData) {
  _display->setFont(fontData);
}

void Canvas::update() {
  if (isDirty()) {
    _display->display();
    _dirty = false;
  }
}

void Canvas::setPixel(int x, int y) {
  _display->setPixel(x, y);
  setDirty();
}

void Canvas::drawLine(int x0, int y0, int x1, int y1) {
  _display->drawLine(x0, y0, x1, y1);
  setDirty();
}

void Canvas::drawHorizontalLine(int x, int y, int length) {
  _display->drawHorizontalLine(x, y, length);
  setDirty();
}

void Canvas::drawVerticalLine(int x, int y, int length) {
  _display->drawVerticalLine(x, y, length);
  setDirty();
}

void Canvas::drawRect(int x, int y, int width, int height) {
  _display->drawRect(x, y, width, height);
  setDirty();
}

void Canvas::fillRect(int x, int y, int width, int height) {
  _display->fillRect(x, y, width, height);
  setDirty();
}

void Canvas::drawCircle(int x, int y, int radius) {
  _display->drawCircle(x, y, radius);
  setDirty();
}

void Canvas::drawCircleQuads(int x, int y, int radius, int quads) {
  _display->drawCircleQuads(x, y, radius, quads);
  setDirty();
}

void Canvas::fillCircle(int x, int y, int radius) {
  _display->fillCircle(x, y, radius);
  setDirty();
}

void Canvas::drawXBM(const uint8_t *xbm, int x, int y, int width, int height) {
  _display->drawXbm(x, y, width, height, xbm);
  setDirty();
}

int Canvas::getStringWidth(String text) {
  return _display->getStringWidth(text);
}

void Canvas::drawString(String text, int x, int y) {
  _display->drawString(x, y, text);
  setDirty();
}

void Canvas::drawMultilineString(String text, int x, int y, int maxLineWidth) {
  _display->drawStringMaxWidth(x, y, maxLineWidth, text);
  setDirty();
}

void Canvas::clear() {
  _display->clear();
  setDirty();
}
