#include "TextView.h"

TextView::TextView(String text, FontSize fontSize, TextAlign textAlign) {
  if (text == NULL) {
    text = "";
  }
  _text = text;
  _fontSize = fontSize;
  _textAlign = textAlign;
}

TextView::TextView(FontSize fontSize, TextAlign textAlign) {
  _text = "";
  _fontSize = fontSize;
  _textAlign = textAlign;
}

String TextView::getText() {
  return _text;
}

void TextView::setText(String text) {
  if (text == NULL) {
    text = "";
  }
  if (!text.equals(_text)) {
    _text = text;
    setDirty();
  }
}

void TextView::render(DrawingContext *context) {
  context->setFontSize(_fontSize);
  context->setTextAlign(_textAlign);
  context->drawString(_text);
}
