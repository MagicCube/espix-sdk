#include "Settings.h"

#include <EEPROM.h>

#define RESET_FLAG 84

void SettingsClass::begin() {
  EEPROM.begin(16);
  if (EEPROM.read(0) != RESET_FLAG) {
    EEPROM.write(0, RESET_FLAG);
    saveAlarmSettings({.mode = AlarmMode::OFF, .hours = 0, .minutes = 0});
    saveDisplaySettings({.isNightMode = false, .isPreviewing = false, .dayTimeBrightness = 40, .nightTimeBrightness = 15});
  }
  _alarmSettings.mode = (AlarmMode)EEPROM.read(1);
  _alarmSettings.hours = EEPROM.read(2);
  _alarmSettings.minutes = EEPROM.read(3);
  _displaySettings.dayTimeBrightness = EEPROM.read(4);
  _displaySettings.nightTimeBrightness = EEPROM.read(5);
}

AlarmSettings *SettingsClass::getAlarmSettings() {
  return &_alarmSettings;
}

void SettingsClass::saveAlarmSettings(AlarmSettings settings) {
  _alarmSettings = settings;
  EEPROM.write(1, (uint8_t)_alarmSettings.mode);
  EEPROM.write(2, _alarmSettings.hours);
  EEPROM.write(3, _alarmSettings.minutes);
  EEPROM.commit();
}

DisplaySettings *SettingsClass::getDisplaySettings() {
  return &_displaySettings;
}

void SettingsClass::saveDisplaySettings(DisplaySettings settings) {
  _displaySettings = settings;
  EEPROM.write(4, _displaySettings.dayTimeBrightness);
  EEPROM.write(5, _displaySettings.nightTimeBrightness);
  EEPROM.commit();
}

SettingsClass Settings;
