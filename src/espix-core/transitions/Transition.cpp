#include "Transition.h"

void Transition::start(int startValue, int endValue, TransitionOptions options) {
  _isRunning = true;
  _startValue = startValue;
  _endValue = endValue;
  _startTime = millis();
  _options = options;
}

void Transition::stop() {
  _isRunning = false;
}

int Transition::getValue() {
  int elapsedTime = millis() - _startTime;
  if (elapsedTime >= getDuration()) {
    return _endValue;
  }
  float percentage = (float)elapsedTime / getDuration();
  return _startValue + percentage * (_endValue - _startValue);
}

int Transition::getStartTime() {
  return _startTime;
}

int Transition::getStartValue() {
  return _startValue;
}

int Transition::getEndValue() {
  return _endValue;
}

TransitionDirection Transition::getDirection() {
  return _options.direction;
}

TransitionOrientation Transition::getOrientation() {
  return _options.getOrientation();
}

int Transition::getDuration() {
  return _options.duration;
}

TransitionOptions Transition::getOptions() {
  return _options;
}

bool Transition::isRunning() {
  return _isRunning;
}

bool Transition::isTimeout() {
  if (getDuration() == 0) {
    return false;
  }
  int elapsedTime = millis() - _startTime;
  return elapsedTime >= getDuration();
}
