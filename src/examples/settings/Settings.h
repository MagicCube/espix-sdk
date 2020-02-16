#pragma once

#include "AlarmSettings.h"

class SettingsClass {
public:
  void begin();

  AlarmSettings getAlarmSettings();
  void saveAlarmSettings(AlarmSettings settings);

  bool isNightMode();
  void setNightMode(bool nightMode);

private:
  bool _isNightMode = false;

  AlarmSettings _alarmSettings;
};

extern SettingsClass Settings;
