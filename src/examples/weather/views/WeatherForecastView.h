#pragma once

#include <Arduino.h>

#include "../../../espix-core.h"

#include "../assets/meteocons-font.h"

String DAYS[3] = {"THU", "FRI", "SAT"};
String WEATHERS[3] = {"Q", "H", "B"};
String TEMPERATURES[3] = {"26|33", "26|31", "26|32"};

class WeatherForecastView : public View {
public:
  void render(CanvasContext *context) {
    _drawContent(context);
  }

private:
  void _drawContent(CanvasContext *context) {
    _drawForecastDetails(context, 0, 0);
    _drawForecastDetails(context, 44, 1);
    _drawForecastDetails(context, 88, 2);
  }

  void _drawForecastDetails(CanvasContext *context, int x, int dayIndex) {
    context->setTextAlign(TextAlign::CENTER);
    context->setFontSize(FontSize::NORMAL);
    String day = DAYS[dayIndex];
    context->drawString(day, 20 + x, 2);

    context->setFont(Meteocons_Plain_21);
    context->drawString(WEATHERS[dayIndex], x + 20, 14);

    context->setFontSize(FontSize::NORMAL);
    context->drawString(TEMPERATURES[dayIndex], x + 20, 38);
  }
};
