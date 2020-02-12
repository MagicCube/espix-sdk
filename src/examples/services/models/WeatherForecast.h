#pragma once

#include <Arduino.h>

struct WeatherForecast {
  String day;
  String dayCond;
  String dayCondCode;
  String nightCond;
  String nightCondCode;
  int highTemp;
  int lowTemp;
};
