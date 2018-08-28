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

  void addToPreferredList(WiFiConnectionSetting setting);
  void addToPreferredList(String ssid, String password) {
    WiFiConnectionSetting setting(ssid, password);
    addToPreferredList(setting);
  }

  void connect(NetworkConnectionCallback callback = NULL);
  void connect(String ssid, String password, NetworkConnectionCallback callback = NULL) {
    addToPreferredList(ssid, password);
    connect(callback);
  }

  void disconnect(bool wifiOff = false);

private:
  void _scan();

  WiFiConnectionState _connectionState = WiFiConnectionState::DISCONNECTED;
  List<WiFiConnectionSetting> _preferredList;
};

extern WiFiNetworkClass WiFiNetwork;
