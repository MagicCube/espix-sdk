#pragma once

#include <Arduino.h>

#include "ViewContainer.h"

#include "../collections/List.h"

// Represents a container which can contain multiple views.
class MultiViewContainer : public ViewContainer {
public:
  MultiViewContainer();

  // Returns a readonly list of subviews of the container.
  ReadonlyList<View *> getSubviews();

  // Add the specific subview to the container.
  void addSubview(View *subview);

  // Remove the specific subview from the container.
  void removeSubview(View *subview);

private:
  List<View *> _subviews;
};
