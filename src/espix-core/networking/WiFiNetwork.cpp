#include "WiFiNetwork.h"

WiFiNetwork::WiFiNetwork() {
}

void WiFiNetwork::connect(WiFiConnectionSetting setting) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(setting.ssid.c_str(), setting.password.c_str());
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
