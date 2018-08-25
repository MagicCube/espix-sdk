#pragma once

#include <Arduino.h>

#include "ViewContainer.h"

class MultiViewContainer : public ViewContainer {
public:
  MultiViewContainer();

  int indexOfSubview(View *subview);

  void addSubview(View *subview);

protected:
  std::vector<View *> _subviews;
};
