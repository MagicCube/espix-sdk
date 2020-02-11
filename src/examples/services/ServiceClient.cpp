#include "ServiceClient.h"

void _handleReadyStateChange(void *optParm, asyncHTTPrequest *request, int readyState);

void ServiceClientClass::begin() {
  _ajax.onReadyStateChange(_handleReadyStateChange);
  _ajax.setTimeout(UPDATE_TIMEOUT);
  _initialized = true;
}

void ServiceClientClass::update() {
  if (!_initialized) return;

  if (_lastUpdateTime == 0 || (millis() - _lastUpdateTime > UPDATE_INTERVAL)) {
    if (_ajax.readyState() == 0 || _ajax.readyState() == 4) {
      _lastUpdateTime = millis();
      Serial.println("Fetching from my-cloudflare-services.you-fm.workers.dev...");
      _ajax.open("GET", "http://my-cloudflare-services.you-fm.workers.dev/");
      _ajax.send();
    }
  }
}

Stock ServiceClientClass::getStock(uint8_t index) {
  return _stocks[0];
}

WeatherForecast ServiceClientClass::getWeatherForecast(uint8_t day) {
  return _weatherForecast[day];
}

void ServiceClientClass::handleCallback(asyncHTTPrequest *request) {
  Serial.print("Response HTTP Code: ");
  Serial.println(request->responseHTTPcode());
  Serial.println();

  if (request->responseHTTPcode() == 200) {
    DynamicJsonDocument json(1024);
    deserializeJson(json, request->responseText());
    ServiceClient._extractStock(json);
    ServiceClient._extractForecast(json);
  }
}

void ServiceClientClass::_extractStock(DynamicJsonDocument json) {
  auto first = json["stock"];
  _stocks[0].symbol = first["symbol"].as<char *>();
  _stocks[0].price = first["price"];
  _stocks[0].change = first["change"];
  _stocks[0].changePercent = first["changePercent"];
}

void ServiceClientClass::_extractForecast(DynamicJsonDocument json) {
  for (int i = 0; i < 3; i++) {
    auto forecast = json["weather"][0];
    _weatherForecast[i].day = forecast["day"].as<char *>();
    _weatherForecast[i].dayCode = forecast["dayCode"].as<char *>();
    _weatherForecast[i].night = forecast["night"].as<char *>();
    _weatherForecast[i].nightCode = forecast["nightCode"].as<char *>();
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
