#pragma once

#include <Arduino.h>

#include <espix-core.h>

class StockView : public View {
public:
  StockView();

  static StockView *getInstance();

  void render(CanvasContext *context);

private:
  void _drawTriangle(CanvasContext *context, int8_t direction, int8_t x, int8_t y, uint8_t size, uint8_t height);
};
