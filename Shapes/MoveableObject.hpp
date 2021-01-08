#ifndef MOVEABLESCREENOBJECT_HPP
#define MOVEABLESCREENOBJECT_HPP

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
  ~MoveableObject(){};

  virtual FloatRect getBound() = 0;
  virtual void draw(RenderWindow& window) = 0;
  virtual void move(const Vector2f& velo)  = 0;
  virtual void jump(const Vector2f& new_pos) = 0;
  virtual void setFillColor(const sf::Color col) = 0;
  void jump(const Vector2i& new_pos);
};

#endif  // MOVEABLESCREENOBJECT_HPP