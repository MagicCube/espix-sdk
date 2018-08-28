#pragma once

#include <Arduino.h>

#include "../events/EventArgs.h"

#include "KeyCode.h"

using namespace std;

struct ScrollEventArgs : EventArgs {
  ScrollEventArgs(int p_delta) {
    delta = p_delta;
  }

  int delta;
};

struct KeyEventArgs : EventArgs {
  KeyEventArgs(KeyCode p_keyCode) {
    keyCode = p_keyCode;
  }

  KeyCode keyCode;
};

typedef function<void(ScrollEventArgs)> ScrollEventHandler;
typedef function<void(KeyEventArgs)> KeyEventHandler;
