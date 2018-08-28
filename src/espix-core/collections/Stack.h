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

  T top() {
    return _vector.back();
  }

  // Gets the number of items in the stack.
  int size() {
    return _vector.size();
  }

  // Push the specific item to the stack.
  void push(T item) {
    return _vector.push_back(item);
  }

  // Pop the top item and return it.
  T pop() {
    if (_vector.empty()) {
      return NULL;
    }
    return _vector.pop_back();
  }

protected:
  vector<T> _vector;
};
