#pragma once

// Stores a set of four integers that represent the location and size of a rectangle.
struct Rectangle {
  Rectangle(int p_left = 0, int p_top = 0, int p_width = 0, int p_height = 0) {
    left = p_left;
    top = p_top;
    width = p_width;
    height = p_height;
  }

  void copyFrom(Rectangle rectangle) {
    left = rectangle.left;
    top = rectangle.top;
    width = rectangle.width;
    height = rectangle.height;
  }

  int left = 0;
  int top = 0;
  int width = 0;
  int height = 0;
};
