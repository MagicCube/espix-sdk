#include <Arduino.h>

#include "espix.h"
#include <SH1106Wire.h>

SH1106Wire display(0x3c, D1, D2);
Application app(&display);
DrawingContext *context;

void setup() {
  Serial.begin(115200);

  app.begin();
  app.getScreen()->setOrientation(true);

  context = app.getScreen()->createDrawingContext();
  context->setTextAlign(TEXT_ALIGN_CENTER_BOTH);
  context->setFontSize(FONT_SIZE_H1);
  context->drawString("Henry");
}

void loop() {
  app.update();
  delay(500);
}
