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
    if (to_add != nullptr)
    {
      if (count < N) 
      {
        store[count] = to_add;
        ++count;
      }
      else{
        fillGaps(to_add);
      }
    }
  }

  void fillGaps(const T &to_add){
    bool added = false;
    for (unsigned int i = 0; i < count; i++)
    {
      if ( store[i] == nullptr ) 
      { 
        store[i] = to_add; 
        break;
      }
    }
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

  void moveToBackground(const T &to_swap)
  {
    //to swap moet vooraan in de lijst komen te staan. dus eerst de index ervan zoeken.
    int index = -1;
    for(unsigned int i = 0; i < count; i++){ if ( store[i] == to_swap) { index = i; break; }} //check using mem adress
    if (index == -1) { std::cout << "i not found." << std::endl; break;}
    std::cout << "found i" << std::endl;
    //Index is nu bekend. dus nu index swappen met 0;
    T temp = store[0];
    store[0] = store[index];
    store[index] = temp;
  }

  void moveToForeground(const T &to_swap)
  {
    //to swap moet achteraan in de lijst komen te staan. dus eerst de index ervan zoeken.
    int index = -1;
    for(unsigned int i = 0; i < count; i++){ if ( store[i] == to_swap) { index = i; break; }} //check using mem adress

    //Index is nu bekend. dus nu index swappen met count;
    T temp = store[count];
    store[count] = store[index];
    store[index] = temp;
  }

  T *begin() { return store; }
  T *end() { return store + count; }

  const T *begin() const { return store; }
  const T *end() const { return store + count; }
};

#endif  // STORAGE_HPP