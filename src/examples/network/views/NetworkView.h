#pragma once

#include <Arduino.h>

#include <espix-core.h>

class NetworkView : public View {
public:
  static NetworkView *getInstance();

  void willMount();
  void willUnmount();

  void render(CanvasContext *context);
};
