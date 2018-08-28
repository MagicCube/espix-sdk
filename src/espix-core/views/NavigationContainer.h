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
  void pushView(View *view, bool withTransition = true);

  // Pops the view on the top of the navigation stack and return it back.
  // Returns `NULL` if the navigation stack is empty.
  View *popView(bool withTransition = true);

private:
  Stack<View *> _navigationStack;
};
