#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>

#include "../collections/List.h"

#include "WiFiConnectionSetting.h"
#include "WiFiConnectionState.h"

typedef std::function<void()> NetworkConnectionCallback;

class WiFiNetworkClass {
public:
  WiFiNetworkClass();

  bool isConnected();
  wl_status_t getStatus();
  String getLocalIP();


  void connect(List<WiFiConnectionSetting> settings, NetworkConnectionCallback callback = NULL);
  void connect(WiFiConnectionSetting setting, NetworkConnectionCallback callback = NULL) {
    List<WiFiConnectionSetting> settings;
    connect(settings, callback);
  }
  void connect(String ssid, String password, NetworkConnectionCallback callback = NULL) {
    WiFiConnectionSetting setting(ssid, password);
    connect(setting, callback);
  }

  void disconnect(bool wifiOff = false);
  void update();

private:
  WiFiConnectionState _connectionState = WiFiConnectionState::DISCONNECTED;
};

extern WiFiNetworkClass WiFiNetwork;
