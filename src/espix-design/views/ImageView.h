#pragma once

#include <Arduino.h>

#include "espix-core.h"

class ImageView : public View {
public:
  ImageView(const uint8_t *xbm, int width, int height) {
    _xbm = xbm;
    _width = width;
    _height = height;
  }

  void render(DrawingContext *context) {
    Serial.println("ImageView::render()");
    context->drawXBM(_xbm, _width, _height, (getWidth() - _width) / 2, (getHeight() - _height) / 2);
  }

private:
  const uint8_t *_xbm;
  int _width;
  int _height;
};
