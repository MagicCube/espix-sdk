#include "MultiViewContainer.h"

using namespace std;

MultiViewContainer::MultiViewContainer() {
  _subviews = new vector<View *>();
}

int MultiViewContainer::indexOfSubview(View *subview) {
  int index = -1;
  return index;
}

void MultiViewContainer::addSubview(View *subview) {
  _subviews->push_back(subview);
}
