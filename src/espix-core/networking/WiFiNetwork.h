#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>

#include "WiFiConnectionSetting.h"

typedef std::function<void()> NetworkConnectionCallback;

class WiFiNetwork {
public:
  WiFiNetwork();

  bool isConnected();
  wl_status_t getStatus();
  String getLocalIP();

  void connect(WiFiConnectionSetting setting, NetworkConnectionCallback callback = NULL);
  void connect(String ssid, String password, NetworkConnectionCallback callback = NULL) {
    WiFiConnectionSetting setting(ssid, password);
    connect(setting, callback);
  }
  void disconnect(bool wifiOff = false);

private:
};
