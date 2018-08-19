#include "AnimationLoop.h"

AnimationLoop::AnimationLoop() {
  begin();
}

void AnimationLoop::onTick(AnimationTickEventHandler handler) {
  _onTick = handler;
}

AnimationOptions AnimationLoop::getOptions() {
  return _options;
}

AnimationState AnimationLoop::getState() {
  return _state;
}

void AnimationLoop::begin() {
  _state.updateStart = millis();
  _state.lastUpdate = millis();
  _state.timeBudget = 0;
}

void AnimationLoop::update() {
  unsigned long updateStart = millis();
  unsigned long lastUpdate = _state.lastUpdate;
  int sinceLastUpdate = updateStart - _state.lastUpdate;
  int timeBudget = _options.updateInterval - sinceLastUpdate;
  if (timeBudget <= 0) {
    _state.lastUpdate = _state.updateStart;
    _state.updateStart = updateStart;
    _state.sinceLastUpdate = sinceLastUpdate;
    _state.timeBudget = timeBudget;
    _fireTickEvent();
    // Recalculate time after tick event has done.
    _state.sinceLastUpdate = millis() - lastUpdate;
    _state.timeBudget = _options.updateInterval - _state.sinceLastUpdate;
  }
  _state.timeBudget = timeBudget;
}

void AnimationLoop::_fireTickEvent() {
  if (_onTick != NULL) {
    _onTick(this);
  }
}
