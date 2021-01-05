#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "Shapes/MoveableObject.hpp"

template <typename T, unsigned int N>
class Storage {
 private:
  T store[N];
  unsigned int count = 0;

 public:
  void add(const T &to_add) {
    if (count < N) {
      store[count] = to_add;
      ++count;
    }
  }

  T *begin() { return store; }
  T *end() { return store + count; }

  const T *begin() const { return store; }
  const T *end() const { return store + count; }
};

#endif  // STORAGE_HPP