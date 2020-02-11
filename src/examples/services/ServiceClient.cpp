#include "ServiceClient.h"

void ServiceClientClass::begin() {
  _httpClient.setTimeout(60 * 1000);
  update();
}

void ServiceClientClass::update() {
  long startTime = millis();
  Serial.println("Fetching...");
  _httpClient.begin("http://my-cloudflare-services.you-fm.workers.dev/");
  int code = _httpClient.GET();
  if (code == 200) {
    Serial.print("Done in ");
    Serial.print((millis() - startTime) / 100.0);
    Serial.println(" sec");
    DynamicJsonDocument json(1024);
    deserializeJson(json, _httpClient.getString());
    _updateStocks(json);
    _updateWeatherForecast(json);
  } else {
    Serial.print("HTTP Error: ");
    Serial.println(code);
  }
}

Stock ServiceClientClass::getStock(uint8_t index) {
  return _stocks[0];
}

WeatherForecast ServiceClientClass::getWeatherForecast(uint8_t day) {
  return _weatherForecast[day];
}

void ServiceClientClass::_updateStocks(DynamicJsonDocument json) {
  auto first = json["stock"];
  _stocks[0].symbol = first["symbol"].as<char *>();
  _stocks[0].price = first["price"];
  _stocks[0].change = first["change"];
  _stocks[0].changePercent = first["changePercent"];
}

void ServiceClientClass::_updateWeatherForecast(DynamicJsonDocument json) {
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

ServiceClientClass ServiceClient;
