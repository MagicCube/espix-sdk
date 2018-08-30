#pragma once

#include <Arduino.h>

#include "../../../espix-core.h"

class ClockView : public View {
public:
  ClockView();

  static ClockView *getInstance();

  bool shouldUpdate();
  void update();
  void didSelect();
  void render(CanvasContext *context);

private:
  String _timeString = "-- : -- : --";
};
