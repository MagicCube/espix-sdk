#pragma once

#include <Arduino.h>

struct Stock {
  String symbol;
  float price;
  float change;
  float changePercent;
};
