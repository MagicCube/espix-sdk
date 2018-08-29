#pragma once

#include <Arduino.h>

#include "enums/TransitionDirection.h"
#include "enums/TransitionOrientation.h"

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

  TransitionOrientation getOrientation() {
    switch (direction) {
    case TransitionDirection::LEFT:
    case TransitionDirection::RIGHT:
      return TransitionOrientation::HORIZONTAL;
    case TransitionDirection::UP:
    case TransitionDirection::DOWN:
      return TransitionOrientation::VERTICAL;
    default:
      return TransitionOrientation::NONE;
    }
  }

  TransitionDirection direction = TransitionDirection::NONE;
  int duration = 0;
};

const TransitionOptions TRANSITION_OPTIONS_NONE;
const TransitionOptions TRANSITION_OPTIONS_AUTO(TransitionDirection::AUTO);
const TransitionOptions TRANSITION_OPTIONS_LEFT(TransitionDirection::LEFT);
const TransitionOptions TRANSITION_OPTIONS_RIGHT(TransitionDirection::RIGHT);
const TransitionOptions TRANSITION_OPTIONS_UP(TransitionDirection::UP);
const TransitionOptions TRANSITION_OPTIONS_DOWN(TransitionDirection::DOWN);
