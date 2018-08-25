#pragma once

#include <Arduino.h>

enum TRANSITION_DIRECTION {
  TRANSITION_TO_LEFT = 1,
  TRANSITION_DIRECTION_NONE = 0,
  TRANSITION_TO_RIGHT = -1,
  TRANSITION_TO_TOP = 2,
  TRANSITION_TO_BOTTOM = -2
};

struct TransitionOptions {
  TransitionOptions() {
    direction = TRANSITION_DIRECTION_NONE;
    duration = 200;
  }

  TransitionOptions(int duration) {
    direction = TRANSITION_DIRECTION_NONE;
    duration = duration;
  }

  TransitionOptions(TRANSITION_DIRECTION p_direction) {
    direction = p_direction;
    duration = 200;
  }

  TransitionOptions(TRANSITION_DIRECTION p_direction, int p_duration) {
    direction = p_direction;
    duration = p_duration;
  }

  TRANSITION_DIRECTION direction = TRANSITION_DIRECTION_NONE;
  int duration = 0;
};

const TransitionOptions TRANSITION_OPTIONS_NONE;
