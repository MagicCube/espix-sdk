#pragma once

#include <Arduino.h>

class EventArgs {
public:
  bool isDefaultPrevented();
  void preventDefault();

private:
  bool _isDefaultPrevented = false;
};
