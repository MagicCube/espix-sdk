#pragma once

#include <Arduino.h>

#include <time.h>

class TimeClient {
public:
  static TimeClient *getInstance();
  time_t now();

  // Get formatted time.
  // http://www.cplusplus.com/reference/ctime/strftime/
  String getFormattedTime(String format = "%T");

  void begin();
  void update();

private:
  TimeClient(time_t timeOffset = 8 * 60 * 60);
  time_t _timeOffset;
};
