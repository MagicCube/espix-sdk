#include "EventArgs.h"

bool EventArgs::isDefaultPrevented() {
  return _isDefaultPrevented;
}

void EventArgs::preventDefault() {
  _isDefaultPrevented = true;
}
