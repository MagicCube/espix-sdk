#pragma once

#include <Arduino.h>

#include "../../../espix-design.h"

enum class DisplaySetupStep {
  SETTING_DAY_TIME_BRIGHTNESS,
  SETTING_NIGHT_TIME_BRIGHTNESS,
};

class DisplayView : public ProgressView {
public:
  DisplayView();

  static DisplayView *getInstance();

  String getTitle() {
    return "DISPLAY SETTINGS";
  }

  void willMount();
  void willUnmount();
  void handleScroll(ScrollEventArgs *e);
  void didSelect();

private:
  uint8_t _dayTimeBrightness = 0;
  uint8_t _nightTimeBrightness = 0;
  DisplaySetupStep _step = DisplaySetupStep::SETTING_DAY_TIME_BRIGHTNESS;

  void _nextStep();
};
