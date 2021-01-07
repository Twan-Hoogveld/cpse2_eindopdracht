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

  void remove(const T &to_remove)
  {
    std::cout << "Will Remove " << to_remove << std::endl;
    for (unsigned i = 0; i < count; i++)
    {
      if(store[i] == to_remove)
      {
        store[i] == nullptr;
        std::cout << store[i] << std::endl;
      }
    }
  }

  T *begin() { return store; }
  T *end() { return store + count; }

  const T *begin() const { return store; }
  const T *end() const { return store + count; }
};

#endif  // STORAGE_HPP