#pragma once

#include <Arduino.h>


#include "../../espix-core/views/View.h"

class StatusBar : public View {
public:
  StatusBar();

  String getText();
  void setText(String text);

  bool shouldUpdate();
  void render(CanvasContext *context);

private:
  String _text = "";
};
