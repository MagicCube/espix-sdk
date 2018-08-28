#include "NavigationContainer.h"

NavigationContainer::NavigationContainer() : ViewContainer() {
}

void NavigationContainer::pushView(View *view, bool withTransition) {
  _navigationStack.push(view);
  TransitionOptions options = withTransition && !_navigationStack.isEmpty()
                                  ? TransitionOptions(TransitionDirection::LEFT)
                                  : TRANSITION_OPTIONS_NONE;
  setCurrentView(view, options);
}

View *NavigationContainer::popView(bool withTransition) {
  if (_navigationStack.isEmpty()) {
    return NULL;
  }
  View *view = _navigationStack.pop();
  TransitionOptions options =
      withTransition ? TransitionOptions(TransitionDirection::RIGHT) : TRANSITION_OPTIONS_NONE;
  setCurrentView(view, options);
  return view;
}
