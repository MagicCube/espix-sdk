#pragma once

#include <Arduino.h>

#include "../devices/Keyboard.h"
#include "../drawing/CanvasContext.h"
#include "../drawing/Thickness.h"

class ViewContainer;

// Represents a part or full of screen which makes up an application's user interface.
class View {
public:
  // Initailize a new instance of the View class.
  View();

  // Gets or sets the parent of the view.
  ViewContainer *getParentView();
  void setParentView(ViewContainer *parentView);

  // Gets the canvas of the view.
  // Can be derived from its parent or ancestor.
  Canvas *getCanvas();
  void setCanvas(Canvas *canvas);

  // Gets or sets the width of the view.
  int getWidth();
  void setWidth(int width);

  // Gets or sets the height of the view.
  int getHeight();
  void setHeight(int height);

  // Gets or sets the left of the view.
  int getLeft();
  void setLeft(int left);

  // Gets or sets the top of the view.
  int getTop();
  void setTop(int top);

  // Gets or sets a `Rectangle` object which represents the bounds of the view.
  Rectangle getBounds();
  void setBounds(Rectangle bounds);

  // Gets the left of the client area of the view.
  int getClientLeft();

  // Gets the top of the client area of the view.
  int getClientTop();

  // Gets the width of the client area of the view.
  int getClientWidth();

  // Gets the height of the client area of the view.
  int getClientHeight();

  // Gets a `Rectangle` object which represents the bounds of the view's client area.
  Rectangle getClientBounds();

  // Gets or sets a `Thickness` object which represents the paddings of the view.
  Thickness getPaddings();
  void setPaddings(Thickness paddings);
  void setPaddings(int all);
  void setPaddings(int horizontal, int vertical);
  void setPaddings(int left, int top, int right, int bottom);

  // Gets left side of paddings of the view.
  int getPaddingLeft();

  // Gets right side of paddings of the view.
  int getPaddingRight();

  // Gets top side of paddings of the view.
  int getPaddingTop();

  // Gets bottom side of paddings of the view.
  int getPaddingBottom();

  // Gets a boolean value indicates whether the view is dirty.
  // Sets it true by invoking `setDirty()`.
  bool isDirty();

  // Marks the view as dirty. So it will be redrawed in the next update.
  void setDirty();

  // Gets the time of last update.
  unsigned long getLastUpdate();

  // Resizes the view to the specific size.
  void resizeTo(int width, int height);

  // Moves the view to the specific location.
  void moveTo(int left, int top);

  // Updates the view if it is dirty or `shouldUpdate()` is true.
  // It also change the value of `lastUpdate` which you can retain from `getLastUpdate()`.
  bool tryUpdate();

  // Redraws the view.
  void redraw();

  // Trigger didSelect();
  // Please avoid to call this method directly from your program.
  void select();

  /*************************************/
  /* Lifecyle of View                  */
  /*************************************/
  // Overrides if you want to do something before the view is mountied.
  // Please avoid to call this method directly from your program.
  virtual void willMount();

  // Overrides if you want to customize rendering.
  // Please avoid to call this method directly from your program.
  virtual void render(CanvasContext *context);

  // Overrides if you want to do something after the view has been mounted.
  // Please avoid to call this method directly from your program.
  virtual void didMount();

  // Overrides if you want to determine when to update.
  // Please avoid to call this method directly from your program.
  virtual bool shouldUpdate();

  // Overrides if you want to customize updating.
  // Please avoid to call this method directly from your program.
  virtual void update();

  // Overrides if you want to do something after the view is selected.
  // Occurs after the user press Enter key.
  // Please avoid to call this method directly from your program.
  virtual void didSelect();

  // Overrides if you want to do something before the view is unmounted.
  // Please avoid to call this method directly from your program.
  virtual void willUnmount();


  /*************************************/
  /* Event Handlers                    */
  /*************************************/
  // Overrides if you want to capture key press event.
  // Please avoid to call this method directly from your program.
  virtual void handleKeyPress(KeyEventArgs e);

  // Overrides if you want to capture scroll event.
  // Please avoid to call this method directly from your program.
  virtual void handleScroll(ScrollEventArgs e);

private:
  Canvas *_canvas;
  ViewContainer *_parentView = NULL;

  Rectangle _bounds;
  Thickness _paddings;

  bool _dirty = false;
  unsigned long _lastUpdate = 0;
};
