#pragma once

#include <Arduino.h>

struct MenuItem {
  MenuItem(String p_text) : key(p_text), text(p_text) {
  }

  MenuItem(String p_key, String p_text) : key(p_key), text(p_text) {
  }

  String key;
  String text;
};
