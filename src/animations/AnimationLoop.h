#pragma once

#include <Arduino.h>

#include "AnimationOptions.h"
#include "AnimationState.h"

class AnimationLoop;

typedef std::function<void(AnimationLoop *target)> AnimationTickEventHandler;

class AnimationLoop {
public:
  AnimationLoop();

  AnimationOptions getOptions();
  AnimationState getState();

  void onTick(AnimationTickEventHandler handler);

  void begin();
  int update();

private:
  AnimationOptions _options;
  AnimationState _state;

  AnimationTickEventHandler _onTick;

  void _fireTickEvent();
};
