#pragma once

#include <Arduino.h>

#include <espix-core.h>

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
  String _timeString = "00:00";
  uint8_t _sideViewIndex = 0;
  long _millisSinceLastSideViewIndexChanged = 0;
  bool _blinking = false;

  void _drawDateTime(CanvasContext *context);
  void _drawWeather(CanvasContext *context);
  void _drawStocks(CanvasContext *context);
};
