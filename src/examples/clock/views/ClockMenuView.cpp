#include "ClockMenuView.h"

ClockMenuView::ClockMenuView() : MenuListView() {
  Serial.println("ClockMenuView");
}

ClockMenuView *ClockMenuView::getInstance() {
  static ClockMenuView instance;
  return &instance;
}
