#pragma once

#include <Arduino.h>

#include "../../../espix-core.h"

#include "./WeatherForecastView.h"

#include "../assets/meteocons-font.h"


class WeatherTodayView : public View {
public:
  WeatherTodayView() : View() {
    setSelectable(true);
  }

  void render(CanvasContext *context) {
    _drawContent(context, (getClientWidth() - 72) / 2, (getClientHeight() - 40) / 2);
  }

  void didSelect() {
    Application.pushView(getForecastView());
  }

private:
  WeatherForecastView *getForecastView() {
    if (_forecastView == NULL) {
      _forecastView = new WeatherForecastView();
    }
    return _forecastView;
  }

  void _drawContent(CanvasContext *context, int x, int y) {
    context->setFontSize(FontSize::NORMAL);
    context->setTextAlign(TextAlign::LEFT);
    context->drawString("Mostly Cloudy", x + 28, y + 5);

    String temp = "32°C";
    context->setFontSize(FontSize::H1);
    context->drawString(temp, x + 28, y + 15);

    context->setFont(Meteocons_Plain_42);
    String weatherIcon = "Q";
    int weatherIconWidth = context->getStringWidth(weatherIcon);
    context->drawString(weatherIcon, x - weatherIconWidth / 2, y);
  }

  WeatherForecastView *_forecastView = NULL;
};
