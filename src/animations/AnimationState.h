#pragma once

#include <Arduino.h>

struct AnimationState {
  unsigned long lastUpdate = 0;
  unsigned long updateStart = 0;
  int timeBudget = 0;
  int ticksSinceLastUpdate = 0;
};
