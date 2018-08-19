#include <Arduino.h>

#include "espix.h"
#include <SH1106Wire.h>

SH1106Wire display(0x3c, D1, D2);
Application app(&display);
DrawingContext *context;

void setup() {
  app.begin();
  app.getScreen()->setOrientation(true);
  context = app.getScreen()->createDrawingContext();
}

void loop() {
  context->setOffset(20, 0);
  context->setFontSize(FONT_SIZE_H1);
  context->drawString("Henry");
  context->redraw();
  delay(500);
}
