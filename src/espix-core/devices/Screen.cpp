#include "Screen.h"

#include "../timing/TimeClient.h"

// TODO: DELETE
#include "../../examples/settings/Settings.h"

ScreenClass::ScreenClass() {
}

OLEDDisplay *ScreenClass::getDisplay() {
  return _display;
}

Canvas *ScreenClass::getCanvas() {
  return _canvas;
}

bool ScreenClass::isOn() {
  return _isOn;
}

bool ScreenClass::isActive() {
  return _isActive;
}

uint8_t ScreenClass::getBrightness() {
  return _brightness;
}

void ScreenClass::setBrightness(uint8_t percentage) {
  if (_brightness != percentage) {
    _brightness = percentage;
    _display->setBrightness(percentage * 255 / 100);
  }
}

void ScreenClass::dim() {
  uint8_t percentage = 40;
  int hours = TimeClient.now().getHours();
  if (hours <= 6 || Settings.isNightMode()) {
    percentage = 15;
    _isOn = false;
  } else {
    if (hours >= 23) {
      // After 11pm, and before 0am
      percentage = 20;
    } else if (hours >= 20) {
      // After 8pm, and before 9
      percentage = 25;
    }
  }
  setBrightness(percentage);
  _isActive = false;
}

bool ScreenClass::isFlipped() {
  return _flipped;
}

void ScreenClass::setOrientation(bool flipped, bool mirrored) {
  _flipped = flipped;
  _mirrored = mirrored;
  _display->resetOrientation();
  if (_flipped) {
    _display->flipScreenVertically();
  }
  if (_mirrored) {
    _display->mirrorScreen();
  }
}

bool ScreenClass::isMirrored() {
  return _mirrored;
}

int ScreenClass::getWidth() {
  return _display->getWidth();
}

int ScreenClass::getHeight() {
  return _display->getHeight();
}

void ScreenClass::begin(OLEDDisplay *display) {
  _display = display;
  _display->init();
  _display->resetDisplay();
  _display->resetOrientation();
  _display->normalDisplay();

  _canvas = new Canvas(display);

  clear();
}

void ScreenClass::update() {
  if (_canvas) {
    _canvas->update();
  }

  if (millis() - _lastActiveTime > 5 * 1000) {
    dim();
  }
}

void ScreenClass::turnOn() {
  _display->displayOn();
  _isOn = true;
}

void ScreenClass::turnOff() {
  _display->displayOff();
  _isOn = false;
}

void ScreenClass::clearBuffer() {
  _canvas->clear();
}

void ScreenClass::clear() {
  clearBuffer();
  _display->display();
}

void ScreenClass::activate() {
  if (!isOn()) {
    turnOn();
  }
  setBrightness(100);
  _isActive = true;
  _lastActiveTime = millis();
}

ScreenClass Screen;
