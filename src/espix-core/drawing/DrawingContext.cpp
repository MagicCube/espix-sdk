
#include "DrawingContext.h"

#include "../devices/Screen.h"

DrawingContext::DrawingContext(Screen *screen, int width, int height, int offsetX, int offsetY) {
  _screen = screen;
  _display = screen->getDisplay();
  setSize(width, height);
  setOffset(offsetX, offsetY);
}

void DrawingContext::setColor(OLEDDISPLAY_COLOR color) {
  _display->setColor(color);
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
  if (_display == NULL)
    return;
  _textAlign = align;
  _display->setTextAlignment(align);
}

void DrawingContext::setFont(const uint8_t *fontData) {
  _display->setFont(fontData);
}

void DrawingContext::setFontSize(FONT_SIZE size) {
  if (_display == NULL)
    return;
  if (size == FONT_SIZE_H1) {
    _display->setFont(ArialMT_Plain_24);
  } else if (size == FONT_SIZE_H2) {
    _display->setFont(ArialMT_Plain_16);
  } else {
    _display->setFont(ArialMT_Plain_10);
  }
}

void DrawingContext::drawPixel(int x, int y) {
  if (_display == NULL)
    return;
  _display->setPixel(_x(x), _y(y));
  _screen->setDirty();
}

void DrawingContext::drawLine(int x0, int y0, int x1, int y1) {
  if (_display == NULL)
    return;
  _display->drawLine(_x(x0), _y(y0), _x(x1), _y(y1));
  _screen->setDirty();
}

void DrawingContext::drawRect(int x, int y, int width, int height) {
  if (_display == NULL)
    return;
  _display->drawRect(_x(x), _y(y), width, height);
  _screen->setDirty();
}

void DrawingContext::fillRect(int x, int y, int width, int height) {
  if (_display == NULL)
    return;
  _display->fillRect(_x(x), _y(y), width, height);
  _screen->setDirty();
}

void DrawingContext::drawCircle(int x, int y, int radius) {
  if (_display == NULL)
    return;
  _display->drawCircle(_x(x), _y(y), radius);
  _screen->setDirty();
}

void DrawingContext::drawCircleQuads(int x, int y, int radius, int quads) {
  if (_display == NULL)
    return;
  _display->drawCircleQuads(_x(x), _y(y), radius, quads);
  _screen->setDirty();
}

void DrawingContext::fillCircle(int x, int y, int radius) {
  if (_display == NULL)
    return;
  _display->fillCircle(_x(x), _y(y), radius);
  _screen->setDirty();
}

void DrawingContext::drawHorizontalLine(int x, int y, int length) {
  if (_display == NULL)
    return;
  if (length == -1) {
    length = getWidth();
  }
  _display->drawHorizontalLine(_x(x), _y(y), length);
  _screen->setDirty();
}

void DrawingContext::drawVerticalLine(int x, int y, int length) {
  if (_display == NULL)
    return;
  if (length == -1) {
    length = getHeight();
  }
  _display->drawVerticalLine(_x(x), _y(y), length);
  _screen->setDirty();
}

void DrawingContext::drawXBM(const uint8_t *xbm, int width, int height, int x, int y) {
  if (_display == NULL)
    return;
  _display->drawXbm(_x(x), _y(y), width, height, xbm);
  _screen->setDirty();
}

void DrawingContext::drawString(String text, int x, int y) {
  if (_display == NULL)
    return;
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
  _display->drawString(_x(x), _y(y), text);
  _screen->setDirty();
}

void DrawingContext::drawMultilineString(String text, int x, int y, int maxLineWidth) {
  if (_display == NULL)
    return;
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
  _display->drawStringMaxWidth(_x(x), _y(y), maxLineWidth, text);
  _screen->setDirty();
}

int DrawingContext::getStringWidth(String text) {
  return _display->getStringWidth(text);
}

void DrawingContext::clear() {
  return _display->clear();
}

int DrawingContext::_x(int value) {
  return _offsetX + value;
}

int DrawingContext::_y(int value) {
  return _offsetY + value;
}
