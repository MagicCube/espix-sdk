#pragma once

#include <Arduino.h>

#include "../../espix-core/views/View.h"

class TextView : public View {
public:
  TextView(String text, FontSize fontSize = FontSize::H1,
           TextAlign textAlign = TextAlign::CENTER_BOTH);
  TextView(FontSize fontSize = FontSize::H1, TextAlign textAlign = TextAlign::CENTER_BOTH);

  String getText();
  void setText(String text);

  void render(CanvasContext *context);

private:
  String _text;
  TextAlign _textAlign;
  FontSize _fontSize;
};
