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
    for (int i = 0; i < 3; i++) {
      _drawForecastDetails(context, (getClientWidth() / 3) * i, i);
    }
  }

  void _drawForecastDetails(CanvasContext *context, int x, int dayIndex) {
    context->setTextAlign(TextAlign::CENTER);
    context->setFontSize(FontSize::NORMAL);
    String day = DAYS[dayIndex];
    context->drawString(day, 22 + x, 2);

    context->setFont(Meteocons_Plain_21);
    context->drawString(WEATHERS[dayIndex], x + 22, 14);

    context->setFontSize(FontSize::NORMAL);
    context->drawString(TEMPERATURES[dayIndex], x + 22, 38);
  }
};
