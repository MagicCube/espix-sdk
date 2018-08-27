#pragma once

#include <Arduino.h>

#include "../../espix-core/views/View.h"

enum class ProgressMode { DETERMINATE = 0, INDETERMINATE = 1 };

class ProgressView : public View {
public:
  ProgressView(String text = "", ProgressMode mode = ProgressMode::DETERMINATE);
  ProgressView(ProgressMode mode);

  void setMode(ProgressMode mode);
  void setText(String text);
  void setProgress(int progress);

  bool shouldUpdate();
  void update();
  void render(DrawingContext *context);

private:
  void _renderText(DrawingContext *context);

  ProgressMode _mode;
  String _text;
  FontSize _fontSize = FontSize::NORMAL;
  int _progress = 0;
  int _progressOffset = 1;
};
