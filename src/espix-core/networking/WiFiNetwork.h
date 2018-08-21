#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>

#include "../../espix-design/views/ProgressView.h"
#include "WiFiConnectionSetting.h"

typedef std::function<void()> NetworkConnectionCallback;

class WiFiNetwork {
public:
  WiFiNetwork();

  bool isConnected();
  wl_status_t getStatus();
  String getLocalIP();

  void connect(WiFiConnectionSetting setting, bool showProgress,
               NetworkConnectionCallback callback = NULL);
  void connect(String ssid, String password, bool showProgress,
               NetworkConnectionCallback callback = NULL) {
    WiFiConnectionSetting setting(ssid, password);
    connect(setting, showProgress, callback);
  }
  void disconnect(bool wifiOff = false);

private:
  ProgressView *_getProgressView();

  ProgressView *_progressView;
};
