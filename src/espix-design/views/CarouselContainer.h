#pragma once

#include <Arduino.h>

#include "../../espix-core/views/MultiViewContainer.h"

class CarouselContainer : public MultiViewContainer {
public:
  CarouselContainer();
  CarouselContainer(initializer_list<View *> l) : MultiViewContainer(l) {
  }

  int getCurrentSubviewIndex();
  void setCurrentSubviewIndex(int index, TransitionOptions options = TRANSITION_OPTIONS_AUTO);

  TransitionOrientation getTransitionOrientation();
  void setTransitionOrientation(TransitionOrientation orientation);

  void slideToSubview(View *view, TransitionOptions options = TRANSITION_OPTIONS_AUTO);
  void slideToSubview(int index, TransitionOptions options = TRANSITION_OPTIONS_AUTO);
  void slideToFirstSubview();
  void slideToLastSubview();
  void slideToNextSubview();
  void slideToPrevSubview();

  void handleKeyPress(KeyEventArgs e);
  void handleScroll(ScrollEventArgs e);

private:
  TransitionDirection _computeTransitionDirection(int d);
  int _currentSubviewIndex = -1;
  TransitionOrientation _transitionOrientation;
};
