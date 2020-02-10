#pragma once

#include <Arduino.h>

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#include "./models/Stock.h"
#include "./models/WeatherForecast.h"

class ServiceClientClass {
public:
  void begin();
  void update();

  WeatherForecast getWeatherForecast(uint8_t day);
  Stock getStock(uint8_t index);

private:
  HTTPClient _httpClient;
  Stock _stocks[1] = { {
    .symbol = "",
    .price = 0,
    .change = 0,
    .changePercent = 0
  } };
  WeatherForecast _weatherForecast[3] = { {
    .day = "",
    .dayCode = "",
    .night = "",
    .nightCode = "",
    .highTemp = 0,
    .lowTemp = 0
  }, {
    .day = "",
    .dayCode = "",
    .night = "",
    .nightCode = "",
    .highTemp = 0,
    .lowTemp = 0
  }, {
    .day = "",
    .dayCode = "",
    .night = "",
    .nightCode = "",
    .highTemp = 0,
    .lowTemp = 0
  } };

  void _updateStocks(DynamicJsonDocument doc);
  void _updateWeatherForecast(DynamicJsonDocument doc);
};

extern ServiceClientClass ServiceClient;
