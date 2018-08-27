#pragma once

#include <Arduino.h>
#include <OLEDDisplay.h>

#include "Rectangle.h"
#include "enums.h"

class Canvas;

class CanvasContext {
public:
  // Do NOT use this constructor directly.
  CanvasContext();

  Canvas *getCanvas();
  void setCanvas(Canvas *canvas);

  void setDirty();

  void setColor(Color color);

  // Get or set offsetX of context
  int getOffsetX();
  void setOffsetX(int offsetX);

  // Get or set offsetY of context
  int getOffsetY();
  void setOffsetY(int offsetY);

  // Get or set width of context
  int getWidth();
  void setWidth(int width);

  // Get or set height of context
  int getHeight();
  void setHeight(int height);

  Rectangle getBounds();
  void setBounds(Rectangle bounds);

  // Specifies relative to which anchor point
  // the text is rendered.
  void setTextAlign(TextAlign textAlign);

  // Change font
  void setFont(const uint8_t *fontData);

  // Sets the current font size.
  void setFontSize(FontSize size);

  // Draw a pixel at given position
  void setPixel(int x, int y);

  // Draw a line from position 0 to position 1
  void drawLine(int x0, int y0, int x1, int y1);

  // Draw the border of a rectangle at the given location
  void drawRect(int x, int y, int width, int height);

  // Draw the border of a rectangle at the given Rectangle object
  void drawRect(Rectangle rect) {
    drawRect(rect.left, rect.top, rect.width, rect.height);
  }

  // Fill the rectangle
  void fillRect(int x, int y, int width, int height);

  // Fill the rectangle
  void fillRect(Rectangle rect) {
    fillRect(rect.left, rect.top, rect.width, rect.height);
  }

  // Draw the border of a circle
  void drawCircle(int x, int y, int radius);

  // Draw all Quadrants specified in the quads bit mask
  void drawCircleQuads(int x, int y, int radius, int quads);

  // Fill circle
  void fillCircle(int x, int y, int radius);

  // Draw a line horizontally
  void drawHorizontalLine(int x, int y, int length = -1);

  // Draw a line vertically
  void drawVerticalLine(int x, int y, int length = -1);

  // Draw a XBM picture
  void drawXBM(const uint8_t *xbm, int x, int y, int width, int height);

  // Draws a string at the given position
  void drawString(String text, int x = -1, int y = -1);

  // Get width of string
  int getStringWidth(String text);

  // Draws a String with a maximum width at the given location.
  // If the given String is wider than the specified width
  // The text will be wrapped to the next line at a space or dash
  void drawMultilineString(String text, int x = -1, int y = -1, int maxLineWidth = -1);

  // Clear buffer
  void clear();

private:
  int _x(int value);
  int _y(int value);

  Rectangle _bounds;

  Color _color = Color::WHITE;
  const uint8_t *_font = ArialMT_Plain_10;
  TextAlign _textAlign = TextAlign::LEFT;

  Canvas *_canvas = NULL;
};
