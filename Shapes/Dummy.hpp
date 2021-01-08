class DummyMoveableObject : public MoveableObject {
 public:
  DummyMoveableObject() : MoveableObject(Vector2f{0.0, 0.0}) {}
	void move(const Vector2f& velo) override {}
  void jump(const Vector2f& new_pos) override {}
  void setFillColor(const sf::Color col) override {}
  FloatRect getBound() override {return FloatRect();}
  void draw(RenderWindow& window) override {}
};