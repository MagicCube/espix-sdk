#include <Arduino.h>

#include <SH1106Wire.h>

#include "espix-core.h"
#include "espix-design.h"

unsigned long lastUpdate = 0;
unsigned long lastViewChange = 0;

SH1106Wire *display = new SH1106Wire(0x3c, D1, D2);
Application *app = new Application(display);

bool connecting = false;

ProgressView *progressView = new ProgressView("Connecting to WiFi...", PROGRESS_INFINITY);
TextView *textView = new TextView(FONT_SIZE_H2);

void setup() {
  Serial.begin(115200);
  Serial.println();

  app->begin();
  // Settings
  app->getScreen()->setBrightness(100);
  app->getScreen()->setOrientation(false);
  connecting = true;
  app->connectToWiFi(WiFiConnectionSetting("Henry's Living Room 2.4GHz", "13913954971"));
  app->setRootView(progressView);
}

void loop() {
  int timeBudget = app->update();
  if (timeBudget > 0) {
    delay(timeBudget);
    if (connecting && app->isWiFiConnected()) {
      connecting = false;
      textView->setText(app->getWiFiLocalIP());
      app->setRootView(textView, TransitionOptions(TRANSITION_TO_LEFT));
    }
  }
}
