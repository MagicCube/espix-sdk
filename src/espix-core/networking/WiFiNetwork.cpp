#include "WiFiNetwork.h"

#include <Schedule.h>

#include "../applications/Application.h"
#include "../timing/TimeClient.h"

WiFiNetworkClass::WiFiNetworkClass() {
}

bool WiFiNetworkClass::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

wl_status_t WiFiNetworkClass::getStatus() {
  return WiFi.status();
}

String WiFiNetworkClass::getLocalIP() {
  return WiFi.localIP().toString();
}

void WiFiNetworkClass::addToPreferredList(WiFiConnectionSetting setting) {
  _preferredList.add(setting);
}

void WiFiNetworkClass::connect(NetworkConnectionCallback callback) {
  static WiFiEventHandler handler = WiFi.onStationModeGotIP([=](const WiFiEventStationModeGotIP e) {
    _connectionState = WiFiConnectionState::CONNECTED;
    handler = NULL;
    WiFi.onStationModeGotIP(NULL);
    schedule_function([=]() {
      TimeClient.begin();
      if (callback) {
        callback();
      }
    });
  });

  WiFi.mode(WIFI_STA);
  _connectionState = WiFiConnectionState::SCANNING;
  WiFi.scanNetworksAsync([=](int networksFounds) {
    if (_connectionState != WiFiConnectionState::SCANNING) {
      return;
    }
    for (int i = 0; i < networksFounds; i++) {
      for (auto setting : _preferredList) {
        if (setting.ssid.equals(WiFi.SSID(i))) {
          _connectionState = WiFiConnectionState::CONNECTING;
          WiFi.begin(setting.ssid.c_str(), setting.password.c_str());
          break;
        }
      }
    }
  });
}

void WiFiNetworkClass::disconnect(bool wifiOff) {
  WiFi.disconnect(wifiOff);
  _connectionState = WiFiConnectionState::DISCONNECTED;
}

void WiFiNetworkClass::update() {
}

WiFiNetworkClass WiFiNetwork;
