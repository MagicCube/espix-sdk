#include "MainMenuView.h"

#include "../../settings/Settings.h"

#include "../../alarm/views/AlarmView.h"
#include "../../network/views/NetworkView.h"

MainMenuView::MainMenuView()
    : MenuListView({MenuItem("NIGHT_MODE", "Enter Night Mode"), MenuItem("ALARM", "Alarm"),
                    MenuItem("BRIGHTNESS", "Brightness"), MenuItem("NETWORK", "Network"),
                    MenuItem("RESTART", "Restart")}) {
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
  auto menuItem = getItem(getSelectedIndex());
  String key = menuItem->key;
  if (key.equals("NIGHT_MODE")) {
    auto brightnessSettings = Settings.getBrightnessSettings();
    brightnessSettings->isNightMode = !brightnessSettings->isNightMode;
    getItem(0)->text = brightnessSettings->isNightMode ? "Exit Night Mode" : "Enter Night Mode";
    Application.popView();
  } else if (key.equals("ALARM")) {
    Application.pushView(AlarmView::getInstance());
  } else if (key.equals("BRIGHTNESS")) {

  } else if (key.equals("NETWORK")) {
    Application.pushView(NetworkView::getInstance());
  } else if (key.equals("RESTART")) {
    ESP.restart();
  }
}
