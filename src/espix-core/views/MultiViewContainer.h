#pragma once

#include <Arduino.h>

#include "../collections/Set.h"

#include "ViewContainer.h"

// Represents a container which can contains multiple views.
class MultiViewContainer : public ViewContainer {
public:
  // Initializes a new instance of the MultiViewContainer class.
  MultiViewContainer();

  // Add the specific subview.
  void addSubview(View *subview);

  // Remove the specific subview.
  void removeSubview(View *subview);

protected:
  Set<View *> _subviews;
};
