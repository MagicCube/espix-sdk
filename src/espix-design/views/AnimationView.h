#pragma once

#include <Arduino.h>

#include "../../espix-core.h"

class AnimationView : public View {
public:
  AnimationView(const uint8_t **xbmFrames, int width, int height, int frameCount,
                uint8_t fps = 24) {
    _xbmFrames = xbmFrames;
    _width = width;
    _height = height;
    _frameCount = frameCount;
    _fps = fps;
  }

  void willMount() {
    _frameIndex = 0;
  }

  bool shouldUpdate() {
    if (isDirty()) {
      return true;
    }
    return millis() - getLastUpdate() > uint8_t(1000 / _fps);
  }

  void update() {
    _frameIndex++;
    if (_frameIndex >= _frameCount) {
      _frameIndex = 0;
    }
  }

  void render(DrawingContext *context) {
    context->drawXBM(_xbmFrames[_frameIndex], _width, _height, (getWidth() - _width) / 2,
                     (getHeight() - _height) / 2);
  }

private:
  const uint8_t **_xbmFrames;
  int _frameIndex = -1;
  int _frameCount;
  int _fps;
  int _width;
  int _height;
};
