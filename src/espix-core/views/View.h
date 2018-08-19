#pragma once

#include <Arduino.h>

#include "../drawings/DrawingContext.h"
#include "../hmis/Keyboard.h"

#include "ViewUpdateOptions.h"

class View {
public:
  View();

  DrawingContext *getDrawingContext();
  int getWidth();
  int getHeight();
  bool isDirty();
  void setDirty();
  unsigned long getLastUpdate();

  bool tryUpdate(ViewUpdateOptions options);
  void redraw(bool clearBeforeRendering = false);

  // Lifecycle
  virtual void willMount();
  virtual void render(DrawingContext *context);
  virtual void didMount();
  virtual bool shouldUpdate(ViewUpdateOptions options);
  virtual void update(ViewUpdateOptions options);
  virtual void willUnmount();

  // Event Handlers
  virtual void handleKeyPress(KeyCode keyCode);

private:
  DrawingContext *_drawingContext;
  bool _dirty;
  unsigned long _lastUpdate;
};
