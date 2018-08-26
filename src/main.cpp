#include <Arduino.h>

#include <SH1106Wire.h>

#include "espix-core.h"
#include "espix-design.h"

unsigned long lastUpdate = 0;
unsigned long lastViewChange = 0;

SH1106Wire *display = new SH1106Wire(0x3c, D1, D2);
Application *app = new Application(display);

TextView *textView = new TextView("Hello.", FONT_SIZE_H2);

void onConnected() {
  app->enableOTA();
  app->setRootView(textView, TransitionOptions(TRANSITION_TO_LEFT));
  textView->setText(WiFiNetwork.getLocalIP());
}

void connect() {
  WiFiConnectionSetting settings[] = {
      WiFiConnectionSetting("Henry's iPhone 6", "13913954971"),
      WiFiConnectionSetting("Henry's Living Room 2.4GHz", "13913954971")};
  WiFiNetwork.connect(settings, 2, true, onConnected);
}

void setupDevices() {
  Keyboard.begin();
}

void setupApp() {
  app->begin();
  // Settings
  app->getScreen()->setBrightness(100);
  app->getScreen()->setOrientation(true);
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  setupDevices();
  setupApp();
  connect();
}

void loop() {
  int timeBudget = app->update();
  if (timeBudget > 0) {
    delay(timeBudget);
  }
}
