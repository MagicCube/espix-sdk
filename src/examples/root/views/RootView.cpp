#include "RootView.h"

#include "../../home/views/HomeView.h"
#include "../../stock/views/StockView.h"
#include "../../weather/views/WeatherForecastView.h"

RootView::RootView() : CarouselContainer() {
  addSubviews({
    HomeView::getInstance(),
    WeatherForecastView::getInstance(),
    StockView::getInstance(),
  });
}
