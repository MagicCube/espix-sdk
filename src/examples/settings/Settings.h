#pragma once

#include "AlarmSettings.h"
#include "BrightnessSettings.h"

class SettingsClass {
public:
  void begin();

  AlarmSettings *getAlarmSettings();
  void saveAlarmSettings(AlarmSettings settings);

  BrightnessSettings *getBrightnessSettings();
  void saveBrightnessSettings(BrightnessSettings settings);

private:
  AlarmSettings _alarmSettings;
  BrightnessSettings _brightnessSettings;
};

extern SettingsClass Settings;
