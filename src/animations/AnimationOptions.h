#pragma once

#include <Arduino.h>

struct AnimationOptions {
  AnimationOptions(int p_fps = 60) {
    fps = p_fps;
    updateInterval = ((float)1.0 / (float)fps) * 1000;
  }

  int fps;
  int updateInterval;
};
