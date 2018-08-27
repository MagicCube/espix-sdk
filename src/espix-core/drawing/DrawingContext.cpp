
#include "DrawingContext.h"

#include "Canvas.h"

DrawingContext::DrawingContext(Canvas *canvas, int width, int height, int offsetX, int offsetY) {
  _canvas = canvas;
  setSize(width, height);
  setOffset(offsetX, offsetY);
}

Canvas *DrawingContext::getCanvas() {
  return _canvas;
}

int DrawingContext::getWidth() {
  return _width;
}

int DrawingContext::getHeight() {
  return _height;
}

void DrawingContext::setDirty() {
  getCanvas()->setDirty();
}

void DrawingContext::setColor(Color color) {
  getCanvas()->setColor(color);
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

void DrawingContext::setTextAlign(TextAlign align) {
  _textAlign = align;
  getCanvas()->setTextAlign(_textAlign);
}

void DrawingContext::setFont(const uint8_t *fontData) {
  getCanvas()->setFont(fontData);
}

void DrawingContext::setFontSize(FontSize size) {
  if (size == FontSize::H1) {
    getCanvas()->setFont(ArialMT_Plain_24);
  } else if (size == FontSize::H2) {
    getCanvas()->setFont(ArialMT_Plain_16);
  } else {
    getCanvas()->setFont(ArialMT_Plain_10);
  }
}

void DrawingContext::setPixel(int x, int y) {
  getCanvas()->setPixel(_x(x), _y(y));
}

void DrawingContext::drawLine(int x0, int y0, int x1, int y1) {
  getCanvas()->drawLine(_x(x0), _y(y0), _x(x1), _y(y1));
}

void DrawingContext::drawRect(int x, int y, int width, int height) {
  getCanvas()->drawRect(_x(x), _y(y), width, height);
}

void DrawingContext::fillRect(int x, int y, int width, int height) {
  getCanvas()->fillRect(_x(x), _y(y), width, height);
}

void DrawingContext::drawCircle(int x, int y, int radius) {
  getCanvas()->drawCircle(_x(x), _y(y), radius);
}

void DrawingContext::drawCircleQuads(int x, int y, int radius, int quads) {
  getCanvas()->drawCircleQuads(_x(x), _y(y), radius, quads);
}

void DrawingContext::fillCircle(int x, int y, int radius) {
  getCanvas()->fillCircle(_x(x), _y(y), radius);
}

void DrawingContext::drawHorizontalLine(int x, int y, int length) {
  if (length == -1) {
    length = getWidth();
  }
  getCanvas()->drawHorizontalLine(_x(x), _y(y), length);
}

void DrawingContext::drawVerticalLine(int x, int y, int length) {
  if (length == -1) {
    length = getHeight();
  }
  getCanvas()->drawVerticalLine(_x(x), _y(y), length);
}

void DrawingContext::drawXBM(const uint8_t *xbm, int width, int height, int x, int y) {
  getCanvas()->drawXBM(xbm, width, height, _x(x), _y(y));
}

void DrawingContext::drawString(String text, int x, int y) {
  if (x == -1) {
    if (_textAlign == TextAlign::LEFT) {
      x = 0;
    } else if (_textAlign == TextAlign::RIGHT) {
      x = getWidth();
      y = 0;
    } else if (_textAlign == TextAlign::CENTER || _textAlign == TextAlign::CENTER_BOTH) {
      x = getWidth() / 2;
    }
  }
  if (y == -1) {
    if (_textAlign == TextAlign::CENTER_BOTH) {
      y = getHeight() / 2;
    } else {
      y = 0;
    }
  }
  getCanvas()->drawString(text, _x(x), _y(y));
}

void DrawingContext::drawMultilineString(String text, int x, int y, int maxLineWidth) {
  if (x == -1) {
    if (_textAlign == TextAlign::LEFT) {
      x = 0;
    } else if (_textAlign == TextAlign::RIGHT) {
      x = getWidth();
      y = 0;
    } else if (_textAlign == TextAlign::CENTER || _textAlign == TextAlign::CENTER_BOTH) {
      x = getWidth() / 2;
    }
  }
  if (y == -1) {
    if (_textAlign == TextAlign::CENTER_BOTH) {
      y = getHeight() / 2;
    } else {
      y = 0;
    }
  }
  if (maxLineWidth == -1) {
    maxLineWidth = getWidth();
  }
  getCanvas()->drawMultilineString(text, _x(x), _y(y), maxLineWidth);
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
