#include "TimeClient.h"

static TimeClient *__instance = NULL;

TimeClient::TimeClient(time_t timeOffset) {
  _timeOffset = timeOffset;
}

TimeClient *TimeClient::getInstance() {
  if (__instance == NULL) {
    __instance = new TimeClient();
  }
  return __instance;
}

time_t TimeClient::now() {
  return time(nullptr) * 1000;
}

String TimeClient::getFormattedTime(String format) {
  time_t rawTime = time(nullptr);
  time_t localTime = rawTime + _timeOffset;
  struct tm *timeInfo;
  timeInfo = localtime(&localTime);
  char buffer[64];
  strftime(buffer, 64, format.c_str(), timeInfo);
  return buffer;
}

void TimeClient::begin() {
  update();
}

void TimeClient::update() {
  int retryCount = 0;
  unsigned timeout = 1000;
  time_t now = 0;
  while (now == 0 || retryCount > 10) {
    retryCount++;
    configTime(0, 0, "0.cn.pool.ntp.org", "1.cn.pool.ntp.org", "2.cn.pool.ntp.org");
    unsigned start = millis();
    while (millis() - start < timeout) {
      now = time(nullptr);
      if (now > (2016 - 1970) * 365 * 24 * 3600) {
        break;
      }
      delay(50);
    }
  }
}
