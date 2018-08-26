#include "Screen.h"

#include "../drawing/DrawingContext.h"

ScreenClass::ScreenClass() {
}

OLEDDisplay *ScreenClass::getDisplay() {
  return _display;
}

uint8_t ScreenClass::getBrightness() {
  return _brightness;
}

void ScreenClass::setBrightness(uint8_t percentage) {
  _brightness = percentage;
  _display->setContrast(percentage * 255 / 100);
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

void ScreenClass::setDirty() {
  _dirty = true;
}

void ScreenClass::begin(OLEDDisplay *display) {
  _display = display;
  _display->init();
  _display->resetDisplay();
  _display->resetOrientation();
  _display->normalDisplay();
  setBrightness(100);
  clear();
}

void ScreenClass::update() {
  if (_dirty) {
    _display->display();
    _dirty = false;
  }
}

void ScreenClass::clearBuffer() {
  _display->clear();
  _dirty = true;
}

void ScreenClass::clear() {
  clearBuffer();
  _display->display();
  _dirty = false;
}

DrawingContext *ScreenClass::createDrawingContext() {
  auto context = new DrawingContext();
  context->setSize(getWidth(), getHeight());
  return context;
}

ScreenClass Screen;
