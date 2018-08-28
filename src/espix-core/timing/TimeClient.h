#pragma once

#include <Arduino.h>

#include "DateTime.h"

// Represents a automatically synchronized NTP client.
// The only instance of TimeClientClass is a global variable `TimeClient`.
class TimeClientClass {
public:
  // Creates a new instance of the TimeClientClass class.
  // Do not call this constructor directly. Always use the global variable `TimeClient`.
  TimeClientClass(unsigned long timeOffset);

  // Gets the Unix timestamp of now.
  unsigned long now();

  // Gets a boolean value indicates whether the time client is synchronized.
  bool isReady();

  // Get a DateTime object in local time zone.
  DateTime getLocalTime();

  // Get formatted local time.
  // http://www.cplusplus.com/reference/ctime/strftime/
  String getLocalTimeStrig();

  // Initializes the time client.
  void begin();

  // Updates in the loop.
  void update();

  // Forces to update online.
  void forceUpdate();

private:
  void _internalUpdate();
  unsigned long UPDATE_TIMEOUT = 2000;
  unsigned long UPDATE_INTERVAL = 60 * 60 * 1000;
  bool _hasBegun = false;
  bool _isReady = false;
  bool _isUpdating = false;
  unsigned long _timeOffset;
  uint8_t _updateRetries = 0;
  unsigned long _updateStart = 0;
  unsigned long _lastUpdate = 0;
};

extern TimeClientClass TimeClient;
