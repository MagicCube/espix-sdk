#pragma once

#include <Arduino.h>

#include "ViewContainer.h"

#include "../collections/List.h"

// Represents a container which can contain multiple views.
class MultiViewContainer : public ViewContainer {
public:
  MultiViewContainer();
  MultiViewContainer(initializer_list<View *> l) {
    addSubviews(l);
  }

  // Returns a readonly list of subviews of the container.
  ReadonlyList<View *> getSubviews();

  // Add the specific subview to the container.
  void addSubview(View *subview);

  // Add the multiple subviews to the container.
  void addSubviews(List<View *> subviews);

  // Remove the specific subview from the container.
  void removeSubview(View *subview);

protected:
  List<View *> _subviews;
};
