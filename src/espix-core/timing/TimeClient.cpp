#include "TimeClient.h"

#include <WiFiUdp.h>

static TimeClient *__instance = NULL;

TimeClient::TimeClient() {
  static WiFiUDP ntpUDP;
  _client = new NTPClient(ntpUDP, "1.cn.pool.ntp.org", 8 * 60 * 60);
}

TimeClient *TimeClient::getInstance() {
  if (__instance == NULL) {
    __instance = new TimeClient();
  }
  return __instance;
}

unsigned long TimeClient::getTime() {
  return _client->getEpochTime();
}

String TimeClient::getFormattedTime() {
  return _client->getFormattedTime();
}

void TimeClient::begin() {
  _client->begin();
  _hasBegun = true;
  update();
}

void TimeClient::update() {
  if (_hasBegun) {
    _client->update();
  }
}
