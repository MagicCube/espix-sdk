#pragma once

#include <Arduino.h>

enum class AlarmMode {
  OFF = 0,
  EVERYDAY = 1,
  WEEKDAY = 2
};

struct AlarmSettings {
  AlarmMode mode;
  uint8_t hours;
  uint8_t minutes;
};
