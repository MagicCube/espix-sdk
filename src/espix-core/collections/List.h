#pragma once

#include <Arduino.h>

using namespace std;

// Represents a list of items.
template <typename T> class List {
public:
  // Initializes a new instance of the List class.
  List() {
  }
  List(initializer_list<T> l) : _vector(l) {
  }

  // Iterator for begin.
  typename vector<T>::iterator begin() {
    return _vector.begin();
  }

  // Iterator for end.
  typename vector<T>::iterator end() {
    return _vector.end();
  }

  // Gets the number of items in the list.
  int size() {
    return _vector.size();
  }

  // Searches for the specified item and returns the zero-based index of the first occurrence within
  // the list. Returns -1 if not found.
  int indexOf(T item) {
    auto lower = lower_bound(_vector.begin(), _vector.end(), item);
    if (lower != _vector.end()) {
      auto index = lower - _vector.begin();
      return index;
    }
    return -1;
  }

  // Returns true if the given item is in the list.
  bool includes(T item) {
    return indexOf(item) != -1;
  }

  // Add the specific item to the list.
  void add(T item) {
    _vector.push_back(item);
  }

  // Remove the specific item from the list.
  void remove(T item) {
    int index = indexOf(item);
    if (index != -1) {
      removeAt(index);
    }
  }

  // Remove the item with specific index from the list.
  void removeAt(int index) {
    _vector.erase(_vector.begin() + index);
  }

  // Removes all elements from the list.
  void clear() {
    _vector.clear();
  }

private:
  vector<T> _vector;
};
