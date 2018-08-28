#pragma once

#include <Arduino.h>

#include "ViewContainer.h"

#include "../collections/Stack.h"

// Represents a navigation view container.
class NavigationContainer : public ViewContainer {
public:
  // Creates an instance of the NavigationContainer class.
  NavigationContainer();

  // Pushes a specific view to the navigation stack and display it.
  void pushView(View *view, TransitionOptions options = TRANSITION_OPTIONS_RIGHT);

  // Pops the view on the top of the navigation stack and return it back.
  // Returns `NULL` if the navigation stack is empty.
  View *popView(TransitionOptions options = TRANSITION_OPTIONS_LEFT);

private:
  Stack<View *> _navigationStack;
};
