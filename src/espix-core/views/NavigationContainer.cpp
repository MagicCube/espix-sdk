#include "NavigationContainer.h"

NavigationContainer::NavigationContainer() : ViewContainer() {
}

void NavigationContainer::pushView(View *view, TransitionOptions options) {
  _navigationStack.push(view);
  setCurrentView(view, options);
}

View *NavigationContainer::popView(TransitionOptions options) {
  if (_navigationStack.isEmpty()) {
    return NULL;
  }
  View *view = _navigationStack.pop();
  setCurrentView(view, options);
  return view;
}
