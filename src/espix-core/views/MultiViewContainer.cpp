#include "MultiViewContainer.h"

using namespace std;

MultiViewContainer::MultiViewContainer() {
}

MultiViewContainer::MultiViewContainer(initializer_list<View *> l) : _subviews(l) {
}

void MultiViewContainer::addSubview(View *subview) {
  subview->setParentView(this);
  _subviews.add(subview);
}

void MultiViewContainer::removeSubview(View *subview) {
  subview->setParentView(NULL);
  _subviews.remove(subview);
}
