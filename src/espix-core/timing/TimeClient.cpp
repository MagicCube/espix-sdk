#include "TimeClient.h"

static TimeClient *__instance = NULL;

TimeClient::TimeClient(unsigned long timeOffset) {
  _timeOffset = timeOffset;
}

TimeClient *TimeClient::getInstance() {
  if (__instance == NULL) {
    __instance = new TimeClient();
  }
  return __instance;
}

unsigned long TimeClient::now() {
  return time(nullptr) * 1000;
}

String TimeClient::getLocalTimeStrig() {
  time_t rawTime = time(nullptr);
  time_t localTime = rawTime + _timeOffset;
  struct tm *timeInfo;
  timeInfo = localtime(&localTime);
  char buffer[8];
  strftime(buffer, 9, "%T", timeInfo);
  return buffer;
}

void TimeClient::begin() {
  _hasBegun = true;
  forceUpdate();
}

void TimeClient::update() {
  if (!_hasBegun) {
    return;
  }
  if (_isUpdating) {
    if (_updateRetries < 10) {
      if (millis() - _updateStart >= UPDATE_TIMEOUT) {
        // Retry again after timeout
        _updateRetries++;
        _internalUpdate();
      } else {
        long now = time(nullptr);
        if (now > (2016 - 1970) * 365 * 24 * 60 * 60) {
          // Successful
          _isUpdating = false;
          _lastUpdate = millis();
        }
      }
    } else {
      // Stop retrying after 10 times
      _isUpdating = false;
      _lastUpdate = millis();
    }
  } else {
    if (_lastUpdate > 0 && millis() - _lastUpdate >= UPDATE_INTERVAL) {
      // Routine update
      forceUpdate();
    }
  }
}

void TimeClient::forceUpdate() {
  if (!_hasBegun) {
    return;
  }
  _isUpdating = true;
  _updateRetries = 1;
  _internalUpdate();
}

void TimeClient::_internalUpdate() {
  if (!_hasBegun) {
    return;
  }
  _updateStart = millis();
  configTime(0, 0, "0.cn.pool.ntp.org", "1.cn.pool.ntp.org", "2.cn.pool.ntp.org");
}
