#include "WeatherTodayView.h"

#include "../../services/ServiceClient.h"

#include "../assets/meteocons-font.h"

WeatherTodayView::WeatherTodayView() : View() {
}

WeatherTodayView *WeatherTodayView::getInstance() {
  static WeatherTodayView instance;
  return &instance;
}

void WeatherTodayView::didSelect() {
  Application.popView();
}

void WeatherTodayView::render(CanvasContext *context) {
  _drawContent(context, (getClientWidth() - 72) / 2, (getClientHeight() - 40) / 2);
}

void WeatherTodayView::_drawContent(CanvasContext *context, int x, int y) {
  WeatherForecast now = ServiceClient.getWeatherNow();
  context->setFontSize(FontSize::NORMAL);
  context->setTextAlign(TextAlign::LEFT);
  context->drawString(now.dayCond, x + 28, y + 5);

  String temp = String(now.highTemp) + "°C";
  context->setFontSize(FontSize::H1);
  context->drawString(temp, x + 28, y + 14);

  context->setFont(Meteocons_Plain_42);
  String weatherIcon = now.dayCondCode;
  int weatherIconWidth = context->getStringWidth(weatherIcon);
  context->drawString(weatherIcon, x - weatherIconWidth / 2, y);
}
