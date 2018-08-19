#pragma once

#include "TransitionOptions.h"
#include <Arduino.h>

class Transition {
public:
  int getValue();
  int getStartTime();
  int getStartValue();
  int getEndValue();
  int getDuration();
  bool isRunning();
  bool isTimeout();

  void start(int startValue, int endValue, int duration);
  void stop();

private:
  bool _isRunning = false;
  unsigned long _startTime = 0;
  int _startValue = 0;
  int _endValue = 0;
  int _duration = 0;
};
