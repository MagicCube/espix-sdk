#pragma once

#include <Arduino.h>

#include "../devices/Keyboard.h"
#include "../drawing/CanvasContext.h"

class View {
public:
  View();
  ~View();

  CanvasContext *getCanvasContext();
  int getWidth();
  int getHeight();
  bool isDirty();
  void setDirty();
  unsigned long getLastUpdate();

  bool tryUpdate();
  void redraw(bool clearBeforeRendering = false);

  // Lifecycle
  virtual void willMount();
  virtual void render(CanvasContext *context);
  virtual void didMount();
  virtual bool shouldUpdate();
  virtual void update();
  virtual void willUnmount();

  // Event Handlers
  virtual void handleKeyPress(KeyCode keyCode);
  virtual void handleScroll(int delta);

private:
  CanvasContext *_CanvasContext;
  bool _dirty = false;
  unsigned long _lastUpdate = 0;
};
