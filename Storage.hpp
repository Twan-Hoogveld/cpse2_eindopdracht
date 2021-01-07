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
    bool added = false;

    if (count >= 1){ //If there is at least 1 element.
      for(unsigned int i = 0; i < count; i++){
        if (store[i] == nullptr) //if we find a nullptr
        { 
          store[i] = to_add;
          added = true;
        }
      }
    }
    if (count < N && added == false) {
      store[count] = to_add;
      ++count;
    }
  }

  void fillGaps(){
    std::cout << "=========FILL GAPS==============" << std::endl;
    for (const auto x : store)
    {
      if ( x != nullptr ) { std::cout << x << std::endl;}
    }
    std::cout << "=========FILL GAPS END ==============" << std::endl;
  }

  void remove(const T &to_remove)
  {
    std::cout << "start of remove" << std::endl;
    for (unsigned i = 0; i < count; i++)
    {
      if(store[i] != nullptr)
      {
        if(store[i] == to_remove)
        {
          store[i] = nullptr; //Segmentation fault when you reach store[i] now and try to do something with it.
        }
      }
    }
    std::cout << "end of remove" << std::endl;
    fillGaps();
  }

  T *begin() { return store; }
  T *end() { return store + count; }

  const T *begin() const { return store; }
  const T *end() const { return store + count; }
};

#endif  // STORAGE_HPP