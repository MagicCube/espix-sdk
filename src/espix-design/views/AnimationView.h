#pragma once

#include <Arduino.h>

#include "../../espix-core/views/View.h"

class AnimationView : public View {
public:
  AnimationView(const uint8_t **xbmFrames, int width, int height, int frameCount, uint8_t fps = 24);

  void willMount();
  bool shouldUpdate();
  void update();
  void render(DrawingContext *context);

private:
  const uint8_t **_xbmFrames;
  int _frameIndex = -1;
  int _frameCount;
  int _fps;
  int _width;
  int _height;
};
