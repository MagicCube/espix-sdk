#include "WeatherForecastView.h"

#include "../../services/ServiceClient.h"

#include "./WeatherTodayView.h"

WeatherForecastView::WeatherForecastView() : View() {
}

WeatherForecastView *WeatherForecastView::getInstance() {
  static WeatherForecastView instance;
  return &instance;
}

void WeatherForecastView::render(CanvasContext *context) {
  for (int i = 0; i < 3; i++) {
    _drawForecastDetails(context, (getClientWidth() / 3) * i, i);
  }
}

void WeatherForecastView::didSelect() {
  Application.pushView(WeatherTodayView::getInstance());
}

void WeatherForecastView::_drawForecastDetails(CanvasContext *context, int x, int dayIndex) {
  auto forecast = ServiceClient.getWeatherForecast(dayIndex);
  context->setTextAlign(TextAlign::CENTER);
  context->setFontSize(FontSize::NORMAL);
  context->drawString(forecast.day, 22 + x, 2);

  context->setFont(Meteocons_Plain_21);
  context->drawString(forecast.dayCondCode, x + 22, 14);

  context->setFontSize(FontSize::NORMAL);
  context->drawString(String(forecast.lowTemp) + " / " + String(forecast.highTemp), x + 22, 38);
}
