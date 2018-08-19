#pragma once

#include <Arduino.h>

#include "espix-core.h"

class TextView : public View {
public:
  TextView(String text, FONT_SIZE fontSize = FONT_SIZE_H1,
           TEXT_ALIGN textAlign = TEXT_ALIGN_CENTER_BOTH) {
    _text = text;
    _fontSize = fontSize;
    _textAlign = textAlign;
  }

  void setText(String text) {
    if (!text.equals(_text)) {
      _text = text;
      setDirty();
    }
  }

  void render(DrawingContext *context) {
    context->setFontSize(_fontSize);
    context->setTextAlign(_textAlign);
    context->drawString(_text);
  }

private:
  String _text;
  TEXT_ALIGN _textAlign;
  FONT_SIZE _fontSize;
};
