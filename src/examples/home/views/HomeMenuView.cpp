#include "HomeMenuView.h"

HomeMenuView::HomeMenuView()
    : MenuListView({MenuItem("Alarm"), MenuItem("Calendar"), MenuItem("Stop Watch"),
                    MenuItem("Timer"), MenuItem("World Clock"), MenuItem("Resync Time")}) {
}

HomeMenuView *HomeMenuView::getInstance() {
  static HomeMenuView instance;
  return &instance;
}
