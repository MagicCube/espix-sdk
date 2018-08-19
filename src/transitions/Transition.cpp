#include "Transition.h"

void Transition::start(int startValue, int endValue, int duration) {
  _isRunning = true;
  _startValue = startValue;
  _endValue = endValue;
  _duration = duration;
  _startTime = millis();
}

void Transition::stop() {
  _isRunning = false;
}

int Transition::getValue() {
  int elapsedTime = millis() - _startTime;
  if (elapsedTime >= _duration) {
    return _endValue;
  }
  float percentage = (float)elapsedTime / _duration;
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

int Transition::getDuration() {
  return _duration;
}

bool Transition::isRunning() {
  return _isRunning;
}

bool Transition::isTimeout() {
  if (_duration == 0) {
    return false;
  }
  int elapsedTime = millis() - _startTime;
  return elapsedTime >= _duration;
}
