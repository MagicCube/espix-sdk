#pragma once

#include <Arduino.h>

struct WeatherForecast {
  String day;
  String dayCode;
  String night;
  String nightCode;
  int highTemp;
  int lowTemp;
};
