#include "ClockView.h"

#include "ClockMenuView.h"

ClockView::ClockView() : View() {
}

ClockView *ClockView::getInstance() {
  static ClockView instance;
  return &instance;
}

bool ClockView::shouldUpdate() {
  if (isDirty()) {
    return true;
  }
  if (millis() - getLastUpdate() > 1000) {
    return true;
  }
  return false;
}

void ClockView::update() {
  if (TimeClient.isReady()) {
    _timeString = TimeClient.getLocalTimeStrig();
  }
}

void ClockView::didSelect() {
  Application.pushView(ClockMenuView::getInstance());
}

void ClockView::render(CanvasContext *context) {
  context->setFontSize(FontSize::H1);
  context->setTextAlign(TextAlign::CENTER_BOTH);
  context->drawString(_timeString);
}
