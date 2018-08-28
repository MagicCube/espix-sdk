#pragma once

#include <Arduino.h>

using namespace std;

// Represents a stack.
template <typename T> class Stack {
public:
  // Creates a new instance of the Stack class.
  Stack() {
  }
  Stack(initializer_list<T> l) : _vector(l) {
  }

  // Iterator for begin.
  typename vector<T>::iterator begin() {
    return _vector.begin();
  }

  // Iterator for end.
  typename vector<T>::iterator end() {
    return _vector.end();
  }

  // Returns the item on the top of the stack.
  T top() {
    return _vector.back();
  }

  // Gets the number of items in the stack.
  int size() {
    return _vector.size();
  }

  // Returns whether the list is empty.
  bool isEmpty() {
    return _vector.empty();
  }

  // Pushes the specific item to the stack.
  void push(T item) {
    return _vector.push_back(item);
  }

  // Pops the top item and return it.
  // Returns `NULL` if the stack is empty.
  T pop() {
    if (isEmpty()) {
      return NULL;
    }
    auto t = top();
    _vector.pop_back();
    return t;
  }

  // Removes all elements from the list.
  void clear() {
    this->_vector.clear();
  }

protected:
  vector<T> _vector;
};
