#pragma once

#include <Arduino.h>

enum class TransitionDirection { LEFT = 1, NONE = 0, RIGHT = -1, UP = 2, DOWN = -2 };

struct TransitionOptions {
  TransitionOptions() {
    direction = TransitionDirection::NONE;
    duration = 200;
  }

  TransitionOptions(int duration) {
    direction = TransitionDirection::NONE;
    duration = duration;
  }

  TransitionOptions(TransitionDirection p_direction) {
    direction = p_direction;
    duration = 200;
  }

  TransitionOptions(TransitionDirection p_direction, int p_duration) {
    direction = p_direction;
    duration = p_duration;
  }

  TransitionDirection direction = TransitionDirection::NONE;
  int duration = 0;
};

const TransitionOptions TRANSITION_OPTIONS_NONE;
