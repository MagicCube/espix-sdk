#include "RootView.h"

#include "../../home/views/HomeView.h"
#include "../../weather/views/WeatherTodayView.h"
#include "../../weather/views/WeatherForecastView.h"

RootView::RootView() : CarouselContainer() {
  addSubviews({HomeView::getInstance(), WeatherTodayView::getInstance()});
}
