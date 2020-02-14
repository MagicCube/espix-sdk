#include "MainMenuView.h"

MainMenuView::MainMenuView() : MenuListView({MenuItem("Alarm")}) {
}

MainMenuView *MainMenuView::getInstance() {
  static MainMenuView instance;
  return &instance;
}

void MainMenuView::willMount() {
  Application.showStatusBar();
}

void MainMenuView::willUnmount() {
  Application.hideStatusBar();
}

void MainMenuView::didSelect() {

}
