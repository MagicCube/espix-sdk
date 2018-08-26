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
  }
  if (transitionOptions.direction != TRANSITION_DIRECTION_NONE) {
    int startValue = 0;
    switch (transitionOptions.direction) {
    case TRANSITION_TO_LEFT:
    case TRANSITION_TO_RIGHT:
      startValue = transitionOptions.direction * getWidth();
      _mountView(view, startValue, 0);
      break;
    case TRANSITION_TO_TOP:
    case TRANSITION_TO_BOTTOM:
      startValue = transitionOptions.direction / 2 * getHeight();
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
      case TRANSITION_TO_LEFT:
      case TRANSITION_TO_RIGHT:
        _unmountingViewOffset = _viewOffset - direction * getWidth();
        break;
      case TRANSITION_TO_TOP:
      case TRANSITION_TO_BOTTOM:
        _unmountingViewOffset = _viewOffset - direction / 2 * getHeight();
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

void ViewContainer::render(DrawingContext *context) {
  if (_unmountingView) {
    auto direction = _viewTransition.getDirection();
    if (direction == TRANSITION_TO_LEFT || direction == TRANSITION_TO_RIGHT) {
      _unmountingView->getDrawingContext()->setOffset(_unmountingViewOffset);
    } else if (direction == TRANSITION_TO_TOP || direction == TRANSITION_TO_BOTTOM) {
      _unmountingView->getDrawingContext()->setOffset(0, _unmountingViewOffset);
    }
    _unmountingView->redraw();
  }
  if (_currentView) {
    auto direction = _viewTransition.getDirection();
    if (direction == TRANSITION_TO_LEFT || direction == TRANSITION_TO_RIGHT) {
      _currentView->getDrawingContext()->setOffset(_viewOffset);
    } else if (direction == TRANSITION_TO_TOP || direction == TRANSITION_TO_BOTTOM) {
      _currentView->getDrawingContext()->setOffset(0, _viewOffset);
    }
    _currentView->redraw();
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
  _currentView->willMount();
  auto viewContainerContext = getDrawingContext();
  auto viewContext = _currentView->getDrawingContext();
  viewContext->setSize(viewContainerContext->getWidth(), viewContainerContext->getHeight());
  viewContext->setOffset(offsetX, offsetY);
  _currentView->redraw(true);
  _currentView->didMount();
}
