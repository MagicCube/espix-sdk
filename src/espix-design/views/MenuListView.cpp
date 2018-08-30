#include "MenuListView.h"

MenuListView::MenuListView() : View() {
}

void MenuListView::render(CanvasContext *context) {
  int start = _scrollIndex;
  int end = start + _getFullyVisibleItemCount() + 1;
  if (end > _items.size() - 1) {
    end = _items.size() - 1;
  }
  for (int i = start; i <= end; i++) {
    auto item = _items[i];
    context->drawString(item.text, 0, HEIGHT_OF_MENU_ITEM * i + 1);
  }
}


int MenuListView::_getFullyVisibleItemCount() {
  return getClientHeight() / HEIGHT_OF_MENU_ITEM;
}
