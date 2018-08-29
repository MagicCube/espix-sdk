#include "CarouselContainer.h"

CarouselContainer::CarouselContainer() : MultiViewContainer() {
}

int CarouselContainer::getCurrentSubviewIndex() {
  return this->_subviews.size() > 0 ? _currentSubviewIndex : -1;
}

void CarouselContainer::setCurrentSubviewIndex(int index, TransitionOptions options) {
  slideToSubview(index, options);
}

TransitionOrientation CarouselContainer::getTransitionOrientation() {
  return _transitionOrientation;
}

void CarouselContainer::setTransitionOrientation(TransitionOrientation orientation) {
  _transitionOrientation = orientation;
}

void CarouselContainer::slideToSubview(View *view, TransitionOptions options) {
  if (_subviews.size() == 0) {
    return;
  }
  int index = this->_subviews.indexOf(view);
  int curIndex = getCurrentSubviewIndex();
  if (curIndex == index) {
    return;
  }
  if (index != -1) {
    if (options.direction == TransitionDirection::AUTO) {
      auto orientation = getTransitionOrientation();
      if (orientation == TransitionOrientation::NONE) {
        options.direction = TransitionDirection::NONE;
      } else if (curIndex == -1) {
        options.direction = TransitionDirection::NONE;
      } else if (index > curIndex) {
        options.direction = _computeTransitionDirection(1);
      } else if (index < curIndex) {
        options.direction = _computeTransitionDirection(-1);
      }
    }
    _currentSubviewIndex = index;
    setCurrentView(view, options);
  }
}

void CarouselContainer::slideToSubview(int index, TransitionOptions options) {
  if (_subviews.size() == 0) {
    return;
  }
  if (index < 0) {
    index = _subviews.size() - 1;
  } else if (index >= _subviews.size()) {
    index = 0;
  }
  auto view = _subviews[index];
  slideToSubview(view, options);
}

void CarouselContainer::slideToFirstSubview() {
  slideToSubview(0);
}

void CarouselContainer::slideToLastSubview() {
  slideToSubview(_subviews.size() - 1);
}

void CarouselContainer::slideToNextSubview() {
  slideToSubview(_currentSubviewIndex + 1, _computeTransitionDirection(1));
}

void CarouselContainer::slideToPrevSubview() {
  slideToSubview(_currentSubviewIndex - 1, _computeTransitionDirection(-1));
}

void CarouselContainer::handleKeyPress(KeyEventArgs e) {
  auto orientation = getTransitionOrientation();
  if (orientation == TransitionOrientation::HORIZONTAL) {
    if (e.keyCode == KEY_LEFT_ARROW) {
      slideToPrevSubview();
    } else if (e.keyCode == KEY_RIGHT_ARROW) {
      slideToNextSubview();
    }
  } else {
    if (e.keyCode == KEY_UP_ARROW) {
      slideToPrevSubview();
    } else if (e.keyCode == KEY_DOWN_ARROW) {
      slideToNextSubview();
    }
  }
}

void CarouselContainer::handleScroll(ScrollEventArgs e) {
  if (e.delta < 0) {
    slideToPrevSubview();
  } else {
    slideToNextSubview();
  }
}

TransitionDirection CarouselContainer::_computeTransitionDirection(int d) {
  if (d == 0) {
    return TransitionDirection::NONE;
  } else if (d > 0) {
    return _transitionOrientation == TransitionOrientation::HORIZONTAL ? TransitionDirection::LEFT
                                                                       : TransitionDirection::UP;
  } else {
    return _transitionOrientation == TransitionOrientation::HORIZONTAL ? TransitionDirection::RIGHT
                                                                       : TransitionDirection::DOWN;
  }
}
