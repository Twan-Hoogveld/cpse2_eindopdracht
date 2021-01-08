#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "MoveableObject.hpp"

using sf::CircleShape;

class Circle : public MoveableObject {
 private:
  unsigned int diameter;
  Color color;
  CircleShape circle;

 public:
  Circle(const Vector2f& pos, unsigned int diameter, Color col = Color::White)
      : MoveableObject(pos), diameter(diameter), color(col) {
    circle.setRadius(diameter / 2);
    circle.setFillColor(col);
    circle.setPosition(pos);
  }

	void move(const Vector2f& velo) override
  {
    pos += velo;
  }

  void jump(const Vector2f& new_pos) override
  {
    pos = new_pos;
  }

  FloatRect getBound() override
  {
    return circle.getGlobalBounds();
  }

  void draw(RenderWindow& window) override
  {
    circle.setPosition(pos);
    window.draw(circle); 
  }

  sf::Color getOutlineColor(){
    return circle.getOutlineColor();
  }

  sf::Color getFillColor(){
    return circle.getFillColor();
  }

  void setFillColor(const sf::Color col) override{
    circle.setFillColor(col);
  }

};

#endif  // CIRCLE_HPP