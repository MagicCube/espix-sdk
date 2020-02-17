#pragma once

#include <Arduino.h>

struct BrightnessSettings {
  bool isNightMode;
  uint8_t dayTimeBrightness;
  uint8_t nightTimeBrightness;
};
