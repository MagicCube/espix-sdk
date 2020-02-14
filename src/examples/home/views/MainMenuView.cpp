#include "MainMenuView.h"

MainMenuView::MainMenuView() : MenuListView({MenuItem("Alarm")}) {
}

MainMenuView *MainMenuView::getInstance() {
  static MainMenuView instance;
  return &instance;
}

void MainMenuView::willMount() {
  Application.showStatusView();
}

void MainMenuView::willUnmount() {
  Application.hideStatusView();
}

void MainMenuView::didSelect() {

}
