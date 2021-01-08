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
    if (to_add != nullptr)
    {
      if (count >= 1)
      { //If there is at least 1 element.
        for(unsigned int i = 0; i < count; i++){
          if (store[i] == nullptr) //if we find a nullptr
          { 
            store[i] = to_add;
            added = true;
          }
        }
      }
      if (count < N && added == false) 
      {
        store[count] = to_add;
        ++count;
      }
      else{
        std::cout << " can't find empty spot, so we check for nullptr and replace that."
        fillGaps(to_add);
      }
    }
  }

  void fillGaps(const T &to_add){
    std::cout << "=========FILL GAPS==============SHOULD PRINT ALL ALIVE OBJECTS" << std::endl;
    for (unsigned int i = 0; i < count; i++)
    {
      if ( store[i] == nullptr ) { store[i] = to_add; }
    }
    std::cout << "=========FILL GAPS END ==============" << std::endl;
  }

  void showStack(){
    for (const auto x : store) 
    {
      std::cout << x << std::endl;
    }
    std::cout << "======= this was the stack =========" << std::endl;
  }

  void remove(const T &to_remove)
  {
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
  }

  T *begin() { return store; }
  T *end() { return store + count; }

  const T *begin() const { return store; }
  const T *end() const { return store + count; }
};

#endif  // STORAGE_HPP