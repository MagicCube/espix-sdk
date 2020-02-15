#pragma once

#include <Arduino.h>

#include "enums/KeyCode.h"

#include "../events/EventArgs.h"

using namespace std;

class ScrollEventArgs : public EventArgs {
public:
  ScrollEventArgs(int p_delta) {
    delta = p_delta;
  }

  int delta;
};

class KeyEventArgs : public EventArgs {
public:
  KeyCode keyCode;

  KeyEventArgs(KeyCode p_keyCode) {
    keyCode = p_keyCode;
  }
};

typedef function<void(ScrollEventArgs *)> ScrollEventHandler;
typedef function<void(KeyEventArgs *)> KeyEventHandler;
