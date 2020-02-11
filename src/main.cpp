#include <Arduino.h>

#include <ESP8266HTTPClient.h>
#include <SH1106Wire.h>

#include "espix-core.h"
#include "espix-design.h"

#include "examples/root/views/RootView.h"
#include "examples/services/ServiceClient.h"

#define OLED_SDA D1
#define OLED_CLK D2
#define KY04_CLK D5
#define KY04_DT D6
#define KY04_SW D7
#define ESC_BUTTON D3

bool connecting = false;

SH1106Wire display(0x3c, OLED_SDA, OLED_CLK);

StatusBar statusBar;
RootView rootView;
ProgressView connectionView("Connecting to WiFi...", ProgressMode::INDETERMINATE);

void onConnected() {
  connecting = false;
  Application.enableOTA();
  Application.setStatusView(&statusBar);
  Application.setRootView(&rootView, TRANSITION_OPTIONS_DOWN);
  ServiceClient.begin();
}

void connect() {
  Application.setRootView(&connectionView);
  WiFiNetwork.addToPreferredList("Henry's iPhone 6", "13913954971");
  WiFiNetwork.addToPreferredList("Henry's Living Room 2.4GHz", "13913954971");
  WiFiNetwork.connect(onConnected);
  connecting = true;
}

void setupDevices() {
  Screen.begin(&display);
  Screen.setOrientation(true);
  Screen.setBrightness(100);

  Keyboard.registerJogDial(KY04_CLK, KY04_DT, KY04_SW);
  Keyboard.registerKey(KEY_ESC, ESC_BUTTON);
  Keyboard.begin();
}

void setupApp() {
  Application.begin();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  setupDevices();
  setupApp();
  connect();
}

void loop() {
  ServiceClient.update();
  int timeBudget = Application.update();
  if (timeBudget > 0) {
    delay(timeBudget);
  }
}
