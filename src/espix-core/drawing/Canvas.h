#pragma once

#include <Arduino.h>

#include <OLEDDisplay.h>

#include "CanvasContext.h"
#include "Font.h"
#include "enums.h"

// Represents a canvas of OLED display.
class Canvas {
public:
  // Creates a new instance of the Canvas class.
  Canvas(OLEDDisplay *display);

  // Gets the width of the canvas.
  int getWidth();

  // Gets the height of the canvas.
  int getHeight();

  // Gets a boolean value indicates whether the canvas is dirty.
  // Sets it true by invoking `setDirty()`.
  bool isDirty();

  // Sets the front color of the canvas.
  void setColor(Color color);

  // Sets the text alignment of the canvas.
  void setTextAlign(TextAlign textAlign);

  // Sets the font of the canvas.
  void setFont(Font font);

  // Updates in the loop.
  // It will draw the buffer image if the canvas is marked as dirty, then mark it as clean after
  // the canvas is updated.
  void update();

  // Draws a single pixel with the current color.
  void setPixel(int x, int y);

  // Draws a line connecting two points.
  void drawLine(int x0, int y0, int x1, int y1);

  // Draws a horizontal line specified starting point and length.
  void drawHorizontalLine(int x, int y, int length);

  // Draws a vertical line specified starting point and length.
  void drawVerticalLine(int x, int y, int length);

  // Draws a rectangle specified by given top-left point and size.
  void drawRect(int x, int y, int width, int height);

  // Fills the interior of a rectangle specified by given top-left point and size.
  void fillRect(int x, int y, int width, int height);

  // Draws a circle specified by given central point and radius.
  void drawCircle(int x, int y, int radius);

  // Draws circle quads specified by given central point, radius and quads.
  void drawCircleQuads(int x, int y, int radius, int quads);

  // Fills the interior of a circle specified by given central location and radius.
  void fillCircle(int x, int y, int radius);

  // Draws a XBM image at the specified location with specified size.
  void drawXBM(const uint8_t *xbm, int x, int y, int width, int height);

  // Gets the width of the specific text using the current font.
  int getStringWidth(String text);

  // Draws a text specified at specified location.
  void drawString(String text, int x, int y);

  // Draws multi-line text at specified location with specified line width limitation.
  void drawMultilineString(String text, int x, int y, int maxLineWidth);

  // Clears the buffer of the canvas.
  void clear();

private:
  OLEDDisplay *_display;
};
