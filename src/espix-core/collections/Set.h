#pragma once

#include <Arduino.h>

using namespace std;

// Represents a set of items.
template <typename T> class Set {
public:
  // Initializes a new instance of the Set class.
  Set() {
  }

  // Iterator for begin.
  typename vector<T>::iterator begin() {
    return _vector.begin();
  }

  // Iterator for end.
  typename vector<T>::iterator end() {
    return _vector.end();
  }

  // Gets the number of items in the set.
  int size() {
    return _vector.size();
  }

  // Searches for the specified item and returns the zero-based index of the first occurrence within
  // the set. Returns -1 if not found.
  int indexOf(T item) {
    auto lower = lower_bound(_vector.begin(), _vector.end(), item);
    if (lower != _vector.end()) {
      auto index = lower - _vector.begin();
      return index;
    }
    return -1;
  }

  // Returns true if the given item is in the set.
  bool includes(T item) {
    return indexOf(item) != -1;
  }

  // Add the specific item to the set.
  // Nothing happens if the item has been already included.
  void add(T item) {
    if (!includes(item)) {
      _vector.push_back(item);
    }
  }

  // Remove the specific item from the set.
  void remove(T item) {
    int index = indexOf(item);
    if (index != -1) {
      removeAt(index);
    }
  }

  // Remove the item with specific index from the set.
  void removeAt(int index) {
    _vector.erase(_vector.begin() + index);
  }

  // Removes all elements from the set.
  void clear() {
    _vector.clear();
  }

private:
  vector<T> _vector;
};
