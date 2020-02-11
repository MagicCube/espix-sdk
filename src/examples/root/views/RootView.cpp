#include "RootView.h"

#include "../../home/views/HomeView.h"
#include "../../weather/views/WeatherTodayView.h"

RootView::RootView() : CarouselContainer() {
  addSubviews({HomeView::getInstance()});
}
