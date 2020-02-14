#pragma once

#include "AlarmSettings.h"

class AlarmClass {
public:
  void begin();
  void update();

  AlarmSettings getSettings();
  void saveSettings(AlarmSettings settings);

  void snooze();

private:
  unsigned long _lastUpdateTime = 0;

  AlarmSettings _settings;
};

extern AlarmClass Alarm;
