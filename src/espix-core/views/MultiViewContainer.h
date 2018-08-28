#pragma once

#include <Arduino.h>

#include "../collections/List.h"

#include "ViewContainer.h"

// Represents a container which can contains multiple views.
class MultiViewContainer : public ViewContainer {
public:
  // Creates a new instance of the MultiViewContainer class.
  MultiViewContainer();
  MultiViewContainer(initializer_list<View *> l);

  // Add the specific subview.
  void addSubview(View *subview);

  // Remove the specific subview.
  void removeSubview(View *subview);

protected:
  List<View *> _subviews;
};
