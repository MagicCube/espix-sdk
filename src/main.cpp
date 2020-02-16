#include <Arduino.h>

#include <EEPROM.h>
#include <ESP8266HTTPClient.h>

#include <EasyBuzzer.h>
#include <SH1106Wire.h>

#include <espix-core.h>
#include <espix-design.h>

#include "examples/config.h"
#include "examples/settings/Settings.h"

#include "examples/alarm/Alarm.h"
#include "examples/root/views/RootView.h"
#include "examples/services/ServiceClient.h"

bool connecting = false;

SH1106Wire display(0x3c, OLED_SDA_PIN, OLED_CLK_PIN);

StatusBar statusBar;
RootView rootView;
ProgressView connectionView("Connecting to WiFi...", ProgressMode::INDETERMINATE);

void onConnected() {
  connecting = false;
  Application.enableOTA();
  Application.setStatusBar(&statusBar);
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
  pinMode(LED_PIN, OUTPUT);

  Screen.begin(&display);
  Screen.setOrientation(true);
  Screen.setBrightness(100);

  Keyboard.registerJogDial(KY04_CLK_PIN, KY04_DT_PIN, KY04_SW_PIN);
  Keyboard.registerKey(KEY_ESC, ESC_BUTTON_PIN);
  Keyboard.begin();

  EasyBuzzer.setPin(BUZZER_PIN);
}

void handleKeyPress(KeyEventArgs *e) {
  if (e->keyCode == KEY_ESC) {
    if (Alarm.isBeeping()) {
      e->preventDefault();
      Alarm.stopBeep();
    }
  }
}

void setupApp() {
  Alarm.begin();
  Settings.begin();
  Application.begin();
  Application.onKeyPress(handleKeyPress);
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  setupDevices();
  setupApp();
#ifndef DEBUG_LOCAL
  connect();
#else
  Application.setStatusBar(&statusBar);
  Application.setRootView(&rootView);
#endif
}

void loop() {
  Alarm.update();
  EasyBuzzer.update();
  ServiceClient.update();
  int timeBudget = Application.update();
  if (timeBudget > 0) {
    delay(timeBudget);
  }
}
