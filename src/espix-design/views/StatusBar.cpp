#include "StatusBar.h"

#include "../../espix-core/timing/TimeClient.h"

#include "../assets/dialog-font.h"

StatusBar::StatusBar() : View() {
  setHeight(10);
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
    _text = TimeClient.getLocalTimeStrig().substring(0, 5);
  } else {
    _text = "";
  }
}

void StatusBar::render(CanvasContext *context) {
  context->clear();
  context->setFont(Dialog_plain_8);
  context->setTextAlign(TextAlign::CENTER);
  context->drawString(_text);
  context->drawHorizontalLine(0, context->getHeight() - 1);
}
