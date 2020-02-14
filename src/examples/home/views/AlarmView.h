#pragma once

#include <Arduino.h>

#include "../../../espix-design.h"

enum class AlarmSetupStep {
  SETTING_HOURS,
  SETTING_MINUTES,
  SETTING_MODE
};

class AlarmView : public View {
public:
  AlarmView();

  static AlarmView *getInstance();

  String getTitle() {
    return "ALARM SETTINGS";
  }

  void willMount();
  void willUnmount();
  void handleScroll(ScrollEventArgs e);
  void didSelect();

  void render(CanvasContext *context);

private:
  const String ALARM_MODES[3] = { "Everyday", "Weekdays", "Off" };

  uint8_t _hours = 0;
  uint8_t _minutes = 0;
  uint8_t _mode = 0;
  AlarmSetupStep _step = AlarmSetupStep::SETTING_HOURS;

  void _nextStep();
};
