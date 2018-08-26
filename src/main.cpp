#include <Arduino.h>

#include <SH1106Wire.h>

#include "espix-core.h"
#include "espix-design.h"

#define OLED_SDA D1
#define OLED_CLK D2

unsigned long lastUpdate = 0;
unsigned long lastViewChange = 0;

SH1106Wire display(0x3c, OLED_SDA, OLED_CLK);
Application application(&display);
TextView textView("Hello.", FONT_SIZE_H2);

void onConnected() {
  application.enableOTA();
  application.setRootView(&textView, TransitionOptions(TRANSITION_TO_LEFT));
  textView.setText(WiFiNetwork.getLocalIP());
}

void connect() {
  WiFiConnectionSetting settings[] = {
      WiFiConnectionSetting("Henry's iPhone 6", "13913954971"),
      WiFiConnectionSetting("Henry's Living Room 2.4GHz", "13913954971")};
  WiFiNetwork.connect(settings, 2, true, onConnected);
}

void setupDevices() {
  Screen::getInstance()->begin(&display);
  Screen::getInstance()->setBrightness(100);
  Screen::getInstance()->setOrientation(true);
  Keyboard.begin();
}

void setupApp() {
  application.begin();
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  setupDevices();
  setupApp();
  connect();
}

void loop() {
  int timeBudget = application.update();
  if (timeBudget > 0) {
    delay(timeBudget);
  }
}
