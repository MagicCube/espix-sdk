#include "ClockMenuView.h"

ClockMenuView::ClockMenuView()
    : MenuListView({MenuItem("Alarm"), MenuItem("Calendar"), MenuItem("Stop Watch"),
                    MenuItem("Timer"), MenuItem("World Clock"), MenuItem("Resync Time")}) {
}

ClockMenuView *ClockMenuView::getInstance() {
  static ClockMenuView instance;
  return &instance;
}
