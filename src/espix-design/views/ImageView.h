#pragma once

#include <Arduino.h>

#include "../../espix-core/views/View.h"

class ImageView : public View {
public:
  ImageView(const uint8_t *xbm, int width, int height);
  void render(DrawingContext *context);

private:
  const uint8_t *_xbm;
  int _width;
  int _height;
};
