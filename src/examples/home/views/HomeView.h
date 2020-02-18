#pragma once

#include <Arduino.h>

#include <espix-core.h>

#include "../../config.h"

class HomeView : public View {
public:
  HomeView();

  static HomeView *getInstance();

  bool shouldUpdate();
  void update();
  void didSelect();
  void willMount();
  void willUnmount();
  void render(CanvasContext *context);

private:
  #ifdef DEBUG_LOCAL
  String _timeString = "19:43";
  #else
  String _timeString = " T:T ";
  #endif

  uint8_t _sideViewIndex = 0;
  long _millisSinceLastSideViewIndexChanged = 0;
  bool _blinking = false;

  void _drawDateTime(CanvasContext *context);
  void _drawWeather(CanvasContext *context);
  void _drawStocks(CanvasContext *context);
};
