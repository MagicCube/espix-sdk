#include "TimeClient.h"

#include <WiFiUdp.h>

static TimeClient *__instance = NULL;

TimeClient::TimeClient() {
  WiFiUDP ntpUDP;
  _client = new NTPClient(ntpUDP, "1.cn.pool.ntp.org");
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
}

void TimeClient::update() {
  _client->update();
}
