#pragma once

#include <Arduino.h>

#include "../../espix-core/views/View.h"

enum PROGRESS_MODE { PROGRESS_NORMAL, PROGRESS_INFINITY };

class ProgressView : public View {
public:
  ProgressView(String text = "", PROGRESS_MODE mode = PROGRESS_NORMAL);
  ProgressView(PROGRESS_MODE mode);

  void setMode(PROGRESS_MODE mode);
  void setText(String text);
  void setProgress(int progress);

  bool shouldUpdate();
  void update();
  void render(DrawingContext *context);

private:
  void _renderText(DrawingContext *context);

  PROGRESS_MODE _mode;
  String _text;
  FONT_SIZE _fontSize = FONT_SIZE_NORMAL;
  int _progress = 0;
  int _progressOffset = 1;
};
