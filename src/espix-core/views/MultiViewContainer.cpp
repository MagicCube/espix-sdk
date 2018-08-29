#include "MultiViewContainer.h"

MultiViewContainer::MultiViewContainer() : ViewContainer() {
}

ReadonlyList<View *> MultiViewContainer::getSubviews() {
  return _subviews;
}

void MultiViewContainer::addSubview(View *subview) {
  subview->setParentView(this);
  _subviews.add(subview);
}

void MultiViewContainer::addSubviews(List<View *> subviews) {
  for (auto subview : subviews) {
    addSubview(subview);
  }
}

void MultiViewContainer::removeSubview(View *subview) {
  subview->setParentView(NULL);
  _subviews.remove(subview);
}
