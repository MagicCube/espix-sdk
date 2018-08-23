#pragma once

#include <Arduino.h>

#include <time.h>

class TimeClient {
public:
  static TimeClient *getInstance();
  unsigned long now();

  // Get formatted local time.
  // http://www.cplusplus.com/reference/ctime/strftime/
  String getLocalTimeStrig();

  void begin();
  void update();
  void forceUpdate();

private:
  TimeClient(unsigned long timeOffset = 8 * 60 * 60);
  void _internalUpdate();
  unsigned long UPDATE_TIMEOUT = 2000;
  unsigned long UPDATE_INTERVAL = 60 * 60 * 1000;
  bool _hasBegun;
  bool _isUpdating;
  unsigned long _timeOffset;
  uint8_t _updateRetries = 0;
  unsigned long _updateStart = 0;
  unsigned long _lastUpdate = 0;
};
