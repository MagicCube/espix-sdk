#pragma once

#include <Arduino.h>

#include "../../../espix-design.h"

class MainMenuView : public MenuListView {
public:
  MainMenuView();

  static MainMenuView *getInstance();

  void willMount();
  void willUnmount();
  void didSelect();
};
