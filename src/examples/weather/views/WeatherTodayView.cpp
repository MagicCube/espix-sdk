#include "WeatherTodayView.h"

#include "WeatherForecastView.h"

WeatherTodayView::WeatherTodayView() : View() {
}

WeatherTodayView *WeatherTodayView::getInstance() {
  static WeatherTodayView instance;
  return &instance;
}

void WeatherTodayView::didSelect() {
  Application.pushView(WeatherForecastView::getInstance());
}

void WeatherTodayView::render(CanvasContext *context) {
  _drawContent(context, (getClientWidth() - 72) / 2, (getClientHeight() - 40) / 2);
}

void WeatherTodayView::_drawContent(CanvasContext *context, int x, int y) {
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
