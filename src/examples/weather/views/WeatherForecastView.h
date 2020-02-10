#pragma once

#include <Arduino.h>

#include "../../../espix-core.h"

#include "../assets/meteocons-font.h"

class WeatherForecastView : public View {
public:
  WeatherForecastView();

  static WeatherForecastView *getInstance();

  void render(CanvasContext *context);

  void didSelect();

private:
  void _drawForecastDetails(CanvasContext *context, int x, int dayIndex);
};
