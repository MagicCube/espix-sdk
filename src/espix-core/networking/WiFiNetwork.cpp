#include "WiFiNetwork.h"

#include <Schedule.h>

#include "../applications/Application.h"
#include "../timing/TimeClient.h"

WiFiNetwork::WiFiNetwork() {
}

bool WiFiNetwork::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

wl_status_t WiFiNetwork::getStatus() {
  return WiFi.status();
}

String WiFiNetwork::getLocalIP() {
  return WiFi.localIP().toString();
}

void WiFiNetwork::connect(WiFiConnectionSetting settings[], int settingsCount, bool showProgress,
                          NetworkConnectionCallback callback) {
  if (showProgress) {
    _getProgressView()->setMode(PROGRESS_INFINITY);
    _getProgressView()->setText("Connecting to WiFi...");
    Application::getInstance()->setRootView(_getProgressView());
  }

  static WiFiEventHandler handler = WiFi.onStationModeGotIP([=](const WiFiEventStationModeGotIP e) {
    _connecting = false;
    handler = NULL;
    WiFi.onStationModeGotIP(NULL);
    schedule_function([=]() {
      if (showProgress) {
        _getProgressView()->setText("WiFi connected.");
      }
      TimeClient.begin();
      if (callback) {
        callback();
      }
    });
  });

  WiFi.mode(WIFI_STA);
  for (int i = 0; i < settingsCount; i++) {
    auto setting = settings[i];
    _wifiMulti.addAP(setting.ssid.c_str(), setting.password.c_str());
  }
  _wifiMulti.run();
  _connecting = true;
}

void WiFiNetwork::disconnect(bool wifiOff) {
  WiFi.disconnect(wifiOff);
}

void WiFiNetwork::update() {
  if (_connecting) {
    if (millis() - _lastUpdate > 200) {
      _lastUpdate = millis();
      _wifiMulti.run();
    }
  }
}

ProgressView *WiFiNetwork::_getProgressView() {
  if (_progressView == NULL) {
    _progressView = new ProgressView();
  }
  return _progressView;
}
