#ifndef NOTMOVEABLESCREENOBJECT_HPP
#define NOTMOVEABLESCREENOBJECT_HPP

#include "SFML/Graphics.hpp"

using sf::Color;
using sf::FloatRect;
using sf::RenderWindow;
using sf::Vector2f;
using sf::Vector2i;
using std::ostream;

class NotMoveableObject {
 protected:
  const Vector2f pos;

 public:
  NotMoveableObject(const Vector2f& pos) : pos(pos) {}
  ~NotMoveableObject(){};
  virtual FloatRect getBound() = 0;
  virtual void draw(RenderWindow& window) = 0;
};

#endif  // NOTMOVEABLESCREENOBJECT_HPP