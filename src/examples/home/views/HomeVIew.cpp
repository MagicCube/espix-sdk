#include "HomeView.h"

#include "HomeMenuView.h"

HomeView::HomeView() : View() {
}

HomeView *HomeView::getInstance() {
  static HomeView instance;
  return &instance;
}

void HomeView::willMount() {
  Application.hideStatusView();
}

void HomeView::willUnmount() {
  Application.showStatusView();
}

bool HomeView::shouldUpdate() {
  if (isDirty()) {
    return true;
  }
  if (millis() - getLastUpdate() > 1000) {
    return true;
  }
  return false;
}

void HomeView::update() {
  if (TimeClient.isReady()) {
    _timeString = TimeClient.getLocalTimeStrig();
  }
}

void HomeView::didSelect() {
  // Application.pushView(HomeMenuView::getInstance());
}

void HomeView::render(CanvasContext *context) {
  context->setFontSize(FontSize::H1);
  context->setTextAlign(TextAlign::CENTER_BOTH);
  context->drawString(_timeString);
}
