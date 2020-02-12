#include "Screen.h"

ScreenClass::ScreenClass() {
}

OLEDDisplay *ScreenClass::getDisplay() {
  return _display;
}

Canvas *ScreenClass::getCanvas() {
  return _canvas;
}

uint8_t ScreenClass::getBrightness() {
  return _brightness;
}

void ScreenClass::setBrightness(uint8_t percentage) {
  if (_brightness != percentage) {
    _brightness = percentage;
    _display->setContrast(percentage * 255 / 100);
  }
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
    if (_brightness != 0) {
      setBrightness(0);
    }
  }
}

void ScreenClass::turnOn() {
  _display->displayOn();
}

void ScreenClass::turnOff() {
  _display->displayOff();
}

void ScreenClass::clearBuffer() {
  _canvas->clear();
}

void ScreenClass::clear() {
  clearBuffer();
  _display->display();
}

void ScreenClass::activate() {
  setBrightness(100);
  _lastActiveTime = millis();
}

ScreenClass Screen;
