#include "Settings.h"

#include <EEPROM.h>

void SettingsClass::begin() {
  EEPROM.begin(16);
  if (EEPROM.read(0) == 84) {
    _alarmSettings.mode = (AlarmMode)EEPROM.read(1);
    _alarmSettings.hours = EEPROM.read(2);
    _alarmSettings.minutes = EEPROM.read(3);
  }
}

AlarmSettings SettingsClass::getAlarmSettings() {
  return _alarmSettings;
}

void SettingsClass::saveAlarmSettings(AlarmSettings settings) {
  _alarmSettings = settings;
  EEPROM.write(0, 84);
  EEPROM.write(1, (uint8_t)_alarmSettings.mode);
  EEPROM.write(2, _alarmSettings.hours);
  EEPROM.write(3, _alarmSettings.minutes);
  EEPROM.commit();
}

bool SettingsClass::isNightMode() {
  return _isNightMode;
}

void SettingsClass::setNightMode(bool nightMode) {
  _isNightMode = nightMode;
}

SettingsClass Settings;
