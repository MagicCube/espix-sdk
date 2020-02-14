#pragma once

#include <espix-core.h>

#include "AlarmSettings.h"

class AlarmClass {
public:
  void begin();
  void update();

  bool isBeeping();
  AlarmSettings getSettings();
  void saveSettings(AlarmSettings settings);

  void startBeep();
  void stopBeep();

private:
  unsigned long _lastUpdateTime = 0;
  bool _isBeeping = false;

  AlarmSettings _settings;
};

extern AlarmClass Alarm;
