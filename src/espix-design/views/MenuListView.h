#pragma once

#include <Arduino.h>

#define HEIGHT_OF_MENU_ITEM 15

#include "../../espix-core/views/View.h"

#include "../../espix-core/collections/List.h"

#include "MenuItem.h"

class MenuListView : public View {
public:
  MenuListView();

  void render(CanvasContext *context);

private:
  int _getFullyVisibleItemCount();

  List<MenuItem> _items;

  int _selectedIndex = -1;
  int _scrollIndex = 0;
};
