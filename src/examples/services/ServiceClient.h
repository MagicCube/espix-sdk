#pragma once

#include <Arduino.h>

#include <ArduinoJson.h>
#include <asyncHTTPrequest.h>

#include "./models/Stock.h"
#include "./models/WeatherForecast.h"

class ServiceClientClass {
public:
  void begin();
  void update();

  WeatherForecast getWeatherForecast(uint8_t day);
  Stock getStock(uint8_t index);

  void handleCallback(asyncHTTPrequest *request);

private:
  unsigned long UPDATE_INTERVAL = 60 * 60 * 1000;
  unsigned long UPDATE_TIMEOUT = 60 * 1000;

  bool _initialized = false;
  unsigned long _lastUpdateTime = 0;

  asyncHTTPrequest _ajax;

  Stock _stocks[1] = { {
    .symbol = "",
    .price = 0,
    .change = 0,
    .changePercent = 0
  } };

  WeatherForecast _weatherForecast[3] = { {
    .day = "",
    .dayCond = "",
    .dayCondCode = "",
    .nightCond = "",
    .nightCondCode = "",
    .highTemp = 0,
    .lowTemp = 0
  }, {
    .day = "",
    .dayCond = "",
    .dayCondCode = "",
    .nightCond = "",
    .nightCondCode = "",
    .highTemp = 0,
    .lowTemp = 0
  }, {
    .day = "",
    .dayCond = "",
    .dayCondCode = "",
    .nightCond = "",
    .nightCondCode = "",
    .highTemp = 0,
    .lowTemp = 0
  } };

  void _extractStock(DynamicJsonDocument doc);
  void _extractForecast(DynamicJsonDocument doc);
};

extern ServiceClientClass ServiceClient;
