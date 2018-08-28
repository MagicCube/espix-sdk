#include "AnimationLoop.h"

AnimationLoop::AnimationLoop(AnimationOptions options) {
  _options = options;
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
  auto updateStart = millis();
  auto lastUpdate = _state.lastUpdate;
  int elapsedSinceLastUpdate = updateStart - _state.lastUpdate;
  int timeBudget = _options.updateInterval - elapsedSinceLastUpdate;
  if (timeBudget <= 0) {
    _state.lastUpdate = _state.updateStart;
    _state.updateStart = updateStart;
    _state.elapsedSinceLastUpdate = elapsedSinceLastUpdate;
    _state.timeBudget = timeBudget;
    _fireTickEvent();
    // Recalculate time after tick event has done.
    _state.elapsedSinceLastUpdate = millis() - lastUpdate;
    _state.timeBudget = _options.updateInterval - _state.elapsedSinceLastUpdate;
  }
  _state.timeBudget = timeBudget;
}

void AnimationLoop::_fireTickEvent() {
  if (_onTick) {
    _onTick();
  }
}
