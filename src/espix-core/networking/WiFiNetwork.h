#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include "../../espix-design/views/ProgressView.h"
#include "WiFiConnectionSetting.h"

typedef std::function<void()> NetworkConnectionCallback;

class WiFiNetwork {
public:
  WiFiNetwork();

  bool isConnected();
  wl_status_t getStatus();
  String getLocalIP();


  void connect(WiFiConnectionSetting settings[], int settingsCount, bool showProgress = false,
               NetworkConnectionCallback callback = NULL);
  void connect(WiFiConnectionSetting setting, bool showProgress = false,
               NetworkConnectionCallback callback = NULL) {
    WiFiConnectionSetting settings[] = {setting};
    connect(settings, 1, showProgress, callback);
  }
  void connect(String ssid, String password, bool showProgress = false,
               NetworkConnectionCallback callback = NULL) {
    WiFiConnectionSetting setting(ssid, password);
    connect(setting, showProgress, callback);
  }

  void disconnect(bool wifiOff = false);
  void update();

private:
  bool _connecting = false;
  unsigned long _lastUpdate = 0;
  ESP8266WiFiMulti _wifiMulti;
  ProgressView *_getProgressView();
  ProgressView *_progressView;
};
