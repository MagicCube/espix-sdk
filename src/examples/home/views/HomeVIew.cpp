#include "HomeView.h"

#include "../../services/ServiceClient.h"
#include "../../weather/assets/meteocons-font.h"

#include "MainMenuView.h"

HomeView::HomeView() : View() {
}

HomeView *HomeView::getInstance() {
  static HomeView instance;
  return &instance;
}

void HomeView::willMount() {
  Application.hideStatusBar();
}

void HomeView::willUnmount() {
  Application.showStatusBar();
  _sideViewIndex = 0;
  _millisSinceLastSideViewIndexChanged = millis();
}

bool HomeView::shouldUpdate() {
  bool result = false;
  if (isDirty()) {
    result = true;
  }
  if (millis() - getLastUpdate() > 500) {
    _blinking = !_blinking;
    result = true;
  }
  return result;
}

void HomeView::update() {
  if (TimeClient.isReady()) {
    _timeString = TimeClient.now().toString("%H:%M");
  }

  if (_millisSinceLastSideViewIndexChanged == 0 ||
      millis() - _millisSinceLastSideViewIndexChanged > 8 * 1000) {
    _millisSinceLastSideViewIndexChanged = millis();
    if (_sideViewIndex == 0) {
      _sideViewIndex = 1;
    } else {
      _sideViewIndex = 0;
    }
  }
}

void HomeView::didSelect() {
  Application.pushView(MainMenuView::getInstance());
}

void HomeView::render(CanvasContext *context) {
  _drawDateTime(context);
  _drawWeather(context);
  _drawStocks(context);
  if (ServiceClient.isLoading()) {
    if (!_blinking) {
      context->fillCircle(getClientWidth() / 2, 2, 2);
    }
  }
}

void HomeView::_drawDateTime(CanvasContext *context) {
  context->setTextAlign(TextAlign::RIGHT);

  if (TimeClient.isReady()) {
    // Date
    context->setFontSize(FontSize::NORMAL);
    String date = TimeClient.now().toString("%a %d");
    date.toUpperCase();
    context->drawString(date, getClientWidth(), 0);
  }

  // Time
  context->setFontSize(FontSize::H1);
  context->setTextAlign(TextAlign::RIGHT);
  context->drawString(_timeString.substring(0, 2), getClientWidth() - 35, 20);
  context->setTextAlign(TextAlign::LEFT);
  if (_blinking) {
    context->drawString(":", getClientWidth() - 33, 18);
  }
  context->drawString(_timeString.substring(3), getClientWidth() - 25, 20);
}

void HomeView::_drawWeather(CanvasContext *context) {
  WeatherForecast now = ServiceClient.getWeatherNow();
  WeatherForecast forecast = ServiceClient.getWeatherForecast(0);

  if (!forecast.day.equals("")) {
    if (_sideViewIndex == 0) {
      const int PADDING_LEFT = 6;

      context->setTextAlign(TextAlign::CENTER);
      context->setFontSize(FontSize::NORMAL);
      String text = String(forecast.lowTemp) + " / " + forecast.highTemp;
      context->drawString(text, PADDING_LEFT + 20, 0);

      context->setTextAlign(TextAlign::LEFT);
      context->setFont(Meteocons_Plain_42);
      context->drawString(now.dayCondCode, PADDING_LEFT, 11);
    } else {
      context->setTextAlign(TextAlign::CENTER);
      context->setFontSize(FontSize::NORMAL);
      String text = now.dayCond;
      text += "  " + String(forecast.lowTemp) + " / " + String(forecast.highTemp);
      context->drawString(text, getClientWidth() / 2, 52);
    }
  }
}

void HomeView::_drawStocks(CanvasContext *context) {
  Stock stock = ServiceClient.getStock(0);
  if (!stock.symbol.equals("")) {
    if (_sideViewIndex == 1) {
      const uint8_t PADDING_LEFT = 8;
      context->setTextAlign(TextAlign::CENTER);
      context->setFontSize(FontSize::NORMAL);
      context->drawString(String(abs(stock.changePercent)) + "%", PADDING_LEFT + 22, 0);

      context->setFontSize(FontSize::H2);
      context->setTextAlign(TextAlign::RIGHT);
      context->drawString(String((int)stock.price), PADDING_LEFT + 34, 27);
      context->setTextAlign(TextAlign::LEFT);
      context->setFontSize(FontSize::NORMAL);
      context->drawString("." + String((int)(stock.price * 100 - ((int)stock.price * 100))),
                          PADDING_LEFT + 34, 32);

      // Draw Triangle
      if (stock.changePercent > 0) {
        context->drawLine(3, 34, 0, 41);
        context->drawLine(3, 34, 6, 41);
        context->drawLine(0, 41, 6, 41);
        context->drawLine(3, 34, 3, 41);
        context->drawLine(3, 34, 2, 41);
        context->drawLine(3, 34, 4, 41);
      } else if (stock.changePercent < 0) {
        context->drawLine(3, 41, 2, 34);
        context->drawLine(3, 41, 3, 34);
        context->drawLine(3, 41, 4, 34);
        context->drawLine(3, 41, 0, 34);
        context->drawLine(3, 41, 6, 34);
        context->drawLine(0, 34, 6, 34);
      }
    } else {
      context->setTextAlign(TextAlign::CENTER);
      context->setFontSize(FontSize::NORMAL);
      String text = stock.symbol + "  " + stock.price + "  " + stock.changePercent + "%";
      context->drawString(text, getClientWidth() / 2, 52);
    }
  }
}
