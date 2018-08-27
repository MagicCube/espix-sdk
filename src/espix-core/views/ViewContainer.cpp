#include "ViewContainer.h"

ViewContainer::ViewContainer() {
}

View *ViewContainer::getCurrentView() {
  return _currentView;
}

bool ViewContainer::isTransitioning() {
  return _viewTransition.isRunning();
}

void ViewContainer::setView(View *view, TransitionOptions transitionOptions) {
  if (_currentView) {
    _unmountingView = _currentView;
    _currentView->willUnmount();
    _currentView->setParentView(NULL);
  }
  if (transitionOptions.direction != TransitionDirection::NONE) {
    int startValue = 0;
    switch (transitionOptions.direction) {
    case TransitionDirection::LEFT:
    case TransitionDirection::RIGHT:
      startValue = (int)transitionOptions.direction * getWidth();
      _mountView(view, startValue, 0);
      break;
    case TransitionDirection::UP:
    case TransitionDirection::DOWN:
      startValue = (int)transitionOptions.direction / 2 * getHeight();
      _mountView(view, 0, startValue);
      break;
    default:
      break;
    }
    _viewTransition.start(startValue, 0, transitionOptions);
  } else {
    _unmountingView = NULL;
    _mountView(view);
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
    if (_viewTransition.isRunning()) {
      _viewOffset = _viewTransition.getValue();
      auto direction = _viewTransition.getOptions().direction;
      switch (direction) {
      case TransitionDirection::LEFT:
      case TransitionDirection::RIGHT:
        _unmountingViewOffset = _viewOffset - (int)direction * getWidth();
        break;
      case TransitionDirection::UP:
      case TransitionDirection::DOWN:
        _unmountingViewOffset = _viewOffset - (int)direction / 2 * getHeight();
        break;
      default:
        break;
      }
      if (_viewTransition.isTimeout()) {
        _unmountingView = NULL;
        _viewTransition.stop();
      }
    }
    _currentView->tryUpdate();
  }
}

void ViewContainer::render(CanvasContext *context) {
  if (_unmountingView) {
    auto direction = _viewTransition.getDirection();
    if (direction == TransitionDirection::LEFT || direction == TransitionDirection::RIGHT) {
      _unmountingView->moveTo(_unmountingViewOffset, 0);
    } else if (direction == TransitionDirection::UP || direction == TransitionDirection::DOWN) {
      _unmountingView->moveTo(0, _unmountingViewOffset);
    }
    _unmountingView->redraw(getCanvasContext());
  }
  if (_currentView) {
    auto direction = _viewTransition.getDirection();
    if (direction == TransitionDirection::LEFT || direction == TransitionDirection::RIGHT) {
      _currentView->moveTo(_viewOffset, 0);
    } else if (direction == TransitionDirection::UP || direction == TransitionDirection::DOWN) {
      _currentView->moveTo(0, _viewOffset);
    }
    _currentView->redraw(getCanvasContext());
  }
}

void ViewContainer::handleKeyPress(KeyCode keyCode) {
  if (_currentView) {
    _currentView->handleKeyPress(keyCode);
  }
}

void ViewContainer::handleScroll(int delta) {
  if (_currentView) {
    _currentView->handleScroll(delta);
  }
}

void ViewContainer::_mountView(View *view, int offsetX, int offsetY) {
  _currentView = view;
  _currentView->setParentView(this);
  _currentView->willMount();
  _currentView->setBounds(offsetX, offsetY, getWidth(), getHeight());
  _currentView->redraw(getCanvasContext(), true);
  _currentView->didMount();
}
