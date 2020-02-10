#pragma once

#include <Arduino.h>

#include "../../../espix-design.h"

class HomeMenuView : public MenuListView {
public:
  HomeMenuView();

  static HomeMenuView *getInstance();

  void didSelect() {
    Application.popView();
  }
};
