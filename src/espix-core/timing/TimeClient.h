#pragma once

#include <Arduino.h>

#include <NTPClient.h>

class TimeClient {
public:
  static TimeClient *getInstance();
  unsigned long getTime();
  String getFormattedTime();

  void begin();
  void update();

private:
  TimeClient();
  NTPClient *_client;
  bool _hasBegun;
};
