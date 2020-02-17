#include "ServiceClient.h"

void _handleReadyStateChange(void *optParm, asyncHTTPrequest *request, int readyState);

void ServiceClientClass::begin() {
  _ajax.onReadyStateChange(_handleReadyStateChange);
  _ajax.setTimeout(UPDATE_TIMEOUT);
  _initialized = true;
}

void ServiceClientClass::update() {
  if (!_initialized)
    return;

  if (_ajax.readyState() == 0 || _ajax.readyState() == 4) {
    if (_lastUpdateTime == 0 || (millis() - _lastUpdateTime > UPDATE_INTERVAL)) {
      // Routine Update
      _lastUpdateTime = millis();
      Serial.println("Fetching from my-cloudflare-services.you-fm.workers.dev...");
      _isLoading = true;
      _ajax.open("GET", "http://my-cloudflare-services.you-fm.workers.dev/");
      _ajax.send();
    } else {
      auto now = TimeClient.now();
      if ((now.getHours() == 22 && now.getMinutes() >= 29) || now.getHours() > 22) {
        // During the night, when New York time is after 9:30am
        if (millis() - _lastUpdateTime > 1.5 * 60 * 1000) {
          _lastUpdateTime = millis();
          Serial.println("Fetching from my-cloudflare-services.you-fm.workers.dev/stock...");
          _isLoading = true;
          _ajax.open("GET", "http://my-cloudflare-services.you-fm.workers.dev/stock");
          _ajax.send();
        }
      }
    }
  }
}

bool ServiceClientClass::isLoading() {
  return _isLoading;
}

Stock ServiceClientClass::getStock(uint8_t index) {
  return _stocks[0];
}

WeatherForecast ServiceClientClass::getWeatherNow() {
  return _weatherForecast[0];
}

WeatherForecast ServiceClientClass::getWeatherForecast(uint8_t day) {
  return _weatherForecast[day + 1];
}

void ServiceClientClass::handleCallback(asyncHTTPrequest *request) {
  _isLoading = false;

  Serial.print("Response HTTP Code: ");
  Serial.println(request->responseHTTPcode());
  Serial.println();

  if (request->responseHTTPcode() == 200) {
    DynamicJsonDocument json(2048);
    deserializeJson(json, request->responseText());
    if (json.containsKey("stock")) {
      ServiceClient._extractStock(json);
    }
    if (json.containsKey("weather")) {
      ServiceClient._extractWeather(json);
    }
  }
}

void ServiceClientClass::_extractStock(DynamicJsonDocument json) {
  auto first = json["stock"];
  _stocks[0].symbol = first["symbol"].as<char *>();
  _stocks[0].price = first["price"];
  _stocks[0].change = first["change"];
  _stocks[0].changePercent = first["changePercent"];
}

void ServiceClientClass::_extractWeather(DynamicJsonDocument json) {
  for (int i = 0; i < 4; i++) {
    auto forecast = json["weather"][i];
    _weatherForecast[i].day = forecast["day"].as<char *>();
    _weatherForecast[i].dayCond = forecast["dayCond"].as<char *>();
    _weatherForecast[i].dayCondCode = forecast["dayCondCode"].as<char *>();
    _weatherForecast[i].nightCond = forecast["nightCond"].as<char *>();
    _weatherForecast[i].nightCondCode = forecast["nightCondCode"].as<char *>();
    _weatherForecast[i].highTemp = forecast["highTemp"];
    _weatherForecast[i].lowTemp = forecast["lowTemp"];
  }
}

void _handleReadyStateChange(void *optParm, asyncHTTPrequest *request, int readyState) {
  if (readyState == 4) {
    ServiceClient.handleCallback(request);
  }
}

ServiceClientClass ServiceClient;
