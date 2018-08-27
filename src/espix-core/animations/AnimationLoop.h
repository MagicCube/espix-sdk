#pragma once

#include <Arduino.h>

#include "AnimationOptions.h"
#include "AnimationState.h"

class AnimationLoop;

typedef std::function<void(AnimationLoop *target)> AnimationTickEventHandler;

// Represents an animation loop.
class AnimationLoop {
public:
  AnimationLoop(AnimationOptions options = AnimationOptions());

  AnimationOptions getOptions();
  AnimationState getState();

  // Occurs when the timer has elapsed and the animation loop has begun.
  void onTick(AnimationTickEventHandler handler);

  void begin();
  void update();

private:
  AnimationOptions _options;
  AnimationState _state;

  AnimationTickEventHandler _onTick = NULL;

  void _fireTickEvent();
};
