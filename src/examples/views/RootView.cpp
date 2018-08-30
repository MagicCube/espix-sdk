#include "RootView.h"

#include "../clock/views/ClockView.h"
#include "../weather/views/WeatherTodayView.h"

RootView::RootView() : CarouselContainer() {
  addSubviews({ClockView::getInstance(), WeatherTodayView::getInstance()});
}
