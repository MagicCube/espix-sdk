#pragma once

#include <Arduino.h>

#include "../../../espix-core.h"

class ClockView : public View {
public:
  ClockView() {
  }

  bool shouldUpdate() {
    if (isDirty()) {
      return true;
    }
    if (millis() - getLastUpdate() > 1000) {
      return true;
    }
    return false;
  }

  void update() {
    if (TimeClient.isReady()) {
      _text = TimeClient.getLocalTimeStrig();
    } else {
      _text = "-- : -- : --";
    }
  }

  void render(CanvasContext *context) {
    context->setFontSize(FontSize::H1);
    context->setTextAlign(TextAlign::CENTER_BOTH);
    context->drawString(_text);
  }

private:
  String _text;
};
