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

  // Returns whether the navigation stack can be popped.
  bool canPop();

  // Pushes a specific view to the navigation stack and display it.
  void pushView(View *view, TransitionOptions options = TRANSITION_OPTIONS_RIGHT);

  // Pops the view on the top of the navigation stack and return it back.
  // Returns `NULL` if the navigation stack is empty.
  View *popView(TransitionOptions options = TRANSITION_OPTIONS_LEFT);

private:
  View *_rootView = NULL;
  Stack<View *> _navigationStack;
};
