#pragma once

#include <Arduino.h>

#include "../drawings/DrawingContext.h"
#include "../hmis/Keyboard.h"

#include "ViewUpdateOptions.h"

class View {
public:
  View();

  DrawingContext *getDrawingContext();

  void redraw(bool clearBeforeRendering = false);
  int getWidth();
  int getHeight();

  // Lifecycle
  virtual void willMount();
  virtual void render(DrawingContext *context);
  virtual void didMount();
  virtual bool shouldUpdate(ViewUpdateOptions options);
  virtual void update(ViewUpdateOptions options);
  virtual void willUnmount();

  // Event Handlers
  virtual void handleKeyPress(KeyCode keyCode);

protected:
  unsigned long getLastUpdate();
  bool isDirty();
  void setDirty();
  bool tryUpdate(ViewUpdateOptions options);

private:
  DrawingContext *_drawingContext;
  bool _dirty;
  unsigned long _lastUpdate;
};
