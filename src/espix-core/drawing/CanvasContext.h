#pragma once

#include <Arduino.h>
#include <OLEDDisplay.h>

#include "enums.h"
#include "structs.h"

class Canvas;

// Represents the context of given canvas.
class CanvasContext {
public:
  // Creates a new instance of the CanvasContext class.
  CanvasContext(Canvas *canvas, Rectangle bounds);

  // Gets the corresponding canvas of the context.
  Canvas *getCanvas();

  // Gets or sets offsetX of the context.
  int getOffsetX();
  void setOffsetX(int offsetX);

  // Gets or sets offsetY of the context.
  int getOffsetY();
  void setOffsetY(int offsetY);

  // Gets or sets width of the context.
  int getWidth();
  void setWidth(int width);

  // Gets or sets height of the context.
  int getHeight();
  void setHeight(int height);

  // Gets or sets a `Rectangle` object which represents the bounds of the context.
  Rectangle getBounds();
  void setBounds(Rectangle bounds);

  // Sets the front color of the canvas.
  void setColor(Color color);

  // Sets the text alignment of the canvas.
  void setTextAlign(TextAlign textAlign);

  // Sets the font of the canvas.
  void setFont(const uint8_t *fontData);

  // Sets the current font size.
  void setFontSize(FontSize size);

  // Draws a single pixel with the current color.
  void setPixel(int x, int y);

  // Draws a line connecting two points.
  void drawLine(int x0, int y0, int x1, int y1);

  // Draws a horizontal line specified starting point and length.
  void drawHorizontalLine(int x, int y, int length = INT16_MIN);

  // Draws a vertical line specified starting point and length.
  void drawVerticalLine(int x, int y, int length = INT16_MIN);

  // Draws a rectangle specified by given top-left point and size.
  void drawRect(int x, int y, int width, int height);

  // Draws a rectangle specified by given `Rectangle` object.
  void drawRect(Rectangle rect) {
    drawRect(rect.left, rect.top, rect.width, rect.height);
  }

  // Fills the interior of a rectangle specified by given top-left point and size.
  void fillRect(int x, int y, int width, int height);

  // Fills the interior of a rectangle specified by given `Rectangle` object.
  void fillRect(Rectangle rect) {
    fillRect(rect.left, rect.top, rect.width, rect.height);
  }

  // Draws a circle specified by given central point and radius.
  void drawCircle(int x, int y, int radius);

  // Draws circle quads specified by given central point, radius and quads.
  void drawCircleQuads(int x, int y, int radius, int quads);

  // Fills the interior of a circle specified by given central location and radius.
  void fillCircle(int x, int y, int radius);

  // Draws a XBM image at the specified location with specified size.
  void drawXBM(const uint8_t *xbm, int x, int y, int width, int height);

  // Draws a XBM image in the given `Rectangle` location.
  void drawXBM(const uint8_t *xbm, Rectangle rect) {
    drawXBM(xbm, rect.left, rect.top, rect.width, rect.height);
  }

  // Gets the width of the specific text using the current font.
  int getStringWidth(String text);

  // Draws a text specified at specified location.
  void drawString(String text, int x = INT16_MIN, int y = INT16_MIN);

  // Draws multi-line text at specified location with specified line width limitation.
  void drawMultilineString(String text, int x = INT16_MIN, int y = INT16_MIN,
                           int maxLineWidth = INT16_MIN);

  // Clears the buffer of the canvas context.
  // It will only affect the client area of context.
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
