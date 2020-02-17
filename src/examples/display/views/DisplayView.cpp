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
  _dayTimeBrightness = settings->dayTimeBrightness;
  _nightTimeBrightness = settings->nightTimeBrightness;
  setText("Day Time Brightness");
  setProgress(_dayTimeBrightness);
  Application.showStatusBar();
}

void DisplayView::willUnmount() {
  Application.hideStatusBar();
}

void DisplayView::didSelect() {
  _nextStep();
}

void DisplayView::handleScroll(ScrollEventArgs *e) {
  if (_step == DisplaySetupStep::SETTING_DAY_TIME_BRIGHTNESS) {
    if (e->delta < 0) {
      _dayTimeBrightness -= 2;
      if (_dayTimeBrightness < 0) {
        _dayTimeBrightness = 0;
      }
    } else {
      _dayTimeBrightness += 2;
      if (_dayTimeBrightness > 100) {
        _dayTimeBrightness = 100;
      }
    }
    setProgress(_dayTimeBrightness);
  } else if (_step == DisplaySetupStep::SETTING_NIGHT_TIME_BRIGHTNESS) {
    if (e->delta < 0) {
      _nightTimeBrightness -= 2;
      if (_nightTimeBrightness < 0) {
        _nightTimeBrightness = 0;
      }
    } else {
      _nightTimeBrightness += 2;
      if (_nightTimeBrightness > 100) {
        _nightTimeBrightness = 100;
      }
    }
    setProgress(_nightTimeBrightness);
  }
}

void DisplayView::_nextStep() {
  if (_step == DisplaySetupStep::SETTING_DAY_TIME_BRIGHTNESS) {
    _step = DisplaySetupStep::SETTING_NIGHT_TIME_BRIGHTNESS;
    setText("Night Time Brightness");
    setProgress(_nightTimeBrightness);
  } else {
    auto displaySettings = Settings.getDisplaySettings();
    Settings.saveDisplaySettings({.isNightMode = displaySettings->isNightMode,
                                  .dayTimeBrightness = _dayTimeBrightness,
                                  .nightTimeBrightness = _nightTimeBrightness});
    Application.popView();
  }
}
