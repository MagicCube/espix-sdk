#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include "WiFiConnectionSetting.h"

typedef std::function<void()> NetworkConnectionCallback;

class WiFiNetworkClass {
public:
  WiFiNetworkClass();

  bool isConnected();
  wl_status_t getStatus();
  String getLocalIP();


  void connect(WiFiConnectionSetting settings[], int settingsCount,
               NetworkConnectionCallback callback = NULL);
  void connect(WiFiConnectionSetting setting, NetworkConnectionCallback callback = NULL) {
    WiFiConnectionSetting settings[] = {setting};
    connect(settings, 1, callback);
  }
  void connect(String ssid, String password, NetworkConnectionCallback callback = NULL) {
    WiFiConnectionSetting setting(ssid, password);
    connect(setting, callback);
  }

  void disconnect(bool wifiOff = false);
  void update();

private:
  bool _connecting = false;
  unsigned long _lastUpdate = 0;
  ESP8266WiFiMulti _wifiMulti;
};

extern WiFiNetworkClass WiFiNetwork;
