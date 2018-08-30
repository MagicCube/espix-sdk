#pragma once

#include <Arduino.h>

#define HEIGHT_OF_MENU_ITEM 15

#include "../../espix-core/views/View.h"

#include "../../espix-core/collections/List.h"

#include "MenuItem.h"

class MenuListView : public View {
public:
  MenuListView();
  MenuListView(initializer_list<MenuItem> l);

  void selectItem(int index);
  void selectItem(String key);
  void selectNextItem();
  void selectPrevItem();

  void render(CanvasContext *context);

  void handleKeyPress(KeyEventArgs e);
  void handleScroll(ScrollEventArgs e);

private:
  int _getFullyVisibleItemCount();
  void _renderItem(CanvasContext *context, int index);

  List<MenuItem> _items;

  int _selectedIndex = 0;
  int _scrollIndex = 0;
};
