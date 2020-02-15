#include "NavigationContainer.h"

NavigationContainer::NavigationContainer() : ViewContainer() {
}

void NavigationContainer::setCurrentView(View *view, TransitionOptions transitionOptions) {
  ViewContainer::setCurrentView(view, transitionOptions);
  if (_statusBar) {
    _statusBar->setText(view->getTitle());
  }
}

View *NavigationContainer::getRootView() {
  return _rootView;
}

void NavigationContainer::setRootView(View *view, TransitionOptions options) {
  _navigationStack.clear();
  _rootView = view;
  setCurrentView(view, options);
}

StatusBar *NavigationContainer::getStatusBar() {
  return _statusBar;
}

void NavigationContainer::setStatusBar(StatusBar *view) {
  _statusBar = view;
  if (_statusBar) {
    _statusBar->setParentView(this);
    showStatusBar();
  } else {
    hideStatusBar();
  }
}

void NavigationContainer::showStatusBar() {
  if (_statusBar == NULL) {
    return;
  }
  if (!_statusBarVisible) {
    _statusBarVisible = true;
    _statusBar->setWidth(getWidth());
    _statusBar->setTop(-_statusBar->getHeight() - 1);
    setPaddings(Thickness(0, _statusBar->getHeight() + 1, 0, 0));
  }
}

void NavigationContainer::hideStatusBar() {
  if (_statusBarVisible) {
    _statusBarVisible = false;
    setPaddings(Thickness(0));
  }
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
  } else if (_statusBar && _statusBarVisible) {
    return _statusBar->shouldUpdate();
  }
  return false;
}

void NavigationContainer::update() {
  ViewContainer::update();
  if (_statusBar && _statusBarVisible) {
    _statusBar->tryUpdate();
  }
}

void NavigationContainer::render(CanvasContext *context) {
  ViewContainer::render(context);
  if (_statusBar && _statusBarVisible) {
    _statusBar->redraw();
    context->drawHorizontalLine(0, _statusBar->getHeight() + 1);
  }
}

void NavigationContainer::handleKeyPress(KeyEventArgs *e) {
  switch (e->keyCode) {
  case KEY_ENTER:
    if (getCurrentView()) {
      getCurrentView()->select();
    }
    break;
  case KEY_ESC:
    if (canPop()) {
      popView();
    } else {
      if (getCurrentView()) {
        getCurrentView()->handleKeyPress(e);
      }
    }
    break;
  default:
    if (getCurrentView()) {
      getCurrentView()->handleKeyPress(e);
    }
    break;
  }
}
