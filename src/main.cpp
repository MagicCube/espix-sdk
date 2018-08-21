#include <Arduino.h>

#include "espix-core.h"
#include "espix-design.h"

bool connecting = false;
unsigned long lastUpdate = 0;
unsigned long lastViewChange = 0;

SH1106Wire *display = new SH1106Wire(0x3c, D1, D2);
Application *app = new Application(display);

ProgressView *progressView = new ProgressView("Connecting to WiFi...", PROGRESS_INFINITY);
TextView *textView = new TextView("Connecting...", FONT_SIZE_H2);

void setup() {
  Serial.begin(115200);
  Serial.println();

  app->begin();
  // Settings
  app->getScreen()->setBrightness(100);
  app->getScreen()->setOrientation(false);
  connecting = true;
  // app->getNetwork()->connect("Henry's Living Room 2.4GHz", "13913954971");
  app->getNetwork()->connect("Henry's iPhone 6", "13913954971", [=]() {
    textView->setText(app->getNetwork()->getLocalIP());
    app->setRootView(textView, TransitionOptions(TRANSITION_TO_LEFT));
  });
  app->setRootView(progressView);
}

void loop() {
  int timeBudget = app->update();
  if (timeBudget > 0) {
    delay(timeBudget);
  }
}
