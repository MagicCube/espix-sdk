
#include "DrawingContext.h"

#include "../devices/Screen.h"

DrawingContext::DrawingContext(int width, int height, int offsetX, int offsetY) {
  setSize(width, height);
  setOffset(offsetX, offsetY);
}

OLEDDisplay *DrawingContext::getCanvas() {
  return Screen.getDisplay();
}

void DrawingContext::setDirty() {
  Screen.setDirty();
}

void DrawingContext::setColor(OLEDDISPLAY_COLOR color) {
  getCanvas()->setColor(color);
}

int DrawingContext::getWidth() {
  return _width;
}

int DrawingContext::getHeight() {
  return _height;
}

void DrawingContext::setSize(int width, int height) {
  _width = width;
  _height = height;
}

int DrawingContext::getOffsetX() {
  return _offsetX;
}

int DrawingContext::getOffsetY() {
  return _offsetY;
}

void DrawingContext::setOffset(int x, int y) {
  _offsetX = x;
  _offsetY = y;
}

void DrawingContext::setTextAlign(TEXT_ALIGN align) {
  _textAlign = align;
  getCanvas()->setTextAlignment(align);
}

void DrawingContext::setFont(const uint8_t *fontData) {
  getCanvas()->setFont(fontData);
}

void DrawingContext::setFontSize(FONT_SIZE size) {
  if (size == FONT_SIZE_H1) {
    getCanvas()->setFont(ArialMT_Plain_24);
  } else if (size == FONT_SIZE_H2) {
    getCanvas()->setFont(ArialMT_Plain_16);
  } else {
    getCanvas()->setFont(ArialMT_Plain_10);
  }
}

void DrawingContext::drawPixel(int x, int y) {
  getCanvas()->setPixel(_x(x), _y(y));
  setDirty();
}

void DrawingContext::drawLine(int x0, int y0, int x1, int y1) {
  getCanvas()->drawLine(_x(x0), _y(y0), _x(x1), _y(y1));
  setDirty();
}

void DrawingContext::drawRect(int x, int y, int width, int height) {
  getCanvas()->drawRect(_x(x), _y(y), width, height);
  setDirty();
}

void DrawingContext::fillRect(int x, int y, int width, int height) {
  getCanvas()->fillRect(_x(x), _y(y), width, height);
  setDirty();
}

void DrawingContext::drawCircle(int x, int y, int radius) {
  getCanvas()->drawCircle(_x(x), _y(y), radius);
  setDirty();
}

void DrawingContext::drawCircleQuads(int x, int y, int radius, int quads) {
  getCanvas()->drawCircleQuads(_x(x), _y(y), radius, quads);
  setDirty();
}

void DrawingContext::fillCircle(int x, int y, int radius) {
  getCanvas()->fillCircle(_x(x), _y(y), radius);
  setDirty();
}

void DrawingContext::drawHorizontalLine(int x, int y, int length) {
  if (length == -1) {
    length = getWidth();
  }
  getCanvas()->drawHorizontalLine(_x(x), _y(y), length);
  setDirty();
}

void DrawingContext::drawVerticalLine(int x, int y, int length) {
  if (length == -1) {
    length = getHeight();
  }
  getCanvas()->drawVerticalLine(_x(x), _y(y), length);
  setDirty();
}

void DrawingContext::drawXBM(const uint8_t *xbm, int width, int height, int x, int y) {
  getCanvas()->drawXbm(_x(x), _y(y), width, height, xbm);
  setDirty();
}

void DrawingContext::drawString(String text, int x, int y) {
  if (x == -1) {
    if (_textAlign == TEXT_ALIGN_LEFT) {
      x = 0;
    } else if (_textAlign == TEXT_ALIGN_RIGHT) {
      x = getWidth();
      y = 0;
    } else if (_textAlign == TEXT_ALIGN_CENTER || _textAlign == TEXT_ALIGN_CENTER_BOTH) {
      x = getWidth() / 2;
    }
  }
  if (y == -1) {
    if (_textAlign == TEXT_ALIGN_CENTER_BOTH) {
      y = getHeight() / 2;
    } else {
      y = 0;
    }
  }
  getCanvas()->drawString(_x(x), _y(y), text);
  setDirty();
}

void DrawingContext::drawMultilineString(String text, int x, int y, int maxLineWidth) {
  if (x == -1) {
    if (_textAlign == TEXT_ALIGN_LEFT) {
      x = 0;
    } else if (_textAlign == TEXT_ALIGN_RIGHT) {
      x = getWidth();
      y = 0;
    } else if (_textAlign == TEXT_ALIGN_CENTER || _textAlign == TEXT_ALIGN_CENTER_BOTH) {
      x = getWidth() / 2;
    }
  }
  if (y == -1) {
    if (_textAlign == TEXT_ALIGN_CENTER_BOTH) {
      y = getHeight() / 2;
    } else {
      y = 0;
    }
  }
  if (maxLineWidth == -1) {
    maxLineWidth = getWidth();
  }
  getCanvas()->drawStringMaxWidth(_x(x), _y(y), maxLineWidth, text);
  setDirty();
}

int DrawingContext::getStringWidth(String text) {
  return getCanvas()->getStringWidth(text);
}

void DrawingContext::clear() {
  return getCanvas()->clear();
}

int DrawingContext::_x(int value) {
  return _offsetX + value;
}

int DrawingContext::_y(int value) {
  return _offsetY + value;
}
