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
  if (_settings.mode != AlarmMode::OFF && !isBeeping()) {
    if (_lastUpdateTime == 0 || millis() >= _lastUpdateTime + 1000) {
      _lastUpdateTime = millis();
      auto now = TimeClient.now();
      if (now.getHours() == _settings.hours && now.getMinutes() == _settings.minutes) {
        bool rightDay = false;
        if (_settings.mode == AlarmMode::EVERYDAY) {
          rightDay = true;
        } else if (_settings.mode == AlarmMode::WEEKDAY) {
          int day = now.getDay();
          if (day != 0 && day != 6) {
            rightDay = true;
          }
        }
        if (rightDay) {
          startBeep();
          _lastUpdateTime += 1000 * 61;
        }
      }
    }
  }
}

bool AlarmClass::isBeeping() {
  return _isBeeping;
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

void AlarmClass::startBeep() {
  _isBeeping = true;
  EasyBuzzer.beep(4000, // Frequency in hertz(HZ).
                  40,   // On Duration in milliseconds(ms).
                  80,   // Off Duration in milliseconds(ms).
                  4,    // The number of beeps per cycle.
                  500,  // Pause duration.
                  30    // The number of cycle.
  );
  if (!Screen.isOn()) {
    Screen.turnOn();
  }
  Screen.activate();
  digitalWrite(LED_BUILTIN, HIGH);
}

void AlarmClass::stopBeep() {
  EasyBuzzer.stopBeep();
  EasyBuzzer.beep(0, // Frequency in hertz(HZ).
                  0, // On Duration in milliseconds(ms).
                  0, // Off Duration in milliseconds(ms).
                  0, // The number of beeps per cycle.
                  0, // Pause duration.
                  0  // The number of cycle.
  );
  digitalWrite(LED_BUILTIN, LOW);
  _isBeeping = false;
}

AlarmClass Alarm;
