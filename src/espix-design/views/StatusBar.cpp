#include "StatusBar.h"

#include "../../espix-core/timing/TimeClient.h"

StatusBar::StatusBar() : View() {
  setHeight(12);
}

String StatusBar::getText() {
  return _text;
}

void StatusBar::setText(String text) {
  if (_text != text) {
    _text = text;
    setDirty();
  }
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

void StatusBar::render(CanvasContext *context) {
  context->clear();
  context->setFontSize(FontSize::NORMAL);
  context->setTextAlign(TextAlign::CENTER);
  if (!getText().equals("")) {
    context->drawString(getText());
  } else {
    if (TimeClient.isReady()) {
      context->drawString(TimeClient.now().toString("%H:%M"));
    }
  }
}
