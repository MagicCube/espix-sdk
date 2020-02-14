#include "Alarm.h"

#include <EEPROM.h>
#include <EasyBuzzer.h>

void AlarmClass::begin() {
  EEPROM.begin(16);
  if (EEPROM.read(0) == 84) {
    _settings.mode = (AlarmMode)EEPROM.read(1);
    _settings.hours = EEPROM.read(2);
    _settings.minutes = EEPROM.read(3);
  }
}

void AlarmClass::update() {
  if (_settings.mode != AlarmMode::OFF) {
    if (_lastUpdateTime == 0 || millis() - _lastUpdateTime >= 1000) {
      _lastUpdateTime = millis();
    }
  }
}

AlarmSettings AlarmClass::getSettings() {
  return _settings;
}

void AlarmClass::saveSettings(AlarmSettings settings) {
  _settings = settings;
  EEPROM.write(0, 84);
  EEPROM.write(1, (uint8_t)_settings.mode);
  EEPROM.write(2, _settings.hours);
  EEPROM.write(3, _settings.minutes);
  EEPROM.commit();
}

void AlarmClass::snooze() {
  EasyBuzzer.stopBeep();
}

AlarmClass Alarm;
