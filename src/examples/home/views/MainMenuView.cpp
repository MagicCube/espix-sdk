#include "MainMenuView.h"

MainMenuView::MainMenuView() : MenuListView({MenuItem("Alarm")}) {
}

MainMenuView *MainMenuView::getInstance() {
  static MainMenuView instance;
  return &instance;
}
