#pragma once

#include <Arduino.h>

#include "AnimationOptions.h"
#include "AnimationState.h"
#include "events.h"

class AnimationLoop;

// Represents an animation loop.
class AnimationLoop {
public:
  // Creates a new instance of the AnimationLoop class.
  AnimationLoop(AnimationOptions options = AnimationOptions());

  // Gets options of the animation loop.
  AnimationOptions getOptions();

  // Gets current state of the animation loop.
  AnimationState getState();

  // Occurs when the timer has elapsed and the animation loop has begun.
  void onTick(AnimationTickEventHandler handler);

  // Initializes the animation loop.
  void begin();

  // Update in the loop.
  void update();

private:
  AnimationOptions _options;
  AnimationState _state;

  AnimationTickEventHandler _onTick = NULL;

  void _fireTickEvent();
};
