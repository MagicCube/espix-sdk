#pragma once

#include <Arduino.h>

#include "../../espix-core/views/View.h"

class AnimationView : public View {
public:
  AnimationView(const uint8_t **xbmFrames, int width, int height, int frameCount, uint8_t fps = 24);

  void willMount();
  bool shouldUpdate();
  void update();
  void render(CanvasContext *context);

private:
  const uint8_t **_xbmFrames = NULL;
  int _frameIndex = -1;
  int _frameCount = 0;
  int _fps = 0;
  int _width = 0;
  int _height = 0;
};
