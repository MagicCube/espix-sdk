#include "TimeClient.h"

TimeClientClass::TimeClientClass(unsigned long timeOffset) {
  _timeOffset = timeOffset;
}

unsigned long TimeClientClass::now() {
  return time(nullptr) * 1000;
}

bool TimeClientClass::isReady() {
  return _isReady;
}

DateTime TimeClientClass::getLocalTime() {
  long t = now();
  return DateTime(t, _timeOffset);
}

String TimeClientClass::getLocalTimeStrig() {
  time_t rawTime = time(nullptr);
  time_t localTime = rawTime + _timeOffset / 1000;
  struct tm *timeInfo;
  timeInfo = localtime(&localTime);
  char buffer[8];
  strftime(buffer, 9, "%T", timeInfo);
  return buffer;
}

String TimeClientClass::getLocalTimeShortStrig() {
  time_t rawTime = time(nullptr);
  time_t localTime = rawTime + _timeOffset / 1000;
  struct tm *timeInfo;
  timeInfo = localtime(&localTime);
  char buffer[5];
  strftime(buffer, 9, "%H:%M", timeInfo);
  return buffer;
}

String TimeClientClass::getLocalDateShortString() {
  time_t rawTime = time(nullptr);
  time_t localTime = rawTime + _timeOffset / 1000;
  struct tm *timeInfo;
  timeInfo = localtime(&localTime);
  char buffer[6];
  strftime(buffer, 9, "%a %d", timeInfo);
  return buffer;
}

void TimeClientClass::begin() {
  _hasBegun = true;
  forceUpdate();
}

void TimeClientClass::update() {
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
          _isReady = true;
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

void TimeClientClass::forceUpdate() {
  if (!_hasBegun) {
    return;
  }
  _isUpdating = true;
  _updateRetries = 1;
  _internalUpdate();
}

void TimeClientClass::_internalUpdate() {
  if (!_hasBegun) {
    return;
  }
  _updateStart = millis();
  configTime(0, 0, "0.cn.pool.ntp.org", "1.cn.pool.ntp.org", "2.cn.pool.ntp.org");
}

TimeClientClass TimeClient(8 * 60 * 60 * 1000);
