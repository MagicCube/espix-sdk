#include "NavigationContainer.h"

NavigationContainer::NavigationContainer() : ViewContainer() {
}

View *NavigationContainer::getRootView() {
  return _rootView;
}

void NavigationContainer::setRootView(View *view, TransitionOptions options) {
  _navigationStack.clear();
  _rootView = view;
  setCurrentView(view, options);
}

View *NavigationContainer::getStatusView() {
  return _statusView;
}

void NavigationContainer::setStatusView(View *view) {
  _statusView = view;
  if (_statusView) {
    _statusView->setParentView(this);
    showStatusView();
  } else {
    hideStatusView();
  }
}

void NavigationContainer::showStatusView() {
  _statusViewVisible = true;
  _statusView->setWidth(getWidth());
  _statusView->setTop(-_statusView->getHeight() - 1);
  setPaddings(Thickness(0, _statusView->getHeight() + 1, 0, 0));
}

void NavigationContainer::hideStatusView() {
  _statusViewVisible = false;
  setPaddings(Thickness(0));
}

bool NavigationContainer::canPop() {
  return !_navigationStack.isEmpty();
}

void NavigationContainer::pushView(View *view, TransitionOptions options) {
  _navigationStack.push(view);
  setCurrentView(view, options);
}

View *NavigationContainer::popView(TransitionOptions options) {
  if (!canPop()) {
    return NULL;
  }
  View *view = _navigationStack.pop();
  if (!_navigationStack.isEmpty()) {
    setCurrentView(_navigationStack.top(), options);
  } else {
    setCurrentView(getRootView(), options);
  }
  return view;
}

bool NavigationContainer::shouldUpdate() {
  bool result = ViewContainer::shouldUpdate();
  if (result) {
    return result;
  }
  if (_statusView && _statusViewVisible) {
    return _statusView->shouldUpdate();
  } else {
    return false;
  }
}

void NavigationContainer::update() {
  ViewContainer::update();
  if (_statusView && _statusViewVisible) {
    _statusView->tryUpdate();
  }
}

void NavigationContainer::render(CanvasContext *context) {
  ViewContainer::render(context);
  if (_statusView && _statusViewVisible) {
    _statusView->redraw();
    context->drawHorizontalLine(0, -2);
  }
}

void NavigationContainer::handleKeyPress(KeyEventArgs e) {
  switch (e.keyCode) {
  case KEY_ENTER:
    if (getCurrentView()) {
      getCurrentView()->select();
    }
    break;
  case KEY_ESC:
    popView();
    break;
  default:
    if (getCurrentView()) {
      getCurrentView()->handleKeyPress(e);
    }
    break;
  }
}
