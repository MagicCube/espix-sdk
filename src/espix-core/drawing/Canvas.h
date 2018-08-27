#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "CanvasContext.h"
#include "enums.h"

class Canvas {
public:
  Canvas(OLEDDisplay *display);

  int getWidth();

  int getHeight();

  int getStringWidth(String text);

  bool isDirty();

  void setDirty();

  void setColor(Color color);

  void setTextAlign(TextAlign textAlign);

  void setFont(const uint8_t *fontData);

  void update();

  void setPixel(int x, int y);

  void drawLine(int x0, int y0, int x1, int y1);

  void drawRect(int x, int y, int width, int height);

  void fillRect(int x, int y, int width, int height);

  void drawCircle(int x, int y, int radius);

  void drawCircleQuads(int x, int y, int radius, int quads);

  void fillCircle(int x, int y, int radius);

  void drawHorizontalLine(int x, int y, int length);

  void drawVerticalLine(int x, int y, int length);

  void drawXBM(const uint8_t *xbm, int x, int y, int width, int height);

  void drawString(String text, int x, int y);

  void drawMultilineString(String text, int x, int y, int maxLineWidth);

  void clear();

private:
  OLEDDisplay *_display;
  bool _dirty;
};
