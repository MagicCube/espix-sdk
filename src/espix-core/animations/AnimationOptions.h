#pragma once

#include <Arduino.h>

// Represents options of animation.
struct AnimationOptions {
  AnimationOptions(int p_fps = 60) {
    fps = p_fps;
    updateInterval = ((float)1.0 / (float)fps) * 1000;
  }

  // Gets frame per second.
  int fps;

  // Gets update interval in milliseconds.
  int updateInterval;
};
