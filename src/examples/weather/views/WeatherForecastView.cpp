#include "WeatherForecastView.h"

const String DAYS[3] = {"THU", "FRI", "SAT"};
const String WEATHERS[3] = {"2", "3", "4"};
const String TEMPERATURES[3] = {"26|33", "26|31", "26|32"};

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
  Application.popView();
}

void WeatherForecastView::_drawForecastDetails(CanvasContext *context, int x, int dayIndex) {
  context->setTextAlign(TextAlign::CENTER);
  context->setFontSize(FontSize::NORMAL);
  String day = DAYS[dayIndex];
  context->drawString(day, 22 + x, 2);

  context->setFont(Meteocons_Plain_21);
  context->drawString(WEATHERS[dayIndex], x + 22, 14);

  context->setFontSize(FontSize::NORMAL);
  context->drawString(TEMPERATURES[dayIndex], x + 22, 38);
}
