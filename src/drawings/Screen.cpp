#include "Screen.h"

static Screen *__instance = NULL;

Screen::Screen(OLEDDisplay *display) {
  _display = display;
  __instance = this;
}

Screen *Screen::getInstance() {
  return __instance;
}

OLEDDisplay *Screen::getDisplay() {
  return _display;
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

void Screen::setDirty() {
  _dirty = true;
}

void Screen::begin() {
  _display->init();
  _display->resetDisplay();
  _display->resetOrientation();
  _display->normalDisplay();
  setBrightness(100);
  clear();
}

void Screen::update() {
  if (_dirty) {
    _display->display();
    _dirty = false;
  }
}

void Screen::clearBuffer() {
  _display->clear();
  _dirty = true;
}

void Screen::clear() {
  clearBuffer();
  _display->display();
  _dirty = false;
}

DrawingContext *Screen::createDrawingContext() {
  DrawingContext *context = new DrawingContext(this);
  context->setSize(getWidth(), getHeight());
  return context;
}
