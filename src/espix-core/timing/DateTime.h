#include <time.h>

struct DateTime {
  DateTime(long ticks, unsigned long offset = 8 * 60 * 60 * 1000) {
    _ticks = ticks;
    long localTime = ticks / 1000 + offset / 1000;
    _localTime = localtime(&localTime);
  }

  DateTime(struct tm *localTime) {
    _localTime = localTime;
  }

  int getFullYear() {
    return _localTime->tm_year;
  }

  int getMonth() {
    return _localTime->tm_mon;
  }

  int getDate() {
    return _localTime->tm_mday;
  }

  int getDay() {
    return _localTime->tm_wday;
  }

  int getHours() {
    return _localTime->tm_hour;
  }

  int getMinutes() {
    return _localTime->tm_min;
  }

  int getSeconds() {
    return _localTime->tm_sec;
  }

  int ticks() {
    return _ticks;
  }

  long _ticks;
  struct tm *_localTime;
};
