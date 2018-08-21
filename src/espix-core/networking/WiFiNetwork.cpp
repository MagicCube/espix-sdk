#include "WiFiNetwork.h"

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

void WiFiNetwork::connect(WiFiConnectionSetting setting, NetworkConnectionCallback callback) {
  static auto handler = WiFi.onStationModeGotIP([=](const WiFiEventStationModeGotIP &e) {
    WiFi.onStationModeGotIP(NULL);
    if (callback != NULL) {
      callback();
    }
  });
  WiFi.mode(WIFI_STA);
  WiFi.begin(setting.ssid.c_str(), setting.password.c_str());
}

void WiFiNetwork::disconnect(bool wifiOff) {
  WiFi.disconnect(wifiOff);
}
