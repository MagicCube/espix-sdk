#pragma once

#include <Arduino.h>

#include "enums.h"
#include "structs.h"

class Transition {
public:
  int getValue();
  int getStartTime();
  int getStartValue();
  int getEndValue();
  TransitionDirection getDirection();
  TransitionOrientation getOrientation();
  int getDuration();
  TransitionOptions getOptions();
  bool isRunning();
  bool isTimeout();

  void start(int startValue, int endValue, TransitionOptions options);
  void stop();

private:
  TransitionOptions _options;
  bool _isRunning = false;
  unsigned long _startTime = 0;
  int _startValue = 0;
  int _endValue = 0;
};
