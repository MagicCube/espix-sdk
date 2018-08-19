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
}

void loop() {
  int timeBudget = app.update();
  if (timeBudget > 0) {
    delay(timeBudget);
  }
}
