#pragma once

#include "AlarmSettings.h"
#include "DisplaySettings.h"

class SettingsClass {
public:
  void begin();

  AlarmSettings *getAlarmSettings();
  void saveAlarmSettings(AlarmSettings settings);

  DisplaySettings *getDisplaySettings();
  void saveDisplaySettings(DisplaySettings settings);

private:
  AlarmSettings _alarmSettings;
  DisplaySettings _displaySettings;
};

extern SettingsClass Settings;
