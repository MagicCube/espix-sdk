#include "MultiViewContainer.h"

using namespace std;

MultiViewContainer::MultiViewContainer() {
}

int MultiViewContainer::indexOfSubview(View *subview) {
  int index = -1;
  return index;
}

void MultiViewContainer::addSubview(View *subview) {
  subview->setParentView(this);
  _subviews.add(subview);
}

void MultiViewContainer::removeSubview(View *subview) {
  subview->setParentView(NULL);
  _subviews.remove(subview);
}
