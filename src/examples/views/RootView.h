#include <Arduino.h>

#include "../../espix-core.h"

#include "../clock/views/ClockView.h"
#include "../weather/views/WeatherTodayView.h"

class RootView : public CarouselContainer {
public:
  RootView() : CarouselContainer() {
    addSubviews({new ClockView(), new WeatherTodayView()});
  }

  void didMount() {
    if (getCurrentView() == NULL) {
      showFirstSubview();
    }
  }
};
