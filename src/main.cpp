#include <Arduino.h>

#include <ESP8266HTTPClient.h>
#include <SH1106Wire.h>

#include "espix-core.h"
#include "espix-design.h"

#include "examples/config.h"

#include "examples/root/views/RootView.h"
#include "examples/services/ServiceClient.h"

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
  WiFiNetwork.addToPreferredList(WIFI_DEFAULT_SSID, WIFI_DEFAULT_PWD);
  WiFiNetwork.addToPreferredList(WIFI_2_SSID, WIFI_2_PWD);
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
  #ifndef DEBUG_LOCAL
    connect();
  #else
    Application.setStatusView(&statusBar);
    Application.setRootView(&rootView);
  #endif
}

void loop() {
  ServiceClient.update();
  int timeBudget = Application.update();
  if (timeBudget > 0) {
    delay(timeBudget);
  }
}
