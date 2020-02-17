#pragma once

#include <espix-core.h>

class AlarmClass {
public:
  void begin();
  void update();

  bool isBeeping();

  void startBeep();
  void stopBeep();

private:
  unsigned long _lastUpdateTime = 0;
  bool _isBeeping = false;
};

void handleEasyBuzzerCallback();

extern AlarmClass Alarm;
