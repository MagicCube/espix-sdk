#include "Alarm.h"

#include "../config.h"
#include "../settings/Settings.h"

#include <EEPROM.h>
#include <EasyBuzzer.h>

void AlarmClass::begin() {
}

void AlarmClass::update() {
  auto settings = Settings.getAlarmSettings();
  if (settings.mode != AlarmMode::OFF && !isBeeping()) {
    if (_lastUpdateTime == 0 || millis() >= _lastUpdateTime + 1000) {
      _lastUpdateTime = millis();
      auto now = TimeClient.now();
      if (now.getHours() == settings.hours && now.getMinutes() == settings.minutes) {
        bool rightDay = false;
        if (settings.mode == AlarmMode::EVERYDAY) {
          rightDay = true;
        } else if (settings.mode == AlarmMode::WEEKDAY) {
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

void AlarmClass::startBeep() {
  _isBeeping = true;
  EasyBuzzer.beep(4000, // Frequency in hertz(HZ).
                  40,   // On Duration in milliseconds(ms).
                  80,   // Off Duration in milliseconds(ms).
                  4,    // The number of beeps per cycle.
                  500,  // Pause duration.
                  20,    // The number of cycle.
                  handleEasyBuzzerCallback
  );
  if (!Screen.isOn()) {
    Screen.turnOn();
  }
  digitalWrite(LED_PIN, HIGH);
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
  digitalWrite(LED_PIN, LOW);
  _isBeeping = false;
}

void handleEasyBuzzerCallback() {
  Alarm.stopBeep();
}

AlarmClass Alarm;
