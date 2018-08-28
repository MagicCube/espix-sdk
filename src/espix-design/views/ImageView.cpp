#include "ImageView.h"

ImageView::ImageView(const uint8_t *xbm, int width, int height) {
  _xbm = xbm;
  _width = width;
  _height = height;
}

void ImageView::render(CanvasContext *context) {
  context->drawXBM(_xbm, (getClientWidth() - _width) / 2, (getClientHeight() - _height) / 2, _width,
                   _height);
}
