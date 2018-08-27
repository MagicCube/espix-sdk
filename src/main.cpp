#include <Arduino.h>

#include <SH1106Wire.h>

#include "espix-core.h"
#include "espix-design.h"

#define OLED_SDA D1
#define OLED_CLK D2
#define KY04_CLK D5
#define KY04_DT D6
#define KY04_SW D7

unsigned long lastUpdate = 0;
unsigned long lastViewChange = 0;

SH1106Wire display(0x3c, OLED_SDA, OLED_CLK);
Application application;
ProgressView connectionView("Connecting to WiFi...", ProgressMode::INDETERMINATE);
TextView textView("Hello.", FontSize::H2);

void onConnected() {
  application.enableOTA();
  application.setRootView(&textView, TransitionOptions(TransitionDirection::LEFT));
  textView.setText(WiFiNetwork.getLocalIP());
}

void connect() {
  application.setRootView(&connectionView);
  WiFiConnectionSetting settings[] = {
      WiFiConnectionSetting("Henry's iPhone 6", "13913954971"),
      WiFiConnectionSetting("Henry's Living Room 2.4GHz", "13913954971")};
  WiFiNetwork.connect(settings, 2, onConnected);
}

void setupDevices() {
  Screen.begin(&display);
  // Screen.setBrightness(100);
  Screen.setOrientation(true);

  Keyboard.registerJogDial(KY04_CLK, KY04_DT, KY04_SW);
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

bool firstTime = true;
void loop() {
  int timeBudget = application.update();
  if (timeBudget > 0) {
    delay(timeBudget);
  }
}
