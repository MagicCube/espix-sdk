#include <Arduino.h>

struct ViewUpdateOptions {
  ViewUpdateOptions() {
    now = millis();
  }

  ViewUpdateOptions(bool p_forceUpdate) {
    now = millis();
    forceUpdate = p_forceUpdate;
  }

  unsigned long now = 0;
  bool forceUpdate = false;
};
