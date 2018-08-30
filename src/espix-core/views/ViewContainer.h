#pragma once

#include <Arduino.h>

#include "../transitions/Transition.h"

#include "View.h"

// Represents a container of single view.
class ViewContainer : public View {
public:
  // Creates a new instance of the ViewContainer class.
  ViewContainer();

  // Gets the current active view of the container.
  // There's only one active view at one time.
  View *getCurrentView();

  // Gets a bool indicates whether the container is transitioning by using `setCurrentView()`.
  bool isTransitioning();


  // Overrides
  void setBounds(Rectangle bounds);
  void setPaddings(Thickness paddings);
  bool shouldUpdate();
  void update();
  void render(CanvasContext *context);
  void didSelect();
  void handleKeyPress(KeyEventArgs e);
  void handleScroll(ScrollEventArgs e);

protected:
  void setCurrentView(View *view, TransitionOptions transitionOptions = TRANSITION_OPTIONS_NONE);

private:
  void _mountView(View *view, int offsetX = 0, int offsetY = 0);
  void _unmountView();
  void _updateTransition();

  int _viewOffset = 0;
  int _unmountingViewOffset = 0;
  View *_currentView;
  View *_unmountingView;
  Transition _viewTransition;
};
