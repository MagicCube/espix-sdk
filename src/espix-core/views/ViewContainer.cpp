#include "ViewContainer.h"

ViewContainer::ViewContainer() : View() {
}

View *ViewContainer::getCurrentView() {
  return _currentView;
}

bool ViewContainer::isTransitioning() {
  return _viewTransition.isRunning();
}

void ViewContainer::setCurrentView(View *view, TransitionOptions transitionOptions) {
  if (_currentView) {
    _unmountingView = _currentView;
    _currentView->willUnmount();
  }
  if (transitionOptions.direction != TransitionDirection::NONE) {
    int startValue = 0;
    int endValue = 0;
    switch (transitionOptions.getOrientation()) {
    case TransitionOrientation::HORIZONTAL:
      startValue = (int)transitionOptions.direction * getWidth();
      _mountView(view, startValue, 0);
      break;
    case TransitionOrientation::VERTICAL:
      startValue = (int)transitionOptions.direction / 2 * getHeight();
      _mountView(view, 0, startValue);
      break;
    default:
      break;
    }
    _viewTransition.start(startValue, endValue, transitionOptions);
  } else {
    _unmountView();
    _mountView(view);
  }
}

void ViewContainer::setPaddings(Thickness paddings) {
  View::setPaddings(paddings);
  if (_currentView) {
    _currentView->setBounds(getClientBounds());
  }
}

void ViewContainer::setBounds(Rectangle bounds) {
  View::setBounds(bounds);
  if (_currentView) {
    _currentView->setBounds(getClientBounds());
  }
}

bool ViewContainer::shouldUpdate() {
  if (isDirty()) {
    return true;
  }
  if (_currentView) {
    return isTransitioning() || _currentView->shouldUpdate();
  }
  return false;
}

void ViewContainer::update() {
  if (_currentView) {
    _updateTransition();
    _currentView->tryUpdate();
  }
}

void ViewContainer::render(CanvasContext *context) {
  if (_unmountingView) {
    _unmountingView->redraw();
  }
  if (_currentView) {
    _currentView->redraw();
  }
}

void ViewContainer::select() {
  if (_currentView) {
    _currentView->select();
  }
}

void ViewContainer::handleKeyPress(KeyEventArgs e) {
  if (_currentView) {
    _currentView->handleKeyPress(e);
  }
}

void ViewContainer::handleScroll(ScrollEventArgs e) {
  if (_currentView) {
    _currentView->handleScroll(e);
  }
}

void ViewContainer::_mountView(View *view, int offsetX, int offsetY) {
  _currentView = view;
  _currentView->setParentView(this);
  _currentView->willMount();
  _currentView->setBounds(Rectangle(offsetX, offsetY, getClientWidth(), getClientHeight()));
  _currentView->redraw();
  _currentView->didMount();
}

void ViewContainer::_unmountView() {
  if (_unmountingView) {
    _unmountingView = NULL;
  }
}

void ViewContainer::_updateTransition() {
  if (_viewTransition.isRunning()) {
    auto direction = _viewTransition.getDirection();
    auto orientation = _viewTransition.getOrientation();
    _viewOffset = _viewTransition.getValue();

    switch (orientation) {
    case TransitionOrientation::HORIZONTAL:
      _unmountingViewOffset = _viewOffset - (int)direction * getWidth();
      _unmountingView->moveTo(_unmountingViewOffset, 0);
      _currentView->moveTo(_viewOffset, 0);
      break;
    case TransitionOrientation::VERTICAL:
      _unmountingViewOffset = _viewOffset - (int)direction / 2 * getHeight();
      _unmountingView->moveTo(0, _unmountingViewOffset);
      _currentView->moveTo(0, _viewOffset);
      break;
    default:
      break;
    }

    if (_viewTransition.isTimeout()) {
      _unmountView();
      _viewTransition.stop();
    }
  }
}
