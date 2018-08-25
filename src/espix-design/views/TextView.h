#pragma once

#include <Arduino.h>

#include "../../espix-core/views/View.h"

class TextView : public View {
public:
  TextView(String text, FONT_SIZE fontSize = FONT_SIZE_H1,
           TEXT_ALIGN textAlign = TEXT_ALIGN_CENTER_BOTH);
  TextView(FONT_SIZE fontSize = FONT_SIZE_H1, TEXT_ALIGN textAlign = TEXT_ALIGN_CENTER_BOTH);

  String getText();
  void setText(String text);

  void render(DrawingContext *context);

private:
  String _text;
  TEXT_ALIGN _textAlign;
  FONT_SIZE _fontSize;
};
