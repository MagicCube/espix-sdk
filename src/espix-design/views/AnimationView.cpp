#include "AnimationView.h"

AnimationView::AnimationView(const uint8_t **xbmFrames, int width, int height, int frameCount,
                             uint8_t fps) {
  _xbmFrames = xbmFrames;
  _width = width;
  _height = height;
  _frameCount = frameCount;
  _fps = fps;
}

void AnimationView::willMount() {
  _frameIndex = 0;
}

bool AnimationView::shouldUpdate() {
  if (isDirty()) {
    return true;
  }
  return millis() - getLastUpdate() > uint8_t(1000 / _fps);
}

void AnimationView::update() {
  _frameIndex++;
  if (_frameIndex >= _frameCount) {
    _frameIndex = 0;
  }
}

void AnimationView::render(CanvasContext *context) {
  context->drawXBM(_xbmFrames[_frameIndex], _width, _height, (getWidth() - _width) / 2,
                   (getHeight() - _height) / 2);
}
