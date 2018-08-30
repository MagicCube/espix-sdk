#pragma once

#include <Arduino.h>

#include "ViewContainer.h"

#include "../collections/Stack.h"

// Represents a navigation view container.
class NavigationContainer : public ViewContainer {
public:
  // Creates an instance of the NavigationContainer class.
  NavigationContainer();

  // Gets the root view of the navagation container.
  View *getRootView();

  // Pops all the views in the navigation stack, and sets the root view of the navagation container.
  void setRootView(View *view, TransitionOptions options = TRANSITION_OPTIONS_NONE);

  // Gets or sets the status bar view of navigation container.
  // Set to NULL if you don't want to use status bar.
  // Try StatusBar in espix-design if you don't want to implement one by yourself.
  View *getStatusView();
  void setStatusView(View *view);

  // Show or hide status view.
  void showStatusView();
  void hideStatusView();

  // Returns whether the navigation stack can be popped.
  bool canPop();

  // Pushes a specific view to the navigation stack and display it.
  void pushView(View *view, TransitionOptions options = TRANSITION_OPTIONS_LEFT);

  // Pops the view on the top of the navigation stack and return it back.
  // Returns `NULL` if the navigation stack is empty.
  View *popView(TransitionOptions options = TRANSITION_OPTIONS_RIGHT);

  bool shouldUpdate();
  void update();
  void render(CanvasContext *context);
  void handleKeyPress(KeyEventArgs e);

private:
  void _renderIndicators(CanvasContext *context);

  bool _statusViewVisible = false;
  View *_statusView = NULL;
  View *_rootView = NULL;
  Stack<View *> _navigationStack;
};
