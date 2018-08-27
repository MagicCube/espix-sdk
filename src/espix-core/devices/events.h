#pragma once

#include <Arduino.h>

#include "KeyCode.h"

using namespace std;

typedef function<void(int)> ScrollEventHandler;
typedef function<void(KeyCode)> KeyEventHandler;
