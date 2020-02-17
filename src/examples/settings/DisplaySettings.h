#pragma once

#include <Arduino.h>

struct DisplaySettings {
  bool isNightMode;
  uint8_t dayTimeBrightness;
  uint8_t nightTimeBrightness;
};
