#include "StatusBar.h"

#include "../../espix-core/timing/TimeClient.h"

StatusBar::StatusBar() : View() {
  setHeight(12);
}

bool StatusBar::shouldUpdate() {
  if (isDirty()) {
    return true;
  }
  if (millis() - getLastUpdate() > 1000) {
    return true;
  }
  return false;
}

void StatusBar::update() {
  if (TimeClient.isReady()) {
    _text = TimeClient.now().toString("%H:%M");
  } else {
    _text = "";
  }
}

void StatusBar::render(CanvasContext *context) {
  context->clear();
  context->setFontSize(FontSize::NORMAL);
  context->setTextAlign(TextAlign::CENTER);
  context->drawString(_text);
}
