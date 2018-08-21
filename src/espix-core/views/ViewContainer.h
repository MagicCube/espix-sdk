#pragma once

#include <Arduino.h>

#include "../transitions/Transition.h"

#include "View.h"

class ViewContainer : public View {
public:
  ViewContainer();
  View *getView();
  void setView(View *view, TransitionOptions transitionOptions = TRANSITION_OPTIONS_NONE);
  bool isTransitioning();

  bool shouldUpdate();
  void update();
  void render(DrawingContext *context);
  void handleKeyPress(KeyCode keyCode);

private:
  void _mountView(View *view, int offsetX = 0, int offsetY = 0);

  int _viewOffset = 0;
  int _unmountingViewOffset = 0;
  View *_view;
  View *_unmountingView;
  Transition *_viewTransition;
};
