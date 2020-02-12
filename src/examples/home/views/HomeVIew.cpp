#include "HomeView.h"

#include "HomeMenuView.h"

#include "../../services/ServiceClient.h"

#include "../../weather/assets/meteocons-font.h"

HomeView::HomeView() : View() {
}

HomeView *HomeView::getInstance() {
  static HomeView instance;
  return &instance;
}

void HomeView::willMount() {
  Application.hideStatusView();
}

void HomeView::willUnmount() {
  Application.showStatusView();
}

bool HomeView::shouldUpdate() {
  if (isDirty()) {
    return true;
  }
  if (millis() - getLastUpdate() > 1000) {
    return true;
  }
  if (millis() - _millisSinceLastSideViewIndexChanged > 8 * 1000) {
    _millisSinceLastSideViewIndexChanged = millis();
    if (_sideViewIndex == 0) {
      _sideViewIndex = 1;
    } else {
      _sideViewIndex = 0;
    }
  }
  return false;
}

void HomeView::update() {
  if (TimeClient.isReady()) {
    _timeString = TimeClient.getLocalTimeShortStrig();
  }
}

void HomeView::didSelect() {
  // Application.pushView(HomeMenuView::getInstance());
}

void HomeView::render(CanvasContext *context) {
  _drawDateTime(context);
  _drawWeather(context);
  _drawStocks(context);
}

void HomeView::_drawDateTime(CanvasContext *context) {
  const int PADDING_RIGHT = 6;

  context->setTextAlign(TextAlign::RIGHT);

  // Date
  context->setFontSize(FontSize::NORMAL);
  context->drawString(TimeClient.getLocalDateShortString(), getClientWidth() - PADDING_RIGHT, 0);

  // Time
  context->setFontSize(FontSize::H1);
  context->drawString(_timeString, getClientWidth() - PADDING_RIGHT, 14);
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
      context->drawString(now.dayCondCode, PADDING_LEFT, 10);
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
      context->drawString((stock.changePercent > 0 ? "+" : "") + String(stock.changePercent) + "%",
                          PADDING_LEFT + 20, 0);

      context->setFontSize(FontSize::H2);
      context->drawString("$" + String(stock.price), PADDING_LEFT + 20, 20);
    } else {
      context->setTextAlign(TextAlign::CENTER);
      context->setFontSize(FontSize::NORMAL);
      String text = stock.symbol + "  " + stock.price + "  " + stock.changePercent + "%";
      context->drawString(text, getClientWidth() / 2, 52);
    }
  }
}
