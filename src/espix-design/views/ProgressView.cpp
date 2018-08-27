#include "ProgressView.h"

ProgressView::ProgressView(String text, ProgressMode mode) {
  _text = text;
  _mode = mode;
}

ProgressView::ProgressView(ProgressMode mode) {
  _text = "";
  _mode = mode;
}

void ProgressView::setMode(ProgressMode mode) {
  if (mode != _mode) {
    _mode = mode;
    _progress = 0;
    setDirty();
  }
}

void ProgressView::setText(String text) {
  if (!text.equals(_text)) {
    _text = text;
    setDirty();
  }
}

void ProgressView::setProgress(int progress) {
  if (progress != _progress) {
    _progress = progress;
    setDirty();
  }
}

bool ProgressView::shouldUpdate() {
  if (isDirty()) {
    return true;
  }
  if (_mode == ProgressMode::INDETERMINATE) {
    return millis() - getLastUpdate() > 16;
  }
  return false;
}

void ProgressView::update() {
  if (_mode == ProgressMode::INDETERMINATE) {
    _progress += _progressOffset;
    if ((_progress >= 100 && _progressOffset > 0) || (_progress <= 0 && _progressOffset < 0)) {
      _progressOffset = -_progressOffset;
    }
  }
}

void ProgressView::render(DrawingContext *context) {
  _renderText(context);

  int width = getWidth() / 10 * 9;
  int height = 8;
  int x = (getWidth() - width) / 2;
  int y = 32;
  uint16_t radius = height / 2;
  uint16_t xRadius = x + radius;
  uint16_t yRadius = y + radius;
  uint16_t doubleRadius = 2 * radius;
  uint16_t innerRadius = radius - 2;

  context->drawCircleQuads(xRadius, yRadius, radius, 0b00000110);
  context->drawHorizontalLine(xRadius, y, width - doubleRadius + 1);
  context->drawHorizontalLine(xRadius, y + height, width - doubleRadius + 1);
  context->drawCircleQuads(x + width - radius, yRadius, radius, 0b00001001);

  if (_mode == ProgressMode::DETERMINATE) {
    uint16_t maxProgressWidth = (width - doubleRadius + 1) * _progress / 100;
    context->fillCircle(xRadius, yRadius, innerRadius);
    context->fillRect(xRadius + 1, y + 2, maxProgressWidth, height - 3);
    context->fillCircle(xRadius + maxProgressWidth, yRadius, innerRadius);
  } else if (_mode == ProgressMode::INDETERMINATE) {
    uint16_t length = width / 10;
    uint16_t offset = (width - length - doubleRadius + 1) * _progress / 100;
    context->fillCircle(xRadius + offset, yRadius, innerRadius);
    context->fillRect(xRadius + offset + 1, y + 2, length, height - 3);
    context->fillCircle(xRadius + offset + length, yRadius, innerRadius);
  }
}

void ProgressView::_renderText(DrawingContext *context) {
  context->setFontSize(_fontSize);
  context->setTextAlign(TextAlign::CENTER);
  context->drawString(_text != "" ? _text : (String(_progress) + " %"), getWidth() / 2, 12);
}
