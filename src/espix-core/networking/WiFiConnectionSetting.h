#pragma once

#include <Arduino.h>

struct WiFiConnectionSetting {
  WiFiConnectionSetting(String p_ssid, String p_password = "") {
    ssid = p_ssid;
    password = p_password;
  }

  String ssid;
  String password;
};
