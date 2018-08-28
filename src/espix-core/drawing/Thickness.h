#pragma once

// Describes thickness of a frame.
// Thickness can be border, margin or padding.
struct Thickness {
  Thickness() {
    left = 0;
    right = 0;
    top = 0;
    bottom = 0;
  }

  Thickness(int all) {
    left = all;
    right = all;
    top = all;
    bottom = all;
  }

  Thickness(int horizontal, int vertical) {
    left = horizontal;
    right = horizontal;
    top = vertical;
    bottom = vertical;
  }

  Thickness(int p_left, int p_top, int p_right, int p_bottom) {
    left = p_left;
    right = p_right;
    top = p_top;
    bottom = p_bottom;
  }

  int left = 0;
  int right = 0;
  int top = 0;
  int bottom = 0;
};
