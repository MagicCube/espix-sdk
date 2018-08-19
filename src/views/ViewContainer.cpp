#include "ViewContainer.h"

#include "../drawings/Screen.h"

ViewContainer::ViewContainer() {
  _viewTransition = new Transition();
}

View *ViewContainer::getView() {
  return _view;
}

bool ViewContainer::isTransitioning() {
  return _viewTransition->isRunning();
}

void ViewContainer::setView(View *view, TransitionOptions transitionOptions) {
  if (_view != NULL) {
    _unmountingView = _view;
    _view->willUnmount();
  }
  if (transitionOptions.direction != TRANSITION_DIRECTION_NONE) {
    int startValue = 0;
    if (isTransitioning()) {
      startValue = _viewOffset;
    } else {
      switch (transitionOptions.direction) {
      case TRANSITION_TO_LEFT:
      case TRANSITION_TO_RIGHT:
        startValue = transitionOptions.direction * getWidth();
        break;
      default:
        break;
      }
    }
    _viewTransition->start(startValue, 0, transitionOptions);
    _mountView(view, startValue);
  } else {
    _unmountingView = NULL;
    _mountView(view);
  }
}

bool ViewContainer::shouldUpdate(ViewUpdateOptions options) {
  if (_view) {
    return isTransitioning() || _view->shouldUpdate(options);
  }
  return false;
}

void ViewContainer::update(ViewUpdateOptions options) {
  if (_view) {
    if (_viewTransition->isRunning()) {
      _viewOffset = _viewTransition->getValue();
      TRANSITION_DIRECTION direction = _viewTransition->getOptions().direction;
      switch (direction) {
      case TRANSITION_TO_LEFT:
      case TRANSITION_TO_RIGHT:
        _unmountingViewOffset = _viewOffset - direction * getWidth();
        break;
      default:
        break;
      }
      if (_viewTransition->isTimeout()) {
        _unmountingView = NULL;
        _viewTransition->stop();
      }
    }
    _view->update(options);
  }
}

void ViewContainer::render(DrawingContext *context) {
  DrawingContext *viewContext;
  if (_unmountingView) {
    viewContext = _unmountingView->getDrawingContext();
    viewContext->setOffset(_unmountingViewOffset);
    _unmountingView->render(viewContext);
  }
  if (_view) {
    viewContext = _view->getDrawingContext();
    viewContext->setOffset(_viewOffset);
    _view->render(viewContext);
  }
}

void ViewContainer::handleKeyPress(KeyCode keyCode) {
  if (_view) {
    _view->handleKeyPress(keyCode);
  }
}

void ViewContainer::_mountView(View *view, int offsetX, int offsetY) {
  _view = view;
  _view->willMount();
  DrawingContext *viewContainerContext = getDrawingContext();
  DrawingContext *viewContext = _view->getDrawingContext();
  viewContext->setSize(viewContainerContext->getWidth(), viewContainerContext->getHeight());
  viewContext->setOffset(offsetX, offsetY);
  redraw(true);
  _view->didMount();
}
