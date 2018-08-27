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
  void setWidth(int width);
  int getHeight();
  void setHeight(int height);
  int getLeft();
  void setLeft(int left);
  int getTop();
  void setTop(int top);
  bool isDirty();
  void setDirty();
  unsigned long getLastUpdate();

  void resizeTo(int width, int height);
  void moveTo(int left, int top);
  void setBounds(int left, int top, int width, int height);

  bool tryUpdate();
  void redraw(Canvas *canvas, bool clearBeforeRendering = false);

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
  CanvasContext *_canvasContext;
  bool _dirty = false;
  unsigned long _lastUpdate = 0;
};
