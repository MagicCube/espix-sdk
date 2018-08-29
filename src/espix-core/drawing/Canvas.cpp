#include "Canvas.h"

Canvas::Canvas(OLEDDisplay *display) {
  _display = display;
  setColor(Color::WHITE);
  setFont(ArialMT_Plain_10);
  setTextAlign(TextAlign::LEFT);
}

int Canvas::getWidth() {
  return _display->getWidth();
}

int Canvas::getHeight() {
  return _display->getHeight();
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
  _display->display();
}

void Canvas::setPixel(int x, int y) {
  _display->setPixel(x, y);
}

void Canvas::drawLine(int x0, int y0, int x1, int y1) {
  _display->drawLine(x0, y0, x1, y1);
}

void Canvas::drawHorizontalLine(int x, int y, int length) {
  _display->drawHorizontalLine(x, y, length);
}

void Canvas::drawVerticalLine(int x, int y, int length) {
  _display->drawVerticalLine(x, y, length);
}

void Canvas::drawRect(int x, int y, int width, int height) {
  _display->drawRect(x, y, width, height);
}

void Canvas::fillRect(int x, int y, int width, int height) {
  _display->fillRect(x, y, width, height);
}

void Canvas::drawCircle(int x, int y, int radius) {
  _display->drawCircle(x, y, radius);
}

void Canvas::drawCircleQuads(int x, int y, int radius, int quads) {
  _display->drawCircleQuads(x, y, radius, quads);
}

void Canvas::fillCircle(int x, int y, int radius) {
  _display->fillCircle(x, y, radius);
}

void Canvas::drawXBM(const uint8_t *xbm, int x, int y, int width, int height) {
  _display->drawXbm(x, y, width, height, xbm);
}

int Canvas::getStringWidth(String text) {
  return _display->getStringWidth(text);
}

void Canvas::drawString(String text, int x, int y) {
  _display->drawString(x, y, text);
}

void Canvas::drawMultilineString(String text, int x, int y, int maxLineWidth) {
  _display->drawStringMaxWidth(x, y, maxLineWidth, text);
}

void Canvas::clear() {
  _display->clear();
}
