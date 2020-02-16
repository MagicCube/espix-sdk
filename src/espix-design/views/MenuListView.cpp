#include "MenuListView.h"

MenuListView::MenuListView() : View() {
}

MenuListView::MenuListView(initializer_list<MenuItem> l) : _items(l) {
  MenuListView();
  setDirty();
}

int MenuListView::getSelectedIndex() {
  return _selectedIndex;
}

ReadonlyList<MenuItem> MenuListView::getItems() {
  return _items;
}

MenuItem MenuListView::getItem(int index) {
  return _items[index];
}

void MenuListView::addItem(MenuItem item) {
  _items.add(item);
  setDirty();
}

void MenuListView::clearItems() {
  _items.clear();
  setDirty();
}

void MenuListView::selectItem(int index) {
  if (index < 0) {
    index = 0;
  } else if (index >= _items.size()) {
    index = _items.size() - 1;
  }
  if (_selectedIndex != index) {
    _selectedIndex = index;
    setDirty();
  }
}

void MenuListView::selectItem(String key) {
  int i = 0;
  for (auto item : _items) {
    if (item.key && item.key.equals(key)) {
      selectItem(i);
      return;
    }
    i++;
  }
}

void MenuListView::selectNextItem() {
  selectItem(_selectedIndex + 1);
}

void MenuListView::selectPrevItem() {
  selectItem(_selectedIndex - 1);
}

void MenuListView::render(CanvasContext *context) {
  int fullyVisibleItemCount = _getFullyVisibleItemCount();

  if (_selectedIndex < fullyVisibleItemCount) {
    _scrollIndex = 0;
  } else {
    _scrollIndex = _selectedIndex - fullyVisibleItemCount + 1;
  }

  int start = _scrollIndex;
  int end = start + fullyVisibleItemCount + 1;
  if (end > _items.size() - 1) {
    end = _items.size() - 1;
  }
  int row = 0;
  for (int i = start; i <= end; i++) {
    auto item = _items[i];
    bool selected = i == _selectedIndex;
    int top = HEIGHT_OF_MENU_ITEM * row;
    if (selected) {
      context->fillRect(0, top, getClientWidth(), HEIGHT_OF_MENU_ITEM);
      context->setColor(Color::BLACK);
    } else {
      context->setColor(Color::WHITE);
    }
    context->drawString(item.text, 8, top + 1);
    row++;
  }
  context->setColor(Color::WHITE);
}

void MenuListView::handleKeyPress(KeyEventArgs *e) {
  switch (e->keyCode) {
  case KEY_ENTER:
    select();
    break;
  case KEY_UP_ARROW:
  case KEY_LEFT_ARROW:
    selectPrevItem();
    break;
  case KEY_DOWN_ARROW:
  case KEY_RIGHT_ARROW:
    selectNextItem();
    break;
  }
}

void MenuListView::handleScroll(ScrollEventArgs *e) {
  if (e->delta > 0) {
    selectNextItem();
  } else {
    selectPrevItem();
  }
}

int MenuListView::_getFullyVisibleItemCount() {
  return getClientHeight() / HEIGHT_OF_MENU_ITEM;
}
