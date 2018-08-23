#include "TimeClient.h"

TimeClient *__instance = NULL;

TimeClient::TimeClient(unsigned long timeOffset) {
  _timeOffset = timeOffset;
}

TimeClient *TimeClient::getInstance() {
  if (__instance == NULL) {
    __instance = new TimeClient(8 * 60 * 60 * 1000);
  }
  return __instance;
}

unsigned long TimeClient::now() {
  return time(nullptr) * 1000;
}

bool TimeClient::isReady() {
  return _isReady;
}

DateTime TimeClient::getLocalTime() {
  long t = now();
  return DateTime(t, _timeOffset);
}

String TimeClient::getLocalTimeStrig() {
  time_t rawTime = time(nullptr);
  time_t localTime = rawTime + _timeOffset / 1000;
  struct tm *timeInfo;
  timeInfo = localtime(&localTime);
  char buffer[8];
  strftime(buffer, 9, "%T", timeInfo);
  return buffer;
}

void TimeClient::begin() {
  _hasBegun = true;
  Serial.println("TimeClient: Update for the first time");
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
        Serial.println("TimeClient: retry");
        _internalUpdate();
      } else {
        long now = time(nullptr);
        if (now > (2016 - 1970) * 365 * 24 * 60 * 60) {
          // Successful
          _isReady = true;
          _isUpdating = false;
          _lastUpdate = millis();
        }
      }
    } else {
      // Stop retrying after 10 times
      _isUpdating = false;
      _lastUpdate = millis();
      Serial.println("TimeClient: fail");
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
  Serial.println("TimeClient: Internal update...");
  configTime(0, 0, "0.cn.pool.ntp.org", "1.cn.pool.ntp.org", "2.cn.pool.ntp.org");
}
