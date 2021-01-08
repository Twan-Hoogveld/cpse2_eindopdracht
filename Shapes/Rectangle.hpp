#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "MoveableObject.hpp"

using sf::RectangleShape;

class Rectangle : public MoveableObject {
  private:
    Vector2f pos2;
	  Vector2f diff_pos;
    Color color;
    RectangleShape rect;

  public:
    Rectangle(const Vector2f& pos, const Vector2f& pos2, Color col = Color::White)
      : MoveableObject(pos), pos2(pos2), color(col), rect{(pos2 - pos)} 
      {
		    diff_pos = pos2 - pos;
        rect.setFillColor(color);
        rect.setPosition(pos);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(color);
      }

  void move(const Vector2f& velo) override
  {
    	pos += velo;
	    pos2 += velo;
  };

  void jump(const Vector2f& new_pos) override
  {
    	pos = new_pos;
	    pos2 = new_pos + diff_pos;
  };

  FloatRect getBound() override 
  {
    	return rect.getGlobalBounds();
  };

  void draw(RenderWindow& window) override
  {
    rect.setPosition(pos);
	  window.draw(rect);
  };

  void setFillColor(const sf::Color col) override
  {
    rect.setFillColor(col);
  }

  void setOutlineColor(const sf::Color col) override
  {
    rect.setOutlineColor(col);
  }


  void setScale(const float x, const float y) override
  {
    rect.setScale(x,y);
  }

  sf::Vector2f getScale() override
  {
    return rect.getScale();
  }

};

#endif  // RECTANGLE_HPP