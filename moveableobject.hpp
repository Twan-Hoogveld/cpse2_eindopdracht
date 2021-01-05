#ifndef MOVEABLESCREENOBJECT_HPP
#define MOVEABLESCREENOBJECT_HPP

#include "../Operators.hpp"
#include "SFML/Graphics.hpp"

using sf::Color;
using sf::FloatRect;
using sf::RenderWindow;
using sf::Vector2f;
using sf::Vector2i;
using std::ostream;

class MoveableObject {
 protected:
  Vector2f pos;

 public:
  MoveableObject(const Vector2f& pos) : pos(pos) {}

  virtual FloatRect getBound() = 0;
  virtual void draw(RenderWindow& window) = 0;
  virtual ostream& writeToFile(ostream& output) = 0;

  virtual void move(const Vector2f& velo)  = 0;
  virtual void jump(const Vector2f& new_pos) = 0;

  void jump(const Vector2i& new_pos)
  {
      jump(Vector2f(new_pos));
  };
};

class DummyMoveableObject : public MoveableObject {
    public:
        DummyMoveableObject() : MoveableObject(Vector2f{0.0, 0.0}) {}
        void move(const Vector2f& velo) override{};
        void jump(const Vector2f& new_pos) override{};
        FloatRect getBound() override{ return FloatRect();};
        void draw(RenderWindow& window) override{};
        ostream& writeToFile(ostream& output) override{return output;};
};

#endif  // MOVEABLESCREENOBJECT_HPP