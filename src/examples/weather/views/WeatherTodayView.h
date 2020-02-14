#pragma once

#include <Arduino.h>

#include <espix-core.h>

class WeatherTodayView : public View {
public:
  WeatherTodayView();

  static WeatherTodayView *getInstance();

  void didSelect();
  void render(CanvasContext *context);

private:
  void _drawContent(CanvasContext *context, int x, int y);
};
