#pragma once

#include <Arduino.h>

#include "../devices/Keyboard.h"
#include "../drawing/DrawingContext.h"

class View {
public:
  View();
  ~View();

  DrawingContext *getDrawingContext();
  int getWidth();
  int getHeight();
  bool isDirty();
  void setDirty();
  unsigned long getLastUpdate();

  bool tryUpdate();
  void redraw(bool clearBeforeRendering = false);

  // Lifecycle
  virtual void willMount();
  virtual void render(DrawingContext *context);
  virtual void didMount();
  virtual bool shouldUpdate();
  virtual void update();
  virtual void willUnmount();

  // Event Handlers
  virtual void handleKeyPress(KeyCode keyCode);

private:
  DrawingContext *_drawingContext;
  bool _dirty = false;
  unsigned long _lastUpdate = 0;
};
