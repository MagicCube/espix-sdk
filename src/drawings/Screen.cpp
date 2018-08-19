#include "Screen.h"

Screen::Screen(OLEDDisplay *display) {
  _display = display;
}

uint8_t Screen::getBrightness() {
  return _brightness;
}

void Screen::setBrightness(uint8_t percentage) {
  _brightness = percentage;
  _display->setContrast(percentage * 255 / 100);
}

bool Screen::isFlipped() {
  return _flipped;
}

void Screen::setOrientation(bool flipped, bool mirrored) {
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

bool Screen::isMirrored() {
  return _mirrored;
}

int Screen::getWidth() {
  return _display->getWidth();
}

int Screen::getHeight() {
  return _display->getHeight();
}

void Screen::begin() {
  _display->init();
  setBrightness(100);
  clear();
}

void Screen::clear() {
  _display->clear();
}

DrawingContext *Screen::createDrawingContext() {
  DrawingContext *context = new DrawingContext(_display);
  context->setSize(getWidth(), getHeight());
  return context;
}
