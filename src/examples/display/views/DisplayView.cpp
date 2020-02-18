#include "DisplayView.h"

#include "../../settings/Settings.h"

DisplayView::DisplayView() {
}

DisplayView *DisplayView::getInstance() {
  static DisplayView instance;
  return &instance;
}

void DisplayView::willMount() {
  _step = DisplaySetupStep::SETTING_DAY_TIME_BRIGHTNESS;
  auto settings = Settings.getDisplaySettings();
  settings->isPreviewing = true;
  _dayTimeBrightness = settings->dayTimeBrightness;
  _nightTimeBrightness = settings->nightTimeBrightness;
  setText("Day Time Brightness " + String(_dayTimeBrightness) + "%");
  setProgress(_dayTimeBrightness);
  Application.showStatusBar();
}

void DisplayView::willUnmount() {
  Application.hideStatusBar();
  Settings.getDisplaySettings()->isPreviewing = false;
}

void DisplayView::didSelect() {
  _nextStep();
}

void DisplayView::handleScroll(ScrollEventArgs *e) {
  if (_step == DisplaySetupStep::SETTING_DAY_TIME_BRIGHTNESS) {
    if (e->delta < 0) {
      _dayTimeBrightness -= 1;
      if (_dayTimeBrightness < 0) {
        _dayTimeBrightness = 0;
      }
    } else {
      _dayTimeBrightness += 1;
      if (_dayTimeBrightness > 100) {
        _dayTimeBrightness = 100;
      }
    }
    setProgress(_dayTimeBrightness);
    Screen.setBrightness(_dayTimeBrightness);
    setText("Day Time Brightness " + String(_dayTimeBrightness) + "%");
  } else if (_step == DisplaySetupStep::SETTING_NIGHT_TIME_BRIGHTNESS) {
    if (e->delta < 0) {
      _nightTimeBrightness -= 1;
      if (_nightTimeBrightness < 0) {
        _nightTimeBrightness = 0;
      }
    } else {
      _nightTimeBrightness += 1;
      if (_nightTimeBrightness > 100) {
        _nightTimeBrightness = 100;
      }
    }
    setProgress(_nightTimeBrightness);
    Screen.setBrightness(_nightTimeBrightness);
    setText("Night Time Brightness " + String(_nightTimeBrightness) + "%");
  }
}

void DisplayView::_nextStep() {
  if (_step == DisplaySetupStep::SETTING_DAY_TIME_BRIGHTNESS) {
    _step = DisplaySetupStep::SETTING_NIGHT_TIME_BRIGHTNESS;
    setText("Night Time Brightness " + String(_nightTimeBrightness) + "%");
    setProgress(_nightTimeBrightness);
  } else {
    auto displaySettings = Settings.getDisplaySettings();
    Settings.saveDisplaySettings({.isNightMode = displaySettings->isNightMode,
                                  .isPreviewing = displaySettings->isPreviewing,
                                  .dayTimeBrightness = _dayTimeBrightness,
                                  .nightTimeBrightness = _nightTimeBrightness});
    Application.popView();
  }
}
