#pragma once

#include <Arduino.h>

#include "../devices/Keyboard.h"
#include "../drawing/CanvasContext.h"

class View {
public:
  View();
  ~View();

  View *getParentView();
  void setParentView(View *parentView);

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
  void redraw(CanvasContext *canvasContext, bool clearBeforeRendering = false) {
    redraw(canvasContext->getCanvas(), clearBeforeRendering);
  }

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
  View *_parentView;
  CanvasContext *_canvasContext;

  int _left = 0;
  int _top = 0;
  int _width = 0;
  int _height = 0;

  bool _dirty = false;
  unsigned long _lastUpdate = 0;
};
