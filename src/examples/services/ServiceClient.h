#pragma once

#include <Arduino.h>

#include <ArduinoJson.h>
#include <asyncHTTPrequest.h>

#include "../../espix-core.h"

#include "../config.h"

#include "./models/Stock.h"
#include "./models/WeatherForecast.h"

class ServiceClientClass {
public:
  void begin();
  void update();

  WeatherForecast getWeatherNow();
  WeatherForecast getWeatherForecast(uint8_t day);
  Stock getStock(uint8_t index);

  void handleCallback(asyncHTTPrequest *request);

private:
  unsigned long UPDATE_INTERVAL = 60 * 60 * 1000;
  unsigned long UPDATE_TIMEOUT = 60 * 1000;

  bool _initialized = false;
  unsigned long _lastUpdateTime = 0;

  asyncHTTPrequest _ajax;

#ifndef DEBUG_LOCAL
  Stock _stocks[1] = {{.symbol = "", .price = 0, .change = 0, .changePercent = 0}};
  WeatherForecast _weatherForecast[4] = {{.day = "",
                                          .dayCond = "",
                                          .dayCondCode = "",
                                          .nightCond = "",
                                          .nightCondCode = "",
                                          .highTemp = 0,
                                          .lowTemp = 0},
                                         {.day = "",
                                          .dayCond = "",
                                          .dayCondCode = "",
                                          .nightCond = "",
                                          .nightCondCode = "",
                                          .highTemp = 0,
                                          .lowTemp = 0},
                                         {.day = "",
                                          .dayCond = "",
                                          .dayCondCode = "",
                                          .nightCond = "",
                                          .nightCondCode = "",
                                          .highTemp = 0,
                                          .lowTemp = 0},
                                         {.day = "",
                                          .dayCond = "",
                                          .dayCondCode = "",
                                          .nightCond = "",
                                          .nightCondCode = "",
                                          .highTemp = 0,
                                          .lowTemp = 0}};
#else
  Stock _stocks[1] = {{.symbol = "BABA", .price = 320.34, .change = 5.42, .changePercent = 4.21}};
  WeatherForecast _weatherForecast[4] = {{.day = "MON",
                                          .dayCond = "Sunny",
                                          .dayCondCode = "S",
                                          .nightCond = "",
                                          .nightCondCode = "",
                                          .highTemp = 8,
                                          .lowTemp = 8},
                                         {.day = "MON",
                                          .dayCond = "Rain",
                                          .dayCondCode = "Q",
                                          .nightCond = "",
                                          .nightCondCode = "",
                                          .highTemp = 33,
                                          .lowTemp = 30},
                                         {.day = "TUE",
                                          .dayCond = "Snow",
                                          .dayCondCode = "W",
                                          .nightCond = "",
                                          .nightCondCode = "",
                                          .highTemp = -12,
                                          .lowTemp = -4},
                                         {.day = "WEB",
                                          .dayCond = "Fluries",
                                          .dayCondCode = "F",
                                          .nightCond = "",
                                          .nightCondCode = "",
                                          .highTemp = 8,
                                          .lowTemp = 4}};
#endif
  void _extractStock(DynamicJsonDocument doc);
  void _extractWeather(DynamicJsonDocument doc);
};

extern ServiceClientClass ServiceClient;
