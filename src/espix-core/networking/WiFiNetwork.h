#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>

#include "WiFiConnectionSetting.h"

class WiFiNetwork {
public:
  WiFiNetwork();

  bool isConnected();
  wl_status_t getStatus();
  String getLocalIP();

  void connect(WiFiConnectionSetting setting);
  void connect(String ssid, String password) {
    WiFiConnectionSetting setting(ssid, password);
    connect(setting);
  }

private:
};
