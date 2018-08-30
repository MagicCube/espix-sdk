#pragma once

#include <Arduino.h>

#include "../../../espix-design.h"

class ClockMenuView : public MenuListView {
public:
  ClockMenuView();

  static ClockMenuView *getInstance();

  void didSelect() {
    Application.popView();
  }
};
