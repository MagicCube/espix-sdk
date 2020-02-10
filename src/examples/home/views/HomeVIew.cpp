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

  WeatherForecast forecast = ServiceClient.getWeatherForecast(0);

  if (!forecast.day.equals("")) {
    const int PADDING_LEFT = 6;
    context->setTextAlign(TextAlign::LEFT);
    context->setFont(Meteocons_Plain_42);
    String weatherIcon = "Q";
    context->drawString(weatherIcon, PADDING_LEFT, 10);

    context->setTextAlign(TextAlign::CENTER);
    context->setFontSize(FontSize::NORMAL);
    String text = String(forecast.lowTemp) + " / " + forecast.highTemp;
    context->drawString(text, PADDING_LEFT + 20, 0);
  }
}

void HomeView::_drawStocks(CanvasContext *context) {
  Stock stock = ServiceClient.getStock(0);
  if (!stock.symbol.equals("")) {
    context->setTextAlign(TextAlign::CENTER);
    context->setFontSize(FontSize::NORMAL);
    // context->drawString("BABA  216.53  -1.98%", getClientWidth() / 2, 54);
    String text = stock.symbol + "  " + stock.price + "  " + stock.changePercent + "%";
    context->drawString(text, getClientWidth() / 2, 54);
  }
}
